import socket
import sys
import json
import comms

def lobbyLoop(data, sock):
	while True:
		comms.send(sock, data)
		received = comms.receive(sock)
		# received = sock.recv(1024)
		# received = json.loads(received)
		print ("Received: {}".format(received))

		userInput = raw_input("\nLobby actions:\nReady\t\t(1)\nLeave Lobby\t(2)\n~> ")
		if userInput == "1":
			data = {}
			data['agenda'] = "ready"
			comms.send(sock, data)
			while True:
				received = comms.receive(sock) #<- game start
				if received['agenda'] == 'gameStart':
					myHand = received['data']
					board = []
					print("myHand: {}".format(myHand))
					while True:
						rec = comms.receive(sock)
						if rec['agenda'] == "BSblind":
							pass
						elif rec['agenda'] == "yourTurn":
							userInput = raw_input("\nGame actions:\nRaise\t\t(1)\nFold\t\t(2)\nCheck\t\t(3)\n~> ")
							if userInput == "1":
								data = {}
								data['agenda'] = "raise"
								data['data'] = raw_input("Raise ammount: ")
								comms.send(sock, data)
							elif userInput == "2":
								data = {}
								data['agenda'] = "fold"
								comms.send(sock, data)
							elif userInput == "3":
								data = {}
								data['agenda'] = "check"
								comms.send(sock, data)
						elif rec['agenda'] == "cardReveal":
							board += rec['data']
							print("BOARD: {}".format(board))
							pass
						elif rec['agenda'] == "turnEnd": #???
							pass

		elif userInput == "2":
			data = {}
			data['agenda'] = "leaveLobby"

HOST, PORT = "localhost", 9999
data = " ".join(sys.argv[1:])


# try:
userId = ""
while True:
	userInput = raw_input("\nActions:\nLogin\t\t(1)\nRegister\t(2)\nCreate Lobby\t(3)\nGet Lobbies\t(4)\nJoin Lobby\t(5)\nLogout\t\t(6)\n~>")
	if userInput == "1":
		emailInput = raw_input("Email: ")
		passwordInput = raw_input("Password: ")
		data = {}
		data['agenda'] = "login"
		data['email'] = emailInput
		data['password'] = passwordInput
	elif userInput == "2":
		usernameInput = raw_input("Username: ")
		emailInput = raw_input("Email: ")
		passwordInput = raw_input("Password: ")
		data = {}
		data['agenda'] = "register"
		data['username'] = usernameInput
		data['email'] = emailInput
		data['password'] = passwordInput
	elif userInput == "3":
		data = {}
		data['agenda'] = "createLobby"
		data['userId'] = userId
		data['lobbyName'] = "LOBBYNAME"
		# Connect to server and send data
		# Create a socket (SOCK_STREAM means a TCP socket)
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect((HOST, PORT))
		
		lobbyLoop(data,sock)
		continue;

	elif userInput == "4":
		data = {}
		data['agenda'] = "getLobbies"
	elif userInput == "5":
		data = {}
		data['agenda'] = "joinLobby"
		data['lobbyId'] = raw_input("Lobby id: ")
		data['userId'] = userId
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect((HOST, PORT))
		lobbyLoop(data,sock)

		continue;

	elif userInput == "6":
		data = {}
		data['agenda'] = "logout"
	else:
		print("Unknown user input {}".format(userInput))
		continue
	data['userId'] = userId
	# Connect to server and send data
	# Create a socket (SOCK_STREAM means a TCP socket)
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.connect((HOST, PORT))
	comms.send(sock, data)
	# Receive data from the server and shut down
	received = comms.receive(sock)
	# received = sock.recv(1024)
	# received = json.loads(received)
	print ("Received: {}".format(received))
	if received['status'] != "allreadyLoggedIn" and received['status'] == "ok":
		if received['agenda'] == "login" or received['agenda'] == "register":
			userId = received['userId']
	sock.close()
# finally:
# 	print "Sent:     {}".format(data)
# 	print "Received: {}".format(received)