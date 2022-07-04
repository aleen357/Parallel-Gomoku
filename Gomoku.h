#pragma once
#include <vector>
#include <array>
#include<iostream>
using namespace std;
#define BOARD_LEN 15
//gomoku has a board
//Each board block has status: empty, Computer, human
//


class Gomoku
{
	
public:

	enum gameStatus {
		HumanWins,
		ComputerWins,
		Tie,
		statHumanTurn,
		statComputerTurn
	};

	enum turn {
		computerTurn = 0,
		humanTurn = 1
	};


	enum tile_status {
		empty,
		human,
		computer
	};
	array<tile_status, BOARD_LEN* BOARD_LEN> G_board;
	turn curr_turn;
	gameStatus status;

	Gomoku();
	vector<int> AvailableMove();
	int EvaluateLeaf();
	bool ExecuteMove(int index);
	bool UndoMove(int index);
	gameStatus changeStatus();
	void displayGame();
	

	
};

