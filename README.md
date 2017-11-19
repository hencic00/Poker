RUPS projekt - Poker

Communication JSON format:

**"login"**:
- to server:  
  - {agenda="login", email="jan.jurman@student.um.si", password="geslo123"}  
- from server:
  - {agenda="login", userId: "c4e687b4-60af-42f4-bc51-0e9962878e03", status="ok"}  
  - {agenda="login", status="nonExistentUser"}  
  - {agenda="login", status="allreadyLoggedIn"}  
  - {agenda="login", status="wrongPassword"}  

**"logout"**:
- to server:  
  - {"userId": "c4e687b4-60af-42f4-bc51-0e9962878e03", "agenda": "getLobbies"}  
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
  
**"whatTheFuckUndefined"**
- to server:  
  - {????}
- from server:  
  - {agenda="isti kot si ga poslal", status:"badRequest"}
