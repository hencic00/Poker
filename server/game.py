import random
from deuces import Deck #pip install deuces
from deuces import Evaluator
from deuces import Card
evaluator = Evaluator()
import comms

class Game:
	def __init__(self, lobby, minBetInit):
		self.lobby = lobby

		self.cardRankLUT = dict()
		self.cardRankLUT = {
			0 : '2',
			1 : '3',
			2 : '4',
			3 : '5',
			4 : '6',
			5 : '7',
			6 : '8',
			7 : '9',
			8 : 'T',
			9 : 'J',
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
		
		self.unshuffledDeck = Deck()
		self.currentPlayerIndex = 0
		self.minBet = minBetInit

		#TODO: SQL money
		#TODO: variabilni money input?
		#za vsakega lobby usera naredi playera
		for user in lobby['users'].values():
			self.addPlayer(Player(1000, user))
		self.startNewRound()

	def startGame(self):
		self.startNewRound()
		return "GAME END MAGIC"

	def convertNotation(self, rank, suit):
		return self.cardRankLUT[rank] + self.cardSuitLUT[suit]

	def addPlayer(self, player):
		self.players.append(player)

	def removePlayer(self, playerId):   #odstranitev igralca iz liste igre/lobbija
		for i in range(0, len(self.players)):
			if self.players.getPlayerId() == playerId:
				self.players.pop(i)
				return True
			return False

	def startNewRound(self): #"Kucerov TODO: po pointerah se prenasa vse. Nisem jaz noter v roundu tu pokvaril cesa?"
		roundObject = None
		if(len(self.players) > 1):
			roundObject = Round(self)
			roundObject.reset(self)
			roundObject.startRound(self)
			self.startNewRound()
		else:
			return False

class Round:
	def __init__(self, gameObject):
		self.pot = 0
		self.currentMinBet = gameObject.minBet
		self.roundPlayers = gameObject.players
		self.playerStatus = []
		self.playerHandScores = []
		self.playerHandClasses = []
		self.board = []
		self.deck = gameObject.unshuffledDeck
		#self.deck = random.sample(gameObject.unshuffledDeck, 52)    #deck shuffle -> uporablja Fisher-Yates O(n)
	 
		for p in self.roundPlayers: #empty player hands
			p.hand = []

	def reset(self, gameObject):
		self.pot = 0
		self.currentMinBet = gameObject.minBet
		self.roundPlayers = gameObject.players
		self.playerStatus = []
		self.playerHandScores = []
		self.playerHandClasses = []
		self.board = []
		self.deck = Deck()
		#self.deck = random.sample(gameObject.unshuffledDeck, 52)    #deck shuffle -> uporablja Fisher-Yates O(n)
	 
		for p in self.roundPlayers: #empty player hands
			p.hand = []
		
	def bettingPhase(self, gameObject, startPlayerIndex):
		playerCount=len(self.roundPlayers)
		currentPI=startPlayerIndex
		for p in range(0, playerCount):   #init. playerStatus array-all to false, except those who folded (set to None)
			if(self.playerStatus[p]!=None):
				self.playerStatus[p]=False
		# while(True):
		# 	if(self.countActivePlayers(playerCount)==1):    #check if more than 1 player is still active (un-folded)
		# 		return False
		# 	if(self.playerStatus[currentPI]==None): #skip player that folded
		# 		currentPI=self.nextPlayer(currentPI, playerCount)
		# 	else:
		# 		print("Current min. bet: " + str(self.currentMinBet) + "\r\nCurrent pot: " + str(self.pot))
		# 		if(self.checkArray(self.playerStatus)):
		# 			break
		# 		print(" Player "+str(currentPI))
		# 		action = input(" Your current bet: " + str(self.roundPlayers[currentPI].currentBet) + " \r\nSelect action: R-Raise, C-Check, F-Fold\r\n")
		# 		if(action=="C"):
		# 			self.roundPlayers[currentPI].placeBet(self, self.currentMinBet)
		# 			self.playerStatus[currentPI]=True
		# 			currentPI=self.nextPlayer(currentPI, playerCount)
		# 		elif(action=="R"):
		# 			inputRaise = input("Current min. bet: " + str(self.currentMinBet) + " How much do you want to raise?\r\n")
		# 			self.roundPlayers[currentPI].placeBet(self, self.currentMinBet + inputRaise)
		# 			self.playerStatus[currentPI]=True
		# 			self.resetPlayerStatusAfterRaise(currentPI)
		# 			self.currentMinBet+=inputRaise
		# 			currentPI=self.nextPlayer(currentPI, playerCount)
		# 		elif(action=="F"):
		# 			self.playerStatus[currentPI]=None
		# 			currentPI=self.nextPlayer(currentPI, playerCount)
		while(True):
			if(self.countActivePlayers(playerCount)==1):    #check if more than 1 player is still active (un-folded)
				return False
			if(self.playerStatus[currentPI]==None): #skip player that folded
				currentPI=self.nextPlayer(currentPI, playerCount)
			else:
				print("Current min. bet: " + str(self.currentMinBet) + "\r\nCurrent pot: " + str(self.pot))
				if(self.checkArray(self.playerStatus)):
					break
				print(" Player "+str(currentPI))
				#action = input(" Your current bet: " + str(self.roundPlayers[currentPI].currentBet) + " \r\nSelect action: R-Raise, C-Check, F-Fold\r\n")
				#tell the player its his turn
				data = {}
				data['agenda'] = "yourTurn"
				#TODO check for bad input
				print("Sending yourTurn to {}".format(gameObject.players[currentPI].id))
				comms.send(gameObject.players[currentPI].socket, data)

				rec = comms.receive(gameObject.players[currentPI].socket) #todo timeout?
				action = rec['agenda']
				if(action=="check"):
					self.roundPlayers[currentPI].placeBet(self, self.currentMinBet)
					self.playerStatus[currentPI]=True

					data = {}
					data['agenda'] = "playerCheck"
					data['data'] = gameObject.players[currentPI].id #player ki je raisal: SID
					comms.broadcastToPlayers(gameObject.players, data)

					currentPI=self.nextPlayer(currentPI, playerCount)
				elif(action=="raise"):
					#TODO check da raisa vec kot je min SERVER SIDE
					#inputRaise = input("Current min. bet: " + str(self.currentMinBet) + " How much do you want to raise?\r\n")
					inputRaise = int(rec['data'])
					self.roundPlayers[currentPI].placeBet(self, self.currentMinBet + inputRaise)
					self.playerStatus[currentPI]=True
					self.resetPlayerStatusAfterRaise(currentPI)
					self.currentMinBet+=inputRaise

					print("RAISE: {}".format(inputRaise))
					#notify everyone player raised
					data = {}
					data['agenda'] = "playerRaise"
					data['data'] = [gameObject.players[currentPI].id, inputRaise] #player ki je raisal: SID, stevilo
					comms.broadcastToPlayers(gameObject.players, data)

					currentPI=self.nextPlayer(currentPI, playerCount)
				elif(action=="fold"):
					self.playerStatus[currentPI]=None
					
					data = {}
					data['agenda'] = "playerFold"
					data['data'] = gameObject.players[currentPI].id #player ki je raisal: SID
					comms.broadcastToPlayers(gameObject.players, data)

					currentPI=self.nextPlayer(currentPI, playerCount)
		return True

	def preflopPhase(self, gameObject, startPlayerIndex):
		playerCount=len(self.roundPlayers)
		currentPI=startPlayerIndex
		for p in range(0, playerCount):   #init. playerStatus array-all to false
			self.playerStatus.append(False)
		#small blind
		smallPI = currentPI
		self.roundPlayers[currentPI].placeBet(self, self.currentMinBet/2)
		currentPI=self.nextPlayer(currentPI, playerCount)

		#big blind
		bigPI = currentPI
		self.roundPlayers[currentPI].placeBet(self, self.currentMinBet)
		self.playerStatus[currentPI]=True
		currentPI=self.nextPlayer(currentPI, playerCount)		
		#broadcast: smallblind from player
		data = {}
		data['agenda'] = "BSblind" #prvi bo small, drugi bo big
		data['data'] = [gameObject.players[smallPI].id, gameObject.players[bigPI].id, gameObject.minBet]
		comms.broadcastToPlayers(self.roundPlayers, data)

		while(True):
			if(self.countActivePlayers(playerCount)==1):    #check if more than 1 player is still active (un-folded)
				return False
			if(self.playerStatus[currentPI]==None): #skip player that folded
				currentPI=self.nextPlayer(currentPI, playerCount)
			else:
				print("Current min. bet: " + str(self.currentMinBet) + "\r\nCurrent pot: " + str(self.pot))
				if(self.checkArray(self.playerStatus)):
					break
				print(" Player "+str(currentPI))
				#action = input(" Your current bet: " + str(self.roundPlayers[currentPI].currentBet) + " \r\nSelect action: R-Raise, C-Check, F-Fold\r\n")
				#tell the player its his turn
				data = {}
				data['agenda'] = "yourTurn"
				#TODO check for bad input
				comms.send(gameObject.players[currentPI].socket, data)

				rec = comms.receive(gameObject.players[currentPI].socket) #todo timeout?
				action = rec['agenda']
				if(action=="check"):
					self.roundPlayers[currentPI].placeBet(self, self.currentMinBet)
					self.playerStatus[currentPI]=True

					data = {}
					data['agenda'] = "playerCheck"
					data['data'] = gameObject.players[currentPI].id #player ki je raisal: SID
					comms.broadcastToPlayers(gameObject.players, data)

					currentPI=self.nextPlayer(currentPI, playerCount)
				elif(action=="raise"):
					#TODO check da raisa vec kot je min SERVER SIDE
					#inputRaise = input("Current min. bet: " + str(self.currentMinBet) + " How much do you want to raise?\r\n")
					inputRaise = int(rec['data'])
					self.roundPlayers[currentPI].placeBet(self, self.currentMinBet + inputRaise)
					self.playerStatus[currentPI]=True
					self.resetPlayerStatusAfterRaise(currentPI)
					self.currentMinBet+=inputRaise

					print("RAISE: {}".format(inputRaise))
					#notify everyone player raised
					data = {}
					data['agenda'] = "playerRaise"
					data['data'] = [gameObject.players[currentPI].id, inputRaise] #player ki je raisal: SID, stevilo
					comms.broadcastToPlayers(gameObject.players, data)

					currentPI=self.nextPlayer(currentPI, playerCount)
				elif(action=="fold"):
					self.playerStatus[currentPI]=None
					
					data = {}
					data['agenda'] = "playerFold"
					data['data'] = gameObject.players[currentPI].id #player ki je raisal: SID
					comms.broadcastToPlayers(gameObject.players, data)

					currentPI=self.nextPlayer(currentPI, playerCount)
		return True

	def checkArray(self, array):
		for a in array:
			if(a == False):
				return False
		return True

	def resetPlayerStatusAfterRaise(self, currentPI):
		for i in range(0, len(self.playerStatus)):
			if(i != currentPI and self.playerStatus[i] != None):
				self.playerStatus[i] = False               
				   
	def nextPlayer(self, currentPI, playerCount):
		currentPI += 1
		if(currentPI >= playerCount):
			currentPI = 0
		return currentPI  
	
	def countActivePlayers(self, playerCount):
		counter = 0
		for i in range(playerCount):
			if(self.playerStatus[i]!=None):
				counter += 1
		return counter

	def endRound(self, gameObject, winners):
		data = {}
		data['agenda'] = "playerWon"
		data['data'] = {'winnerSid': [], 'earnings': [], 'playerSid':[], 'playerHands':[], 'currentCash':[]}

		if(len(winners)==1):
			#only 1 winner
			gameObject.players[winners[0]].money+=self.pot
			print("Player " + str(winners[0]) + " WON (others Folded)")
			data['playerSid'] = gameObject.players[winners[0]]	#front checks len(data['playerSid'])
			data['earnings'] = self.pot
		else:
			#split the pot
			potSplit=self.pot / len(winners)
			print("Pot split between: ")
			for p in winners:
				gameObject.players[winnerIndex].money+=potSplit
				print("Player " + str(winners[0]) + " ")
				data['playerSid'].append(gameObject.players[p])
				data['earnings'].append(potSplit)	#TODO edge cases kot so all in pa premalo dnara
		
		for player in gameObject.players:
			data['data']['playerSid'].append(player.id)
			data['data']['playerHands'].append(player.hand)
			data['data']['currentCash'].append(player.money)
		comms.broadcastToPlayers(gameObject.players, data);

		gameObject.roundCounter+=1
		print("\r\n\r\n")

	def getLastPlayer(self):
		for i in range(len(self.roundPlayers)):
			if(self.playerStatus[i] is not None):
				return i
		return False

	def getWinnerIndexes(self):
		playerCounter=len(self.playerHandScores)
		winnerIndexes = []
		scoresWithStatusNone=[]
		best=max(self.playerHandScores)
		for j in range(playerCounter):
			if(self.playerStatus[j]==None):
				scoresWithStatusNone.append(None)
			else:
				if(best>self.playerHandScores[j]):
					best=self.playerHandScores[j]
				scoresWithStatusNone.append(self.playerHandScores[j])
		for i in range(playerCounter):
			if(scoresWithStatusNone[i]!=None and scoresWithStatusNone[i]<=best):
				winnerIndexes.append(i)
		return winnerIndexes
				
	def startRound(self, gameObject):
		playerCount = len(self.roundPlayers)
		if(playerCount <= 1): #check if there are more than 1 players in round
			return False #TODO implementiraj ce ni nobenega ker so leavali
		
		#deal initial hands
		for i in range(2):
			for player in self.roundPlayers:
				player.hand.append(self.deck.draw(1))
		#game start & initial cards
		for player in self.roundPlayers:
			data = {}
			data['agenda'] = "gameStart"
			data['status'] = "ok"
			currentHand = player.hand
			data['data'] = [
				gameObject.convertNotation(Card.get_rank_int(currentHand[0]), Card.get_suit_int(currentHand[0])),
				gameObject.convertNotation(Card.get_rank_int(currentHand[1]), Card.get_suit_int(currentHand[1]))
			]
			comms.send(player.socket, data);

		#Preflop phase
		print("--Preflop--")
		result = self.preflopPhase(gameObject, (gameObject.roundCounter % len(self.roundPlayers)))  #TUSNOSTAL
		#check if all but 1 folded else go to next phase      
		if(not result): #only 1 player remains active; end game
			lastPlayerIndex=self.getLastPlayer()
			if(lastPlayerIndex is not False):
				self.endRound(gameObject, [lastPlayerIndex])
				return True   
			else:
				return False         
		#Flop phase
		print("--Flop--")
		self.board=self.deck.draw(3)    #3 cards to board
		self.revealCards(gameObject, self.board)
		result=self.bettingPhase(gameObject, (gameObject.roundCounter % len(self.roundPlayers)))
		#check if all but 1 folded else go to next phase
		if(not result): #only 1 player remains active; end game
			lastPlayerIndex=self.getLastPlayer()
			if(lastPlayerIndex is not False):
				self.endRound(gameObject, [lastPlayerIndex])
				return True   
			else:
				return False
		#Turn phase
		print("--Turn--")
		drawnCard = self.deck.draw(1)
		self.revealCards(gameObject, [drawnCard])
		self.board.append(drawnCard)
		result=self.bettingPhase(gameObject, (gameObject.roundCounter % len(self.roundPlayers)))
		#check if all but 1 folded else go to next phase
		if(not result): #only 1 player remains active; end game
			lastPlayerIndex=self.getLastPlayer()
			if(lastPlayerIndex is not False):
				self.endRound(gameObject, [lastPlayerIndex])
				return True   
			else:
				return False
		#River phase
		print("--River--")
		drawnCard = self.deck.draw(1)
		self.revealCards(gameObject, [drawnCard])
		self.board.append(drawnCard)
		result=self.bettingPhase(gameObject, (gameObject.roundCounter % len(self.roundPlayers)))
		#end hand comparison
		if(not result): #only 1 player remains active; end game
			lastPlayerIndex=self.getLastPlayer()
			if(lastPlayerIndex is not False):
				self.endRound(gameObject, [lastPlayerIndex])
				return True
			else:
				return False
		# allHands = []
		for i in range(playerCount):
			if(self.playerStatus != None):
				self.playerHandScores.append(evaluator.evaluate(self.board, self.roundPlayers[i].hand))
				self.playerHandClasses.append(evaluator.get_rank_class(self.playerHandScores[i]))
		# 		allHands.append(self.roundPlayers[i].hand)
			else:
				self.playerHandScores.append(None)
				self.playerHandClasses.append(None)
				# allHands.append(self.roundPlayers[i].hand)
		#print(str(Card.get_suit_int(self.board[0]))+" "+str(Card.get_rank_int(self.board[0])))
		# print("BOARD: ")
		# Card.print_pretty_cards(self.board)        
		# for i in range(playerCount):
		# 	if(self.playerStatus[i]!=None):
		# 		print("Player " + str(i) + ": ")
		# 		Card.print_pretty_cards(self.roundPlayers[i].hand)
		# 	else:
		# 		print("Player " + str(i) + ": FOLDED")


		winners=self.getWinnerIndexes()      
		self.endRound(gameObject, winners)
		# evaluator.hand_summary(self.board, allHands)      
		return True

	def revealCards(self, gameObject, cards):
		data = {}
		data['agenda'] = "cardReveal"
		data['data'] = []
		for card in cards:
			data['data'].append(gameObject.convertNotation(Card.get_rank_int(card), Card.get_suit_int(card)))
		comms.broadcastToPlayers(gameObject.players, data);

				   
class Player:
	def __init__(self, moneyInit, user):
		#self.id = idInit
		self.hand = []
		self.money = moneyInit
		self.currentBet = 0

		self.id = user['sid']
		self.socket = user['socket']

	def setMoney(self, moneyAmmount):
			self.money=moneyAmmount

	def addCard(self, card):
			self.hand.append(card)

	def placeBet(self, roundObject, ammount): #TODO: ce ti dnara sfali
		if(ammount <= 0):
			return False
		else:
			self.money -= (ammount - self.currentBet)
			roundObject.pot += (ammount - self.currentBet)
			self.currentBet = ammount
			return True

# def main():
#     gameInstance = Game(2)
#     gameInstance.addPlayer(Player(1000, 0))
#     gameInstance.addPlayer(Player(1000, 1))
#     gameInstance.addPlayer(Player(1000, 2))
#     gameInstance.startNewRound()
#     variable=0

# if __name__=='__main__': main()

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