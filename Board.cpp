#include <iostream> 
#include <SFML/Graphics.hpp> 
#include "Piece.cpp" 
#include <map> 
#include <vector>
#include <string> 

using namespace std; 

// Class definition for Board
class Board {
    private:
        Piece* squares[8][8]; // 2D array to store pointers to pieces on the board
        std::map<std::string, sf::Texture> images; // Map to store textures for piece images
        std::vector<std::pair<int, int>> highlightedSquares; // Vector to store highlighted squares
        int highlightedRow; // Integer to store the row of the highlighted square
        int highlightedCol; // Integer to store the column of the highlighted square

        // Private function to draw the board
        void drawBoard(sf::RenderWindow& window) {
            sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE)); // Creates a square shape with the size of a board square
            std::vector<sf::Color> colors = {sf::Color::White, sf::Color(192, 192, 192)}; // Colors for the board squares

            sf::Color validMovesColor(255, 255, 0, 64); // Color for valid move squares
            sf::Color highlightColor(152, 251, 152, 128); // Color for the highlighted square

            // Loop through each row and column of the board
            for (int row = 0; row < BOARD_SIZE; row++) {
                for (int col = 0; col < BOARD_SIZE; col++) {
                    square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE); // Set the position of the square

                    // Check if the current square is the highlighted square
                    if (row == highlightedRow && col == highlightedCol) {
                        square.setFillColor(highlightColor); // Set the color to highlight color
                        window.draw(square); // Draw the square
                    } else {
                        square.setFillColor(colors[(row + col) % 2]); // Set the color based on the row and column
                        window.draw(square); // Draw the square
                        
                        bool isHighlighted = false; // Flag to check if the square is highlighted
                        // Loop through the highlighted squares
                        for (const auto& move : highlightedSquares) {
                            if (move.first == row && move.second == col) {
                                square.setFillColor(validMovesColor); // Set the color to valid moves color
                                window.draw(square); // Draw the square
                                break;
                            }
                        }

                        window.draw(square); // Draw the square
                    }
                }
            }
        }

        // Private function to draw the pieces on the board
        void drawPieces(sf::RenderWindow &window) {
            // Loop through each row and column of the board
            for (int r = 0; r < BOARD_SIZE; r++) {
                for (int c = 0; c < BOARD_SIZE; c++) {
                    Piece* piece = squares[r][c]; // Get the piece at the current square
                    if (piece != nullptr) { // Check if there is a piece
                        sf::Sprite sprite; // Create a sprite
                        sprite.setTexture(images.at(piece->getName())); // Set the texture of the sprite to the piece image
                        sprite.setScale(1.3f, 1.3f); // Scale the sprite
                        sprite.setPosition(c * SQUARE_SIZE + 10, r * SQUARE_SIZE + 10); // Set the position of the sprite
                        window.draw(sprite); // Draw the sprite
                    }
                }
            }
        }

    public:
        static const int BOARD_SIZE = 8; // Constant for the size of the board
        static const int SQUARE_SIZE = 100; // Constant for the size of a square

        // Constructor to initialize the board
        Board() {
            loadImages(); // Load the piece images
            
            // Initialize the board squares to nullptr
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    squares[i][j] = nullptr;
                }
            }

            // Initialize the black pieces
            squares[0][0] = new Rook(false);
            squares[0][1] = new Knight(false);
            squares[0][2] = new Bishop(false);
            squares[0][3] = new Queen(false);
            squares[0][4] = new King(false);
            squares[0][5] = new Bishop(false);
            squares[0][6] = new Knight(false);
            squares[0][7] = new Rook(false);

            // Initialize the black pawns
            for (int j = 0; j < BOARD_SIZE; j++) {
                squares[1][j] = new Pawn(false);
            }

            // Initialize the white pawns
            for (int j = 0; j < BOARD_SIZE; j++) {
                squares[6][j] = new Pawn(true);
            }

            // Initialize the white pieces
            squares[7][0] = new Rook(true);
            squares[7][1] = new Knight(true);
            squares[7][2] = new Bishop(true);
            squares[7][3] = new Queen(true);
            squares[7][4] = new King(true);
            squares[7][5] = new Bishop(true);
            squares[7][6] = new Knight(true);
            squares[7][7] = new Rook(true);
        }
        
        // Destructor to clean up the board
        ~Board() {
            // Loop through each row and column of the board
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    delete squares[i][j]; // Delete the piece at the current square
                }
            }
        }

        // Function to get the squares of the board
        Piece* (&getSquares())[8][8] {
            return squares;
        }

        // Function to draw the board and pieces
        void draw(sf::RenderWindow& window) {
            drawBoard(window); // Draw the board
            drawPieces(window); // Draw the pieces
        }

        // Function to load the piece images
        void loadImages() {
            std::vector<std::string> pieces = {"wp", "wR", "wN", "wB", "wQ", "wK", 
                                            "bp", "bR", "bN", "bB", "bQ", "bK"}; // List of piece names

            // Loop through each piece name
            for (const auto &piece: pieces) {
                sf::Texture temp; // Create a temporary texture
                if (temp.loadFromFile("images/" + piece + ".png")) { // Load the image file
                    images[piece] = temp; // Store the texture in the map
                }
            }
        }

        // Function to move a piece on the board
        int movePiece(int r1, int c1, int r2, int c2, std::vector<std::pair<int, int>> validMoves) {
            // Loop through the valid moves
            for (const auto& move : validMoves) {
                if (move.first == r2 && move.second == c2) { // Check if the move is valid

                    Piece* temp = squares[r1][c1]; // Get the piece being moved
                    Piece* endPiece = squares[r2][c2]; // Get the piece at the destination square
                    squares[r1][c1] = nullptr; // Set the starting square to nullptr
                    squares[r2][c2] = temp; // Move the piece to the destination square

                    // Check if the moved piece captured a king
                    if (endPiece != nullptr && endPiece->getName().find('K') != std::string::npos) {
                        return -1; // Return -1 if a king is captured
                    }

                    return 1; // Return 1 if the move is successful
                }
            }
            return 0; // Return 0 if the move is invalid
        }

        // Function to get the piece at a specific square
        Piece* getPiece(int r, int c) {
            return squares[r][c];
        }

        // Function to highlight squares
        void highlightSquares(std::vector<std::pair<int, int>> moves, int r, int c) {
            highlightedSquares = moves; // Set the highlighted squares

            highlightedRow = r; // Set the highlighted row
            highlightedCol = c; // Set the highlighted column
        }
};