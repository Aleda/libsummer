#!/usr/bin/env python
# -*- coding: utf-8 -*-

################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
This module for the constant.

Authors: Aleda(lishuo02@baidu.com)
Date:    2015/10/08 16:48:06
Version: 1.0.0
"""

class Const(object):
    class ConstError(TypeError): pass
    class ConstCaseError(ConstError): pass

    def __setattr__(self, name, value):
        if self.__dict__.has_key(name):
            raise self.ConstError, "Can't change const. %(name)s" % {'name': name}
        if not name.isupper():
            raise self.ConstCaseError, "const name: %(name)s not all uppercase." % {'name': name}
        self.__dict__[name] = value


const = Const = Constant = constant = Const()

def main():
    """ Main
    Test:
        >>> constant.NAME = 'Aleda'
        >>> print constant.NAME
        Aleda
        >>> constant.NAME = 'Monique'
        Traceback (most recent call last):
        ...
        ConstError: Can't change const. NAME
    """
    import doctest
    doctest.testmod()
    # python -m doctest -v constant.py

if __name__ == '__main__':
    main()
