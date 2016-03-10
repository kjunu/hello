#!/usr/bin/python

import MySQLdb

from MySQLdb.constants import ER

class mariaDBops:
	DB_ip = ""
	DB_id = ""
	DB_pwd = ""
	DB = ""
	table = ""
	
	sql = "INSERT INTO "+DB+"."+table+" (imgurl, linkurl, price) VALUES (%s,%s,%s)"
	def __init__(self):
		self.db = MySQLdb.connect(self.DB_ip, self.DB_id, self.DB_pwd, self.DB)
		self.cursor = self.db.cursor()
		self.cursor.execute("SELECT VERSION()")
		data = self.cursor.fetchone()
		print "Database version : %s " % data

	def __del__(self):
		self.db.close()
		
	def add_item(self, link_url, img_url, price):
		try:
			self.cursor.execute(self.sql, (img_url, link_url, price))
			#TODO: commit every time?
			self.db.commit()
		except MySQLdb.Error as e:
			try:
				if e.args[0] is not ER.DUP_ENTRY:
					print "DB error : "+str(e)
					self.db.rollback()
			except Exception as e:
				print "Exception : "+str(e)
		
		except Exception as e:
			print "System Exception : "+str(e)
			self.db.rollback()
