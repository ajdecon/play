#!/usr/bin/env python

import zmq
import time
import random
import sys

port = 5000
context = zmq.Context()
socket = context.socket(zmq.PAIR)
socket.bind("tcp://*:%s" % (port))

while True:
    msg = socket.recv()
    print "Server received message: %s" % (msg)
    socket.send(msg)
