class Piece {
    private:
        bool isWhite;
        std::string name;
    public:
        Piece(bool isWhite): isWhite(isWhite), name("--") {}
        virtual ~Piece() {}

        virtual bool isValidMove(int startX, int startY, int endX, int endY) = 0;
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
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;;
        }
};

class Queen: public Piece {
    public:
        Queen(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wQ" : "bQ");
        }
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;
        }
};

class Rook: public Piece {
    public:
        Rook(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wR" : "bR");
        }
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;
        }
};

class Bishop: public Piece {
    public:
        Bishop(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wB" : "bB");
        }
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;
        }
};

class Knight: public Piece {
    public:
        Knight(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wN" : "bN");
        }
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;
        }
};

class Pawn: public Piece {
    public:
        Pawn(bool isWhite): Piece(isWhite) {
            setName(isWhite ? "wp" : "bp");
        }
        bool isValidMove(int startX, int startY, int endX, int endY) override {
            return true;
        }
};
