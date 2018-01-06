import random
from deuces import Deck #pip install deuces
from deuces import Evaluator
from deuces import Card
import math
evaluator = Evaluator()
import comms
import User
from Round import Round
from Player import Player

class Game:
	def __init__(self, lobby, minBetInit, startingCash, minRaiseInit):
		self.lobby = lobby
		self.startingCash = startingCash;
		self.roundObject = None
		self.cardRankLUT = dict()
		self.cardRankLUT = {
			0  : '2',
			1  : '3',
			2  : '4',
			3  : '5',
			4  : '6',
			5  : '7',
			6  : '8',
			7  : '9',
			9  : 'J',
			8  : 'T',
			10 : 'Q',
			11 : 'K',
			12 : 'A'
		}

		self.cardSuitLUT = dict()
		self.cardSuitLUT = {
			1 : 's',
			2 : 'h',
			4 : 'd',
			8 : 'c'
		}

		self.roundCounter = 0
		self.players = []
		self.endGameUsers = []
		
		self.unshuffledDeck = Deck()
		self.currentPlayerIndex = 0
		self.minBet = minBetInit
		self.minRaise=minRaiseInit

		#za vsakega lobby usera naredi playera

	def startGame(self):
		data = {}
		data['agenda'] = "gameStart"
		data['data'] = {'players':[], 'startingCash':[]}
		for user in self.lobby['users'].values():
			self.addPlayer(Player(self.startingCash, user))
			#add user to data object for sending of initial players
			data['data']['players'].append({
				'playerSid': user['sid'],
				'username': User.getUsername(user['sid'])
			})

		comms.broadcastToPlayers(self.players, data)
		result=self.startNewRound()
		if(result==False):
			for x in range(len(self.players)-1, -1, -1):
				self.removePlayerFromGame(x)
		#endGameUsers se dodaja ko nekdo zapusti igro ali zmaga
		return self.endGameUsers

	def convertNotation(self, rank, suit):
		return self.cardRankLUT[rank] + self.cardSuitLUT[suit]

	def addPlayer(self, player):
		self.players.append(player)

	def startNewRound(self):
		if(len(self.players) > 1):
			self.roundObject=Round(self)
			while(True):
				if(len(self.players) > 1):	#check if players in game are more than 1; sam pac ne mors spilat, duh
					print("REMOVING PLAYERS WITHOUT MONEY")
					self.removePlayersWithNoMoney()
					print("ROUND " + str(self.roundCounter) + " START")
					result=self.roundObject.startRound(self)
					if(result==False):
						return False
					self.roundObject.reset(self)
				else:
					return False
		else:
			return False

	def removePlayersWithNoMoney(self):
		for x in range(len(self.players)-1, -1, -1):
			if(self.players[x].money<=0):
				self.removePlayerFromGame(x)

	def removePlayerFromGame(self, playerIndex):
		#close the socket conn
		self.players[playerIndex].socket.close()
		#remove player from lobby
		del self.lobby['users'][self.players[playerIndex].id]
		#cleanup
		removedPlayer = self.players.pop(playerIndex)
		#self.playerStatus.pop(playerIndex)
		#DONE(test) set user score, za lazji insert into DB pol. kucer pls
		removedPlayer.score=removedPlayer.money-self.startingCash

		self.endGameUsers.append(removedPlayer);


#Deuces card representation
#{'2': 0, '3': 1, '4': 2, '5': 3, '6': 4, '7': 5, '8': 6, '9': 7, 'A': 12, 'J': 9, 'K': 11, 'Q': 10, 'T': 8}
#{'c': 8, 'd': 4, 'h': 2, 's': 1}

#Poker round phases
	#Preflop - The round of betting that takes place after the hole cards have been dealt, but before the flop has been dealt.
	#Flop - After the preflop, three community cards are dealt face-up on the board for everyone to share and use as part of their hands.  After the three cards are dealt, a round of betting ensues.
	#Turn - After the flop, another face-up card is added to the board, and another round of betting ensues. This round is called the turn.
	#River - After the turn, a final card face-up is added to the board, and a final round of betting ensues.  This round is called the river.  

#Poker hands
	#Royal Flush - 10 to ace all same suit; all suits ranked equally
	#Straight Flush - Any streight with all 5 cards same suit; all suits ranked equally; higher streight wins, if the same split the pot example (10,J,Q,K,A > 9,10,J,Q,K); streight can't wrap around (J,Q,K,A,2)=>not a streight
	#Four of a Kind - 4 cards the same example: (6,J,J,J,J); if 2 or more players have 4 of a kind, the kicker (5th card) decides the winner
	#Full House - 3 cards of the same rank + 2 cards of the same rank; if 2 players have a Full House, the player with the higher value tripple wins
	#Flush - 5 cards of the same suit, non-consecutive; highest card determines the rank example: (AceH, 10H, 9H, 6H, 2H) > (KingH, 10H, 9H, 6H, 2H); if more players have the same rank Flush, split the pot
	#Straight - 5 consecutive cards of different suits, Aces can count as a high or low card; (A,2,3,4,5) lowest possible streight; if more players share the same rank streight, split the pot
	#3 of a Kind - 3 cards of the same rank; (A,A,A,K,Q) - best possible streight; if more players share the same 3 of a Kind, the rank is decided by the remaining 2 cards; if the rank is the same, split the pot
	#2 Pair - any rank Pair + any rank Pair; The rank is determined by the highest pair; if more players have the same 2 pair the kicker (5th card) determines the winner; (A,A,K,K,Q) best possible 2 Pair
	#Pair - any 2 cards of the same rank; (A,A,K,Q,J)-best possible pair
	#High Card - Any hand of not above meantioned; (A,K,Q,J,9) best possible high card    