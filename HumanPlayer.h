#pragma once
#include "Game_Runner.h"
class HumanPlayer:public GameRunner
{
public:
	int FindBestMove(Gomoku GameBoard, int depth);//returns an index to play after taking input from user
};

