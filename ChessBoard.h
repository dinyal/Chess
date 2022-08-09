#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP
#include <iostream>
#include <string>
#include "piece.h"
#include "helper.h"

class Piece;

class ChessBoard {

    Piece* board[BOARD_SIZE][BOARD_SIZE];
    Colour turn = WHITE;

    /*Markers to indicate whether player is in check, or game is over*/
    bool inCheck = false;
    bool gameOver = false;
    
    /*Both king positions stored and updated when required.*/
    Coord kingWhitePos = {KING_COL, BOARD_MIN};
    Coord kingBlackPos = {KING_COL, BOARD_SIZE-1};

    /*initialise castling to and from positions to default value.
    Modified when checking for valid castling, and used by makeCastle
    to permanently move the rook when castling.*/
    Coord fromCastle = {BOARD_MIN, BOARD_MIN};
    Coord toCastle = {BOARD_MIN, BOARD_MIN};

    /*---------------PRIVATE MANIPULATE BOARD FUNCTIONS------------------*/
    void loadPieces(); //populates board with initial positions
    void wipeBoard(); //deletes all current pieces from the heap

    /*---------------------PRIVATE HELPER FUNCTIONS---------------------*/
    //Update king's position when king moved
    void kingPosUpdate(Coord const& coord, Colour colour);

    /*Function that is run AFTER having checked for valid move, called to
    move the rook to the relevant castling position.*/
    void makeCastle(Coord const& moveFrom, Coord const& moveTo);

public:
    /*----INITIALISE CHESSBOARD, AND DEFINE COPY/ASSIGNMENT OPERATOR----*/
    ChessBoard();
    //defined copy/assignment here due to defining destructor
    ChessBoard(ChessBoard const& other);
    ChessBoard& operator=(ChessBoard const& other);

    /*-------------------------MANIPULATE BOARD---------------------------*/
    void resetBoard(); //called wipe and load to reset the board

    /*----SUBMITMOVE MASTER FUNCTION----*/
    void submitMove(std::string const& moveFrom, std::string const& moveTo);

    /*----------------------COORDINATE VALIDATION--------------------------*/
    //returns true if board pointer is null
    bool checkEmpty(Coord const& coord);

    //makes sure string in within specified range, and of right size
    bool validateCoord(std::string const& coord) const;

    //makes sure the piece being moved is of the right colour
    bool checkTurn(Coord const& moveFrom) const;

    /*checks whether the from and to position contain pieces of the same colour.
    NOTE this also makes sure a piece isn't moving to the same spot*/
    bool checkSameColour(Coord const& moveFrom, Coord const& moveTo) const;

    /*--------------------MAKE THE MOVE WITH POINTERS-----------------------*/
    /*Permanently makes the attempted move on the board after
    all checks have been passed*/
    void makePrintMove(std::string const& moveFrom,std::string const& moveTo);

    /*--------------------KING CHECK AND CHECKMATE FUNCTIONS----------------*/
    /*loops through all your pieces, and tests if there is a 
    valid move to your opponent's king's position*/
    bool kingCheck(Colour const oppColour);

    /*Loops through all opponent's pieces. When found, loops through all VALID 
    moves for that piece.*/
    bool staleCheckMate(Colour const oppColour);

    /*Called by kingcheckmate and used separately. Will loop through 
    opponent's pieces and tests for valid move to your king's position.
    If there is one -> returns true and move is invalid. Else -> false*/
    bool selfCheck(Coord const& moveFrom, Coord const& moveTo, 
                                         Colour const player);

    /*--------------------GETTERS, SETTERS, ERRORS-----------------------*/
    void printBoard();
    Piece* getPiece(int const row, int const col) const;
    Colour getOppColour() const; //return opponent's colour
    bool isInCheck() const; //returns state of check
    void printError(ErrorType code, std::string const& moveFrom = "NA", 
                                    std::string const& moveTo = "NA");

    /*--------------------CASTLING FUNCTIONS------------------------------*/
    //sets rook from position for castling
    void setFromCastle(Coord const& _fromCastle);

    //sets rook to position for castling
    void setToCastle(Coord const& _toCastle);

    //returns the position of rook being castled
    const Coord& getFromCastle() const;

    /*----------------------DESTRUCTOR------------------------------------*/
    ~ChessBoard();
};

#endif