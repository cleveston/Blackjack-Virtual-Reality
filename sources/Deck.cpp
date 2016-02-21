#include "Deck.h"
#include "Card.h"

Deck::Deck() {

	//Create 9 types of cards
    for (int i = 0; i < 9; i++) {

		//Create 4 cards of each type
        for (int j = 0; j < 4; j++) {

			//Create the new card
            Card *c = new Card(i + 1);

			//Add the card to the deck
            this->cards[i * 4 + j] = c;
        }
    }

	//Create the rest of the cards
    for (int i = 36; i < 48; i++) {

		//Create the new card
        Card *c = new Card(10);

		//Add the card to the deck
        this->cards[i] = c;

    }
}

//Get some card from the deck
Card* Deck::getCard() {

    //Initialize the sead
    srand(time(NULL));

    Card *card;

    while (1) {

        //Pick up some card
        int position = rand() % 48;

        //Get the card
        card = this->cards[position];

        //Check if the card is available
        if (card->getStatus()) {
            card->setUsed();
            break;
        }

    }

    return card;

}

Deck::~Deck() {
}

