#include <iostream>
#include <string>
#include "knight.h"
using namespace std;

Knight::Knight(ChessBoard* _cb, Colour _colour, PieceType _type, string _symbol) 
            : Piece(_cb, _colour, _type, _symbol) {};

bool Knight::validMoveCheck(Coord const& start, Coord const& end)
{
    //Np need to check free path for the knight
    return checkLShape(start, end);
}

Piece* Knight::clone() const
{
    return new Knight(*this);
}