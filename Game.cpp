#include <SFML/Graphics.hpp> 
#include "Board.cpp" 
#include "Player.cpp" 
#include "Move.cpp" 
#include <SFML/Audio.hpp> 

// Class definition for Game
class Game {
    private:
        Board board; // Instance of the Board class
        Player whitePlayer; // Instance of the Player class for the white player
        Player blackPlayer; // Instance of the Player class for the black player
        bool isWhiteTurn; // Boolean to track whose turn it is (true for white, false for black)

        bool gameStarted; // Boolean to track if the game has started
        bool gameEnded; // Boolean to track if the game has ended

        Player player1; // Instance of the Player class for player 1
        Player player2; // Instance of the Player class for player 2
        Player winner; // Instance of the Player class for the winner

        bool firstMoveMade; // Boolean to track if the first move has been made
        std::pair<int, int> sqClicked; // Pair to store the coordinates of the clicked square
        int totalMoves; // Integer to track the total number of moves

        sf::RenderWindow window; // SFML window for rendering
        sf::Font font; // SFML font for text rendering
        
        sf::Texture backgroundTexture; // SFML texture for the background
        sf::Sprite backgroundSprite; // SFML sprite for the background
        sf::Texture endScreenTexture; // SFML texture for the end screen
        sf::Sprite endScreenSprite; // SFML sprite for the end screen
        sf::Text player1Text; // SFML text for player 1
        sf::Text player2Text; // SFML text for player 2

        std::vector<Move> moveLog; // Vector to store the move log
        std::vector<std::pair<int, int>> validMoves; // Vector to store valid moves
        sf::Music music; // SFML music for playing sounds

    public:
        // Constructor to initialize the game
        Game(): whitePlayer(true, "Player 1"), blackPlayer(false, "Player 2"), isWhiteTurn(true), gameStarted(false), gameEnded(false), player1(true, "Player 1"), player2(false, "Player 2"), winner(), firstMoveMade(false), moveLog(), validMoves(), totalMoves(0), window(), font(), backgroundTexture(), backgroundSprite(), music() {
            initializeWindow(); // Initialize the window
        }

        // Function to run the game loop
        void run() {
            while (window.isOpen()) { // Loop while the window is open
                handleEvents(); // Handle events
                render(); // Render the game
            }
        }

    private:
        // Function to handle events
        void handleEvents() {
            sf::Event event;
            while (window.pollEvent(event)) { // Poll for events
                if (event.type == sf::Event::Closed) { // Check if the window is closed
                    window.close(); // Close the window
                }

                if (gameEnded) { // Check if the game has ended
                    break; // Break the loop
                }

                if (!gameStarted && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // Check if the game has not started and the left mouse button is pressed
                    if (event.mouseButton.x > 175 && event.mouseButton.x < 375 && event.mouseButton.y > 320 && event.mouseButton.y < 415) { // Check if the start button is clicked
                        gameStarted = true; // Start the game
                    }

                    if (event.mouseButton.x > 420 && event.mouseButton.x < 620 && event.mouseButton.y > 320 && event.mouseButton.y < 415) { // Check if the exit button is clicked
                        window.close(); // Close the window
                    }
                }

                if (gameStarted && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // Check if the game has started and the left mouse button is pressed
                    int col = event.mouseButton.x / Board::SQUARE_SIZE; // Calculate the column of the clicked square
                    int row = event.mouseButton.y / Board::SQUARE_SIZE; // Calculate the row of the clicked square

                    // Load the music file
                    if (!music.openFromFile("audios\\capture.wav")) {
                        cout << "Error loading music file" << endl;
                    }
                    music.play(); // Play the music

                    if (row == sqClicked.first && col == sqClicked.second) { // Check if the same square is clicked again
                        sqClicked = std::make_pair(-1, -1); // Reset the clicked square
                        firstMoveMade = false; // Reset the first move flag
                        continue; // Continue to the next iteration
                    }

                    // If one click is already done
                    if (firstMoveMade) {
                        int moveValid = board.movePiece(sqClicked.first, sqClicked.second, row, col, validMoves); // Move the piece

                        if (moveValid == 0) { // Check if the move is invalid
                            cout << "Invalid move" << endl;
                            sqClicked = std::make_pair(-1, -1); // Reset the clicked square
                            firstMoveMade = false; // Reset the first move flag
                            continue; // Continue to the next iteration
                        }

                        if (moveValid == -1) { // Check if a king is captured
                            gameEnded = true; // End the game
                            winner = isWhiteTurn ? player1 : player2; // Set the winner
                            winner.setName((isWhiteTurn ? player1 : player2).getName()); // Set the winner's name
                            continue; // Continue to the next iteration
                        }

                        Move move(sqClicked, std::make_pair(row, col), board.getSquares()); // Create a move
                        moveLog.push_back(move); // Add the move to the move log
                        std::cout << move << std::endl; // Print the move

                        totalMoves++; // Increment the total moves

                        isWhiteTurn = !isWhiteTurn; // Switch the turn
                        sqClicked = std::make_pair(-1, -1); // Reset the clicked square
                        firstMoveMade = false; // Reset the first move flag

                        validMoves.clear(); // Clear the valid moves
                        board.highlightSquares(validMoves, -1, -1); // Clear the highlighted squares
                    } else {
                        if (board.getPiece(row, col) == nullptr) { // Check if there is no piece at the clicked square
                            continue; // Continue to the next iteration
                        }

                        if (isWhiteTurn != board.getPiece(row, col)->getIsWhite()) { // Check if the piece belongs to the current player
                            continue; // Continue to the next iteration
                        }

                        firstMoveMade = true; // Set the first move flag
                        sqClicked = std::make_pair(row, col); // Set the clicked square

                        validMoves = board.getPiece(row, col)->getPossibleMoves(row, col, board.getSquares()); // Get the valid moves for the piece
                        board.highlightSquares(validMoves, row, col); // Highlight the valid moves
                    }
                }
            }
        }

        // Function to render the game
        void render() {
            window.clear(); // Clear the window

            if (!gameStarted) { // Check if the game has not started
                window.draw(backgroundSprite); // Draw the background
            } 
            else if (gameEnded) { // Check if the game has ended
                window.draw(endScreenSprite); // Draw the end screen

                if (winner.getIsWhite()) { // Check if the winner is white
                    player1Text.setPosition(200, 400); // Set the position of player 1 text

                    player2Text.setString("Player 2"); // Set the text for player 2
                    player2Text.setPosition(500, 400); // Set the position of player 2 text
                } else {
                    player1Text.setString("Player 1"); // Set the text for player 1
                    player1Text.setPosition(200, 400); // Set the position of player 1 text

                    player2Text.setPosition(500, 400); // Set the position of player 2 text
                }

                window.draw(player1Text); // Draw player 1 text
                window.draw(player2Text); // Draw player 2 text
            }
            else {
                board.draw(window); // Draw the board and pieces
            }

            window.display(); // Display the window
        }

        // Function to initialize the window
        void initializeWindow() {
            window.create(sf::VideoMode(Board::BOARD_SIZE * Board::SQUARE_SIZE, Board::BOARD_SIZE * Board::SQUARE_SIZE), "Chess"); // Create the window

            if (!backgroundTexture.loadFromFile("startscreen.png")) { // Load the background texture
                cout << "Error loading background texture" << endl;
            }
            backgroundSprite.setTexture(backgroundTexture); // Set the background texture

            if (!endScreenTexture.loadFromFile("endscreen.png")) { // Load the end screen texture
                cout << "Error loading end screen texture" << endl;
            }
            endScreenSprite.setTexture(endScreenTexture); // Set the end screen texture

            if (!font.loadFromFile("arial.ttf")) { // Load the font
                cout << "Error loading font" << endl;
            }
            player1Text.setFont(font); // Set the font for player 1 text
            player1Text.setString("Player 1"); // Set the text for player 1
            player1Text.setCharacterSize(24); // Set the character size for player 1 text
            player1Text.setFillColor(sf::Color::White); // Set the color for player 1 text

            player2Text.setFont(font); // Set the font for player 2 text
            player2Text.setString("Player 2"); // Set the text for player 2
            player2Text.setCharacterSize(24); // Set the character size for player 2 text
            player2Text.setFillColor(sf::Color::White); // Set the color for player 2 text
        }
};