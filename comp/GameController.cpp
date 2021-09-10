//
// Created by alecs on 5/29/2021.
//

#include <iostream>
#include <string>
#include "GameController.h"

GameController::GameController() {
    whoseTurn = WHITE;

    while(!board.getCheckmate(WHITE) && !board.getCheckmate(BLACK) && !board.getStalemate()) {
        board.printBoard();

        const char* whoseTurnString = (whoseTurn == WHITE) ? "White" : "Black";
        printf("%s's move:\n  To make a move, enter coordinate of piece to move and its new location.\n"
               "  Sample input:  A2 A3  or  g8 h6\n", whoseTurnString);
        std::string input;

        int row, col, newRow, newCol;

        // get the integer coordinates from the correct player
        bool valid;
        do {
            printf(">>");
            // get input
            std::getline(std::cin, input);

            // TODO: resign

            std::string compoundLocation; // contains both the current location and the new location
            int validChars = 0; // counts the number of non-space characters were read
            valid = true;
            // parse input
            for(int i=0; i<input.length(); i++ ) {
                if(input[i] != ' ') {
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
                row = (compoundLocation[1] - 48) - 1;
                col = (compoundLocation[0] >= 97) ? compoundLocation[0] - 97 : compoundLocation[0] - 65;
                newRow = (compoundLocation[3] - 48) - 1;
                newCol = (compoundLocation[2] >= 97) ? compoundLocation[2] - 97 : compoundLocation[2] - 65;

                // check for validity
                if(board.getPiece(row, col) == nullptr) {
                    printf("  Invalid move. No piece exists at the given coordinates.\n");
                    valid = false;
                } else {
                    valid = board.getPiece(row, col)->getTeam() == whoseTurn;

                    if (!valid) {
                        printf("  It's %s's turn. Only a %s piece can move.\n", whoseTurnString, whoseTurnString);
                    }
                }

                // make move
                if(valid) {
                    valid = board.movePiece(row, col, newRow, newCol);
                }
            }
        } while(!valid);

        if( (board.getCheck(WHITE) || board.getCheck(BLACK) ) && ( !board.getCheckmate(WHITE) && !board.getCheckmate(BLACK) ) ) {
            printf("Check!\n");
        }

        whoseTurn = (whoseTurn == WHITE) ? BLACK : WHITE;
    }

    if(board.getCheckmate(WHITE)) {
        printf("Checkmate! Black wins!\n");
    } else if(board.getCheckmate(BLACK)) {
        printf("Checkmate! White wins!\n");
    } else {
        printf("Stalemate! Game over.\n");
    }

    board.destroyBoard();
}
