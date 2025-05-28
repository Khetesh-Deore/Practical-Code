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
