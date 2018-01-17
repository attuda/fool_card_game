#include "Deck.h"
//#include <algorithm>


Deck::Deck (bool isShuffle) {
    int i = 0; 

    for (int j = diamonds; j <= pikes; j++){
        for (int k = 6; k < 15; k++ ) {
            Card* card = new Card(k, (Suit)j, i);
            cards.push_back(card);
            i += 1;
        }
    }
    nCards = i;
    if (isShuffle) {
        std::srand ( unsigned ( std::time(0) ) );
        std::random_shuffle(cards.begin(), cards.end());
        sorted = false;
    } else {
        sorted = true;
    }
}

bool Deck::deal(int nPlayers, std::vector<CardSet*>& hands) {
    for (int i = 0; i < nPlayers; i++) {
        if (!hands[i]->takeN(6, this)) return false;
    }
    return true;
}

// Deck::~Deck() {
//     for (int i = 0; i < nCards; i++){
//         delete cards[i];
//     }
// }

// void Deck::shuffle() {
//     std::srand ( unsigned ( std::time(0) ) );
//     std::random_shuffle(cards.begin(), cards.end());
//     sorted = false;
// }

// void Deck::sort() {
//     std::sort(cards.begin(), cards.end(), Deck::compare);
//     sorted = true;
// }

// Card* Deck::pop() {
//     if (empty()) return 0;
//     Card* toPop = cards[nCards-1];
//     cards.pop_back();
//     nCards -= 1;
//     return toPop;
// }

// std::ostream& operator<<(std::ostream& out, const Deck& deck) {
//     for (int i = 0; i < deck.getNumCards(); i++) {
//         out << *(deck[i]) << " ";
//     }
//     return out;
// }