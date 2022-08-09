#include <iostream>
#include <string>
#include "rook.h"
using namespace std;

Rook::Rook(ChessBoard* _cb, Colour _colour, PieceType _type, string _symbol) 
            : Piece(_cb, _colour, _type, _symbol) {};

bool Rook::validMoveCheck(Coord const& start, Coord const& end)
{
    /*Check valid horizontal or vertical move made. Then check
    path is free*/
    if((checkHor(start, end) || checkVert(start, end))
        && freeTravel(start, end)) {   
             
        return true;
    }
    return false;
}

Piece* Rook::clone() const
{
    return new Rook(*this);
}