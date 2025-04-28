#pragma once
#include <iostream>
#include <sstream>
using namespace std;

class card {
public:	
	card(int cardVal, int cardHouse) : cardVal(cardVal), cardHouse(cardHouse) {};
	int GetCardVal();
	int GetCardHouse();
	bool WasCardDiscovered();
	void DiscoverCard();
	string DisplayInfo();

private:
	int cardVal;
	int cardHouse;
	bool wasDiscovered = false;
};