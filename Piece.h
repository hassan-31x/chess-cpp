class Piece {
    private:
        bool isWhite;
        std::string name;
    public:
        Piece(bool isWhite): isWhite(isWhite), name("--") {}
        virtual ~Piece() {}

        virtual std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) = 0;
        bool getIsWhite() const { 
            return isWhite; 
        }
        std::string getName() const {
            return name;
        }
    protected:
        void setName(const std::string& n) {
            name = n;
        }
};

class King: public Piece {
    public:
        King(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wK" : "bK");
        }
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            std::vector<std::pair<int, int>> directions = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, 
                                                         {0,1}, {1,-1}, {1,0}, {1,1}};
            
            for (const auto& dir : directions) {
                int newRow = r + dir.first;
                int newCol = c + dir.second;
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                    if (board[newRow][newCol] == nullptr || 
                        board[newRow][newCol]->getIsWhite() != getIsWhite()) {
                        moves.push_back({newRow, newCol});
                    }
                }
            }
            return moves;
        }
};

class Queen: public Piece {
    public:
        Queen(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wQ" : "bQ");
        }
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            std::vector<std::pair<int, int>> directions = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, 
                                                         {0,1}, {1,-1}, {1,0}, {1,1}};
            
            for (const auto& dir : directions) {
                for (int i = 1; i < 8; i++) {
                    int newRow = r + dir.first * i;
                    int newCol = c + dir.second * i;
                    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                        if (board[newRow][newCol] == nullptr) {
                            moves.push_back({newRow, newCol});
                        } else {
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

class Rook: public Piece {
    public:
        Rook(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wR" : "bR");
        }
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
            
            for (const auto& dir : directions) {
                for (int i = 1; i < 8; i++) {
                    int newRow = r + dir.first * i;
                    int newCol = c + dir.second * i;
                    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                        if (board[newRow][newCol] == nullptr) {
                            moves.push_back({newRow, newCol});
                        } else {
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

class Bishop: public Piece {
    public:
        Bishop(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wB" : "bB");
        }
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            std::vector<std::pair<int, int>> directions = {{-1,-1}, {-1,1}, {1,-1}, {1,1}};
            
            for (const auto& dir : directions) {
                for (int i = 1; i < 8; i++) {
                    int newRow = r + dir.first * i;
                    int newCol = c + dir.second * i;
                    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                        if (board[newRow][newCol] == nullptr) {
                            moves.push_back({newRow, newCol});
                        } else {
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

class Knight: public Piece {
    public:
        Knight(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wN" : "bN");
        }
        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            std::vector<std::pair<int, int>> knightMoves = {{-2,-1}, {-2,1}, {-1,-2}, {-1,2},
                                                          {1,-2}, {1,2}, {2,-1}, {2,1}};
            
            for (const auto& move : knightMoves) {
                int newRow = r + move.first;
                int newCol = c + move.second;
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                    if (board[newRow][newCol] == nullptr || 
                        board[newRow][newCol]->getIsWhite() != getIsWhite()) {
                        moves.push_back({newRow, newCol});
                    }
                }
            }
            return moves;
        }
};

class Pawn: public Piece {
    public:
        Pawn(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wp" : "bp");
        }

        std::vector<std::pair<int, int>> getPossibleMoves(int r, int c, Piece* board[8][8]) override {
            std::vector<std::pair<int, int>> moves;
            int direction = getIsWhite() ? -1 : 1;
            
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
