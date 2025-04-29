#include "SolitaireCore.h"

void SolitaireCore::CreateGame() {
	deck cardDeck;
	score->NewGame();
	cardDeck.GenerateDeck();
	cardDeck.ShuffleDeck();

	vector<shared_ptr<card>> deckInstance = cardDeck.GiveDeck();

	vector<shared_ptr<card>> rowStartingCards;

	rowStartingCards.insert(rowStartingCards.begin(), deckInstance.begin(), deckInstance.begin());

	stock->Reset();

	for (int i = 0; i < 7; i++) 
	{
		rowContentArr[i]->Reset();
	}
	for (int i = 0; i < 4; i++) {
		pileArr[i]->Reset();
	}

	int i = 0;
	int j = 0;
	while (i < 7) {
		rowStartingCards.insert(rowStartingCards.begin(), deckInstance.begin() + j, deckInstance.begin() + j + i + 1);
		rowContentArr[i]->ReceiveCards(rowStartingCards);
		rowContentArr[i]->MakeCardVisible();
		rowStartingCards.clear();
		i++;		
		j += i;
	}
	rowStartingCards.insert(rowStartingCards.begin(), deckInstance.begin() + j, deckInstance.end());
	stock->ReceiveCards(rowStartingCards);
}

void SolitaireCore::DisplayGame() {
	ostringstream msg;
	console cons;
	msg << "   1   2   3   4   5   6   7" << '\n';
	int GameHeight = rowContentArr[0]->GetRowLength();
	//To make sure the game always displays every card, it will make always take as many lines as the longest vector out of the 7 rows.
	for (int i = 1; i < 7; i++) {
		if (GameHeight < rowContentArr[i]->GetRowLength()) {
			GameHeight = rowContentArr[i]->GetRowLength();
		}
	}
	//This loop displays every card currently on the game board.
	for (int i = 0; i < GameHeight; i++) {		
		if (i + 1 < 10) {
			msg << "0";
		}
		msg << i + 1 << " ";

		for (int j = 0; j < 7; j++) {
			msg << rowContentArr[j]->GetCard(i) << " ";
		}
		msg << '\n';
	}
	msg << '\n';
	msg << "Waste: " << stock->DisplayWaste() << '\n';
	msg << "Piles:  1   2   3   4" << '\n';
	msg << "        ";
	for (int i = 0; i < 4; i++) {
		msg << pileArr[i]->ShowTopCard() << " ";
	}
	msg << '\n';
	msg << "Moves: " << score->DisplayScore();
	cons.DisplayMessage(msg.str());
}

void SolitaireCore::MoveCards(int i, int j, int k) {
	ostringstream msg;
	console cons;
	int nI = i - 1;
	int nJ = j - 1;
	int nK = k - 1;
	cons.ClearConsole();
	if ( nI < 7 && nJ < 7 && nK < rowContentArr[nI]->GetRowLength() && nI >= 0 && nJ >= 0 && nK >= 0) {
		vector<shared_ptr<card>> CardsToGive = rowContentArr[nI]->GiveCards(nK);
		if (rowContentArr[nJ]->bCanReceiveCard(CardsToGive[0]) && rowContentArr[nI]->bCanGiveCards(nK)) {
			rowContentArr[nI]->RemoveCards(nK);
			rowContentArr[nJ]->ReceiveCards(CardsToGive);
			score->IncrementScore();
			msg << "Cards succesfuly sent from column " << i << " to column " << j << "!" << '\n';
		}
		else {
			CardsToGive.clear();
			msg << "ERROR! The selected cards are not compatible with the selected column" << '\n';
		}
	}
	else {
		msg << "ERROR! the selected column does not have a card at the index specified" << '\n';
	}
	cons.DisplayMessage(msg.str());
}

void SolitaireCore::GetCardFromWaste(int targetRow) {
	ostringstream msg;
	console cons;
	cons.ClearConsole();
	int nI = targetRow - 1;
	shared_ptr<card> wasteCard = stock->SendCardFromWaste();
	if (wasteCard != nullptr) {
		if (nI < 7 && nI >= 0) {
			if (rowContentArr[nI]->bCanReceiveCard(wasteCard)) {
				vector<shared_ptr<card>> wasteCardV;
				wasteCardV.push_back(wasteCard);
				rowContentArr[nI]->ReceiveCards(wasteCardV);
				stock->RemoveCardFromPile();
				score->IncrementScore();
				msg << "Card taken from waste succesfully !";
			}
			else {
				msg << "ERROR! " << wasteCard->DisplayInfo() << " is not compatible with the selected column";
			}
		}
		else {
			msg << "ERROR! The specified column does not exist." << '\n';
		}
	}
	else {
		msg << "ERROR! No card is currently in the waste pile." << '\n';
	}
	cons.DisplayMessage(msg.str());
}

void SolitaireCore::HitWaste() {
	console cons;
	cons.ClearConsole();
	stock->SendCardsToWaste();
}

void SolitaireCore::SendCardToPile(int i, int j) {
	int nI = i - 1;
	int nJ = j - 1;
	ostringstream msg;
	console cons;
	cons.ClearConsole();
	if (nI >= 0 && nI < 7 && nJ >= 0 && nJ < 4) {
		int len = rowContentArr[nI]->GetRowLength() - 1;
		shared_ptr<card> C = rowContentArr[nI]->GiveCards(len)[0];
		if (pileArr[nJ]->bCanReceiveCard(C)) {
			pileArr[nJ]->AddCard(C);
			rowContentArr[nI]->RemoveCards(len);
			score->IncrementScore();
			msg << C->DisplayInfo() <<" successfully added to pile " << j << "!" << '\n';
		}
		else {
			msg << "ERROR! " << C->DisplayInfo() << "  is not compatible with the pile." << '\n';
		}
	}
	else {
		msg << "ERROR! The selected pile or column does not exist." << '\n';
	}
	cons.DisplayMessage(msg.str());

}

void SolitaireCore::GetCardFromPile(int i, int j) {
	int nI = i - 1;
	int nJ = j - 1;
	ostringstream msg;
	console cons;
	cons.ClearConsole();
	if (nI >= 0 && nI < 4 && nJ >= 0 && nJ < 7) {
		shared_ptr<card> C = pileArr[nI]->GiveCard();
		if (C != nullptr) {
			if (rowContentArr[nJ]->bCanReceiveCard(C)) {
				vector<shared_ptr<card>> CA;
				CA.push_back(C);
				rowContentArr[nJ]->ReceiveCards(CA);
				pileArr[nI]->RemoveCard();
				score->IncrementScore();
				msg << "Card moved from pile to column." << '\n';
				}
			else {
				msg << "ERROR! The selected card is not compatible with the selected column." << '\n';
			}
		}
		else {
			msg << "ERROR! The selected pile is empty" << '\n';
		}
		
	}
	else {
		msg << "ERROR! The selected pile or column does not exist." << '\n';
	}
	cons.DisplayMessage(msg.str());
}

void SolitaireCore::SendCardFromWasteToPile(int i) {
	ostringstream msg;
	console cons;
	cons.ClearConsole();
	int nI = i - 1;
	shared_ptr<card> wasteCard = stock->SendCardFromWaste();
	if (wasteCard != nullptr) {
		if (nI < 4 && nI >= 0) {
			if (pileArr[nI]->bCanReceiveCard(wasteCard)) {
				pileArr[nI]->AddCard(wasteCard);
				stock->RemoveCardFromPile();
				score->IncrementScore();
				msg << "Card taken from waste succesfully !";
			}
			else {
				msg << "ERROR! " << wasteCard->DisplayInfo() << " is not compatible with the selected pile";
			}
		}
		else {
			msg << "ERROR! The specified pile does not exist." << '\n';
		}
	}
	else {
		msg << "ERROR! No card is currently in the waste pile." << '\n';
	}
	cons.DisplayMessage(msg.str());
}

bool SolitaireCore::CheckWin() {

	for (int i = 0; i < 4; i++) {
		if (pileArr[i]->GivePileSize() != 13) {
			break;
		}
		else if (i == 3) {	
			return true;
		}
	}
	return false;
}

string SolitaireCore::DisplayScores() {
	return score->DisplayAllScores();
}