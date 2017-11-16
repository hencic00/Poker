import json

def send(socket, data):
	socket.sendall(json.dumps(data).encode('utf-8')) #send "ok"

def recieve(socket):
	data = socket.recv(1024) #za ready
	reqData = data.decode("utf-8");
	reqData = json.loads(reqData)
	return reqData

def broadcastToPlayers(players, data):
	for player in players:
		send(player.socket, data)

def broadcastToEveryoneExcept(players, data):
	pass