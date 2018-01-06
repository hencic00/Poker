import random
from deuces import Deck #pip install deuces
from deuces import Evaluator
from deuces import Card
import math
evaluator = Evaluator()
import comms
import User

class Player:
	def __init__(self, moneyInit, user):
		#self.id = idInit
		self.hand = []
		self.money = moneyInit
		self.currentBet = 0
		self.allIn=False
		self.allInDifference=0
		self.id = user['sid']
		self.socket = user['socket']
		self.score = 0

	def setMoney(self, moneyAmmount):
			self.money=moneyAmmount

	def addCard(self, card):
			self.hand.append(card)

	def placeBet(self, roundObject, ammount): #DONE(test): ce ti dnara sfali
		if(ammount <= 0):
			return False
		else:
			if(self.money<=0 or ammount>self.money):
				print("The ammount you wish to bet is larger than what you have-going all in!")
				roundObject.pot += self.money
				self.currentBet += self.money
				self.allIn=True
				self.allInDifference=(ammount-self.money)
				self.money=0
			else:
				self.money -= (ammount - self.currentBet)
				roundObject.pot += (ammount - self.currentBet)
				self.currentBet = ammount
			return self.currentBet#True

	def returnMoney(self, ammount):	#return money in case of pot splitting; the minimum all in bet is used for mainPot, the second min bet is used for side pot, the 'overbet' of the other players is returned
		self.money+=ammount
