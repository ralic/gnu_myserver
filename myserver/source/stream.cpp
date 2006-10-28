/*
MyServer
Copyright (C) 2002, 2003, 2004 The MyServer Team
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

 
#include "../include/isapi.h"
#include "../include/stream.h"

#include <string>
#include <sstream>
using namespace std;

/*!
 *Read [len] characters from the stream. Returns -1 on errors.
 */
int Stream::read(char* buffer,u_long len, u_long *nbr)
{
  *nbr=0;
  return 0;
}

/*!
 *Write [len] characters to the stream. Returns -1 on errors.
 */
int Stream::write(const char* buffer, u_long len, u_long *nbw)
{
  *nbw=0;
  return 0;
}

/*! 
 *Write remaining data to the stream. 
 */
int Stream::flush(u_long* nbw)
{
  *nbw=0;
  return 0;
}

Stream::Stream()
{

}

Stream::~Stream()
{

}