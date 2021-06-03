//
// Created by alecs on 5/29/2021.
//

#include <cstdio>
#include <cmath>
#include "Queen.h"
#include "ChessPiece.h"
#include "../ChessBoard.h"

Queen::Queen(Color team) {
    this->team = team;
    this->col = 3;
    this->row = (team == WHITE) ? 0 : 7;
}

Queen::Queen(Color team, int row, int col) { // pawn gets promoted
    this->team = team;
    this->row = row;
    this->col = col;
}

bool Queen::validateMove(int r, int c, ChessBoard* board) {
    int rowDisplacement = r-row;
    int colDisplacement = c-col;
    // check if movement is valid
    // Queen can move in straight lines in any direction
    if( !(abs(rowDisplacement) == abs(colDisplacement) || rowDisplacement == 0 || colDisplacement == 0) ) {
        printf("  Invalid move, Queen can move in straight lines perpendicularly or diagonally.\n");
        return false;
    }

    // check if jumping over another piece
    if(rowDisplacement == 0) { // moving horizontally
        int i = (colDisplacement > 0) ? col+1 : col-1; // starting position for the loop, left or right 1
        int inc = (colDisplacement > 0) ? 1 : -1; // increment left or right

        for(; i!=c; i+=inc) { // look for spaces on board that are not null
            if(board->getPiece(row, i) != nullptr) {
                printf("  Invalid move, Queen cannot jump over pieces.\n");
                return false;
            }
        }
    } else if(colDisplacement == 0) { // moving vertically
        int i = (rowDisplacement > 0) ? row+1 : row-1; // starting position for the loop, up or down 1
        int inc = (rowDisplacement > 0) ? 1 : -1; // increment up or down

        for(; i!=r; i+=inc) { // look for spaces on board that are not null
            if(board->getPiece(i, col) != nullptr) {
                printf("  Invalid move, Queen cannot jump over pieces.\n");
                return false;
            }
        }
    } else { // moving diagonally
        // incrementer for row and column
        int rowInc = (rowDisplacement > 0) ? 1 : -1; // moving up or down
        int colInc = (colDisplacement > 0) ? 1 : -1; // moving right or left

        int j = col+colInc; // set initial row and column
        for(int i = row+rowInc; i!=r; i+=rowInc) { // look for spaces on board that are not null
            if(board->getPiece(i, j) != nullptr) {
                printf("  Invalid move, Queen cannot jump over pieces.\n");
                return false;
            }
            j+=colInc; // increment row and column
        }
    }

    // propose move
    proposedRow = r;
    proposedCol = c;

    return true;
}

void Queen::makeMove() {
    // check for valid move
    if(proposedRow < 0 || proposedCol < 0) {
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

int Queen::getRow() {
    return row;
}

int Queen::getCol() {
    return col;
}

void Queen::resetValidation() {
    // reset proposed move
    proposedRow = -1;
    proposedCol = -1;
}
