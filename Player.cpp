#include <string> 
// Class definition for Player
class Player {
    private:
        bool isWhite; // Boolean variable to store the color of the player (true for white, false for black)
        std::string name; // String variable to store the name of the player

    public:
        // Constructor to initialize the player with its color and name
        // Default values: isWhite is true, name is "Player"
        Player(bool isWhite = true, std::string name = "Player"): isWhite(isWhite), name(name) {}
        
        // Getter function to return the color of the player
        bool getIsWhite() const { 
            return isWhite; 
        }

        // Getter function to return the name of the player
        std::string getName() const {
            return name;
        }

        // Setter function to set the name of the player
        void setName(std::string n) {
            name = n;
        }
};