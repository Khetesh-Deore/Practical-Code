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





import socket
import os

# Server configuration
SERVER_IP = '127.0.0.1'
PORT = 5005
BUFFER_SIZE = 65507

# Create UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Take file names from user
file_input = input("Enter file names to send (comma separated): ")
files_to_send = [file.strip() for file in file_input.split(",")]

# Send each file
for file_path in files_to_send:
    if not os.path.exists(file_path):
        print(f"[-] File not found: {file_path}")
        continue

    filename = os.path.basename(file_path)
    print(f"[+] Sending file: {filename}")

    # Send file name first
    sock.sendto(filename.encode(), (SERVER_IP, PORT))

    # Send file content
    with open(file_path, "rb") as f:
        while True:
            chunk = f.read(BUFFER_SIZE)
            if not chunk:
                break
            sock.sendto(chunk, (SERVER_IP, PORT))

    # Send end-of-file marker
    sock.sendto(b"__END__", (SERVER_IP, PORT))
    print(f"[+] {filename} sent successfully.\n")

sock.close()
