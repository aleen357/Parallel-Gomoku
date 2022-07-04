#include "ParallelAutoPlayer.h"
#include<omp.h>
#include<iostream>
#include<fstream>
//#include <chrono>
//using namespace std::chrono;
using namespace std;
float time_array2;


int ParallelAutoPlayer::Para_MinMax(Gomoku GameBoard, bool isComputer, int depth)
{
	int index;
	int Bestscore_m;
	int score = 0;
	auto moves = GameBoard.AvailableMove();
	score = GameBoard.EvaluateLeaf();
	if ((score == INT_MAX) || (score == INT_MIN) || (GameBoard.status == Gomoku::Tie) || (depth <= 0))
	{
		//this is a terminal state we return score
		
		return score;
	}

	
		if (isComputer) {
			int Bestscore_m = INT_MIN;
 //#pragma omp for schedule(static, 1) 
			for (index = 0; index < (int)moves.size(); index++)
			{
				GameBoard.ExecuteMove(moves[index]);//execute this move on gameBoard
				//make a copy of gameboard
				Gomoku copyGame;
				copyGame = GameBoard;
				//undo on original board
				GameBoard.UndoMove(moves[index]);
				depth = depth - 1;
				score = Para_MinMax(copyGame, false, depth);
                #pragma omp critical
				if (score > Bestscore_m)
				{
					Bestscore_m = score;
				}

			}
			return Bestscore_m;

		}
		else
		{
			Bestscore_m = INT_MAX;
         
			for (index = 0; index < (int)moves.size(); index++)
			{
				GameBoard.ExecuteMove(moves[index]);//execute this move on gameBoard
				//make a copy of gameboard
				Gomoku copyGame;
				copyGame = GameBoard;
				//undo on original board
				GameBoard.UndoMove(moves[index]);
				depth = depth - 1;
				score = Para_MinMax(copyGame, true, depth);
                #pragma omp critical
				if (score < Bestscore_m)
				{
					Bestscore_m = score;
				}

			}
			return Bestscore_m;



		}
	
}
	   
int ParallelAutoPlayer::FindBestMove(Gomoku GameBoard, int depth)
{
	int score = 0;
	int BestScore = INT_MIN;
	int BestMove = 0;//best index to place piece on
	auto moves = GameBoard.AvailableMove();
	auto size_moves = moves.size();
	int index;
	int id;
	//these are moves for original game board..we will call minmax for all of these and the
	//one which returns best score is the best move
	//int p = omp_get_num_procs();
	//int p = 12;
	//omp_set_num_threads(p);

	//omp_set_nested(1);
	auto start = omp_get_wtime();

#pragma omp parallel for schedule(static,10) private(index, score) shared(BestScore, BestMove) num_threads(12)
	for (index = 0; index < (int)moves.size(); index++)
	{
		score = 0;
		id = omp_get_thread_num();
		int x = omp_get_num_threads();
		GameBoard.ExecuteMove(moves[index]);//execute this move on gameBoard
		//make a copy of gameboard
		Gomoku copyGame;
		copyGame = GameBoard;
		//undo on original board
		GameBoard.UndoMove(moves[index]);
		score = Para_MinMax(copyGame, false, depth);
#pragma omp critical
		if (score > BestScore)
		{
			BestScore = score;
			BestMove = moves[index];
		}
	}

	auto stop = omp_get_wtime();
	float duration = stop - start;
	time_array2 = duration;
	ofstream fout;
	fout.open("ParallelMinMax-static10-12p-D2.txt", std::ios_base::app);

	if (fout.is_open())
	{

		fout << size_moves << " " << time_array2 << endl;
		fout.close();
	}

	return BestMove;
}