class Player {
    private:
        bool isWhite;

    public:
        Player(bool isWhite): isWhite(isWhite) {}
        
        bool getIsWhite() const { 
            return isWhite; 
        }
};

