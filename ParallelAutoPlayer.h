#pragma once
#include "Game_Runner.h"
class ParallelAutoPlayer :public GameRunner
{
	int Para_MinMax(Gomoku GameBoard, bool isComputer, int depth);//A simple OMP For
	int FindBestMove(Gomoku GameBoard, int depth);
};