#include "ParallelAutoPlayer.h"
#include<iostream>
using namespace std;

int ParallelAutoPlayer::SeqMinMax(Gomoku GameBoard, bool isComputer, int depth)
{
	int Bestscore;
	int score = 0;
	auto moves = GameBoard.AvailableMove();
	score = GameBoard.EvaluateLeaf();
	if ((score == INT_MAX) || (score == INT_MIN) || (GameBoard.status == Gomoku::Tie) || depth <= 0)
	{
		//this is a terminal state we return score

		return score;
	}


	if (isComputer) {
		int Bestscore = INT_MIN;
		for (auto& it : moves) {
			GameBoard.ExecuteMove(it);//execute this move on gameBoard
			//make a copy of gameboard
			Gomoku copyGame;
			copyGame = GameBoard;
			//undo on original board
			GameBoard.UndoMove(it);
			score = SeqMinMax(copyGame, false, depth - 1);
			if (score > Bestscore)
			{
				Bestscore = score;
			}
			return Bestscore;
		}
	}
	else
	{
		Bestscore = INT_MAX;
		for (auto& it : moves) {
			GameBoard.ExecuteMove(it);//execute this move on gameBoard
			//make a copy of gameboard
			Gomoku copyGame;
			copyGame = GameBoard;
			//undo on original board
			GameBoard.UndoMove(it);
			score = SeqMinMax(copyGame, true, depth - 1);
			if (score < Bestscore)
			{
				Bestscore = score;
			}
			return Bestscore;
		}

	}

}
int SeqAutoPlayer::FindBestMove(Gomoku GameBoard, int depth)
{
	int score = 0;
	int BestScore = INT_MIN;
	int BestMove = 0;//best index to place piece on
	auto moves = GameBoard.AvailableMove();
	//these are moves for original game board..we will call minmax for all of these and the
	//one which returns best score is the best move
	for (auto& it : moves) {
		GameBoard.ExecuteMove(it);//execute this move on gameBoard
		//make a copy of gameboard
		Gomoku copyGame;
		copyGame = GameBoard;
		//undo on original board
		GameBoard.UndoMove(it);
		score = SeqMinMax(copyGame, true, depth);
		if (score > BestScore)
		{
			BestScore = score;
			BestMove = it;
		}
	}
	return BestMove;
}