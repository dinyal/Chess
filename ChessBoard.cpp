#include <iostream>
#include <string>
#include <cctype>
#include "ChessBoard.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"

using namespace std;

/*=======INITIALISE CHESSBOARD, AND DEFINE COPY/ASSIGNMENT OPERATOR======*/
ChessBoard::ChessBoard() {
    loadPieces();   
}

ChessBoard::ChessBoard(ChessBoard const& other)
{
    /*initialise everything to null pointer in order for
    wipeboard function to not delete uninitialised pointers*/
    for (int row = BOARD_MIN; row < BOARD_SIZE; row++) {
        for (int col = BOARD_MIN; col < BOARD_SIZE; col++) {
            this->board[row][col] = nullptr;
        }
    }
    //Then delegate to assignment operator
    *this = other;
}

ChessBoard& ChessBoard::operator=(ChessBoard const& other)
{
    //Delete any currently existing dynamic pieces
    wipeBoard();
    /*Do not need to copy across castling positions, as those
    will be updated to new castling positions next needed*/
    this->turn = other.turn;
    this->kingWhitePos = other.kingWhitePos;
    this->kingBlackPos = other.kingBlackPos;
    this->gameOver = other.gameOver;
    this->inCheck = other.inCheck;

    for (int row = BOARD_MIN; row < BOARD_SIZE; row++) {
        for (int col = BOARD_MIN; col < BOARD_SIZE; col++) {
            if(other.board[row][col] != nullptr) {
                this->board[row][col] = other.board[row][col]->clone();
            }
        }
    }
    return *this;
}

/*=====================MANIPULATE CHESSBOARD==========================*/
void ChessBoard::loadPieces() 
{
    /*Numbers here are only used once in loading of the board,
    so not all enumerated due to very limited use*/
    cout << "A new chess game is started!" << endl;
    for (int row = 6; row < BOARD_SIZE; row++) {
        for (int col = BOARD_MIN; col < BOARD_SIZE; col++) {
            if(row == BOARD_SIZE-1) {    
                if (col == 0 || col == 7) 
                    board[row][col] = new Rook(this, BLACK, ROOK, "♜");
                if (col == 1 || col == 6) 
                    board[row][col] = new Knight(this, BLACK, KNIGHT, "♞");
                if (col == 2 || col == 5) 
                    board[row][col] = new Bishop(this, BLACK, BISHOP, "♝");
                if (col == 3) 
                    board[row][col] = new Queen(this, BLACK, QUEEN, "♛");
                if (col == KING_COL) 
                    board[row][col] = new King(this, BLACK, KING, "♚");
            }
            else 
                board[row][col] = new Pawn(this, BLACK, PAWN, "♟");
        }
    }
    for (int row = BOARD_MIN; row < 2; row++) {
        for (int col = BOARD_MIN; col < BOARD_SIZE; col++) {
            if(row == BOARD_MIN) {    
                if (col == 0 || col == 7) 
                    board[row][col] = new Rook(this, WHITE, ROOK, "♖");
                if (col == 1 || col == 6) 
                    board[row][col] = new Knight(this, WHITE, KNIGHT, "♘");
                if (col == 2 || col == 5) 
                    board[row][col] = new Bishop(this, WHITE, BISHOP, "♗");
                if (col == 3) 
                    board[row][col] = new Queen(this, WHITE, QUEEN, "♕");
                if (col == KING_COL) 
                    board[row][col] = new King(this, WHITE, KING, "♔");
            }
            else 
                board[row][col] = new Pawn(this, WHITE, PAWN, "♙");
        }
    }
    for (int row = 2; row < 6; row++) {
        for (int col = BOARD_MIN; col < BOARD_SIZE; col++) {
            board[row][col] = nullptr;
        }
    }
}

void ChessBoard::wipeBoard()
{
    for (int row = BOARD_MIN; row < BOARD_SIZE; row++) {
        for (int col = BOARD_MIN; col < BOARD_SIZE; col++) {
            if(board[row][col] != nullptr) {
                delete board[row][col];
                board[row][col] = nullptr;
            }
        }
    }
}

void ChessBoard::resetBoard()
{  
    /*Do not need to reset castling positions, as those
    will be updated to new castling positions when next needed*/
    turn = WHITE;
    kingWhitePos = {KING_COL, BOARD_MIN};
    kingBlackPos = {KING_COL, BOARD_SIZE-1};
    gameOver = false;
    inCheck = false;

    wipeBoard();
    loadPieces();
    return;
}

/*====================SUBMITMOVE MASTER FUNCTION=========================*/
void ChessBoard::submitMove(string const& moveFrom, string const& moveTo)
{
    //Convert string to Coordinate struct here to minimise conversions
    Coord start = {fConv(moveFrom), rConv(moveFrom)};
    Coord end = {fConv(moveTo), rConv(moveTo)};
    
    //prevent moves being submitted after game is over
    if (gameOver) {
        printError(GAME_OVER);
        return;
    }
    //check validity of coordinates
    if (validateCoord(moveFrom)) {
        printError(INVALID_POS, moveFrom);
        return;
    }
    if (validateCoord(moveTo)) {
        printError(INVALID_POS, moveTo);
        return;
    }
    //check there is actually a piece in the position
    if (checkEmpty(start)) {
        printError(NO_PIECE, moveFrom);
        return;
    }
    //check it is the right turn (check piece type trying to move)
    if (!checkTurn(start)) {
        printError(PLAYER_TURN, moveFrom);
        return;
    }
    //chekcs not moving to piece of same colour or same position
    if (checkSameColour(start, end)) {
        printError(INVALID_MOVE, moveFrom, moveTo);
        return;
    }
    //check general move valid
    if (!board[start.rank][start.file]->validMoveCheck(start, end)) {
        printError(INVALID_MOVE, moveFrom, moveTo);
        return;
    }
    //if move valid make sure move does not put king in check
    if(selfCheck(start, end, turn)) {
        printError(CHECK, moveFrom, moveTo);
        return;
    }
    //if king is validly moved, update king position
    if(board[start.rank][start.file]->getType() == KING) {
        kingPosUpdate(end, turn);
    }
    //make the move (handles moving rook for castling within function)
    makePrintMove(moveFrom, moveTo);

    //check for check and checkmate
    if(kingCheck(getOppColour())) {
        inCheck = true;
        if (turn == WHITE) 
            cout << "Black is ";
        else 
            cout << "White is ";
    
        if (staleCheckMate(getOppColour())) { 
            cout << "in checkmate" << endl;
            gameOver = true;
        }
        else 
            cout << "in check" << endl;
    }
    //run checkmate function to check for stalemate.
    else {
        inCheck = false;
        if (staleCheckMate(getOppColour())) {
            cout << "The game ends in stalemate" << endl;
            gameOver = true;
        }
    }
    //change turn
    turn = (turn == WHITE) ? BLACK : WHITE;
    return;
}

/*=====================COORDINATE VALIDATION=====================*/
bool ChessBoard::checkEmpty(Coord const& coord)
{
    return (board[coord.rank][coord.file] == nullptr);
}

bool ChessBoard::validateCoord(string const& coord) const
{  
    if (coord.length() != R_TWO) {
        return true;
    }
    if (coord[FI] < 'A' || coord[FI] > 'H') {
        return true;
    }
    if (coord[RA] < '1' || coord[RA] > '8') {
        return true;
    }
    return false;
}

bool ChessBoard::checkTurn(Coord const& start) const
{
    return (board[start.rank][start.file]->getColour() == turn);
}

bool ChessBoard::checkSameColour(Coord const& start, Coord const& end) const
{
    if(board[end.rank][end.file] == nullptr) {
        return false;
    }
    if(board[start.rank][start.file]->getColour() 
        == board[end.rank][end.file]->getColour()) {
        return true;
    }
    return false;
}

/*=======================MAKE MOVE AND PRINT===============================*/
void ChessBoard::makePrintMove(string const& moveFrom, string const& moveTo)
{
    //convert strings once and use conversions in functions
    int rowF = rConv(moveFrom), colF = fConv(moveFrom),
        rowT = rConv(moveTo), colT = fConv(moveTo);

    //First check if castling, and if so move the rook
    if(abs(colF - colT) == 2 && board[rowF][colF]->getType() == KING) {
        makeCastle(fromCastle, toCastle);
    }
    
    //print which piece is moving where
    cout << board[rowF][colF]->printColour() << board[rowF][colF]->printType()
         << " moves from " << moveFrom << " to " << moveTo;

    //if piece is taken, print which piece, and then delete taken piece.
    if(board[rowT][colT] != nullptr) {
        cout << " taking " << board[rowT][colT]->printColour()
             << board[rowT][colT]->printType();
        delete board[rowT][colT];
        board[rowT][colT] = nullptr;
    }
    cout << endl;

    //set firstMove boolean in piece to false, then swap the positions
    if(board[rowF][colF]->getMove() == true) {
        board[rowF][colF]->setMove();
    }
    board[rowT][colT] = board[rowF][colF];
    board[rowF][colF] = nullptr;
}

/*=================KING CHECK, CHECKMATE AND STALEMATE FUNCTIONS================*/
bool ChessBoard::kingCheck(Colour const oppColour)
{
    Coord kingToCheck = (oppColour == WHITE) ? kingWhitePos : kingBlackPos;
    Coord Pos = {BOARD_MIN, BOARD_MIN}; //A1 represents first cell to loop from
    bool isCheck = false;

    for (; Pos.rank < BOARD_SIZE && isCheck == false; Pos.rank++) {
        Pos.file = BOARD_MIN; //reset column value
        for (; Pos.file < BOARD_SIZE && isCheck == false; Pos.file++) {
            //only check if the position is not empty and of the right colour
            if (!checkEmpty(Pos) 
                && oppColour != board[Pos.rank][Pos.file]->getColour()) {
                isCheck = board[Pos.rank][Pos.file]->validMoveCheck(Pos, kingToCheck);
            }
        }
    }
    return isCheck;
}

bool ChessBoard::staleCheckMate(Colour const oppColour)
{
    bool checkMate = true;
    Coord from = {BOARD_MIN, BOARD_MIN};

    //First loop to find an opponent's piece
    for (;from.rank < BOARD_SIZE && checkMate == true; from.rank++) {
        from.file = BOARD_MIN; // reset column after row loop

        for (;from.file < BOARD_SIZE && checkMate == true; from.file++) {
            if(checkEmpty(from)) {
                continue; //skips position if empty
            }
            if(board[from.rank][from.file]->getColour() == oppColour) { 
                Coord toPos = {BOARD_MIN, BOARD_MIN};
                //for every position on the board, find a valid move for that piece
                for(;toPos.rank < BOARD_SIZE && checkMate == true; toPos.rank++) {
                    toPos.file = BOARD_MIN; //reset column after row loop

                    for (;toPos.file < BOARD_SIZE && checkMate == true; toPos.file++) {
                        /*if the moveTo position is empty and moving there is valid
                        ->OR if the moveTo position contain opp's piece, and move is valid*/
                        if ((checkEmpty(toPos) 
                             && board[from.rank][from.file]->validMoveCheck(from, toPos))
                             || (!checkEmpty(toPos)
                             && !checkSameColour(from, toPos)
                             && board[from.rank][from.file]->validMoveCheck(from, toPos))) {
                            //Check whether the move would leave them in check
                            checkMate = selfCheck(from, toPos, oppColour);
                        }
                    }
                }
            }
        }
    }
    return checkMate;
}

bool ChessBoard::selfCheck(Coord const& start, Coord const& end, 
                                            Colour const player)
{
    //if the piece being moved is the king, temporarily update king's position
    if (board[start.rank][start.file]->getType() == KING) {
        kingPosUpdate(end, player);
    }
    //Temporarily swap pieces to simulate move
    /*NOTE: for castling, no need to simulate the rook's move as well as the king's
    move as it would NOT affect whether the castling puts the king in check*/
    auto moveToPtr = board[end.rank][end.file];
    board[end.rank][end.file] = board[start.rank][start.file];
    board[start.rank][start.file] = nullptr;

    Coord pos = {BOARD_MIN, BOARD_MIN}; //initialise starting loop position
    Coord kingToCheck = (player == WHITE) ? kingWhitePos : kingBlackPos;
    bool isCheck = false;

    /*loop through opponent's pieces checking to see if they can make
     a valid move to your king. Exit loop if one found*/
    for (; pos.rank < BOARD_SIZE && isCheck == false; pos.rank++) {
        pos.file = BOARD_MIN;
        for (; pos.file < BOARD_SIZE && isCheck == false; pos.file++) {
            if(checkEmpty(pos)) {
                continue;
            }
            if (player != board[pos.rank][pos.file]->getColour()) {
                isCheck = board[pos.rank][pos.file]->validMoveCheck(pos, kingToCheck);
            }
        }
    }
    //swap pieces back and return the value
    board[start.rank][start.file] = board[end.rank][end.file];
    board[end.rank][end.file] = moveToPtr;

    //reset king's position back to previous
    if (board[start.rank][start.file]->getType() == KING) {
        kingPosUpdate(start, player);
    }
    return isCheck;
}

/*========PRIVATE HELPER FUNCTIONS FOR CASTLING/UPDATING KING POSITION=========*/
void ChessBoard::makeCastle(Coord const& start, Coord const& end)
{
    //change boolean to indicate rook has moved
    board[start.rank][start.file]->setMove();
    board[end.rank][end.file] = board[start.rank][start.file];
    board[start.rank][start.file] = nullptr;
}

//private function that can only be called by chessboard class
void ChessBoard::kingPosUpdate(Coord const& coord, Colour colour) {
    if(colour == WHITE) 
        kingWhitePos = coord;
    else  
        kingBlackPos = coord;
}

/*================GETTERS, SETTERS and PRINTS=====================*/
void ChessBoard::printBoard() {
    cout << "  ";
    char coord = 'A';
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << "  " << static_cast<char>(coord + i) << " ";
    }
    cout << endl;

    cout << " -+---+---+---+---+---+---+---+---+" << endl;

    for (int i = BOARD_SIZE; i > 0; i--) {
        cout << i << " | ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            if(board[i-1][j] == nullptr) {
                cout << " " << " | ";
            }
            else {
                cout << board[i-1][j]->printSymbol() << " | ";
            }
        }
            
        cout << endl;
        cout << " -+---+---+---+---+---+---+---+---+" << endl;
    }
}

Piece* ChessBoard::getPiece(int const row, int const col) const
{
    return board[row][col];
}

Colour ChessBoard::getOppColour() const
{
    return (turn == WHITE) ? BLACK : WHITE;
}

bool ChessBoard::isInCheck() const
{
    return inCheck;
}
void ChessBoard::printError(ErrorType code, string const& moveFrom, 
                                            string const& moveTo) {
    switch (code)
    {
        case GAME_OVER:     cout << "The game is already over! "
                                 << "Please reset the board for a new game."
                                 << endl;
                            break;
        case INVALID_POS:   cout << moveFrom
                                 << " is not a valid position on the board!" 
                                 << endl;
                            break;
        case NO_PIECE:      cout << "There is no piece at position " 
                                 << moveFrom << "!" << endl;
                            break;
        case PLAYER_TURN:   cout << "It is not "
                                 << board[rConv(moveFrom)][fConv(moveFrom)]->printColour()
                                 << "turn to move!" << endl;
                            break;
        case INVALID_MOVE:  cout << board[rConv(moveFrom)][fConv(moveFrom)]->printColour()
                                 << board[rConv(moveFrom)][fConv(moveFrom)]->printType()
                                 << " cannot move to " << moveTo << "!" << endl;
                            break;
        case CHECK:         cout << board[rConv(moveFrom)][fConv(moveFrom)]->printColour()
                                 << board[rConv(moveFrom)][fConv(moveFrom)]->printType()
                                 << " to " << moveTo << " would put you in check!" << endl;
                            break;
        default:            cout << "No error code provided. Case should not occur!"
                                 << endl;
                            break;
    }
}

/*=======================CASTLING FUNCTIONS===========================*/
void ChessBoard::setFromCastle(Coord const& _fromCastle)
{
    fromCastle = _fromCastle;
}

void ChessBoard::setToCastle(Coord const& _toCastle)
{
    toCastle = _toCastle;
}

const Coord& ChessBoard::getFromCastle() const
{
    return fromCastle;
}

/*=========================DESTRUCTOR==============================*/
ChessBoard::~ChessBoard() {
    wipeBoard();
}