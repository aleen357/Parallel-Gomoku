#pragma once
#include "Gomoku.h"
class GameRunner {

public:
	
	// Determines and plays the best move for the current state.


	virtual int FindBestMove(Gomoku GameBoard, int depth)=0;//if i want to replace it with parallel minimax, alpha beta minimax..etc..
	//so we make it a virtual class
	//FindBestMove=Minimax

};
