/*
  MyServer
  Copyright (C) 2009, 2010, 2012 The Free Software Foundation Inc.
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

#include <string.h>
#include <libguile.h>
#include <guile/gh.h>
#include <include/plugin/plugin.h>
#include <include/conf/main/main_configuration.h>
#include <include/conf/vhost/xml_vhost_handler.h>
#include <include/server/server.h>

#define CONF_FILE_NAME "myserver.sch"

/*! Define the interface to read from the main configuration file.  */
class GuileConfiguration : public MainConfiguration
{
public:
  GuileConfiguration ();
  virtual const char *getValue (const char* field);
  virtual void readData (list<NodeTree<string>*> *hashedDataTrees,
                         HashMap<string, NodeTree<string>*> *hashedData);

 private:
    Server *serverInstance;
};

class GuileVhostManagerHandler : public XmlVhostHandler
{
public:
  GuileVhostManagerHandler (ListenThreads* lt, LogManager* lm) :
    XmlVhostHandler (lt, lm)
  {
  }

    virtual int load (const char *resource);

 private:
    Server *serverInstance;
};
