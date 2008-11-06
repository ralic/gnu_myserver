/*
MyServer
Copyright (C) 2002, 2003, 2004, 2006, 2007, 2008 Free Software Foundation, Inc.
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "stdafx.h"
#include <include/base/utility.h>

extern "C" {
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef WIN32
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifdef GRP
#include <grp.h>
#endif

#endif
}

#ifdef WIN32
#include <direct.h>
#endif

#ifdef HAVE_PTHREAD
Mutex Process::forkMutex;
#endif

/*!
 *Generate the arguments vector for execve.
 *\param args The output arguments vector to fill.
 *\param proc The executable.
 *\param additionalArgs additional arguments.
 */
int Process::generateArgList (const char **args, const char *proc, string &additionalArgs)
{
  args[0] = proc;
  
  const char *arg = additionalArgs.c_str ();
  int count = 1;
  int len = additionalArgs.length ();
  int start = 0;

  while((arg[start] == ' ') && (start < len))
    start++;

  for(int i = start; i < len; i++)
    {
      if(arg[i] == '"')
        {
          start = i++;
          while(additionalArgs[++i] != '"' && i < len);
          if(i == len)
            exit(1);

          if(count < 100)
            {
              args[count++] = &(additionalArgs[start + 1]);
              start = i + 1;
              additionalArgs[i] = '\0';
            }
          else
            break;
        }
      else if(arg[i] == ' ')
        {
          if(i - start <= 1)
            continue;
          if(count < 100)
            {
              args[count++] = &(additionalArgs[start]);
              additionalArgs[i] = '\0';

              while((arg[i] == ' ') && (i < len))
                i++;

              start = i + 1;
            }
          else
            break;
        }
    }
  if(count < 100 && len != start)
    {
      args[count++] = &(additionalArgs[start]);
    }

  args[count] = NULL;

  return 0;
}


/*!
 *Generate the env array for execve.
 *\param envp Enviroment variables array.
 *\param envString Enviroment values separed by '\0'.
 */
int Process::generateEnvString (const char **envp, char *envString)
{
  int i = 0;
  int index = 0;
 

  if(envString != NULL)
    {
      while(*(envString + i) != '\0')
        {
          envp[index] = envString + i;
          index++;
          
          while(*(envString + i++) != '\0');
        }
      envp[index] = NULL;
    }
  else
    envp[0] = NULL;
  return 0;
}



/*!
 *Spawn a new process.
 *
 *\param spi new process information.
 *\param waitEnd Specify if wait until the process finishes.
 *\param timeout The maximum amount to wait for the process.
 *
 *\return -1 on failure.
 *\return the new process identifier on success.
 */
int Process::exec(StartProcInfo* spi, bool waitEnd, u_long timeout)
{
  int ret = 0;
#ifdef NOT_WIN
  u_long count;
#endif
  pid = 0;
#ifdef WIN32
  /*!
   *Set the standard output values for the CGI process.
   */
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  const char *cwd;
  ZeroMemory( &si, sizeof(si));
  si.cb = sizeof(si);
  si.hStdInput = (HANDLE)spi->stdIn;
  si.hStdOutput = (HANDLE)spi->stdOut;
  si.hStdError = (HANDLE)spi->stdError;
  si.dwFlags = STARTF_USESHOWWINDOW;
  if(si.hStdInput || si.hStdOutput ||si.hStdError)
    si.dwFlags |= STARTF_USESTDHANDLES;
  si.wShowWindow = SW_HIDE;

  cwd = spi->cwd.length() ? (char*)spi->cwd.c_str() : 0;
  ZeroMemory( &pi, sizeof(pi) );
  ret = CreateProcess(NULL, (char*)spi->cmdLine.c_str(), NULL, NULL, TRUE,0,
                      spi->envString, cwd, &si, &pi);
  if(!ret)
    return (-1);
  pid = (u_long)pi.hProcess;

  if (waitEnd)
    {
      /*
       *Wait until the process stops its execution.
       */
      ret = WaitForSingleObject(pi.hProcess, timeout);

      if(ret == WAIT_FAILED)
        return (u_long)(-1);

      ret = CloseHandle( pi.hProcess );

      if(!ret)
        return (u_long)(-1);

      ret = CloseHandle( pi.hThread );

      if(!ret)
        return (u_long)(-1);

      return 0;
  }
  else
    {
      ret = CreateProcess(NULL, (char*)spi->cmdLine.c_str(), NULL, NULL, TRUE, 0,
                          spi->envString, cwd, &si, &pi);

      if(!ret)
        return (-1);

      pid = (*((int*)&pi.hProcess));

      return pid;
    }
#endif

#ifdef NOT_WIN
  pid = fork();

  if(pid < 0) // a bad thing happened
    return 0;

  if(pid == 0) // child
  {
    // Set env vars
    const char *envp[100];
    const char *args[100];

    if (generateArgList (args, spi->cmd.c_str(), spi->arg))
      exit (1);

    if (generateEnvString (envp, (char*) spi->envString))
      exit (1);

    // change to working dir
    if(spi->cwd.length())
    {
      ret = chdir((const char*)(spi->cwd.c_str()));
      if(ret == -1)
        exit(1);
    }
     // If stdOut is -1, pipe to /dev/null
    if((long)spi->stdOut == -1)
      spi->stdOut = (FileHandle)open("/dev/null", O_WRONLY);
    // map stdio to files
    ret = close(0); // close stdin
    if(ret == -1)
      exit (1);
    ret = dup2(spi->stdIn, 0);
    if(ret == -1)
      exit (1);
    ret = close(spi->stdIn);
    if(ret == -1)
      exit (1);
    ret = close(1); // close stdout
    if(ret == -1)
      exit (1);
    ret = dup2(spi->stdOut, 1);
    if(ret == -1)
      exit (1);
    ret = close(spi->stdOut);
    if(ret == -1)
      exit(1);
    //close(2); // close stderr
    //dup2((int)spi->stdError, 2);
    // Run the script
    ret = execve((const char*)args[0], 
                 (char* const*)args, (char* const*) envp);
    exit(0);

  }

  if (waitEnd)
  {
    //XXX: Fix polling.
    count = 0;
    for( ;  ; count++)
      {
        if(count >= timeout / 100)
          {
            kill(pid, SIGKILL);
            ret = -1;
            break;
          }
        ret = waitpid(pid, NULL, WNOHANG);
        if(ret == -1)
          {
            if(errno == ECHILD)
              return 0;
            else
              return (-1);
          }
        else if(ret != 0)
          {
            break;
          }
        Thread::wait(100);
      }

    if(ret == -1)
      return (-1);
    return 0;
  }
  else
    return pid;


#endif

}

/*!
 *Return a nonzero value if the process is still alive. A return value of zero
 *means the process is a zombie.
 */
int Process::isProcessAlive()
{
  if(pid == 0)
    return 0;
#ifdef WIN32
  u_long ec;
  int ret = GetExitCodeProcess(*((HANDLE*)&pid), &ec);
  if(ret == 0)
    return 0;
  if(ec == STILL_ACTIVE)
    return 1;
  return 0;
#endif

#ifdef NOT_WIN
  int status = 0;
#ifdef PROCESS_ALIVE_USEWAITPID
  int ret;
  do
  {
    ret = waitpid(pid, &status, WNOHANG);
  }
  while(!ret && errno == EINTR);
  if(!ret)
    return 1;
  return 0;
#else
  /*! Send the pseudo-signal 0 to check if the process is alive.  */
  int ret;
  do
  {
    ret = kill(pid, 0);
  }
  while(!ret && errno == EINTR);
  if(ret == 0)
    return 1;

  /*! Waitpid it to free the resource.  */
  waitpid(pid, &status, WNOHANG | WUNTRACED);

  return 0;
#endif

#endif
  return 0;
}

/*!
 *Execute a process and wait for its execution to be completed or the timeout, 
 *whatever happens before.
 *
 *\param spi The new process information.
 *\param timeout Maximum amount of time to wait for.
 *\return -1 on fails.
 *\return 0 on success.
 */
int Process::execAndWait (StartProcInfo *spi, u_long timeout)
{
  return exec(spi, true, timeout);
}

#ifdef HAVE_PTHREAD

/*!
 *Called in the parent before do a fork.
 */
void Process::forkPrepare()
{
  forkMutex.lock();
}

/*!
 *Called in the parent after the fork.
 */
void Process::forkParent()
{
  forkMutex.unlock();
}

/*!
 *Called in the child process after the fork.
 */
void Process::forkChild()
{
  forkMutex.unlock();  
}
#endif

/*!
 *Initialize the static process data.
 */
void Process::initialize()
{
#ifdef HAVE_PTHREAD
  forkMutex.init();
  pthread_atfork(forkPrepare, forkParent, forkChild);
#endif
}

/*!
 *Create the object.
 */
Process::Process()
{
  pid = 0;
}

/*!
 *Destroy the object.
 */
Process::~Process()
{

}

/*!
 *Terminate a process.
 *Return 0 on success.
 *Return nonzero on fails.
 */
int Process::terminateProcess()
{
  int ret;
  if(pid == 0)
    return 0;
#ifdef WIN32
  ret = TerminateProcess(*((HANDLE*)&pid),0);
  pid = 0;
  return (!ret);
#endif
#ifdef NOT_WIN
  ret = kill((pid_t)pid, SIGKILL);
  pid = 0;
  return ret;
#endif
}

/*!
 *Set the user identity for the process. Returns 0 on success.
 */
int Process::setuid(u_long uid)
{
#ifdef NOT_WIN
  return ::setuid(uid);
#endif
  return 0;
}

/*!
 *Set the group identity for the process. Returns 0 on success.
 */
int Process::setgid(u_long gid)
{
#ifdef NOT_WIN
  return ::setgid(gid);
#endif
  return 0;
}

/*!
 *Set the additional groups list for the process.
 */
int Process::setAdditionalGroups(u_long len, u_long *groups)
{
#ifdef NOT_WIN

#if HAVE_SETGROUPS
  u_long i;
  int ret;
  gid_t *gids = new gid_t[len];
  
  for(i = 0; i < len; i++)
    if(groups)
      gids[i] = (gid_t)groups[i];
    else
      gids[i] = (gid_t)0;

  ret = setgroups((size_t)0, gids) == -1;

  delete [] gids;

  if(errno == EPERM && len == 0)
    return 0;
  return ret;

#else
  return 0;
#endif

#else
  return 0;
#endif
}
