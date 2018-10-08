#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('10.1.87.212', 1468))
content = u'qwer1234*| 中文测试*|\n'
sock.send(content.encode('utf-8'))
sock.close()
