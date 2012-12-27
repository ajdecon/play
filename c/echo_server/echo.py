#!/usr/bin/env python

import socket

host = ''
port = 5000
backlog = 5
size = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host,port))
s.listen(backlog)

while 1:
    client, address = s.accept()
    data = client.recv(size)
    if data:
        print "Received message from %s: %s" % (address,data)
        client.send(data)
    client.close()


