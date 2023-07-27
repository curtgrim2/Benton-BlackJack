#pragma once
#ifndef _CARD_H__
#define _CARD_H__

enum Suit {
	SPADES, HEARTS, CLUBS, DIAMONDS
};
extern const char* SuitNames[DIAMONDS + 1];
enum Spot {
	TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
	JACK, QUEEN, KING, ACE
};
extern const char* SpotNames[ACE + 1];
struct Card {
	Spot spot;
	Suit suit;
};


#endif _CARD_H__