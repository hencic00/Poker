import mysqlService

def getGame(gameId):
	cur,con = mysqlService.connect()
	cur.execute("SELECT * FROM game WHERE id = '{}'".format(gameId))
	rows = cur.fetchall()

	cur.close()
	con.close()
	if len(rows) == 0:
		return 0
	else:
		return rows[0]

def insertGame():
	cur,con = mysqlService.connect()
	cur.execute("INSERT INTO game (time) VALUES (now())")
	con.commit()
	lastInsertId = cur.lastrowid
	cur.close()
	con.close()
	return lastInsertId

def insertUserGame(userId, gameId, score):
	cur,con = mysqlService.connect()
	cur.execute("INSERT INTO user_game (tk_user, tk_game, score) VALUES ('{}','{}','{}')".format(userId, gameId, score))
	con.commit()
	lastInsertId = cur.lastrowid
	cur.close()
	con.close()
	return lastInsertId

def getUserGames(userId):
	cur,con = mysqlService.connect()
	cur.execute("SELECT * FROM user_game WHERE tk_user = '{}'".format(userId))
	rows = cur.fetchall()

	cur.close()
	con.close()
	if len(rows) == 0:
		return 0
	else:
		return rows

def insertPostGameData():
	createdGame = insertGame()
	#TODO
