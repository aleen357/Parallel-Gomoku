#pragma once
#include "Game_Runner.h"

class SeqAutoPlayer:public GameRunner
{
	int SeqMinMax(Gomoku GameBoard, bool isComputer, int depth);
	int FindBestMove(Gomoku GameBoard, int depth);
};

