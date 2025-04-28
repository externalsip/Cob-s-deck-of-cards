#include "card.h"

using namespace std;

int card::GetCardVal() {
	return cardVal;
}

int  card::GetCardHouse() {
	return cardHouse;
}

bool card::WasCardDiscovered() {
	return wasDiscovered;
}

void card::DiscoverCard() {
	wasDiscovered = true;
}

string card::DisplayInfo() {
	ostringstream message;
	if (WasCardDiscovered()) {
		//Special case for cards displayed with letters instead of numbers.
		switch (GetCardVal()) {
		case 1: {
			message << "A";
			break;
		}
		case 11: {
			message << "J";
			break;
		}
		case 12: {
			message << "Q";
			break;
		}
		case 13: {
			message << "K";
			break;
		}
		default: {
			message << GetCardVal();

			break;
		}
		}
		switch (GetCardHouse()) {
			//Display the house of the cards.
		case 1: {
			message << "H";
			break;
		}
		case 2: {
			message << "S";
			break;
		}
		case 3: {
			message << "D";
			break;
		}
		case 4: {
			message << "C";
			break;
		}
		}
		if (GetCardVal() != 10) {
			message << " ";
		}
		return(message.str());

	}
	else {
		//If a card is not currently discovered, return XX.
		message << "XX ";
		return(message.str());
	}
}