import socket

def send_message():
    # Destination host and port (must match the server)
    host = '127.0.0.1'
    port = 62555
    
    # Create a TCP/IP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        # Connect to the server
        client_socket.connect((host, port))
        
        # Define and encode the string message into bytes
        message = "Hello, this is a test TCP message!"
        client_socket.sendall(message.encode('utf-8'))
        print("Message sent!")
        
        # Receive the server's reply
        response = client_socket.recv(1024)
        print(f"Server reply: {response.decode('utf-8')}")

if __name__ == "__main__":
    send_message()

# python3 simpleTCPClient.py
#
