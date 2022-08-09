#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
#include <string>

//Constants replacing magic numbers to be used across program
enum BoardConsts {BOARD_MIN = 0, BOARD_SIZE = 8, KING_COL = 4};
enum FileRank {FI, RA};
enum PieceType{KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN};
enum Colour {BLACK, WHITE};
enum Direction {UP = 1, DOWN = -1};
enum Range {R_ONE = 1, R_TWO = 2};
enum ErrorType {GAME_OVER, INVALID_POS, NO_PIECE, PLAYER_TURN, 
                                        INVALID_MOVE, CHECK};


//String converted to 2 integers representing the file and rank.
struct Coord {
    int file;
    int rank;
};

//Convert character into int position
int fConv(std::string const& coord);
int rConv(std::string const& coord);

#endif