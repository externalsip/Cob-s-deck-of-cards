#pragma once
#include <iostream>
#include <sstream>
using namespace std;

class card {
public:	
	card(int cardValue, int cardHouse) : CardValue(cardValue), CardHouse(cardHouse) {};
	int GetCardVal();
	int GetCardHouse();
	bool WasCardDiscovered();
	void DiscoverCard();
	string DisplayInfo();

private:
	int CardValue;
	int CardHouse;
	bool WasDiscovered = false;
};