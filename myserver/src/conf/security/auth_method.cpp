/*
  MyServer
  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010
  Free Software Foundation, Inc.
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
#include <include/conf/security/auth_method.h>


AuthMethod::AuthMethod ()
{
  cryptAlgoManager = NULL;
}

AuthMethod::~AuthMethod ()
{

}

/*!
 *Get the permission mask for the specified user/password.
 */
int AuthMethod::getPermissionMask (SecurityToken* st)
{
  return 0;
}


/*!
 * Check if ALGORITHM (SAVED_PASSWORD) = PASSWORD.
 */
bool AuthMethod::comparePassword (const char *password,
                                  const char *savedPassword,
                                  const char *algorithm)
{
  if (!algorithm)
    return  strcasecmp (password, savedPassword) == 0;

  if (cryptAlgoManager)
    {
      try
        {
          return cryptAlgoManager->check (savedPassword, strlen (savedPassword),
                                          password, algorithm);
        }
      catch (...)
        {
          return false;
        }
    }

  return false;
}
