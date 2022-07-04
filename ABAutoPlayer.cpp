#include "ABAutoPlayer.h"
#include<iostream>
#include <chrono>
#include<fstream>

using namespace std::chrono;
using namespace std;
int time_array0[1];
#define DEPTH 3

int ABAutoPlayer::ABMinMax(Gomoku GameBoard, bool isComputer, int depth, int alpha, int beta)
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
			depth = depth - 1;
			score = ABMinMax(copyGame, false, depth , alpha, beta);
			if (score > Bestscore)
			{
				Bestscore = score;
			}
			if (Bestscore > alpha) alpha = Bestscore;
			if (beta <= alpha) break;
		}
		return Bestscore;
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
			depth = depth - 1;
			score = ABMinMax(copyGame, true, depth, alpha, beta);
			if (score < Bestscore)
			{
				Bestscore = score;
			}
			if (Bestscore < beta) beta = Bestscore;
			if (beta <= alpha) break;
		}
		return Bestscore;
	}

}
int ABAutoPlayer::FindBestMove(Gomoku GameBoard, int depth)
{
	int score = 0;
	int BestScore = INT_MIN;
	int BestMove = 0;//best index to place piece on
	auto moves = GameBoard.AvailableMove();
	//these are moves for original game board..we will call minmax for all of these and the
	//one which returns best score is the best move
	auto start = high_resolution_clock::now();
	for (auto& it : moves) {
		GameBoard.ExecuteMove(it);//execute this move on gameBoard
		//make a copy of gameboard
		Gomoku copyGame;
		copyGame = GameBoard;
		//undo on original board
		GameBoard.UndoMove(it);
		score = ABMinMax(copyGame, false, depth, INT_MIN, INT_MAX);
		if (score > BestScore)
		{
			BestScore = score;
			BestMove = it;
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	
	time_array0[1] = duration.count();
	//file handling
	ofstream fout;
	fout.open("ABMinmax.txt", std::ios_base::app);
	if (fout.is_open())
	{
		fout << time_array0[1] << " ";
		fout.close();
	}
	
	return BestMove;
}