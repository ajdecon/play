#!/usr/bin/env python

import zmq
import sys
import time
import random

try:
    message = sys.argv[1]
except IndexError:
    message = "not creative, are we?"

port = "5000"
context = zmq.Context()
socket = context.socket(zmq.PAIR)
socket.connect("tcp://localhost:%s" % (port))

socket.send(message)
echo=socket.recv()
print "received back: %s" % (echo)
