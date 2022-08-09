#include <iostream>
#include <string>
#include "king.h"
using namespace std;

King::King(ChessBoard* _cb, Colour _colour, PieceType _type, string _symbol) 
            : Piece(_cb, _colour, _type, _symbol) {};

bool King::validMoveCheck(Coord const& start, Coord const& end)
{
    /*Only check for castling if king's first move, not in check,it's a horizontal 
    move with range 2 and its end position has no piece*/
    if(firstMove == true
        && checkHor(start, end) 
        && abs(start.file - end.file) == R_TWO
        && !cb->isInCheck()
        && cb->getPiece(end.rank, end.file) == nullptr) {

        return validCastling(start, end);
    }
    /*Check if a vertical or diagonal with a vertical distance of 1. Only need to check 
    vert distance for diagonal as checkDiag confirms vert and hori distance are the same*/
    if((checkVert(start, end)
        || checkDiag(start, end))
        && abs(start.rank - end.rank) == R_ONE) {
        
        return true;
    }
    //check valid horizontal move of distance 1
    if(checkHor(start, end) && abs(start.file - end.file) == R_ONE) {
        return true;
    }
    return false;
}

bool King::validCastling(Coord const& start, Coord const& end)
{
    //Determine position of rook to castle with. Passed into getPiece function.
    int rookRow = start.rank;
    int rookCol = (start.file > end.file) ? BOARD_MIN : BOARD_SIZE-1;

    //Determine file index to be applied to potential new rook position
    int rookIndex = (start.file > end.file) ? DOWN : UP;

    //Determine king move index to know which position to test passing thru check
    int kingIndex = (rookCol == 0) ? DOWN : UP;

    //Create position to check for king passing check
    Coord endCheck = {start.file + kingIndex, start.rank};

    /*Update positions for rook being castled, to and from. May be used if move is valid.
    IF NOT, position will be overwritten next time a potential castle is being checked.*/
    cb->setFromCastle({rookCol, start.rank});
    cb->setToCastle({start.file + rookIndex, start.rank});

    if(!cb->checkEmpty(cb->getFromCastle())
        && cb->getPiece(rookRow, rookCol)->getType() == ROOK
        && cb->getPiece(rookRow, rookCol)->getMove() == true
        && freeTravel(start, cb->getFromCastle())
        && !cb->selfCheck(start, endCheck, colour)) {

        return true;
    }
    return false;
}

Piece* King::clone() const
{
    return new King(*this);
}