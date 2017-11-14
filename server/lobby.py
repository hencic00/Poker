import User
import json
import time

def createLobby(lobbies, lobbyName): #TODO spremeni spodnji user v njegov MYSQL id
	#create lobby object
	import uuid
	lobby = {'id': str(uuid.uuid4()), 'name': lobbyName, 'users': dict()}
	print("Created lobby {}".format(lobby['id']))
	#add it to the lobby list
	lobbies[lobby['id']] = lobby
	return lobby['id']

def joinLobby(lobbies, lobbyId, userSid, clientSock, reqData): #sid = sql id
	user = {'sid': userSid, 'socket': clientSock, 'ready': False}

	lobbies[lobbyId]['users'][userSid] = user

	#communicate with client
	resData = {}
	resData['agenda'] = reqData['agenda']
	clientSock.sendall(json.dumps(resData).encode('utf-8')) #send "ok"

	#tell everyone a player joined
	notifyEveryoneExcept(lobbies, lobbyId, "playerJoined", {'userSid':userSid, 'username':User.getUsername(userSid)}, userSid)

	#wait for start game or leave lobby
	waiting = True
	while waiting:
		data = clientSock.recv(1024) #za ready
		reqData = data.decode("utf-8");
		reqData = json.loads(reqData)
		print("LOBBY {}: {}".format(lobbyId,reqData))
		resData = {}
		resData['agenda'] = reqData['agenda']
		if reqData['agenda'] == "ready":
			lobbies[lobbyId]['users'][userSid]['ready'] = True
			notifyEveryoneExcept(lobbies, lobbyId, "userReady", None, userSid)
			while True:
				time.sleep(3)
				print "LOBBY {}: ready users {}/{}".format(lobbyId, readyUsersCount(lobbies[lobbyId]), len(lobbies[lobbyId]['users']))
				if readyUsersCount(lobbies[lobbyId]) == len(lobbies[lobbyId]['users']) and len(lobbies[lobbyId]['users']) > 1: #atleast 2 players
					#game logic is in first users thread
					if(userSid == lobbies[lobbyId]['users'][lobbies[lobbyId]['users'].keys()[0]]['sid']): #try and fire me bois
						print "starting game from user {} thread".format(userSid)
						#start game
						print "LOBBY {}: Game started".format(lobbies[lobbyId]['id'])
						startGame(lobbies, lobbyId)
						waiting = False
						break
					#else end thread
					else:
						waiting = False
						break
					
		elif reqData['agenda'] == "leaveLobby":
			leaveLobby(lobbies, lobbyId, userSid, clientSock, resData)
			break
	#wait for user to start game

def leaveLobby(lobbies, lobbyId, userSid, clientSock, resData):#TODO: MUTEX
	print "LOBBY {}: {} left.".format(lobbies[lobbyId]['id'], userSid)
	#send him ok and disconnect the socket
	resData['status'] = "ok"
	clientSock.sendall(json.dumps(resData).encode('utf-8'))
	clientSock.close();
	del lobbies[lobbyId]['users'][userSid]
	notifyEveryone(lobbies, lobbyId, "playerLeft", {'userSid':userSid, 'username':User.getUsername(userSid)}, userSid);
	
	#if the leaving player is the last one, destroy the lobby
	if len(lobbies[lobbyId]['users']) == 0:
		print "Deleting empty lobby {}.".format(lobbyId)
		del lobbies[lobbyId]

def notifyEveryone(lobbies, lobbyId, status, data, userSid):
	resData = {}
	resData['status'] = status
	if data != None:
		resData['data'] = data
	for user in lobbies[lobbyId]['users'].values(): #gets all user objects
		user['socket'].sendall(json.dumps(resData))

def notifyEveryoneExcept(lobbies, lobbyId, status, data, exceptUserSid):
	resData = {}
	resData['status'] = status
	if data != None:
		resData['data'] = data
	for user in lobbies[lobbyId]['users'].values(): #gets all user objects
		if(user['sid']) != exceptUserSid:
			user['socket'].sendall(json.dumps(resData))

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
			users.append({'userSid':usr['sid'], 'username':User.getUsername(usr['sid'])})
		lobby = {'id' : lob['id'], 'name': lob['name'], 'users': users} #todo names?
		lobbiesForFront.append(lobby)
	return lobbiesForFront

def getMyLobbyData(lobbies, lobbyId): #TODO
	users = []
	#get user names
	for usr in lobbies[lobbyId]['users']:
		users.append(usr[1])
	lob = {'id' : lobbies[lobbyId]['id'], 'name': lobbies[lobbyId]['name'], 'users': users}
	return lob

def startGame(lobbies, lobbyId):
	while True:
		time.sleep(3)
		print "Game logic goes here"