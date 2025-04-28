#include "HousePile.h"

bool HousePile::bCanReceiveCard(shared_ptr<card> C) {
	int len = pile.size();
	if (len == 0) {
		if (C->GetCardVal() == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (C->GetCardVal() == pile[len - 1]->GetCardVal() + 1 && C->GetCardHouse() == pile[0]->GetCardHouse()) {
		return true;
	}

	else {
		return false;
	}
}

void HousePile::AddCard(shared_ptr<card> C) {
	pile.push_back(C);
}

shared_ptr<card> HousePile::GiveCard() {
	int len = pile.size();
	if (len > 0) {
		return pile[len - 1];
	}
	else {
		return nullptr;
	}
}

void HousePile::RemoveCard() {
	pile.erase(pile.end() - 1);
}

string HousePile::ShowTopCard() {
	int len = pile.size();
	ostringstream msg;
	if (len > 0) {
		msg << pile[len - 1]->DisplayInfo();
	}
	else {
		msg << "## ";
	}
	return msg.str();
}

int HousePile::GivePileSize() {
	return pile.size();
}

void HousePile::Reset() {
	pile.clear();
}