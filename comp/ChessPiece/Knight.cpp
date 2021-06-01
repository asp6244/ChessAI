//
// Created by alecs on 5/29/2021.
//

#include <cstdio>
#include <cmath>
#include "Knight.h"
#include "ChessPiece.h"

Knight::Knight(Color team, bool kingside) {
    this->team = team;
    this->col = kingside ? 6 : 1;
    this->row = (team == WHITE) ? 0 : 7;
}

Knight::Knight(Color team, int row, int col) { // pawn gets promoted
    this->team = team;
    this->row = row;
    this->col = col;
}

bool Knight::move(int r, int c) {
    int rowDisplacement = r-row;
    int colDisplacement = c-col;
    // check if movement is valid
    // Knight can only move in L movements
    if( !( (abs(rowDisplacement) == 2 && abs(colDisplacement) == 1) ||
           (abs(rowDisplacement) == 1 && abs(colDisplacement) == 2) ) ) {
        printf("  Invalid move, Knight can only move in L movements.\n");
        return false;
    }

    // make move
    row = r;
    col = c;

    return true;
}

int Knight::getRow() {
    return row;
}

int Knight::getCol() {
    return col;
}