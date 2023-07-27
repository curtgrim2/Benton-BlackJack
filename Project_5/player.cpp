#include "player.h"


class Simple_Player : public Player {

	int Bet(unsigned int bankroll, unsigned int minimum) {
		return minimum;
	}

	bool Draw(Card dealer, const Hand& player) {

		if (!player.PresentHandValue().soft) {

			if (player.PresentHandValue().count <= 11) {
				return true;
			}

			if (player.PresentHandValue().count >= 17) {
				return false;
			}


			if (player.PresentHandValue().count == 12) {
				if (dealer.spot == FOUR || dealer.spot == FIVE || dealer.spot == SIX) {
					return false;
				}
				else {
					return true;
				}
			}

			if (player.PresentHandValue().count >= 13 && player.PresentHandValue().count <= 16) {

				if (dealer.spot >= TWO && dealer.spot <= SIX) {
					return false;
				}
				else {
					return true;
				}

			}

		}

		else {
			if (player.PresentHandValue().count <= 17) {
				return true;
			}
			if (player.PresentHandValue().count == 18) {
				if (dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT) {
					return false;
				}
				else {
					return true;
				}
			}

			if (player.PresentHandValue().count >= 19) {
				return false; // WAS TRUE
			}


		}
	}


	void Expose(Card c) {

	}

	void Shuffled() {

	}


};


class Counting_Player : public Simple_Player {

	int count = 0;

	int Bet(unsigned int bankroll, unsigned int minimum) {

		if (count >= 2) {

			if (minimum * 2 > bankroll) {
				return bankroll;
			}
			return minimum * 2;

		}

		else {
			return minimum;
		}
	}

	void Expose(Card c) {
		if (c.spot == TEN || c.spot == JACK || c.spot == QUEEN || c.spot == KING || c.spot == ACE) {
			count--;
		}

		if (c.spot == TWO || c.spot == THREE || c.spot == FOUR || c.spot == FIVE || c.spot == SIX) {
			count++;
		}
	}

	void Shuffled() { //FROM SPEC!!!
		count = 0;

	}
};


class Competitor : public Player {

	int count = 0;

	int Bet(unsigned int bankroll, unsigned int minimum) {
		return minimum;
	}
	bool Draw(Card dealer, const Hand& player) {

		if (!player.PresentHandValue().soft) {

			if (player.PresentHandValue().count <= 11) {
				return true;
			}

			if (player.PresentHandValue().count >= 17) {
				return false;
			}


			if (player.PresentHandValue().count == 12) {
				if (dealer.spot == 4 || dealer.spot == 5 || dealer.spot == 6) { //Written Values
					return false;
				}
				else {
					return true;
				}
			}

			if (player.PresentHandValue().count >= 13 && player.PresentHandValue().count <= 16) {

				if (dealer.spot >= 2 && dealer.spot <= 6) {
					return false;
				}
				else {
					return true;
				}

			}

		}

		else {
			if (player.PresentHandValue().count <= 17) {
				return true;
			}
			if (player.PresentHandValue().count == 18) {
				if (dealer.spot == 2 || dealer.spot == 7 || dealer.spot == 8) {
					return false;
				}
				else {
					return true;
				}
			}

			if (player.PresentHandValue().count >= 19) {
				return true;
			}


		}

	}

	void Expose(Card c) {
		if (c.spot == TEN || c.spot == JACK || c.spot == QUEEN || c.spot == KING || c.spot == ACE) {
			count--;
		}

		if (c.spot == TWO || c.spot == THREE){ 
			count+=2;
		}

		if ( c.spot == FOUR || c.spot == FIVE || c.spot == SIX) {		
			count ++;
		}

	}

	void Shuffled() {
		count = 0;
	}
};


Player* GetSimple() {
	return new Simple_Player();
}
// EFFECTS: returns a pointer to a "simple player", as defined by the
// project specification
Player* GetCounting() {

	return new Counting_Player();

}
// EFFECTS: returns a pointer to a "counting player", as defined by
// the project specification.
Player* GetCompetitor() {

	return new Competitor();

}