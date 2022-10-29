//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_KING_H
#define CHESSAI_KING_H

#include "ColorsType.h"
#include "Rook.h"

class ChessBoard;

class King {
protected:
    Color team;
    int rank;
    int file;
    bool hasNotMoved = true;
    int proposedRank = -1;
    int proposedFile = -1;
public:
    King(Color team);
    bool validateMove(int r, int f, ChessBoard* board);
    void makeMove();
    int getRank();
    int getFile();
    void resetValidation();
};


#endif //CHESSAI_KING_H
