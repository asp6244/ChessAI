//
// Created by alecs on 4/30/2020.
//

#include <cmath>
#include <cstdio>
#include "ChessPiece.h"
#include "ChessBoard.h"


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

bool Queen::move(int r, int c, ChessBoard* board) {
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

    // make move
    row = r;
    col = c;

    return true;
}



Bishop::Bishop(Color team, bool bishopAtC) {
    this->team = team;
    this->col = bishopAtC ? 2 : 5;
    this->row = (team == WHITE) ? 0 : 7;
}

Bishop::Bishop(Color team, int row, int col) { // pawn gets promoted
    this->team = team;
    this->row = row;
    this->col = col;
}

bool Bishop::move(int r, int c, ChessBoard* board) {
    int rowDisplacement = r-row;
    int colDisplacement = c-col;
    // check if movement is valid
    // Bishop can only move diagonally
    if(abs(rowDisplacement) != abs(colDisplacement)) {
        printf("  Invalid move, Bishop can only move in straight lines diagonally.\n");
        return false;
    }

    // check if jumping over another piece
    // incrementer for row and column
    int rowInc = (rowDisplacement > 0) ? 1 : -1; // moving up or down
    int colInc = (colDisplacement > 0) ? 1 : -1; // moving right or left

    int j = col+colInc; // set initial row and column
    for(int i = row+rowInc; i!=r; i+=rowInc) { // look for spaces on board that are not null
        if(board->getPiece(i, j) != nullptr) {
            printf("  Invalid move, Bishop cannot jump over pieces.\n");
            return false;
        }
        j+=colInc; // increment row and column
    }

    // make move
    row = r;
    col = c;

    return true;
}



Knight::Knight(Color team, bool knightAtB) {
    this->team = team;
    this->col = knightAtB ? 1 : 6;
    this->row = (team == WHITE) ? 0 : 7;
}

Knight::Knight(Color team, int row, int col) { // pawn gets promoted
    this->team = team;
    this->row = row;
    this->col = col;
}

bool Knight::move(int r, int c) {
    int rowDisplacement = r-row;
    int colDisplacement = c-col;
    // check if movement is valid
    // Knight can only move in L movements
    if( !( (abs(rowDisplacement) == 2 && abs(colDisplacement) == 1) ||
           (abs(rowDisplacement) == 1 && abs(colDisplacement) == 2) ) ) {
        printf("  Invalid move, Knight can only move in L movements.\n");
        return false;
    }

    // make move
    row = r;
    col = c;

    return true;
}



Rook::Rook(Color team, bool rookAtA) {
    this->team = team;
    this->col = rookAtA ? 0 : 7;
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


Pawn::Pawn(Color team, int col) {
    this->team = team;
    this->col = col;
    this->row = (team == WHITE) ? 1 : 6;
}

bool Pawn::move(int r, int c, ChessBoard* board) {
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

    hasNotMoved = false;

    // make move
    row = r;
    col = c;

    return true;
}



ChessPiece::ChessPiece(PieceType type, Color team) {
    this->type = type;
    this->team = team;

    switch(type) {
        case KING:
            pointer.king = King(team);
            break;
        case QUEEN:
            pointer.queen = Queen(team);
            break;
        default:
            fprintf(stderr, "Error: Wrong constructor used for initializing piece [Constructor 1].\n");
            exit(99);
    }
}

ChessPiece::ChessPiece(PieceType type, Color team, bool firstPiece) {
    this->type = type;
    this->team = team;

    switch(type) {
        case BISHOP:
            pointer.bishop = Bishop(team, firstPiece);
            break;
        case KNIGHT:
            pointer.knight = Knight(team, firstPiece);
            break;
        case ROOK:
            pointer.rook = Rook(team, firstPiece);
            break;
        default:
            fprintf(stderr, "Error: Wrong constructor used for initializing piece [Constructor 2].\n");
            exit(99);
    }
}

ChessPiece::ChessPiece(PieceType type, Color team, int col) {
    this->type = type;
    this->team = team;

    switch(type) {
        case PAWN:
            pointer.pawn = Pawn(team, col);
            break;
        default:
            fprintf(stderr, "Error: Wrong constructor used for initializing piece [Constructor 3].\n");
            exit(99);
    }
}

ChessPiece::ChessPiece(PieceType type, Color team, int row, int col) {
    this->type = type;
    this->team = team;

    switch(type) {
        case QUEEN:
            pointer.queen = Queen(team, row, col);
            break;
        case BISHOP:
            pointer.bishop = Bishop(team, row, col);
            break;
        case KNIGHT:
            pointer.knight = Knight(team, row, col);
            break;
        case ROOK:
            pointer.rook = Rook(team, row, col);
            break;
        default:
            fprintf(stderr, "Error: Wrong constructor used for initializing piece [Constructor 4].\n");
            exit(99);
    }
}

PieceType ChessPiece::getType() {
    return type;
}

Color ChessPiece::getTeam() {
    return team;
}

TypePointer ChessPiece::getPointer() {
    return pointer;
}

bool ChessPiece::move(int r, int c, ChessBoard* board){
    switch(type) {
        case KING:
            return (pointer.king).move(r, c, board);
        case QUEEN:
            return (pointer.queen).move(r, c, board);
        case BISHOP:
            return (pointer.bishop).move(r, c, board);
        case KNIGHT:
            return (pointer.knight).move(r, c);
        case ROOK:
            return (pointer.rook).move(r, c, board);
        case PAWN:
            return (pointer.pawn).move(r, c, board);
        default:
            fprintf(stderr, "Error: piece has no type [move()].\n");
            exit(99);
    }
}

void ChessPiece::print() {
    char teamChar = (team == WHITE) ? '*' : '_';
    switch(type) {
        case KING:
            printf("K%c", teamChar);
            break;
        case QUEEN:
            printf("Q%c", teamChar);
            break;
        case BISHOP:
            printf("B%c", teamChar);
            break;
        case KNIGHT:
            printf("N%c", teamChar);
            break;
        case ROOK:
            printf("R%c", teamChar);
            break;
        case PAWN:
            printf("p%c", teamChar);
            break;
        default:
            fprintf(stderr, "Error: piece has no type [print()].\n");
            exit(99);
    }
}

