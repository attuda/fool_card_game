
#ifndef COPYCARDSET_H
#define COPYCARDSET_H

#include <iostream>     // std::cout, std::cin
#include <algorithm>    // std::random_shuffle, std::sort
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "Card.h"
#include "CardSet.h"

class CopyCardSet: public CardSet {


    public:
        // CopyCardSet(CardSet* source, bool (*condition)(Card*));
        ~CopyCardSet();

        

        
};

std::ostream& operator<<(std::ostream& out, const CardSet& deck);

#endif // COPYCARDSET_H
