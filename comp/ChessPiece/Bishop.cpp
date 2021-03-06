//
// Created by alecs on 5/29/2021.
//

#include <cmath>
#include <cstdio>
#include "Bishop.h"
#include "../ChessBoard.h"

Bishop::Bishop(Color team, bool kingside) {
    this->team = team;
    this->col = kingside ? 5 : 2;
    this->row = (team == WHITE) ? 0 : 7;
}

Bishop::Bishop(Color team, int row, int col) { // pawn gets promoted
    this->team = team;
    this->row = row;
    this->col = col;
}

bool Bishop::validateMove(int r, int c, ChessBoard* board) {
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

    // propose move
    proposedRow = r;
    proposedCol = c;

    return true;
}

void Bishop::makeMove() {
    // check for valid move
    if (proposedRow < 0 || proposedCol < 0) {
        printf("Error: makeMove() attempted to make an invalid move.\n");
        exit(99);
    }

    // mave move
    row = proposedRow;
    col = proposedCol;

    // reset proposed move
    proposedRow = -1;
    proposedCol = -1;
}

int Bishop::getRow() {
    return row;
}

int Bishop::getCol() {
    return col;
}

void Bishop::resetValidation() {
    // reset proposed move
    proposedRow = -1;
    proposedCol = -1;
}
