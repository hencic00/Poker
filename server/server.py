import SocketServer
import User
import lobby
import json
from threading import Thread
import uuid


class MyTCPHandler(SocketServer.BaseRequestHandler):
	"""
	The request handler class for our server.

	It is instantiated once per connection to the server, and must
	override the handle() method to implement communication to the
	client.
	"""
	global users
	users = dict() #LUT {uuid: SQL id}
	lobbies = []

	def handle(self):
		# self.request is the TCP socket connected to the client <---- pass this to new thread?
		self.data = self.request.recv(1024)

		print("{} wrote:".format(self.client_address[0]))
		self.reqData = self.data.decode("utf-8");
		self.reqData = json.loads(self.reqData)
		self.responseData = {}
		self.responseData['agenda'] = self.reqData['agenda']
		#login user
		if self.reqData['agenda'] == "login":
			print("Login attempt: {}\t{}".format(self.reqData['username'],self.reqData['password']))
			self.user = User.getUser(self.reqData['username'])
			if self.user == 0:
				self.responseData['status'] = "nonExistentUser"
			else:
				self.user = User.login(self.reqData['username'], self.reqData['password'])
				if self.user == 0:
					self.responseData['status'] = "wrongPassword"
				else:
					#am i allready logged in?
					if self.user in users.values():
						self.userHash = next((k for k, v in users.items() if v == self.user), None)
						self.responseData['status'] = "allreadyLoggedIn"
						self.responseData['data'] = self.userHash
					else:
						self.responseData['status'] = "ok"
						users[str(uuid.uuid4())] = self.user
					print users
		#register user
		elif self.reqData['agenda'] == "register":
			print("Register attempt: {}\t{}".format(self.reqData['username'],self.reqData['password']))
			self.registerResult = User.register(self.reqData['username'],self.reqData['password'])
			if self.registerResult == 0:
				self.responseData['data'] = "usernameTaken"
			else:
				self.responseData['status'] = "ok" #TODO user UUID se poslje ob vsakem requestu
		#get lobbies
		elif self.reqData['agenda'] == "getLobbies":
			self.responseData['data'] = self.lobbies
		#create a lobby
		elif self.reqData['agenda'] == "createLobby":
			#create new thread
			self.responseData['data'] = "ok"		#TODO check if user is logged in
			thread = Thread(target = lobby.createLobby, args = (self.request, self.lobbies, 1))
			thread.start()
		#join a lobby
		elif self.reqData['agenda'] == "joinLobby":
			self.responseData['data'] = "join lobby request"
		#get profile data
		elif self.reqData['agenda'] == "profileData":
			self.responseData['data'] = "profileData request"
		else:
			print("Unknown request command {}".format(agenda))
			self.responseData['status'] = "badRequest"

		self.request.sendall(json.dumps(self.responseData).encode('utf-8'))

class MyTCPServer(SocketServer.TCPServer):
	def server_bind(self):
		import socket
		self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.socket.bind(self.server_address)

if __name__ == "__main__":
	HOST, PORT = '', 9999

	# Create the server, binding to localhost on port 9999
	#server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)
	server = MyTCPServer((HOST,PORT), MyTCPHandler)
	# Activate the server; this will keep running until you
	# interrupt the program with Ctrl-C
	server.serve_forever()