import time
import socket

_IP = '127.0.0.1'
_PORT = 2324

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
sock.connect((_IP, _PORT))

'''
count = 0
while count < 10:
    msg = 'test'.encode('utf8')
    sock.send(msg)
    count = count + 1
    time.sleep(2)
'''

msg = 'test'.encode('utf8')
sock.send(msg)
