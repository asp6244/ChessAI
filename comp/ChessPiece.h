//
// Created by alecs on 4/30/2020.
//

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include "ChessBoard.h"

enum PieceType {
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN
};

enum Color {
    BLACK,
    WHITE
};

class King {
protected:
    Color team;
    int row;
    int col;
    bool hasNotMoved = true;
public:
    King(Color team);
    bool move(int r, int c, ChessBoard* board);
};

class Queen {
protected:
    Color team;
    int row;
    int col;
public:
    Queen(Color team);
    Queen(Color team, int row, int col); // Pawn gets promoted
    bool move(int r, int c, ChessBoard* board);
};

class Bishop {
protected:
    Color team;
    int row;
    int col;
public:
    Bishop(Color team, bool bishopAtC);
    Bishop(Color team, int row, int col); // Pawn gets promoted
    bool move(int r, int c, ChessBoard* board);
};

class Knight {
protected:
    Color team;
    int row;
    int col;
public:
    Knight(Color team, bool knightAtB);
    Knight(Color team, int row, int col); // Pawn gets promoted
    bool move(int r, int c);
};

class Rook {
protected:
    Color team;
    int row;
    int col;
    bool hasNotMoved = true;
public:
    Rook(Color team, bool rookAtA);
    Rook(Color team, int row, int col); // Pawn gets promoted
    bool move(int r, int c, ChessBoard* board);
    bool getHasNotMoved();
};

class Pawn {
protected:
    Color team;
    int row;
    int col;
    bool hasNotMoved = true;
public:
    Pawn(Color team, int col);
    bool move(int r, int c, ChessBoard* board);
};

union TypePointer {
    int null;
    King king;
    Queen queen;
    Bishop bishop;
    Knight knight;
    Rook rook;
    Pawn pawn;
};

class ChessPiece {
protected:
    PieceType type;
    TypePointer pointer{};
    Color team;
public:
    ChessPiece(PieceType type, Color team); // King, Queen
    ChessPiece(PieceType type, Color team, bool firstPiece); // Rook, Knight, Bishop
    ChessPiece(PieceType type, Color team, int col); // Pawn
    ChessPiece(PieceType type, Color team, int row, int col); // promoted Pawn - Queen, Rook, Knight, Bishop
    PieceType getType();
    Color getTeam();
    TypePointer getPointer();
    bool move(int r, int c, ChessBoard* board);
    void print();
};

#endif //CHESS_CHESSPIECE_H
