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
	
def getAllInactiveUsers():
	cur,con = mysqlService.connect()
	cur.execute("SELECT * FROM user where DATE_SUB(now(),interval 1 month) >= user.last_login")
	results = cur.fetchall()
	cur.close()
	con.close()
	if len(results) == 0:
		return 0
	else:
		return results

#get user average lifetime score
def getUserAvgScore(userId):
	cur,con = mysqlService.connect()
	cur.execute("SELECT AVG(ug.score) as userAvgScore FROM user_game as ug WHERE tk_user = '{}'".format(userId))
	rows = cur.fetchall()

	cur.close()
	con.close()
	if len(rows) == 0:
		return 0
	else:
		return rows[0]

#get user average score for last month
def getUserAvgMonthlyScore(userId):
	cur,con = mysqlService.connect()
	cur.execute("""SELECT u.score FROM user as u
	INNER JOIN user_game as ug on ug.tk_user = u.id
	INNER JOIN game as g on ug.tk_game = g.id
	AND g.time < DATE_SUB(now(),interval 1 month)
	WHERE u.id = '{}'
	ORDER BY g.time;""".format(userId))
	rows = cur.fetchall()

	cur.close()
	con.close()
	if len(rows) == 0:
		return 0
	else:
		return rows[0]