//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_KNIGHT_H
#define CHESSAI_KNIGHT_H

#include "ColorsType.h"

class Knight {
protected:
    Color team;
    int row;
    int col;
    int proposedRow = -1;
    int proposedCol = -1;
public:
    Knight(Color team, bool kingside);
    Knight(Color team, int row, int col); // Pawn gets promoted
    bool validateMove(int r, int c);
    void makeMove();
    int getRow();
    int getCol();
    void resetValidation();
};


#endif //CHESSAI_KNIGHT_H
