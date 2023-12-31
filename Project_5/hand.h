#ifndef _HAND_H__
#define _HAND_H__
#include "card.h"
struct HandValue {
	int count; // Value of hand
	bool soft; // true if hand value is a soft count
};
class Hand {
	// OVERVIEW: A blackjack hand of zero or more cards
	// Note: this really is the only private state you need!

	HandValue curValue;
public:
	Hand();
	// EFFECTS: establishes an empty blackjack hand.
	void DiscardAll();
	// MODIFIES: this
	// EFFECTS: discards any cards presently held, restoring the state
	// of the hand to that of an empty blackjack hand.
	void AddCard(Card c);
	// MODIFIES: this
	// EFFECTS: adds the card "c" to those presently held.
	HandValue PresentHandValue() const;
	// EFFECTS: returns the present value of the blackjack hand. The
	// count field is the highest blackjack total possible without
	// going over 21. The soft field should be true if and only if at
	// least one ACE is present, and its value is counted as 11 rather
	// than 1.
	//
	// Note: the const qualifier at the end of handValue means that
	// you are not allowed to change any member variables inside
	// handValue. It is required because Players only get const Hands
	// passed to them, and therefore can only call methods gauranteed

		// not to change the hand.
};

#endif