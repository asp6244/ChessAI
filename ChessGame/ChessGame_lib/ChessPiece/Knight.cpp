//
// Created by alecs on 5/29/2021.
//

#include <cstdio>
#include <cmath>
#include "Knight.h"

Knight::Knight(Color team, bool kingside) {
    this->team = team;
    this->file = kingside ? 6 : 1;
    this->rank = (team == WHITE) ? 0 : 7;
}

Knight::Knight(Color team, int rank, int file) { // pawn gets promoted
    this->team = team;
    this->rank = rank;
    this->file = file;
}

bool Knight::validateMove(int r, int c) {
    int rowDisplacement = r-rank;
    int colDisplacement = c-file;
    // check if movement is valid
    // Knight can only move in L movements
    if( !( (abs(rowDisplacement) == 2 && abs(colDisplacement) == 1) ||
           (abs(rowDisplacement) == 1 && abs(colDisplacement) == 2) ) ) {
        printf("  Invalid move, Knight can only move in L movements.\n");
        return false;
    }

    // propose move
    proposedRank = r;
    proposedFile = c;

    return true;
}

void Knight::makeMove() {
    // check for valid move
    if(proposedRank < 0 || proposedFile < 0) {
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

int Knight::getRank() {
    return rank;
}

int Knight::getFile() {
    return file;
}

void Knight::resetValidation() {
    // reset proposed move
    proposedRank = -1;
    proposedFile = -1;
}