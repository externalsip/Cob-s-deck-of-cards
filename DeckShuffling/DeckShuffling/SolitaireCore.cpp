#include "SolitaireCore.h"

void SolitaireCore::CreateGame() {
	deck cardDeck;
	ScoreObject->NewGame();
	cardDeck.GenerateDeck();
	cardDeck.ShuffleDeck();

	vector<shared_ptr<card>> deckInstance = cardDeck.GiveDeck();

	vector<shared_ptr<card>> rowStartingCards;

	rowStartingCards.insert(rowStartingCards.begin(), deckInstance.begin(), deckInstance.begin());

	Stock->Reset();

	for (int i = 0; i < 7; i++) 
	{
		RowContentArr[i]->Reset();
	}
	for (int i = 0; i < 4; i++) {
		PileArr[i]->Reset();
	}

	int i = 0;
	int j = 0;
	while (i < 7) {
		rowStartingCards.insert(rowStartingCards.begin(), deckInstance.begin() + j, deckInstance.begin() + j + i + 1);
		RowContentArr[i]->ReceiveCards(rowStartingCards);
		RowContentArr[i]->MakeCardVisible();
		rowStartingCards.clear();
		i++;		
		j += i;
	}
	rowStartingCards.insert(rowStartingCards.begin(), deckInstance.begin() + j, deckInstance.end());
	Stock->ReceiveCards(rowStartingCards);
}

void SolitaireCore::DisplayGame() {
	ostringstream message;
	console console;
	message << "   1   2   3   4   5   6   7" << '\n';
	int GameHeight = RowContentArr[0]->GetRowLength();

	//To make sure the game always displays every card, every line will be as long as the longest vector out of the 7 rows.
	
	for (int i = 1; i < 7; i++) {
		if (GameHeight < RowContentArr[i]->GetRowLength()) {
			GameHeight = RowContentArr[i]->GetRowLength();
		}
	}
	//This loop displays every card currently on the game board.
	for (int i = 0; i < GameHeight; i++) {		
		if (i + 1 < 10) {
			message << "0";
		}
		message << i + 1 << " ";

		for (int j = 0; j < 7; j++) {
			message << RowContentArr[j]->GetCard(i) << " ";
		}
		message << '\n';
	}
	message << '\n';
	message << "Waste: " << Stock->DisplayWaste() << '\n';
	message << "Piles:  1   2   3   4" << '\n';
	message << "        ";
	for (int i = 0; i < 4; i++) {
		message << PileArr[i]->ShowTopCard() << " ";
	}
	message << '\n';
	message << "Moves: " << ScoreObject->DisplayScore();
	console.DisplayMessage(message.str());
}

void SolitaireCore::MoveCards(int i, int j, int k) {
	ostringstream message;
	console console;
	int fromColumn = i - 1;
	int toColumn = j - 1;
	int highestInsertedCardIndex = k - 1;
	console.ClearConsole();

	if (fromColumn >= 7 || fromColumn < 0 || toColumn >= 7 || toColumn < 0 || highestInsertedCardIndex >= RowContentArr[fromColumn]->GetRowLength() || highestInsertedCardIndex < 0) {
		message << "ERROR! the selected column does not have a card at the index specified" << '\n';
		console.DisplayMessage(message.str());
		return;
	}

	vector<shared_ptr<card>> CardsToGive = RowContentArr[fromColumn]->GiveCards(highestInsertedCardIndex);

	if (!RowContentArr[toColumn]->bCanReceiveCard(CardsToGive[0]) || !RowContentArr[fromColumn]->bCanGiveCards(highestInsertedCardIndex)) {
		CardsToGive.clear();
		message << "ERROR! The selected cards are not compatible with the selected column" << '\n';
		console.DisplayMessage(message.str());
		return;
	}

	RowContentArr[fromColumn]->RemoveCards(highestInsertedCardIndex);
	RowContentArr[toColumn]->ReceiveCards(CardsToGive);
	ScoreObject->IncrementScore();
	message << "Cards succesfuly sent from column " << i << " to column " << j << "!" << '\n';
	
	console.DisplayMessage(message.str());
}

void SolitaireCore::GetCardFromWaste(int i) {
	ostringstream message;
	console console;
	console.ClearConsole();
	int targetRow = i - 1;
	shared_ptr<card> wasteCard = Stock->SendCardFromWaste();

	if (wasteCard == nullptr) {
		message << "ERROR! No card is currently in the waste pile." << '\n';
		console.DisplayMessage(message.str());
		return;
	}

	if (targetRow >= 7 || targetRow < 0) {
		message << "ERROR! The specified column does not exist." << '\n';
		console.DisplayMessage(message.str());
		return;
	}

	if (!RowContentArr[targetRow]->bCanReceiveCard(wasteCard)) {
		message << "ERROR! " << wasteCard->DisplayInfo() << " is not compatible with the selected column";
		console.DisplayMessage(message.str());
		return;
	}

	vector<shared_ptr<card>> wasteCardsVector;
	wasteCardsVector.push_back(wasteCard);
	RowContentArr[targetRow]->ReceiveCards(wasteCardsVector);
	Stock->RemoveCardFromPile();
	ScoreObject->IncrementScore();
	message << "Card taken from waste succesfully !";
			
	console.DisplayMessage(message.str());
}

void SolitaireCore::HitWaste() {
	console console;
	console.ClearConsole();
	Stock->SendCardsToWaste();
}

void SolitaireCore::SendCardToPile(int i, int j) {
	int selectedColumn = i - 1;
	int selectedPile = j - 1;
	ostringstream message;
	console console;
	console.ClearConsole();

	if (selectedColumn >= 7 || selectedColumn < 0 || selectedPile >= 4 || selectedPile < 0) {
		message << "ERROR! The selected pile or column does not exist." << '\n';
		console.DisplayMessage(message.str());
		return;
	}

	int lenght = RowContentArr[selectedColumn]->GetRowLength() - 1;
	shared_ptr<card> selectedCard = RowContentArr[selectedColumn]->GiveCards(lenght)[0];

	if (!PileArr[selectedPile]->bCanReceiveCard(selectedCard)) {
		message << "ERROR! " << selectedCard->DisplayInfo() << "  is not compatible with the pile." << '\n';
		console.DisplayMessage(message.str());
		return;
	}


	PileArr[selectedPile]->AddCard(selectedCard);
	RowContentArr[selectedColumn]->RemoveCards(lenght);
	ScoreObject->IncrementScore();
	message << selectedCard->DisplayInfo() <<" successfully added to pile " << j << "!" << '\n';

	console.DisplayMessage(message.str());

}

void SolitaireCore::GetCardFromPile(int i, int j) {
	int selectedPile = i - 1;
	int selectedColumn = j - 1;
	ostringstream message;
	console console;
	console.ClearConsole();

	if (selectedPile >= 4 || selectedPile < 0 || selectedColumn >= 7 || selectedColumn < 0) {
		message << "ERROR! The selected pile or column does not exist." << '\n';
		console.DisplayMessage(message.str());
		return;
	}


	shared_ptr<card> selectedCard = PileArr[selectedPile]->GiveCard();

	if (selectedCard == nullptr) {
		message << "ERROR! The selected pile is empty" << '\n';
		console.DisplayMessage(message.str());
		return;
	}

	if (!RowContentArr[selectedColumn]->bCanReceiveCard(selectedCard)) {
		message << "ERROR! The selected card is not compatible with the selected column." << '\n';
		console.DisplayMessage(message.str());
		return;
	}

	vector<shared_ptr<card>> cardVector;
	cardVector.push_back(selectedCard);
	RowContentArr[selectedColumn]->ReceiveCards(cardVector);
	PileArr[selectedPile]->RemoveCard();
	ScoreObject->IncrementScore();
	message << "Card moved from pile to column." << '\n';

		
	console.DisplayMessage(message.str());
}

void SolitaireCore::SendCardFromWasteToPile(int i) {
	ostringstream message;
	console console;
	console.ClearConsole();
	int SelectedPile = i - 1;
	shared_ptr<card> wasteCard = Stock->SendCardFromWaste();

	if (wasteCard == nullptr) {
		message << "ERROR! No card is currently in the waste pile." << '\n';
		console.DisplayMessage(message.str());
		return;
	}

	if (SelectedPile >= 4 || SelectedPile < 0) {
		message << "ERROR! The specified pile does not exist." << '\n';
		console.DisplayMessage(message.str());
		return;
	}

	if (!PileArr[SelectedPile]->bCanReceiveCard(wasteCard)) {
		message << "ERROR! " << wasteCard->DisplayInfo() << " is not compatible with the selected pile";
		console.DisplayMessage(message.str());
		return;
	}

	PileArr[SelectedPile]->AddCard(wasteCard);
	Stock->RemoveCardFromPile();
	ScoreObject->IncrementScore();
	message << "Card taken from waste succesfully !";
	console.DisplayMessage(message.str());
}

bool SolitaireCore::CheckWin() {

	for (int i = 0; i < 4; i++) {
		if (PileArr[i]->GivePileSize() != 13) {
			return false;
		}
	}
	return true;

}

string SolitaireCore::DisplayScores() {
	return ScoreObject->DisplayAllScores();
}