#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

class Board; // forward declaration

class Piece {
protected:
    int positionX;
    int positionY;
    string colour;
    char symbol;

public:
    Piece();
    Piece(string c, char s);
    virtual ~Piece() {}
    virtual int getPositionX() = 0;
    virtual int getPositionY() = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual string getColour() = 0;
    virtual char getSymbol() = 0;
    virtual bool isValidMove(int startX, int startY, int endX, int endY, Board& board) = 0;
};

class Board {
    Piece* grid[8][8];
public:
    Board();
    ~Board();
    void initializeBoard();
    void setBoardWhite();
    void setBoardBlack();
    void displayBoard();
    Piece* getPiece(int x, int y);
    void movePiece(int startX, int startY, int endX, int endY);
    void setPiece(int x, int y, Piece* p);
};

class Game {
private:
    Board board;
    bool isWhiteTurn;
    bool gameOver;
    string lastResult;
public:
    Game();
    void startGame();
    Board& getBoard() { return board; }
    bool   getIsWhiteTurn() { return isWhiteTurn; }
    bool   getGameOver() { return gameOver; }
    string getStatus() {
        if (gameOver)
            return lastResult.empty() ? "Game Over!" : lastResult;
        string base = isWhiteTurn ? "White's turn" : "Black's turn";
        return lastResult.empty() ? base : base + "  |  " + lastResult;
    }
    bool tryMove(int r1, int c1, int r2, int c2);
    bool isKingInCheck(bool whiteKing);
    bool hasAnyLegalMove(bool forWhite);
    bool isSquareAttacked(int row, int col, bool byWhite);
};

class King : public Piece {
public:
    King();
    King(string c);
    void setPosition(int x, int y) override;
    bool isValidMove(int startX, int startY, int endX, int endY, Board& board) override;
    int getPositionX() override;
    int getPositionY() override;
    string getColour() override;
    char getSymbol() override;
};

class Queen : public Piece {
public:
    Queen();
    Queen(string c);
    void setPosition(int x, int y) override;
    bool isValidMove(int startX, int startY, int endX, int endY, Board& board) override;
    int getPositionX() override;
    int getPositionY() override;
    string getColour() override;
    char getSymbol() override;
};

class Rook : public Piece {
public:
    Rook();
    Rook(string c);
    void setPosition(int x, int y) override;
    bool isValidMove(int startX, int startY, int endX, int endY, Board& board) override;
    int getPositionX() override;
    int getPositionY() override;
    string getColour() override;
    char getSymbol() override;
};

class Bishop : public Piece {
public:
    Bishop();
    Bishop(string c);
    void setPosition(int x, int y) override;
    bool isValidMove(int startX, int startY, int endX, int endY, Board& board) override;
    int getPositionX() override;
    int getPositionY() override;
    string getColour() override;
    char getSymbol() override;
};

class Knight : public Piece {
public:
    Knight();
    Knight(string c);
    void setPosition(int x, int y) override;
    bool isValidMove(int startX, int startY, int endX, int endY, Board& board) override;
    int getPositionX() override;
    int getPositionY() override;
    string getColour() override;
    char getSymbol() override;
};

class Pawn : public Piece {
public:
    Pawn();
    Pawn(string c);
    void setPosition(int x, int y) override;
    bool isValidMove(int startX, int startY, int endX, int endY, Board& board) override;
    int getPositionX() override;
    int getPositionY() override;
    string getColour() override;
    char getSymbol() override;
};