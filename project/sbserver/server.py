import sys
import socket
import atexit
import threading

HOST = "127.0.0.1"
PORT = 23333
MAX_CONNECTIONS = 8
MAX_BUFFER_SIZE = 2048
ENCODING = "utf-8"

if len(sys.argv) > 2:
    HOST = sys.argv[1]
    PORT = int(sys.argv[2])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))

# str:connection
user = {}

# reg {name}
# send {name} {message}
# exit

atexit.register(quit)
def quit():
    global s
    s.close()

def send(conn, message):
    conn.sendall(message.encode(ENCODING))

def serve(conn, addr):
    global user

    name = "Unknown Guest"
    
    while True:
        buf = conn.recv(MAX_BUFFER_SIZE)
        command = buf.decode(ENCODING).strip()

        print("(info) Message from %s:%s: %s" % (addr[0], addr[1], command.strip()))

        parameters = command.split(" ")
        token = parameters[0].lower()

        if token == "reg":
            user[parameters[1]] = conn
            name = parameters[1]

            print("(info) Register new user: %s" % name)

        elif token == "send":
            send(user[parameters[1]], " ".join(parameters[2:]))

        elif token == "exit":
            conn.close()
            user.pop(name)

            print("(warn) %s left the server" % name)

            return None

s.listen(MAX_CONNECTIONS)

while True:
    conn, addr = s.accept()

    print("(info) New connection from %s:%s" % addr)

    t = threading.Thread(target=serve, args=(conn, addr))
    t.start()
