#ifndef HAND_H
#define HAND_H

#include <iostream>     // std::cout, std::cin
#include <algorithm>    // std::random_shuffle, std::sort
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "Card.h"
#include "Deck.h"

class Hand: public CardSet {
    protected:
        // std::vector<Card*> cards;
        // bool sorted;
        // int nCards;

    public:
        

        // Hand();
        // ~Hand();
        // bool pop(Card* card);
        // void take(Card* card);
        // bool isSorted() const { return sorted;}
        // bool empty() const {return (nCards == 0);}
        // int getNumCards() const {return nCards;}
        // Card* operator[] (int i) const { return cards[i];}
        Card* minValue();
        // void sort();
        bool restore6(Deck* deck);
        void show(bool sortB4 = true);
        // static bool compare(Card* i, Card* j) {return (i->getNumber() < j->getNumber());}
 
};

// std::ostream& operator<<(std::ostream& out, Hand& unit);

#endif // HAND_H
