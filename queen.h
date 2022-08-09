#ifndef QUEEN_HPP
#define QUEEN_HPP
#include <iostream>
#include <string>
#include "piece.h"

class Queen : public Piece {

public:
    Queen(ChessBoard* _cb, Colour _colour, PieceType _type, std::string _symbol);
    bool validMoveCheck(Coord const& start, Coord const& end) override;
    Piece* clone() const override;
    ~Queen() override {};
};

#endif