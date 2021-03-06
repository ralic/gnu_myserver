/*
MyServer
Copyright (C) 2002, 2003, 2004, 2006, 2008 Free Software Foundation, Inc.
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

#ifdef WIN32
# include <windows.h>
# include <io.h>
#endif

#include <Fl/Fl.H>
#include <Fl/fl_ask.H>

#include "language.h"
#include <include/base/string/stringutils.h>
#include <include/base/xml/xml_parser.h>
#include <include/base/file/file.h>
#include <include/base/file/files_utility.h>
#include "vector.h"
#include "fltkconfig.h"
#include "language.h"

#include <include/base/find_data/find_data.h>

extern "C"
{
#include <stdio.h>
#ifdef WIN32
# include <direct.h>
#elif HAVE_DL
# include <dlfcn.h>
# define HMODULE void *
#else
# define HMODULE void *
#endif
}

#ifndef intptr_t
# define intptr_t int
#endif

typedef char* (*registerNamePROC)(char*,int);

static void GetDynamicProtocols(const char *, Vector &);

///
/// Main function.
/// Intilize all supporting libraries and windows.
/// Gets the list of dynamic protocols and language files.
/// Loads the first avaible configuration.
/// Displays the main dialog.
/// Waits for FLTK to quit and dose clean up.
///
int main(int argc, char * argv[])
{
   char languages_path[MAX_PATH];
   char main_configuration_file[MAX_PATH];
   int conf_location = 0;
   XmlParser xmlFile;
   FindData fd;
   int fd_ret;
   bool langFound = true;
   bool confFound = true;
   int ret;

  LanguageXMLinit();
   /*! Initialize the SSL library. */
#ifndef DO_NOT_USE_SSL
   SSL_library_init();
   SSL_load_error_strings();
#endif

#ifdef WIN32
	/*!
   *Under windows we need to initialize the socket library before use it.
   */
	WSADATA wsaData;
	WSAStartup(MAKEWORD( 1, 1), &wsaData);

   // Find the language files:
   strncpy(languages_path, "languages/", MAX_PATH);
   fd_ret=fd.findfirst("languages/");
#else
   if(FilesUtility::fileExists("languages"))
     {
	strncpy(languages_path, "languages/", MAX_PATH);
     }
   else
     {
# ifdef PREFIX
	snprintf(languages_path, MAX_PATH, "%s/share/myserver/languages/", PREFIX);
# else
	strncpy(languages_path, "/usr/share/myserver/languages/", MAX_PATH);
# endif
     }
   if(!(FilesUtility::fileExists(languages_path)))
     {
	fl_alert("Languages directory not found.");
	langFound = false;
     }
   if(langFound)
     fd_ret=fd.findfirst(languages_path);
#endif

   // Search for myserver.xml
   /* Under an *nix environment look for .xml files in the following order.
    * 1) myserver executable working directory
    * 2) ~/.myserver/
    * 3) /etc/myserver/
    * 4) default files will be copied in myserver executable working
    */
#ifndef WIN32
   // just a little hack
   snprintf(main_configuration_file, MAX_PATH, "%s/.myserver/myserver.xml", getenv("HOME"));
#endif
   if(FilesUtility::fileExists("myserver.xml"))
     {
	conf_location = 1;
	strncpy(main_configuration_file,"myserver.xml", MAX_PATH);
     }
#ifndef WIN32
   else if(FilesUtility::fileExists(main_configuration_file))
     {
	conf_location = 2;
     }
   else if(FilesUtility::fileExists("/etc/myserver/myserver.xml"))
     {
	conf_location = 3;
	strncpy(main_configuration_file,"/etc/myserver/myserver.xml", MAX_PATH);
     }
#endif
     /*
      * If the myserver.xml files doesn't exist copy it from the default one.
      */
   else
     {
	conf_location = 1;
	strncpy(main_configuration_file,"myserver.xml", MAX_PATH);
	File inputF;
	File outputF;
	if(!FilesUtility::fileExists("myserver.xml.default"))
	  {  // no configuration files found
	     fl_alert("Default configuration files not found.  Loading empty values.");
	     confFound = false;
	     conf_location = 0;
	  }
	else
	  {  // Copy the default files
	     char buffer[512];
	     u_long nbr, nbw;
	     fl_alert("Configuration files not found.  Loading default files.");
	     inputF.openFile("myserver.xml.default", File::MYSERVER_OPEN_READ|File::MYSERVER_OPEN_IFEXISTS);
	     outputF.openFile("myserver.xml", File::MYSERVER_OPEN_WRITE|File::MYSERVER_OPEN_ALWAYS);
	     for(;;)
	       {
		  inputF.read(buffer, 512, &nbr );
		  if(nbr==0)
		    break;
		  outputF.writeToFile(buffer, nbr, &nbw);
	       }
	     inputF.close();
	     outputF.close();

	     if(FilesUtility::fileExists("MIMEtypes.xml.default"))
	       {
		  char buffer[512];
		  u_long nbr, nbw;
		  inputF.openFile("MIMEtypes.xml.default", File::MYSERVER_OPEN_READ|File::MYSERVER_OPEN_IFEXISTS);
		  outputF.openFile("MIMEtypes.xml", File::MYSERVER_OPEN_WRITE|File::MYSERVER_OPEN_ALWAYS);
		  for(;;)
		    {
		       inputF.read(buffer, 512, &nbr );
		       if(nbr==0)
			 break;
		       outputF.writeToFile(buffer, nbr, &nbw);
		    }
		  inputF.close();
		  outputF.close();
	       }

	     if(FilesUtility::fileExists("virtualhosts.xml.default"))
	       {
		  char buffer[512];
		  u_long nbr, nbw;
		  inputF.openFile("virtualhosts.xml.default", File::MYSERVER_OPEN_READ|
											File::MYSERVER_OPEN_IFEXISTS);
		  outputF.openFile("virtualhosts.xml", File::MYSERVER_OPEN_WRITE|
											 File::MYSERVER_OPEN_ALWAYS);
		  for(;;)
		    {
		       inputF.read(buffer, 512, &nbr );
		       if(nbr==0)
			 break;
		       outputF.writeToFile(buffer, nbr, &nbw);
		    }
		  inputF.close();
		  outputF.close();
	       }
	  }
     }

   // Initilize APIs
   XmlParser::startXML();
   // LanguageXMLinit handeled internaly

   // Load the language file for configure
   // Handeled internaly


   // Initilize the Dialogs
   MainDlg Configure;
   Configure.make_window();
   Configure.make_about();
   Configure.make_type();
   Configure.make_login();
   Configure.make_status();
   Configure.make_connections();
   Configure.make_regask();

   // Show the main window
   Configure.ConfDlg->show(argc, argv);

   // Load the language file names
   Configure.Language->clear();
   if(langFound)
     {
	do
	  {
	     char dir[MAX_PATH];
	     char filename[MAX_PATH];
	     if(fd.name[0] == '.')
	       continue;
	     FilesUtility::splitPath(fd.name,dir,filename);
	     if(strcmpi(&(filename[strlen(filename) - 3]), "xml") == 0)
	       Configure.Language->add(filename, 0, 0, 0, 0);
	  }
	while(!fd.findnext());
	fd.findclose();
     }

   // Load the dynamic protocol names
   Vector list;
   if(FilesUtility::fileExists("plugins/protocols"))
     {
	GetDynamicProtocols("plugins/protocols", list);
     }
#ifndef WIN32
#ifdef PREFIX
   else if(FilesUtility::fileExists(PREFIX "/lib/myserver/plugins/protocols"))
     {
	GetDynamicProtocols(PREFIX "/lib/myserver/plugins/protocols", list);
     }
#else
   else if(FilesUtility::fileExists("/usr/lib/myserver/plugins/protocols"))
     {
	GetDynamicProtocols("/usr/lib/myserver/plugins/protocols", list);
     }
#endif
#endif
   Configure.setDynamic(list);
   list.clear();

   // Load, if found, fist avaible configuration
   Configure.ConfType = conf_location;
   switch(conf_location)
     {
      case 1 :
	Configure.ConfTypeDlgLocal->setonly();
	break;
      case 2 :
	Configure.ConfTypeDlgUser->setonly();
	break;
      case 3 :
	Configure.ConfTypeDlgGlobal->setonly();
	break;
      default :
	break;
     }
   Configure.load_config();

   // Start the app
   ret = Fl::run();

   // Close the language xml file
   LanguageXMLclose();

   // Cleanup
   LanguageXMLend();
   XmlParser::cleanXML();

   // Exit
   return ret;
}

///
/// Get the local dynamic protocols.
/// Parts taken from protocols_manager.cpp
///
static void GetDynamicProtocols(const char * folder, Vector & list)
{
   list.clear();

   HMODULE module;
   registerNamePROC name;

   FindData fd;
   int fd_ret;
   int filenamelen = 0;
   char *filename = 0;
#ifdef WIN32
   filenamelen=strlen(folder)+6;
   filename=new char[filenamelen];
   if(filename == 0)
     return;
   snprintf(filename,filenamelen,"%s/*.*",folder);
#endif
#ifdef NOT_WIN
   filenamelen=strlen(folder)+2;
   filename=new char[filenamelen];
   if(filename == 0)
     return;
   strncpy(filename,folder, filenamelen);
#endif

   fd_ret=fd.findfirst(filename);
   if(fd_ret==-1)
       {
	  delete [] filename;
	  filename = 0;
	  return;
       }
   char *completeFileName = 0;
   int completeFileNameLen = 0;
   do
     {
	if(fd.name[0]=='.')
	  continue;
	/*
	 *Do not consider file other than dynamic libraries.
	 */
#ifdef WIN32
	if(!strstr(fd.name,".dll"))
#endif
#ifdef NOT_WIN
	  if(!strstr(fd.name,".so"))
#endif
	    continue;
	completeFileNameLen = strlen(folder) + strlen(fd.name) + 2;
	completeFileName = new char[completeFileNameLen];
	if(completeFileName == 0)
	  {
	     delete [] filename;
	     filename = 0;
	     return;
	  }
	snprintf(completeFileName,completeFileNameLen,"%s/%s",folder,fd.name);
#ifdef WIN32
	module = LoadLibrary(completeFileName);
#endif
#ifdef HAVE_DL
	module = dlopen(completeFileName, RTLD_LAZY);
#endif
	if(module != NULL)
	  {
#ifdef WIN32
	     name = (registerNamePROC)GetProcAddress((HMODULE)module, "registerName");
#endif
#ifdef HAVE_DL
	     name = (registerNamePROC)dlsym(module, "registerName");
#endif
	     if(name != NULL)
	       {
		  list.add(name(NULL, 0));
	       }
	  }
#ifdef WIN32
	FreeLibrary((HMODULE)module);
#endif
#ifdef HAVE_DL
	dlclose(module);
#endif
	delete [] completeFileName;
     }
   while(!fd.findnext());
   fd.findclose();
   delete [] filename;
   filename = 0;
}
