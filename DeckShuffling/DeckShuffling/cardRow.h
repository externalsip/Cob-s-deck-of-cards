#pragma once
#include "card.h"
#include <iostream>
#include <vector>
#include <sstream>

class cardRow {
public:
	cardRow(vector<shared_ptr<card>> rowContent) : rowContent(rowContent) {};
	string GetCard(int i);

	bool bCanReceiveCard(shared_ptr<card> cCard);
	bool bCanGiveCards(int i);

	void ReceiveCards(vector<shared_ptr<card>> newCards);
	vector<shared_ptr<card>> GiveCards(int i);

	void RemoveCards(int i);

	void MakeCardVisible();

	int GetRowLength();

	void Reset();

private:
	vector<shared_ptr<card>> rowContent;
};