#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* arcv[]) {

	int counter = 1;

	if (argc != 4) {

		cout << "Improper amount of arguments" << endl;
		return 0;

	}


	Deck deck_class;
	int bankroll = atoi(arcv[1]);
	int amount_hands = atoi(arcv[2]);
	string player_t = arcv[3];



	cout << "Shuffling the deck\n";

	for (int x = 0; x < 7; x++) {

		int cut = GetCut();
		deck_class.Shuffle(cut); 

		cout << "cut at " << cut << endl;
	}

	

	int hands = 1; // Round Counter (vs the argument where thats the max number of rounds)


	Player* player_obj = NULL;
	Card player, dealer;
	Hand players_cards, dealers_cards;


	//Determining player_t (player type) 

	if (player_t == "simple") {

		player_obj = GetSimple();
	}

	else if (player_t == "counting") {

		player_obj = GetCounting();
	}

	else if (player_t == "competitor") {

		player_obj = GetCompetitor();
	}

	else {
		return 0;
	}




	while (bankroll >= 5 && hands <= amount_hands) {
		players_cards.DiscardAll();
		dealers_cards.DiscardAll();

		cout << "Hand " << hands << " bankroll " << bankroll << endl;
		//Get hand value from hand.cpp

		if (deck_class.CardsLeft() < 20) {
			//If there are fewer than 20 cards left in the deck, reshuffle the deck 
			cout << "Shuffling the deck\n";
			for (int x = 0; x < 7; x++) {
				int cut = GetCut();
				deck_class.Shuffle(cut);  
				cout << "cut at " << cut << endl;

			}

			player_obj->Shuffled(); 
		}


		cout << "Player bets " << player_obj->Bet(bankroll, 5) << endl;

		int wager = player_obj->Bet(bankroll, 5);

		// NEXT STEP: Deal four cards
		player = deck_class.Deal(); 
		players_cards.AddCard(player);
		player_obj->Expose(player);
		cout << "Player dealt " << SpotNames[player.spot] << " of " << SuitNames[player.suit] << endl;

		dealer = deck_class.Deal();
		Card up = dealer;
		dealers_cards.AddCard(up);
		player_obj->Expose(dealer);
		cout << "Dealer dealt " << SpotNames[dealer.spot] << " of " << SuitNames[dealer.suit] << endl;

		player = deck_class.Deal();
		players_cards.AddCard(player);
		player_obj->Expose(player);
		cout << "Player dealt " << SpotNames[player.spot] << " of " << SuitNames[player.suit] << endl;

		dealer = deck_class.Deal();
		Card hole = dealer;
		dealers_cards.AddCard(dealer); //This card dealt is face down

		


		//NEW STEP: After checking if player got a natural 21, deal players cards until player (based on type) is satisfied

		if (players_cards.PresentHandValue().count == 21 && players_cards.PresentHandValue().soft == true) {

			bankroll = bankroll + (wager * 3) / 2;
			cout << "Player dealt natural 21 " << endl;

		}

		else {

			while (player_obj->Draw(up, players_cards) && players_cards.PresentHandValue().count <= 21) { 
				
				player = deck_class.Deal();
				player_obj->Expose(player);
				players_cards.AddCard(player);


				cout << "Player dealt " << SpotNames[player.spot] << " of " << SuitNames[player.suit] << endl;
			}

			cout << "Player's total is " << players_cards.PresentHandValue().count << endl;

			if (players_cards.PresentHandValue().count > 21) {//Won't need to go through dealer if player busts

				cout << "Player busts " << endl;

				bankroll = bankroll - wager;

			}



			// If player doesn't bust, then its dealers turn to go 


			else {

				player_obj->Expose(hole); 
				cout << "Dealer's hole card is " << SpotNames[dealer.spot] << " of " << SuitNames[dealer.suit] << endl;

		

				while (dealers_cards.PresentHandValue().count < 17) {

					
					dealer = deck_class.Deal();				
					dealers_cards.AddCard(dealer);
					player_obj->Expose(dealer);

					cout << "Dealer dealt " << SpotNames[dealer.spot] << " of " << SuitNames[dealer.suit] << endl;

				}  


				cout << "Dealer's total is " << dealers_cards.PresentHandValue().count << endl;
				if (dealers_cards.PresentHandValue().count >= 17 && dealers_cards.PresentHandValue().count <= 21) {

					if (dealers_cards.PresentHandValue().count > players_cards.PresentHandValue().count) {
						bankroll = bankroll - wager;
						cout << "Dealer wins" << endl;

					}

					else if (dealers_cards.PresentHandValue().count < players_cards.PresentHandValue().count) {

						bankroll = bankroll + wager;
						cout << "Player wins" << endl;
					}

					else if (dealers_cards.PresentHandValue().count == players_cards.PresentHandValue().count && dealers_cards.PresentHandValue().count == 21) {
						//totals are equal

						bankroll = bankroll + (wager * 3) / 2;
						cout << "Player wins" << endl; 

					}

					else { //totals are qual but do not equal 21
						cout << "Push" << endl;
					}

				}




				else if (dealers_cards.PresentHandValue().count > 21) {

					cout << "Dealer busts" << endl;
					bankroll = bankroll + wager; 

				}
				//end of dealers play (page 11)
			
			}

		}


	
		hands++;
	}

	cout << "Player has " << bankroll << " after " << hands - 1 << " hands" << endl;

	return 0;
}

