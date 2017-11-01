import SocketServer
import User
import json

class MyTCPHandler(SocketServer.BaseRequestHandler):
	"""
	The request handler class for our server.

	It is instantiated once per connection to the server, and must
	override the handle() method to implement communication to the
	client.
	"""

	def handle(self):
		# self.request is the TCP socket connected to the client
		self.data = self.request.recv(1024)

		print("{} wrote:".format(self.client_address[0]))
		self.reqData = self.data.decode("utf-8");
		self.reqData = json.loads(self.reqData)
		self.responseData = {}
		self.responseData['agenda'] = self.reqData['agenda']

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
					self.responseData['status'] = "ok"
					#dodeli neki hash id pa shrani v redis / sql
		elif self.reqData['agenda'] == "register":
			print("Register attempt: {}\t{}".format(self.reqData['username'],self.reqData['password']))
			self.registerResult = User.register(self.reqData['username'],self.reqData['password'])
			if self.registerResult == 0:
				self.responseData['data'] = "usernameTaken"
			else:
				self.responseData['status'] = "ok"
		elif self.reqData['agenda'] == "getLobbies":
			self.responseData['data'] = "getLobbies request"
		elif self.reqData['agenda'] == "joinLobby":
			self.responseData['data'] = "join lobby request"
		elif self.reqData['agenda'] == "profileData":
			self.responseData['data'] = "profileData request"
		else:
			print("Unknown request command {}".format(agenda))
			self.responseData['status'] = "badRequest"
		# just send back the same data, but upper-cased
		self.request.sendall(json.dumps(self.responseData).encode('utf-8'))

if __name__ == "__main__":
	HOST, PORT = "localhost", 9999

	# Create the server, binding to localhost on port 9999
	server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)
	# Activate the server; this will keep running until you
	# interrupt the program with Ctrl-C
	server.serve_forever()