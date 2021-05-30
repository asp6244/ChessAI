//
// Created by alecs on 5/29/2021.
//

#include <cmath>
#include <cstdio>
#include "Bishop.h"
#include "ChessPiece.h"
#include "../ChessBoard.h"

Bishop::Bishop(Color team, bool bishopAtC) {
    this->team = team;
    this->col = bishopAtC ? 2 : 5;
    this->row = (team == WHITE) ? 0 : 7;
}

Bishop::Bishop(Color team, int row, int col) { // pawn gets promoted
    this->team = team;
    this->row = row;
    this->col = col;
}

bool Bishop::move(int r, int c, ChessBoard* board) {
    int rowDisplacement = r-row;
    int colDisplacement = c-col;
    // check if movement is valid
    // Bishop can only move diagonally
    if(abs(rowDisplacement) != abs(colDisplacement)) {
        printf("  Invalid move, Bishop can only move in straight lines diagonally.\n");
        return false;
    }

    // check if jumping over another piece
    // incrementer for row and column
    int rowInc = (rowDisplacement > 0) ? 1 : -1; // moving up or down
    int colInc = (colDisplacement > 0) ? 1 : -1; // moving right or left

    int j = col+colInc; // set initial row and column
    for(int i = row+rowInc; i!=r; i+=rowInc) { // look for spaces on board that are not null
        if(board->getPiece(i, j) != nullptr) {
            printf("  Invalid move, Bishop cannot jump over pieces.\n");
            return false;
        }
        j+=colInc; // increment row and column
    }

    // make move
    row = r;
    col = c;

    return true;
}
