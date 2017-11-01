import socket
import sys
import json

HOST, PORT = "localhost", 9999
data = " ".join(sys.argv[1:])


# try:

while True:
	userInput = raw_input("\nActions:\nLogin\t\t(1)\nRegister\t(2)\nGet Lobbies\t(3)\n~>")
	if userInput == "1":
		usernameInput = raw_input("Username: ")
		passwordInput = raw_input("Password: ")
		data = {}
		data['agenda'] = "login"
		data['username'] = usernameInput
		data['password'] = passwordInput
	elif userInput == "2":
		usernameInput = raw_input("Username: ")
		passwordInput = raw_input("Password: ")
		data = {}
		data['agenda'] = "register"
		data['username'] = usernameInput
		data['password'] = passwordInput
	elif userInput == "3":
		data = {}
		data['agenda'] = "getLobbies"
	else:
		print("Unknown user input {}".format(userInput))
		continue
	# Connect to server and send data
	data = json.dumps(data)
	print("Sending: {}".format(data))
	# Create a socket (SOCK_STREAM means a TCP socket)
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.connect((HOST, PORT))
	sock.sendall(data)
	# Receive data from the server and shut down
	received = sock.recv(1024)
	print ("Received: {}".format(received))
	sock.close()
# finally:
# 	print "Sent:     {}".format(data)
# 	print "Received: {}".format(received)