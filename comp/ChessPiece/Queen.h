//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_QUEEN_H
#define CHESSAI_QUEEN_H

class ChessBoard;
enum Color;

class Queen {
protected:
    Color team;
    int row;
    int col;
public:
    Queen(Color team);
    Queen(Color team, int row, int col); // Pawn gets promoted
    bool move(int r, int c, ChessBoard* board);
};


#endif //CHESSAI_QUEEN_H
