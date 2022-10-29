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
    int rank;
    int file;
    bool hasNotMoved = true;
    int proposedRank = -1;
    int proposedFile = -1;
public:
    Pawn(Color team, int file);
    bool validateMove(int r, int c, ChessBoard* board);
    void makeMove();
    int getRank();
    int getFile();
    void resetValidation();
};


#endif //CHESSAI_PAWN_H
