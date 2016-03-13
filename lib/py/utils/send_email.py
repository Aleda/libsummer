#!/usr/bin/env python
# -*- coding: utf-8 -*-

################################################################################
#
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
#
################################################################################
"""
This module provide sending email.
Any details see doctest.
function include:
        * cc
        * attachments
        * any content-type
        * mixed

Authors: Aleda(lishuo02@baidu.com)
Date:    2015/09/14 16:11:06
Version: 1.0
"""

__ALL__ = ['sendmail']

SMTP_DICT = {"smtp_server": None, #proxy-in.baidu.com, hotswap-in.baidu.com
             "smtp_port": 25,
             "smtp_username": None,
             "smtp_password": None,
             "smtp_debuglevel": None,
             "smtp_starttls": False}


class EmailMessage(object):
    """ The summary of the mail sender.
    Based on webpy/web/utils.py
    Args:
        from_address                    - The address that send.
        to_address                      - The email address to send.
        subject                         - The subject.
        message                         - The message that you want to send.
        headers                         - The mail headers.
        kw                              - Including:
                                          Cc: carbon copy list;
                                          Bcc: secret cc;                                 
    """
    def __init__(self, from_address, to_address, subject, message, headers=None, **kw):
        def listify(x):
            if not isinstance(x, list):
                return [safestr(x)]
            else:
                return [safestr(a) for a in x]
        subject = safestr(subject)
        message = safestr(message)
        from_address = safestr(from_address)
        to_address = listify(to_address)    
        cc = listify(kw.get('cc', []))
        bcc = listify(kw.get('bcc', []))
        recipients = to_address + cc + bcc
        import email.Utils
        self.from_address = email.Utils.parseaddr(from_address)[1]
        self.recipients = [email.Utils.parseaddr(r)[1] for r in recipients]        
        self.headers = dictadd({
          'From': from_address,
          'To': ", ".join(to_address),
          'Subject': subject
        }, headers or {})
        if cc:
            self.headers['Cc'] = ", ".join(cc)
        self.message = self.new_message()
        self.message.add_header("Content-Transfer-Encoding", "7bit")
        self.message.add_header("Content-Disposition", "inline")
        self.message.add_header("MIME-Version", "1.0")
        ##! Modified by Aleda at 2015-11-27 12:47
        ##! determine the Content-Type.
        self.message.add_header("Content-type", headers.get("Content-Type", "text/html"))
        self.message.set_payload(message, 'utf-8')
        self.multipart = False
        
    def new_message(self):
        """ New a email message.
        Returns:
            message                     - A message with email.Message
        """
        from email.Message import Message
        return Message()
        
    def attach(self, filename, content, content_type=None):
        """ The summary of the attach.
        Attach the file to email.
        Args:
            filename                    - The file name.
            content                     - The file content.
        """
        if not self.multipart:
            msg = self.new_message()
            ##! Added by Aleda at 2015-11-27 12:58
            msg.add_header("Content-Type", "multipart/alternative; boundary=bcaec520ea5d6918e204a8cea3b4")
            msg.attach(self.message)
            self.message = msg
            self.multipart = True
                        
        import mimetypes
        try:
            from email import encoders
        except:
            from email import Encoders as encoders
            
        content_type = content_type or mimetypes.guess_type(filename)[0] or "applcation/octet-stream"
        
        msg = self.new_message()
        msg.set_payload(content)
        msg.add_header('Content-Type', content_type)
        msg.add_header('Content-Disposition', 'attachment', filename=filename)
        
        if not content_type.startswith("text/"):
            encoders.encode_base64(msg)

        self.message.attach(msg)

    def prepare_message(self):
        """ Prepare the email message.
        """
        for k, v in self.headers.iteritems():
            if k.lower() == "content-type":
                ##! Modified by Aleda at 2015-11-27 12:45
                ##! Not need to change the content-type.
                continue
            else:
                self.message.add_header(k, v)

        self.headers = {}

    def send(self):
        self.prepare_message()
        #for part in self.message.walk():
        #    print part.get_content_type()
        #    print part.keys()
        #    print part.values()
        message_text = self.message.as_string()
    
        if SMTP_DICT.get('smtp_server'):
            server = SMTP_DICT.get('smtp_server')
            port = SMTP_DICT.get('smtp_port', 0)
            username = SMTP_DICT.get('smtp_username') 
            password = SMTP_DICT.get('smtp_password')
            debug_level = SMTP_DICT.get('smtp_debuglevel', None)
            starttls = SMTP_DICT.get('smtp_starttls', False)

            import smtplib
            smtpserver = smtplib.SMTP(server, port)

            if debug_level:
                smtpserver.set_debuglevel(debug_level)

            if starttls:
                smtpserver.ehlo()
                smtpserver.starttls()
                smtpserver.ehlo()

            if username and password:
                smtpserver.login(username, password)

            smtpserver.sendmail(self.from_address, self.recipients, message_text)
            smtpserver.quit()
        elif SMTP_DICT.get('email_engine') == 'aws':
            import boto.ses
            c = boto.ses.SESConnection(
              aws_access_key_id=SMTP_DICT.get('aws_access_key_id'),
              aws_secret_access_key=web.api.config.get('aws_secret_access_key'))
            c.send_raw_email(self.from_address, message_text, self.recipients)
        else:
            sendmail = SMTP_DICT.get('sendmail_path', '/usr/sbin/sendmail')
        
            assert not self.from_address.startswith('-'), 'security'
            for r in self.recipients:
                assert not r.startswith('-'), 'security'
                
            cmd = [sendmail, '-f', self.from_address] + self.recipients

            import subprocess
            if subprocess:
                p = subprocess.Popen(cmd, stdin=subprocess.PIPE)
                p.stdin.write(message_text)
                p.stdin.close()
                p.wait()
            else:
                i, o = os.popen2(cmd)
                i.write(message)
                i.close()
                o.close()
                del i, o
                
    def __repr__(self):
        return "<EmailMessage>"
    
    def __str__(self):
        return self.message.as_string()


def sendmail(from_address, to_address, subject, message, headers=None, **kw):
    """
    Sends the email message `message` with mail and envelope headers
    for from `from_address_` to `to_address` with `subject`. 
    Additional email headers can be specified with the dictionary 
    `headers.
    
    Optionally cc, bcc and attachments can be specified as keyword arguments.
    Attachments must be an iterable and each attachment can be either a 
    filename or a file object or a dictionary with filename, content and 
    optionally content_type keys.

    If `web.config.smtp_server` is set, it will send the message
    to that SMTP server. Otherwise it will look for 
    `/usr/sbin/sendmail`, the typical location for the sendmail-style
    binary. To use sendmail from a different path, set `web.config.sendmail_path`.
    Test:
        >>> sendmail('spider@db-spi-offline0.db01.baidu.com', 'lishuo02@baidu.com', \
            'HelloWorld', 'Hi, Anyone.')

        >>> sendmail('spider@db-spi-offline0.db01.baidu.com', 'lishuo02@baidu.com', \
            'HelloWorld', 'Hi, Anyone.', cc=['lishuo02@baidu.com', '348983192@qq.com'])

        >>> sendmail('spider@db-spi-offline0.db01.baidu.com', 'lishuo02@baidu.com', \
            'HelloWorld', 'Hi, Anyone.', cc=['lishuo02@baidu.com', '348983192@qq.com'])

        >>> sendmail('spider@db-spi-offline0.db01.baidu.com', 'lishuo02@baidu.com', \
            'HelloWorld', 'Hi, Anyone.', cc=['lishuo02@baidu.com', '348983192@qq.com'], \
            attachments=['TODO'])


    """
    attachments = kw.pop("attachments", [])
    mail = EmailMessage(from_address, to_address, subject, message, headers, **kw)
    import os
    for a in attachments:
        if isinstance(a, dict):
            mail.attach(a['filename'], a['content'], a.get('content_type'))
        elif hasattr(a, 'read'): # file
            filename = os.path.basename(getattr(a, "name", ""))
            content_type = getattr(a, 'content_type', None)
            mail.attach(filename, a.read(), content_type)
        elif isinstance(a, basestring):
            f = open(a, 'rb')
            content = f.read()
            f.close()
            filename = os.path.basename(a)
            mail.attach(filename, content, None)
        else:
            raise ValueError, "Invalid attachment: %s" % repr(a)
    mail.send()


def safestr(obj, encoding='utf-8'):
    r"""
    Converts any given object to utf-8 encoded string. 
    
        >>> safestr('hello')
        'hello'
        >>> safestr(u'\u1234')
        '\xe1\x88\xb4'
        >>> safestr(2)
        '2'
    """
    if isinstance(obj, unicode):
        return obj.encode(encoding)
    elif isinstance(obj, str):
        return obj
    elif hasattr(obj, 'next'): # iterator
        return itertools.imap(safestr, obj)
    else:
        return str(obj)


def dictadd(*dicts):
    """
    Returns a dictionary consisting of the keys in the argument dictionaries.
    If they share a key, the value from the last argument is used.
        >>> dictadd({1: 0, 2: 0}, {2: 1, 3: 1})
        {1: 0, 2: 1, 3: 1}
    """
    result = {}
    for dct in dicts:
        result.update(dct)
    return result


def main():
    """ Main
    """
    pass

if __name__ == '__main__':
    main()
