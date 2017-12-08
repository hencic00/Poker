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
		return rows[0]

def getLastUserGames5(userId):
	cur,con = mysqlService.connect()
	cur.execute("SELECT * FROM user_game as ug WHERE tk_user = '{}' ORDER BY ug.id LIMIT 5".format(userId))
	rows = cur.fetchall()

	cur.close()
	con.close()
	if len(rows) == 0:
		return 0
	else:
		return rows[0]


def getUserLastGoodGames3(userId):
	cur,con = mysqlService.connect()
	cur.execute("""SELECT ug.tk_game as gameId, ug.score, g.time FROM user as u
	INNER JOIN user_game as ug on ug.tk_user = u.id
	AND ug.score > 1000
	INNER JOIN game as g on ug.tk_game = g.id
	WHERE u.id = '{}'
	ORDER BY g.time
	LIMIT 5;""".format(userId))
	rows = cur.fetchall()

	cur.close()
	con.close()
	if len(rows) == 0:
		return 0
	else:
		return rows[0]

def getUserLastBadGames3(userId):
	cur,con = mysqlService.connect()
	cur.execute("""SELECT ug.tk_game as gameId, ug.score, g.time FROM user as u
	INNER JOIN user_game as ug on ug.tk_user = u.id
	AND ug.score < 200
	INNER JOIN game as g on ug.tk_game = g.id
	WHERE u.id = '{}'
	ORDER BY g.time
	LIMIT 5;""".format(userId))
	rows = cur.fetchall()

	cur.close()
	con.close()
	if len(rows) == 0:
		return 0
	else:
		return rows[0]

def checkUserWinstreak(userId):
	cur,con = mysqlService.connect()
	cur.execute("""SELECT AVG(ug.score) as avgScore FROM user as u
	INNER JOIN user_game as ug on ug.tk_user = u.id
	INNER JOIN game as g on ug.tk_game = g.id
	WHERE u.id = '{}'
	ORDER BY g.time
	LIMIT 3;""".format(userId))
	rows = cur.fetchall()

	cur.close()
	con.close()
	if len(rows) == 0:
		return 0
	else:
		if rows[0][0] > 1000:
			return 1
		else:
			return -1

def insertPostGameData(endGameUsers):
	createdGame = insertGame()
	for usr in endGameUsers:
		insertUserGame(usr.id, createdGame, usr.score)
