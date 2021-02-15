import socket

host = 'localhost'
port = 9999
address = (host, port)

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((address))
server_socket.listen(5)
print ("Listening for client . . .")
conn, address = server_socket.accept()
print ("Connected to client at ", address)
while True:
    try:
        output = conn.recv(2048)
        if output:
            print ("Message received from client:")
            print (output)

    except:
        sys.exit(0)