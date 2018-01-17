#ifndef GAME_H
#define GAME_H

#include <iostream>     // std::cout, std::cin
#include <algorithm>    // std::random_shuffle, std::sort
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <string>
#include "Card.h"
#include "CardSet.h"
#include "Player.h"
#include "Deck.h"
#include "Hand.h"
// #include "Strategy.h"


class Game {
    protected:
        

    public:
        Deck* deck;
        CardSet* discard;
        CardSet* table;
        int numPlayers;
        int playersInGame;
        std::vector<Hand*> hands;
        std::vector<Player*> players;
        Player* attacker;
        Player* defender;
        Player* pickedUp;
        Player* fool;
        Suit trump;
        Card* trumpCard;
        bool firstAttack;
        bool pickUp;

        Game();
        ~Game();

        // void init();
        void DealAndSetFirstAttacker();
        void addPlayer(std::string& name);
        Player* firstAttacker();
        Player* nextAttacker();
        bool deal();
        void turn();
        bool drawCards();
        // void updateNexts();
        bool over();
        bool hasFool() const {return (fool!=0);}
        bool correctPitch(Card* card) const;
        Card* chooseAttCard();
        Card* chooseDefCard(Card* attCard);
        Card* choosePitchCard(Player* pitcher);
};







#endif // GAME_H
