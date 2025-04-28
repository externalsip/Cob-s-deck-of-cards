#pragma once
#include "card.h"
#include "deck.h"
#include "cardRow.h"
#include <sstream>
#include <iostream>
#include <vector>
#include "console.h"
#include "Stockpile.h"
#include "HousePile.h"

class SolitaireCore {
public:
	void CreateGame();
	void DisplayGame();
	void MoveCards(int i, int j, int k);

	void GetCardFromWaste(int targetRow);
	void HitWaste();

	void SendCardToPile(int i, int j);
	void GetCardFromPile(int i, int j);

	void SendCardFromWasteToPile(int i);

	bool CheckWin();
private:
	vector<shared_ptr<card>> emptyVector;

	shared_ptr<cardRow> row1 = make_unique<cardRow>(emptyVector);
	shared_ptr<cardRow> row2 = make_unique<cardRow>(emptyVector);
	shared_ptr<cardRow> row3 = make_unique<cardRow>(emptyVector);
	shared_ptr<cardRow> row4 = make_unique<cardRow>(emptyVector);
	shared_ptr<cardRow> row5 = make_unique<cardRow>(emptyVector);
	shared_ptr<cardRow> row6 = make_unique<cardRow>(emptyVector);
	shared_ptr<cardRow> row7 = make_unique<cardRow>(emptyVector);

	shared_ptr<cardRow> rowContentArr[7] = { row1, row2, row3, row4, row5, row6, row7 };

	shared_ptr<Stockpile> stock = make_unique<Stockpile>(emptyVector, emptyVector);

	shared_ptr<HousePile> pile1 = make_unique<HousePile>(emptyVector);
	shared_ptr<HousePile> pile2 = make_unique<HousePile>(emptyVector);
	shared_ptr<HousePile> pile3 = make_unique<HousePile>(emptyVector);
	shared_ptr<HousePile> pile4 = make_unique<HousePile>(emptyVector);

	shared_ptr<HousePile> pileArr[4] = { pile1, pile2, pile3, pile4 };
};