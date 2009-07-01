# -*- coding: utf-8 -*-
'''
MyServer
Copyright (C) 2009 Free Software Foundation, Inc.
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
'''

import unittest
from log import Stream, Log
from lxml import etree

class StreamTest(unittest.TestCase):
    def test_creation(self):
        log = Stream('/logs/MyServer.log')
        log = Stream('/logs/MyServer.log', 1048576)
        log = Stream('/logs/MyServer.log', 1048576, False)
        log = Stream('/logs/MyServer.log', 1048576, False, ['gzip', 'bzip2'])

    def test_location(self):
        log = Stream('/logs/MyServer.log')
        self.assertEqual('/logs/MyServer.log', log.get_location())
        log.set_location('/logs/new.log')
        self.assertEqual('/logs/new.log', log.get_location())
        self.assertRaises(AttributeError, log.set_location, None)

    def test_cycle(self):
        log = Stream('path')
        self.assertEqual(None, log.get_cycle())
        log.set_cycle(123)
        self.assertEqual(123, log.get_cycle())
        log.set_cycle(None)
        self.assertEqual(None, log.get_cycle())
        log = Stream('path', 123)
        self.assertEqual(123, log.get_cycle())

    def test_cycle_gzip(self):
        log = Stream('path')
        self.assertEqual(None, log.get_cycle_gzip())
        log.set_cycle_gzip(True)
        self.assertEqual(True, log.get_cycle_gzip())
        log.set_cycle_gzip(None)
        self.assertEqual(None, log.get_cycle_gzip())
        log = Stream('path', 123, False)
        self.assertEqual(False, log.get_cycle_gzip())
        log = Stream('path', cycle_gzip = False)
        self.assertEqual(False, log.get_cycle_gzip())

    def test_filter(self):
        log = Stream('path')
        self.assertEqual([], log.get_filters())
        log.add_filter('gzip')
        self.assertEqual(['gzip'], log.get_filters())
        log.add_filter('bzip2')
        self.assertEqual(['gzip', 'bzip2'], log.get_filters())
        log.add_filter('bzip2', 0)
        self.assertEqual(['bzip2', 'gzip', 'bzip2'], log.get_filters())
        self.assertEqual('gzip', log.get_filter(1))
        log.remove_filter(1)
        self.assertEqual(['bzip2', 'bzip2'], log.get_filters())
        log = Stream('path', 123, False, ['gzip'])
        self.assertEqual(['gzip'], log.get_filters())
        log = Stream('path', filter = ['gzip'])
        self.assertEqual(['gzip'], log.get_filters())

    def test_from_string(self):
        text = '''<STREAM location="path" cycle="123" cycle_gzip="NO">
  <FILTER>gzip</FILTER>
  <FILTER>bzip2</FILTER>
</STREAM>'''
        log = Stream.from_string(text)
        self.assertEqual('path', log.get_location())
        self.assertEqual('123', log.get_cycle())
        self.assertFalse(log.get_cycle_gzip())
        self.assertEqual(['gzip', 'bzip2'], log.get_filters())
        text = '<STREAM location="path" />'
        log = Stream.from_string(text)
        self.assertEqual('path', log.get_location())
        self.assertEqual(None, log.get_cycle())
        self.assertEqual(None, log.get_cycle_gzip())
        self.assertEqual([], log.get_filters())

    def test_from_lxml(self):
        text = '''<STREAM location="path" cycle="123" cycle_gzip="NO">
  <FILTER>gzip</FILTER>
  <FILTER>bzip2</FILTER>
</STREAM>'''
        log = Stream.from_lxml_element(etree.XML(text))
        self.assertEqual('path', log.get_location())
        self.assertEqual('123', log.get_cycle())
        self.assertFalse(log.get_cycle_gzip())
        self.assertEqual(['gzip', 'bzip2'], log.get_filters())
        text = '<STREAM location="path" />'
        log = Stream.from_lxml_element(etree.XML(text))
        self.assertEqual('path', log.get_location())
        self.assertEqual(None, log.get_cycle())
        self.assertEqual(None, log.get_cycle_gzip())
        self.assertEqual([], log.get_filters())

    def test_bad_root_tag(self):
        text = '<ERROR location="path" />'
        self.assertRaises(AttributeError, Stream.from_string, text)
        self.assertRaises(AttributeError, Stream.from_lxml_element,
                          etree.XML(text))
    
    def test_equality(self):
        self.assertEqual(Stream('path', 123, False, ['gzip', 'bzip2']),
                         Stream('path', 123, False, ['gzip', 'bzip2']))
        self.assertNotEqual(Stream('path1', 123, False, ['gzip', 'bzip2']),
                            Stream('path2', 123, False, ['gzip', 'bzip2']))
        self.assertNotEqual(Stream('path', 1234, False, ['gzip', 'bzip2']),
                            Stream('path', 123, False, ['gzip', 'bzip2']))
        self.assertNotEqual(Stream('path', 123, True, ['gzip', 'bzip2']),
                            Stream('path', 123, False, ['gzip', 'bzip2']))
        self.assertNotEqual(Stream('path', 123, True, ['bzip2']),
                            Stream('path', 123, False, ['gzip', 'bzip2']))
        self.assertNotEqual([], Stream('path'))

    def test_to_string(self):
        text = '''<STREAM location="path" cycle="123" cycle_gzip="NO">
  <FILTER>gzip</FILTER>
  <FILTER>bzip2</FILTER>
</STREAM>'''
        log = Stream.from_string(text)
        copy = Stream.from_string(str(log))
        self.assertEqual(log, copy)

    def test_to_lxml(self):
        text = '''<STREAM location="path" cycle="123" cycle_gzip="NO">
  <FILTER>gzip</FILTER>
  <FILTER>bzip2</FILTER>
</STREAM>'''
        log = Stream.from_string(text)
        copy = Stream.from_lxml_element(log.to_lxml_element())
        self.assertEqual(log, copy)

class LogTest(unittest.TestCase):
    def setUp(self):
        text_0 = '<STREAM location="file://logs/MyServerHTTP.log" />'
        self.stream_0 = Stream.from_string(text_0)
        text_1 = '<STREAM location="console://stdout" />'
        self.stream_1 = Stream.from_string(text_1)

    def test_creation(self):
        log = Log('ACCESSLOG')
        log = Log('WARNINGLOG')
        log = Log('ACCESSLOG', [self.stream])
        log = Log('ACCESSLOG', [self.stream], 'combined')

    def test_log_type(self):
        log = Log('ACCESSLOG')
        self.assertEqual('ACCESSLOG', log.get_log_type())
        log.set_log_type('WARNINGLOG')
        self.assertEqual('WARNINGLOG', log.get_log_type())
        self.assertRaises(AttributeError, log.set_log_type, None)

    def test_type(self):
        log = Log('ACCESSLOG')
        self.assertEqual(None, log.get_type())
        log.set_type('combined')
        self.assertEqual('combined', log.get_type())
        log.set_type(None)
        self.assertEqual(None, log.get_type())
        log = Log('ACCESSLOG', [], 'combined')
        self.assertEqual('combined', log.get_type())

    def test_stream(self):
        log = Log('ACCESSLOG')
        self.assertEqual([], log.get_streams())
        log.add_stream(self.stream_0)
        self.assertEqual([self.stream_0], log.get_streams())
        log.add_stream(self.stream_1)
        self.assertEqual([self.stream_0, self.stream_1], log.get_streams())
        log.add_stream(self.stream_1, 0)
        self.assertEqual([self.stream_1, self.stream_0, self.stream_1],
                         log.get_streams())
        self.assertEqual(self.stream_0, log.get_stream(1))
        log.remove_stream(1)
        self.assertEqual([self.stream_1, self.stream_1], log.get_streams())
        log = Log('ACCESSLOG', [self.stream_0])
        self.assertEqual([self.stream_0], log.get_streams())

    def test_from_string(self):
        text = '''<ACCESSLOG type="combined">{0}{1}</ACCESSLOG>'''.format( \
            self.stream_0, self.stream_1)
        log = Log.from_string(text)
        self.assertEqual('ACCESSLOG', log.get_log_type())
        self.assertEqual('combined', log.get_type())
        self.assertEqual([self.stream_0, self.stream_1], log.get_streams())

    def test_from_lxml(self):
        text = '''<ACCESSLOG type="combined">{0}{1}</ACCESSLOG>'''.format( \
            self.stream_0, self.stream_1)
        log = Log.from_lxml_element(etree.XML(text))
        self.assertEqual('ACCESSLOG', log.get_log_type())
        self.assertEqual('combined', log.get_type())
        self.assertEqual([self.stream_0, self.stream_1], log.get_streams())

    def test_to_string(self):
        text = '''<ACCESSLOG type="combined">{0}{1}</ACCESSLOG>'''.format( \
            self.stream_0, self.stream_1)
        log = Log.from_string(text)
        copy = Stream.from_string(str(log))
        self.assertEqual(log, copy)

    def test_to_lxml(self):
        text = '''<ACCESSLOG type="combined">{0}{1}</ACCESSLOG>'''.format( \
            self.stream_0, self.stream_1)
        log = Log.from_string(text)
        copy = Stream.from_lxml_element(log.to_lxml_element())
        self.assertEqual(log, copy)

    def test_equality(self):
        self.assertEqual(Log('ACCESSLOG', [self.stream_0, self.stream_1], 'combined'),
                         Log('ACCESSLOG', [self.stream_0, self.stream_1], 'combined'))
        self.assertNotEqual(Log('ACCESSLOG', [self.stream_0], 'combined'),
                            Log('WARNINGLOG', [self.stream_0], 'combined'))
        self.assertNotEqual(Log('ACCESSLOG', [self.stream_0], 'combined'),
                            Log('ACCESSLOG', [self.stream_1], 'combined'))
        self.assertNotEqual(Log('ACCESSLOG', [self.stream_0], 'combined'),
                            Log('WARNINGLOG', [self.stream_0], None))
        self.assertNotEqual([], Log('ACCESSLOG'))

if __name__ == '__main__':
    unittest.main()
