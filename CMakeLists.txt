cmake_minimum_required(VERSION 3.15)
project(ChessAI)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChessAI main.cpp comp/ChessBoard.cpp comp/ChessBoard.h comp/ChessPiece/ChessPiece.cpp comp/ChessPiece/ChessPiece.h comp/GameController.cpp comp/GameController.h comp/ChessPiece/King.cpp comp/ChessPiece/King.h comp/ChessPiece/Queen.cpp comp/ChessPiece/Queen.h comp/ChessPiece/Bishop.cpp comp/ChessPiece/Bishop.h comp/ChessPiece/Knight.cpp comp/ChessPiece/Knight.h comp/ChessPiece/Rook.cpp comp/ChessPiece/Rook.h comp/ChessPiece/Pawn.cpp comp/ChessPiece/Pawn.h comp/ChessPiece/DataTypes.h comp/ChessPiece/ColorsType.h)