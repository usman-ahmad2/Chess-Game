# ♟️ OOP Chess Game

A feature-rich Chess game built using **Object-Oriented Programming (OOP)** concepts in C++. Includes both console and graphical interface using **SFML**.

## ✨ Features

- **Full Chess Rules** implemented (except castling & en passant)
- **Graphical Interface** using SFML
- **Console Mode** available
- **Check, Checkmate & Stalemate** detection
- **Legal Move Validation** (including pins)
- **Pawn Promotion** (to Queen)
- **Undo simulation** for move legality
- **Highlighting**: Selected piece, valid moves, last move
- **Restart** functionality (Press `R`)

## 🏗️ OOP Design

This project demonstrates strong OOP principles:
- **Inheritance**: `Piece` base class with derived classes (`King`, `Queen`, `Rook`, etc.)
- **Polymorphism**: Virtual functions for move validation
- **Encapsulation**: Private data members with getters/setters
- **Abstraction**: Abstract `Piece` class with pure virtual functions
- **Composition**: `Game` contains `Board`, `Board` contains `Piece*`

## 🎮 How to Play

### Controls (Graphical Mode)
- **Left Click** on your piece to select
- **Left Click** on highlighted square to move
- **R** → Restart game
- Close window to quit

### Console Mode
- Enter moves in algebraic notation (e.g. `e2 e4`)
- Type `quit` to exit

## 📁 Project Structure

Chess-Game/
├── main.cpp          # SFML Graphical Interface

├── class.h           # Class declarations

├── class.cpp         # Class implementations

├── Chess.h           # Header (if separate)

├── pieces.png        # Chess pieces sprite sheet

└── README.md

🎯 Future Improvements

Castling
En Passant
Pawn promotion choice (Queen/Rook/Bishop/Knight)
Move history & undo
AI opponent
Sound effects
Threefold repetition & 50-move rule
