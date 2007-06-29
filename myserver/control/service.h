/*
 MyServer
 Copyright (C) 2002, 2003, 2004 The MyServer Team
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
#ifndef SERVICE_H
#define SERVICE_H

void RunAsConsole();
void RunAsService();
void StopConsole();
void StopService();
void InstallService();
void RemoveService();

#endif
