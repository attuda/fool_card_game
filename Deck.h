#ifndef DECK_H
#define DECK_H

#include <iostream>     // std::cout, std::cin
#include <algorithm>    // std::random_shuffle, std::sort
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "CardSet.h"


class Deck : public CardSet {
    // protected:
    //     std::vector<Card*> cards;
    //     bool sorted;
    //     int nCards;


    public:

        Deck(bool isShuffle = false);
        // ~Deck();
        // Card* pop();
        // void shuffle();
        // void sort();
        // int getNumCards() const {return nCards;}
        // bool isSorted() const { return sorted;}
        // bool empty() const {return (nCards == 0);}
        // Card* operator[] (int i) const { return cards[i];}
        Card* trumpCard() const {if (nCards == 0) return 0; else return cards[0];}
        bool deal (int nPlayers, std::vector<CardSet*>& hands);
        // static bool compare(Card* i, Card* j) {return (i->getNumber() < j->getNumber());}

        
};

// std::ostream& operator<<(std::ostream& out, const Deck& deck);

#endif // DECK_H
