//
// Created by alecs on 5/29/2021.
//

#include <iostream>
#include <string>
#include "GameController.h"

GameController::GameController() {
    whoseTurn = BLACK; // this gets flipped immediately as the game starts

    while(!board.getCheckmate(WHITE) &&
          !board.getCheckmate(BLACK) &&
          !board.getStalemate() &&
          !resigned) {
        whoseTurn = (whoseTurn == WHITE) ? BLACK : WHITE;

        board.printBoard();

        const char* whoseTurnString = (whoseTurn == WHITE) ? "White" : "Black";
        printf("%s's move:\n  To make a move, enter coordinate of piece to move and its new location.\n"
               "  Type 'resign' to resign from the game.\n"
               "  Sample input:  A2 A3  or  g8 h6\n", whoseTurnString);
        std::string input;

        int rank, file, newRank, newFile;

        // get the integer coordinates from the correct player
        bool valid;
        do {
            printf(">> ");
            // get input
            std::getline(std::cin, input);
            printf("%s\n", input.c_str());

            // check for resignation
            if(input == "resign") {
                resigned = true;
                break;
            }

            std::string compoundLocation; // contains both the current location and the new location
            int validChars = 0; // counts the number of non-space characters were read
            valid = true;
            // parse input
            for(int i=0; i<input.length(); i++ ) {
                if(input[i] != ' ' && input[i] != 0xD) {
                    if(validChars == 4) {
                        printf("  Invalid input.\n");
                        valid = false;
                        break;
                    }
                    compoundLocation += input[i];
                    validChars++;
                    if(validChars == 2 && input[i+1] != ' ') {
                        printf("  Invalid input.\n");
                        valid = false;
                        break;
                    }
                }
            }
            if(compoundLocation.length() != 4 && valid) {
                printf("  Invalid input.\n");
                valid = false;
            }

            if(valid) {
                // format input
                rank = (compoundLocation[1] - 48) - 1;
                file = (compoundLocation[0] >= 97) ? compoundLocation[0] - 97 : compoundLocation[0] - 65;
                newRank = (compoundLocation[3] - 48) - 1;
                newFile = (compoundLocation[2] >= 97) ? compoundLocation[2] - 97 : compoundLocation[2] - 65;

                // check for validity
                if(board.getPiece(rank, file) == nullptr) {
                    printf("  Invalid move. No piece exists at the given coordinates.\n");
                    valid = false;
                } else {
                    valid = board.getPiece(rank, file)->getTeam() == whoseTurn;

                    if (!valid) {
                        printf("  It's %s's turn. Only a %s piece can move.\n",
                                whoseTurnString, whoseTurnString);
                    }
                }

                // make move
                if(valid) {
                    valid = board.movePiece(rank, file, newRank, newFile);
                }
            }
        } while(!valid);

        if( (board.getCheck(WHITE) || board.getCheck(BLACK)) &&
            (!board.getCheckmate(WHITE) && !board.getCheckmate(BLACK)) ) {
            printf("Check!\n");
        }
    }

    if(board.getCheckmate(WHITE)) {
        printf("Checkmate! Black wins!\n");
    } else if(board.getCheckmate(BLACK)) {
        printf("Checkmate! White wins!\n");
    } else if(board.getStalemate()) {
        printf("Stalemate! Game over.\n");
    } else {
        // resigned
        if(whoseTurn == WHITE) {
            printf("White resigns. Black wins!\n");
        } else {
            printf("Black resigns. White wins!\n");
        }
    }

    board.destroyBoard();
}
