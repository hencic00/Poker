#define _BSD_SOURCE

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QThread>
#include <QTimer>

#include <iostream>

#include <unistd.h>
#include "math.h"
#include "lobbiesPage.h"
#include "task.h"

Task::Task(serverHandler* s, QListWidget *uL, QPushButton* rB, lobbyPage* papa):QObject()
{
	server = s;
	usersList = uL;
	readyButton = rB;
	foter = papa;
}

Task::Task(serverHandler* s, playPage* papa):QObject()
{
	server = s;
	foter1 = papa;
	// card.insert(c.begin(), c.end());

}

Task::~Task()
{}

#ifndef MYLISTITEM
#define MYLISTITEM
class myListItem : public QListWidgetItem
{
	public:
		int userSid;
};
#endif

void Task::doWork()
{
	QFont font;
	font.setPixelSize(40);

	while(true)
	{	
		QJsonObject response = server->receviceMessage();

		if (response.value("agenda").toString() == "playerJoined")
		{
			QJsonObject data = response.value("data").toObject();
			myListItem *item = new myListItem();
			item->setText(data["username"].toString());
			item->setFont(font);
			item->userSid = data["userSid"].toInt();


			usersList->insertItem(0, item);
			if(usersList->count() > 1)
			{
				readyButton->setEnabled(true);
			}
		}
		else if(response.value("agenda").toString() == "leaveLobby")
		{
			usersList->clear();
			usleep(10000);
			stack->setCurrentIndex(3);
			((lobbiesPage*)stack->widget(3))->stackFocus();



			break;
		}
		else if(response.value("agenda").toString() == "playerLeft")
		{
			QJsonObject data = response.value("data").toObject();
			int userSid = data["userSid"].toInt();

			for (int i = 0; i < usersList->count(); ++i)
			{
				if (userSid == ((myListItem*)usersList->item(i))->userSid)
				{
					usersList->takeItem(i);
				}
			}

			if(usersList->count() < 2)
			{
				readyButton->setEnabled(false);
			}
		}
		else if(response.value("agenda").toString() == "userReady")
		{
			QJsonObject data = response.value("data").toObject();
			int userSid = data["userSid"].toInt();
			for (int i = 0; i < usersList->count(); ++i)
			{
				if (userSid == ((myListItem*)usersList->item(i))->userSid)
				{
					usersList->item(i)->setForeground(Qt::green);
					usersList->item(i)->setText(usersList->item(i)->text() + "✔");
					// foter->update();
					usersList->repaint();
				}
			}
		}
		else if(response.value("agenda").toString() == "gameStart")
		{
			QJsonObject data = response.value("data").toObject();
			QJsonValue players = data.value("players");
			QJsonArray playersArray = players.toArray();

			QString usernames[5];
			int playerSid[5];
			QString usercards[10];

			int nmOfPlayers = playersArray.count();

			for (int i = 0; i < playersArray.count(); ++i)
			{
				usernames[i] = playersArray.at(i).toObject()["username"].toString();
				playerSid[i] = playersArray.at(i).toObject()["playerSid"].toInt();
			}
			foter->startGame(nmOfPlayers, usernames, playerSid);
			break;
		}
	}

	this->thread()->quit();
}



void Task::doWork1()
{
	bool nekaj = false;
	int cardReveal = 0;
	bool nekaj1 = false;
	bool nekaj2 = false;

	while(true)
	{	
		QJsonObject response = server->receviceMessage();

		if (response.value("agenda").toString() == "roundStart")
		{
			QJsonArray cards = response.value("data").toArray();
			std::string card0 = cards.at(0).toString().toStdString();
			std::string card1 = cards.at(1).toString().toStdString();

			foter1->render->playerCard[0][0] = foter1->card[card0];
			foter1->render->playerCard[0][1] = foter1->card[card1];
			cardReveal = 0;

			foter1->render->tableCards[0] = foter1->card["cardBack"];
			foter1->render->tableCards[1] = foter1->card["cardBack"];
			foter1->render->tableCards[2] = foter1->card["cardBack"];
			foter1->render->tableCards[3] = foter1->card["cardBack"];
			foter1->render->tableCards[4] = foter1->card["cardBack"];

			for (int i = 1; i < foter1->render->nmOfPlayers; ++i)
			{
				
				foter1->render->playerCard[i][0] = foter1->card["cardBack"];
				foter1->render->playerCard[i][1] = foter1->card["cardBack"];
			}

			// std::cout << "nekaj" << std::endl;
		}
		else if (response.value("agenda").toString() == "BSblind")
		{
			QJsonArray cards = response.value("data").toArray();
			for (int i = 0; i < foter1->render->nmOfPlayers; ++i)
			{
					if (cards.at(0).toInt() == foter1->render->playerSid[i].toInt())
					{
						foter1->render->bet[i] = QString::number(floor(cards.at(2).toInt() / 2.0)) + " $";	
						foter1->render->bet1[i] = floor(cards.at(2).toInt() / 2.0);
						foter1->render->userMoney[i] -= floor(cards.at(2).toInt() / 2.0);
					}
					else if (cards.at(1).toInt() == foter1->render->playerSid[i].toInt())
					{
						foter1->render->bet[i] = QString::number(cards.at(2).toInt()) + " $";
						foter1->render->bet1[i] = cards.at(2).toInt();
						foter1->render->maxBet = cards.at(2).toInt();
						foter1->render->userMoney[i] -= cards.at(2).toInt();
					}

					foter1->minBet = cards.at(2).toInt();

			}

			if (nekaj)
			{
				foter1->render->repaint();
				/* code */
			}
			nekaj = true;

			int nmOfTicks = 0;
			int bet = 5;
			while(bet == foter1->render->userMoney[0])
			{
				nmOfTicks++;
			}
			foter1->bettAmmoutScroll->setRange(0, 8);

			// std::cout << foter1->render->nmOfPlayers << std::endl;
		}
		else if (response.value("agenda").toString() == "yourTurn")
		{
			foter1->raiseButton->setEnabled(true);
			if (foter1->render->bet1[0] >= foter1->render->maxBet)
			{
				foter1->checkButton->setEnabled(true);
			}
			foter1->foldButton->setEnabled(true);
			foter1->bettAmmoutScroll->setEnabled(true);

			// foter1->render->boxColor[0] = "#C3A1A1";

			// if (nekaj2)
			// {
			// 	foter1->repaint();
			// }

			// nekaj2 = true;
			// nekaj1 = true;
		}
		else if (response.value("agenda").toString() == "playerFold")
		{
			for (int i = 0; i < foter1->render->nmOfPlayers; ++i)
			{
				if (response.value("data").toInt() == foter1->render->playerSid[i].toInt())
				{
					foter1->render->bet[i] = "Fold";
					foter1->render->repaint();
				}
			}
		}
		else if (response.value("agenda").toString() == "playerWonRound")
		{
			QString WinnerName = "";
			QJsonObject data = response.value("data").toObject();
			for (int i = 0; i < foter1->render->nmOfPlayers; ++i)
			{
				if (data.value("winnerSid").toInt() == foter1->render->playerSid[i].toInt())
				{
					WinnerName = foter1->render->userNames[i];
				}

				foter1->render->bet[i] = "";
			}

			QJsonArray players = data.value("playerSid").toArray();
			QJsonArray currentCash = data.value("currentCash").toArray();
			QJsonArray playerHands = data.value("playerHands").toArray();
			for (int i = 0; i < foter1->render->nmOfPlayers; ++i)
			{
				for (int j = 0; j < foter1->render->nmOfPlayers; ++j)
				{
					if (QString::number(players.at(i).toInt()) == foter1->render->playerSid[j])
					{
						foter1->render->userMoney[j] = currentCash.at(i).toInt();

						QJsonArray hand = playerHands.at(i).toArray();
					

						std::string card0 = hand.at(0).toString().toStdString();
						std::string card1 = hand.at(1).toString().toStdString();

						foter1->render->playerCard[j][0] = foter1->card[card0];
						foter1->render->playerCard[j][1] = foter1->card[card1];
					}
				}
			}


			foter1->render->message = WinnerName + " won!";
			foter1->render->repaint();
			usleep(2000000);
			foter1->render->message = "";
			foter1->render->repaint();
		}
		else if (response.value("agenda").toString() == "playerRaise")
		{
			QJsonArray data = response.value("data").toArray();
			int bet = 5;
			int minimum = 0;
			for (int i = 0; i < foter1->render->nmOfPlayers; ++i)
			{
				if (foter1->render->playerSid[i] == QString::number(data.at(0).toInt()))
				{
					foter1->render->userMoney[i] -= ((data.at(1).toInt() + foter1->minBet) - foter1->render->bet1[i]);
					foter1->render->bet1[i] = (data.at(1).toInt() + foter1->minBet);
					foter1->render->bet[i] = QString::number(foter1->render->bet1[i]) + "$";
					// foter1->bigBlind = foter1->render->bet1[i];

					
					while(bet < foter1->render->bet1[i])
					{
						bet *= 2;
						++minimum;
					}
					// foter1->repaint();


					foter1->minBet = foter1->render->bet1[i];
				}
			}
			foter1->repaint();
			foter1->bettAmmoutScroll->setRange(minimum, 8);
		}
		else if (response.value("agenda").toString() == "playerCheck")
		{
			int sid = response.value("data").toInt();

			for (int i = 0; i < foter1->render->nmOfPlayers; ++i)
			{
				if (foter1->render->playerSid[i] == QString::number(sid))
				{
					foter1->render->userMoney[i] -= ((foter1->minBet) - foter1->render->bet1[i]);
					foter1->render->bet1[i] = foter1->minBet;
					foter1->render->bet[i] = QString::number(foter1->minBet) + "$";
				}
			}
			foter1->repaint();
		}
		else if (response.value("agenda").toString() == "cardReveal")
		{
			QJsonArray cards = response.value("data").toArray();

			if (cardReveal == 0)
			{
				std::string card0 = cards.at(0).toString().toStdString();
				std::string card1 = cards.at(1).toString().toStdString();
				std::string card2 = cards.at(2).toString().toStdString();

				foter1->render->tableCards[0] = foter1->card[card0];
				foter1->render->tableCards[1] = foter1->card[card1];
				foter1->render->tableCards[2] = foter1->card[card2];
				/* code */
			}
			else if (cardReveal == 1)
			{
				std::string card0 = cards.at(0).toString().toStdString();

				foter1->render->tableCards[3] = foter1->card[card0];
			}
			else if (cardReveal == 2)
			{
				std::string card0 = cards.at(0).toString().toStdString();

				foter1->render->tableCards[4] = foter1->card[card0];
			}

			cardReveal++;

			foter1->repaint();
		}
		else if (response.value("agenda").toString() == "playersTurn")
		{
			int sid = response.value("data").toInt();

			// for (int i = 0; i < foter1->render->nmOfPlayers; ++i)
			// {
			// 	if (foter1->render->playerSid[i] == QString::number(sid))
			// 	{
			// 		foter1->render->boxColor[i] = "#C3A1A1";
			// 	}
			// 	else 
			// 	{
			// 		foter1->render->boxColor[i] = "#FFFFFF";
			// 	}
			// }
			// if (nekaj1)
			// {
			// 	foter1->repaint();
			// 	std::cout << "nekaj" << std::endl;
			// }

			
		}
	}
}

void Task::updateBox()
{
	std::cout << "nekaj" << std::endl;
}