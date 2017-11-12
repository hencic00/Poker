import User
import json
import time

def createLobby(lobbies): #TODO spremeni spodnji user v njegov MYSQL id
	#create lobby object
	import uuid
	lobby = {'id': str(uuid.uuid4()), 'name': "myLobby", 'users': dict()}
	print("Created lobby {}".format(lobby['id']))
	#add it to the lobby list
	lobbies[lobby['id']] = lobby
	return lobby['id']

def joinLobby(lobbies, lobbyId, client, reqData, userSid): #sid = sql id
	user = {'sid': userSid, 'socket': client, 'ready': False}

	lobbies[lobbyId]['users'][userSid] = user

	#communicate with client
	responseData = {}
	responseData['agenda'] = reqData['agenda']
	client.sendall(json.dumps(responseData).encode('utf-8')) #send "ok"

	#wait for start game or leave lobby
	waiting = True
	while waiting:
		data = client.recv(1024) #za ready
		reqData = data.decode("utf-8");
		reqData = json.loads(reqData)
		print("LOBBY {}: {}".format(lobbyId,reqData))
		responseData = {}
		responseData['agenda'] = reqData['agenda']
		if reqData['agenda'] == "ready":
			lobbies[lobbyId]['users'][userSid]['ready'] = True
			#TODO poslji vsem da je nekdo readyjal
			while True:
				time.sleep(3)
				print "LOBBY {}: ready users {}/{}".format(lobbyId, readyUsersCount(lobbies[lobbyId]), len(lobbies[lobbyId]['users']))
				if readyUsersCount(lobbies[lobbyId]) == len(lobbies[lobbyId]['users']) and len(lobbies[lobbyId]['users']) > 1: #atleast 2 players
					#start game
					print "LOBBY {}: Game started".format(lobbies[lobbyId]['id'])

					#game logic is in first users thread
					if(userSid == lobbies[lobbyId]['users'][lobbies[lobbyId]['users'].keys()[0]]):
						print "starting game from user {} thread".format(userSid)
					else:
						waiting = False
						break
					#else end thread
		elif reqData['agenda'] == "leaveLobby":
			print "LOBBY {}: {} left.".format(lobby['id'], userSid)
			del lobbies[lobbyId][userSid]
			#send him ok and disconnect the socket
			responseData['status'] = "ok"
			client.sendall(json.dumps(responseData).encode('utf-8'))
			#TODO tell every one else some 1 left


	#wait for user to start game

def leaveLobby(lobbies, lobbyId, user):
	pass

def readyUsersCount(lobby):
	readyCount = 0
	for usr in lobby['users'].values():
		if usr['ready'] == True:
			readyCount += 1
	return readyCount


def getAllLobbiesForFront(lobbies):
	lobbiesForFront = []
	for lob in lobbies.values():
		users = []
		for usr in lob['users'].values():
			users.append(usr['sid'])
		lobby = {'id' : lob['id'], 'name': lob['name'], 'users': users} #todo names?
		lobbiesForFront.append(lobby)
	return lobbiesForFront

def getMyLobbyData(lobbies, lobbyId): #TODO testing
	users = []
	#get user names
	for usr in lobbies[lobbyId]['users']:
		users.append(usr[1])
	lob = {'id' : lobbies[lobbyId]['id'], 'name': lobbies[lobbyId]['name'], 'users': users}
	return lob