# GNU MyServer
#
# Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010,
# 2011 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
SUBDIRS = logs system web certificates plugins

examplesdir = $(docdir)/examples

dist_examples_DATA = myserver-daemon MIMEtypes.default.xml myserver.default.xml \
			virtualhosts.default.xml

confdir = $(sysconfdir)/myserver

conf_DATA = MIMEtypes.default.xml myserver.default.xml \
			virtualhosts.default.xml

install-data-hook:
	mv $(DESTDIR)$(sysconfdir)/myserver/MIMEtypes.default.xml $(DESTDIR)$(sysconfdir)/myserver/MIMEtypes.xml
	mv $(DESTDIR)$(sysconfdir)/myserver/myserver.default.xml $(DESTDIR)$(sysconfdir)/myserver/myserver.xml
	mv $(DESTDIR)$(sysconfdir)/myserver/virtualhosts.default.xml $(DESTDIR)$(sysconfdir)/myserver/virtualhosts.xml
