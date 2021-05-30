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
    BLACK,
    WHITE
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
