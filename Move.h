#include <map>
#include <string>
#include "Piece.h"

class Move {
    private:
        // Maps for chess notation conversion
        static const std::map<std::string, int> ranksToRows;
        static const std::map<int, std::string> rowsToRanks;
        static const std::map<std::string, int> filesToCols;
        static const std::map<int, std::string> colsToFiles;

        int startRow;
        int startCol;
        int endRow;
        int endCol;
        Piece* pieceMoved;
        Piece* pieceCaptured;
        bool isPawnPromotion;
        int moveID;

        std::string getRankFile(int r, int c) const {
            return colsToFiles.at(c) + rowsToRanks.at(r);
        }

    public:
        Move(std::pair<int,int> startSq, std::pair<int,int> endSq, Piece* board[8][8]);

        bool operator == (const Move& other) const;

        std::ostream& operator << (std::ostream& os) const;
};

// Static member initialization
const std::map<std::string, int> Move::ranksToRows = {
    {"1", 7}, {"2", 6}, {"3", 5}, {"4", 4},
    {"5", 3}, {"6", 2}, {"7", 1}, {"8", 0}
};

const std::map<int, std::string> Move::rowsToRanks = {
    {7, "1"}, {6, "2"}, {5, "3"}, {4, "4"},
    {3, "5"}, {2, "6"}, {1, "7"}, {0, "8"}
};

const std::map<std::string, int> Move::filesToCols = {
    {"a", 0}, {"b", 1}, {"c", 2}, {"d", 3},
    {"e", 4}, {"f", 5}, {"g", 6}, {"h", 7}
};

const std::map<int, std::string> Move::colsToFiles = {
    {0, "a"}, {1, "b"}, {2, "c"}, {3, "d"},
    {4, "e"}, {5, "f"}, {6, "g"}, {7, "h"}
};
