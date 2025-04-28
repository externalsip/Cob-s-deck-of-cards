#include "deck.h"
#include "console.h"
#include "SolitaireCore.h"

int main() {
	deck cardDeck;
	console cons;
	
	SolitaireCore SolitaireClass;

	bool isRunning = true;
	bool playingSolitaire = false;
	while (isRunning) {

		ostringstream message;		
		if (!playingSolitaire) {
			int decision = cardDeck.AskUserInput<int>("What will it be today ? \n |1| Generate a card deck \n |2| Shuffle the card deck \n |3| Un-shuffle the card deck  \n |4| Display the card deck \n |5| Play Solitaire \n |6| Quit \n");
			switch (decision) {
			case 1: {
				cardDeck.GenerateDeck();

				message << "Deck generated" << '\n';
				cons.DisplayMessage(message.str());
				break;
			}
			case 2: {
				if (cardDeck.GetDeckSize() > 0) {
					cardDeck.ShuffleDeck();
					message << "Deck shuffled" << '\n';
					cons.DisplayMessage(message.str());
				}
				else {
					message << "Generate a deck first." << '\n';
					cons.DisplayMessage(message.str());
				}
				break;
			}
			case 3: {
				if (cardDeck.GetDeckSize() > 0) {
					cardDeck.UnShuffleDeck();
					message << "Deck un-shuffled" << '\n';
					cons.DisplayMessage(message.str());
				}
				else {
					message << "Generate a deck first." << '\n';
					cons.DisplayMessage(message.str());
				}
				break;
			}
			case 4: {
				cardDeck.DisplayDeck();
				break;
			}
			case 5: {
				playingSolitaire = true;
				SolitaireClass.CreateGame();
				break;
			}

			case 6: {
				message << "Goodbye" << '\n';
				isRunning = false;
				break;
			}
			default: {
				message << "Unkown character" << '\n';
				cons.DisplayMessage(message.str());
				break;
			}
			}
			if (isRunning && !playingSolitaire) {
				decision = cardDeck.AskUserInput<int>("Anything else ? \n |1| Yes \n |2| No \n");
				message.clear();
				switch (decision) {
				case 1: {
					break;
				}
				case 2: {
					isRunning = false;
					message << "Goodbye" << '\n';
					cons.DisplayMessage(message.str());
					break;
				}
				default: {
					isRunning = false;
					message << "Unknown character, goodbye" << '\n';
					cons.DisplayMessage(message.str());
					break;
				}
				}
			}
		}
		else {
			SolitaireClass.DisplayGame();
			int decision = cardDeck.AskUserInput<int>("Cob's Solitaire \n |1| Swap cards from one row to another \n |2| Add to waste pile \n |3| Take card from waste pile \n |4| Send card from column to one of the piles \n |5| Take a card from one of the piles \n |6| Move a card from the waste to a pile \n |7| Quit \n");
			switch (decision) {
			case 1: {
				int i = cardDeck.AskUserInput<int>("From which column do you wish to take the cards ? \n");
				int j = cardDeck.AskUserInput<int>("To which column do you wish to move the cards ? \n");
				int k = cardDeck.AskUserInput<int>("What is the row of the highest card you wish to move ? \n");
				SolitaireClass.MoveCards(i, j, k);
				break;
			}
			case 2: {
				SolitaireClass.HitWaste();
				break;
			}
			case 3: {
				int i = cardDeck.AskUserInput<int>("Which column will the waste card go to ? \n");
				SolitaireClass.GetCardFromWaste(i);
				break;
			}
			case 4: {
				int i = cardDeck.AskUserInput<int>("From which column do you wish to take a card ? \n");
				int j = cardDeck.AskUserInput<int>("To what pile do you wish to send the card ? \n");
				SolitaireClass.SendCardToPile(i, j);
				break;
			}
			case 5: {
				int i = cardDeck.AskUserInput<int>("From which pile do you wish to take a card ? \n");
				int j = cardDeck.AskUserInput<int>("To what column do you wish to send the card ? \n");
				SolitaireClass.GetCardFromPile(i, j);
				break;
			}
			case 6: {
				int i = cardDeck.AskUserInput<int>("To what pile do you wish to move the card ? \n");
				SolitaireClass.SendCardFromWasteToPile(i);
				break;
			}
			case 7: {
				message << "Goodbye";
				isRunning = false;
				cons.DisplayMessage(message.str());
				break;
			}
			default: {
				message << "Unknown Character";
				cons.DisplayMessage(message.str());
			}
			}
			if (SolitaireClass.CheckWin()) {
				message.clear();
				cons.ClearConsole();
				message << "######  ###  #####     #     # ### #     # ### ### ###" << '\n';
				message << "#     #  #  #     #    #  #  #  #  ##    # ### ### ###" << '\n';
				message << "#     #  #  #          #  #  #  #  # #   # ### ### ###" << '\n';
				message << "######   #  #  ####    #  #  #  #  #  #  #  #   #   # " << '\n';
				message << "#     #  #  #     #    #  #  #  #  #   # #            " << '\n';
				message << "#     #  #  #     #    #  #  #  #  #    ## ### ### ###" << '\n';
				message << "######  ###  #####      ## ##  ### #     # ### ### ###" << '\n';
				cons.DisplayMessage(message.str());
				message.clear();
				decision = cardDeck.AskUserInput<int>("Do you wish to play again ? \n |1| Yes \n |2| No \n |3| Quit software");
				switch (decision) {
				case 1: {
					SolitaireClass.CreateGame();
					break;
				}
				case 2: {
					playingSolitaire = false;
					break;
				}
				case 3: {
					message << "Goodbye";
					cons.DisplayMessage(message.str());
					isRunning = false;
				}
				}
			}
		}
		
	}

	return 0;
}