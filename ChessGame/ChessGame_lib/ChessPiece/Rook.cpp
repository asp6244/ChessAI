//
// Created by alecs on 5/29/2021.
//

#include <cstdio>
#include <cstdlib>
#include "Rook.h"
#include "../ChessBoard.h"

Rook::Rook(Color team, bool kingside) {
    this->team = team;
    this->file = kingside ? 7 : 0;
    this->rank = (team == WHITE) ? 0 : 7;
}
Rook::Rook(Color team, int rank, int file) { // pawn gets promoted
    this->team = team;
    this->rank = rank;
    this->file = file;
}

bool Rook::validateMove(int r, int f, ChessBoard* board) {
    int rankDisplacement = r-rank;
    int fileDisplacement = f-file;

    // check if movement is valid
    // Rook can only move in perpendicular straight lines
    if( !(rankDisplacement == 0 || fileDisplacement == 0) ) {
        printf("  Invalid move, Rook can only move in straight lines perpendicularly.\n");
        return false;
    }

    // check if jumping over another piece
    if(rankDisplacement == 0) { // moving horizontally
        int i = (fileDisplacement > 0) ? file+1 : file-1; // starting position for the loop, left or right 1
        int inc = (fileDisplacement > 0) ? 1 : -1; // increment left or right

        for(; i!=f; i+=inc) { // look for spaces on board that are not null
            if(board->getPiece(rank, i) != nullptr) {
                printf("  Invalid move, Rook cannot jump over pieces.\n");
                return false;
            }
        }
    } else { // moving vertically
        int i = (rankDisplacement > 0) ? rank+1 : rank-1; // starting position for the loop, up or down 1
        int inc = (rankDisplacement > 0) ? 1 : -1; // increment up or down

        for(; i!=r; i+=inc) { // look for spaces on board that are not null
            if(board->getPiece(i, file) != nullptr) {
                printf("  Invalid move, Rook cannot jump over pieces.\n");
                return false;
            }
        }
    }

    // propose move
    proposedRank = r;
    proposedFile = f;

    return true;
}

void Rook::makeMove() {
    // check for valid move
    if (proposedRank < 0 || proposedFile < 0) {
        printf("rError: makeMove() attempted to make an invalid move.\n");
        exit(99);
    }

    // make move
    rank = proposedRank;
    file = proposedFile;

    // reset proposed move
    proposedRank = -1;
    proposedFile = -1;

    hasNotMoved = false;
}

bool Rook::getHasNotMoved() {
    return hasNotMoved;
}

int Rook::getRank() {
    return rank;
}

int Rook::getFile() {
    return file;
}

void Rook::resetValidation() {
    // reset proposed move
    proposedRank = -1;
    proposedFile = -1;
}