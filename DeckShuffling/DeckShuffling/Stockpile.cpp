#include "Stockpile.h"

void Stockpile::ReceiveCards(vector<shared_ptr<card>> cardList) {
	StockPile.insert(StockPile.end(), cardList.begin(), cardList.end());
	CardCount = StockPile.size();
	for (int i = 0; i < StockPile.size(); i++) {
		StockPile[i]->DiscoverCard();
	}
}

bool Stockpile::CardsLeftInStockPile() {
	if (StockPile.size() > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Stockpile::SendCardsToWaste() {

	if (CardCount <= 0) {
		return;
	}

	if (StockPile.size() == 0) {
		StockPile.insert(StockPile.begin(), WastePile.begin(), WastePile.end());
		WastePile.clear();
	}

	int i = 0;
	vector<shared_ptr<card>> cardsToSend;

	while (i < 3) {
		if (StockPile.size() > 0) {
			cardsToSend.push_back(StockPile[0]);
			StockPile.erase(StockPile.begin());
		}
		i++;
	}
	reverse(cardsToSend.begin(), cardsToSend.end());
	WastePile.insert(WastePile.end(), cardsToSend.begin(), cardsToSend.end());

}

string Stockpile::DisplayWaste() {
	ostringstream message;
	int i = 0;
	int len = WastePile.size();
	int j = len - 1;
	while (i < 3) {
		if (j - i >= 0 && len != 0) {
			message << WastePile[j - i]->DisplayInfo() << " ";
		}
		i++;
	}
	return message.str();
}

void Stockpile::ResetStockPile() {
	StockPile.insert(StockPile.begin(), WastePile.begin(), WastePile.end());
}

shared_ptr<card> Stockpile::SendCardFromWaste() {
	int length = WastePile.size();
	if (length > 0) {
		return WastePile[length-1];
	}
	else {
		return nullptr;
	}

}

void Stockpile::RemoveCardFromPile() {
	WastePile.erase(WastePile.end() - 1);
	CardCount--;
}

void Stockpile::Reset() {
	StockPile.clear();
	WastePile.clear();
}