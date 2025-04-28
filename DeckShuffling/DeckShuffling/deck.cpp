#include "deck.h"

void deck::GenerateDeck() {
	cardList.clear();
	shared_ptr<card> cardBase;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 13; j++) {
			cardBase = make_unique<card>(j, i);
			cardList.push_back(cardBase);
		}
	}
}

void deck::DisplayDeck() {
	console cons;
	ostringstream message;
	message << "Current card list and order: " << '\n';
	for (int i = 0; i < cardList.size(); i++) {
		switch (cardList[i]->GetCardVal()) {
		case 1: {
			message << "Ace";
			break;
		}
		case 11: {
			message << "Jack";
			break;
		}
		case 12: {
			message << "Queen";
			break;
		}
		case 13: {
			message << "King";
			break;
		}
		default: {
			message << cardList[i]->GetCardVal();
			break;
		}

		}		

		message << " of ";

		switch (cardList[i]->GetCardHouse()) {
		case 1: {
			message << "Hearts" << '\n';
			break;
		}
		case 2: {
			message << "Spades" << '\n';
			break;
		}
		case 3: {
			message << "Diamonds" << '\n';
			break;
		}
		case 4: {
			message << "Clubs" << '\n';
			break;
		}
		}

	}		
	cons.DisplayMessage(message.str());
}

void deck::UnShuffleDeck() {
	int n = cardList.size();
	
	vector<int> vals;

	for (int i = 0; i < cardList.size(); i++) {
		vals.push_back(cardList[i]->GetCardVal());
	}

	QuickSort(cardList, 0, n - 1, vals);

	SortHouses(cardList, 4, 13);
}



void deck::QuickSort(vector<shared_ptr<card>> &cardList, int low, int high, vector<int> &objectVals) {
	if (low < high) {
		int pi = Partition(cardList, low, high, objectVals);


		QuickSort(cardList, low, pi - 1, objectVals);
		QuickSort(cardList, pi + 1, high, objectVals);
	}
}

int deck::Partition(vector<shared_ptr<card>> &cardList, int low, int high, vector<int> &objectVals) {
	int pivot = objectVals[high];

	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (objectVals[j] <= pivot) {
			i++;
			swap(cardList[i], cardList[j]);
			swap(objectVals[i], objectVals[j]);
		}
	}

	swap(cardList[i + 1], cardList[high]);
	swap(objectVals[i + 1], objectVals[high]);
	return(i + 1);
}

//These quicksort functions arent very clean, but they do their job, since I only ever sort cards with them I did not bother making them templates, but if I ever want to make something more modular that is one of the first things I would do.

void deck::ShuffleDeck() {
	int i = 0;
	srand(time(0));
	while (i < 120) {
		int index = rand() % 52;
		int otherIndex = rand() % 52;

		if (index != otherIndex) {
			swap(cardList[index], cardList[otherIndex]);
			i++;
		}

	}
}

void deck::SortHouses(vector<shared_ptr<card>> &cardList, int houseCount, int increment) {		
	vector<int> vals;
	for (int i = 0; i < cardList.size(); i++) {
		vals.push_back(cardList[i]->GetCardHouse());
	}
	for (int i = 0; i < increment; i++) {
		QuickSort(cardList, 0 + (houseCount * i), houseCount + (houseCount * i) - 1, vals);
	}
}

int deck::GetDeckSize() {
	return cardList.size();
}

vector<shared_ptr<card>> deck::GiveDeck() {
	return cardList;
}