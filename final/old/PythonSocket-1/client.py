#
# Copyright 2015 riteme
#

import random
import time
import socket
import sys

SERVER_IP = '127.0.0.1'
SERVER_PORT = 2048

DATA_START = 1
if not __name__ == '__main__' or  len(sys.argv) == 1:
    print 'No parameters given.'
else:
    if len(sys.argv) > 1:
        SERVER_IP = sys.argv[1]
        DATA_START += 1
    if len(sys.argv) > 2:
        SERVER_PORT = int(sys.argv[2])
        DATA_START += 1
    
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((SERVER_IP, SERVER_PORT))
print 'Connected to the server.'

BUF_MAXSIZE = 1024

print client_socket.recv(BUF_MAXSIZE)

for data in sys.argv[DATA_START:]:
    client_socket.send(data)
    if data == 'exit':
        print 'Exited.'
        break
    if data == 'exitserver':
        print 'Client and server exited.'
        break

    print client_socket.recv(BUF_MAXSIZE)
    time.sleep(random.random() * 2)

if not 'exit' in sys.argv and not 'exitserver' in sys.argv:
    client_socket.send('exit')
client_socket.close()
