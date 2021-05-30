//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_KNIGHT_H
#define CHESSAI_KNIGHT_H

enum Color;

class Knight {
protected:
    Color team;
    int row;
    int col;
public:
    Knight(Color team, bool knightAtB);
    Knight(Color team, int row, int col); // Pawn gets promoted
    bool move(int r, int c);
};


#endif //CHESSAI_KNIGHT_H
