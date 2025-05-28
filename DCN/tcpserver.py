import socket, os

s = socket.socket()
s.bind(('', 9999))
s.listen(1)
print("Server is waiting for client connection...")
c, _ = s.accept()

print("Client:", c.recv(1024).decode())
c.send(b"Hello from Server")

# Calculator
expr = c.recv(1024).decode()
c.send(str(eval(expr)).encode())

# Receive requested file name
file_name = c.recv(1024).decode()
if os.path.exists(file_name):
    with open(file_name, 'rb') as f:
        data = f.read()
        c.sendall(data)
    c.shutdown(socket.SHUT_WR)
    print(f"Sent file: {file_name}")
else:
    c.send(b"File not found")
    c.shutdown(socket.SHUT_WR)
    print("File not found.")
    
c.close()









import socket

s = socket.socket()
s.connect(('localhost', 9999))

s.send(b"Hello from Client")
print("Server:", s.recv(1024).decode())

expr = input("Enter expression (e.g., 2+3*4): ")
s.send(expr.encode())
print("Result:", s.recv(1024).decode())

# Ask user for file name to request
file_name = input("Enter file name to download from server: ")
s.send(file_name.encode())

# Save with same name
with open('received_' + file_name, 'wb') as f:
    while True:
        data = s.recv(1024)
        if not data: break
        f.write(data)
print("File received.")
s.close()
