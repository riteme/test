#
# Copyright 2015 riteme
#

import threading
import socket
import sys

SOCKET_IP = '127.0.0.1'
SOCKET_PORT = 2048
SOCKET_LISTEN = 4

if __name__ == '__main__':
    if len(sys.argv) > 1:
        SOCKET_IP = sys.argv[1]
    if len(sys.argv) > 2:
        SOCKET_PORT = int(sys.argv[2])
    if len(sys.argv) > 3:
        SOCKET_LISTEN = int(sys.argv[3])

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((SOCKET_IP, SOCKET_PORT))
server_socket.listen(SOCKET_LISTEN)
print 'Server opened. Waiting for connections...'

BUF_MAXSIZE = 1024
flag = True

def tcp_connection(sock, address):
    global server_socket
    global flag

    try:
        print 'New connection from', str(address) + '.'
        sock.send('Welcome!')
        while flag:
            buf = sock.recv(BUF_MAXSIZE)
            if buf == 'exit' or not buf:
                print 'Thread on', address, 'received EXIT signal.'
                break
            elif buf == 'exitserver':
                print 'Thread on', address, 'received EXITSER signal.'
                flag = False
                server_socket.shutdown(socket.SHUT_RDWR)
                break
            print 'Thread on', address, 'received', buf + '.'
            sock.send('Hello, ' + buf + '.')
    finally:
        sock.close()
        print 'Thread on', address, 'exited.'

while flag:
    try:
        client_socket, client_address = server_socket.accept()
    except socket.error:
        print 'Socket shutdown.'
    else:
        print 'MAIN: Create new thread.'
        t = threading.Thread(target=tcp_connection, args=(client_socket, client_address))
        t.start()

server_socket.close()

print 'Server exited.'
