#include "Move.h"

Move::Move(std::pair<int,int> startSq, std::pair<int,int> endSq, Piece* board[8][8]) {
    startRow = startSq.first;
    startCol = startSq.second;
    endRow = endSq.first;
    endCol = endSq.second;
    pieceMoved = board[startRow][startCol];
    pieceCaptured = board[endRow][endCol];
    
    isPawnPromotion = false;
    if ((pieceMoved->getName() == "wp" && endRow == 0) || 
        (pieceMoved->getName() == "bp" && endRow == 7)) {
        isPawnPromotion = true;
    }
    
    moveID = startRow * 1000 + startCol * 100 + endRow * 10 + endCol;
}

bool Move::operator == (const Move& other) const {
    return moveID == other.moveID;
}

std::ostream& Move::operator << (std::ostream& os) const {
    os << getRankFile(startRow, startCol) + getRankFile(endRow, endCol);
    return os;
}