#include "Player.h"

Player::Player(const std::string& playerName, Strategy strat)
    : name(playerName), strategy(strat), wins(0), losses(0), ties(0) {}

int Player::getMove(const ConnectFour& game, char symbol) const {
    return strategy(game, symbol);
}

std::string Player::getName() const {
    return name;
}

int Player::getWins() const {
    return wins;
}

int Player::getLosses() const {
    return losses;
}

int Player::getTies() const {
    return ties;
}

void Player::recordWin() {
    wins++;
}

void Player::recordLoss() {
    losses++;
}

void Player::recordTie() {
    ties++;
}

void Player::resetStats() {
    wins = 0;
    losses = 0;
    ties = 0;
}
