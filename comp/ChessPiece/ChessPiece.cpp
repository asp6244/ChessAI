//
// Created by alecs on 4/30/2020.
//

#include <cmath>
#include <cstdio>
#include "ChessPiece.h"

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

