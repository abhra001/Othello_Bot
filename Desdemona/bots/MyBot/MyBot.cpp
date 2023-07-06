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

Move MyBot::play( const OthelloBoard& board )
{
    list<Move> moves = board.getValidMoves( turn );
    int randNo = rand() % moves.size();
    list<Move>::iterator it = moves.begin();
    n=int(moves.size())

    for (int i=0; i<=1; i++){
        for (int j=0; j<=1; j++){
            if board.validateMove(turn,i*(board.BOARD_SIZE-1),j*(board.BOARD_SIZE-1)){
                return Move(i*(board.BOARD_SIZE-1),j*(board.BOARD_SIZE-1));
            }
        }
    }

    for(int i=0; i < n; it++, i++){
        Move move=*it;
        if (move.x==0 or *it.move==(board.BOARD_SIZE-1)){
            return *it;
        }
        if (move.y==0 or move.y==(board.BOARD_SIZE-1)){
            return *it;
        }
    }

    list<Move>::iterator itr = moves.begin();

    for(int i=0; i < randNo; itr++, i++);
    return *itr;
}

int MyBot::minimax(const OthelloBoard& board, int depth)
{
    int val[8][8]={{1000,-10,10,10,10,10,-10,1000},{-10,-10,1,1,1,1,-10,-10},{10,1,1,1,1,1,1,10},{10,1,1,1,1,1,1,10},{10,1,1,1,1,1,1,10},{10,1,1,1,1,1,1,10},{-10,-10,1,1,1,1,-10,-10},{1000,-10,10,10,10,10,-10,1000}}

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

