#include "Game.h"
#include "CopyCardSet.h"
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

Game::Game() {
    this->numPlayers = 0;
    this->fool = NULL;
    this->attacker = NULL;
    this->defender = NULL;
    this->pickedUp = NULL;
    // this->pickedUp = 0;
    deck = new Deck();
    table = new CardSet();
    discard = new CardSet();
}


Game::~Game() {
    for (int i = 0; i < numPlayers; i++){
        delete players[i];
    }
    delete deck;
    delete table;
    delete discard;
}
void Game::DealAndSetFirstAttacker() {
    // int last = numPlayers-1;
    // players[last]->setNextPlayer(players[0]);
    // for (int i = 0; i < last; i++){
    //     players[i]->setNextPlayer(players[i+1]);
    // }
    playersInGame = numPlayers;
    attacker = 0;
    while (!attacker){
        deck->shuffle();
        std::cout << "Deck shuffled." << std::endl;
        if (deal()) {std::cout << "Card are in your hands." << std::endl;} else {std::cout << "It is problem with deal." << std::endl;}
        // deckCards = 36 - nPlayers * 6;
        trumpCard = deck->trumpCard();
        std::cout << "Trump card is " << *trumpCard << std::endl;
        trump = trumpCard->getSuit();
        attacker = firstAttacker();
        firstAttack = true;
    }
    // defender = attacker->getNextPlayer();
}

void Game::addPlayer(std::string& name) {
    bool isComp = true;
    trim(name);
    if (name.find("me/") == 0) {
        isComp = false;
        name = name.substr(3);
        ltrim(name);
    }
    Player* player = new Player(name, isComp);
    players.push_back(player);
    numPlayers +=1;
}

bool Game::deal() {
    for (int i = 0; i < playersInGame; i++) {
        if (!players[i]->restore6(deck)) return false;
    }
    return true;
}

Player* Game::firstAttacker() {
    for (int i = 6; i < 15; i++) {
        Card* card = new Card(i, trump, 0);
        for (int j = 0; j < numPlayers; j++){
            if (players[j]->hand->containCard(*card)) return players[j];
        }
    }
    return 0;
}

void Game::turn() {
    Card* attCard = 0;
    bool turnOver = false;
    pickUp = false;
    Player* pitcher = attacker;
    pickedUp = 0;
    int passes = 0;
    bool pass = false;
    int cardsToBeat;
    int pitchedCards;

    std::cout << std::endl << std::endl;
    std::cout << attacker->getName() << ", your move! Defender is " << defender->getName() << std::endl;
    if (firstAttack) {
        cardsToBeat = 5;
        std::cout << "First attack. 5 cards to be beaten." << std::endl;
        firstAttack = false;
        } else {
            cardsToBeat = defender->hand->getNumCards();
            if (cardsToBeat > 6) cardsToBeat = 6;
        }
    if (deck->empty()) {
        std::cout << "Deck is empty!" << std::endl << "Trump is " << trump << std::endl << std::endl;
    } else {
        std::cout << "Trump is " << trump << std::endl << "Trump card is " << *trumpCard << std::endl << std::endl;
    }

    if (attacker->isComp()) {
        attCard = chooseAttCard();        
    } else {
        int n;
        std::cout << attacker->getName() << "! Choose attacking card (enter it`s number):" << std::endl;
        attacker->printHand();
        std::cin >> n;
        attCard = (*(attacker->hand))[n-1];
        std::cout << std::endl;
    }
    std::cout << attacker->getName() << " attacking: " << *attCard << std::endl;
    attacker->hand->pop(attCard, table);
    pitchedCards = 1;

    while (!turnOver) {
        Card* defCard = 0;

        if (!pickUp && !pass) {
            passes = 0;
            if (defender->isComp()) {
                defCard = chooseDefCard(attCard);
                if (!defCard) {
                    pickUp = true;
                }
            } else {
                while ((not defCard) && (not pickUp)) {
                    int n;
                    std::cout << pitchedCards - 1 << " cards was beaten. Maximum " << cardsToBeat - pitchedCards + 1 << " cards to beat" << std::endl;
                    std::cout << "Trump is " << trump << std::endl;
                    std::cout << "Cards on table: " << *table << std::endl;
                    std::cout << defender->getName() << "! Choose defending card (enter it`s number) or enter 0 to pick up cards:" << std::endl;
                    defender->printHand();
                    std::cin >> n;
                    if (n == 0) {
                        pickUp = true;
                    } else {
                        defCard = (*(defender->hand))[n-1];
                        if (not defCard->beat(attCard, trump)) {
                            std::cout << "Card " << *defCard << " can't beat " << *attCard << std::endl;
                            defCard = 0;
                        }
                    }
                    std::cout << std::endl;
                    
                }
            }
            if (defCard) {
                std::cout << "Card " << *attCard << " was beaten by " << defender->getName() << ": " << *defCard << std::endl;
                defender->hand->pop(defCard, table);
                // table->take(defCard);
                if (defender->hand->empty() || pitchedCards == cardsToBeat){
                    std::cout << "Congratulations, " << defender->getName() << "! You've beaten " << pitchedCards << " attacking cards." <<std::endl;
                    turnOver = true;
                    // discard->takeN(table->getNumCards(), table);
                    continue;
                } else pitcher = attacker;
                // passes = 0;
            } else {
                std::cout << "Picked up by " << defender->getName() << std::endl;
                pickedUp = defender;
            }
        }

        attCard = 0;
        pass = false;
        while (pitcher->hand->empty()){
            pass = true;
            passes += 1;
            if (passes == playersInGame - 1) {
                turnOver = true;
                break;
            }
            pitcher = pitcher->nextPitcher(defender);
        }
        if (pitchedCards == cardsToBeat) turnOver = true;
        if (!turnOver){
            if (pitcher->isComp()) {
                attCard = choosePitchCard(pitcher);
                if (attCard == 0) {
                    pass = true;
                    passes += 1;
                    pitcher = pitcher->nextPitcher(defender);
                }
            } else {
                while ((not attCard) && (not pass)){
                    int n;
                    std::cout << std::endl;
                    std::cout << "Trump is " << trump << std::endl;
                    std::cout << "Cards on table: " << *table << std::endl;
                    std::cout << pitcher->getName() << "! Choose card to pitch in (enter it`s number) or enter 0 to pass:" << std::endl;
                    pitcher->printHand();
                    std::cin >> n;
                    if (n == 0) {
                        pass = true;
                        passes += 1;
                        pitcher = pitcher->nextPitcher(defender);
                    } else {
                        attCard = (*(pitcher->hand))[n-1];
                        if (not correctPitch(attCard)) {
                            std::cout << "Card " << *attCard << " is not correct pitch." << std::endl;
                            attCard = 0;
                        }
                    }
                    std::cout << std::endl;
                }
            }
            if (attCard) {
                pitcher->hand->pop(attCard, table);
                std::cout << pitcher->getName() << " attacking: " << *attCard << std::endl;
                pitchedCards += 1;
            }
        }
        if (passes == playersInGame - 1) {
            if (!pickUp) std::cout << "Congratulations, " << defender->getName() << "! You've beaten " << pitchedCards << " attacking cards." <<std::endl;
            turnOver = true;
        }
    }
    std::cout << "TURN OVER" << std::endl;
    if (pickUp) {
        std::cout << defender->getName() << " pickedUp " << table->getNumCards() << " cards: " << *table << std::endl;
        defender->hand->takeN(table->getNumCards(), table);
    } else {
        std::cout << defender->getName()  << " successfully DEFENDED. Discard: " << *table << std::endl;
        discard->takeN(table->getNumCards(), table);
    }
    std::cout << std::endl;
}

bool Game::correctPitch(Card* card) const {
    for (int i = 0; i < table->getNumCards(); i++) {
        if (card->getRank() == (*table)[i]->getRank()) return true;
    }
    return false;
}

Card* Game::chooseAttCard() {

    //
    // std::cout << "... " << attacker->getName() << " thinking on attack..." << std::endl;
    attacker->hand->sortByStrength(trump);
    // std::cout << "... Variants: " << *(attacker->hand) << std::endl;
    return (*attacker->hand)[0];
}

Card* Game::chooseDefCard(Card* attCard) {
    // std::cout << "... " << defender->getName() << " thinking on defense..." << std::endl;
    // std::cout << "... His hand:" << *(defender->hand) << std::endl;
    CopyCardSet* defendCards = new CopyCardSet;
    // std::cout << "new CopyCardSet : ";
    for (int i = 0; i < defender->hand->getNumCards(); i++) {
        Card* card1 = (*(defender->hand))[i];
        if (card1->beat(attCard, trump))  {
            defendCards-> take(card1);
            // std::cout << *card1 << ", ";
        }
    }
    // std::cout << std::endl;
    if (defendCards->getNumCards() > 0) {
        defendCards->sortByStrength(trump);
        // std::cout << "... His variants:" << *defendCards << std::endl;
        Card* choice = (*defendCards)[0];
        // std::cout << "... His choice:" << *choice << std::endl; 
        return choice;
    } else return NULL;
}

Card* Game::choosePitchCard(Player* pitcher) {
    // std::cout << "... " << pitcher->getName() << " thinking on pitching..." << std::endl;
    // std::cout << "... His hand:" << *(pitcher->hand) << std::endl;
    CopyCardSet* pitchCards = new CopyCardSet;
    // std::cout << "new CopyCardSet : ";
    for (int i = 0; i < pitcher->hand->getNumCards(); i++) {
        Card* card1 = (*(pitcher->hand))[i];
        if (correctPitch(card1))  {
            pitchCards-> take(card1);
            // std::cout << *card1 << ", ";
        }
    }
    // std::cout << std::endl;
    if (pitchCards->getNumCards() > 0) {
        pitchCards->sortByStrength(trump);
        // std::cout << "... His variants:" << *pitchCards << std::endl;
        Card* choice = (*pitchCards)[0];
        // std::cout << "... His choice:" << *choice << std::endl; 
        if (pickUp && choice->getSuit() == trump) return NULL; else return choice;
    } else return NULL;
}


bool Game::drawCards() {
    if (attacker->restore6(deck)) {
        for (Player* pitcher = defender->getNextPlayer(); (pitcher != attacker) && (pitcher->restore6(deck)); pitcher = pitcher->getNextPlayer());
    }
    if (!deck->empty()) return defender->restore6(deck);
    return false;
}

bool Game::over() {
    int i, j;
    for (i = 0; players[i]->hand->empty() && i < numPlayers; i++) {
        std::cout << players[i]->getName() << " LEAVES THE GAME without cards in his hand." << std::endl;
    }
    if (i == numPlayers){
        //Draw.
        return true;
    } 
    playersInGame = 1;
    Player* first = players[i];
    std::cout << first->getName() << " is here with " << first->getNumCards() << " cards." << std::endl;
    for (j = i + 1; j < numPlayers; j++){
        if (!players[j]->hand->empty()) {
            playersInGame += 1;
            std::cout << players[j]->getName() << " is here with " << players[j]->getNumCards() << " cards." << std::endl;
            players[i]->setNextPlayer(players[j]);
            i = j;
        } else {
            std::cout << players[j]->getName() << " LEAVES THE GAME without cards in his hand." << std::endl;
        }
    }
    players[i]->setNextPlayer(first);
    if (first->getNextPlayer() == first) {
        //First is fool.
        fool = first;
        return true;
    }
    return false;
}

Player* Game::nextAttacker() {
    Player* pretendent = attacker->getNextPlayer();
    if (pretendent == pickedUp) pretendent = pickedUp->getNextPlayer();
    // pickedUp = 0;
    return pretendent;
}
// void updateNexts() {
//     // Player* xAttacker = attacker;
//     // for (Player* previous = attacker, Player* next = attacker->getNextPlayer(); )
//     int last = numPlayers - 1;
//     int i, j;
//     for (i = 0; i < last; i = j) {
//         if (players[i]->isInGame()) {
//             for(j = i + 1; j < numPlayers; j++) {
//                 if (players[j]->isInGame()) {
//                     players[i]->setNextPlayer(players[j]);
//                 }
//             }
//         } else j = i + 1;
//     }
// }