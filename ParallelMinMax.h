#pragma once
#include "Game_Runner.h"
class ParallelAutoPlayer:public Game_Runner
{
	int Para_MinMax(Gomoku GameBoard, bool isComputer, int depth);//A simple OMP For
	int FindBestMove(Gomoku GameBoard, int depth);
};

