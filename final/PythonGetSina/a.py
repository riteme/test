#
# Copyright 2015 riteme
#

import socket

url = 'www.sina.com.cn'
try:
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((url, 80))
except:
    print 'Cannot connect with', url

command = 'GET / HTTP/1.1\r\nHost: www.sina.com.cn\r\nConnection: close\r\n\r\n'
client.send(command)

buf = []
BUF_MAXSIZE = 1024
while True:
    tmp = client.recv(BUF_MAXSIZE)
    if not len(tmp) == 0:  # when received nothing, exit.
        buf.append(tmp)
    else:
        break
data = ''.join(buf)

client.close()

locate = data.find('<!DOCTYPE html>')
header  = data[:locate]
html = data[locate:]
print header

with open('sina.html', 'w') as f:
    f.write(html)
with open('sina-header.txt', 'w') as f:
    f.write(header)
with open('sina-all.txt', 'w') as f:
    f.write(data)
