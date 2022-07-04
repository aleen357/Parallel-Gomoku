#pragma once
#include "Game_Runner.h"
class Parallel_ABAutoPlayer:public GameRunner
{

	int Parallel_ABMinMax(Gomoku GameBoard, bool isComputer, int depth, int alpha, int beta);
	int FindBestMove(Gomoku GameBoard, int depth);
};

