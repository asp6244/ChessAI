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
    board[0][0] = new ChessPiece(ROOK, WHITE, false, 0);
    board[0][1] = new ChessPiece(KNIGHT, WHITE, false, 1);
    board[0][2] = new ChessPiece(BISHOP, WHITE, false, 2);
    board[0][3] = new ChessPiece(QUEEN, WHITE, 3);
    board[0][4] = new ChessPiece(KING, WHITE, 4);
    board[0][5] = new ChessPiece(BISHOP, WHITE, true, 5);
    board[0][6] = new ChessPiece(KNIGHT, WHITE, true, 6);
    board[0][7] = new ChessPiece(ROOK, WHITE, true, 7);

    // make black pieces
    board[7][0] = new ChessPiece(ROOK, BLACK, false, 16);
    board[7][1] = new ChessPiece(KNIGHT, BLACK, false, 17);
    board[7][2] = new ChessPiece(BISHOP, BLACK, false, 18);
    board[7][3] = new ChessPiece(QUEEN, BLACK, 19);
    board[7][4] = new ChessPiece(KING, BLACK, 20);
    board[7][5] = new ChessPiece(BISHOP, BLACK, true, 21);
    board[7][6] = new ChessPiece(KNIGHT, BLACK, true, 22);
    board[7][7] = new ChessPiece(ROOK, BLACK, true, 23);

    // make Pawns
    for(int i=0; i<8; i++) {
        board[1][i] = new ChessPiece(PAWN, WHITE, i, 8 + i);
        board[6][i] = new ChessPiece(PAWN, BLACK, i, 24 + i);
    }

    int rowIterator[4] = {0, 1, 6, 7};
    for(int row : rowIterator) {
        for(int col=0; col<8; col++) {
            // set hot squares
            setAllHotSquares(row, col, true, false);

            // set values in pointer dictionary
            ChessPiece* piece = board[row][col];
            pointerMap[piece->getID()] = piece;
        }
    }
    printHotSquares(false);
}

void ChessBoard::printBoard() {
    for(int i=7; i>=0; i--) {
        printf("   +----+----+----+----+----+----+----+----+");

        switch(i) {
            case 7:
                printf("     Captured White Pieces");
                break;
            case 6:
            case 5: {
                int j = (i==6) ? 4 : 12;
                int bound = j+4;
                printf("     ");
                for (; j < bound; j++) {
                    if (capturedWhitePieces[j] != nullptr) {
                        printf(" ");
                        capturedWhitePieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }}
                break;
            case 2:
                printf("     Captured Black Pieces");
                break;
            case 1:
            case 0: {
                int j = (i==1) ? 4 : 12;
                int bound = j+4;
                printf("     ");
                for (; j < bound; j++) {
                    if (capturedBlackPieces[j] != nullptr) {
                        printf(" ");
                        capturedBlackPieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }}
                break;
            default:
                break;
        }

        printf("\n%d  |", i+1);
        for(int j=0; j<8; j++)
        {
            printf(" ");
            if(board[i][j] != nullptr) {
                board[i][j]->print();
            } else {
                printf("  ");
            }
            printf(" |");
        }

        switch(i) {
            case 7:
            case 6: {
                int j = (i==7) ? 0 : 8;
                int bound = j+4;
                printf("     ");
                for (; j < bound; j++) {
                    if (capturedWhitePieces[j] != nullptr) {
                        printf(" ");
                        capturedWhitePieces[j]->print();
                    } else {
                        printf("   ");
                    }
                }}
                break;
            case 2:
            case 1: {
                int j = (i==2) ? 0 : 8;
                int bound = j+4;
                printf("     ");
                for (; j < bound; j++) {
                    if (capturedBlackPieces[j] != nullptr) {
                        printf(" ");
                        capturedBlackPieces[j]->print();
                    } else {
                        printf("  ");
                    }
                }}
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
        printf("  Invalid move, no piece at target square %c%d.\n", col+65, row+1);
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

            // remove hot squares from the piece that was captured
            setAllHotSquares(newRow, newCol, false, false);
        }

        // unset old hot squares
        setAllHotSquares(row, col, false, false);

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

        // set new hot squares
        setAllHotSquares(newRow, newCol, true, false);

        for(int i=0; i<32; i++) {
            // old location of moved piece
            if(hotSquares[row][col][i] || hotSquares[newRow][newCol][i]) {
                // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
                ChessPiece* pieceToEvaluate = pointerMap[i];
                switch(pieceToEvaluate->getType()) {
                    case QUEEN:
                    case BISHOP:
                    case ROOK:
                        setAllHotSquares(pieceToEvaluate->getRow(), pieceToEvaluate->getCol(), true, true);
                }
            }
        }

        printHotSquares(false);

        // TODO: iterate through pieces making old square hot and make them reset their hot pieces (reevaluating set to true)
        // TODO: do same for new square (reevaluating set to true, only time this can be true because something could have moved into the path)
        // TODO: only need to do this for pieces that can be blocked by an opponent: Queen, Bishop, Rook

        // TODO: white and black pieces can block each others hot paths, so you need to iterate through both or combine arrays
    }

    return validMove;
}

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

    // TODO: cleanup
    // execute rook movement
    int rookNewCol = (kingside) ? 5 : 3;
    //if(!movePiece(row, rookCol, row, rookNewCol)) {
        // printf("  Invalid move, Rook cannot castle.\n");
    //    return false;
    //}
    return movePiece(row, rookCol, row, rookNewCol);

    //return true;
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
        fprintf(stderr, "Error: promoted piece is null at %c%d.\n", col + 65, row+1);
        exit(99);
    }
    // check if promoted piece is pawn
    if(piece->getType() != PAWN) {
        fprintf(stderr, "Error: promoted piece is not a pawn %c%d.\n", col + 65, row+1);
        exit(99);
    }
    // check if pawn is in correct location
    Color team = piece->getTeam();
    if( !((team == WHITE && row == 7) || (team == BLACK && row == 0)) ) {
        fprintf(stderr, "Error: promoted piece is not at the other side of the board at %c%d.\n", col + 65, row+1);
        exit(99);
    }

    // free memory of promoted pawn
    delete board[row][col];
    board[row][col] = nullptr;

    // get pawn id to copy
    int id = piece->getID();

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
                board[row][col] = new ChessPiece(QUEEN, team, row, col, id);
                valid = true;
                break;
            case 'B':
            case 'b':
                board[row][col] = new ChessPiece(BISHOP, team, row, col, id);
                valid = true;
                break;
            case 'N':
            case 'n':
                board[row][col] = new ChessPiece(KNIGHT, team, row, col, id);
                valid = true;
                break;
            case 'R':
            case 'r':
                board[row][col] = new ChessPiece(ROOK, team, row, col, id);
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

void ChessBoard::setAllHotSquares(int row, int col, bool value, bool reevaluating) {
    ChessPiece* piece = board[row][col];
    if(piece == nullptr) {
        fprintf(stderr, "Error: piece to set hot is null at %c%d.\n", col + 65, row+1);
        exit(99);
    }

    Color team = piece->getTeam();
    int id = piece->getID();

    PieceType type = piece->getType();
    // set squares hot based on piece type
    switch(type) {
        case KING:
            setSquareHot(id, row, col+1, value);
            setSquareHot(id, row+1, col+1, value);
            setSquareHot(id, row+1, col, value);
            setSquareHot(id, row+1, col-1, value);
            setSquareHot(id, row, col-1, value);
            setSquareHot(id, row-1, col-1, value);
            setSquareHot(id, row-1, col, value);
            setSquareHot(id, row-1, col+1, value);
            break;
        case QUEEN:
        case BISHOP: {
            int incrementor[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}}; // incrementor for row and column
            int boundaries[4][2] = {{8, 8}, {8, -1}, {-1, -1}, {-1, 8}}; // boundaries for the board
            int rowInc, colInc, rowBound, colBound;
            bool pathBlocked; // used to determine when a piece is blocking the path of the checked piece

            // loop through all four directions that must be checked
            for(int i=0; i<4; i++) {
                rowInc = incrementor[i][0];
                colInc = incrementor[i][1];
                rowBound = boundaries[i][0];
                colBound = boundaries[i][1];
                pathBlocked = false;

                for(int r = row+rowInc, c = col+colInc; r != rowBound && c != colBound; r += rowInc, c += colInc) {
                    if(!pathBlocked) {
                        hotSquares[r][c][id] = value;
                        if(board[r][c] != nullptr) { // if statement succeeds setSquareHot to set hot the square with a piece on it
                            pathBlocked = true;
                        }
                    } else if(reevaluating) { // TODO: if might need to be removed
                        // ensure that all squares in the direction of the path after being blocked are set to false
                        // only needs to happen when value is true because this is only used when a piece has moved and
                        // all squares that made the old piece hot are being re-evaluated
                        hotSquares[r][c][id] = false;
                    }
                }
            }}

            // if the piece is a Queen, set hot squares in rank and file
            if(type == BISHOP) {
                break;
            }
        case ROOK:
            int inc, bound;
            bool pathBlocked;

            // loop through all four directions that must be checked
            for (int i = 0; i < 2; i++) {
                inc = i==0 ? 1 : -1;
                bound = i==0 ? 8 : -1;

                pathBlocked = false;
                for (int r = row + inc; r != bound; r += inc) {
                    if(!pathBlocked) {
                        hotSquares[r][col][id] = value;
                        if(board[r][col] != nullptr) { // if statement succeeds setSquareHot to set hot the square with a piece on it
                            pathBlocked = true;
                        }
                    } else if(reevaluating) { // TODO: if might need to be removed
                        // ensure that all squares in the direction of the path after being blocked are set to false
                        // only needs to happen when value is true because this is only used when a piece has moved and
                        // all squares that made the old piece hot are being re-evaluated
                        hotSquares[r][col][id] = false;
                    }
                }

                pathBlocked = false; // reset to false for new direction
                for (int c = col + inc; c != bound; c += inc) {
                    if(!pathBlocked) {
                        hotSquares[row][c][id] = value;
                        if(board[row][c] != nullptr) { // if statement succeeds setSquareHot to set hot the square with a piece on it
                            pathBlocked = true;
                        }
                    } else if(reevaluating) { // TODO: if might need to be removed
                        // ensure that all squares in the direction of the path after being blocked are set to false
                        // only needs to happen when value is true because this is only used when a piece has moved and
                        // all squares that made the old piece hot are being re-evaluated
                        hotSquares[row][c][id] = false;
                    }
                }
            }
            break;
        case KNIGHT:
            setSquareHot(id, row+1, col+2, value);
            setSquareHot(id, row+2, col+1, value);
            setSquareHot(id, row+2, col-1, value);
            setSquareHot(id, row+1, col-2, value);
            setSquareHot(id, row-1, col-2, value);
            setSquareHot(id, row-2, col-1, value);
            setSquareHot(id, row-2, col+1, value);
            setSquareHot(id, row-1, col+2, value);
            break;
        case PAWN:
            if(team == WHITE) {
                setSquareHot(id, row+1, col+1, value);
                setSquareHot(id, row+1, col-1, value);
            } else {
                setSquareHot(id, row-1, col+1, value);
                setSquareHot(id, row-1, col-1, value);
            }
            break;
        default:
            fprintf(stderr, "Error: piece has no type [setHotSquares].\n");
            exit(99);
    }
}

void ChessBoard::setSquareHot(int id, int row, int col, bool value) {
    if((row >= 0 && row < 8) && (col >= 0 && col < 8)) {
        hotSquares[row][col][id] = value;
    }
}

void ChessBoard::printHotSquares(bool printValues) {
    printf("Printing hot squares...\n");

    if(printValues) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                printf("Row: %d    Col: %d\n", i, j);
                printf("    White:    Black:\n");
                for (int k = 0; k < 16; k++) {
                    if(k<=9) {
                        printf(" ");
                    }
                    printf("%d: ", k);
                    if (hotSquares[i][j][k]) {
                        printf("X");
                    } else {
                        printf(" ");
                    }
                    printf("         ");
                    if (hotSquares[i][j][k+16]) {
                        printf("O");
                    }
                    printf("\n");
                }
            }
        }
    }

    for(int i=7; i>=0; i--) {
        printf("   +----+----+----+----+----+----+----+----+");

        printf("\n%d  |", i+1);
        for(int j=0; j<8; j++)
        {
            bool whiteHot = false, blackHot = false;
            for(int k=0; k<16; k++) {
                whiteHot |= hotSquares[i][j][k];
                blackHot |= hotSquares[i][j][k+16];
            }

            printf(" ");

            if(whiteHot) {
                printf("X");
            } else {
                printf(" ");
            }

            if(blackHot) {
                printf("O");
            } else {
                printf(" ");
            }

            printf(" |");
        }

        printf("\n");
    }
    printf("   +----+----+----+----+----+----+----+----+\n");
    printf("     A    B    C    D    E    F    G    H   \n");

    printf("\n");
    fflush(stdout);
}

