#pragma once
#include "Gomoku.h"
#include "HumanPlayer.h"
#include "Game_Runner.h"
//this class will have the gomoku items e.g turns etc,,a human player so we can take input
//from a function in human class
//we make a function play game which will alternate between game solver..which is the auto
//solver class...and the human...till it determines game is over
class GamePlay
{
public:
	Gomoku GomokuVer;
	//HumanPlayer HPlayer;
	GameRunner* AutoPlayer;
	GameRunner* HPlayer;
	int depth;

	GamePlay(int x);
	void StartGame();//play game until game over
	bool GameOver();//in case of tie or return of int max or min

};

