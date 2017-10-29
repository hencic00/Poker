import mysql.connector

def connect():
	cnx = mysql.connector.connect(user='poker', password='geslo123',
                              host='127.0.0.1',
                              database='poker',
                              port='3306')
	db = cnx.cursor()
	return db,cnx;