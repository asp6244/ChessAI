//
// Created by alecs on 4/30/2020.
//

#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H

#include "ChessPiece/ChessPiece.h"

class ChessBoard {
private:
    ChessPiece* board[8][8] = {nullptr}; // the board
    ChessPiece* capturedWhitePieces[16] = {nullptr};
    int capturedWhitePiecesSize = 0;
    ChessPiece* capturedBlackPieces[16] = {nullptr};
    int capturedBlackPiecesSize = 0;
    bool check = false;
    bool checkMate = false;
    bool hotSquares[8][8][32] = {false};
    ChessPiece* pointerMap[32];
public:
    ChessBoard(); // create a new board with new pieces
    void printBoard();
    bool movePiece(int row, int col, int newRow, int newCol);
    bool castle(Color team, bool kingside); // moves Rook to correct position for a castle
    ChessPiece* getPiece(int row, int col);
    void destroyBoard();
    bool getCheck();
    bool getCheckMate();
    void printHotSquares(bool printValues);
private:
    void promotion(int row, int col);
    void setAllHotSquares(int row, int col, bool value, bool reevaluating); // find all hot squares from a single piece
    void setSquareHot(int id, int row, int col, bool value); // for one square to be set hot
};


#endif //CHESS_CHESSBOARD_H
