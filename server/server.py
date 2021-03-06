import socket
import User
import lobby
import json
from threading import Thread
import uuid
import comms

class ThreadedServer(object):
	global users
	users = dict() #LUT {uuid: SQL id}
	lobbies = dict() #LUT {uuid: {id, name, users}}

	#TODO MUTEX!

	def __init__(self, host, port):
		self.host = host
		self.port = port
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.sock.bind((self.host, self.port))

	def listen(self):
		self.sock.listen(50) #max con size?
		while True:
			clientSock, address = self.sock.accept()
			# print("User connected {}".format(address))
			clientSock.settimeout(None)
			clientHandlerThead = Thread(target = self.handle,args = (clientSock,address))
			clientHandlerThead.daemon = True
			clientHandlerThead.start()

	def handle(self, clientSock, address):
		packetSize = 1024
		closeSocket = True
		try:
			reqData = comms.receive(clientSock)
		except socket.error as msg:
			clientSock.close()
			return
		responseData = {}
		responseData['agenda'] = reqData['agenda']
		#login user
		if reqData['agenda'] == "login":
			print("Login attempt: {}\t{}".format(reqData['email'], reqData['password']))
			user = User.getUser(reqData['email'])
			if user == 0:
				responseData['status'] = "nonExistentUser"
			else:
				user = User.login(reqData['email'], reqData['password'])
				if user == 0:
					responseData['status'] = "wrongPassword"
				else:
					#am i allready logged in?
					if user in users.values():
						userHash = next((k for k, v in users.items() if v == user), None)
						responseData['status'] = "allreadyLoggedIn"
						responseData['data'] = userHash
					else:
						responseData['username'] = User.getUser(reqData['email'])[1]
						responseData['status'] = "ok"
						responseData['userId'] = str(uuid.uuid4())
						users[responseData['userId']] = user
					print users
		#register user
		elif reqData['agenda'] == "register":
			print("Register attempt: {}\t{}".format(reqData['username'], reqData['email'], reqData['password']))
			user = User.register(reqData['username'], reqData['email'],reqData['password'])
			if user == 0:
				responseData['status'] = "emailTaken"
			else:
				responseData['status'] = "ok"
				responseData['userId'] = str(uuid.uuid4())
				users[responseData['userId']] = user
		#is user logged in legitely?
		elif reqData['userId'] not in users:
			responseData['status'] = "unauthenticated"
		else:
			#get lobbies
			if reqData['agenda'] == "getLobbies":
				responseData['data'] = lobby.getAllLobbiesForFront(self.lobbies)
				responseData['status'] = "ok"
			#create a lobby
			elif reqData['agenda'] == "createLobby":
				closeSocket = False
				responseData['data'] = "ok"
				createdLobbyId =lobby.createLobby(self.lobbies, reqData['lobbyName'])
				lobby.joinLobby(self.lobbies, createdLobbyId, users[reqData['userId']], clientSock, reqData)
			#join a lobby
			elif reqData['agenda'] == "joinLobby":
				if reqData['lobbyId'] in self.lobbies:
					closeSocket = False
					lobby.joinLobby(self.lobbies, reqData['lobbyId'], users[reqData['userId']], clientSock, reqData)
				else:
					responseData['status'] = "lobbyNotFound"
			#get profile data
			elif reqData['agenda'] == "profileData":
				responseData['data'] = "profileData request"
			elif reqData['agenda'] == "logout":
				if reqData['userId'] in users:
					del users[reqData['userId']]
					responseData['status'] = "ok"
				else:
					responseData['status'] = "notLoggedIn"
			else:
				print("Unknown request command {}".format(agenda))
				responseData['status'] = "badRequest"

		if closeSocket:
			try:
				comms.send(clientSock, responseData)
			except socket.error as msg:
				print("Exception handled: {}".format(msg))
				clientSock.close()
				return
			print "Closing socket for {}.".format(address)
			clientSock.close()


if __name__ == "__main__":
	HOST, PORT = '', 9999

	ThreadedServer(HOST, PORT).listen()