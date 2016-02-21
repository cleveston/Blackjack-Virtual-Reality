
#include "Card.h"

Card::Card(int value) {

    this->value = value;

    this->status = AVAILABLE;

}

//Get the card value
int Card::getValue() {
    return this->value;
}

//Set the card status to used
void Card::setUsed() {
    this->status = USED;
}

//Get the card status
bool Card::getStatus() {
    return this->status;
}

Card::~Card() {
}

