#include "GamePlay.h"
#include<time.h>
#include "Gomoku.h"
#include<iostream>
#include<Windows.h>
#include "SeqAutoPlayer.h"
#include "ParallelAutoPlayer.h"
#include "ABAutoPlayer.h"
#include "Parallel_ABAutoPlayer.h"
using namespace std;
GamePlay::GamePlay(int x)
{
	if (x == 1)
	{
		//seq minimax
		AutoPlayer = new  Parallel_ABAutoPlayer;
		//HumanPlayer = new ParallelAutoPlayer;
		HPlayer = new Parallel_ABAutoPlayer;
	}
	//determine first turn so if it is computer we can randomly pick a move from center
	int index = 0;
	srand((unsigned)time(NULL));
	int t = rand() % 2;
	if (t == 0)
	{
		GomokuVer.status=Gomoku::statComputerTurn;
		GomokuVer.curr_turn =Gomoku::computerTurn;
		////if it is computer turn rather than seeing all the possible space we assign a random block from mid values
		//int first_possible = (BOARD_LEN - 1) / 2;
		////we can choose from 5 rows back and 5 rows front also any 5 col up or 5 col down
		//int r_rightLimit = first_possible - 4;
		//int c_upLimit = r_rightLimit;
		//int r_leftLimit = first_possible + 4;
		//int c_downLimit = r_leftLimit;
		//for row rand
		int rand_row = 1 + ((rand() % (BOARD_LEN-1)) + 0 - 1);
		//random col
		int rand_col = 1 + ((rand() % (BOARD_LEN - 1)) + 0 - 1);
		index = (rand_row * BOARD_LEN) + rand_col;
		GomokuVer.displayGame();
		
		Sleep(100);
		GomokuVer.ExecuteMove(index);
		GomokuVer.displayGame();
	}
	else
		if (t == 1)
		{
			GomokuVer.status = Gomoku::statHumanTurn;
			GomokuVer.curr_turn = Gomoku::humanTurn;
			//int rand_row = 1 + ((rand() % (BOARD_LEN - 1)) + 0 - 1);
			////random col
			//int rand_col = 1 + ((rand() % (BOARD_LEN - 1)) + 0 - 1);
			//index = (rand_row * BOARD_LEN) + rand_col;
			//GomokuVer.displayGame();

			//Sleep(100);
			//GomokuVer.ExecuteMove(index);
			//GomokuVer.displayGame();
			int rand_row = 1 + ((rand() % (BOARD_LEN - 1)) + 0 - 1);
			//random col
			int rand_col = 1 + ((rand() % (BOARD_LEN - 1)) + 0 - 1);
			index = (rand_row * BOARD_LEN) + rand_col;
			GomokuVer.displayGame();
			Sleep(100);
			GomokuVer.ExecuteMove(index);
		}
	GomokuVer.displayGame();
	this->StartGame();
}
void GamePlay::StartGame()//play game until game over
{
	int x;
	cout << "enter depth: ";
	cin >> x;
	this->depth=x;
	while (!GameOver())
	{
		if (GomokuVer.curr_turn == Gomoku::computerTurn)
		{
			//autoplayer is called a best move is got and executed
			int index = AutoPlayer->FindBestMove(GomokuVer, depth);
			GomokuVer.ExecuteMove(index);

		}
		else if (GomokuVer.curr_turn == Gomoku::humanTurn)
		{
			//human 
			int index=HPlayer->FindBestMove(GomokuVer, depth);
			GomokuVer.ExecuteMove(index);

		}

		GomokuVer.displayGame();

	}
	GomokuVer.changeStatus();
	GomokuVer.displayGame();
}
bool GamePlay::GameOver()//in case of tie or return of int max or min
{
	int score = GomokuVer.EvaluateLeaf();
	if (score == INT_MIN || score == INT_MAX || GomokuVer.status == Gomoku::Tie)
	{
		
		return 1;
	}
	else
		return 0;
}