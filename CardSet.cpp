#include "CardSet.h"
#include <iomanip>
//#include <algorithm>


CardSet::CardSet() {
    sorted = false;
    nCards = 0;
}

CardSet::~CardSet() {
    for (int i = 0; i < nCards; i++){
        delete cards[i];
    }
}

void CardSet::shuffle() {
    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle(cards.begin(), cards.end());
    sorted = false;
}

void CardSet::sort() {
    std::sort(cards.begin(), cards.end(), CardSet::compare);
    sorted = true;
}

void CardSet::sortByStrength(Suit trump) {
    std::sort(cards.begin(), cards.end(), CardSet::compareByStrength(trump));
    sorted = false;
}

Card* CardSet::pop() {
    if (empty()) return 0;
    Card* toPop = cards[nCards-1];
    cards.pop_back();
    nCards -= 1;
    return toPop;
}

bool CardSet::pop(Card* card, CardSet* destination) {
    for (int i = 0; i < nCards; i++) {
        if (cards[i] == card) {
            cards[i] = cards[nCards-1];
            sorted = false;
            destination -> take(card);
            cards.pop_back();
            nCards -= 1;
            return true;
        }
    }
    return false;   
}


void CardSet::take(Card* card) {
    cards.push_back(card);
    nCards += 1;
    sorted = false;
}

void CardSet::popAll(CardSet* destination) {
    int n = this->nCards;
    destination->takeN(n, this);
}

bool CardSet::take(Card* card, CardSet* source) {

}

bool CardSet::takeN(int n, CardSet* source) {
    int i = 0;
    for (; (!source->empty()) && (i < n); i++) {
        this->take(source->pop());
    }
    if (i == n) return true; else return false;
}

bool CardSet::containCard(Card& card) {
    for (int i = 0; i < nCards; i++){
        if (*cards[i] == card) return true;
    }
    return false;
}

void CardSet::show(bool sortB4) {
    if (!sorted && sortB4) sort();
    for (int i = 1; i <= nCards; i++) {
        std::cout << std::setw(4) << std::left << i;
        if (sorted && i < nCards && cards[i-1]->getSuit() != cards[i]->getSuit()) std::cout << "  ";
    }
    std::cout << std::endl;
    for (int i = 0; i < nCards; i++) {
        if (sorted && i > 0 && cards[i-1]->getSuit() != cards[i]->getSuit()) std::cout << "  ";
        std::cout << std::setw(4) << std::left << *(cards[i]);
    }
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& out, const CardSet& deck) {
    for (int i = 0; i < deck.getNumCards(); i++) {
        out << *(deck[i]) << " ";
    }
    return out;
}