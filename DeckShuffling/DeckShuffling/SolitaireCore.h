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
#include "Score.h"

class SolitaireCore {
public:
	void CreateGame();
	void DisplayGame();
	void MoveCards(int i, int j, int k);

	void GetCardFromWaste(int i);
	void HitWaste();

	void SendCardToPile(int i, int j);
	void GetCardFromPile(int i, int j);

	void SendCardFromWasteToPile(int i);

	bool CheckWin();

	string DisplayScores();
private:
	vector<shared_ptr<card>> EmptyVector;
	vector<int> EmptyInt;

	shared_ptr<cardRow> Row1 = make_unique<cardRow>(EmptyVector);
	shared_ptr<cardRow> Row2 = make_unique<cardRow>(EmptyVector);
	shared_ptr<cardRow> Row3 = make_unique<cardRow>(EmptyVector);
	shared_ptr<cardRow> Row4 = make_unique<cardRow>(EmptyVector);
	shared_ptr<cardRow> Row5 = make_unique<cardRow>(EmptyVector);
	shared_ptr<cardRow> Row6 = make_unique<cardRow>(EmptyVector);
	shared_ptr<cardRow> Row7 = make_unique<cardRow>(EmptyVector);

	shared_ptr<cardRow> RowContentArr[7] = { Row1, Row2, Row3, Row4, Row5, Row6, Row7 };

	shared_ptr<Stockpile> Stock = make_unique<Stockpile>(EmptyVector, EmptyVector);

	shared_ptr<HousePile> Pile1 = make_unique<HousePile>(EmptyVector);
	shared_ptr<HousePile> Pile2 = make_unique<HousePile>(EmptyVector);
	shared_ptr<HousePile> Pile3 = make_unique<HousePile>(EmptyVector);
	shared_ptr<HousePile> Pile4 = make_unique<HousePile>(EmptyVector);

	shared_ptr<HousePile> PileArr[4] = { Pile1,Pile2, Pile3, Pile4 };

	unique_ptr<Score> ScoreObject = make_unique<Score>(EmptyInt); 
};