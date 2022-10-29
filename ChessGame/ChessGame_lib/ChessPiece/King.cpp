//
// Created by alecs on 5/29/2021.
//

#include <cstdio>
#include <cmath>
#include "King.h"
#include "../ChessBoard.h"

King::King(Color team) {
    this->team = team;
    this->file = 4;
    this->rank = (team == WHITE) ? 0 : 7;
}

bool King::validateMove(int r, int f, ChessBoard *board) {
    // TODO: this can be simplified by using the array of hot squares from ChessBoard

    int rankDisplacement = r-rank;
    int fileDisplacement = f-file;
    // check if movement is valid
    // King can only move a single tile adjacently
    if( (abs(rankDisplacement) > 1 || abs(fileDisplacement) > 1) &&
        !(((team == WHITE && rank == 0) || (team == BLACK && rank == 7)) && (file == 4 || file == 3) &&
          (abs(fileDisplacement) == 2 && rankDisplacement == 0)) ) { // castle condition
        printf("  Invalid move, King can only move a single tile adjacently.\n");
        return false;
    }

    // check for castle
    if(((team == WHITE && rank == 0) || (team == BLACK && rank == 7)) && (file == 4 || file == 3) &&
       (abs(fileDisplacement) == 2 && rankDisplacement == 0)) {
        if(!hasNotMoved) {
            printf("  Invalid move, castle condition not met; King cannot have moved in order to castle.\n");
            return false;
        }

        if(board->getCheck(team)) {
            printf("  Invalid move, castle condition not met; King cannot be in check to castle.\n");
            return false;
        }

        bool kingside = (fileDisplacement == 2);

        // check for taking a piece or jumping over a piece
        if( (board->getPiece(r, f) != nullptr) || ((kingside && board->getPiece(rank, file+1) != nullptr) ||
          (!kingside && board->getPiece(rank, file-1) != nullptr)) ) {
            printf("  Invalid move, castle cannot contain any pieces between the King and Rook.\n");
            return false;
        }

        // attempt to castle
        if(!board->castle(team, kingside)) {
            return false;
        }
    }

    // propose move
    proposedRank = r;
    proposedFile = f;

    return true;
}

void King::makeMove() {
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

    hasNotMoved = false;
}

int King::getRank() {
    return rank;
}

int King::getFile() {
    return file;
}

void King::resetValidation() {
    // reset proposed move
    proposedRank = -1;
    proposedFile = -1;
}
