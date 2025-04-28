#pragma once
#include "card.h"
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class HousePile {
public:
	HousePile(vector<shared_ptr<card>> pile) : pile(pile) {};

	bool bCanReceiveCard(shared_ptr<card> card);
	void AddCard(shared_ptr<card> card);
	shared_ptr<card> GiveCard();
	void RemoveCard();
	string ShowTopCard();
	int GivePileSize();

	void Reset();
private:
	vector<shared_ptr<card>> pile;
};