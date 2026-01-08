#include "HousePile.h"

bool HousePile::bCanReceiveCard(shared_ptr<card> card) {
	int length = Pile.size();
	if (length == 0) {
		if (card->GetCardVal() == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (card->GetCardVal() == Pile[length - 1]->GetCardVal() + 1 && card->GetCardHouse() == Pile[0]->GetCardHouse()) {
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
	int length = Pile.size();
	if (length > 0) {
		return Pile[length - 1];
	}
	else {
		return nullptr;
	}
}

void HousePile::RemoveCard() {
	Pile.erase(Pile.end() - 1);
}

string HousePile::ShowTopCard() {
	int length = Pile.size();
	ostringstream message;
	if (length > 0) {
		message << Pile[length - 1]->DisplayInfo();
	}
	else {
		message << "## ";
	}
	return message.str();
}

int HousePile::GivePileSize() {
	return Pile.size();
}

void HousePile::Reset() {
	Pile.clear();
}