import sys
import socket
import atexit
import threading

import chess_core

from imp import reload
from math import *

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
