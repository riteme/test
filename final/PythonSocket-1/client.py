#
# Copyright 2015 riteme
#

import random
import time
import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('127.0.0.1', 2048))
print 'Connected to the server.'

BUF_MAXSIZE = 1024

print client_socket.recv(BUF_MAXSIZE)
for data in ['Apple', 'Banana', 'Juice', 'Fuck', 'TTT', '@!%$&^##$@%^@#$^']:
    client_socket.send(data)
    print client_socket.recv(BUF_MAXSIZE)
    time.sleep(random.random() * 2)

client_socket.send('exitserver')
client_socket.close()
