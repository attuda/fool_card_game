#include "Player.h"

Player::Player (const std::string& name, bool isComp) {
    this->name = name;
    this->comp = isComp;
    this->nextPlayer = NULL;
    this->hand = new Hand();
}

Player::~Player() {
    nextPlayer = NULL;
    delete nextPlayer;
    delete hand;
}

Player* Player::nextPitcher(Player* defender) {
    if (this->nextPlayer == defender) {return defender->getNextPlayer();}
    return this->nextPlayer;
}