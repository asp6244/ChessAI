//
// Created by alecs on 5/29/2021.
//

#ifndef CHESS_GAMECONTROLLER_H
#define CHESS_GAMECONTROLLER_H

#include "ChessBoard.h"
#include "ChessPiece/ColorsType.h"

class GameController {
protected:
    ChessBoard board;
    Color whoseTurn;
    bool resigned = false;
public:
    GameController();
};


#endif //CHESS_GAMECONTROLLER_H
