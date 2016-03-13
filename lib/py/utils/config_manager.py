#!/usr/bin/env python
# -*- coding: utf-8 -*-

################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
This module of read and manager the configure file.
    include:
        *
        *
        *

Authors: Aleda(lishuo02@baidu.com)
Date:    2015/09/14 16:11:06
Version: 1.0
"""

__all__ = ["ConfigureManager", "config_manager",
        "confManager", "conf_manager"]

class Singleton(object):
    """ The summary of Singleton.
    """
    def __new__(cls, *args, **kw):
        if not hasattr(cls, '_instance'):
            cls._instance = super().__new__(cls, args, kw)
        return cls._instance

class ConfigureManager(object):
    """ The summary of ConfigureManager.
    """
    def __init__(self):
        self._sections = {}
        pass

    def read_config_file(self, conf_file):
        """ Read config from the config file and init it.
        Args:
        Returns:
            read_status                 - The read config status.
                                          -1: conf_file empty or not exists.
                                          -2: ConfigParser parsing error.
                                          -3: Read error.
        Test:
            >>> config_manager = ConfigureManager()
            >>> config_manager.read_config_file('../conf/configure.ini')
            1
        """
        import os
        if not conf_file or not os.path.exists(conf_file):
            return -1
        import ConfigParser
        config = ConfigParser.ConfigParser()
        success_list = []
        try:
            success_list = config.read(conf_file)
        except ConfigParser.Error as error:
            print "Reading error in: %s" % conf_file
            print "Error is: %s" % str(error)
            return -2
        if conf_file not in success_list:
            print "ReadingError while reading the config: %s" % conf_file
            return -3
        for sec in config.sections():
            if sec:
                _dict = {}
                for item_tuple in config.items(sec):
                    _dict[item_tuple[0]] = item_tuple[1]
                self._sections[sec] = _dict
        return 1

    def get(self, section, option):
        """ Get the item.
        Args:
            section                     - The section in basestring type.
            option                      - The option  in basestring type.
        Rerturn:
            item                        - Return the value with basestring.
        Test:
            >>> config_manager = ConfigureManager()
            >>> config_manager.read_config_file('../conf/configure.ini')
            1
            >>> config_manager.get('Crawl', 'small_task')
            '5000'
            >>> config_manager.get('Crawl', 'small_task1')
            >>> config_manager.get('Crawl1', 'small_task1')
        """
        if not self.section(section):
            return None
        return self.section(section).get(option)

    def section(self, section):
        """ Get the section with dict.
        Args:
            section                     - The section in basestring type.
        Returns:
            section                     - The dict for the section.
        Test:
            >>> config_manager = ConfigureManager()
            >>> config_manager.read_config_file('../conf/configure.ini')
            1
            >>> config_manager.section('Main')
            {'whether_compress_file_flag': '0', 'default_running_queue_size': '20', 'waiting_queue_size': '20', 'running_queue_cache_size': '200', 'default_running_url_num': '100000', 'port_range_end': '10000', 'running_queue_size': '100', 'default_extract_threads': '10', 'crawl_success_rate_req': '0.95', 'serialize_db': '.serialize.db', 'default_running_task_num': '20', 'taskinfo_db': 'taskinfo.db', 'default_top_num': '10', 'default_level_task_num': '10', 'max_inmem_task_num': '100', 'max_lineup_time': '300'}
        """
        return self._sections.get(section)

    def sections(self):
        """
        Returns:
            keys                        - The list of the _sections.keys
        Test:
            >>> config_manager = ConfigureManager()
            >>> config_manager.read_config_file('../conf/configure.ini')
            1
            >>> config_manager.sections()
            ['Crawl', 'Global', 'Main']
        """
        return self._sections.keys()

    def __getitem__(self, section):
        """ get a dict for the section.
        Args:
            section                     - The section name.
        Return:
            section                     - The dict for the section.
        Test:
            >>> config_manager = ConfigureManager()
            >>> config_manager.read_config_file('../conf/configure.ini')
            1
            >>> config_manager['Main']
            {'whether_compress_file_flag': '0', 'default_running_queue_size': '20', 'waiting_queue_size': '20', 'running_queue_cache_size': '200', 'default_running_url_num': '100000', 'port_range_end': '10000', 'running_queue_size': '100', 'default_extract_threads': '10', 'crawl_success_rate_req': '0.95', 'serialize_db': '.serialize.db', 'default_running_task_num': '20', 'taskinfo_db': 'taskinfo.db', 'default_top_num': '10', 'default_level_task_num': '10', 'max_inmem_task_num': '100', 'max_lineup_time': '300'}
            >>> config_manager['Main1']
        """
        return self._sections.get(section)

conf_manager = ConfigureManager()
config_manager = conf_manager
confManager = conf_manager


def main():
    """ Main
    Test:
        >>> config_manager = ConfigureManager()
        >>> config_manager.read_config_file('../conf/configure.ini')
        1
        >>> config_manager['Main']['whether_compress_file_flag']
        '0'
        >>> config_manager['Main']['whether_compress_file_flag1']
        Traceback (most recent call last):
        ...
        KeyError: 'whether_compress_file_flag1'
        >>> config_manager['Main'].get('whether_compress_file_flag1')
        
        >>> import conf_manager
        >>> conf1 = conf_manager.config_manager
        >>> conf2 = conf_manager.config_manager
        >>> id(conf1) == id(conf2)
        True
    """
    import doctest
    doctest.testmod()

if __name__ == '__main__':
    main()



