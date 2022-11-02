import socket
import sys

global host
global port
host="10.12.68.8"
port=9999
s=socket.socket()
try:
    s.connect((host,port))

    while True:
        data=s.recv(1024).decode()
        print('The data from the Server has been recieved : DATA - >>' + str(data) + "has been recieved")
        yime=input()
        if(yime=='Quit'):
            s.close()
            sys.exit()
        s.send(yime.encode(),1024)
except socket.error as msg:
    print("No servers to connect")
    print(msg)
    
