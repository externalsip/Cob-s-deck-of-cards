#include "HousePile.h"

bool HousePile::bCanReceiveCard(shared_ptr<card> card) {
	int len = Pile.size();
	if (len == 0) {
		if (card->GetCardVal() == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (card->GetCardVal() == Pile[len - 1]->GetCardVal() + 1 && card->GetCardHouse() == Pile[0]->GetCardHouse()) {
		return true;
	}

	else {
		return false;
	}
}

void HousePile::AddCard(shared_ptr<card> card) {
	Pile.push_back(card);
}

shared_ptr<card> HousePile::GiveCard() {
	int len = Pile.size();
	if (len > 0) {
		return Pile[len - 1];
	}
	else {
		return nullptr;
	}
}

void HousePile::RemoveCard() {
	Pile.erase(Pile.end() - 1);
}

string HousePile::ShowTopCard() {
	int len = Pile.size();
	ostringstream msg;
	if (len > 0) {
		msg << Pile[len - 1]->DisplayInfo();
	}
	else {
		msg << "## ";
	}
	return msg.str();
}

int HousePile::GivePileSize() {
	return Pile.size();
}

void HousePile::Reset() {
	Pile.clear();
}