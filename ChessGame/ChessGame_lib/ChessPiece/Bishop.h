//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_BISHOP_H
#define CHESSAI_BISHOP_H

#include "ColorsType.h"

class ChessBoard;
enum Color;

class Bishop {
protected:
    Color team;
    int rank;
    int file;
    int proposedRank = -1;
    int proposedFile = -1;
public:
    Bishop(Color team, bool kingside);
    Bishop(Color team, int rank, int file); // Pawn gets promoted
    bool validateMove(int r, int c, ChessBoard* board);
    void makeMove();
    int getRank();
    int getFile();
    void resetValidation();
};

#endif //CHESSAI_BISHOP_H
