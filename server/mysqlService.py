import mysql.connector

def connect():
	con = mysql.connector.connect(user='poker',
								password='geslo123',
								host='127.0.0.1',
								database='poker',
								port='3306')
	cur = con.cursor()
	return cur,con;