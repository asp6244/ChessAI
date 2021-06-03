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
    int proposedRow = -1;
    int proposedCol = -1;
public:
    Bishop(Color team, bool kingside);
    Bishop(Color team, int row, int col); // Pawn gets promoted
    bool validateMove(int r, int c, ChessBoard* board);
    void makeMove();
    int getRow();
    int getCol();
    void resetValidation();
};

#endif //CHESSAI_BISHOP_H
