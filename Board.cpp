#include "Board.h"

Board::Board() {
    loadImages();
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            squares[i][j] = nullptr;
        }
    }

    squares[0][0] = new Rook(false);
    squares[0][1] = new Knight(false);
    squares[0][2] = new Bishop(false);
    squares[0][3] = new Queen(false);
    squares[0][4] = new King(false);
    squares[0][5] = new Bishop(false);
    squares[0][6] = new Knight(false);
    squares[0][7] = new Rook(false);

    for (int j = 0; j < BOARD_SIZE; j++) {
        squares[1][j] = new Pawn(false);
    }

    for (int j = 0; j < BOARD_SIZE; j++) {
        squares[6][j] = new Pawn(true);
    }

    squares[7][0] = new Rook(true);
    squares[7][1] = new Knight(true);
    squares[7][2] = new Bishop(true);
    squares[7][3] = new Queen(true);
    squares[7][4] = new King(true);
    squares[7][5] = new Bishop(true);
    squares[7][6] = new Knight(true);
    squares[7][7] = new Rook(true);
}

Board::~Board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            delete squares[i][j];
        }
    }
}

void Board::drawBoard(sf::RenderWindow& window) {
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

void Board::drawPieces(sf::RenderWindow &window) {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            Piece* piece = squares[r][c];
            if (piece != nullptr) {
                sf::Sprite sprite;
                sprite.setTexture(images.at(piece->getName()));
                sprite.setScale(1.3f, 1.3f);
                sprite.setPosition(c * SQUARE_SIZE + 10, r * SQUARE_SIZE + 10);
                window.draw(sprite);
            }
        }
    }
}

Piece* (*Board::getSquares())[8] {
    return squares;
}

void Board::draw(sf::RenderWindow& window) {
    drawBoard(window);
    drawPieces(window);
}

void Board::loadImages() {
    std::vector<std::string> pieces = {"wp", "wR", "wN", "wB", "wQ", "wK", 
                                    "bp", "bR", "bN", "bB", "bQ", "bK"};

    for (const auto &piece: pieces) {
        sf::Texture temp;
        if (temp.loadFromFile("images/" + piece + ".png")) {
            images[piece] = temp;
        }
    }
}



bool Board::movePiece(int r1, int c1, int r2, int c2, std::vector<std::pair<int, int>> validMoves) {
    for (const auto& move : validMoves) {
        if (move.first == r2 && move.second == c2) {
            squares[r1][c1] = nullptr;
            squares[r2][c2] = squares[r1][c1];
            return true;
        }
    }
    return false;
}

Piece* Board::getPiece(int r, int c) {
    return squares[r][c];
}

void Board::highlightSquares(std::vector<std::pair<int, int>> moves, int r, int c, bool isWhite) {
    sf::RenderWindow tempWindow(sf::VideoMode(BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE), "Chess");
    sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    std::vector<sf::Color> colors = {sf::Color::White, sf::Color(192, 192, 192)};

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
            if (row == r && col == c) {
                square.setFillColor(sf::Color::Yellow);
            } else {
                bool isValidMove = false;
                for (const auto& move : moves) {
                    if (move.first == row && move.second == col) {
                        isValidMove = true;
                        break;
                    }
                }
                if (isValidMove) {
                    square.setFillColor(sf::Color::Green); // Highlight possible moves
                } else {
                    square.setFillColor(colors[(row + col) % 2]);
                }
            }
            tempWindow.draw(square);
        }
    }
    tempWindow.display();
}