#include "deck.h"
#include <iostream>




Deck::Deck()
{
	Card card;
	for (int i = 0; i < DeckSize; i++)
	{	
		card.spot = Spot(i % 13);
		card.suit = Suit(i / 13);
		
		deck[i] = card;
	}
	next = 0;
}

void Deck::Reset()
{
	Deck();
}

void Deck::Shuffle(int n)
{
	/*if (n==0 || n==52 || n==51) { // edge/special cases (Doesn't work)
		next = 0;
		return;
	}*/

	Deck temp;
	int r_count = 0;
	int l_count = 0;
	int i = 0;


	for ( i=0 ; i < DeckSize && l_count<n && n+ r_count<DeckSize; i++)
	{
		if (i % 2 == 0) // the right side
		{
			temp.deck[i] = deck[n + r_count];
			//temp.deck[i] = this->deck[n + count];
			r_count++;
		}
		else//left side
		{
			temp.deck[i] = deck[l_count];
			l_count++;
		}
	}

	if (l_count >= n) { // adding in any remaining cards
		
		//cout << "right: " << i << endl;

		for (i; n + r_count < DeckSize && i<DeckSize; i++) {

			temp.deck[i] = deck[n + r_count];
			r_count++;
		}
	}

	else {
		//cout << l_count << endl;

		//cout << "left: " << i << endl;
		for (i; l_count <= n && i < DeckSize; i++) {
			temp.deck[i] = deck[ l_count];
			l_count++;
		}

	}
	//cout << i;

	//cout << "R COUNT"<< r_count<<endl;
	//cout << "L COUNT" << l_count << endl;

	for (int i = 0; i < DeckSize; i++)
	{
		deck[i] = temp.deck[i];
		
	}

	next = 0;
}



Card Deck::Deal()
{
	DeckEmpty d_empty;
	//cout << "NEXT is "<< next << endl; //TESTING TESTING
	if (next == DeckSize)
	{
		//cout<<"xxx " <<endl;
		throw d_empty;
	}

	else {
		Card card;

		card.spot = deck[next].spot;
		card.suit = deck[next].suit;

		next = next + 1;
		return card;
	}
}

int Deck::CardsLeft()
{
		return DeckSize - next;
}