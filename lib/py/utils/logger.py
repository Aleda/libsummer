#!/usr/bin/env python
# -*- coding: utf-8 -*-

################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
This module for the self.logger with baidu logging type.
    include:
        * BaiduLogger("./test/test").info
        * BaiduLogger("./test/test").waring
        * Baidulogger("./test/test").error
The logging type:
INFO: 09-14 15:13:06: logger.py:87 * 182896918592 Hello world.

Authors: Aleda(lishuo02@baidu.com)
Date:    2015/09/14 15:19:06
Version: 1.0
"""
import logging
import logging.handlers
import os

__all__ = ["BaiduLogger", "baiduLogger"]

class BaiduLogger(object):
    """ The Summary of the BaiduLogger.
    BaiduLogger packages the output type of log in Baidu.
    see http://styleguide.baidu.com/style/python/index.html#编程实践id9
    """
    def __init__(self, log_path, log_name, level=logging.INFO, when="D", backup=7,
            format="%(levelname)s: %(asctime)s: %(filename)s:%(lineno)d * %(thread)d %(message)s",
            datefmt="%m-%d %H:%M:%S"):
        """
        init_log - initialize log module

        Args:
        log_path      - Log file path prefix.
                        Log data will go to two files: log_path.log and log_path.log.wf
                        Any non-exist parent directories will be created automatically
        level         - msg above the level will be displayed
                        DEBUG < INFO < WARNING < ERROR < CRITICAL
                        the default value is logging.INFO
        when          - how to split the log file by time interval
                        'S' : Seconds
                        'M' : Minutes
                        'H' : Hours
                        'D' : Days
                        'W' : Week day
                        default value: 'D'
        format        - format of the log
                        default format:
                        %(levelname)s: %(asctime)s: %(filename)s:%(lineno)d * %(thread)d %(message)s
                        INFO: 12-09 18:02:42: log.py:40 * 139814749787872 HELLO WORLD
        backup        - how many backup file to keep
                        default value: 7

        Raises:
            OSError: fail to create log directories
            IOError: fail to open log file
        Test:
        """
        formatter = logging.Formatter(format, datefmt)
        ##! logger是有继承关系的实例
        self.logger = logging.getLogger(log_path)
        self.logger.setLevel(level)
        self_dir = os.path.dirname(log_path)
        if self_dir and not os.path.isdir(self_dir):
            os.makedirs(self_dir)
        handler = logging.handlers.TimedRotatingFileHandler(log_path + ".log",
                                                            when=when,
                                                            backupCount=backup)
        handler.setLevel(level)
        handler.setFormatter(formatter)
        self.logger.addHandler(handler)

        handler = logging.handlers.TimedRotatingFileHandler(log_path + ".log.wf",
                                                            when=when,
                                                            backupCount=backup)
        handler.setLevel(logging.WARNING)
        handler.setFormatter(formatter)
        self.logger.addHandler(handler)

    def info(self, msg):
        """
        Args:
            msg                     - The msg which need to write into log.
        Test:
            >>> new_logger = BaiduLogger('./test/new_logger')
            >>> new_logger.info('Hello world.')
        """
        return self.logger.info(msg)

    def warning(self, msg):
        """
        Args:
            msg                     - The msg which need to write into log.
        Test:
            >>> new_logger = BaiduLogger('./test/new_logger')
            >>> new_logger.warning('Hello world.')
        """
        return self.logger.warning(msg)

    def debug(self, msg):
        """
        Args:
            msg                     - The msg which need to write into log.
        Test:
            >>> new_logger = BaiduLogger('./test/new_logger')
            >>> new_logger.debug('Hello world.')
        """
        return self.logger.debug(msg)
    
    def error(self, msg):
        """
        Args:
            msg                     - The msg which need to write into log.
        Test:
            >>> new_logger = BaiduLogger('./test/new_logger')
            >>> new_logger.error('Hello world.')
        """
        return self.logger.error(msg)

    def critical(self, msg):
        """
        Args:
            msg                     - The msg which need to write into log.
        Test:
            >>> new_logger = BaiduLogger('./test/new_logger')
            >>> new_logger.critical('Hello world.')
        """
        return self.logger.critical(msg)

baiduLogger = BaiduLogger

def main():
    """
    Main
    Test:
        python -m doctest -v logger.py
    """
    import doctest
    doctest.testmod()

if __name__ == '__main__':
    main()
