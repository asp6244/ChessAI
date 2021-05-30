//
// Created by alecs on 5/29/2021.
//

#ifndef CHESSAI_ROOK_H
#define CHESSAI_ROOK_H

class ChessBoard;
enum Color;

class Rook {
protected:
    Color team;
    int row;
    int col;
    bool hasNotMoved = true;
public:
    Rook(Color team, bool rookAtA);
    Rook(Color team, int row, int col); // Pawn gets promoted
    bool move(int r, int c, ChessBoard* board);
    bool getHasNotMoved();
};


#endif //CHESSAI_ROOK_H
