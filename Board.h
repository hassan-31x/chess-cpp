#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

class Board {
    private:
        Piece* squares[8][8];
        std::map<std::string, sf::Texture> images;
        std::vector<std::vector<std::string>> board = {
            {"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
            {"bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp"},
            {"--", "--", "--", "--", "--", "--", "--", "--"},
            {"--", "--", "--", "--", "--", "--", "--", "--"},
            {"--", "--", "--", "--", "--", "--", "--", "--"},
            {"--", "--", "--", "--", "--", "--", "--", "--"},
            {"wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp"},
            {"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}
        };

    public:
        static const int BOARD_SIZE = 8;
        static const int SQUARE_SIZE = 120;

        Board() {
            loadImages();
        }
        
        ~Board() {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    delete squares[i][j];
                }
            }
        }

        void draw(sf::RenderWindow& window) {
            drawBoard(window);
            drawPieces(window);
        }

        void loadImages() {
            std::vector<std::string> pieces = {"wp", "wR", "wN", "wB", "wQ", "wK", 
                                            "bp", "bR", "bN", "bB", "bQ", "bK"};

            for (const auto &piece: pieces) {
                sf::Texture temp;
                if (temp.loadFromFile("images/" + piece + ".png")) {
                    images[piece] = temp;
                }
            }
        }

    private:
        void drawBoard(sf::RenderWindow& window) {
            sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            std::vector<sf::Color> colors = {sf::Color::White, sf::Color(192, 192, 192)};

            for (int row = 0; row < BOARD_SIZE; row++) {
                for (int col = 0; col < BOARD_SIZE; ++col) {
                    square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
                    square.setFillColor(colors[(row + col) % 2]);
                    window.draw(square);
                }
            }
        }
        
        void drawPieces(sf::RenderWindow &window) {
            for (int r = 0; r < BOARD_SIZE; r++) {
                for (int c = 0; c < BOARD_SIZE; ++c) {
                    std::string piece = board[r][c];
                    if (piece != "--") {
                        sf::Sprite sprite;
                        sprite.setTexture(images.at(piece));
                        sprite.setScale(1.8f, 1.8f);
                        sprite.setPosition(c * SQUARE_SIZE, r * SQUARE_SIZE);
                        window.draw(sprite);
                    }
                }
            }
        }
};
