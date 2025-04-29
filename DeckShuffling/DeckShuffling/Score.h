#pragma once
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

class Score {
public:
	Score(vector<int> scoreList) : scoreList(scoreList) {};

	int DisplayScore();
	void NewGame();
	void IncrementScore();
	string DisplayAllScores();
private:
	int score;
	vector<int> scoreList;
};