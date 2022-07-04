# Parallel-Gomoku
Gomoku with auto player using minimax and alpha beta pruning. Incorporated parallelization using OpenMp.

INTRODUCTION:
Our project focus was to implement Auto Player for the Gomoku game and use parallelization
techniques to achieve speedup in-game tree evaluation. We implemented the game using
sequential minimax, and Alpha-Beta pruning and then compared them with the parallelized
versions created using openMP to achieve the best possible speedup.

Gomoku:
Gomoku is a version of tic tac toe in which we have a grid of 19 x 19 and the player has to
make a pattern of 5 of his pieces vertically, diagonally, or horizontally.
Class Gomoku:
An array of sizes of Board length and type Tile Status is a representation of the board.
Tile status shows three states of a point: empty, computer piece, human piece GameStatus
shows the current status of the game which could be Human Turn, Computer Turn, Human
Wins, Computer Wins, Tie
● Gomoku(): The array is initialized with all tiles status set to empty
● AvailableMove(): Returns an int vector array with all the indexes possible for a turn. ●
EvaluateLeaf(): Returns score for a specific gameBoard state
● ExecuteMove(int index): Takes an index to place the player’s piece and changes the turns.
● UndoMove(int index):Makes the index empty and changes turns and status. ●
changeStatus(): Changes the status of game.
● displayGame(): Displays current game board with computer piece as ‘X’ and human’s as ‘O’
and empty tiles as spaces.
Auto Players:
● Simple Minimax: This class runs a simple minimax algorithm for game tree search.
Another class Parallel_Minimax parallelizes this algorithm using openMP.
● Alpha-Beta Autoplayer: This class implements sequential alpha beta pruning on simple
minimax algorithm. Parallel AB Autoplayer parallelizes this algorithm.
Human Player:
This class has one function which takes input from human
GamePlay:
● GameOver():Returns 1 if game has reached a terminal state: Human ins, Computer Wins,
Tie
● PlayGame(): Alternates between human and compute. Auto player child is created
depending on algorithm you would like to use. If it is computer turn we call FindBestMove of
that child Autoplayer which returns an index for move to playgame. The move is then
executed.
● If it is human’s turn it takes, input of move from human and returns that to PlayGame and it is
sent as a parameter when calling gomoku execute move.
● This is a loop which continues while gameOver does not return 1.

