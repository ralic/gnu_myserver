/*
  MyServer
  Copyright (C) 2006, 2008, 2009, 2010, 2011 Free Software Foundation,
  Inc.
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

#include "myserver.h"
#include <include/log/stream/console_stream_creator.h>

LogStream*
ConsoleStreamCreator::create (FiltersFactory* ff, string location,
                              list<string>& filters, u_long cycle)
{
  Console* out = new Console ();
  if (out && !out->openConsole (location))
    {
      size_t nbw;
      FiltersChain* fc = ff->makeChain (filters, out, &nbw);
      if (fc)
        {
          return new ConsoleStream (ff, cycle, out, fc);
        }
    }
  if (out)
    {
      delete out;
    }
  return 0;
}
