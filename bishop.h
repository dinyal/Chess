#ifndef BISHOP_HPP
#define BISHOP_HPP
#include <iostream>
#include <string>
#include "piece.h"

class Bishop : public Piece {

public:
    Bishop(ChessBoard* _cb, Colour _colour, PieceType _type, std::string _symbol);
    bool validMoveCheck(Coord const& start, Coord const& end) override;
    Piece* clone() const override;
    ~Bishop() override {};
};

#endif