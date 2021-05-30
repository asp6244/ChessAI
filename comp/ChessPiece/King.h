//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_KING_H
#define CHESSAI_KING_H

class ChessBoard;
enum Color;

class King {
protected:
    Color team;
    int row;
    int col;
    bool hasNotMoved = true;
public:
    King(Color team);
    bool move(int r, int c, ChessBoard* board);
};


#endif //CHESSAI_KING_H
