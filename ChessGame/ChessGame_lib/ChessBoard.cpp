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

    int rankIterator[4] = {0, 1, 6, 7};
    for(int rank : rankIterator) {
        for(int file=0; file<8; file++) {
            // set hot squares
            setAllHotSquares(rank, file, true, false);

            // set values in pointer map
            ChessPiece* piece = board[rank][file];
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
                for(; j < bound; j++) {
                    if(capturedWhitePieces[j] != nullptr) {
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
                for(; j < bound; j++) {
                    if(capturedBlackPieces[j] != nullptr) {
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
                for(; j < bound; j++) {
                    if(capturedWhitePieces[j] != nullptr) {
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
                for(; j < bound; j++) {
                    if(capturedBlackPieces[j] != nullptr) {
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

bool ChessBoard::movePiece(int rank, int file, int newRank, int newFile) {
    // check if input is in bounds of board
    if( (newRank > 7 || newRank < 0) || (newFile > 7 || newFile < 0) ) {
        printf("  Invalid move, proposed move is not inside the board.\n");
        return false;
    }

    ChessPiece* piece = board[rank][file]; // get the piece to be moved
    // check if moved piece is a valid piece
    if(piece == nullptr) {
        printf("  Invalid move, no piece at target square %c%d.\n", file+65, rank+1);
        return false;
    }

    Color team = piece->getTeam();

    ChessPiece* proposedMove = board[newRank][newFile]; // get the piece at the spot of the proposed move, if one exists
    // check if piece at proposed move exists
    if(proposedMove != nullptr) {
        // make sure the proposed move is not an allied piece of the moved piece
        if(team == proposedMove->getTeam()) {
            if( (rank == newRank) && (file == newFile) ) {
                printf("  Invalid move, no movement made.\n");
            } else {
                printf("  Invalid move, proposed move is on top of an allied piece.\n");
            }
            return false;
        }
    }

    // TODO: if player is in check, move must remove check

    // TODO: check for valid movement
    // Also determines if move is a castle
    bool validMove = piece->validateMove(newRank, newFile, this);
    if(!validMove) {
        return false;
    }

    // Get castle information
    bool kingside;
    int rookFile;
    int newRookFile;
    ChessPiece* rook;
    if(castling) {
        kingside = (newFile - file == 2);
        rookFile = (kingside) ? 7 : 0;
        newRookFile = (kingside) ? 5 : 3;
        rook = board[rank][rookFile];

        // Determine if castle is valid
        validMove = rook->validateMove(rank, newRookFile, this);
        if(!validMove) {
            return false;
        }
    }

    // TODO: remove hot squares
    // if capturing piece
    if(proposedMove != nullptr) {
        // remove hot squares from the piece that was captured
        setAllHotSquares(newRank, newFile, false, false);
    }

    // unset old hot squares
    setAllHotSquares(rank, file, false, false);
    if(castling) {
        // unset old hot squares for rook
        setAllHotSquares(rank, rookFile, false, false);
    }

    // TODO: make pseudo movement
    board[newRank][newFile] = piece;
    board[rank][file] = nullptr;
    // TODO: make pseudo castle movement
    if(castling) {
        board[rank][newRookFile] = rook;
        board[rank][rookFile] = nullptr;
    }

    // TODO: reevaluate opponent hot squares
    int i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
    int bound = (team == WHITE) ? 32 : BLACK_ID_OFFSET;
    for(; i<bound; i++) {
        // old location and new location of moved piece
        if(hotSquares[rank][file][i] || hotSquares[newRank][newFile][i]) {
            // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
            ChessPiece* pieceToEvaluate = pointerMap[i];
            PieceType type = pieceToEvaluate->getType();
            if(type == QUEEN || type == BISHOP || type == ROOK) {
                // reevaluate the hot squares for the pieces that were making the old and new location hot
                setAllHotSquares(pieceToEvaluate->getRank(), pieceToEvaluate->getFile(), true, true);
                // only true when not castling, since in a castle the king and rook are not blocking any pieces from seeing the king
            }
        }
    }

    // TODO: check to see if, after movement, king is not in check
    setCheck(team, false);

    if( (whiteCheck && team == WHITE) || (blackCheck && team == BLACK) ) {
        // king is in check following movement
        printf("  Invalid move, King is in check after move.\n");

        // TODO: otherwise, reset pieces (including proposedMove), hot squares, resetValidation, and return false


        // set back the moved pieces into their original locations
        board[rank][file] = piece;
        board[newRank][newFile] = proposedMove;
        if(castling) {
            board[rank][newRookFile] = nullptr;
            board[rank][rookFile] = rook;
        }

        // set hot squares back
        if(proposedMove != nullptr) {
            setAllHotSquares(newRank, newFile, true, false); // captured piece
        }
        setAllHotSquares(rank, file, true, false); // moved piece
        if(castling) {
            setAllHotSquares(rank, rookFile, true, false);
        }

        // TODO: reevaluate affected pieces
        // reevaluate affected opponent pieces
        i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
        for(; i<bound; i++) {
            // old location and new location of moved piece
            if(hotSquares[rank][file][i] || hotSquares[newRank][newFile][i]) {
                // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
                ChessPiece* pieceToEvaluate = pointerMap[i];
                PieceType type = pieceToEvaluate->getType();
                if(type == QUEEN || type == BISHOP || type == ROOK) {
                    // reevaluate the hot squares for the pieces that were making the old and new location hot
                    setAllHotSquares(pieceToEvaluate->getRank(), pieceToEvaluate->getFile(), true, true);
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

    // move is valid
    // make move, update check, set hot squares

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
        Color thisTeam = piece->getTeam();
        if((newRank == 7 && thisTeam == WHITE) || (newRank == 0 && thisTeam == BLACK)) {
            promotion(newRank, newFile);
        }
    }

    // TODO: set hot squares back
    // set new hot squares
    setAllHotSquares(newRank, newFile, true, false);
    if(castling) {
        setAllHotSquares(rank, newRookFile, true, false);
    }

    // TODO: I modified this range
    // only need to reevaluate allied pieces, since this was already done for opponent pieces
    i = (team == WHITE) ? 0 : BLACK_ID_OFFSET;
    for(; i<bound; i++) {
        // old location and new location of moved piece
        if(hotSquares[rank][file][i] || hotSquares[newRank][newFile][i]) {
            // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
            ChessPiece* pieceToEvaluate = pointerMap[i];
            PieceType type = pieceToEvaluate->getType();
            if(type == QUEEN || type == BISHOP || type == ROOK) {
                // reevaluate the hot squares for the pieces that were making the old and new location hot
                setAllHotSquares(pieceToEvaluate->getRank(), pieceToEvaluate->getFile(), true, true);
                // only true when not castling, since in a castle the king and rook are not blocking any pieces from seeing the king
            }
        }
    }

    // TODO: I don't think both checks need to be set again
    // set the opponents check status, since the moving player's check status has already been set
    stalemate = true; // used to determine if stalemate needs to be checked
    if(team == WHITE) {
        setCheck(BLACK, true);
    } else {
        setCheck(WHITE, true);
    }

    if(stalemate) { // stalemate needs to be checked if checking for checkmate did not return false for stalemate
        setStalemate(team);
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
    int rank = (team == WHITE) ? 0 : 7;
    int rookFile = (kingside) ? 7 : 0;

    // check if Rook piece is valid to castle
    ChessPiece* maybeRook = board[rank][rookFile];
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

    int rookNewFile = (kingside) ? 5 : 3;

    // TODO: king can't move through check : validate this
    // look through all black pieces for piece making the kings piece hot
    int i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
    int bound = (team == WHITE) ? 32 : BLACK_ID_OFFSET;
    for(; i<bound; i++) {
        if(hotSquares[rank][rookNewFile][i]) {
            printf("  Invalid move, King cannot castle through check.\n");
            return false; // check mate only occurs if check occurs
        }
    }

    // execute rook movement
    // TODO: this might cause a bug
    //if(!movePiece(rank, rookFile, rank, rookNewFile)) {
    //    return false;
    //}

    // set castling boolean if valid castle
    castling = true;
    return true;
}

ChessPiece* ChessBoard::getPiece(int rank, int file) {
    return board[rank][file];
}

void ChessBoard::promotion(int rank, int file) {
    printBoard();

    ChessPiece* piece = board[rank][file]; // get the piece to be promoted

    // TODO: maybe remove these checks
    // check if promoted piece is a valid piece
    if(piece == nullptr) {
        fprintf(stderr, "Error: promoted piece is null at %c%d.\n", file + 65, rank+1);
        exit(99);
    }
    // check if promoted piece is pawn
    if(piece->getType() != PAWN) {
        fprintf(stderr, "Error: promoted piece is not a pawn %c%d.\n", file + 65, rank+1);
        exit(99);
    }
    // check if pawn is in correct location
    Color team = piece->getTeam();
    if( !((team == WHITE && rank == 7) || (team == BLACK && rank == 0)) ) {
        fprintf(stderr, "Error: promoted piece is not at the other side of the board at %c%d.\n", file + 65, rank+1);
        exit(99);
    }

    // free memory of promoted pawn
    delete board[rank][file];
    board[rank][file] = nullptr;

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
                board[rank][file] = new ChessPiece(QUEEN, team, rank, file, id);
                valid = true;
                break;
            case 'B':
            case 'b':
                board[rank][file] = new ChessPiece(BISHOP, team, rank, file, id);
                valid = true;
                break;
            case 'N':
            case 'n':
                board[rank][file] = new ChessPiece(KNIGHT, team, rank, file, id);
                valid = true;
                break;
            case 'R':
            case 'r':
                board[rank][file] = new ChessPiece(ROOK, team, rank, file, id);
                valid = true;
                break;
            default:
                printf("  Invalid input.\n>>");
        }
    } while(!valid);
}

void ChessBoard::setCheck(Color team, bool checkCheckmate) {
    ChessPiece* king = pointerMap[KING_ID + ((team == WHITE) ? 0 : BLACK_ID_OFFSET)];
    int rank = king->getRank();
    int file = king->getFile();

    if(team == WHITE) {
        whiteCheck = false;
    } else {
        blackCheck = false;
    }
    // look through all black pieces for piece making the kings piece hot
    int i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
    int bound = (team == WHITE) ? 32 : BLACK_ID_OFFSET;
    for(; i<bound; i++) {
        if(hotSquares[rank][file][i]) {
            if(team == WHITE) {
                whiteCheck = true;
            } else {
                blackCheck = true;
            }
            break;
        }
    }

    // checkmate only occurs when check occurs
    if( ((whiteCheck && team == WHITE) || (blackCheck && team == BLACK)) && checkCheckmate ) {
        setCheckmate(team);
    }
}

bool ChessBoard::getCheck(Color team) {
    return (team == WHITE) ? whiteCheck : blackCheck;
}

// TODO: look for adjacent square for the team's king to move into (not hot)
// TODO: if one exists, set team's checkmate boolean to false, return
// TODO: count how many pieces are making king hot
// TODO: if more than one piece is making king square hot, set team's checkmate boolean to true
// TODO: if king square is hot from only one piece, must capture or block that piece, since king cannot move adjacently
// TODO: iterate through pieces making the attacking piece hot,
    // TODO: then check pieces making any squares in the path between the king and the attacking piece hot
    //   (only if the attacking piece is queen, rook, or bishop since they are the only pieces that can be blocked)
// TODO: if iterated through all options, set team's checkmate boolean to true, return
// TODO: if checkmate, then stalemate is false
void ChessBoard::setCheckmate(Color team) {
    // look for adjacent square for the team's king to move into (not hot)
    // if one exists, set team's checkmate boolean to false, return

    // get king
    ChessPiece* king = pointerMap[KING_ID + ((team == WHITE) ? 0 : BLACK_ID_OFFSET)];
    int rank = king->getRank();
    int file = king->getFile();
    // create array of all adjacent square locations around the king to make iterating through them easier
    struct squareCoordinates {
        int rank;
        int file;
    };
    struct squareCoordinates adjSquares[8] = {{rank, file+1},
                                              {rank+1, file+1},
                                              {rank+1, file},
                                              {rank+1, file-1},
                                              {rank, file-1},
                                              {rank-1, file-1},
                                              {rank-1, file},
                                              {rank-1, file+1}};

    // for each adjacent square
    bool hot;
    int opponentBound = (team == WHITE) ? 32 : BLACK_ID_OFFSET;
    for(struct squareCoordinates adjSquare : adjSquares) {
        hot = false;
        // if inside the board
        if( (adjSquare.rank >= 0 && adjSquare.rank < 8) && (adjSquare.file >=0 && adjSquare.file < 8) ) {
            // if not occupied by an ally
            if(board[adjSquare.rank][adjSquare.file] != nullptr) {
                if(board[adjSquare.rank][adjSquare.file]->getTeam() == team) {
                    hot = true;
                }
            }

            if(!hot) {
                // look through all opponent pieces for piece making the adjacent piece hot
                int i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
                for(; i<opponentBound; i++) {
                    // check if adjacent piece is hot from specific opponent piece
                    if(hotSquares[adjSquare.rank][adjSquare.file][i]) {
                        hot = true;
                        break;
                    }
                }
            }
        }

        // if the square is not hot
        if(!hot) {
            // set boolean to false
            if(team == WHITE) {
                whiteCheckMate = false;
            } else {
                blackCheckMate = false;
            }
            // if king can move, no stalemate exists
            stalemate = false;
            return;
        }
    }


    // count how many pieces are making king hot
    int numHot = 0;
    ChessPiece *attacker = nullptr; // only used if numHot = 1
    int attackerIndex = -1;
    // look through all opponent pieces for piece making the kings piece hot
    {
        int i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
        for(; i<opponentBound; i++) {
            if(hotSquares[rank][file][i]) {
                numHot++;
                attacker = pointerMap[i];
                attackerIndex = i;
            }
        }
    }

    if(numHot > 1) {
        // if more than one piece is making king square hot, set team's checkmate boolean to true
        if(team == WHITE) {
            whiteCheckMate = true;
        } else {
            blackCheckMate = true;
        }
    } else if(attacker != nullptr) {
        // if king square is hot from only one piece, must capture or block that piece, since king cannot move adjacently
        // iterate through pieces making the attacking piece hot,

        int attackerRank = attacker->getRank();
        int attackerFile = attacker->getFile();

        if(foundValidMove(team, attackerRank, attackerFile, attacker, attackerIndex)) {
            stalemate = false;
            return;
        }

        // then check pieces making any squares in the path between the king and the attacking piece hot
        //   (only if the attacking piece is queen, rook, or bishop since they are the only pieces that can be blocked)
        PieceType type = attacker->getType();
        if(type == QUEEN || type == BISHOP || type == ROOK) {
            int rankDisplacement = rank - attackerRank;
            int fileDisplacement = file - attackerFile;

            // check if jumping over another piece
            if(rankDisplacement == 0) { // attacking horizontally
                int i = (fileDisplacement > 0) ? attackerFile+1 : attackerFile-1; // starting position for the loop, left or right 1
                int inc = (fileDisplacement > 0) ? 1 : -1; // increment left or right

                for(; i!=file; i+=inc) { // iterate through available spaces
                    if(foundValidMove(team, rank, i)) {
                        stalemate = false;
                        return;
                    }
                }
            } else if(fileDisplacement == 0) { // attacking vertically
                int i = (rankDisplacement > 0) ? attackerRank+1 : attackerRank-1; // starting position for the loop, up or down 1
                int inc = (rankDisplacement > 0) ? 1 : -1; // increment up or down

                for(; i!=rank; i+=inc) { // iterate through available spaces
                    if(foundValidMove(team, i, file)) {
                        stalemate = false;
                        return;
                    }
                }
            } else { // attacking diagonally
                // incrementer for rank and file
                int rankInc = (rankDisplacement > 0) ? 1 : -1; // moving up or down
                int fileInc = (fileDisplacement > 0) ? 1 : -1; // moving right or left

                int j = attackerFile+fileInc; // set initial rank and file
                for(int i = attackerRank+rankInc; i!=rank; i+=rankInc) { // iterate through available spaces
                    if(foundValidMove(team, i, j)) {
                        stalemate = false;
                        return;
                    }
                    j+=fileInc; // increment rank and file
                }
            }
        }

        // if iterated through all options, set team's checkmate boolean to true, return
        if(team == WHITE) {
            whiteCheckMate = true;
        } else {
            blackCheckMate = true;
        }

        // if checkmated, then stalemate is false
        stalemate = false;
    } else {
        fprintf(stderr, "Error: attacker is nullptr [setCheckmate].\n");
        exit(99);
    }
}

// TODO; determine if an allied piece can be moved to the specified rank/file
// TODO: iterate through allied pieces making the specified square hot
    // TODO: for each, make a pseudo movement and reevaluate pieces making that piece hot
    // TODO: check to see if the king will enter check from another piece (that is not the attacking piece) after movement
    // TODO: if king enters check from another piece after movement, reset and reevaluate, skip that iteration
    // TODO: else, return true
// attacker and attackerIndex will be nullptr and -1 if the requested move will not capture an opponent piece
bool ChessBoard::foundValidMove(Color team, int rank, int file, ChessPiece* attacker, int attackerIndex) {
    int i = (team == WHITE) ? 0 : BLACK_ID_OFFSET;
    int alliedBound = (team == WHITE) ? BLACK_ID_OFFSET : 32;
    for(; i<alliedBound; i++) {
        if(hotSquares[rank][file][i]) {

            // make pseudo movement
            ChessPiece* attackingAttacker = pointerMap[i];
            int attackingAttackerRank = attackingAttacker->getRank();
            int attackingAttackerFile = attackingAttacker->getFile();

            board[rank][file] = attackingAttacker;
            board[attackingAttackerRank][attackingAttackerFile] = nullptr;

            // remove hot squares from the piece that was captured
            if(attacker != nullptr) {
                setAllHotSquares(rank, file, false, false);
            }

            // reevaluate opponent pieces attacking allied piece attacking attacker (that are not the attacking piece)
            int opponentBound = (team == WHITE) ? 32 : BLACK_ID_OFFSET;
            {
                int j = (team == WHITE) ? BLACK_ID_OFFSET : 0;
                for(; j < opponentBound; j++) {
                    // old location of moved piece
                    if(hotSquares[attackingAttackerRank][attackingAttackerFile][j] && attackerIndex != j) {
                        // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
                        ChessPiece *pieceToEvaluate = pointerMap[j];
                        PieceType type = pieceToEvaluate->getType();
                        if(type == QUEEN || type == BISHOP || type == ROOK) {
                            // reevaluate the hot squares for the pieces that were making the old location hot
                            // reevaluating is false because movement cannot block a piece that was not already blocked
                            setAllHotSquares(pieceToEvaluate->getRank(), pieceToEvaluate->getFile(), true, false);
                        }
                    }
                }
            }

            // set new check value
            setCheck(team, false);

            // set back the moved pieces into their original locations
            board[attackingAttackerRank][attackingAttackerFile] = attackingAttacker;
            board[rank][file] = attacker;

            // set hot squares back
            if(attacker != nullptr) {
                setAllHotSquares(rank, file, true, false); // captured piece
            }

            // re-reevaluate opponent pieces attacking allied piece attacking attacker (that are not the attacking piece)
            {
                int j = (team == WHITE) ? BLACK_ID_OFFSET : 0;
                for(; j < opponentBound; j++) {
                    // old location of moved piece
                    if(hotSquares[attackingAttackerRank][attackingAttackerFile][j] && attackerIndex != j) {
                        // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
                        ChessPiece *pieceToEvaluate = pointerMap[j];
                        PieceType type = pieceToEvaluate->getType();
                        if(type == QUEEN || type == BISHOP || type == ROOK) {
                            // reevaluate the hot squares for the pieces that were making the old location hot
                            // reevaluating is false because movement cannot block a piece that was not already blocked
                            setAllHotSquares(pieceToEvaluate->getRank(), pieceToEvaluate->getFile(), true, false);
                        }
                    }
                }
            }

            // check if movement took king out of check
            if(!whiteCheck && team == WHITE) {
                // valid white movement
                whiteCheckMate = false;
                setCheck(team, false); // reset check value
                return true;
            } else if (!blackCheck && team == BLACK) {
                // valid black movement
                blackCheckMate = false;
                setCheck(team, false); // reset check value
                return true;
            }
        }
    }

    setCheck(team, false); // reset check value
    return false; // no valid move found
}

bool ChessBoard::getCheckmate(Color team) {
    return (team == WHITE) ? whiteCheckMate : blackCheckMate;
}

// TODO: must check that another piece can make a move (that does not cause king to enter check)
    // TODO: iterate through pieces that are still on the board (getIsCaptured() == false)
    //   start with pawns, then knight, queen, bishop, rook.
        // TODO: iterate through available movements based on piece type
        //   For queen, rook, and bishop, only check for adjacent movements, since all other ones are just extra steps
            // TODO: for each, ensure move is in the board and not on top of an allied piece
            // TODO: make pseudo movement, reevaluate opponent pieces that make the moved square hot.
            // TODO: If king becomes hot, reset pseudo movement and reevaluation, skip iteration
                // TODO: if king does not become hot, move is valid; set stalemate to false, return
    // TODO: if iterated through all movements from all pieces on the board, no valid moves exist
    //   set stalemate to true, return
void ChessBoard::setStalemate(Color team) {
    // get the order of pieces that should be checked for maximum efficiency
    int piece_order[16];
    for(int i=0; i<8; i++) {
        piece_order[i] = PAWS_START_ID + i;
    }
    piece_order[8] = KNIGHT_QS_ID;
    piece_order[9] = KNIGHT_KS_ID;
    piece_order[10] = QUEEN_ID;
    piece_order[11] = BISHOP_QS_ID;
    piece_order[12] = BISHOP_KS_ID;
    piece_order[13] = ROOK_QS_ID;
    piece_order[14] = ROOK_KS_ID;
    piece_order[15] = KING_ID;

    if(team == BLACK) {
        for(int i=0; i<16; i++) {
            piece_order[i] += BLACK_ID_OFFSET;
        }
    }

    // iterate through pieces that are still on the board
    for(int id : piece_order) {
        ChessPiece* piece = pointerMap[id];
        if(!piece->getIsCaptured()) {
            int rank = piece->getRank();
            int file = piece->getFile();
            PieceType type = piece->getType();

            // set squares hot based on piece type
            // TODO: consider moving these to the respective piece objects
            switch(type) {
                case KING:
                case QUEEN:
                case BISHOP:
                    if(checkStalemateValidMove(rank, file, rank+1, file+1) ||
                       checkStalemateValidMove(rank, file, rank+1, file-1) ||
                       checkStalemateValidMove(rank, file, rank-1, file+1) ||
                       checkStalemateValidMove(rank, file, rank-1, file-1)) {
                        stalemate = false;
                        return;
                    }

                    // if the piece is a Queen, set hot squares in rank and file
                    if(type == BISHOP) {
                        break;
                    }
                case ROOK:
                    if(checkStalemateValidMove(rank, file, rank+1, file) ||
                       checkStalemateValidMove(rank, file, rank-1, file) ||
                       checkStalemateValidMove(rank, file, rank, file+1) ||
                       checkStalemateValidMove(rank, file, rank, file-1)) {
                        stalemate = false;
                        return;
                    }

                    // do not set stalemate if king is in check(mate)
                    if(type == KING) {
                        int i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
                        int bound = (team == WHITE) ? 32 : BLACK_ID_OFFSET;
                        for(; i<bound; i++) {
                            if(hotSquares[rank][file][i]) {
                                // this should theoretically never be reached because
                                // this condition is checked when checkmate is checked
                                stalemate = false;
                                return;
                            }
                        }
                    }

                    break;
                case KNIGHT:
                    if(checkStalemateValidMove(rank, file, rank+1, file+2) ||
                       checkStalemateValidMove(rank, file, rank+2, file+1) ||
                       checkStalemateValidMove(rank, file, rank+2, file-1) ||
                       checkStalemateValidMove(rank, file, rank+1, file-2) ||
                       checkStalemateValidMove(rank, file, rank-1, file-2) ||
                       checkStalemateValidMove(rank, file, rank-2, file-1) ||
                       checkStalemateValidMove(rank, file, rank-2, file+1) ||
                       checkStalemateValidMove(rank, file, rank-1, file+2)) {
                        stalemate = false;
                        return;
                    }

                    break;
                case PAWN:
                    if(team == WHITE) {
                        if(checkStalemateValidMove(rank, file, rank+1, file+1) ||
                           checkStalemateValidMove(rank, file, rank+1, file-1)) {
                            stalemate = false;
                            return;
                        }
                    } else {
                        if(checkStalemateValidMove(rank, file, rank-1, file+1) ||
                           checkStalemateValidMove(rank, file, rank-1, file-1)) {
                            stalemate = false;
                            return;
                        }
                    }

                    break;
                default:
                    fprintf(stderr, "Error: has no type [setStalemate].\n");
                    exit(99);
            }
        }
    }

    stalemate = true;
}

bool ChessBoard::checkStalemateValidMove(int rank, int file, int newRank, int newFile) {
    // ensure move is inside the board
    if(newRank < 0 || newRank >= 8 || newFile < 0 || newFile >= 8) {
        return false;
    }

    ChessPiece* piece = board[rank][file];
    Color team = piece->getTeam();
    ChessPiece* attackedPiece = board[newRank][newFile];

    // ensure piece is not on top of an allied piece
    if(attackedPiece != nullptr) {
        if(attackedPiece->getTeam() == team) {
            return false;
        }
    }

    // make pseudo movement
    board[rank][file] = nullptr;
    board[newRank][newFile] = piece;

    // reevaluate opponent pieces that make the moved square hot
    int i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
    int bound = (team == WHITE) ? 32 : BLACK_ID_OFFSET;
    for(; i<bound; i++) {
        // old location of moved piece
        if(hotSquares[rank][file][i]) { // TODO: hotSquares[newRank][newFile][i] verify this does not need to be checked with unit testing
            // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
            ChessPiece* pieceToEvaluate = pointerMap[i];
            PieceType type = pieceToEvaluate->getType();
            if(type == QUEEN || type == BISHOP || type == ROOK) {
                // reevaluate the hot squares for the pieces that were making and new location hot
                setAllHotSquares(pieceToEvaluate->getRank(), pieceToEvaluate->getFile(), true, true);
                // only true when not castling, since in a castle the king and rook are not blocking any pieces from seeing the king
            }
        }
    }

    // if king does not become hot, move is valid
    ChessPiece* king = pointerMap[KING_ID + ((team == WHITE) ? 0 : BLACK_ID_OFFSET)];
    int kingRank = king->getRank();
    int kingFile = king->getFile();
    i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
    bool hot = false;
    for(; i<bound; i++) {
        if(hotSquares[kingRank][kingFile][i]) {
            hot = true;
            break;
        }
    }

    // reset pseudo movement
    board[rank][file] = piece;
    board[newRank][newFile] = attackedPiece;

    // reset reevaluation of opponent pieces that make the moved square hot
    i = (team == WHITE) ? BLACK_ID_OFFSET : 0;
    for(; i<bound; i++) {
        // old location of moved piece
        if(hotSquares[rank][file][i]) { // TODO: hotSquares[newRank][newFile][i] verify this does not need to be checked with unit testing
            // only need to reevaluate hot squares for pieces that can be blocked by an opponent: Queen, Bishop, Rook
            ChessPiece* pieceToEvaluate = pointerMap[i];
            PieceType type = pieceToEvaluate->getType();
            if(type == QUEEN || type == BISHOP || type == ROOK) {
                // reevaluate the hot squares for the pieces that were making the old location hot
                setAllHotSquares(pieceToEvaluate->getRank(), pieceToEvaluate->getFile(), true, true);
                // only true when not castling, since in a castle the king and rook are not blocking any pieces from seeing the king
            }
        }
    }

    return !hot;
}

bool ChessBoard::getStalemate() {
    return stalemate;
}

void ChessBoard::setAllHotSquares(int rank, int file, bool value, bool reevaluating) {
    ChessPiece* piece = board[rank][file];
    if(piece == nullptr) {
        fprintf(stderr, "Error: piece to set hot is null at %c%d.\n", file + 65, rank+1);
        exit(99);
    }

    Color team = piece->getTeam();
    int id = piece->getID();

    PieceType type = piece->getType();
    // set squares hot based on piece type
    // TODO: consider moving these to the respective piece objects
    switch(type) {
        case KING:
            setSquareHot(id, rank, file+1, value);
            setSquareHot(id, rank+1, file+1, value);
            setSquareHot(id, rank+1, file, value);
            setSquareHot(id, rank+1, file-1, value);
            setSquareHot(id, rank, file-1, value);
            setSquareHot(id, rank-1, file-1, value);
            setSquareHot(id, rank-1, file, value);
            setSquareHot(id, rank-1, file+1, value);
            break;
        case QUEEN:
        case BISHOP: {
            int incrementor[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}}; // incrementor for rank and file
            int boundaries[4][2] = {{8, 8}, {8, -1}, {-1, -1}, {-1, 8}}; // boundaries for the board
            int rankInc, fileInc, rankBound, fileBound;
            bool pathBlocked; // used to determine when a piece is blocking the path of the checked piece

            // loop through all four directions that must be checked
            for(int i=0; i<4; i++) {
                rankInc = incrementor[i][0];
                fileInc = incrementor[i][1];
                rankBound = boundaries[i][0];
                fileBound = boundaries[i][1];
                pathBlocked = false;

                for(int r = rank+rankInc, c = file+fileInc; r != rankBound && c != fileBound; r += rankInc, c += fileInc) {
                    if(!pathBlocked) {
                        hotSquares[r][c][id] = value;
                        if(board[r][c] != nullptr) { // if statement succeeds setSquareHot to set hot the square with a piece on it
                            pathBlocked = true;
                        }
                    } else if(reevaluating) {
                        // ensure that all squares in the direction of the path after being blocked are set to false
                        // only needs to happen when reevaluating is true because this is only used when a piece has moved and
                        // all squares that made the old piece hot are being re-evaluated.
                        // TLDR something blocked a path and path squares need to be set to false
                        if(!hotSquares[r][c][id]) {
                            break; // TODO: could be broken
                        }
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
            for(int i = 0; i < 2; i++) {
                inc = i==0 ? 1 : -1;
                bound = i==0 ? 8 : -1;

                pathBlocked = false;
                for(int r = rank + inc; r != bound; r += inc) {
                    if(!pathBlocked) {
                        hotSquares[r][file][id] = value;
                        if(board[r][file] != nullptr) { // if statement succeeds setSquareHot to set hot the square with a piece on it
                            pathBlocked = true;
                        }
                    } else if(reevaluating) {
                        // ensure that all squares in the direction of the path after being blocked are set to false
                        // only needs to happen when reevaluating is true because this is only used when a piece has moved and
                        // all squares that made the old piece hot are being re-evaluated
                        if(!hotSquares[r][file][id]) {
                            break;
                        }
                        hotSquares[r][file][id] = false;
                    }
                }

                pathBlocked = false; // reset to false for new direction
                for(int c = file + inc; c != bound; c += inc) {
                    if(!pathBlocked) {
                        hotSquares[rank][c][id] = value;
                        if(board[rank][c] != nullptr) { // if statement succeeds setSquareHot to set hot the square with a piece on it
                            pathBlocked = true;
                        }
                    } else if(reevaluating) {
                        // ensure that all squares in the direction of the path after being blocked are set to false
                        // only needs to happen when reevaluating is true because this is only used when a piece has moved and
                        // all squares that made the old piece hot are being re-evaluated
                        if(!hotSquares[rank][c][id]) {
                            break;
                        }
                        hotSquares[rank][c][id] = false;
                    }
                }
            }
            break;
        case KNIGHT:
            setSquareHot(id, rank+1, file+2, value);
            setSquareHot(id, rank+2, file+1, value);
            setSquareHot(id, rank+2, file-1, value);
            setSquareHot(id, rank+1, file-2, value);
            setSquareHot(id, rank-1, file-2, value);
            setSquareHot(id, rank-2, file-1, value);
            setSquareHot(id, rank-2, file+1, value);
            setSquareHot(id, rank-1, file+2, value);
            break;
        case PAWN:
            if(team == WHITE) {
                setSquareHot(id, rank+1, file+1, value);
                setSquareHot(id, rank+1, file-1, value);
            } else {
                setSquareHot(id, rank-1, file+1, value);
                setSquareHot(id, rank-1, file-1, value);
            }
            break;
        default:
            fprintf(stderr, "Error: piece has no type [setHotSquares].\n");
            exit(99);
    }
}

void ChessBoard::setSquareHot(int id, int rank, int file, bool value) {
    // TODO : maybe make this a DEFINE
    if((rank >= 0 && rank < 8) && (file >= 0 && file < 8)) {
        hotSquares[rank][file][id] = value;
    }
}

void ChessBoard::printHotSquares(bool printValues) {
    printf("Printing hot squares...\n");

    if(printValues) {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                printf("Rank: %d    File: %d\n", i, j);
                printf("    White:    Black:\n");
                for(int k = 0; k < 16; k++) {
                    if(k<=9) {
                        printf(" ");
                    }
                    printf("%d: ", k);
                    if(hotSquares[i][j][k]) {
                        printf("X");
                    } else {
                        printf(" ");
                    }
                    printf("         ");
                    if(hotSquares[i][j][k+16]) {
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

