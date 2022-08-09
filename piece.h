#ifndef PIECE_HPP
#define PIECE_HPP
#include <iostream>
#include <string>
#include "ChessBoard.h"
#include "helper.h"

class ChessBoard;

class Piece {
protected:
    ChessBoard* cb = nullptr;
    Colour colour;
    PieceType type;
    std::string symbol;
    bool firstMove = true;

    /*---CHECKERS TO DETERMINE DIRECTION OF TRAVEL, AND IF PATH IS FREE---*/
    bool checkHor(Coord const& start, Coord const& end) const;
    bool checkVert(Coord const& start, Coord const& end) const;
    bool checkDiag(Coord const& start, Coord const& end) const;
    
    //checks an L shape move for horse.
    bool checkLShape(Coord const& start, Coord const& end) const;

    bool freeTravel(Coord const& start, Coord const& end) const;

public:
    /*------------------CONSTRUCTOR AND VIRTUAL DESTRUCTOR-----------------*/
    Piece(ChessBoard* _cb, Colour _colour, PieceType _type, std::string _symbol);

    virtual ~Piece() {};

    /*-----------GETTERS FOR TYPE AND COLOUR AND SETTER FOR FIRSTMOVE------*/
    PieceType getType() const;
    Colour getColour() const;
    bool getMove() const;
    void setMove();

    /*---PRINT OUT FUNCTIONS---*/
    const std::string printSymbol() const;
    const std::string printColour() const;
    const std::string printType() const;

    /*---PURE VIRTUAL FUNCTION TO CHECK VALIDITY OF MOVE---*/
    virtual bool validMoveCheck(Coord const& start, Coord const& end) = 0;

    /*---PURE VIRTUAL TO RETURN COPY OF PIECE FOR COPY ASSIGNMENT/CONSTRUCTOR---*/
    virtual Piece* clone() const = 0;
};

#endif