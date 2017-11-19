import json
import struct

def send(socket, data):
	strData = json.dumps(data)
	strData = strData.encode('utf-8')
	# print(len(strData))
	# msgLenPackage = bytearray.fromhex(format(len(strData), '04x'))
	# print len(strData)
	msgLenPackage = struct.pack('!i', len(strData))
	print "sending:{}".format(msgLenPackage);
	socket.sendall(msgLenPackage)
	print("Sending: {}".format(strData))
	socket.sendall(strData)

def receive(socket):
	# msgLenPackage = socket.recv(4)
	# msgLenPackage = struct.unpack("I", bytearray(msgLenPackage))
	# print("msglen:{}".format(msgLenPackage))
	msgLenPackage = 0
	index = 0
	while index < 4:
		recBuf = socket.recv(1)
		msgLenPackage += (ord(recBuf) * 2**(8 * index))
		index = index + 1

	# msgLenPackage = struct.unpack('!i', buf[:4])[0]

	reqData = socket.recv(msgLenPackage)
	print reqData
	print(">>>> {}".format(msgLenPackage))
	reqData = reqData.decode("utf-8");
	reqData = json.loads(reqData)
	print("==>> {}".format(reqData))
	return reqData

def broadcastToPlayers(players, data):
	for player in players:
		send(player.socket, data)

def broadcastToEveryoneExcept(players, data):
	pass