//
// Created by alecs on 5/29/2021.
//

#include <cstdio>
#include <cmath>
#include "King.h"
#include "ChessPiece.h"
#include "../ChessBoard.h"

King::King(Color team) {
    this->team = team;
    this->col = 4;
    this->row = (team == WHITE) ? 0 : 7;
}

bool King::validateMove(int r, int c, ChessBoard *board) {
    // TODO: this can be simplified by using the array of hot squares from ChessBoard

    int rowDisplacement = r-row;
    int colDisplacement = c-col;
    // check if movement is valid
    // King can only move a single tile adjacently
    if( (abs(rowDisplacement) > 1 || abs(colDisplacement) > 1) &&
        !(((team == WHITE && row == 0) || (team == BLACK && row == 7)) && (col == 4 || col == 3) &&
          (abs(colDisplacement) == 2 && rowDisplacement == 0)) ) { // castle condition
        printf("  Invalid move, King can only move a single tile adjacently.\n");
        return false;
    }

    // check for castle
    if(((team == WHITE && row == 0) || (team == BLACK && row == 7)) && (col == 4 || col == 3) &&
       (abs(colDisplacement) == 2 && rowDisplacement == 0)) {
        if(!hasNotMoved) {
            printf("  Invalid move, castle condition not met; King cannot have moved in order to castle.\n");
            return false;
        }

        if( (board->getWhiteCheck() && team == WHITE) || (board->getBlackCheck() && team == BLACK) ) {
            printf("  Invalid move, castle condition not met; King cannot be in check to castle.\n");
            return false;
        }

        bool kingside = (colDisplacement == 2);

        // check for taking a piece or jumping over a piece
        if( (board->getPiece(r, c) != nullptr) || ((kingside && board->getPiece(row, col+1) != nullptr) ||
          (!kingside && board->getPiece(row, col-1) != nullptr)) ) {
            printf("  Invalid move, castle cannot contain any pieces between the King and Rook.\n");
            return false;
        }

        // attempt to castle
        if(!board->castle(team, kingside)) {
            return false;
        }

        // save the rook that is being castled
        int rookCol = (kingside) ? 7 : 0;
        castledRook = board->getPiece(row, rookCol)->getPointer().rook;
    } else {
        castledRook = nullptr;
    }

    // propose move
    proposedRow = r;
    proposedCol = c;

    return true;
}

void King::makeMove() {
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

    // execute castle
    castledRook->makeMove();

    // reset castle
    castledRook = nullptr;
}

int King::getRow() {
    return row;
}

int King::getCol() {
    return col;
}

void King::resetValidation() {
    // reset proposed move
    proposedRow = -1;
    proposedCol = -1;

    // reset castle
    castledRook = nullptr;
}
