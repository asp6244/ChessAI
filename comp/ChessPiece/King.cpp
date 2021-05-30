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

bool King::move(int r, int c, ChessBoard* board) {
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

    // TODO: check if movement enters check

    // check for castle
    if(((team == WHITE && row == 0) || (team == BLACK && row == 7)) && (col == 4 || col == 3) &&
       (abs(colDisplacement) == 2 && rowDisplacement == 0)) {
        if(!hasNotMoved) {
            printf("  Invalid move, castle condition not met; King cannot have moved in order to castle.\n");
            return false;
        }

        bool kingside = (colDisplacement == 2);
        if(!board->castle(team, kingside)) {
            return false;
        }
    }

    hasNotMoved = false;

    // make move
    row = r;
    col = c;

    return true;
}
