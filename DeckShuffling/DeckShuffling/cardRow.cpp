#include "cardRow.h"

string cardRow::GetCard(int i) {
	ostringstream message;
	if (i < rowContent.size()) {
		message << rowContent[i]->DisplayInfo();
		return(message.str());
	}
	else {
		//if there is no card at this position, return two blank spaces as to not screw up the layout.
		message << "   ";
		return(message.str());
	}
}

bool cardRow::bCanReceiveCard(shared_ptr<card> cCard) {
	if (rowContent.size() > 0) {
		//Get the values of the last card of the array since this is the one that has to be able to receive the cards being sent.
		int Len = rowContent.size();
		int H = rowContent[Len - 1]->GetCardHouse();
		int i = rowContent[Len - 1]->GetCardVal();

		int oH = cCard->GetCardHouse();
		int cardVal = cCard->GetCardVal();

		if (cardVal == i - 1) {
			//If the added card's value is equal to the value of the last card of the row -1, (meaning for example that you are trying to add a jack over a queen), check the house of the card.
			//If the last card of the array is of the house of hearts (1) or diamonds (3) and the added card is of the house of spades (2) or clubs (4) or vice-versa, return true, otherwise return false.
			//The way this is checked is by adding up the value of the houses of both cards, since both black houses are even numbers and red houses are odd numbers, the result of the addition should be odd if the two cards arent from the same color of house.
			if ((H + oH) % 2 != 0) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	//if the row is currently empty, only accept a king, the house of the king does not matter (meaning a card with a value of 13).
	else {
		int cardVal = cCard->GetCardVal();
		if (cardVal == 13) {
			return true;
		}
		else {
			return false;
		}
	}
}

void cardRow::ReceiveCards(vector<shared_ptr<card>> newCards) {
	//Move the new cards into the row.
	rowContent.insert(rowContent.end(), newCards.begin(), newCards.end());
}

vector<shared_ptr<card>> cardRow::GiveCards(int i) {
	//Make a new vector that contains the cards to send
	vector<shared_ptr<card>> packageContent;
	packageContent.insert(packageContent.begin(), rowContent.begin() + i, rowContent.end());

	return packageContent;
}

void cardRow::RemoveCards(int i) {
	//remove the cards that are being sent from the vector
	rowContent.erase(rowContent.begin() + i, rowContent.end());
	//return a vector with the cards to send.

	int Len = rowContent.size();
	if (Len > 0) {
		bool Discovered = rowContent[Len - 1]->WasCardDiscovered();
		if (!Discovered) {
			rowContent[Len - 1]->DiscoverCard();
		}
	}
}

bool cardRow::bCanGiveCards(int i) {
	return rowContent[i]->WasCardDiscovered();
}

void cardRow::MakeCardVisible() {
	int Len = rowContent.size();
	rowContent[Len - 1]->DiscoverCard();
}

int cardRow::GetRowLength() {
	return rowContent.size();
}

void cardRow::Reset() {
	rowContent.clear();
}