#include "Player.h"

//Creates the player
Player::Player(int money) {
	this->money = money;
	this->score = 0;
	this->ace = false;

}

//Add points to the player
bool Player::addScore(int score) {

	if (score == 1) {

		if (ace == false && this->score <= 10){
			this->score += 11;
			this->ace = true;
		}
		else{
			this->score += 1;
		}

	}
	else {

		//Sum the score
		this->score += score;
	}

	//Test if the ...
	if (this->getScore() > 21){

		if (this->ace == true){

			this->addScore(-10);
			this->ace = false;

		}

	}

	//Return true if the player score is higher than 21
	return this->getScore() > 21;

}

//Get the player score
int Player::getScore() {
	return this->score;
}

//Get the player money
int Player::getMoney() {
	return this->money;
}

//Debit money for the loser
void Player::debit(int money) {
	this->money -= money;
}

//Credit money for winner
void Player::credit(int money) {
	this->money += money;
}

//Reset the score to next match
void Player::reset() {
	this->score = 0;
}

Player::~Player() {
}

