//
// Created by alecs on 5/29/2021.
//

#include <cstdio>
#include <cmath>
#include "Pawn.h"
#include "ChessPiece.h"
#include "../ChessBoard.h"

Pawn::Pawn(Color team, int col) {
    this->team = team;
    this->col = col;
    this->row = (team == WHITE) ? 1 : 6;
}

bool Pawn::validateMove(int r, int c, ChessBoard* board) {
    int rowDisplacement = r-row;
    int colDisplacement = c-col;

    // check if trying to capture
    if(board->getPiece(r, c) != nullptr) {
        // check to see if trying to capture diagonally 1 away
        if( !(abs(colDisplacement) == 1 &&
              ( (team == WHITE && rowDisplacement == 1) || (team == BLACK && rowDisplacement == -1) )) ) {
            printf("  Invalid move, Pawn can only capture diagonally forward 1 square.\n");
            return false;
        }
    } else {
        // check if movement is valid
        // Pawn can only move forwards one, twice when not moved yet
        if (!((abs(colDisplacement) == 0) &&
              (((rowDisplacement == 1 && team == WHITE) || (rowDisplacement == -1 && team == BLACK)) ||
               (hasNotMoved && ((rowDisplacement == 2 && team == WHITE) || (rowDisplacement == -2 && team == BLACK)))))) {
            printf("  Invalid move, Pawn can only move forward one square or two when it has not moved yet.\n");
            return false;
        }

        // check if jumping over another piece
        if (abs(rowDisplacement) == 2) {
            int rowInc = (team == WHITE) ? 1 : -1;
            if (board->getPiece(row + rowInc, col) != nullptr) {
                printf("  Invalid move, Pawn cannot jump over pieces.\n");
                return false;
            }
        }
    }

    // propose move
    proposedRow = r;
    proposedCol = c;

    return true;
}

void Pawn::makeMove() {
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

    hasNotMoved = false;
}

int Pawn::getRow() {
    return row;
}

int Pawn::getCol() {
    return col;
}

void Pawn::resetValidation() {
    // reset proposed move
    proposedRow = -1;
    proposedCol = -1;
}
