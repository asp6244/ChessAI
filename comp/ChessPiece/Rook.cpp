//
// Created by alecs on 5/29/2021.
//

#include <cstdio>
#include "Rook.h"
#include "ChessPiece.h"
#include "../ChessBoard.h"

Rook::Rook(Color team, bool kingside) {
    this->team = team;
    this->col = kingside ? 7 : 0;
    this->row = (team == WHITE) ? 0 : 7;
}
Rook::Rook(Color team, int row, int col) { // pawn gets promoted
    this->team = team;
    this->row = row;
    this->col = col;
}

bool Rook::move(int r, int c, ChessBoard* board) {
    int rowDisplacement = r-row;
    int colDisplacement = c-col;

    // check if movement is valid
    // Rook can only move in perpendicular straight lines
    if( !(rowDisplacement == 0 || colDisplacement == 0) ) {
        printf("  Invalid move, Rook can only move in straight lines perpendicularly.\n");
        return false;
    }

    // check if jumping over another piece
    if(rowDisplacement == 0) { // moving horizontally
        int i = (colDisplacement > 0) ? col+1 : col-1; // starting position for the loop, left or right 1
        int inc = (colDisplacement > 0) ? 1 : -1; // increment left or right

        for(; i!=c; i+=inc) { // look for spaces on board that are not null
            if(board->getPiece(row, i) != nullptr) {
                printf("  Invalid move, Rook cannot jump over pieces.\n");
                return false;
            }
        }
    } else { // moving vertically
        int i = (rowDisplacement > 0) ? row+1 : row-1; // starting position for the loop, up or down 1
        int inc = (rowDisplacement > 0) ? 1 : -1; // increment up or down

        for(; i!=r; i+=inc) { // look for spaces on board that are not null
            if(board->getPiece(i, col) != nullptr) {
                printf("  Invalid move, Rook cannot jump over pieces.\n");
                return false;
            }
        }
    }

    hasNotMoved = false;

    // make move
    row = r;
    col = c;

    return true;
}

bool Rook::getHasNotMoved() {
    return hasNotMoved;
}

int Rook::getRow() {
    return row;
}

int Rook::getCol() {
    return col;
}