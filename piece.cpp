#include <iostream>
#include <string>
#include "piece.h"

using namespace std;

/*---CONSTRUCTOR AND DESTRUCTOR---*/

Piece::Piece(ChessBoard* _cb, Colour _colour, PieceType _type, string _symbol) 
            : cb(_cb), colour(_colour), type(_type), symbol(_symbol) {};

/*---CHECKERS TO SEE IF PARTICULAR DIRECTIONAL MOVE IS VALID---*/
bool Piece::checkHor(Coord const& start, Coord const& end) const
{
    //If rank(row) is different, not horizontal
    if (start.rank != end.rank) {
        return false;
    }
    return true;
}

bool Piece::checkVert(Coord const& start, Coord const& end) const
{
    //if file(column) is different, not vertical
    if (start.file != end.file) {
        return false;
    }
    return true;
}

bool Piece::checkDiag(Coord const& start, Coord const& end) const
{
    //if abs diff between file and diff between ranks are same, is diagonal
    if (abs(start.file - end.file) != abs(start.rank - end.rank)) {
        return false;
    }
    return true;
}

bool Piece::checkLShape(Coord const& start, Coord const& end) const
{
    int vert = abs(start.file - end.file);
    int hori = abs(start.rank - end.rank);
    //if vert has range 2 and hori has range 1, or vice versa, is valid L shape
    if((vert == 2 && hori == 1)
        || (vert == 1 && hori == 2)) {
        
        return true;
    }
    return false;
}

/*---CHECKERS TO SEE IF NO PIECES IN THE WAY---*/
bool Piece::freeTravel(Coord const& start, Coord const& end) const
{
    int rowFrom = start.rank, colFrom = start.file;
    int loopRow = 0, loopCol = 0;

    if(start.rank != end.rank) {
        loopRow = (rowFrom > end.rank) ? DOWN : UP;
    }
    if(start.file != end.file) {
        loopCol = (colFrom > end.file) ? DOWN : UP;
    }
    
    /*Travel to end position using direction and range vectors, based on 
    whether there is vertical/horizontal movement. Skips the end square*/
    rowFrom += loopRow;
    colFrom += loopCol;
    
    while (rowFrom != end.rank || colFrom != end.file) {
        if (cb->getPiece(rowFrom, colFrom) != nullptr) {
            return false;
        }
        rowFrom += loopRow;
        colFrom += loopCol;
    }
    return true;
}

/*---GETTERS FOR TYPE AND COLOUR---*/
PieceType Piece::getType() const 
{ 
    return type;
}

Colour Piece::getColour() const 
{ 
    return colour;
}

bool Piece::getMove() const
{
    return firstMove;
}

void Piece::setMove()
{
    firstMove = false;
}

/*---PRINT SYMBOL---*/
const string Piece::printSymbol() const
{
    return symbol;
}

const string Piece::printColour() const
{
    switch (colour)
    {
        case WHITE: return "White's ";
                    break;
        case BLACK: return "Black's ";
                    break;
        default:    return "No colour to return\n";
                    break;
    }
}
const string Piece::printType() const
{
    switch (type)
    {
        case KING: return "King";
                    break;
        case QUEEN: return "Queen";
                    break;
        case BISHOP: return "Bishop";
                    break;
        case KNIGHT:return "Knight";
                    break;
        case ROOK:  return "Rook";
                    break; 
        case PAWN:  return "Pawn";
                    break; 
        default:    return "No piece to return\n";   
                    break;                                          
    }
}