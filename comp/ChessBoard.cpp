//
// Created by alecs on 4/30/2020.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "ChessBoard.h"

ChessBoard::ChessBoard() {
    // make white pieces
    board[0][0] = new ChessPiece(ROOK, WHITE, true);
    board[0][1] = new ChessPiece(KNIGHT, WHITE, true);
    board[0][2] = new ChessPiece(BISHOP, WHITE, true);
    board[0][3] = new ChessPiece(QUEEN, WHITE);
    board[0][4] = new ChessPiece(KING, WHITE);
    board[0][5] = new ChessPiece(BISHOP, WHITE, false);
    board[0][6] = new ChessPiece(KNIGHT, WHITE, false);
    board[0][7] = new ChessPiece(ROOK, WHITE, false);

    // make black pieces
    board[7][0] = new ChessPiece(ROOK, BLACK, true);
    board[7][1] = new ChessPiece(KNIGHT, BLACK, true);
    board[7][2] = new ChessPiece(BISHOP, BLACK, true);
    board[7][3] = new ChessPiece(QUEEN, BLACK);
    board[7][4] = new ChessPiece(KING, BLACK);
    board[7][5] = new ChessPiece(BISHOP, BLACK, false);
    board[7][6] = new ChessPiece(KNIGHT, BLACK, false);
    board[7][7] = new ChessPiece(ROOK, BLACK, false);

    // make Pawns
    for(int i=0; i<8; i++) {
        board[1][i] = new ChessPiece(PAWN, WHITE, i);
        board[6][i] = new ChessPiece(PAWN, BLACK, i);
    }
}

void ChessBoard::printBoard() {
    for(int i=7; i>=0; i--) {
        printf("   +----+----+----+----+----+----+----+----+");

        switch(i) {
            case 7:
                printf("     Captured White Pieces");
                break;
            case 6:
                printf("     ");
                for (int j = 4; j < 8; j++) {
                    if (capturedWhitePieces[j] != nullptr) {
                        printf(" ");
                        capturedWhitePieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }
                break;
            case 5:
                printf("     ");
                for (int j = 12; j < 16; j++) {
                    if (capturedWhitePieces[j] != nullptr) {
                        printf(" ");
                        capturedWhitePieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }
                break;
            case 2:
                printf("     Captured Black Pieces");
                break;
            case 1:
                printf("     ");
                for (int j = 4; j < 8; j++) {
                    if (capturedBlackPieces[j] != nullptr) {
                        printf(" ");
                        capturedBlackPieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }
                break;
            case 0:
                printf("     ");
                for (int j = 12; j < 16; j++) {
                    if (capturedBlackPieces[j] != nullptr) {
                        printf(" ");
                        capturedBlackPieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }
                break;
            default:
                break;
        }

        printf("\n%d  |", i+1);
        for(int j=0; j<8; j++)
        {
            if(board[i][j] != nullptr) {
                printf(" ");
                board[i][j]->print();
                printf(" |");
            } else {
                printf("    |");
            }
        }

        switch(i) {
            case 7:
                printf("     ");
                for (int j = 0; j < 4; j++) {
                    if (capturedWhitePieces[j] != nullptr) {
                        printf(" ");
                        capturedWhitePieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }
                break;
            case 6:
                printf("     ");
                for (int j = 8; j < 12; j++) {
                    if (capturedWhitePieces[j] != nullptr) {
                        printf(" ");
                        capturedWhitePieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }
                break;
            case 2:
                printf("     ");
                for (int j = 0; j < 4; j++) {
                    if (capturedBlackPieces[j] != nullptr) {
                        printf(" ");
                        capturedBlackPieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }
                break;
            case 1:
                printf("     ");
                for (int j = 8; j < 12; j++) {
                    if (capturedBlackPieces[j] != nullptr) {
                        printf(" ");
                        capturedBlackPieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }
                break;
            default:
                break;
        }

        printf("\n");
    }
    printf("   +----+----+----+----+----+----+----+----+\n");
    printf("     A    B    C    D    E    F    G    H   \n");
    fflush(stdout);
}

bool ChessBoard::movePiece(int row, int col, int newRow, int newCol) {
    // check if input is in bounds of board
    if( (newRow > 7 || newRow < 0) || (newCol > 7 || newCol < 0) ) {
        printf("  Invalid move, proposed move is not inside the board.\n");
        return false;
    }

    ChessPiece* piece = board[row][col]; // get the piece to be moved
    // check if moved piece is a valid piece
    if(piece == nullptr) {
        printf("  Invalid move, no piece at target square %c%d.\n", col+65, row);
        return false;
    }

    ChessPiece* proposedMove = board[newRow][newCol]; // get the piece at the spot of the proposed move, if one exists
    // check if piece at proposed move exists
    if(proposedMove != nullptr) {
        // make sure the proposed move is not an allied piece of the moved piece
        if(piece->getTeam() == proposedMove->getTeam()) {
            printf("  Invalid move, proposed move is on top of an allied piece.\n");
            return false;
        }
    }

    // make move
    bool validMove = piece->move(newRow, newCol, this);

    // if valid move
    if(validMove) {
        // if capturing piece
        if(proposedMove != nullptr) {
            // move captured piece to array of captured pieces
            if(proposedMove->getTeam() == WHITE) {
                capturedWhitePieces[capturedWhitePiecesSize] = proposedMove;
                capturedWhitePiecesSize++;
            } else {
                capturedBlackPieces[capturedBlackPiecesSize] = proposedMove;
                capturedBlackPiecesSize++;
            }
        }

        // move piece
        board[newRow][newCol] = piece;
        board[row][col] = nullptr;

        // look for promotion from pawn
        if(piece->getType() == PAWN) {
            Color team = piece->getTeam();
            if ((newRow == 7 && team == WHITE) || (newRow == 0 && team == BLACK)) {
                promotion(newRow, newCol);
            }
        }
    }

    return validMove;
}

// moves Rook to correct position for a castle
bool ChessBoard::castle(Color team, bool kingside) {
    int row = (team == WHITE) ? 0 : 7;
    int rookCol = (kingside) ? 7 : 0;

    // check if Rook piece is valid to castle
    ChessPiece* maybeRook = board[row][rookCol];
    if(maybeRook == nullptr) {
        printf("  Invalid move, Rook has been moved and cannot castle.\n");
        return false;
    } else if(maybeRook->getType() != ROOK) {
        printf("  Invalid move, Rook has been moved and cannot castle.\n");
        return false;
    }

    // get Rook piece
    Rook rook = maybeRook->getPointer().rook;
    if(!rook.getHasNotMoved()) {
        printf("  Invalid move, Rook has been moved and cannot castle.\n");
        return false;
    }

    // execute rook movement
    int rookNewCol = (kingside) ? 5 : 3;
    if(!movePiece(row, rookCol, row, rookNewCol)) {
        printf("  Invalid move, Rook cannot castle.\n");
        return false;
    }

    return true;
}

ChessPiece* ChessBoard::getPiece(int row, int col) {
    return board[row][col];
}

void ChessBoard::destroyBoard() {
    // delete all pieces in board
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(board[i][j] != nullptr) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }

    // delete all pieces in arrays for captured pieces;
    for(int i=0; i<16; i++) {
        if(capturedWhitePieces[i] != nullptr) {
            delete capturedWhitePieces[i];
            capturedWhitePieces[i] = nullptr;
        }
        if(capturedBlackPieces[i] != nullptr) {
            delete capturedBlackPieces[i];
            capturedBlackPieces[i] = nullptr;
        }
    }
    capturedWhitePiecesSize = 0;
    capturedBlackPiecesSize = 0;
}

void ChessBoard::promotion(int row, int col) {
    printBoard();

    ChessPiece* piece = board[row][col]; // get the piece to be promoted

    // TODO: maybe remove these checks
    // check if promoted piece is a valid piece
    if(piece == nullptr) {
        fprintf(stderr, "Error: promoted piece is null at %c%d.\n", col + 56, row);
        exit(99);
    }
    // check if promoted piece is pawn
    if(piece->getType() != PAWN) {
        fprintf(stderr, "Error: promoted piece is not a pawn %c%d.\n", col + 56, row);
        exit(99);
    }
    // check if pawn is in correct location
    Color team = piece->getTeam();
    if( !((team == WHITE && row == 7) || (team == BLACK && row == 0)) ) {
        fprintf(stderr, "Error: promoted piece is not at the other side of the board at %c%d.\n", col + 56, row);
        exit(99);
    }

    // free memory of promoted pawn
    delete board[row][col];
    board[row][col] = nullptr;

    // get promotion request from player
    printf("Pawn promoted! Which piece should the Pawn be promoted to?\n"
           "'Q' - Queen     'B' - Bishop     'N' - Knight     'R' - Rook\n>>");

    // check for valid input
    bool valid = false;
    do {
        std::string input;
        std::getline(std::cin, input);

        // create new piece
        switch(input[0]) {
            case 'Q':
            case 'q':
                board[row][col] = new ChessPiece(QUEEN, team, row, col);
                valid = true;
                break;
            case 'B':
            case 'b':
                board[row][col] = new ChessPiece(BISHOP, team, row, col);
                valid = true;
                break;
            case 'N':
            case 'n':
                board[row][col] = new ChessPiece(KNIGHT, team, row, col);
                valid = true;
                break;
            case 'R':
            case 'r':
                board[row][col] = new ChessPiece(ROOK, team, row, col);
                valid = true;
                break;
            default:
                printf("  Invalid input.\n>>");
        }
    } while(!valid);
}

bool ChessBoard::getCheck() {
    return check;
}

bool ChessBoard::getCheckMate() {
    return checkMate;
}

