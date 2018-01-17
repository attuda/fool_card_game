#ifndef CARD_H
#define CARD_H

#include <iostream>
//#include "../States/State.h"

enum Suit {diamonds, hearts, clovers, pikes};

class Card {
    protected:
        int rank;
        Suit suit;
        int number;

    public:
        Card(int rank, Suit suit, int number);
        ~Card();

        int strength(Suit trump) const;
        bool beat(Card* card, Suit trump) const;
        Suit getSuit() const;
        char getSuitChar() const;
        int getRank() const;
        int getNumber() const;
        bool operator==(Card& another) const {return (this->rank == another.getRank() && this->suit == another.getSuit());}
        // bool operator<(Card* another) const {return (this->getNumber() < another->getNumber());}
};

std::ostream& operator<<(std::ostream& out, const Card& card);
std::ostream& operator<<(std::ostream& out, Suit suit);

#endif // CARD_H
