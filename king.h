#ifndef KING_HPP
#define KING_HPP
#include <iostream>
#include <string>
#include "piece.h"

class King : public Piece {
    /*--PRIVATE FUNCTION IN PIECE TO CHECK FOR VALID CASTLING---*/
    bool validCastling(Coord const& start, Coord const& end);

public:
    
    King(ChessBoard* _cb, Colour _colour, PieceType _type, std::string _symbol);

    bool validMoveCheck(Coord const& start, Coord const& end) override;

    Piece* clone() const override;

    ~King() override {};
};

#endif