#include <iostream>
#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include "Game.h"
// #include "Strategy.h"

int main(){
    Game game;
    // Deck* deck;
    int nPlayers, deckCards;
    // Hand* hands;
    // Player* players;
    // Player* attacker, defender;
    // Player* fool = 0;
    // Suit trump;
    // Card* trumpCard;

    std::cout << "Input number of players:" << std::endl;
    std::cin >> nPlayers;
    for (int i = 0; i < nPlayers; i++) {
        std::string name;
        std::cout << "Print name of Player " << i + 1 << ". Print \"me/ \" before name if You play for him." << std::endl;
        std::cin >> name;
        game.addPlayer(name);
    }

    std::cout << "Ok, ";
    for (int i = 0; i < game.numPlayers; i++){
        std::cout << game.players[i]->getName() << ", ";
    }
    std::cout << "let's go!" << std::endl;

    game.DealAndSetFirstAttacker();


    while (not game.over()) {
        if (!game.firstAttack) {game.attacker = game.nextAttacker();} 
        game.defender = game.attacker->getNextPlayer();
        game.turn();
        if (!game.deck->empty()) game.drawCards();
    }

    std::cout << "Game over! ";
    if (game.hasFool()) {
        std::cout << game.fool->getName() << " is fool.";
    } else std::cout << "Draw.";
    std::cout << std::endl;

    return 0;
}