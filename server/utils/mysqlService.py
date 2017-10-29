import mysql.connector

def connect():
	con = mysql.connector.connect(user='poker',
							  passwd='geslo123',
                              host='localhost',
                              db='Poker',
                              port='3306')
	cur = con.cursor()
	return cur,con;