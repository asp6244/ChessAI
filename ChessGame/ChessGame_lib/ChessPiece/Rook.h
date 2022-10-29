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
    int rank;
    int file;
    bool hasNotMoved = true;
    int proposedRank = -1;
    int proposedFile = -1;
public:
    Rook(Color team, bool kingside);
    Rook(Color team, int rank, int file); // Pawn gets promoted
    bool validateMove(int r, int f, ChessBoard* board);
    void makeMove();
    bool getHasNotMoved();
    int getRank();
    int getFile();
    void resetValidation();
};


#endif //CHESSAI_ROOK_H
