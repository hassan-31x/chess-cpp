class Piece {
    private:
        bool isWhite;
    public:
        Piece(bool isWhite): isWhite(isWhite) {}
        virtual ~Piece() {}

        virtual bool isValidMove(int startX, int startY, int endX, int endY) = 0; 
        bool getIsWhite() const { 
            return isWhite; 
        }
};

class King: public Piece {
    public:
        King(bool isWhite): Piece(isWhite) {}
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;;
        }
};

class Queen: public Piece {
    public:
        Queen(bool isWhite): Piece(isWhite) {}
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;
        }
};

class Rook: public Piece {
    public:
        Rook(bool isWhite): Piece(isWhite) {}
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;
        }
};

class Bishop: public Piece {
    public:
        Bishop(bool isWhite): Piece(isWhite) {}
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;
        }
};

class Knight: public Piece {
    public:
        Knight(bool isWhite): Piece(isWhite) {}
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;
        }
};

class Pawn: public Piece {
    public:
        Pawn(bool isWhite): Piece(isWhite) {}
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;
        }
};
