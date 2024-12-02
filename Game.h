#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include "Move.h"
#include <SFML/Audio.hpp>

class Game {
    private:
        Board board;
        Player whitePlayer;
        Player blackPlayer;
        bool isWhiteTurn;

        bool gameStarted;
        bool gameEnded;

        Player player1;
        Player player2;
        Player winner;

        bool firstMoveMade;
        std::pair<int, int> sqClicked;
        int totalMoves;

        sf::RenderWindow window;
        sf::Font font;
        
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;  
        sf::Texture endScreenTexture;
        sf::Sprite endScreenSprite;
        sf::Text player1Text;
        sf::Text player2Text;

        std::vector<Move> moveLog;
        std::vector<std::pair<int, int>> validMoves;
        sf::Music music;

    public:
        Game(): whitePlayer(true, "Player 1"), blackPlayer(false, "Player 2"), isWhiteTurn(true), gameStarted(false), gameEnded(false), player1(true, "Player 1"), player2(false, "Player 2"), winner(), firstMoveMade(false), moveLog(), validMoves(), totalMoves(0), window(), font(), backgroundTexture(), backgroundSprite(), music() {
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

                if (gameEnded) {
                    break;
                }

                if (!gameStarted && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                    if (event.mouseButton.x > 175 && event.mouseButton.x < 375 && event.mouseButton.y > 320 && event.mouseButton.y < 415) {
                        gameStarted = true;
                    }

                    if (event.mouseButton.x > 420 && event.mouseButton.x < 620 && event.mouseButton.y > 320 && event.mouseButton.y < 415) {
                        window.close();
                    }
                }

                if (gameStarted && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        int col = event.mouseButton.x / Board::SQUARE_SIZE;
                        int row = event.mouseButton.y / Board::SQUARE_SIZE;


                        //loading music file
                        if (!music.openFromFile("audios\\capture.wav")) {
                            cout << "Error loading music file" << endl;
                        }
                        music.play();

                        if (row == sqClicked.first && col == sqClicked.second) {
                            sqClicked = std::make_pair(-1, -1);
                            firstMoveMade = false;
                            continue;
                        }

                        //if one click is already done
                        if (firstMoveMade) {
                            int moveValid = board.movePiece(sqClicked.first, sqClicked.second, row, col, validMoves);

                            if (moveValid == 0) {
                                cout << "Invalid move" << endl;
                                sqClicked = std::make_pair(-1, -1);
                                firstMoveMade = false;

                                continue;
                            }

                            if (moveValid == -1) {
                                gameEnded = true;
                                winner = isWhiteTurn ? player1 : player2;
                                winner.setName((isWhiteTurn ? player1 : player2).getName());

                                continue;
                            }

                            Move move(sqClicked, std::make_pair(row, col), board.getSquares());
                            moveLog.push_back(move);
                            std::cout << move << std::endl;

                            totalMoves++;

                            isWhiteTurn = !isWhiteTurn;
                            sqClicked = std::make_pair(-1, -1);
                            firstMoveMade = false;

                            validMoves.clear();
                            board.highlightSquares(validMoves, -1, -1);
                        } else {
                            if (board.getPiece(row, col) == nullptr) {
                                continue;
                            }

                            if (isWhiteTurn != board.getPiece(row, col)->getIsWhite()) {
                                continue;
                            }

                            firstMoveMade = true;
                            sqClicked = std::make_pair(row, col);

                            validMoves = board.getPiece(row, col)->getPossibleMoves(row, col, board.getSquares());
                            board.highlightSquares(validMoves, row, col);
                        }
                
                }
            }
        }

        void render() {
            window.clear();

            if (!gameStarted) {
                window.draw(backgroundSprite);
            } 
            else if (gameEnded) {
                window.draw(endScreenSprite);

                if (winner.getIsWhite()) {
                    player1Text.setPosition(200, 200);

                    player2Text.setString("Player 2");
                    player2Text.setPosition(400, 200);
                } else {
                    player1Text.setString("Player 1");
                    player1Text.setPosition(200, 200);

                    player2Text.setPosition(400, 200);
                }


                window.draw(player1Text);
                window.draw(player2Text);
            }
            else {
                board.draw(window);
            }

            window.display();
        }

        void initializeWindow() {
            window.create(sf::VideoMode(Board::BOARD_SIZE * Board::SQUARE_SIZE, Board::BOARD_SIZE * Board::SQUARE_SIZE), "Chess");

            if (!backgroundTexture.loadFromFile("startscreen.png")) {
                cout << "Error loading background texture" << endl;
            }
            backgroundSprite.setTexture(backgroundTexture);

            if (!endScreenTexture.loadFromFile("endscreen.png")) {
                cout << "Error loading end screen texture" << endl;
            }
            endScreenSprite.setTexture(endScreenTexture);

            if (!font.loadFromFile("arial.ttf")) {
                cout << "Error loading font" << endl;
            }
            player1Text.setFont(font);
            player1Text.setString("Player 1");
            player1Text.setCharacterSize(24);
            player1Text.setFillColor(sf::Color::White);

            player2Text.setFont(font);
            player2Text.setString("Player 2"); 
            player2Text.setCharacterSize(24);
            player2Text.setFillColor(sf::Color::White);

        }
};
