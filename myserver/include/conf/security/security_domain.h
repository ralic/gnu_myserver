/* -*- mode: c++ -*- */
/*
MyServer
Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef SECURITY_DOMAIN_H
# define SECURITY_DOMAIN_H

# include "stdafx.h"

# include <string>

using namespace std;

class SecurityDomain
{
public:
  SecurityDomain ();
  SecurityDomain (const char* name);
  SecurityDomain (string &name);
  virtual ~SecurityDomain ();
  virtual string *getValue (string &name);
  string& getName(){return name;}
protected:
  string name;
};

#endif
