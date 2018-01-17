#include "Hand.h"
#include <iomanip>
//#include <algorithm>


// Hand::Hand () {
//     sorted = false;
//     nCards = 0;
// }

// Hand::~Hand() {
//     for (int i = 0; i < nCards; i++){
//         delete cards[i];
//     }
// }

// void Hand::shuffle() {
//     std::srand ( unsigned ( std::time(0) ) );
//     std::random_shuffle(cards.begin(), cards.end());
//     sorted = false;
// }

// void Hand::sort() {
//     std::sort(cards.begin(), cards.end(), Hand::compare);
//     sorted = true;
// }

// bool Hand::pop(Card* card) {
//     for (int i = 0; i < nCards; i++) {
//         if (cards[i] == card) {
//             cards[i] = cards[nCards-1];
//             sorted = false;
//             cards.pop_back();
//             nCards -= 1;
//             return true;
//         }
//     }
//     return false;   
// }

// void Hand::take(Card* card) {
//     cards.push_back(card);
//     nCards += 1;
//     sorted = false;
// }

bool Hand::restore6(Deck* deck) {
    while (!deck->empty() && nCards < 6) {
        take(deck->pop());
    }
    if (nCards >= 6) return true; else return false;
}

void Hand::show(bool sortB4) {
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