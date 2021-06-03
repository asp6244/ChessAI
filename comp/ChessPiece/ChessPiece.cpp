//
// Created by alecs on 4/30/2020.
//

#include <cmath>
#include <cstdio>
#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceType type, Color team, int id) {
    this->type = type;
    this->team = team;
    this->id = id;

    switch(type) {
        case KING:
            pointer.king = new King(team);
            break;
        case QUEEN:
            pointer.queen = new Queen(team);
            break;
        default:
            fprintf(stderr, "Error: Wrong constructor used for initializing piece [Constructor 1].\n");
            exit(99);
    }
}

ChessPiece::ChessPiece(PieceType type, Color team, bool kingside, int id) {
    this->type = type;
    this->team = team;
    this->id = id;

    switch(type) {
        case BISHOP:
            pointer.bishop = new Bishop(team, kingside);
            break;
        case KNIGHT:
            pointer.knight = new Knight(team, kingside);
            break;
        case ROOK:
            pointer.rook = new Rook(team, kingside);
            break;
        default:
            fprintf(stderr, "Error: Wrong constructor used for initializing piece [Constructor 2].\n");
            exit(99);
    }
}

ChessPiece::ChessPiece(PieceType type, Color team, int col, int id) {
    this->type = type;
    this->team = team;
    this->id = id;

    switch(type) {
        case PAWN:
            pointer.pawn = new Pawn(team, col);
            break;
        default:
            fprintf(stderr, "Error: Wrong constructor used for initializing piece [Constructor 3].\n");
            exit(99);
    }
}

ChessPiece::ChessPiece(PieceType type, Color team, int row, int col, int id) {
    this->type = type;
    this->team = team;
    this->id = id;

    switch(type) {
        case QUEEN:
            pointer.queen = new Queen(team, row, col);
            break;
        case BISHOP:
            pointer.bishop = new Bishop(team, row, col);
            break;
        case KNIGHT:
            pointer.knight = new Knight(team, row, col);
            break;
        case ROOK:
            pointer.rook = new Rook(team, row, col);
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

bool ChessPiece::validateMove(int r, int c, ChessBoard* board){
    switch(type) {
        case KING:
            return (pointer.king)->validateMove(r, c, board);
        case QUEEN:
            return (pointer.queen)->validateMove(r, c, board);
        case BISHOP:
            return (pointer.bishop)->validateMove(r, c, board);
        case KNIGHT:
            return (pointer.knight)->validateMove(r, c);
        case ROOK:
            return (pointer.rook)->validateMove(r, c, board);
        case PAWN:
            return (pointer.pawn)->validateMove(r, c, board);
        default:
            fprintf(stderr, "Error: piece has no type [move()].\n");
            exit(99);
    }
}

void ChessPiece::makeMove() {
    switch(type) {
        case KING:
            (pointer.king)->makeMove();
        case QUEEN:
            (pointer.queen)->makeMove();
        case BISHOP:
            (pointer.bishop)->makeMove();
        case KNIGHT:
            (pointer.knight)->makeMove();
        case ROOK:
            (pointer.rook)->makeMove();
        case PAWN:
            (pointer.pawn)->makeMove();
        default:
            fprintf(stderr, "Error: piece has no type [makeMove()].\n");
            exit(99);
    }
}

int ChessPiece::getRow() {
    switch(type) {
        case KING:
            return (pointer.king)->getRow();
        case QUEEN:
            return (pointer.queen)->getRow();
        case BISHOP:
            return (pointer.bishop)->getRow();
        case KNIGHT:
            return (pointer.knight)->getRow();
        case ROOK:
            return (pointer.rook)->getRow();
        case PAWN:
            return (pointer.pawn)->getRow();
        default:
            fprintf(stderr, "Error: piece has no type [getRow()].\n");
            exit(99);
    }
}

int ChessPiece::getCol() {
    switch(type) {
        case KING:
            return (pointer.king)->getCol();
        case QUEEN:
            return (pointer.queen)->getCol();
        case BISHOP:
            return (pointer.bishop)->getCol();
        case KNIGHT:
            return (pointer.knight)->getCol();
        case ROOK:
            return (pointer.rook)->getCol();
        case PAWN:
            return (pointer.pawn)->getCol();
        default:
            fprintf(stderr, "Error: piece has no type [getCol()].\n");
            exit(99);
    }
}

void ChessPiece::resetValidation() {
    switch(type) {
        case KING:
            (pointer.king)->resetValidation();
        case QUEEN:
            (pointer.queen)->resetValidation();
        case BISHOP:
            (pointer.bishop)->resetValidation();
        case KNIGHT:
            (pointer.knight)->resetValidation();
        case ROOK:
            (pointer.rook)->resetValidation();
        case PAWN:
            (pointer.pawn)->resetValidation();
        default:
            fprintf(stderr, "Error: piece has no type [resetValidation()].\n");
            exit(99);
    }
}

int ChessPiece::getID() {
    return id;
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

