#include <iostream>
#include <string>
#include "bishop.h"
using namespace std;

Bishop::Bishop(ChessBoard* _cb, Colour _colour, PieceType _type, string _symbol) 
            : Piece(_cb, _colour, _type, _symbol) {};

bool Bishop::validMoveCheck(Coord const& start, Coord const& end) 
{
    return (checkDiag(start, end) && freeTravel(start, end));
}

Piece* Bishop::clone() const
{
    return new Bishop(*this);
}