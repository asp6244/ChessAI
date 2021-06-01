//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_PAWN_H
#define CHESSAI_PAWN_H

class ChessBoard;
enum Color;

class Pawn {
protected:
    Color team;
    int row;
    int col;
    bool hasNotMoved = true;
public:
    Pawn(Color team, int col);
    bool move(int r, int c, ChessBoard* board);
    int getRow();
    int getCol();
};


#endif //CHESSAI_PAWN_H
