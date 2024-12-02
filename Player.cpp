#include "Player.h"

Player::Player(bool isWhite): isWhite(isWhite) {}

bool Player::getIsWhite() const {
    return isWhite;
}