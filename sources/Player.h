
#ifndef PLAYER_H
#define	PLAYER_H

using namespace std;

class Player {
public:
    Player(int money);
    bool addScore(int score);
    int getScore();
    int getMoney();
    void debit(int money);
    void credit(int money);
    void reset();
    virtual ~Player();
private:
    int score;
    int money;
    bool ace;

};

#endif

