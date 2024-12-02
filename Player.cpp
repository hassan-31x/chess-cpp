class Player {
    private:
        bool isWhite;
        std::string name;

    public:
        Player(bool isWhite = true, std::string name = "Player"): isWhite(isWhite), name(name) {}
        
        bool getIsWhite() const { 
            return isWhite; 
        }

        std::string getName() const {
            return name;
        }

        void setName(std::string n) {
            name = n;
        }
};

