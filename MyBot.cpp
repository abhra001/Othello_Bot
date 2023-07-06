/*
* @file botTemplate.cpp
* @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
* @date 2010-02-04
* Template for users to create their own bots
*/

#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include <cstdlib>
using namespace std;
using namespace Desdemona;

class MyBot: public OthelloPlayer
{
    public:
        /**
         * Initialisation routines here
         * This could do anything from open up a cache of "best moves" to
         * spawning a background processing thread. 
         */
        MyBot( Turn turn );

        /**
         * Play something 
         */
        virtual Move play( const OthelloBoard& board );
    private:
};

MyBot::MyBot( Turn turn )
    : OthelloPlayer( turn )
{
}

int eval(int x, int y);
int eval_board(const OthelloBoard& board, Turn turn);
int minimax(const OthelloBoard& board, int depth, bool player, Turn turn);
int alphabeta(const OthelloBoard& board, int depth, bool player, Turn turn, int alpha, int beta);

Move MyBot::play( const OthelloBoard& board )
{
    list<Move> moves = board.getValidMoves( turn );
    //int randNo = rand() % moves.size();
    list<Move>::iterator it = moves.begin();
    int n=int(moves.size());
    
    Move bestMove=*it;
    int bestVal=-10000;
    int alpha=-10000;
    int beta=10000;
    //for (int i=0; i<n; it++, i++)
    //{
    //	Move move=*it;
    //	if (v>bestVal)
    //	{
    //		bestMove=*it;
    //		bestVal=v;
    //	}
    //}
    for (int i=0; i<n; it++, i++)
    {
    	OthelloBoard newBoard=board;
	Move move=*it;
	newBoard.makeMove(turn,move);
	int v=alphabeta(newBoard,5,false,other(turn),alpha,beta);
	//if (turn==BLACK)
	//{
	//	int v=minimax(newBoard,3,false,other(turn));
	//}
	//else
	//{
	//	int v=minimax(newBoard,3,true,other(turn));
	//}
	if (v>bestVal)
		{
			bestVal=v;
			bestMove=move;
		}
    }
    return bestMove;
    
    //for (int i=0; i<=1; i++)
    //{
    //	for (int j=0; j<=1; j++)
    //	{
    //		if (board.validateMove(turn,i*7,j*7)) // Replace with board size
    //		{
    //			return Move(i*7,j*7);
    //		}
    //	}
    //}
    
    //for (int i=0; i<n; it++, i++)
    //{
    //	Move move=*it;
    //	if (move.x==0 or move.x==7) // Replace with board size
    //	{
    //		return *it;
    //	}
    //	if (move.y==0 or move.y==7) // Replace with board size
    //	{
    //		return *it;
    //	}
    //}
    
    //list<Move>::iterator itr = moves.begin();
    //for (int i=0; i<randNo; itr++, i++);
    //return *itr;
}

int eval(int x, int y)
{
	int val[8][8]={{1000,-10,10,10,10,10,-10,1000},{-10,-10,1,1,1,1,-10,-10},{10,1,1,1,1,1,1,10},{10,1,1,1,1,1,1,10},{10,1,1,1,1,1,1,10},{10,1,1,1,1,1,1,10},{-10,-10,1,1,1,1,-10,-10},{1000,-10,10,10,10,10,-10,1000}};
	return val[x][y];
}

int eval_board(const OthelloBoard& board, Turn turn)
{
	int val[8][8]={{1000,-10,10,10,10,10,-10,1000},{-10,-10,1,1,1,1,-10,-10},{10,1,1,1,1,1,1,10},{10,1,1,1,1,1,1,10},{10,1,1,1,1,1,1,10},{10,1,1,1,1,1,1,10},{-10,-10,1,1,1,1,-10,-10},{1000,-10,10,10,10,10,-10,1000}};
	int v=0;
	if (turn==BLACK)
	{
		for( int i = 0; i<8; i++ )
		{
			for( int j = 0; j<8; j++ )
			{
				if (board.get(i,j)==BLACK)
				{
					v=v+val[i][j];
				}
				if (board.get(i,j)==RED)
				{
					v=v-val[i][j];
				}
			}
		}
	}
	else
	{
		for( int i = 0; i<8; i++ )
		{
			for( int j = 0; j<8; j++ )
			{
				if (board.get(i,j)==RED)
				{
					v=v+val[i][j];
				}
				if (board.get(i,j)==BLACK)
				{
					v=v-val[i][j];
				}
			}
		}
	}
	return v;
}

int minimax(const OthelloBoard& board, int depth, bool player, Turn turn)
{
	if (depth==0)
	{
		return eval_board(board, turn);
	}
	if (player)
	{
		int bestVal=-10000;
		list<Move> moves = board.getValidMoves( turn );
		list<Move>::iterator itr = moves.begin();
		for (int i=0; i<int(moves.size()); itr++, i++)
		{
			OthelloBoard newBoard=board;
			Move move=*itr;
			newBoard.makeMove(turn,move);
			int v= minimax(newBoard,depth-1,!player,other(turn));
			if (v>bestVal)
			{
				bestVal=v;
			}
		}
		return bestVal;
	}
	else
	{
		int bestVal=10000;
		list<Move> moves = board.getValidMoves( turn );
		list<Move>::iterator itr = moves.begin();
		for (int i=0; i<int(moves.size()); itr++, i++)
		{
			OthelloBoard newBoard=board;
			Move move=*itr;
			newBoard.makeMove(turn,move);
			int v= minimax(newBoard,depth-1,!player,other(turn));
			if (v<bestVal)
			{
				bestVal=v;
			}
		}
		return bestVal;
	}
}

int alphabeta(const OthelloBoard& board, int depth, bool player, Turn turn, int alpha, int beta)
{
	if (depth==0)
	{
		return eval_board(board, turn);
	}
	if (player)
	{
		list<Move> moves = board.getValidMoves( turn );
		list<Move>::iterator itr = moves.begin();
		for (int i=0; i<int(moves.size()); itr++, i++)
		{
			OthelloBoard newBoard=board;
			Move move=*itr;
			newBoard.makeMove(turn,move);
			int v = alphabeta(newBoard,depth-1,!player,other(turn),alpha,beta);
			if (v>alpha)
			{
				alpha=v;
			}
			if (alpha>=beta)
			{
				return beta;
			}
		}
		return alpha;
	}
	else
	{
		list<Move> moves = board.getValidMoves( turn );
		list<Move>::iterator itr = moves.begin();
		for (int i=0; i<int(moves.size()); itr++, i++)
		{
			OthelloBoard newBoard=board;
			Move move=*itr;
			newBoard.makeMove(turn,move);
			int v = alphabeta(newBoard,depth-1,!player,other(turn),alpha,beta);
			if (v<beta)
			{
				beta=v;
			}
			if (alpha>=beta)
			{
				return alpha;
			}
		}
		return beta;
	}
}

// The following lines are _very_ important to create a bot module for Desdemona

extern "C" {
    OthelloPlayer* createBot( Turn turn )
    {
        return new MyBot( turn );
    }

    void destroyBot( OthelloPlayer* bot )
    {
        delete bot;
    }
}

