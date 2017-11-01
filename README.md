RUPS projekt - Poker

Communication JSON format:

**"login"**:
- to server:  
  - {agenda="login", username="jan", password="geslo123"}  
- from server:
  - {agenda="login", status="ok"}  
  - {agenda="login", status="wrongPassword"}  

**"register"**:
- to server:
  - {agenda="register", username="jan", password="geslo123"}
- from server:  
  - {agenda="register", status:"ok"}
  - {agenda="register", status:"usernameTaken"}  
  
**"getLobbies"**:
- server:  
  - {agenda="getLobbies"}
- from server:	
  - {agenda="getLobbies", data="TBD"}

**"whatTheFuckUndefined"**:
- to server:  
  - {????}
- from server:  
  - {agenda="isti kot si ga poslal", status:"badRequest"}
