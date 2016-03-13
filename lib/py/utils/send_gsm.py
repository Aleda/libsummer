#!/usr/bin/python
# -*- coding: utf-8 -*
# #############################################################################
#
#  Copyright (c) 2015 Baidu.com,  Inc. All Rights Reserved
#
# #############################################################################
"""
This module provide sending gsm.
Any details see doctest.
Depend on /bin/gsmsend.
function includes:

        * send gsm from baidu gsm server.
        *
        *

Authors: maguannan@baidu.com, Modified by Aleda(lishuo02@baidu.com)
Date:    2015/09/14 16:11:06
Version: 1.0
"""

import os
import sys
import signal
import subprocess
import threading
import warnings

__all__ = ['GsmSender', 'ShellExec']

class ShellExec(object):  # pylint: disable=R0903
    """
    用来执行shell的类。 用法如下:
    shellexec = cup.shell.ShellExec()
    # timeout=None, 一直等待直到命令执行完
    shellexec.run('/bin/ls', timeout=None)
    # timeout>=0, 等待固定时间，如超时未结束terminate这个shell命令。
    shellexec.run(cmd='/bin/ls', timeout=100)
    """

    def __init__(self):
        self._subpro = None
        self._subpro_data = None

    def run(self, cmd, timeout):
        """
        参见类说明。
        :param cmd:
            执行命令
        :param timeout:
            执行等待时间， None为无线等待。 timeout>=0等待具体时间，超时
            terminate.
        :return:
            一个dict, 包含'stdout' 'stderr' 'returncode' 三个key:
            returncode == 0 代表执行成功, returncode 999代表执行超时
            {
                'stdout' : 'Success',
                'stderr' : None,
                'returncode' : 0
            }
        E.g.
        执行ls， 超时时间为1s, 超过1s会kill掉该shell进程， 然后回返returncode
        999
        ::
            import cup
            shelltool = cup.shell.ShellExec()
            print shelltool.run('/bin/ls', timeout=1)
        """
        def _signal_handle():
            """
            signal setup
            """
            signal.signal(signal.SIGPIPE, signal.SIG_DFL)

        def _target(cmd):
            self._subpro = subprocess.Popen(
                cmd, shell=True, stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                preexec_fn=_signal_handle
            )
            self._subpro_data = self._subpro.communicate()
        ret = {
            'stdout': None,
            'stderr': None,
            'returncode': 0
        }
        cmdthd = threading.Thread(target=_target, args=(cmd, ))
        cmdthd.start()
        cmdthd.join(timeout)
        if cmdthd.isAlive() is True:
            str_warn = (
                'Shell "%s"execution timout:%d. To kill it' % (cmd, timeout)
            )
            warnings.warn(str_warn, RuntimeWarning)
            self._subpro.terminate()
            ret['returncode'] = 999
            ret['stderr'] = str_warn
        else:
            ret['returncode'] = self._subpro.returncode
            assert type(self._subpro_data) == tuple, \
                'self._subpro_data should be a tuple'
            ret['stdout'] = self._subpro_data[0]
            ret['stderr'] = self._subpro_data[1]
        return ret

# pylint: disable=R0903
class GsmSender(object):
    """
    :param path_smstool:
        path_smstool默认指向/bin/gsmsend, 请检查它是否存在.
        内部统一发生短信的Singleton类, 请确保/bin/gsmsend 是存在的.
    *示例*
    ::
        persons = []
        persons.append(
            ('某乙', '138888888'),
        )
        persons.append(
            ('某甲', '139999999'),
        )
        smstool = GsmSender()
        smstool.post_sms(persons, '测试你能收到吗?')
    """
    def __init__(self, path_smstool='/bin/gsmsend'):
        self.__smstool = path_smstool
        if os.path.exists(path_smstool) is False:
            raise IOError('smtool not found: %s' % path_smstool)

    def _del_extra_space(self, msg, sign_len):
        if sign_len == 1:
            return msg
        ret = list(msg)
        index = 0
        while index < len(ret):
            cmp_list = ret[index: index + sign_len]
            cmp_str = ''.join(cmp_list)
            if cmp_str == '(' + ' ' * (sign_len - 1):
                del ret[index + 1: index + sign_len]
            elif cmp_str == ')' + ' ' * (sign_len - 1):
                del ret[index + 1: index + sign_len]
            index += 1
        return ''.join(ret)

    def _handle_msg(self, msg, rm_left_sign, rm_right_sign):
        l_index_st = []
        r_index_st = []
        ret = list(msg)
        sign_len = len(rm_left_sign)
        for index in range(0, len(msg) - sign_len):
            cmp_list = ret[index: index + sign_len]
            cmp_str = ''.join(cmp_list)
            if cmp_str == rm_left_sign:
                l_index_st.append(index)
            elif cmp_str == rm_right_sign:
                r_index_st.append(index)
        while len(r_index_st) != 0 and len(l_index_st) != 0:
            r_index = r_index_st.pop()
            l_index = l_index_st.pop()
            while r_index < l_index:
                l_index = l_index_st.pop()
            ret[r_index: r_index + sign_len] = ')' + ' ' * (sign_len - 1)
            ret[l_index: l_index + sign_len] = '(' + ' ' * (sign_len - 1)
        while len(r_index_st) != 0:
            r_index = r_index_st.pop()
            ret[r_index: r_index + sign_len] = ')' + ' ' * (sign_len - 1)
        while len(l_index_st) != 0:
            l_index = l_index_st.pop()
            ret[l_index: l_index + sign_len] = '(' + ' ' * (sign_len - 1)
        return ''.join(ret)

    def _deal_msg(self, msg):
        """
        该函数回去删除短信body中含有的配对的【】以及[]，替换成为配对的()
        """
        msg = self._handle_msg(msg, '[', ']')
        msg = self._handle_msg(msg, u'【', u'】')
        msg = self._del_extra_space(msg, len('【'))
        return msg

    def post_sms(self, persons, msg):
        """
        该函数会调用/bin/gsmsend 发送短信到我厂内网登记过的员工手机号上.
        :param persons:
            persons是一个list, 每一个list的item由 ('姓名', '电话号码')组成.
        :param msg:
            **请注意，发送中文请使用utf8编码!!!.  msg = '一个utf8编码的msg'
            否则会乱码.**
        :return code:
            返回的是以returncode, stderr, stdout,组成的dict的list
            returncode=0: 发送成功
            returncode非0：发送失败,stderr,stdout打印出错信息
            returnlist: 按照发送persons的顺序回返信息
            例如：
            [
                {'returncode': 0, 'stderr': '', 'stdout': ''}，
                {'returncode': 1, 'stderr': '', 'stdout': 'Use utf8 encode\n'}
            ]
        """
        # if not isinstance(msg, unicode):
        #     raise TypeError('msg should be in unicode')
        print('Start to post_sms')
        shelltool = ShellExec()
        res = []
        if len(persons) == 0:
            res_dict = {}
            res_dict['returncode'] = 1
            res_dict['stderr'] = ''
            res_dict['stdout'] = 'Person list empty\n'
            res.append(res_dict)
            return res
        try:
            print('Handle the post_sms')
            msg = self._deal_msg(msg.decode('utf8'))
            for person in persons:
                print(
                    'Post msg [%s] to [%s] phone [%s]' % (
                        msg, person[0], person[1]
                    )
                )
                print('Start to post_sms')
                cmd = '%s -s emp01.baidu.com:15003 %s@"%s"' % \
                    (self.__smstool, person[1], msg.encode('gbk'))
                res.append(shelltool.run(cmd, timeout=10))
            print('End to post_sms')
        except UnicodeDecodeError as error:
            res_dict = {}
            res_dict['returncode'] = 1
            res_dict['stderr'] = ''
            res_dict['stdout'] = 'Use utf8 encode\n'
            res.append(res_dict)
        except Exception as error:
            res_dict = {}
            res_dict['returncode'] = 1
            res_dict['stderr'] = ''
            res_dict['stdout'] = 'Catch error\n'
            res.append(res_dict)
        return res

def main():
    pattern_phone_number = '^(13|18|15|17)[0-9]{9}\s*$|^(\d{3,4}-)?\d{7,8}\s*$'
    if len(sys.argv) <= 1:
        print "Plase input phone numbers, eg. 15345678912 15345678913"
    import re
    persons = []
    for arg in sys.argv[1:]:
        if not re.match(pattern_phone_number, arg):
            print 'The {0} is not a phone number.'.format(arg)
            continue
        persons.append(('Aleda', arg))
    msg = sys.stdin.read()
    gsm_sender = GsmSender()
    gsm_sender.post_sms(persons, msg)


if __name__ == '__main__':
    main()

# vi:set tw=0 ts=4 sw=4 nowrap fdm=indent
