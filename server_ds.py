import socket
import sys


def create_sock():
    global host
    global port
    global s
    host=""
    port=9999
    print("Hello")
    s = socket.socket()



# Binding the Socket and listening for connections

def bind_sock():

    try:
        global host
        global port
        global s

        print("Binding the port with port number :  " + str(port))

        s.bind((host,port))
        s.listen(5)
    except socket.error:
        print("Socket Binding error")
        bind_sock()
# Estalish connection with a client  (socekt must be listening)

def socket_accept():
    print("Binding completed, now listening .. ...")
    connectionsock,addr=s.accept()
    print("Connection has been established with a client with IP :" + str(addr[0]) + " and port number :" + str(addr[1]))

    send_commands(connectionsock)
    connectionsock.close()


def send_commands(connectionsock):
    while True:
        cmd = input()
        if cmd == 'Quit':
            connectionsock.close()
            s.close()
            sys.exit()
        if len(str.encode(cmd))>0:
            connectionsock.send(str.encode(cmd))
            client_resp=str(connectionsock.recv(1024))
            print(client_resp,end='')

def main():
    create_sock()
    bind_sock()
    socket_accept()
main()