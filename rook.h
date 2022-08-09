#ifndef ROOK_HPP
#define ROOK_HPP
#include <iostream>
#include <string>
#include "piece.h"

class Rook : public Piece {

public:
    Rook(ChessBoard* _cb, Colour _colour, PieceType _type, std::string _symbol);
    bool validMoveCheck(Coord const& start, Coord const& end) override;
    Piece* clone() const override;
    ~Rook() override {};
};

#endif