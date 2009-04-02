/*
MyServer
Copyright (C) 2002, 2003, 2004, 2007, 2008, 2009 Free Software Foundation, Inc.
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

#include <include/protocol/protocol.h>
#include <include/protocol/https/https.h>

extern "C" 
{
#ifdef WIN32
#include <direct.h>
#include <errno.h>
#endif
#ifndef WIN32
#include <string.h>
#include <errno.h>
#endif
}


/*!
 *Returns the name of the protocol. If an out buffer is defined 
 *fullfill it with the name too.
 */
char* Https::registerNameImpl(char* out, int len)
{
  if(out)
  {
    strncpy(out, "HTTPS", len);
  }
  return (char*)"HTTPS";
}

char* Https::registerName(char* out, int len)
{
  return registerNameImpl(out, len);
}

/*!
 *Https class constructor.
 */
Https::Https() 
{
  protocolPrefix.assign("https://");
  protocolOptions = PROTOCOL_USES_SSL;
}

/*!
 *Destructor for the class Https.
 */
Https::~Https()
{

}
