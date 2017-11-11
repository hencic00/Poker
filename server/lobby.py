def createLobby(socket, lobbies, user):
	#create lobby object
	import uuid
	lobby = {'id': str(uuid.uuid4()), 'name': "myLobby", 'users': [user]}
	print("Created lobby {}".format(lobby['id']))


	#append it to the lobby list

	lobbies.append(lobby)

	#wait for user to start game

def joinLobby(lobbies, lobbyId, user):
	pass

def leaveLobby(lobbies, lobbyId, user):
	pass

def getAllLobbiesForFront(lobbies):
	pass
	#id, ime lobbija, idji od uporabnikov