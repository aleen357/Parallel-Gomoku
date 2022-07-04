#include "HumanPlayer.h"
#include<iostream>
#define BOARD_LEN 15
using namespace std;
int HumanPlayer::FindBestMove(Gomoku GameBoard, int depth)
{
	int row;
	int col;
	cout << "Human Player enter row: ";
	cin >> row;
	cout << endl;
	cout << "Human Player enter col: ";
	cin >> col;
	cout << endl;
	int index = (row * BOARD_LEN) + col;
	return index;
}