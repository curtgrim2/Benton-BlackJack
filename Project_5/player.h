#ifndef __PLAYER_H_
#define __PLAYER_H_
#include "hand.h"
#include "card.h"

class Player {
    // A virtual base class, providing the player interface
public:
    virtual int Bet(unsigned int bankroll,
        unsigned int minimum) = 0;
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll 
    // inclusive

    virtual bool Draw(Card dealer,             // Dealer's "up card"
        const Hand& player) = 0; // Player's current hand
// EFFECTS: returns true if the player wishes to be dealt another
// card, false otherwise.

    virtual void Expose(Card c) = 0;
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    // For example, each card that is dealt "face up" is expose()d.
    // Likewise, if the dealer must show his "hole card", it is also
    // expose()d.  Note: not all cards dealt are expose()d---if the
    // player goes over 21 or is dealt a natural 21, the dealer need
    // not expose his hole card.

    virtual void Shuffled() = 0;
    // EFFECTS: tells the player that the deck has been re-shuffled.

    virtual ~Player() { }
    // Note: this is here only to suppress a compiler warning.
    //       Destructors are not needed for this project.
};

extern Player* GetSimple();
// EFFECTS: returns a pointer to a "simple player", as defined by the
// project specification

extern Player* GetCounting();
// EFFECTS: returns a pointer to a "counting player", as defined by
// the project specification.

extern Player* GetCompetitor();
// EFFECTS: returns a pointer to a "competitor"---this player can do
// anything you want, as long as it adheres to the specification.

#endif /* __PLAYER_H__ */