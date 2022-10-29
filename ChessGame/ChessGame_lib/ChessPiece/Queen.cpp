//
// Created by alecs on 5/29/2021.
//

#include <cstdio>
#include <cmath>
#include "Queen.h"
#include "../ChessBoard.h"

Queen::Queen(Color team) {
    this->team = team;
    this->file = 3;
    this->rank = (team == WHITE) ? 0 : 7;
}

Queen::Queen(Color team, int rank, int file) { // pawn gets promoted
    this->team = team;
    this->rank = rank;
    this->file = file;
}

bool Queen::validateMove(int r, int c, ChessBoard* board) {
    int rowDisplacement = r-rank;
    int colDisplacement = c-file;
    // check if movement is valid
    // Queen can move in straight lines in any direction
    if( !(abs(rowDisplacement) == abs(colDisplacement) || rowDisplacement == 0 || colDisplacement == 0) ) {
        printf("  Invalid move, Queen can move in straight lines perpendicularly or diagonally.\n");
        return false;
    }

    // check if jumping over another piece
    if(rowDisplacement == 0) { // moving horizontally
        int i = (colDisplacement > 0) ? file+1 : file-1; // starting position for the loop, left or right 1
        int inc = (colDisplacement > 0) ? 1 : -1; // increment left or right

        for(; i!=c; i+=inc) { // look for spaces on board that are not null
            if(board->getPiece(rank, i) != nullptr) {
                printf("  Invalid move, Queen cannot jump over pieces.\n");
                return false;
            }
        }
    } else if(colDisplacement == 0) { // moving vertically
        int i = (rowDisplacement > 0) ? rank+1 : rank-1; // starting position for the loop, up or down 1
        int inc = (rowDisplacement > 0) ? 1 : -1; // increment up or down

        for(; i!=r; i+=inc) { // look for spaces on board that are not null
            if(board->getPiece(i, file) != nullptr) {
                printf("  Invalid move, Queen cannot jump over pieces.\n");
                return false;
            }
        }
    } else { // moving diagonally
        // incrementer for rank and file
        int rowInc = (rowDisplacement > 0) ? 1 : -1; // moving up or down
        int colInc = (colDisplacement > 0) ? 1 : -1; // moving right or left

        int j = file+colInc; // set initial rank and file
        for(int i = rank+rowInc; i!=r; i+=rowInc) { // look for spaces on board that are not null
            if(board->getPiece(i, j) != nullptr) {
                printf("  Invalid move, Queen cannot jump over pieces.\n");
                return false;
            }
            j+=colInc; // increment rank and file
        }
    }

    // propose move
    proposedRank = r;
    proposedFile = c;

    return true;
}

void Queen::makeMove() {
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

int Queen::getRank() {
    return rank;
}

int Queen::getFile() {
    return file;
}

void Queen::resetValidation() {
    // reset proposed move
    proposedRank = -1;
    proposedFile = -1;
}
