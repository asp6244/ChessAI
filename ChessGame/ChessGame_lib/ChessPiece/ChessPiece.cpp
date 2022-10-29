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

ChessPiece::ChessPiece(PieceType type, Color team, int file, int id) {
    this->type = type;
    this->team = team;
    this->id = id;

    switch(type) {
        case PAWN:
            pointer.pawn = new Pawn(team, file);
            break;
        default:
            fprintf(stderr, "Error: Wrong constructor used for initializing piece [Constructor 3].\n");
            exit(99);
    }
}

ChessPiece::ChessPiece(PieceType type, Color team, int rank, int file, int id) {
    this->type = type;
    this->team = team;
    this->id = id;

    switch(type) {
        case QUEEN:
            pointer.queen = new Queen(team, rank, file);
            break;
        case BISHOP:
            pointer.bishop = new Bishop(team, rank, file);
            break;
        case KNIGHT:
            pointer.knight = new Knight(team, rank, file);
            break;
        case ROOK:
            pointer.rook = new Rook(team, rank, file);
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

bool ChessPiece::validateMove(int r, int f, ChessBoard* board){
    switch(type) {
        case KING:
            return (pointer.king)->validateMove(r, f, board);
        case QUEEN:
            return (pointer.queen)->validateMove(r, f, board);
        case BISHOP:
            return (pointer.bishop)->validateMove(r, f, board);
        case KNIGHT:
            return (pointer.knight)->validateMove(r, f);
        case ROOK:
            return (pointer.rook)->validateMove(r, f, board);
        case PAWN:
            return (pointer.pawn)->validateMove(r, f, board);
        default:
            fprintf(stderr, "Error: piece has no type [move()].\n");
            exit(99);
    }
}

void ChessPiece::makeMove() {
    switch(type) {
        case KING:
            (pointer.king)->makeMove();
            break;
        case QUEEN:
            (pointer.queen)->makeMove();
            break;
        case BISHOP:
            (pointer.bishop)->makeMove();
            break;
        case KNIGHT:
            (pointer.knight)->makeMove();
            break;
        case ROOK:
            (pointer.rook)->makeMove();
            break;
        case PAWN:
            (pointer.pawn)->makeMove();
            break;
        default:
            fprintf(stderr, "Error: piece has no type [makeMove()].\n");
            exit(99);
    }
}

int ChessPiece::getRank() {
    switch(type) {
        case KING:
            return (pointer.king)->getRank();
        case QUEEN:
            return (pointer.queen)->getRank();
        case BISHOP:
            return (pointer.bishop)->getRank();
        case KNIGHT:
            return (pointer.knight)->getRank();
        case ROOK:
            return (pointer.rook)->getRank();
        case PAWN:
            return (pointer.pawn)->getRank();
        default:
            fprintf(stderr, "Error: piece has no type [getRank()].\n");
            exit(99);
    }
}

int ChessPiece::getFile() {
    switch(type) {
        case KING:
            return (pointer.king)->getFile();
        case QUEEN:
            return (pointer.queen)->getFile();
        case BISHOP:
            return (pointer.bishop)->getFile();
        case KNIGHT:
            return (pointer.knight)->getFile();
        case ROOK:
            return (pointer.rook)->getFile();
        case PAWN:
            return (pointer.pawn)->getFile();
        default:
            fprintf(stderr, "Error: piece has no type [getFile()].\n");
            exit(99);
    }
}

void ChessPiece::resetValidation() {
    switch(type) {
        case KING:
            (pointer.king)->resetValidation();
            break;
        case QUEEN:
            (pointer.queen)->resetValidation();
            break;
        case BISHOP:
            (pointer.bishop)->resetValidation();
            break;
        case KNIGHT:
            (pointer.knight)->resetValidation();
            break;
        case ROOK:
            (pointer.rook)->resetValidation();
            break;
        case PAWN:
            (pointer.pawn)->resetValidation();
            break;
        default:
            fprintf(stderr, "Error: piece has no type [resetValidation()].\n");
            exit(99);
    }
}

void ChessPiece::pieceCaptured() {
    isCaptured = true;
}

bool ChessPiece::getIsCaptured() {
    return isCaptured;
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

void ChessPiece::deletePiece(){
    switch(type) {
        case KING:
            delete pointer.king;
            break;
        case QUEEN:
            delete pointer.queen;
            break;
        case BISHOP:
            delete pointer.bishop;
            break;
        case KNIGHT:
            delete pointer.knight;
            break;
        case ROOK:
            delete pointer.rook;
            break;
        case PAWN:
            delete pointer.pawn;
            break;
        default:
            fprintf(stderr, "Error: piece has no type [delete()].\n");
            exit(99);
    }
}

