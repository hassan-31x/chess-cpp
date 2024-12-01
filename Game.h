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
    Game(): whitePlayer(true), blackPlayer(false), isWhiteTurn(true), gameStarted(false), firstMoveMade(false), moveLog(), validMoves() {
        initializeWindow();
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            render();
        }
    }


private:
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (!gameStarted && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    gameStarted = true;
                }
            }

            if (gameStarted && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    int col = event.mouseButton.x / Board::SQUARE_SIZE;
                    int row = event.mouseButton.y / Board::SQUARE_SIZE;

                    cout << "Clicked square: (" << row << ", " << col << ")" << endl;
                    if (row == sqClicked.first && col == sqClicked.second) {
                        sqClicked = std::make_pair(-1, -1);
                        firstMoveMade = false;
                        continue;
                    }

                    //if one click is already done
                    if (firstMoveMade) {
                        cout << "Second click" << endl;

                        bool moveValid = board.movePiece(sqClicked.first, sqClicked.second, row, col, validMoves);

                        if (!moveValid) {
                            cout << "Invalid move" << endl;
                            sqClicked = std::make_pair(-1, -1);
                            firstMoveMade = false;

                            continue;
                        }
                        

                        Move move(sqClicked, std::make_pair(row, col), board.getSquares());
                        cout << "Move: " << move << endl;
                        moveLog.push_back(move);

                        isWhiteTurn = !isWhiteTurn;
                        sqClicked = std::make_pair(-1, -1);
                        firstMoveMade = false;
                    } else {
                        if (board.getPiece(row, col) == nullptr) {
                            continue;
                        }
                        cout << "First click" << endl;
                        firstMoveMade = true;
                        sqClicked = std::make_pair(row, col);

                        validMoves = board.getPiece(row, col)->getPossibleMoves(row, col, board.getSquares());
                        board.highlightSquares(validMoves, row, col, isWhiteTurn);
                    }
            }
        }
    }

    void render() {
        window.clear();

        if (!gameStarted) {
            window.draw(backgroundSprite);
            window.draw(startButton);
        } 
        else {
            board.draw(window);
        }

        window.display();
    }

    void initializeWindow() {
        window.create(sf::VideoMode(Board::BOARD_SIZE * Board::SQUARE_SIZE, Board::BOARD_SIZE * Board::SQUARE_SIZE), "Chess");

        if (!backgroundTexture.loadFromFile("background.jpg")) {
        }
        backgroundSprite.setTexture(backgroundTexture);

        if (!font.loadFromFile("arial.ttf")) {
        }

        startButton.setFont(font);
        startButton.setString("Start");
        startButton.setCharacterSize(24);
        startButton.setFillColor(sf::Color::White);
        startButton.setPosition((Board::BOARD_SIZE * Board::SQUARE_SIZE) / 2, (Board::BOARD_SIZE * Board::SQUARE_SIZE) / 2);
    }
};
