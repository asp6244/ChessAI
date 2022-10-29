//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_QUEEN_H
#define CHESSAI_QUEEN_H

#include "ColorsType.h"

class ChessBoard;
enum Color;

class Queen {
protected:
    Color team;
    int rank;
    int file;
    int proposedRank = -1;
    int proposedFile = -1;
public:
    Queen(Color team);
    Queen(Color team, int rank, int file); // Pawn gets promoted
    bool validateMove(int r, int c, ChessBoard* board);
    void makeMove();
    int getRank();
    int getFile();
    void resetValidation();
};


#endif //CHESSAI_QUEEN_H
