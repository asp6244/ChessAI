//
// Created by alecs on 5/29/2021.
//

#include <cmath>
#include <cstdio>
#include "Bishop.h"
#include "../ChessBoard.h"

Bishop::Bishop(Color team, bool kingside) {
    this->team = team;
    this->file = kingside ? 5 : 2;
    this->rank = (team == WHITE) ? 0 : 7;
}

Bishop::Bishop(Color team, int rank, int file) { // pawn gets promoted
    this->team = team;
    this->rank = rank;
    this->file = file;
}

bool Bishop::validateMove(int r, int c, ChessBoard* board) {
    int rankDisplacement = r-rank;
    int colDisplacement = c-file;
    // check if movement is valid
    // Bishop can only move diagonally
    if(abs(rankDisplacement) != abs(colDisplacement)) {
        printf("  Invalid move, Bishop can only move in straight lines diagonally.\n");
        return false;
    }

    // check if jumping over another piece
    // incrementer for rank and file
    int rankInc = (rankDisplacement > 0) ? 1 : -1; // moving up or down
    int colInc = (colDisplacement > 0) ? 1 : -1; // moving right or left

    int j = file+colInc; // set initial rank and file
    for(int i = rank+rankInc; i!=r; i+=rankInc) { // look for spaces on board that are not null
        if(board->getPiece(i, j) != nullptr) {
            printf("  Invalid move, Bishop cannot jump over pieces.\n");
            return false;
        }
        j+=colInc; // increment rank and file
    }

    // propose move
    proposedRank = r;
    proposedFile = c;

    return true;
}

void Bishop::makeMove() {
    // check for valid move
    if (proposedRank < 0 || proposedFile < 0) {
        printf("Error: makeMove() attempted to make an invalid move.\n");
        exit(99);
    }

    // mave move
    rank = proposedRank;
    file = proposedFile;

    // reset proposed move
    proposedRank = -1;
    proposedFile = -1;
}

int Bishop::getRank() {
    return rank;
}

int Bishop::getFile() {
    return file;
}

void Bishop::resetValidation() {
    // reset proposed move
    proposedRank = -1;
    proposedFile = -1;
}
