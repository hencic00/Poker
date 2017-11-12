import socket
import sys
import json

HOST, PORT = "localhost", 9999
data = " ".join(sys.argv[1:])


# try:
userId = ""
while True:
	userInput = raw_input("\nActions:\nLogin\t\t(1)\nRegister\t(2)\nCreate Lobby\t(3)\nGet Lobbies\t(4)\nJoin Lobby\t(5)\nLogout\t\t(6)\n~>")
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
		data['agenda'] = "createLobby"
		data['userId'] = userId
		# Connect to server and send data
		data = json.dumps(data)
		# Create a socket (SOCK_STREAM means a TCP socket)
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect((HOST, PORT))
		
		while True:
			print("Sending: {}".format(data))
			sock.sendall(data)
			received = sock.recv(1024)
			received = json.loads(received)
			print ("Received: {}".format(received))

			userInput = raw_input("\nLobby actions:\nReady\t\t(1)\nLeave Lobby\t(2)\n~>")
			if userInput == "1":
				data = {}
				data['agenda'] = "ready"
			elif userInput == "2":
				data = {}
				data['agenda'] = "leaveLobby"
			data = json.dumps(data)
		continue;

	elif userInput == "4":
		data = {}
		data['agenda'] = "getLobbies"
	elif userInput == "5":
		data = {}
		data['agenda'] = "joinLobby"
		data['lobbyId'] = raw_input("Lobby id: ")
		data['userId'] = userId
		data = json.dumps(data)
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect((HOST, PORT))
		while True:
			print("Sending: {}".format(data))
			sock.sendall(data)
			received = sock.recv(1024)
			received = json.loads(received)
			print ("Received: {}".format(received))

			userInput = raw_input("\nLobby actions:\nReady\t\t(1)\nLeave Lobby\t(2)\n~>")
			if userInput == "1":
				data = {}
				data['agenda'] = "ready"
			elif userInput == "2":
				data = {}
				data['agenda'] = "leaveLobby"
			data = json.dumps(data)
		continue;

	elif userInput == "6":
		data = {}
		data['agenda'] = "logout"
	else:
		print("Unknown user input {}".format(userInput))
		continue
	data['userId'] = userId
	# Connect to server and send data
	data = json.dumps(data)
	print("Sending: {}".format(data))
	# Create a socket (SOCK_STREAM means a TCP socket)
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.connect((HOST, PORT))
	sock.sendall(data)
	# Receive data from the server and shut down
	received = sock.recv(1024)
	received = json.loads(received)
	print ("Received: {}".format(received))
	if received['status'] != "allreadyLoggedIn" and received['status'] == "ok":
		if received['agenda'] == "login" or received['agenda'] == "register":
			userId = received['userId']
	sock.close()
# finally:
# 	print "Sent:     {}".format(data)
# 	print "Received: {}".format(received)