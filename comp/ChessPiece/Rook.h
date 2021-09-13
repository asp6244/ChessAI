//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_ROOK_H
#define CHESSAI_ROOK_H

#include "ColorsType.h"

class ChessBoard;

class Rook {
protected:
    Color team;
    int row;
    int col;
    bool hasNotMoved = true;
    int proposedRow = -1;
    int proposedCol = -1;
public:
    Rook(Color team, bool kingside);
    Rook(Color team, int row, int col); // Pawn gets promoted
    bool validateMove(int r, int c, ChessBoard* board);
    void makeMove();
    bool getHasNotMoved();
    int getRow();
    int getCol();
    void resetValidation();
};


#endif //CHESSAI_ROOK_H
