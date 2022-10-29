//
// Created by alecs on 4/30/2020.
//

#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H

#include "ChessPiece/ChessPiece.h"

#define ROOK_QS_ID      0
#define KNIGHT_QS_ID    1
#define BISHOP_QS_ID    2
#define QUEEN_ID        3
#define KING_ID         4
#define BISHOP_KS_ID    5
#define KNIGHT_KS_ID    6
#define ROOK_KS_ID      7
#define PAWS_START_ID   8
#define BLACK_ID_OFFSET 16

class ChessBoard {
private:
    ChessPiece* board[8][8] = {nullptr}; // the board
    ChessPiece* capturedWhitePieces[16] = {nullptr};
    int capturedWhitePiecesSize = 0;
    ChessPiece* capturedBlackPieces[16] = {nullptr};
    int capturedBlackPiecesSize = 0;
    bool castling = false;
    bool whiteCheck = false;
    bool whiteCheckMate = false;
    bool blackCheck = false;
    bool blackCheckMate = false;
    bool stalemate = false;
    bool hotSquares[8][8][32] = {false};
    ChessPiece* pointerMap[32] = {nullptr};
public:
    ChessBoard(); // create a new board with new pieces
    void printBoard();
    bool movePiece(int rank, int file, int newRank, int newFile);
    bool castle(Color team, bool kingside); // moves Rook to correct position for a castle
    ChessPiece* getPiece(int rank, int file);
    bool getCheck(Color team);
    bool getCheckmate(Color team);
    bool getStalemate();
    void printHotSquares(bool printValues);
    void destroyBoard();
private:
    void promotion(int rank, int file);
    void setAllHotSquares(int rank, int file, bool value, bool reevaluating); // find all hot squares from a single piece
    void setSquareHot(int id, int rank, int file, bool value); // for one square to be set hot
    void setCheck(Color team, bool checkCheckmate);
    void setCheckmate(Color team);
    bool foundValidMove(Color team, int rank, int file, ChessPiece* attacker=nullptr, int attackerIndex=-1);
    void setStalemate(Color team);
    bool checkStalemateValidMove(int rank, int file, int newRank, int newFile);
};


#endif //CHESS_CHESSBOARD_H
