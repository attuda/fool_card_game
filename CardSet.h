#ifndef CARDSET_H
#define CARDSET_H

#include <iostream>     // std::cout, std::cin
#include <algorithm>    // std::random_shuffle, std::sort
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "Card.h"

class CardSet {
    protected:
        std::vector<Card*> cards;
        bool sorted;
        int nCards;


    public:

        CardSet();
        ~CardSet();
        Card* pop();
        bool pop(Card* card, CardSet* destination);
        int popN(int n);
        int popN(int n, CardSet* destination);
        void popAll(CardSet* destination);
        void take(Card* card);
        bool take(Card* card, CardSet* source);
        bool takeN(int n, CardSet* source);
        bool containCard(Card& card);
        void shuffle();
        void sort();
        void sortByStrength(Suit trump);
        int getNumCards() const {return nCards;}
        bool isSorted() const { return sorted;}
        bool empty() const {return (nCards == 0);}
        Card* operator[] (int i) const { return cards[i];}
        void show(bool sortB4 = false);
        static bool compare(Card* i, Card* j) {return (i->getNumber() < j->getNumber());}
        struct compareByStrength {
            compareByStrength (Suit trump) {this->trump = trump;}
            bool operator() (Card* i, Card* j) {return (i->strength(trump) < j->strength(trump));}
            Suit trump;
        };
        

        
};

std::ostream& operator<<(std::ostream& out, const CardSet& deck);

#endif // CARDSET_H
