#!/usr/bin/env python
# -*- coding: utf-8 -*-

################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
This module for the wrapper of running cmd in cli(*inux).

Authors: Aleda(lishuo02@baidu.com)
Date:    2015/10/30 16:18:06
Version: 1.0.0
"""

import subprocess
import datetime
import time

__ALL__ = ['CMDRunner']

CMD_RUNNER_GLOBAL_POLL_INTERVAL_TIME = 0.5
CMD_RUNNER_GLOBAL_POLL_TIME_OUT = 5
CMD_RUNNER_GLOBAL_MULTI_THREAD_NUM = 20

class CMDRunner(object):
    """ The summary of the CMDRunner.
    CMDRunner is a wrapper for python calling shell cmd.
    """
    class CMDRunnerError(IOError):
        """ Exceptions.
        """
        pass

    @classmethod
    def kill_process_pipe(cls, process):
        """ close the stdin, stdout, stderr & kill it.
        Args:
            process                 - The object of process.
        Returns:
            ret_code                - The ret code.
                                      * 0 => fail.
                                      * 1 => success.
        """
        assert process
        if process.stdin:
            process.stdin.close()
        if process.stdout:
            process.stdout.close()
        if process.stderr:
            process.stderr.close()
        try:
            process.kill()
        except OSError:
            return 0
        return 1

    @classmethod
    def run_cmd(cls, cmd, timeout=0, *args, **kwargs):
        """ Run cmd in bash.
        Args:
            cmd                         - The cmd.
            timeout                     - The timeout of running cmd.
            kwargs                      - The kwargs. see subprocess.Popen
        Returns:
            returncode                  - The subprocess run status.
            stdout                      - The string of stdout.
            stderr                      - The string of stderr.
        Test:
            >>> returncode, stdout, stderr = CMDRunner.run_cmd('uname')
            >>> print returncode
            0
            >>> print stdout.rstrip("\\n")
            Linux
            >>> returncode, stdout, stderr = \\
            ... CMDRunner.run_cmd('xargs -i curl -I {}', stdin='www.baidu.com/')
            >>> print returncode
            0
        """
        if 'stdin' in kwargs and isinstance(kwargs['stdin'], basestring):
            stdin = kwargs.pop('stdin')
        else:
            stdin = None
        kwargs.setdefault('stdout', subprocess.PIPE)
        kwargs.setdefault('stderr', subprocess.PIPE)
        kwargs.setdefault('close_fds', True)
        kwargs.setdefault('shell', True)
        timeout = CMD_RUNNER_GLOBAL_POLL_TIME_OUT if timeout == 0 else timeout
        
        start = datetime.datetime.now()
        p = subprocess.Popen(cmd, stdin=subprocess.PIPE if stdin else None, **kwargs)
        ##! Be careful for the return of p.poll()
        ##! None & 0
        stdout, stderr = p.communicate(stdin)
        while p.poll() is None and stdin is None:
            time.sleep(CMD_RUNNER_GLOBAL_POLL_INTERVAL_TIME)
            print p.poll()
            now = datetime.datetime.now()
            if (now - start).seconds > timeout:
                try:
                    p.terminate()
                except Exception as e:
                    print e
                finally:
                    stdout_str = p.stdout.read()
                    stderr_str = p.stderr.read()
                    cls.kill_process_pipe(p)
                    return (-1, stdout_str, stderr_str)

        return p.returncode, stdout, stderr

    @classmethod
    def run_cmd_multi_thread(cls, cmd, stdin, thread_num=0, *args, **kwargs):
        """ Run cmd with stdin in multi threads.
        Args:
            cmd                     - The cmd string.
            stdin                   - The stdin iteratable.
            thread_num              - The thread number.
        Returns:
            ans_dict                - The ans dict:
                                      {input_line_key: (ret_code, stdout, stderr)}
        Test:
            >>> stdin = ['www.baidu.com/', 'www.sina.com.cn/', 'www.qq.com/']
            >>> cmd = 'xargs -i curl -I {}'
            >>> ans_list = CMDRunner.run_cmd_multi_thread(cmd, \\
            ... stdin, 3)
            >>> ans_key_list = []
            >>> for ans in ans_list:
            ...     ans_key_list.append(ans.keys())
            ... 
            >>> print ans_key_list
            [['www.baidu.com/'], ['www.sina.com.cn/'], ['www.qq.com/']]
        """
        assert cmd and stdin
        import Queue
        import threading
        kwargs.setdefault('stdout', subprocess.PIPE)
        kwargs.setdefault('stderr', subprocess.PIPE)
        kwargs.setdefault('close_fds', True)
        kwargs.setdefault('shell', True)

        thread_num = CMD_RUNNER_GLOBAL_MULTI_THREAD_NUM if thread_num == 0 else thread_num
        def put_input_into_queue():
            for line in stdin:
                job_queue.put(line)
            for _ in xrange(thread_num):
                job_queue.put(EOFError)

        def working():
            while True:
                job = job_queue.get()
                if job is EOFError:
                    ans_queue.put(EOFError)
                    break
                ans_queue.put({job: cls.run_cmd(cmd, timeout=5, 
                    stdin=job, **kwargs)})

        job_queue = Queue.Queue(thread_num * 4)
        ans_queue = Queue.Queue()

        thread_put_inputs = threading.Thread(target=put_input_into_queue)
        thread_put_inputs.deamon = True
        thread_put_inputs.start()

        work_threads = [threading.Thread(target=working) for _ in xrange(thread_num)]
        for thread in work_threads:
            thread.deamon = True
            thread.start()
        thread_done_num = 0
        while thread_done_num < thread_num:
            ans = ans_queue.get()
            if ans is EOFError:
                thread_done_num += 1
            else:
                yield ans

        thread_put_inputs.join()
        for thread in work_threads:
            thread.join()

def run_cmd(cmd, timeout, *args, **kwargs):
    """ Run cmd API.
    """
    return CMDRunner.run_cmd(cmd, timeout, *args, **kwargs)

def main():
    """ Main
    Test:
    """
    #import doctest
    #doctest.testmod()
    # python -m doctest -v constant.py


if __name__ == '__main__':
    main()
