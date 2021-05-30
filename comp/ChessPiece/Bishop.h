//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_BISHOP_H
#define CHESSAI_BISHOP_H

class ChessBoard;
enum Color;

class Bishop {
protected:
    Color team;
    int row;
    int col;
public:
    Bishop(Color team, bool bishopAtC);
    Bishop(Color team, int row, int col); // Pawn gets promoted
    bool move(int r, int c, ChessBoard* board);
};

#endif //CHESSAI_BISHOP_H
