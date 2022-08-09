#include <iostream>
#include <string>
#include "queen.h"
using namespace std;

Queen::Queen(ChessBoard* _cb, Colour _colour, PieceType _type, string _symbol) 
            : Piece(_cb, _colour, _type, _symbol) {};

bool Queen::validMoveCheck(Coord const& start, Coord const& end)
{
    /*check a valid hori, vertical, or diagonal move is made
    Then check path is free*/
    if((checkHor(start, end) 
        || checkVert(start, end) 
        || checkDiag(start, end))
        && freeTravel(start, end)) {
        
        return true;
    }
    return false;
}

Piece* Queen::clone() const
{
    return new Queen(*this);
}