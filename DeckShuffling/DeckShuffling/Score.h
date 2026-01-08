#pragma once
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

class Score {
public:
	Score(vector<int> scoreList) : ScoreList(scoreList) {};

	int DisplayScore();
	void NewGame();
	void IncrementScore();
	string DisplayAllScores();
private:
	vector<int> ScoreList;
};