#pragma once 

#include<iostream> 
#include<vector> 

// Class definition for Piece
class Piece {
    private:
        bool isWhite; // Boolean variable to store the color of the piece (true for white, false for black)
        std::string name; // String variable to store the name of the piece
    public:
        // Constructor to initialize the piece with its color and default name "--"
        Piece(bool isWhite): isWhite(isWhite), name("--") {}
        
        // Virtual destructor to allow proper cleanup of derived class objects
        virtual ~Piece() {}

        // Pure virtual function to get possible moves for the piece
        // Must be implemented by derived classes
        virtual std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) = 0;
        
        // Getter function to return the color of the piece
        bool getIsWhite() const { 
            return isWhite; 
        }
        
        // Getter function to return the name of the piece
        std::string getName() const {
            return name;
        }
    protected:
        // Setter function to set the name of the piece
        void setName(const std::string& n) {
            name = n;
        }
};

// Class definition for King, derived from Piece
class King: public Piece {
    public:
        // Constructor to initialize the King with its color and name
        King(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wK" : "bK");
        }
        
        // Override function to get possible moves for the King
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            // Possible directions the King can move
            std::vector<std::pair<int, int>> directions = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, 
                                                         {0,1}, {1,-1}, {1,0}, {1,1}};
            
            // Check each direction for valid moves
            for (const auto& dir : directions) {
                int newRow = r + dir.first;
                int newCol = c + dir.second;
                // Ensure the move is within the board boundaries
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                    // Check if the destination is empty or contains an opponent's piece
                    if (board[newRow][newCol] == nullptr || 
                        board[newRow][newCol]->getIsWhite() != getIsWhite()) {
                        moves.push_back({newRow, newCol});
                    }
                }
            }
            return moves;
        }
};

// Class definition for Queen, derived from Piece
class Queen: public Piece {
    public:
        // Constructor to initialize the Queen with its color and name
        Queen(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wQ" : "bQ");
        }
        
        // Override function to get possible moves for the Queen
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            // Possible directions the Queen can move
            std::vector<std::pair<int, int>> directions = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, 
                                                         {0,1}, {1,-1}, {1,0}, {1,1}};
            
            // Check each direction for valid moves
            for (const auto& dir : directions) {
                for (int i = 1; i < 8; i++) {
                    int newRow = r + dir.first * i;
                    int newCol = c + dir.second * i;
                    // Ensure the move is within the board boundaries
                    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                        // Check if the destination is empty
                        if (board[newRow][newCol] == nullptr) {
                            moves.push_back({newRow, newCol});
                        } else {
                            // Check if the destination contains an opponent's piece
                            if (board[newRow][newCol]->getIsWhite() != getIsWhite()) {
                                moves.push_back({newRow, newCol});
                            }
                            break;
                        }
                    } else break;
                }
            }
            return moves;
        }
};

// Class definition for Rook, derived from Piece
class Rook: public Piece {
    public:
        // Constructor to initialize the Rook with its color and name
        Rook(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wR" : "bR");
        }
        
        // Override function to get possible moves for the Rook
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            // Possible directions the Rook can move
            std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
            
            // Check each direction for valid moves
            for (const auto& dir : directions) {
                for (int i = 1; i < 8; i++) {
                    int newRow = r + dir.first * i;
                    int newCol = c + dir.second * i;
                    // Ensure the move is within the board boundaries
                    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                        // Check if the destination is empty
                        if (board[newRow][newCol] == nullptr) {
                            moves.push_back({newRow, newCol});
                        } else {
                            // Check if the destination contains an opponent's piece
                            if (board[newRow][newCol]->getIsWhite() != getIsWhite()) {
                                moves.push_back({newRow, newCol});
                            }
                            break;
                        }
                    } else break;
                }
            }
            return moves;
        }
};

// Class definition for Bishop, derived from Piece
class Bishop: public Piece {
    public:
        // Constructor to initialize the Bishop with its color and name
        Bishop(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wB" : "bB");
        }
        
        // Override function to get possible moves for the Bishop
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            // Possible directions the Bishop can move
            std::vector<std::pair<int, int>> directions = {{-1,-1}, {-1,1}, {1,-1}, {1,1}};
            
            // Check each direction for valid moves
            for (const auto& dir : directions) {
                for (int i = 1; i < 8; i++) {
                    int newRow = r + dir.first * i;
                    int newCol = c + dir.second * i;
                    // Ensure the move is within the board boundaries
                    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                        // Check if the destination is empty
                        if (board[newRow][newCol] == nullptr) {
                            moves.push_back({newRow, newCol});
                        } else {
                            // Check if the destination contains an opponent's piece
                            if (board[newRow][newCol]->getIsWhite() != getIsWhite()) {
                                moves.push_back({newRow, newCol});
                            }
                            break;
                        }
                    } else break;
                }
            }
            return moves;
        }
};

// Class definition for Knight, derived from Piece
class Knight: public Piece {
    public:
        // Constructor to initialize the Knight with its color and name
        Knight(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wN" : "bN");
        }
        
        // Override function to get possible moves for the Knight
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            // Possible moves the Knight can make
            std::vector<std::pair<int, int>> knightMoves = {{-2,-1}, {-2,1}, {-1,-2}, {-1,2},
                                                          {1,-2}, {1,2}, {2,-1}, {2,1}};
            
            // Check each move for validity
            for (const auto& move : knightMoves) {
                int newRow = r + move.first;
                int newCol = c + move.second;
                // Ensure the move is within the board boundaries
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                    // Check if the destination is empty or contains an opponent's piece
                    if (board[newRow][newCol] == nullptr || 
                        board[newRow][newCol]->getIsWhite() != getIsWhite()) {
                        moves.push_back({newRow, newCol});
                    }
                }
            }
            return moves;
        }
};

// Class definition for Pawn, derived from Piece
class Pawn: public Piece {
    public:
        // Constructor to initialize the Pawn with its color and name
        Pawn(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wp" : "bp");
        }

        // Override function to get possible moves for the Pawn
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            int direction = getIsWhite() ? -1 : 1; // Determine the direction of movement based on color

            // Forward move
            if (board[r + direction][c] == nullptr) {
                moves.push_back({r + direction, c});
                // Initial two-square move
                if ((getIsWhite() && r == 6) || (!getIsWhite() && r == 1)) {
                    if (board[r + 2 * direction][c] == nullptr) {
                        moves.push_back({r + 2 * direction, c});
                    }
                }
            }
            
            // Captures
            if (c - 1 >= 0 && board[r + direction][c - 1] != nullptr && 
                board[r + direction][c - 1]->getIsWhite() != getIsWhite()) {
                moves.push_back({r + direction, c - 1});
            }
            if (c + 1 < 8 && board[r + direction][c + 1] != nullptr && 
                board[r + direction][c + 1]->getIsWhite() != getIsWhite()) {
                moves.push_back({r + direction, c + 1});
            }
            
            return moves;
        }
};