#ifndef CARD_H
#define	CARD_H

using namespace std;

//Define the card status
const bool AVAILABLE = true;
const bool USED = false;

class Card {
public:
    Card(int value);
    int getValue();
    void setUsed();
    bool getStatus();
    virtual ~Card();
private:
    int value;
    bool status;
};

#endif

