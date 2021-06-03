//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_KING_H
#define CHESSAI_KING_H

#include "Rook.h"

class ChessBoard;
enum Color;

class King {
protected:
    Color team;
    int row;
    int col;
    bool hasNotMoved = true;
    int proposedRow = -1;
    int proposedCol = -1;
    Rook* castledRook;
public:
    King(Color team);
    bool validateMove(int r, int c, ChessBoard* board);
    void makeMove();
    int getRow();
    int getCol();
    void resetValidation();
};


#endif //CHESSAI_KING_H
