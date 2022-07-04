#pragma once
#include "Game_Runner.h"
class ABAutoPlayer:public GameRunner
{

	int ABMinMax(Gomoku GameBoard, bool isComputer, int depth, int alpha, int beta);
	int FindBestMove(Gomoku GameBoard, int depth);

};

