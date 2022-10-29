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
#include "ColorsType.h"

enum PieceType {
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN
};

union TypePointer {
    King* king;
    Queen* queen;
    Bishop* bishop;
    Knight* knight;
    Rook* rook;
    Pawn* pawn;
};

class ChessPiece {
protected:
    PieceType type;
    TypePointer pointer;
    Color team;
    int id; // white is positive; black is negative
    bool isCaptured = false;
public:
    ChessPiece(PieceType type, Color team, int id); // King, Queen
    ChessPiece(PieceType type, Color team, bool kingside, int id); // Rook, Knight, Bishop
    ChessPiece(PieceType type, Color team, int file, int id); // Pawn
    ChessPiece(PieceType type, Color team, int rank, int file, int id); // promoted Pawn - Queen, Rook, Knight, Bishop
    PieceType getType();
    Color getTeam();
    TypePointer getPointer();
    bool validateMove(int r, int f, ChessBoard* board);
    void makeMove();
    int getRank();
    int getFile();
    void resetValidation();
    void pieceCaptured();
    bool getIsCaptured();
    int getID();
    void print();
    void deletePiece();
};

#endif //CHESS_CHESSPIECE_H
