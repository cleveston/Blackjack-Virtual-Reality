#ifndef DECK_H
#define	DECK_H

#include <time.h>
#include <stdlib.h>

class Card;

using namespace std;

class Deck {
public:
    Deck();
    Card* getCard();
    virtual ~Deck();
private:
    Card* cards[48];

};

#endif

