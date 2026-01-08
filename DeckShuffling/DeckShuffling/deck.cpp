#include "deck.h"

void deck::GenerateDeck() {
	CardList.clear();
	shared_ptr<card> cardBase;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 13; j++) {
			cardBase = make_unique<card>(j, i);
			CardList.push_back(cardBase);
		}
	}
}

void deck::DisplayDeck() {
	console cons;
	ostringstream message;
	message << "Current card list and order: " << '\n';
	for (int i = 0; i < CardList.size(); i++) {
		switch (CardList[i]->GetCardVal()) {
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
				message << CardList[i]->GetCardVal();
				break;
			}

		}		

		message << " of ";

		switch (CardList[i]->GetCardHouse()) {
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
	int n = CardList.size();
	
	vector<int> cardValues;

	for (int i = 0; i < CardList.size(); i++) {
		cardValues.push_back(CardList[i]->GetCardVal());
	}

	QuickSort(CardList, 0, n - 1, cardValues);

	SortHouses(CardList, 4, 13);
}



void deck::QuickSort(vector<shared_ptr<card>> &cardList, int low, int high, vector<int> &objectVals) {
	if (low < high) {
		int pivot = Partition(cardList, low, high, objectVals);


		QuickSort(cardList, low, pivot - 1, objectVals);
		QuickSort(cardList, pivot + 1, high, objectVals);
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

void deck::ShuffleDeck() {
	int i = 0;
	srand(time(0));
	while (i < 120) {
		int index = rand() % 52;
		int otherIndex = rand() % 52;

		if (index != otherIndex) {
			swap(CardList[index], CardList[otherIndex]);
			i++;
		}

	}
}

void deck::SortHouses(vector<shared_ptr<card>> &cardList, int houseCount, int increment) {		
	vector<int> values;
	for (int i = 0; i < cardList.size(); i++) {
		values.push_back(cardList[i]->GetCardHouse());
	}
	for (int i = 0; i < increment; i++) {
		QuickSort(cardList, 0 + (houseCount * i), houseCount + (houseCount * i) - 1, values);
	}
}

int deck::GetDeckSize() {
	return CardList.size();
}

vector<shared_ptr<card>> deck::GiveDeck() {
	return CardList;
}