import random
from deuces import Deck #pip install deuces
from deuces import Evaluator
from deuces import Card
import math
evaluator = Evaluator()
import comms
import User

class Round:
	def __init__(self, gameObject):
		self.pot = 0
		self.sidePot = 0
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
			p.currentBet=0
			self.allIn=False
			self.allInDifference=0

		#self.board[:]=[]
		#del self.board[:]
		#self.board=[]

	def reset(self, gameObject):
		self.__init__(gameObject)

	def bettingPhase(self, gameObject, startPlayerIndex):
		playerCount=len(self.roundPlayers)
		currentPI=startPlayerIndex
		for p in range(0, playerCount):   #init. playerStatus array-all to false, except those who folded (set to None)
			if(self.playerStatus[p]!=None):
				self.playerStatus[p]=False
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

				#tell everyone else its his turn
				data = {}
				data['agenda'] = "playersTurn"
				data['data'] = gameObject.players[currentPI].id
				comms.broadcastToEveryoneExcept(gameObject.players, gameObject.players[currentPI], data)

				data = {}
				data['agenda'] = "yourTurn"
				print("Sending yourTurn to {}".format(gameObject.players[currentPI].id))
				comms.send(gameObject.players[currentPI].socket, data)
				rec = comms.receive(gameObject.players[currentPI].socket)
				
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
					#DONE(test) check, da raisa vec kot je min SERVER SIDE
					inputRaise = int(rec['data'])
					#if(inputRaise<=0):
					#	inputRaise=minRaise
					#elif(inputRaise>self.roundPlayers[currentPI].money):
					#	inputRaise=self.roundPlayers[currentPI].money
					#DONE-end
					betPlaced=self.roundPlayers[currentPI].placeBet(self, self.currentMinBet + inputRaise)
					self.playerStatus[currentPI]=True
					self.resetPlayerStatusAfterRaise(currentPI)

					#self.currentMinBet+=inputRaise
					self.currentMinBet=betPlaced

					print("RAISE: {}".format(inputRaise))
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
				elif(action=="leave"):
					#poslji mu ok za left?
					self.removePlayer(gameObject, currentPI)
					# print("\n><\n><\nround:{}, game:{}\n><\n><\n".format(len(self.roundPlayers), len(gameObject.players)))
					if currentPI > 0:
						if currentPI == playerCount - 1:
							currentPI -= 1
					#fix index problems from leaver
					playerCount -= 1

		return True

	def preflopPhase(self, gameObject, startPlayerIndex):
		playerCount = len(self.roundPlayers)
		currentPI = startPlayerIndex
		for p in range(0, playerCount):   #init. playerStatus array-all to false
			self.playerStatus.append(False)
		#small blind
		smallPI = currentPI
		betPlaced=self.roundPlayers[currentPI].placeBet(self, self.currentMinBet/2)
		currentPI = self.nextPlayer(currentPI, playerCount)

		#big blind
		bigPI = currentPI
		betPlaced=self.roundPlayers[currentPI].placeBet(self, self.currentMinBet)
		self.playerStatus[currentPI] = True
		currentPI = self.nextPlayer(currentPI, playerCount)		
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

				#tell everyone else its his turn
				data = {}
				data['agenda'] = "playersTurn"
				data['data'] = gameObject.players[currentPI].id
				comms.broadcastToEveryoneExcept(gameObject.players, gameObject.players[currentPI], data)

				data = {}
				data['agenda'] = "yourTurn"
				print("Sending yourTurn to {}".format(gameObject.players[currentPI].id))
				comms.send(gameObject.players[currentPI].socket, data)
				rec = comms.receive(gameObject.players[currentPI].socket)

				action = rec['agenda']
				if(action=="check"):
					betPlaced=self.roundPlayers[currentPI].placeBet(self, self.currentMinBet)
					self.playerStatus[currentPI]=True
					data = {}
					data['agenda'] = "playerCheck"
					data['data'] = gameObject.players[currentPI].id #player ki je raisal: SID
					comms.broadcastToPlayers(gameObject.players, data)

					currentPI=self.nextPlayer(currentPI, playerCount)
				elif(action=="raise"):
					inputRaise = int(rec['data'])
					#DONE(test) check, da raisa vec kot je min SERVER SIDE
					#if(inputRaise<minRaise):
					#	inputRaise=minRaise
					#elif(inputRaise>self.roundPlayers[currentPI].money):
					#	inputRaise=self.roundPlayers[currentPI].money
					#DONE-end
					betPlaced=self.roundPlayers[currentPI].placeBet(self, self.currentMinBet + inputRaise)
					self.playerStatus[currentPI]=True
					self.resetPlayerStatusAfterRaise(currentPI)

					#self.currentMinBet+=inputRaise
					self.currentMinBet=betPlaced

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
				elif(action=="leave"):
					#poslji mu ok za left?
					self.removePlayer(gameObject, currentPI)
					# print("\n><\n><\nround:{}, game:{}\n><\n><\n".format(len(self.roundPlayers), len(gameObject.players)))
					if currentPI > 0:
						if currentPI == playerCount - 1:
							currentPI -= 1
					#fix index problems from leaver
					playerCount -= 1

		return True

	def removePlayer(self, gameObject, playerIndex):
		#close the socket conn
		self.roundPlayers[playerIndex].socket.close()
		
		#remove player from lobby
		del gameObject.lobby['users'][self.roundPlayers[playerIndex].id]
		
		#cleanup
		removedPlayer = self.roundPlayers.pop(playerIndex)
		self.playerStatus.pop(playerIndex)

		#DONE(test) set user score, za lazji insert into DB pol. kucer pls
		removedPlayer.score=removedPlayer.money-gameObject.startingCash

		gameObject.endGameUsers.append(removedPlayer);

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

	def getMinBetAndSecondMinBetAndItsIndexes(self):
		minBet=None;
		secondMinBet=None;
		index=None
		secondIndex=None
		for i in range(len(self.roundPlayers)):	#get first non-folded players bet as min
			if(self.playerStatus[i] is not None):
				minBet=self.roundPlayers[i].currentBet
				index=i
				break;

		for i in range(len(self.roundPlayers)):	#search for smaller bet
			if(self.playerStatus[i] is not None and self.roundPlayers[i].currentBet < minBet):
				secondMinBet=minBet
				secondIndex=index
				minBet=self.roundPlayers[i].currentBet
				index=i
		return [index, minBet, secondIndex, secondMinBet];

	def endRound(self, gameObject, winners):
		#winners=[0,1]
		data = {}
		data['agenda'] = "playerWonRound"
		data['data'] = {'winnerSid': [], 'earnings': [], 'playerSid':[], 'playerHands':[], 'currentCash':[]}

		if(len(winners)==1):
			#only 1 winner
			gameObject.players[winners[0]].money+=self.pot
			print("Player " + str(winners[0]) + " WON")
			data['data']['winnerSid'] = gameObject.players[winners[0]].id	#front checks len(data['playerSid'])
			data['data']['earnings'] = self.pot
		else:
			#OH LORD HELP US, CE BO TO DELALO
			mainPot=0
			sidePot=0
			leftoverMainPot=0
			leftoverSidePot=0
			retVal=self.getMinBetAndSecondMinBetAndItsIndexes()
			minBetIndex=retVal[0]
			minBet=retVal[1]
			secondMinIndex=retVal[2]
			secondMinBet=retVal[3]
			sidePotWinners=[]
			for i in range(len(self.roundPlayers)):	#get main pot
				#calculate mainPot
				if(self.playerStatus[i] is not None):
					mainPot+=minBet

				#advanced black magic sidePot calculations
				if(self.playerStatus[i] is not None and self.roundPlayers[i].currentBet > minBet):
					sidePot+=(secondMinBet-minBet)
					if(self.roundPlayers[i].currentBet>secondMinBet):
						self.roundPlayers[i].returnMoney((self.roundPlayers[i].currentBet-secondMinBet))
						sidePotWinners.push(i)
						self.roundPlayers[i].currentBet=secondMinBet #needed?
			
			if(len(winners)==0):
				mainPotSplit=mainPot
			else:
				mainPotSplit=math.floor(mainPot/len(winners))
				leftoverMainPot=mainPot%len(winners)
			if(len(sidePotWinners)==0):
				sidePotSplit=sidePot
				sidePotWinners=winners
			else:
				sidePotSplit=math.floor(sidePot/len(sidePotWinners))
				leftoverSidePot=sidePot%len(sidePotWinners)
			
			for j in range(len(winners)):
				if(self.roundPlayers[j].currentBet==minBet):
					gameObject.players[winners[j]].money+=mainPotSplit
				if(self.roundPlayers[j].currentBet > minBet):
					gameObject.players[winners[j]].money+=sidePotSplit
			#split leftover earnings amongst players (remainder at pot/ammountOfWinners; example=> 15/2=7=>remainder:1; first winners gets the leftover money)
			#requires in-depth testing
			mainLeftoverEarnings=[]
			for p in winners:
				mainLeftoverEarnings.append(0)
			mainPotPI=0
			while(leftoverMainPot>0):
				mainLeftoverEarnings[mainPotPI]+=1
				leftoverMainPot-=1
				mainPotPI+=1
				if(mainPotPI>len(winners)):
					mainPotPI=0
			sideLeftoverEarnings=[]
			for p in sidePotWinners:
				sideLeftoverEarnings.addpend(0)
			sidePotPI=0
			while(leftoverSidePot>0):
				sideLeftoverEarnings[sidePotPI]+=1
				leftoverSidePot-=1
				sidePotPI+=1
				if(sidePotPI>len(sidePotWinners)):
					sidePotPI=0

			mainPotPI2=0
			sidePotPI2=0
			for p in winners:
				earnings=mainPotSplit
				if(mainPotPI2<len(winners)):
					earnings+=mainLeftoverEarnings[mainPotPI2]
					mainPotPI2+=1
				data['data']['winnerSid'].append(gameObject.players[p].id)
				if(p in sidePotWinners):
					earnings+=sidePotSplit
					if(sidePotPI2<len(sideLeftoverEarnings)):
						earnings+=sideLeftoverEarnings[sidePotPI2]
						sidePotPI2+=1
				data['data']['earnings'].append(earnings)

			#split the pot-DEPRECATED

			#potSplit=self.pot / len(winners)
			#print("Pot split between: ")
			#for p in winners:
			#	gameObject.players[winnerIndex].money+=potSplit
			#	print("Player " + str(winners[0]) + " ")
			#	data['playerSid'].append(gameObject.players[p])
			#	data['earnings'].append(potSplit)
		
		for player in gameObject.players:
			data['data']['playerSid'].append(player.id)
			convertedHand = player.hand
			convertedHand[0] = gameObject.convertNotation(Card.get_rank_int(convertedHand[0]), Card.get_suit_int(convertedHand[0]))
			convertedHand[1] = gameObject.convertNotation(Card.get_rank_int(convertedHand[1]), Card.get_suit_int(convertedHand[1]))
			data['data']['playerHands'].append(convertedHand)
			data['data']['currentCash'].append(player.money)
		print(data)
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
		self.board=[]
		self.pot=0
		self.sidePot=0
		print("MAIN POT: "+ str(self.pot)+ " SIDE POT: "+ str(self.sidePot))
		playerCount = len(self.roundPlayers)
		if(playerCount <= 1): #check if there are more than 1 players in round
			print("ENDING GAME - NOT ENOUGH PLAYERS LEFT")
			return False #DONE implementiraj ce ni nobenega ker so leavali
		
		#deal initial hands
		for i in range(2):
			for player in self.roundPlayers:
				player.hand.append(self.deck.draw(1))
		#game start & initial cards
		for player in self.roundPlayers:
			data = {}
			data['agenda'] = "roundStart"
			data['status'] = "ok"
			currentHand = player.hand
			data['data'] = [
				gameObject.convertNotation(Card.get_rank_int(currentHand[0]), Card.get_suit_int(currentHand[0])),
				gameObject.convertNotation(Card.get_rank_int(currentHand[1]), Card.get_suit_int(currentHand[1]))
			]
			comms.send(player.socket, data);

		#Preflop phase
		print("--Preflop--")
		result = self.preflopPhase(gameObject, (gameObject.roundCounter % len(self.roundPlayers)))
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
		playerCount = len(self.roundPlayers)
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
		#DONE(test): ob koncu igre klici removePlayer() nad vsemi igralci ki so ostali zavoljo konsistence
		# evaluator.hand_summary(self.board, allHands)      
		return True

	def revealCards(self, gameObject, cards):
		data = {}
		data['agenda'] = "cardReveal"
		data['data'] = []
		for card in cards:
			data['data'].append(gameObject.convertNotation(Card.get_rank_int(card), Card.get_suit_int(card)))
		comms.broadcastToPlayers(gameObject.players, data);
