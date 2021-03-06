/*
*MyServer
*Copyright (C) 2002,2003,2004 The MyServer Team
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
#pragma comment(lib,"../../../cgi-lib/CGI-LIB.lib")
#endif
#include "../../../cgi-lib/cgi_manager.h"
#include "../../../../include/thread.h"
#include "../../../../include/mutex.h"
#include "../../../../include/files_utility.h"
#include "counter_output.h"
#include <limits.h>

static Mutex lock;

#ifdef WIN32
extern "C" int EXPORTABLE myserver_main (char *cmd, MsCgiData* data)
#else
extern "C" int myserver_main (char *cmd, MsCgiData* data)
#endif
{
	lock.lock();

	CgiManager cm(data);

	Counter_Output counter;

	cm.setContentType("image/png");

	counter.setWrite(&cm); //set the png writer function

	// Lets count!
	unsigned long int count;
	u_long nbw;

	File msfile;

	if(FilesUtility::fileExists("count.dat"))
	{
		// read the last number
		if(msfile.openFile("count.dat", File::MYSERVER_OPEN_READ|File::MYSERVER_OPEN_IFEXISTS) == 0)
		{
			msfile.readFromFile((char *)&count, sizeof(count), &nbw);
			msfile.closeFile();
    }
    else
      count = 0;

		count++; // add the hit

		if(count > ULONG_MAX - 5)
			count = 1;

		//now save it
		if(msfile.openFile("count.dat", File::MYSERVER_OPEN_WRITE|File::MYSERVER_OPEN_ALWAYS)==0)
    {
		  msfile.writeToFile((char *)&count, sizeof(count), &nbw);
		  msfile.closeFile();
    }
	}
	else
	{
		// never been counted so start
		count = 1;

		//now save it
		msfile.openFile("count.dat", File::MYSERVER_OPEN_WRITE|File::MYSERVER_CREATE_ALWAYS);
		msfile.writeToFile((char *)&count, sizeof(count), &nbw);
		msfile.closeFile();
	}

	counter.setNumber(count);

	counter.run();

	cm.clean();

	lock.unlock();

	return 0;
}

#ifdef WIN32
BOOL APIENTRY DllMain( HANDLE,DWORD ul_reason_for_call,LPVOID)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
#endif

