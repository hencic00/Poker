RUPS projekt - Poker

Communication JSON format:

# Basic requests #

**"login"**:
- to server:  
  - {agenda="login", email="jan.jurman@student.um.si", password="geslo123"}  
- from server:
  - {agenda="login", userId: "c4e687b4-60af-42f4-bc51-0e9962878e03", username="whatever", status="ok"}  
  - {agenda="login", status="nonExistentUser"}  
  - {agenda="login", status="allreadyLoggedIn"}  
  - {agenda="login", status="wrongPassword"}  

**"logout"**:
- to server:  
  - {"userId": "c4e687b4-60af-42f4-bc51-0e9962878e03", "agenda": "logout"}  
- from server:
  - {agenda="logout", status="ok"}
  - {agenda="logout", status="notLoggedIn"}  

**"register"**:
- to server:
  - {agenda="register", username="jan", email="jan.jurman@student.um.si" password="geslo123"}  
- from server:  
  - {agenda="register", status:"ok"}  
  - {agenda="register", status:"usernameTaken"}  
  
**"getLobbies"**:
- to server:  
  - {agenda="getLobbies"}  
- from server:	
  - {agenda="getLobbies", data=[[{'users': [{'userSid': 5, 'username': 'asd'}], 'name': 'LOBBYNAME', 'id': '22d98e1c-7ac9-4a5b-9179-df17b0750387'},...]}  

**"joinLobby"**:
- to server:  
  - {"agenda": "joinLobby", "lobbyId": "22d98e1c-7ac9-4a5b-9179-df17b0750387", "userId": "1b4b3cd7-97e7-4525-8295-c3558881f8e5"}  
- from server:	
  - {'status': 'ok', 'data': {'users': [{'userSid': 5, 'username': 'asd'}, {'userSid': 6, 'username': 'w'}], 'name': 'LOBBYNAME', 'id': '22d98e1c-7ac9-4a5b-9179-df17b0750387'}, 'agenda': 'joinLobby'}
  - {'status': 'lobbyNotFound', 'agenda': 'joinLobby'}  
  
**"createLobby"**:
- to server:  
  - {lobbyName": "LOBBYNAME", "userId": "4614d4c0-1aba-4a7a-b579-a17d6c5840f1", "agenda": "createLobby"}  
- from server:	
  - {'status': 'ok', 'data': {'users': [{'userSid': 5, 'username': 'asd'}], 'name': 'LOBBYNAME', 'id': '86ed400e-7440-44cd-aa1c-749f7c2bd26d'}, 'agenda': 'createLobby'}
  
 # Inside a lobby #

**"playerJoined"**:
- from server:	
  - {"data": {"userSid": 6, "username": "w"}, "agenda": "playerJoined"}

**"playerLeft"**:
- from server:	
  - {"data": {"userSid": 5, "username": "asd"}, "agenda": "playerLeft"}  

**"leaveLobby"**:
- to server:	
  - {"agenda": "leaveLobby"}
- from server:	
  - {"status": "ok", "agenda": "leaveLobby"}
  
**"gameStart"**:
- from server:	
  - {"status": "ok", "data": ["9h", "Ad"], "agenda": "gameStart"} //data je tvoj hand
  
 # Inside a game #
 
 **"blinds"**:
- from server:	
  - {"data": [5, 6, 5], "agenda": "BSblind"}  //[small, big, minBet]  

 **"yourTurn"**:
- from server:	
  - {"agenda": "yourTurn"}  

 **"playerRaise"**:
- to server:	
  - {"data": "12", "agenda": "raise"}
 - from server:  
  - {'data': [5, 12], 'agenda': 'playerRaise'} //[playerSid, amount] //isto če drugi player raisa (brez to server)
 
  **"playerCheck"**:
- to server:	
  - {"agenda": "check"}
 - from server:  
  - {"data": 6, "agenda": "playerCheck"}  // isto kot pri raise

  **"playerFold"**:
- to server:	
  - {"agenda": "fold"}
 - from server:  
  - {"data": 5, "agenda": "playerFold"}  // isto kot pri raise

**"cardReveal"**:
- from server:	
  - {"data": ["4c", "Qh", "7d"], "agenda": "cardReveal"}  //prvic
  - {"data": ["Jh"], "agenda": "cardReveal"} //naslednjih 2x

**"playerWon"**
- from server:
  - {needs finishing touches}

# Other # 
 
**"whatTheFuckUndefined"**
- to server:  
  - {????}
- from server:  
  - {agenda="isti kot si ga poslal", status:"badRequest"}
