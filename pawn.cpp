#include <iostream>
#include <string>
#include "pawn.h"
using namespace std;

Pawn::Pawn(ChessBoard* _cb, Colour _colour, PieceType _type, string _symbol) 
            : Piece(_cb, _colour, _type, _symbol) {};

bool Pawn::validMoveCheck(Coord const& start, Coord const& end)
{
    bool isvalid = false;
    //if colour is white, 'from' rank - 'to' rank must be -1, and +1 if black
    int direction = (colour == WHITE) ? DOWN : UP;
    //If a vertical move of 2, pawn must be on first move. End position must be empty
    if (checkVert(start, end) && (start.rank - end.rank == direction*2)
        && firstMove == true && cb->checkEmpty(end)
        && freeTravel(start, end)) {

		isvalid = true;
    }

    //diagonal only valid if moving onto opponent's piece
    if(checkDiag(start, end) && (start.rank - end.rank == direction)
        && !cb->checkEmpty(end)) {
            
        isvalid = true;
    }
    //vertical move only valid if moving into empty square. Must be in right direction
    if(checkVert(start, end) && (start.rank - end.rank == direction)
        && cb->checkEmpty(end)) {

        isvalid = true;
    }
    
    return isvalid;
}

Piece* Pawn::clone() const
{
    return new Pawn(*this);
}