//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_PAWN_H
#define CHESSAI_PAWN_H

#include "ColorsType.h"

class ChessBoard;

class Pawn {
protected:
    Color team;
    int row;
    int col;
    bool hasNotMoved = true;
    int proposedRow = -1;
    int proposedCol = -1;
public:
    Pawn(Color team, int col);
    bool validateMove(int r, int c, ChessBoard* board);
    void makeMove();
    int getRow();
    int getCol();
    void resetValidation();
};


#endif //CHESSAI_PAWN_H
