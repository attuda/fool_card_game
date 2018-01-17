#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Hand.h"
#include "Deck.h"

class Player {
    protected:
        std::string name;
        bool comp;
        Player* nextPlayer;

    public:
        
        Hand* hand;

        Player(const std::string& name, bool isComp);
        ~Player();
        // bool restore6(Deck* deck) {return hand->restore6(deck);}
        const std::string getName() const {return name;}
        bool isComp() const {return comp;}
        bool isHuman() const {return !comp;}
        int getNumCards() const {return this->hand->getNumCards();}
        bool restore6(Deck* deck) {return this->hand->restore6(deck);}
        Player* getNextPlayer() const {return nextPlayer;}
        void setNextPlayer(Player* player) {nextPlayer = player;}
        void printHand() const {hand->show(true);}
        Player* nextPitcher(Player* defender);

        
};

std::ostream& operator<<(std::ostream& out, const Player& player);

#endif // PLAYER_H
