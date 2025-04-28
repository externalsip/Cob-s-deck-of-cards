#pragma once
#include "card.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Stockpile {
public:
	Stockpile(vector<shared_ptr<card>> stockPile, vector<shared_ptr<card>> wastePile) : stockPile(stockPile), wastePile(wastePile) {};

	void ReceiveCards(vector<shared_ptr<card>> cardList);
	bool CardsLeftInStockPile();
	void SendCardsToWaste();
	void ResetStockPile();
	string DisplayWaste();

	shared_ptr<card> SendCardFromWaste();
	void RemoveCardFromPile();

	void Reset();
private:
	vector<shared_ptr<card>> stockPile;
	vector<shared_ptr<card>> wastePile;
	int CardCount;
};