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
AM_CXXFLAGS=-I"$(top_builddir)/lib" -I"$(top_srcdir)/lib" -I"$(top_srcdir)"
noinst_PROGRAMS = test_suite
test_suite_SOURCES =  	main.cpp				\
			memory_socket.h			        \
			test_auth_domain.cpp			\
			test_auth_method.cpp			\
			test_base64.cpp				\
			test_bitvec.cpp				\
			test_cached_file.cpp			\
			test_cached_file_buffer.cpp		\
			test_cached_file_factory.cpp		\
			test_connection.cpp			\
			test_connections_scheduler.cpp		\
			test_crypt_algo_manager.cpp		\
			test_exceptions.cpp	\
			test_file.cpp				\
			test_file_stream.cpp			\
			test_file_stream_creator.cpp		\
			test_files_utility.cpp			\
			test_filter_chain.cpp			\
			test_fork_server.cpp			\
			test_ftp.cpp				\
			test_gopher_content.cpp			\
			test_gzip.cpp				\
			test_hashmap.cpp			\
			test_homedir.cpp			\
			test_http_req_security_domain.cpp	\
			test_http_request.cpp			\
			test_http_response.cpp			\
			test_ip.cpp				\
			test_log_manager.cpp			\
			test_log_stream_factory.cpp		\
			test_md5.cpp				\
			test_mem_buff.cpp			\
			test_mem_stream.cpp			\
			test_membuf_file.cpp			\
			test_mem_socket.cpp			\
			test_mime_manager.cpp			\
			test_multicast.cpp			\
			test_mutex.cpp				\
			test_nodetree.cpp			\
			test_pipe.cpp				\
			test_plugin_info.cpp			\
			test_plugins_manager.cpp		\
			test_read_directory.cpp			\
			test_rec_read_directory.cpp		\
			test_recursive_mutex.cpp		\
			test_regex.cpp				\
			test_safetime.cpp			\
			test_security_cache.cpp			\
			test_security_domain.cpp		\
			test_security_manager.cpp		\
			test_security_token.cpp			\
			test_semaphore.cpp			\
			test_sha1.cpp				\
			test_slab.cpp				\
			test_socket.cpp				\
			test_socket_pair.cpp			\
			test_socket_stream_creator.cpp		\
			test_ssl_socket.cpp			\
			test_stringutils.cpp \
			test_thread.cpp				\
			test_unix_socket.cpp			\
			test_url.cpp				\
			test_utility.cpp			\
			test_validator.cpp			\
			test_validator_factory.cpp		\
			test_xml.cpp				\
			test_xml_main_configuration.cpp		\
			test_xml_validator.cpp

test_suite_LDADD = ../src/libmyserver.la  ../lib/libgnu.la $(CPPUNIT_LDFLAGS) \
	$(PTHREAD_LIB) 	$(IDN_LIB) $(XNET_LIB) $(DL_LIB) $(ZLIB_LIB) \
	$(XML_LIBS) $(INTLLIBS) $(LDFLAGS)

test_suite_LDFLAGS = -static

install:

check-am:
	./test_suite$(EXEEXT)
