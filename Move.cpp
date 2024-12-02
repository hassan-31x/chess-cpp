#include <map>
#include <string>
#include "Piece.cpp" 
// Class definition for Move
class Move {
    private:
        // Static maps to convert between ranks/files and rows/columns
        static const std::map<std::string, int> ranksToRows;
        static const std::map<int, std::string> rowsToRanks;
        static const std::map<std::string, int> filesToCols;
        static const std::map<int, std::string> colsToFiles;

        int startRow; // Integer variable to store the starting row of the move
        int startCol; // Integer variable to store the starting column of the move
        int endRow; // Integer variable to store the ending row of the move
        int endCol; // Integer variable to store the ending column of the move
        Piece* pieceMoved; // Pointer to the piece that is being moved
        Piece* pieceCaptured; // Pointer to the piece that is being captured (if any)

        // Private function to get the rank and file notation for a given row and column
        std::string getRankFile(int r, int c) const {
            return colsToFiles.at(c) + rowsToRanks.at(r);
        }

    public:
        // Constructor to initialize the move with starting and ending squares and the board state
        Move(std::pair<int,int> startSq, std::pair<int,int> endSq, Piece* board[8][8]) {
            startRow = startSq.first; // Set the starting row
            startCol = startSq.second; // Set the starting column
            endRow = endSq.first; // Set the ending row
            endCol = endSq.second; // Set the ending column
            pieceMoved = board[startRow][startCol]; // Set the piece being moved
            pieceCaptured = board[endRow][endCol]; // Set the piece being captured (if any)
        }

        // Friend function to overload the << operator for printing the move
        friend std::ostream& operator<<(std::ostream& os, const Move& move) {
            os << move.getRankFile(move.startRow, move.startCol) + move.getRankFile(move.endRow, move.endCol);
            return os;
        }
};

// Static map definitions to convert between ranks/files and rows/columns
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