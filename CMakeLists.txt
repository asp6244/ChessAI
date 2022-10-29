cmake_minimum_required(VERSION 3.15)
project(ChessAI)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChessAI main.cpp ChessGame/ChessGame_lib/ChessBoard.cpp ChessGame/ChessGame_lib/ChessBoard.h ChessGame/ChessGame_lib/ChessPiece/ChessPiece.cpp ChessGame/ChessGame_lib/ChessPiece/ChessPiece.h ChessGame/ChessGame_lib/GameController.cpp ChessGame/ChessGame_lib/GameController.h ChessGame/ChessGame_lib/ChessPiece/King.cpp ChessGame/ChessGame_lib/ChessPiece/King.h ChessGame/ChessGame_lib/ChessPiece/Queen.cpp ChessGame/ChessGame_lib/ChessPiece/Queen.h ChessGame/ChessGame_lib/ChessPiece/Bishop.cpp ChessGame/ChessGame_lib/ChessPiece/Bishop.h ChessGame/ChessGame_lib/ChessPiece/Knight.cpp ChessGame/ChessGame_lib/ChessPiece/Knight.h ChessGame/ChessGame_lib/ChessPiece/Rook.cpp ChessGame/ChessGame_lib/ChessPiece/Rook.h ChessGame/ChessGame_lib/ChessPiece/Pawn.cpp ChessGame/ChessGame_lib/ChessPiece/Pawn.h ChessGame/ChessGame_lib/ChessPiece/ColorsType.h)