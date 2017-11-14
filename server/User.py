import mysqlService

def getUser(email):
	cur,con = mysqlService.connect()
	cur.execute("SELECT * FROM user WHERE email = '{}'".format(email))
	rows = cur.fetchall()

	cur.close()
	con.close()
	if len(rows) == 0:
		return 0
	else:
		return rows[0]

def getUsername(userSid):
	cur,con = mysqlService.connect()
	cur.execute("SELECT username FROM user WHERE id = '{}'".format(userSid))
	rows = cur.fetchall()

	cur.close()
	con.close()
	if len(rows) == 0:
		return "ERROR"
	else:
		return rows[0][0]

def login(email, password):
	cur,con = mysqlService.connect()
	cur.execute("SELECT * FROM user WHERE email = '{}' AND password = '{}'".format(email, password))
	#print("SELECT * FROM user WHERE email = '{}' AND password = '{}'".format(email, password))
	rows = cur.fetchall()
	retval = None
	if len(rows) == 0:
		cur.close()
		con.close()	
		return 0
	else:
		cur.execute("UPDATE user SET last_login = NOW() WHERE user.email = '{}'".format(email))
		con.commit()
		cur.close()
		con.close()
		return rows[0][0] #cant access by key, god help us all


def register(username, email, password):
	user = getUser(email)
	if user != 0:
		return 0 #user allready taken
	cur,con = mysqlService.connect()
	cur.execute("INSERT INTO user (username, email, password) VALUES ('{}','{}', '{}')".format(username, email, password))
	#print("INSERT INTO user (email, password) VALUES ('{}', '{}')".format(email, password))
	con.commit()
	lastInsertId = cur.lastrowid
	cur.close()
	con.close()
	return lastInsertId