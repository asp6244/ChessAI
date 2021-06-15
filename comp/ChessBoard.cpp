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
    board[0][0] = new ChessPiece(ROOK, WHITE, false, ROOK_QS_ID);
    board[0][1] = new ChessPiece(KNIGHT, WHITE, false, KNIGHT_QS_ID);
    board[0][2] = new ChessPiece(BISHOP, WHITE, false, BISHOP_QS_ID);
    board[0][3] = new ChessPiece(QUEEN, WHITE, QUEEN_ID);
    board[0][4] = new ChessPiece(KING, WHITE, KING_ID);
    board[0][5] = new ChessPiece(BISHOP, WHITE, true, BISHOP_KS_ID);
    board[0][6] = new ChessPiece(KNIGHT, WHITE, true, KNIGHT_KS_ID);
    board[0][7] = new ChessPiece(ROOK, WHITE, true, ROOK_KS_ID);

    // make black pieces
    board[7][0] = new ChessPiece(ROOK, BLACK, false, ROOK_QS_ID + BLACK_ID_OFFSET);
    board[7][1] = new ChessPiece(KNIGHT, BLACK, false, KNIGHT_QS_ID + BLACK_ID_OFFSET);
    board[7][2] = new ChessPiece(BISHOP, BLACK, false, BISHOP_QS_ID + BLACK_ID_OFFSET);
    board[7][3] = new ChessPiece(QUEEN, BLACK, QUEEN_ID + BLACK_ID_OFFSET);
    board[7][4] = new ChessPiece(KING, BLACK, KING_ID + BLACK_ID_OFFSET);
    board[7][5] = new ChessPiece(BISHOP, BLACK, true, BISHOP_KS_ID + BLACK_ID_OFFSET);
    board[7][6] = new ChessPiece(KNIGHT, BLACK, true, KNIGHT_KS_ID + BLACK_ID_OFFSET);
    board[7][7] = new ChessPiece(ROOK, BLACK, true, ROOK_KS_ID + BLACK_ID_OFFSET);

    // make Pawns
    for(int i=0; i<8; i++) {
        board[1][i] = new ChessPiece(PAWN, WHITE, i, PAWS_START_ID + i);
        board[6][i] = new ChessPiece(PAWN, BLACK, i, PAWS_START_ID + BLACK_ID_OFFSET + i);
    }

    int rowIterator[4] = {0, 1, 6, 7};
    for(int row : rowIterator) {
        for(int col=0; col<8; col++) {
            // set hot squares
            setAllHotSquares(row, col, true, false);

            // set values in pointer map
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

    Color team = piece->getTeam();

    ChessPiece* proposedMove = board[newRow][newCol]; // get the piece at the spot of the proposed move, if one exists
    // check if piece at proposed move exists
    if(proposedMove != nullptr) {
        // make sure the proposed move is not an allied piece of the moved piece
        if(team == proposedMove->getTeam()) {
            if( (row == newRow) && (col == newCol) ) {
                printf("  Invalid move, no movement made.\n");
            } else {
                printf("  Invalid move, proposed move is on top of an allied piece.\n");
            }
            return false;
        }
    }

    // TODO: if player is in check, move must remove check

    // TODO: check for valid movement
    bool validMove = piece->validateMove(newRow, newCol, this);
    if(!validMove) {
        return false;
    }

    // TODO: remove hot squares
    // if capturing piece
    if(proposedMove != nullptr) {
        // remove hot squares from the piece that was captured
        setAllHotSquares(newRow, newCol, false, false);
    }

    // unset old hot squares
    setAllHotSquares(row, col, false, false);

    bool kingside;
    int rookCol;
    int newRookCol;
    ChessPiece* rook;
    if(castling) {
        kingside = (newCol-col == 2);
        rookCol = (kingside) ? 7 : 0;

        // unset old hot squares
        setAllHotSquares(row, rookCol, false, false);
    }

    // TODO: make pseudo movement
    board[newRow][newCol] = piece;
    board[row][col] = nullptr;
    // TODO: make pseudo castle movement
    if(castling) {
        newRookCol = (kingside) ? 5 : 3;

        rook = board[row][rookCol];
        board[row][newRookCol] = rook;
        board[row][rookCol] = nullptr;
    }

    // TODO: reevaluate opponent hot squares
    int i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
    int bound = (team == WHITE) ? 32 : BLACK_ID_OFFSET;
    for(; i<bound; i++) {
        // old location and new location of moved piece
        if(hotSquares[row][col][i] || hotSquares[newRow][newCol][i]) {
            // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
            ChessPiece* pieceToEvaluate = pointerMap[i];
            switch(pieceToEvaluate->getType()) {
                case QUEEN:
                case BISHOP:
                case ROOK:
                    // reevaluate the hot squares for the pieces that were making the old and new location hot
                    setAllHotSquares(pieceToEvaluate->getRow(), pieceToEvaluate->getCol(), true, true);
                    // only true when not castling, since in a castle the king and rook are not blocking any pieces from seeing the king
            }
        }
    }

    // TODO: check to see if, after movement, king is not in check
    if(team == WHITE) {
        setWhiteCheck(false);
    } else {
        setBlackCheck(false);
    }

    if( (whiteCheck && team == WHITE) || (blackCheck && team == BLACK) ) {
        // king is in check following movement
        printf("  Invalid move, King is in check after move.\n");

        // TODO: otherwise, reset pieces (including proposedMove), hot squares, resetValidation, and return false


        // set back the moved pieces into their original locations
        board[row][col] = piece;
        board[newRow][newCol] = proposedMove;
        if(castling) {
            board[row][newRookCol] = nullptr;
            board[row][rookCol] = rook;
        }

        // set hot squares back
        if(proposedMove != nullptr) {
            setAllHotSquares(newRow, newCol, true, false); // captured piece
        }
        setAllHotSquares(row, col, true, false); // moved piece
        if(castling) {
            setAllHotSquares(row, rookCol, true, false);
        }

        // TODO: reevaluate affected pieces
        // reevaluate affected opponent pieces
        i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
        bound = (team == WHITE) ? 32 : BLACK_ID_OFFSET;
        for(; i<bound; i++) {
            // old location and new location of moved piece
            if(hotSquares[row][col][i] || hotSquares[newRow][newCol][i]) {
                // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
                ChessPiece* pieceToEvaluate = pointerMap[i];
                switch(pieceToEvaluate->getType()) {
                    case QUEEN:
                    case BISHOP:
                    case ROOK:
                        // reevaluate the hot squares for the pieces that were making the old and new location hot
                        setAllHotSquares(pieceToEvaluate->getRow(), pieceToEvaluate->getCol(), true, true);
                        // only true when not castling, since in a castle the king and rook are not blocking any pieces from seeing the king
                }
            }
        }

        // reset the valid move status for the moved piece(s)
        piece->resetValidation();
        if(castling) {
            rook->resetValidation();
        }

        return false;
    }


    // TODO: if so, make move and update check, set hot squares
    // move is valid

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
        proposedMove->pieceCaptured();
    }

    // TODO: this is new code
    // move piece
    piece->makeMove();
    if(castling) {
        rook->makeMove();
    }

    // look for promotion from pawn
    if(piece->getType() == PAWN) {
        Color team = piece->getTeam();
        if ((newRow == 7 && team == WHITE) || (newRow == 0 && team == BLACK)) {
            promotion(newRow, newCol);
        }
    }

    // TODO: set hot squares back
    // set new hot squares
    setAllHotSquares(newRow, newCol, true, false);
    if(castling) {
        setAllHotSquares(row, newRookCol, true, false);
    }

    // TODO: I modified this range
    // only need to reevaluate allied pieces, since this was already done for opponent pieces
    i = (team == WHITE) ? 0 : BLACK_ID_OFFSET;
    bound = (team == WHITE) ? BLACK_ID_OFFSET : 32;
    for(; i<bound; i++) {
        // old location and new location of moved piece
        if(hotSquares[row][col][i] || hotSquares[newRow][newCol][i]) {
            // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
            ChessPiece* pieceToEvaluate = pointerMap[i];
            switch(pieceToEvaluate->getType()) {
                case QUEEN:
                case BISHOP:
                case ROOK:
                    // reevaluate the hot squares for the pieces that were making the old and new location hot
                    setAllHotSquares(pieceToEvaluate->getRow(), pieceToEvaluate->getCol(), true, true);
                    // only true when not castling, since in a castle the king and rook are not blocking any pieces from seeing the king
            }
        }
    }

    // TODO: I don't think both checks need to be set again
    // set the opponents check status, since the moving players check status has already been set
    stalemate = true; // used to determine if stalemate needs to be checked
    if(team == WHITE) {
        setBlackCheck(true);

        if(stalemate) { // stalemate needs to be checked if checking for checkmate did not return false for stalemate
            setWhiteStalemate();
        }
    } else {
        setWhiteCheck(true);

        if(stalemate) { // stalemate needs to be checked if checking for checkmate did not return false for stalemate
            setBlackStalemate();
        }
    }

    printHotSquares(false); // TODO: remove

    castling = false;

    // reset the valid move status for the moved piece(s)
    piece->resetValidation();
    if(castling) {
        rook->resetValidation();
    }

    return true;
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
    Rook* rook = maybeRook->getPointer().rook;
    if(!rook->getHasNotMoved()) {
        printf("  Invalid move, Rook has been moved and cannot castle.\n");
        return false;
    }

    int rookNewCol = (kingside) ? 5 : 3;

    // TODO: king can't move through check : validate this
    // look through all black pieces for piece making the kings piece hot
    int i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
    int bound = (team == WHITE) ? 32 : BLACK_ID_OFFSET;
    for(; i<bound; i++) {
        if(hotSquares[row][rookNewCol][i]) {
            printf("  Invalid move, King cannot castle through check.\n");
            return false; // check mate only occurs if check occurs
        }
    }

    // execute rook movement
    if(!movePiece(row, rookCol, row, rookNewCol)) {
        return false;
    }

    // set castling boolean if valid castle
    castling = true;
    return true;
}

ChessPiece* ChessBoard::getPiece(int row, int col) {
    return board[row][col];
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

void ChessBoard::setWhiteCheck(bool checkCheckmate) {
    ChessPiece* king = pointerMap[KING_ID];
    int row = king->getRow();
    int col = king->getCol();

    whiteCheck = false;
    // look through all black pieces for piece making the kings piece hot
    for(int i=BLACK_ID_OFFSET; i<32; i++) {
        if(hotSquares[row][col][i]) {
            whiteCheck = true;
            break;
        }
    }

    // checkmate only occurs when check occurs
    if(whiteCheck && checkCheckmate) {
        setWhiteCheckmate();
    }
}

bool ChessBoard::getWhiteCheck() {
    return whiteCheck;
}

void ChessBoard::setWhiteCheckmate() {
    // TODO: look for adjacent square for the king to move into (not hot)
    // TODO: if one exists, set whiteCheckMate to false, return

    // get white king
    ChessPiece* king = pointerMap[KING_ID];
    int row = king->getRow();
    int col = king->getCol();
    // create array of all adjacent square locations around the king to make iterating through them easier
    struct squareCoordinates {
        int row;
        int col;
    };
    struct squareCoordinates adjSquares[8] = {{row, col+1}, {row+1, col+1}, {row+1, col}, {row+1, col-1}, {row, col-1}, {row-1, col-1}, {row-1, col}, {row-1, col+1}};

    // for each adjacent square
    bool hot;
    for(struct squareCoordinates adjSquare : adjSquares) {
        hot = false;
        // if inside the board
        if( (row >= 0 && row < 8) && (col >=0 && col < 8) ) {
            // look through all black pieces for piece making the adjacent piece hot
            for(int i=BLACK_ID_OFFSET; i<32; i++) {
                if(hotSquares[adjSquares->row][adjSquares->col][i]) {
                    hot = true;
                    break;
                }
            }
        }

        // check if adjacent piece is hot
        if(!hot) {
            // if not, set boolean to false
            whiteCheckMate = false;
            // if king can move, no stalemate exists
            stalemate = false;
            return;
        }
    }

    // TODO: if king square is hot from only one piece, must capture or block that piece, since king cannot move adjacently
        // TODO: iterate through pieces making the checking piece hot,
        //   and then pieces making any squares in the path between the king and the attacking piece hot
        //   (only if the attacking piece is queen, rook, or bishop since they are the only pieces that can be blocked)
            // TODO: for each, make a pseudo movement and reevaluate pieces making that piece hot
            // TODO: check see if the king will enter check from another piece after movement
            // TODO: if king enters check from another piece after movement, reset and reevaluate, skip that iteration
            // TODO: else, set whiteCheckMate to false, return
        // TODO: if iterated through all options, set whiteCheckMate to true, return

    // TODO: if more than one piece is making king square hot, set whiteCheckMate to true

    // TODO: if checkmate, then stalemate if false

}

bool ChessBoard::getWhiteCheckmate() {
    return whiteCheckMate;
}

void ChessBoard::setBlackCheck(bool checkCheckmate) {
    ChessPiece* king = pointerMap[KING_ID + BLACK_ID_OFFSET];
    int row = king->getRow();
    int col = king->getCol();

    blackCheck = false;
    // look through all white pieces for piece making the kings piece hot
    for(int i=0; i<BLACK_ID_OFFSET; i++) {
        if(hotSquares[row][col][i]) {
            blackCheck = true;
            break;
        }
    }

    // checkmate only occurs when check occurs
    if(blackCheck && checkCheckmate) {
        setBlackCheckmate();
    }
}

bool ChessBoard::getBlackCheck() {
    return blackCheck;
}

void ChessBoard::setBlackCheckmate() {
    // TODO
}

bool ChessBoard::getBlackCheckmate() {
    return blackCheckMate;
}

void ChessBoard::setWhiteStalemate() {
    // TODO: must check that another piece can make a move (that does not cause king to enter check)
        // TODO: iterate through pieces that are still on the board (getIsCaptured() == false)
        //   start with pawns, then knight, queen, bishop, rook.
        //   For queen, rook, and bishop, only check for adjacent movements, since all other ones are just extra steps
            // TODO: iterate through available movements based on piece type
            // TODO: for each, ensure piece is in the board and not on top of an allied piece
                // TODO: make pseudo movement, reevalute opponent pieces making the moved square hot,
                // TODO: for each, if king become hot, reset pseudo movement and reevaluation, skip iteration
                    // TODO: if king does not become hot, move is valid; set stalemate to false, return
        // TODO: if iterated through all movements from all pieces on the board, no valid moves exist
        //   set stalemate to true, return
}

void ChessBoard::setBlackStalemate() {
    // TODO
}

bool ChessBoard::getStalemate() {
    return stalemate;
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
    // TODO: consider moving these to the respective piece objects
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
                    } else if(reevaluating) {
                        // ensure that all squares in the direction of the path after being blocked are set to false
                        // only needs to happen when reevaluating is true because this is only used when a piece has moved and
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
                    } else if(reevaluating) {
                        // ensure that all squares in the direction of the path after being blocked are set to false
                        // only needs to happen when reevaluating is true because this is only used when a piece has moved and
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
                    } else if(reevaluating) {
                        // ensure that all squares in the direction of the path after being blocked are set to false
                        // only needs to happen when reevaluating is true because this is only used when a piece has moved and
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
    // TODO : maybe make this a DEFINE
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

void ChessBoard::destroyBoard() {
    // delete all pieces in board
    for(auto & i : board) {
        for(auto & j : i) {
            if(j != nullptr) {
                j->deletePiece();
                delete j;
                j = nullptr;
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

