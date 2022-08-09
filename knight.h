#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include <iostream>
#include <string>
#include "piece.h"

class Knight : public Piece {

public:
    Knight(ChessBoard* _cb, Colour _colour, PieceType _type, std::string _symbol);
    bool validMoveCheck(Coord const& start, Coord const& end) override;
    Piece* clone() const override;
    ~Knight() override {};
};

#endif