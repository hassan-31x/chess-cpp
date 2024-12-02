#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include "Move.h"

class Game {
private:
    Board board;
    Player whitePlayer;
    Player blackPlayer;
    bool isWhiteTurn;
    bool gameStarted;
    bool firstMoveMade;
    std::pair<int, int> sqClicked;

    sf::RenderWindow window;
    sf::Font font;
    sf::Text startButton;
    
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;  
    std::vector<Move> moveLog;
    std::vector<std::pair<int, int>> validMoves;

public:
    Game();

    void run();


private:
    void handleEvents();

    void render();

    void initializeWindow();
};
