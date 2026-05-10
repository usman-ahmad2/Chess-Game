#include "SFML/Graphics.hpp"
#include "Chess.h"

const int TILE = 100;
const int BOARD_SIZE = TILE * 8;
const int WIN_H = BOARD_SIZE + 50;  // extra space for status bar

// Maps PieceType symbol to column index in the sprite sheet
int getSpriteCol(char symbol)
{
    char s = toupper(symbol);
    switch (s)
    {
    case 'K': return 0;
    case 'Q': return 1;
    case 'B': return 2;
    case 'N': return 3;
    case 'R': return 4;
    case 'P': return 5;
    default:  return 0;
    }
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(BOARD_SIZE, WIN_H),
        "Chess Game"
    );
    window.setFramerateLimit(60);

    // Load assets 
    sf::Texture piecesTex;
    if (!piecesTex.loadFromFile("pieces.png"))
    {
        // If image missing, show error and exit
        return -1;
    }

    sf::Font font;
    bool fontLoaded = font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    int pieceW = piecesTex.getSize().x / 6;
    int pieceH = piecesTex.getSize().y / 2;

    // Colors 
    sf::Color lightSq(240, 217, 181);
    sf::Color darkSq(181, 136, 99);
    sf::Color selectedC(20, 180, 20, 150);
    sf::Color validC(20, 180, 20, 80);
    sf::Color lastMoveC(100, 180, 255, 80);

    // Game state 
    Game game;
    game.getBoard().initializeBoard();
    game.getBoard().setBoardWhite();
    game.getBoard().setBoardBlack();

    int  selRow = -1, selCol = -1;
    bool selected = false;

    // Store last move for highlight
    int lastR1 = -1, lastC1 = -1, lastR2 = -1, lastC2 = -1;

    while (window.isOpen())
    {
        // Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed
                && !game.getGameOver())
            {
                int col = event.mouseButton.x / TILE;
                int row = event.mouseButton.y / TILE;

                if (row >= 0 && row < 8 && col >= 0 && col < 8)
                {
                    if (!selected)
                    {
                        // First click: select a piece
                        Piece* pc = game.getBoard().getPiece(row, col);
                        if (pc != nullptr)
                        {
                            bool myPiece =
                                (game.getIsWhiteTurn() && pc->getColour() == "White") ||
                                (!game.getIsWhiteTurn() && pc->getColour() == "Black");

                            if (myPiece)
                            {
                                selRow = row; selCol = col;
                                selected = true;
                            }
                        }
                    }
                    else
                    {
                        // Second click: try to move
                        if (row == selRow && col == selCol)
                        {
                            // Clicked same square: deselect
                            selected = false;
                            selRow = selCol = -1;
                        }
                        else
                        {
                            bool moved = game.tryMove(selRow, selCol, row, col);
                            if (moved)
                            {
                                lastR1 = selRow; lastC1 = selCol;
                                lastR2 = row;    lastC2 = col;
                            }
                            selected = false;
                            selRow = selCol = -1;
                        }
                    }
                }
            }

            // R to restart
            if (event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::R)
            {
                game = Game();
                game.getBoard().initializeBoard();
                game.getBoard().setBoardWhite();
                game.getBoard().setBoardBlack();
                selected = false;
                selRow = selCol = -1;
                lastR1 = lastC1 = lastR2 = lastC2 = -1;
            }
        }

        window.clear(sf::Color(30, 30, 30));

        // Draw board squares 
        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                sf::RectangleShape sq(sf::Vector2f(TILE, TILE));
                sq.setPosition(c * TILE, r * TILE);

                // Base color
                bool isLight = (r + c) % 2 == 0;
                sq.setFillColor(isLight ? lightSq : darkSq);
                window.draw(sq);

                // Last move highlight
                if ((r == lastR1 && c == lastC1) || (r == lastR2 && c == lastC2))
                {
                    sq.setFillColor(lastMoveC);
                    window.draw(sq);
                }

                // Selected square highlight
                if (selected && r == selRow && c == selCol)
                {
                    sq.setFillColor(selectedC);
                    window.draw(sq);
                }

                // Valid move dots for selected piece
                if (selected)
                {
                    Piece* pc = game.getBoard().getPiece(selRow, selCol);
                    if (pc && pc->isValidMove(selRow, selCol, r, c,
                        game.getBoard()))
                    {
                        Piece* target = game.getBoard().getPiece(r, c);
                        if (target == nullptr)
                        {
                            // Empty square draw a dot
                            sf::CircleShape dot(TILE * 0.15f);
                            dot.setFillColor(validC);
                            dot.setOrigin(TILE * 0.15f, TILE * 0.15f);
                            dot.setPosition(c * TILE + TILE / 2, r * TILE + TILE / 2);
                            window.draw(dot);
                        }
                        else
                        {
                            // Enemy square draw a ring
                            sf::CircleShape ring(TILE * 0.47f);
                            ring.setFillColor(sf::Color::Transparent);
                            ring.setOutlineColor(sf::Color(20, 180, 20, 180));
                            ring.setOutlineThickness(4);
                            ring.setOrigin(TILE * 0.47f, TILE * 0.47f);
                            ring.setPosition(c * TILE + TILE / 2, r * TILE + TILE / 2);
                            window.draw(ring);
                        }
                    }
                }
            }
        }

        // Draw pieces 
        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                Piece* pc = game.getBoard().getPiece(r, c);
                if (!pc) continue;

                char sym = pc->getSymbol();
                int  spriteRow = (pc->getColour() == "White") ? 0 : 1;
                int  spriteCol = getSpriteCol(sym);

                sf::Sprite sprite(piecesTex);
                sprite.setTextureRect(sf::IntRect(
                    spriteCol * pieceW,
                    spriteRow * pieceH,
                    pieceW, pieceH
                ));
                sprite.setScale(
                    (float)TILE / pieceW,
                    (float)TILE / pieceH
                );
                sprite.setPosition(c * TILE, r * TILE);
                window.draw(sprite);
            }
        }

        // Draw rank
        if (fontLoaded)
        {
            for (int i = 0; i < 8; i++)
            {
                // Rank numbers (1–8)
                sf::Text rankLabel;
                rankLabel.setFont(font);
                rankLabel.setCharacterSize(18);
                rankLabel.setFillColor(sf::Color(0, 0, 0, 255));
                rankLabel.setString(to_string(8 - i));
                rankLabel.setPosition(3, i * TILE + 3);
                window.draw(rankLabel);

                // File letters (a–h)
                sf::Text fileLabel;
                fileLabel.setFont(font);
                fileLabel.setCharacterSize(18);
                fileLabel.setFillColor(sf::Color(0, 0, 0, 255));
                string fl = ""; fl += (char)('a' + i);
                fileLabel.setString(fl);
                fileLabel.setPosition(i * TILE + TILE - 12, BOARD_SIZE - 23);
                window.draw(fileLabel);
            }

            // Status bar 
            sf::RectangleShape bar(sf::Vector2f(BOARD_SIZE, 50));
            bar.setPosition(0, BOARD_SIZE);
            bar.setFillColor(sf::Color(20, 20, 20));
            window.draw(bar);

            sf::Text status;
            status.setFont(font);
            status.setCharacterSize(18);
            status.setFillColor(sf::Color::White);
            status.setString(game.getStatus() + "   |   R = restart");
            status.setPosition(10, BOARD_SIZE + 12);
            window.draw(status);
        }

        window.display();
    }

    return 0;
}