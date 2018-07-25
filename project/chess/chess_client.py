import sys
import socket
import atexit
import threading

# import frontend

HOST = sys.argv[1]
PORT = int(sys.argv[2])

BUFFER_MAX_SIZE = 2048
ENCODING = "utf-8"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

atexit.register(quit)
def quit():
	global s
	s.close()

def send(message):
	global s
	s.sendall(message.encode(ENCODING))

def receive():
	global s
	data = s.recv(BUFFER_MAX_SIZE)
	message = data.decode(ENCODING)
	return message

def listener():
	global s

	while True:
		print(receive())

t = threading.Thread(target=listener)
t.start()

# frontend.start()

while True:
	command = input(">>> ")
	send(command)

	if command.lower() == "exit":
		del t
		s.close()
		exit(0)