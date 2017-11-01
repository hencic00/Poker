import mysqlService

def getUser(username):
	cur,con = mysqlService.connect()
	cur.execute("SELECT * FROM user WHERE username = '{}'".format(username))
	rows = cur.fetchall()
	if len(rows) == 0:
		return 0
	else:
		return rows[0]
	cur.close()
	con.close()

def login(username, password):
	cur,con = mysqlService.connect()
	cur.execute("SELECT * FROM user WHERE username = '{}' AND password = '{}'".format(username, password))
	#print("SELECT * FROM user WHERE username = '{}' AND password = '{}'".format(username, password))
	rows = cur.fetchall()
	if len(rows) == 0:
		return 0
	else:
		return 1
	cur.close()
	con.close()

def register(username, password):
	user = getUser(username)
	if user != 0:
		return 0 #user allready taken
	cur,con = mysqlService.connect()
	cur.execute("INSERT INTO user (username, password) VALUES ('{}', '{}')".format(username, password))
	#print("INSERT INTO user (username, password) VALUES ('{}', '{}')".format(username, password))
	con.commit()	
	cur.close()
	con.close()