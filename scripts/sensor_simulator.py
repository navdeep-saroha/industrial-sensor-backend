import socket

HOST = "127.0.0.1"
PORT = "5000"

points = [
    (1,2,3),
    (4,5,6),
    (7,8,9),
]

with socket.create_connection((HOST, PORT)) as sock:
    for x,y,z in points:
        message = f"{x},{y},{z}\n"
        sock.sendall(message.encode("utf-8"))
        print(f"Sent: {message.strip()}")