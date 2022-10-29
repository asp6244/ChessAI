//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_KNIGHT_H
#define CHESSAI_KNIGHT_H

#include "ColorsType.h"

class Knight {
protected:
    Color team;
    int rank;
    int file;
    int proposedRank = -1;
    int proposedFile = -1;
public:
    Knight(Color team, bool kingside);
    Knight(Color team, int rank, int file); // Pawn gets promoted
    bool validateMove(int r, int c);
    void makeMove();
    int getRank();
    int getFile();
    void resetValidation();
};


#endif //CHESSAI_KNIGHT_H
