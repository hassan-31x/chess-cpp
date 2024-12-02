#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

class Board {
    private:
        Piece* squares[8][8];
        std::map<std::string, sf::Texture> images;

        void drawBoard(sf::RenderWindow& window);
        void drawPieces(sf::RenderWindow &window);

    public:
        static const int BOARD_SIZE = 8;
        static const int SQUARE_SIZE = 100;

        Board();
        
        ~Board();

        Piece* (*getSquares())[8];

        void draw(sf::RenderWindow& window);

        void loadImages();

        bool movePiece(int r1, int c1, int r2, int c2, std::vector<std::pair<int, int>> validMoves);

        Piece* getPiece(int r, int c);

        void highlightSquares(std::vector<std::pair<int, int>> moves, int r, int c, bool isWhite);
};
