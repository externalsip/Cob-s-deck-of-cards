#include "cardRow.h"

string cardRow::GetCard(int i) {
	ostringstream message;
	if (i < RowContent.size()) {
		message << RowContent[i]->DisplayInfo();
		return(message.str());
	}
	else {
		//if there is no card at this position, return two blank spaces as to not screw up the layout.
		message << "   ";
		return(message.str());
	}
}

bool cardRow::bCanReceiveCard(shared_ptr<card> otherCard) {
	if (RowContent.size() > 0) {
		//Get the values of the last card of the array since this is the one that has to be able to receive the cards being sent.
		int lenght = RowContent.size();
		int house = RowContent[lenght - 1]->GetCardHouse();
		int i = RowContent[lenght - 1]->GetCardVal();

		int otherHouse = otherCard->GetCardHouse();
		int cardValue = otherCard->GetCardVal();

		if (cardValue != i - 1) {
			return false;
		}

		//If the added card's value is equal to the value of the last card of the row -1, (meaning for example that you are trying to add a jack over a queen), check the house of the card.
		//If the last card of the array is of the house of hearts (1) or diamonds (3) and the added card is of the house of spades (2) or clubs (4) or vice-versa, return true, otherwise return false.
		//The way this is checked is by adding up the value of the houses of both cards, since both black houses are even numbers and red houses are odd numbers, the result of the addition should be odd if the two cards arent from the same color of house.
		if ((house + otherHouse) % 2 != 0) {
			return true;
		}
		else {
			return false;
		}
		
	}
	//if the row is currently empty, only accept a king, the house of the king does not matter (meaning a card with a value of 13).
	else {
		int cardValue = otherCard->GetCardVal();
		if (cardValue == 13) {
			return true;
		}
		else {
			return false;
		}
	}
}

void cardRow::ReceiveCards(vector<shared_ptr<card>> newCards) {
	//Move the new cards into the row.
	RowContent.insert(RowContent.end(), newCards.begin(), newCards.end());
}

vector<shared_ptr<card>> cardRow::GiveCards(int i) {
	//Make a new vector that contains the cards to send
	vector<shared_ptr<card>> packageContent;
	packageContent.insert(packageContent.begin(), RowContent.begin() + i, RowContent.end());

	return packageContent;
}

void cardRow::RemoveCards(int i) {
	//remove the cards that are being sent from the vector
	RowContent.erase(RowContent.begin() + i, RowContent.end());
	//return a vector with the cards to send.

	int Len = RowContent.size();
	if (Len > 0) {
		bool Discovered = RowContent[Len - 1]->WasCardDiscovered();
		if (!Discovered) {
			RowContent[Len - 1]->DiscoverCard();
		}
	}
}

bool cardRow::bCanGiveCards(int i) {
	return RowContent[i]->WasCardDiscovered();
}

void cardRow::MakeCardVisible() {
	int length = RowContent.size();
	RowContent[length - 1]->DiscoverCard();
}

int cardRow::GetRowLength() {
	return RowContent.size();
}

void cardRow::Reset() {
	RowContent.clear();
}