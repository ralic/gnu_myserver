/*
  MyServer
  Copyright (C) 2002, 2003, 2004 Free Software Foundation, Inc.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
 
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
 
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  */
#ifndef PROGRESS_H
#define PROGRESS_H

#include <FL/Fl.H>
#include <FL/Fl_Progress.H>
#include <stdio.h>

/* Status callback function */

void ProgressCallback(void * Object, unsigned int len, unsigned int pos);
#endif
