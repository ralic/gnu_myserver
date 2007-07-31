/*
MyServer
Copyright (C) 2007 The MyServer Team
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

#include "python.h"

PyInterpreterState* pythonMainInterpreterState = NULL;
HashMap<ThreadID, PythonData*> pythonThreadData;

static Server *serverInstance;

char* name(char* name, u_long len)
{
	char* str = (char*)"python";

	if(name)
		strncpy(name, str, len);

	return str;
}


PyInterpreterState* PythonData::getInterpreter()
	{
		if(interp == 0)
			interp = Py_NewInterpreter();
		PyThreadState_Swap(NULL);
		return interp->interp;
	}

PythonData::PythonData()
{
	clear();
}

void PythonData::clear()
{
	interp = 0;
}



int load(void* server, void* parser)
{
	serverInstance = (Server*)server;
	const char* pathData = serverInstance->getHashedData("PYTHON_PATH");
	PyThreadState * mainThreadState;
	if(pathData)
	{	
		string path(pathData);
		FilesUtility::completePath(path);
		
		setenv("PYTHONPATH", path.c_str(), 1);
	}
	else
	{
		string path(".");
		FilesUtility::completePath(path);

		setenv("PYTHONPATH", path.c_str(), 1);
	}

	Py_Initialize();
	PyEval_InitThreads();

	mainThreadState = PyThreadState_Get();

	pythonMainInterpreterState = mainThreadState->interp;

	PyEval_ReleaseLock();

	return 0;
}

/*! Unload the plugin.  Called once.  Returns 0 on success.  */
int unLoad(void* p)
{
	PyInterpreterState *interpreter = NULL;
	PyThreadState *threadState = NULL;
	PythonData* data = NULL;
	ThreadID tid = Thread::threadID();

	PyEval_AcquireLock();


	data = pythonThreadData.get(tid);
	if(data == 0)
	{
		data = new PythonData();
		pythonThreadData.put(tid, data);
	}

	interpreter = data->getInterpreter();
	threadState = PyThreadState_New(interpreter);

	PyThreadState_Swap(threadState);


	Py_Finalize();

	
	PyThreadState_Swap(NULL);


	PyEval_ReleaseLock();

	HashMap<ThreadID, PythonData*>::Iterator it = pythonThreadData.begin();
	while(it != pythonThreadData.end())
		delete *it++;
	return 0;
}


int execute(char* code, u_long length)
{
	PyInterpreterState *interpreter = NULL;
	PyThreadState *threadState = NULL;
	PythonData* data = NULL;
	ThreadID tid = Thread::threadID();

	PyEval_AcquireLock();

	data = pythonThreadData.get(tid);
	if(data == 0)
	{
		data = new PythonData();
		pythonThreadData.put(tid, data);
	}

	interpreter = data->getInterpreter();
	threadState = PyThreadState_New(interpreter);

	PyThreadState_Swap(threadState);


	PyRun_SimpleString(code);
	
	PyThreadState_Swap(NULL);

	PyThreadState_Clear(threadState);
	PyThreadState_Delete(threadState);

	PyEval_ReleaseLock();

  return 0;


}

int executeFromFile(char* filename)
{
	PyInterpreterState *interpreter = NULL;
	PyThreadState *threadState = NULL;
	int ret = 0;
	FILE *file = NULL;
	PythonData* data = NULL;
	ThreadID tid = Thread::threadID();

	PyEval_AcquireLock();

	data = pythonThreadData.get(tid);
	if(data == 0)
	{
		data = new PythonData();
		pythonThreadData.put(tid, data);
	}

	interpreter = data->getInterpreter();
	threadState = PyThreadState_New(interpreter);

	PyThreadState_Swap(threadState);

	file = fopen(filename, "r");

	if(file == 0)
	{
		string msg;
		msg.assign("Python: Cannot load file ");
		msg.append(filename);

		serverInstance->logLockAccess();
		serverInstance->logPreparePrintError();
		serverInstance->logWriteln(msg.c_str());
		serverInstance->logEndPrintError();
		serverInstance->logUnlockAccess();

		ret = -1;
	}
	else
		ret = PyRun_AnyFileEx(file, filename, 1);

	
	PyThreadState_Swap(NULL);

	PyThreadState_Clear(threadState);
	PyThreadState_Delete(threadState);

	PyEval_ReleaseLock();

  return ret;

}

int initModule(char* name, PyMethodDef methods[])
{
	PyInterpreterState *interpreter = NULL;
	PyThreadState *threadState = NULL;
	PythonData* data = NULL;
	ThreadID tid = Thread::threadID();

	PyEval_AcquireLock();

	data = pythonThreadData.get(tid);
	if(data == 0)
	{
		data = new PythonData();
		pythonThreadData.put(tid, data);
	}

	interpreter = data->getInterpreter();
	threadState = PyThreadState_New(interpreter);

	PyThreadState_Swap(threadState);


	Py_InitModule(name, methods);

	PyThreadState_Swap(NULL);


	PyEval_ReleaseLock();

	return 0;
}