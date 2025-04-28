#include "Stockpile.h"

void Stockpile::ReceiveCards(vector<shared_ptr<card>> cardList) {
	stockPile.insert(stockPile.end(), cardList.begin(), cardList.end());
	CardCount = stockPile.size();
	for (int i = 0; i < stockPile.size(); i++) {
		stockPile[i]->DiscoverCard();
	}
}

bool Stockpile::CardsLeftInStockPile() {
	if (stockPile.size() > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Stockpile::SendCardsToWaste() {
	int i = 0;
	if (CardCount > 0) {
		if (stockPile.size() == 0) {
			stockPile.insert(stockPile.begin(), wastePile.begin(), wastePile.end());
			wastePile.clear();
		}
		vector<shared_ptr<card>> cardsToSend;
		while (i < 3) {
			if (stockPile.size() > 0) {
				cardsToSend.push_back(stockPile[0]);
				stockPile.erase(stockPile.begin());
			}
			i++;
		}
		reverse(cardsToSend.begin(), cardsToSend.end());
		wastePile.insert(wastePile.end(), cardsToSend.begin(), cardsToSend.end());
	}

}

string Stockpile::DisplayWaste() {
	ostringstream msg;
	int i = 0;
	int len = wastePile.size();
	int j = len - 1;
	while (i < 3) {
		if (j - i >= 0 && len != 0) {
			msg << wastePile[j - i]->DisplayInfo() << " ";
		}
		i++;
	}
	return msg.str();
}

void Stockpile::ResetStockPile() {
	stockPile.insert(stockPile.begin(), wastePile.begin(), wastePile.end());
}

shared_ptr<card> Stockpile::SendCardFromWaste() {
	int len = wastePile.size();
	if (len > 0) {
		return wastePile[len-1];
	}
	else {
		return nullptr;
	}

}

void Stockpile::RemoveCardFromPile() {
	wastePile.erase(wastePile.end() - 1);
	CardCount--;
}

void Stockpile::Reset() {
	stockPile.clear();
	wastePile.clear();
}