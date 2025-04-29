#include "Score.h"

int Score::DisplayScore() {
	int len = scoreList.size();
	return scoreList[len - 1];
}

void Score::NewGame() {
	int newScore = 0;
	scoreList.push_back(newScore);
}

void Score::IncrementScore() {
	int len = scoreList.size();
	scoreList[len - 1]++;
}

string Score::DisplayAllScores() {
	ostringstream msg;
	for (int i = 0; i < scoreList.size(); i++) {
		msg << i + 1 << ": " << scoreList[i] << '\n';
	}
	return msg.str();
}