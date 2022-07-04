#include "Gomoku.h"
#include <vector>
#include <array>
#include<iostream>
#include<time.h>
#include<Windows.h>
#define BOARD_LEN 15

using namespace std;

Gomoku::Gomoku()
{
	int index = 0;
	for (int i = 0; i < BOARD_LEN*BOARD_LEN; i++)
	{
		G_board[i] = empty;
	}
	
}
vector<int> Gomoku::AvailableMove()
{
	vector<int> Moves;
	for (int r = 0; r < BOARD_LEN; ++r) {
		for (int c = 0; c < BOARD_LEN; ++c) {
			if (G_board[r * BOARD_LEN + c] == empty) {
				Moves.push_back((r * BOARD_LEN) + c);
			}
		}
	}
	if (Moves.size() == 0)
	{
		//no moves left
		this->status = Tie;
		
	}
	return Moves;

}
Gomoku::gameStatus Gomoku::changeStatus()
{
	int score = EvaluateLeaf();
	if (score == INT_MAX)
	{
		
		this->status= ComputerWins;
	}
	else
		if (score == INT_MIN)
		{
			this->status=HumanWins;
		}
	//change turns
	for (int i = 0; i < BOARD_LEN; i++)
	{
		if (G_board[i] == empty)
		{
			if (curr_turn == statHumanTurn)
				return statComputerTurn;
			else
				return statHumanTurn;
		}
	}
	return Tie;

}
int Gomoku::EvaluateLeaf()
//{
//	//{
//	//	bool block_adv = false;
//	//	bool once = false; //the first time for a main piece
//	//	int totalScore = 0;
//	//	int scoreOP = 0;
//	//	int index = 0;
//	//	int newRow=0;
//	//	int newCol = 0;
//	//	int newIndex = 0;
//	//	int score = 0;//indvidual tile scores
//	//	bool blocked = false;
//	//	//current turn=computer always in this case
//	//	//we will go through each tile to calc N in row combinations
//	//	for (int i = 0; i < BOARD_LEN; i++)
//	//	{
//	//		for (int j = 0; j < BOARD_LEN; j++)
//	//		{
//	//			if (i == 0 && j == 1)
//	//				int yes = 0;
//	//			once = false;
//	//			scoreOP = 0;
//	//			index = (i * BOARD_LEN) + j;
//	//			if (G_board[index] == empty)
//	//				continue;
//	//			if (G_board[index] == human)
//	//				scoreOP = -1;
//	//			if (G_board[index] == computer)
//	//				scoreOP = 1;
//	//
//	//			tile_status copy_tile = G_board[index];
//	//
//	//			//for moving in 8 directions
//	//			if (scoreOP == 0)
//	//				continue;
//	//			//1=left,2=right, up, down, diagonal up-left, diagonal up-right,diagonal down-left, diagonal down-right, 
//	//			//e.g diagonal up-left -1 row -1 column
//	//			for (int r = -1; r <= 1; r++)
//	//			{
//	//				for (int c = -1; c <= 1; c++)
//	//				{
//	//					if (r == 0 && c == 0)//00 has no direction
//	//						continue;
//	//
//	//					//we see if in the certain direction five places possible in this direction
//	//					int limit_r = i + (5 * r);
//	//					int limit_c = j + (5 * c);
//	//					if (limit_r > BOARD_LEN || limit_c > BOARD_LEN)
//	//						continue;
//	//					if (limit_r + 1 < 0 || limit_c + 1 < 0)
//	//						continue;
//	//					score = 1;
//	//					blocked = false;
//	//					for(int count=1;count<5;count++)
//	//					{
//	//						newRow = i + (r * count);
//	//						newCol = j + (c * count);
//	//						newIndex = (newRow * BOARD_LEN) + newCol;
//	//						if (G_board[newIndex] == copy_tile )
//	//						{
//	//							score++;
//	//						}
//	//						else if (G_board[newIndex] != copy_tile && G_board[newIndex]!=empty)
//	//						{
//	//							//this lane is blocked
//	//							blocked = true;
//	//							break;
//	//						}				
//	//					}	
//	//					if (score == 5)//winnig score in an individual tile
//	//					{
//	//						if (copy_tile == human)
//	//						{
//	//							return INT_MIN;
//	//						}
//	//						if (copy_tile == computer)
//	//						{
//	//							return INT_MAX;
//	//						}
//	//					}
//	//					if (!blocked && score>1)
//	//					{
//	//					
//	//						
//	//						if (score >= 2)
//	//						{
//	//							score = score+2;//increased threat
//	//						}
//	//						totalScore = totalScore + (scoreOP * score);
//	//						once = true;
//	//
//	//					}
//	//					/*
//	//					if (score==1 && once==false)
//	//					{
//	//						totalScore = totalScore + (scoreOP * score);
//	//						once = true;
//	//					}*/
//	//				}
//	//
//	//			}
//	//			
//	//			
//	//		}
//	//
//	//	}
//	//	return totalScore;
//	//
//
//	//int totalScore_enemy = 0;//calculates score of enemy on current gameboard
//	//int totalScore_player = 0;//score of current player
//	//int totalScore = 0;//difference of enemy and player
//	//int finalMultiplier = 0;
//	//int scoreOP = 0;
//	//int index = 0;
//	//int newRow = 0;
//	//int newCol = 0;
//	//int newIndex = 0;
//	//int score = 0;//indvidual tile scores
//	//bool blocked = false;
//	////current turn=computer always in this case
//	////we will go through each tile to calc N in row combinations
//	//for (int i = 0; i < BOARD_LEN; i++)
//	//{
//	//	for (int j = 0; j < BOARD_LEN; j++)
//	//	{
//	//		scoreOP = 0;
//	//		index = (i * BOARD_LEN) + j;
//	//		if (G_board[index] == empty)
//	//			continue;
//	//		if (G_board[index] == human)
//	//			scoreOP = -1;
//	//		if (G_board[index] == computer)
//	//			scoreOP = 1;
//
//	//		tile_status copy_tile = G_board[index];
//
//	//		//for moving in 8 directions
//	//		if (scoreOP == 0)
//	//			continue;
//	//		//1=left,2=right, up, down, diagonal up-left, diagonal up-right,diagonal down-left, diagonal down-right, 
//	//		//e.g diagonal up-left -1 row -1 column
//	//		for (int r = -1; r <= 1; r++)
//	//		{
//	//			for (int c = -1; c <= 1; c++)
//	//			{
//	//				if (r == 0 && c == 0)//00 has no direction
//	//					continue;
//
//	//				//we see if in the certain direction five places possible in this direction
//	//				int limit_r = i + (5 * r);
//	//				int limit_c = j + (5 * c);
//	//				if (limit_r > BOARD_LEN || limit_c > BOARD_LEN)
//	//					continue;
//	//				if (limit_r + 1 < 0 || limit_c + 1 < 0)
//	//					continue;
//	//				score = 1;
//	//				blocked = false;
//	//				for (int count = 1; count < 5; count++)
//	//				{
//	//					newRow = i + (r * count);
//	//					newCol = j + (c * count);
//	//					newIndex = (newRow * BOARD_LEN) + newCol;
//	//					if (G_board[newIndex] == copy_tile)
//	//					{
//	//						score++;
//	//					}
//	//					else if (G_board[newIndex] != copy_tile && G_board[newIndex] != empty)
//	//					{
//	//						//this lane is blocked
//	//						blocked = true;
//	//						finalMultiplier = 0;
//	//						break;
//	//					}
//	//				}
//	//				if (score == 5)//winnig score in an individual tile
//	//				{
//	//					if (copy_tile == human)
//	//					{
//	//						return INT_MIN;
//	//					}
//	//					if (copy_tile == computer)
//	//					{
//	//						return INT_MAX;
//	//					}
//	//				}
//	//				if (!blocked)
//	//				{
//	//					if ((curr_turn == computerTurn && copy_tile == computer) && (curr_turn == humanTurn && copy_tile == human))
//	//					{
//
//	//						totalScore_player = totalScore_player + 2 * score;
//	//					}
//	//					else if ((curr_turn == computerTurn && copy_tile == human) && (curr_turn == humanTurn && copy_tile == computer))
//	//					{
//
//	//						totalScore_enemy = totalScore_enemy + 2 * score;
//	//					}
//
//	//				}
//	//			}
//
//	//		}
//
//
//	//	}
//
//	//}
//	//totalScore = totalScore_player - totalScore_enemy;
//	//return totalScore;
{
	int possibility_score = 8;
	int totalScore_enemy = 0;//calculates score of enemy on current gameboard
	int totalScore_player = 0;//score of current player
	int totalScore = 0;//difference of enemy and playerb
	int finalMultiplier = 0;
	int scoreOP = 0;
	int index = 0;
	int newRow = 0;
	int newCol = 0;
	int newIndex = 0;
	int score = 0;//indvidual tile scores
	bool blocked = false;
	bool chain = true;
	int additional = 0;
	int chainScore = 0;
	bool second_chain = false;
	int secondchain_count = 0;
	//current turn=computer always in this case
	//we will go through each tile to calc N in row combinations
	for (int i = 0; i < BOARD_LEN; i++)
	{
		for (int j = 0; j < BOARD_LEN; j++)
		{
			scoreOP = 0;
			possibility_score = 8;
			index = (i * BOARD_LEN) + j;
			if (G_board[index] == empty)
				continue;
			if (G_board[index] == human)
				scoreOP = -1;
			if (G_board[index] == computer)
				scoreOP = 1;

			tile_status copy_tile = G_board[index];

			//for moving in 8 directions
			if (scoreOP == 0)
				continue;
			//1=left,2=right, up, down, diagonal up-left, diagonal up-right,diagonal down-left, diagonal down-right, 
			//e.g diagonal up-left -1 row -1 column
			for (int r = -1; r <= 1; r++)
			{
				for (int c = -1; c <= 1; c++)
				{
					if (r == 0 && c == 0)//00 has no direction
						continue;

					//we see if in the certain direction five places possible in this direction
					int limit_r = i + (5 * r);
					int limit_c = j + (5 * c);
					if (limit_r > BOARD_LEN || limit_c > BOARD_LEN)
					{
						possibility_score--;
						continue;
					}
					if (limit_r + 1 < 0 || limit_c + 1 < 0)
					{
						possibility_score--;
						continue;
					}
					score = 1;
					blocked = false;
					finalMultiplier = 1;
					chain = true;
					additional = 0;
					chainScore = 0;
					second_chain = false;
					secondchain_count = 0;
					for (int count = 1; count < 5; count++)
					{
						newRow = i + (r * count);
						newCol = j + (c * count);
						newIndex = (newRow * BOARD_LEN) + newCol;
						if (G_board[newIndex] == copy_tile)
						{
							score++;
						}
						else if (G_board[newIndex] != copy_tile && G_board[newIndex] != empty)
						{
							//this lane is blocked
							blocked = true;
							finalMultiplier = 0;
							break;
						}
						if (G_board[newIndex] == empty && chain == true)
						{
							chain = false;
							second_chain = true;
							additional++;

						}
						if (chain == false && second_chain == true && G_board[newIndex] == empty)
						{
							second_chain = false;
							additional++;
						}
						else if (chain == false && second_chain == true && G_board[newIndex] == copy_tile)
						{
							secondchain_count++;

						}
					}
					if (score >= 5)//winnig score in an individual tile
					{
						if ((copy_tile == human && curr_turn == computerTurn) || (copy_tile == computer && curr_turn == humanTurn))
						{
							return INT_MAX;
						}
						if ((copy_tile == human && curr_turn == humanTurn) || (copy_tile == computer && curr_turn == computerTurn))
						{
							return INT_MIN;
						}
					}
					//if (score >= 5)//winnig score in an individual tile
					//{
					//	if (copy_tile == human)
					//	{
					//		return INT_MIN;
					//	}
					//	if (copy_tile == computer )
					//	{
					//		return INT_MAX;
					//	}
					//}

					if (secondchain_count == 2)
					{

						finalMultiplier = 4;
					}
					else if (score == 4)
					{
						finalMultiplier = 3;
					}
					else if (score == 3)
					{
						finalMultiplier = 2;
					}
					else
						finalMultiplier = 1;
					chainScore = score - additional;//any additional 
					if (!blocked)
					{
						if ((curr_turn == computerTurn && copy_tile == computer) || (curr_turn == humanTurn && copy_tile == human))
						{
							totalScore_player = totalScore_player + finalMultiplier * score;
						}
						else if ((curr_turn == computerTurn && copy_tile == human) || (curr_turn == humanTurn && copy_tile == computer))
						{

							totalScore_enemy = totalScore_enemy + finalMultiplier * score;
						}

					}
					if (blocked)
					{
						possibility_score--;
					}
				}

			}
			if ((curr_turn == computerTurn && copy_tile == computer) && (curr_turn == humanTurn && copy_tile == human))
			{
				totalScore_player += possibility_score * 2;
			}
			else if ((curr_turn == computerTurn && copy_tile == human) && (curr_turn == humanTurn && copy_tile == computer))
			{

				totalScore_enemy += possibility_score * 2;
			}

		}

	}
	totalScore = totalScore_player - totalScore_enemy;
	return totalScore;


}
bool Gomoku::ExecuteMove(int index)
{
	if (curr_turn == 0)
	{
		//computer's turn
		G_board[index] = computer;
	}
	else
	{
		//human's turn
		G_board[index] = human;
	}
	if (curr_turn == 0)
	{
		this->status = statHumanTurn;
		curr_turn = humanTurn;
	}
	else
	{
		this->status = statComputerTurn;
		curr_turn = computerTurn;
	}

	return 1;
}
bool Gomoku::UndoMove(int index)
{
	G_board[index] = empty;
	if (curr_turn == 0)
	{
		this->status = statHumanTurn;
		curr_turn = humanTurn;
	}
	else
	{
		this->status = statComputerTurn;
		curr_turn = computerTurn;
	}
	return 1;
}
void Gomoku::displayGame()
{
	system("CLS");
	int index = 0;
	if (status == statHumanTurn)
		cout << "Human Turn" << endl;
	else if (status == statComputerTurn)
		cout << "Computer Turn" << endl;
	else if (status == HumanWins)
		cout << "human wins" << endl;
	else if (status == ComputerWins)
		cout << "computer wins" << endl;
	else
		cout << "TIE....GameOver" << endl;
	//to display the game board and status
	for (int i = 0; i < BOARD_LEN; i++)
	{
		cout << "   ";
		for (int j = 0; j < BOARD_LEN; j++)
		{
			cout << "|";
			index = (i * BOARD_LEN) + j;
			if (G_board[index] == human)
				cout << " O ";
			else
				if (G_board[index] == computer)
					cout << " X ";
				else
					cout << "   ";

		}
		cout << endl << "   -------------------------------------------------------------------------" << endl;
	}
	

}