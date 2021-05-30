cmake_minimum_required(VERSION 3.15)
project(ChessAI)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChessAI main.cpp comp/ChessBoard.cpp comp/ChessBoard.h comp/ChessPiece.cpp comp/ChessPiece.h comp/GameController.cpp comp/GameController.h)