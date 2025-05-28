import socket
import os

# Server configuration
SERVER_IP = '0.0.0.0'
PORT = 5005
BUFFER_SIZE = 65507  # Max size of UDP packet

# Create UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((SERVER_IP, PORT))
print(f"[+] Server listening on {SERVER_IP}:{PORT}")

def receive_file():
    # Receive filename
    data, addr = sock.recvfrom(BUFFER_SIZE)
    filename = data.decode() 
    print(f"[+] Receiving file: {filename} from {addr}")
    
    with open(f"received_{filename}", "wb") as f:
        while True:
            data, _ = sock.recvfrom(BUFFER_SIZE)
            if data == b"__END__":
                print(f"[+] {filename} received successfully.\n")
                break
            f.write(data)

# Receive 4 files one by one
for _ in range(4):
    receive_file()

sock.close()
