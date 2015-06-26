#
# Copyright 2015 riteme
#

import threading
import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('127.0.0.1', 2048))
server_socket.listen(4)
print 'Server opened. Waiting for connections...'

BUF_MAXSIZE = 1024

def tcp_connection(socket, address):
    try:
        print 'New connection from', address, '.'
        socket.send('Welcome!')
        while True:
            buf = socket.recv(BUF_MAXSIZE)
            if buf == 'exit' or not buf:
                print 'Thread on', address, 'received EXIT signal.'
                break
            print address, 'received', buf, '.'
            socket.send('Hello, ' + buf)
    finally:
        socket.close()
        print 'Thread on', address, 'exited.'

while True:
    client_socket, client_address = server_socket.accept()
    t = threading.Thread(target=tcp_connection, args=(client_socket, client_address))
    t.start()
    print 'MAIN: Create new thread.'

server_socket.close()

print 'Server exited.'
