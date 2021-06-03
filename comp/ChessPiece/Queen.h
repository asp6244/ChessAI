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
    int proposedRow = -1;
    int proposedCol = -1;
public:
    Queen(Color team);
    Queen(Color team, int row, int col); // Pawn gets promoted
    bool validateMove(int r, int c, ChessBoard* board);
    void makeMove();
    int getRow();
    int getCol();
    void resetValidation();
};


#endif //CHESSAI_QUEEN_H
