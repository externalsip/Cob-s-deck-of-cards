#include "Score.h"

int Score::DisplayScore() {
	int lenght = ScoreList.size();
	return ScoreList[lenght - 1];
}

void Score::NewGame() {
	int newScore = 0;
	ScoreList.push_back(newScore);
}

void Score::IncrementScore() {
	int lenght = ScoreList.size();
	ScoreList[lenght - 1]++;
}

string Score::DisplayAllScores() {
	ostringstream message;
	for (int i = 0; i < ScoreList.size(); i++) {
		message << i + 1 << ": " << ScoreList[i] << '\n';
	}
	return message.str();
}