#include "SeqAutoPlayer.h"
#include<iostream>
#include<fstream>
#include<omp.h>

using namespace std;

float time_array3;


int SeqAutoPlayer::SeqMinMax(Gomoku GameBoard, bool isComputer, int depth2)
{
	int newDepth;
	int Bestscore;
	int score=0;
	auto moves = GameBoard.AvailableMove();
	score = GameBoard.EvaluateLeaf();
	if((score == INT_MAX) || (score==INT_MIN) || (GameBoard.status==Gomoku::Tie)|| (depth2<=0))
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
			depth2 = depth2 - 1;
			score = SeqMinMax(copyGame, false, depth2);
			if (score > Bestscore)
			{
				Bestscore = score;
			}
			
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
			depth2 = depth2 - 1;
			score = SeqMinMax(copyGame, true, depth2);
			if (score < Bestscore)
			{
				Bestscore = score;
			}
			
		}
		return Bestscore;

	}

}
int SeqAutoPlayer::FindBestMove(Gomoku GameBoard, int depth)
{
	int score = 0;
	int BestScore = INT_MIN;
	int BestMove = 0;//best index to place piece on
	auto moves = GameBoard.AvailableMove();
	auto size_moves = moves.size();
	//these are moves for original game board..we will call minmax for all of these and the
	//one which returns best score is the best move
	auto start = omp_get_wtime();
	for (auto& it : moves) {
		GameBoard.ExecuteMove(it);//execute this move on gameBoard
		//make a copy of gameboard
		Gomoku copyGame;
		copyGame = GameBoard;
		//undo on original board
		GameBoard.UndoMove(it);
		score = SeqMinMax(copyGame, false, depth);
		if (score > BestScore)
		{
			BestScore = score;
			BestMove = it;
		}
	}
	auto stop = omp_get_wtime();
	auto duration = stop - start;
	////
	time_array3= duration;
	ofstream fout;
	fout.open("SeqMinMax.txt", std::ios_base::app);
	if (fout.is_open())
	{
		fout << size_moves << " " << time_array3 << endl;
		fout.close();
	}
	
	
	////
	return BestMove;
}