#ifndef PAWN_HPP
#define PAWN_HPP
#include <iostream>
#include <string>
#include "piece.h"

class Pawn : public Piece {

public:
    Pawn(ChessBoard* _cb, Colour _colour, PieceType _type, std::string _symbol);
    bool validMoveCheck(Coord const& start, Coord const& end) override;
    Piece* clone() const override;
    ~Pawn() override {};
};

#endif