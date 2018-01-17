#include "Card.h"
#include <string>
#include <sstream>

Card::Card(int rank, Suit suit, int number) {
    this->rank = rank;
    this->suit = suit;
    this->number = number;
}

Card::~Card() {}

int Card::strength(Suit trump) const {
    if (this->suit == trump) return this->rank + 9;
    return this->rank;
}
bool Card::beat(Card* card, Suit trump) const {
    if (this->suit == card->getSuit()) return this->rank > card->getRank();
    if (this->suit == trump) return this->strength(trump) > card->strength(trump);
    return false;
}
Suit Card::getSuit() const {
    return this->suit; 
}
char Card::getSuitChar() const {
    if (suit == diamonds) return 4; 
    if (suit == hearts) return 3; 
    if (suit == clovers) return 5; 
    if (suit == pikes) return 6; 
}
int Card::getRank() const {
    return this->rank; 
}
int Card::getNumber() const {
    return this->number; 
}

std::ostream& operator<<(std::ostream& out, const Card& card) {
    char humanRank;
    int numRank = card.getRank();
    std::stringstream strCard;
    // if (numRank == 10) humanRank = 'X';
    if (numRank == 11) humanRank = 'J';
    if (numRank == 12) humanRank = 'Q';
    if (numRank == 13) humanRank = 'K';
    if (numRank == 14) humanRank = 'A';
    strCard << card.getSuitChar();
    if (numRank > 10) {
        strCard << humanRank;
    } else {
        strCard << numRank;
    }
    out << strCard.str();
    // out << card.getSuitChar() << card.getRank();
    return out;
}

std::ostream& operator<<(std::ostream& out, Suit suit) {
    char suitChar;
    std::string suitString;
    if (suit == diamonds) {
        suitChar = 4; 
        suitString = "diamonds";
    } 
    if (suit == hearts) {
        suitChar = 3; 
        suitString = "hearts";
    }
    if (suit == clovers) {
        suitChar = 5; 
        suitString = "clovers";
    }
    if (suit == pikes) {
        suitChar = 6; 
        suitString = "pikes";
    }
    out << suitChar << " (" << suitString << ")";
    return out;
}
