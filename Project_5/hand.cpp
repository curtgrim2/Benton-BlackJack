#include "card.h"
#include "hand.h"

Hand::Hand() {
	// EFFECTS: establishes an empty blackjack hand.

	curValue.count = 0;
	curValue.soft = false;

	//HOW DOES HAND RELATE TO PLAYER?
}

// EFFECTS: establishes an empty blackjack hand.

void Hand::DiscardAll() {
	curValue.count = 0;
	curValue.soft = false;
}
// MODIFIES: this
// EFFECTS: discards any cards presently held, restoring the state
// of the hand to that of an empty blackjack hand.


void Hand::AddCard(Card c) {

	switch (c.spot) {
	case TWO: //Going through each possible card scenario / case
		curValue.count += 2;
		break;
	case THREE:
		curValue.count += 3;
		break;
	case FOUR:
		curValue.count += 4;
		break;
	case FIVE:
		curValue.count += 5;
		break;
	case SIX:
		curValue.count += 6;
		break;
	case SEVEN:
		curValue.count += 7;
		break;
	case EIGHT:
		curValue.count += 8;
		break;
	case NINE:
		curValue.count += 9;
		break;
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		curValue.count += 10;	
		break;

	case ACE:
		if (curValue.soft ){//&& curValue.count+11> curValue.count + 1) {
			curValue.count += 1;	//ACE logic could be wrong/ 11 or 1 based on the benefit of the player
			//curValue.soft = false;
			//break;
		}

		else {
			curValue.count += 11;	//ACE logic could be wrong/ 11 or 1 based on the benefit of the player
			curValue.soft = true;
			//break;

		}
	}

	if (curValue.count>21) {
		if (curValue.soft) {
			curValue.count -= 10;
			curValue.soft = false;
		}
	}
	// MODIFIES: this
	// EFFECTS: adds the card "c" to those presently held.
}

HandValue Hand::PresentHandValue() const {
	return curValue;
}
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