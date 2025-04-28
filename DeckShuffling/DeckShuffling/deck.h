#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include "card.h"
#include "console.h"

using namespace std;

class deck {
public:

	void GenerateDeck();
	void ShuffleDeck();
	void UnShuffleDeck();
	void DisplayDeck();

	int GetDeckSize();

	vector<shared_ptr<card>> GiveDeck();

	template <typename T>

	T AskUserInput(string message) {
		cout << message;
		T result = -1;

		while (!(cin >> result)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			console cons;
			ostringstream message;
			message << "Invalid input, please try again.";
			cons.DisplayMessage(message.str());
		}

		return result;
	}
private:
	vector<shared_ptr<card>> cardList; //This is the deck.

	int Partition(vector<shared_ptr<card>> &cardList, int low, int high, vector<int>& objectVals);

	
	void QuickSort(vector<shared_ptr<card>> &cardList, int low, int high, vector<int> &objectVals);

	void SortHouses(vector<shared_ptr<card>> &cardList, int houseCount, int increment);
};