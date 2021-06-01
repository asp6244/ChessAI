//
// Created by alecs on 4/30/2020.
//

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"

enum PieceType {
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN
};

enum Color {
    WHITE,
    BLACK
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
    int id; // white is positive; black is negative
public:
    ChessPiece(PieceType type, Color team, int id); // King, Queen
    ChessPiece(PieceType type, Color team, bool kingside, int id); // Rook, Knight, Bishop
    ChessPiece(PieceType type, Color team, int col, int id); // Pawn
    ChessPiece(PieceType type, Color team, int row, int col, int id); // promoted Pawn - Queen, Rook, Knight, Bishop
    PieceType getType();
    Color getTeam();
    TypePointer getPointer();
    bool move(int r, int c, ChessBoard* board);
    int getRow();
    int getCol();
    int getID();
    void print();
};

#endif //CHESS_CHESSPIECE_H
