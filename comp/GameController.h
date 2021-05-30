//
// Created by alecs on 5/29/2021.
//

#ifndef CHESS_GAMECONTROLLER_H
#define CHESS_GAMECONTROLLER_H

#include "ChessBoard.h"
#include "ChessPiece.h"

class GameController {
protected:
    ChessBoard board;
    Color whoseTurn;
public:
    GameController();
};


#endif //CHESS_GAMECONTROLLER_H
