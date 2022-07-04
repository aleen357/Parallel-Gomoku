#include "Parallel_ABAutoPlayer.h"
#include <omp.h>
#include<iostream>

#include<fstream>

using namespace std;
float time_array;
#define DEPTH 3

int Parallel_ABAutoPlayer::Parallel_ABMinMax(Gomoku GameBoard, bool isComputer, int depth, int alpha, int beta)
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
			score = Parallel_ABMinMax(copyGame, false, depth, alpha, beta);
            #pragma omp critical
			if (score > Bestscore)
			{
				Bestscore = score;
			}
            #pragma omp critical
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
			score = Parallel_ABMinMax(copyGame, true, depth, alpha, beta);
            #pragma omp critical
			{
				if (score < Bestscore)
				{
					Bestscore = score;
				}


				if (Bestscore < beta) beta = Bestscore;
			}
				if (beta <= alpha) break;
			
		}
		return Bestscore;
	}

}
int Parallel_ABAutoPlayer::FindBestMove(Gomoku GameBoard, int depth)
{
	int score = 0;
	int index = 0;
	int BestScore = INT_MIN;
	int BestMove = 0;//best index to place piece on
	auto moves = GameBoard.AvailableMove();
	auto size_moves = moves.size();
	//these are moves for original game board..we will call minmax for all of these and the
	//one which returns best score is the best move

	int p = omp_get_num_procs();
	omp_set_num_threads(p);

	//omp_set_nested(1);
	auto start = omp_get_wtime();
#pragma omp parallel for schedule(static) private(index, score) shared(BestScore, BestMove) num_threads(2)
	for (index=0;index<(int)moves.size();index++)
	{
		GameBoard.ExecuteMove(moves[index]);//execute this move on gameBoard
		//make a copy of gameboard
		Gomoku copyGame;
		copyGame = GameBoard;
		//undo on original board
		GameBoard.UndoMove(moves[index]);
		score = Parallel_ABMinMax(copyGame, false, depth, INT_MIN, INT_MAX);
        #pragma omp critical
		if (score > BestScore)
		{
			BestScore = score;
			BestMove = moves[index];
		}
	}
	auto stop = omp_get_wtime();
	auto duration = stop - start;
	time_array = duration;
	//file handling
	ofstream fout;
	fout.open("ABParallel-staitc0-2p-D3.txt", std::ios_base::app);
	if (fout.is_open())
	{

		fout << size_moves << " " << time_array << endl;
		fout.close();
	}
	
	return BestMove;
}