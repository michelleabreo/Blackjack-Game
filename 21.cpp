// blackjack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>
#include <random>
#include "card.h"
#define cardmax 5

//11 is Jack
//12 is Queen
//13 is King
//ace is either 1 or 11

void populateDeck(card deck[])
{
	for (int i = 0; i < 9; i++)
	{
		deck[i + 1].setSuit("Clubs");
		deck[i + 1].setVal(i + 2);
		deck[8 + 2 + i].setSuit("Spades");
		deck[8 + 2 + i].setVal(i + 2);
		deck[16 + 3 + i].setSuit("Hearts");
		deck[16 + 3 + i].setVal(i + 2);
		deck[24 + 4 + i].setSuit("Diamonds");
		deck[24 + 4 + i].setVal(i + 2);
	}
	deck[0].setSuit("Ace of Clubs");
	deck[0].setVal(11);
	deck[37].setSuit("Ace of Spades");
	deck[37].setVal(11);
	deck[38].setSuit("Ace of Hearts");
	deck[38].setVal(11);
	deck[39].setSuit("Ace of Diamonds");
	deck[39].setVal(11);
	deck[40].setSuit("Jack of Clubs");
	deck[41].setSuit("Queen of Clubs");
	deck[42].setSuit("King of Clubs");
	deck[43].setSuit("Jack of Spades");
	deck[44].setSuit("Queen of Spades");
	deck[45].setSuit("King of Spades");
	deck[46].setSuit("Jack of Hearts");
	deck[47].setSuit("Queen of Hearts");
	deck[48].setSuit("King of Hearts");
	deck[49].setSuit("Jack of Diamonds");
	deck[50].setSuit("Queen of Diamonds");
	deck[51].setSuit("King of Diamonds");

	for (int i = 40; i < 52; i++)
	{
		deck[i].setVal(10);
	}

}

void printDeck(card deck[])
{
	for (int i = 0; i < 52; i++)
	{
		std::cout << deck[i].getSuit() << "\t" << deck[i].getVal() << "\n";
	}
}

int getRandNum(int cardsRem)
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, cardsRem); // guaranteed unbiased

	auto random_integer = uni(rng);
	return random_integer;
}

card getCard(card deck[])
{
	int position = getRandNum(52);

	while (deck[position].getVal() == 0)
	{
		position = getRandNum(52);
	}

	card temp = deck[position];
	deck[position].setSuit("");
	deck[position].setVal(0);
	return temp;
}

void dealRound(card deck[52], int& cardsRem, card dealer[], card player[])
{
	//int cardsRem = 52;

	player[0] = getCard(deck);
	cardsRem--;
	dealer[0] = getCard(deck);
	cardsRem--;

	std::cout << "dealer: " << dealer[0].getSuit() << "\t" << dealer[0].getVal() << "\n\n";
	std::cout << "player: " << player[0].getSuit() << "\t" << player[0].getVal() << std::endl;

}

void hitMe(card deck[52], card person[])
{

	int i;

	for (i = 0; i < cardmax; i++)
	{
		if (person[i].getVal() == 0)
		{
			person[i] = getCard(deck);
			break;
		}
				
	}

	//std::cout << "dealer: " << dealer[0].getSuit() << "\t" << dealer[0].getVal() << std::endl;

}

int cardSum(card person[])
{
	int sum = 0;
	for (int i = 0; i < cardmax; i++)
	{
		sum += person[i].getVal();
	}
	return sum;
}

void viewHand(card player[])
{
	int times = 0;
	while (player[times].getVal() != 0 && times <5)
	{
		std::cout << player[times].getSuit() << "\t" << player[times].getVal() << std::endl;
		times++;
	}
	std::cout << "Sum of card values: ";
	std::cout << cardSum(player) << "\n\n";
}


void changeAce(card player[])
{
	for (int i = 0; i < 5; i++)
	{
		if (player[i].getVal() == 1)
		{
			player[i].setVal(11);
			break;
		}
		else
		{
			player[i].setVal(1);
			break;
		}
	}
	std::cout << "\nAce value changed!\n\n";
	viewHand(player);
}

bool findAce(card person[])
{
	int i = 0;
	while (person[i].getVal() != 0 && i < 5)
	{
		if (person[i].getVal() == 11)
		{
			return true;
		}
		i++;
	}
	return false;
}

int main()
{
	char playAgain = 'y';
	while (playAgain == 'y')
	{
		
		int cardsRem = 52;
		card deck[52];
		card player[cardmax];
		card dealer[cardmax];

		populateDeck(deck);
	
		std::cout << "Let's play Blackjack!\n\n\n";

		std::cout << "Round 1 cards:\n";
		//1st card to everyone
		dealRound(deck, cardsRem, dealer, player);

		//2nd card to everyone
		hitMe(deck,player);
		std::cout << "player: " << player[1].getSuit() << "\t" << player[1].getVal() << std::endl;
		hitMe(deck, dealer);

		if (cardSum(player) == 21)
		{
			std::cout << "Blackjack!\n";
		}

		char choice = 'y';
		int times = 1;
		std::string possibleChoices = "yavn";
		//next possible hit
		while ((possibleChoices.find(choice) != std::string::npos) && cardSum(player) < 21)
		{

			std::cout << "\nWould you like a hit? (y or n)\n";
			std::cout << "If you would like to change the value of an ace, type \"a\""
				<< "\nType \"v\" to view your hand\n";
			std::cin >> choice;

			if (choice == 'y')
			{
				times++;
				hitMe(deck, player);
				std::cout << "player: " << player[times].getSuit() << "\t" << player[times].getVal() << std::endl;
			}

			if (choice == 'a')
			{
				changeAce(player);
			} 

			if (choice == 'v')
			{
				viewHand(player);
			}

			if (cardSum(player) == 21)
			{
				std::cout << "Blackjack!\n";
				break;
			}

			if (player[4].getVal() > 0)
			{
				std::cout << "You have 5 cards!\n";
				break;
			}

			if (cardSum(player) > 21)
			{
				if (findAce(player))
				{
					changeAce(player);
				}
				else
				{
					std::cout << "Sorry, you bust!\n";
				}
			}
			if (possibleChoices.find(choice) == std::string::npos)
			{
				std::cout << "Invalid letter choice.\n";
			}
			if (choice == 'n')
			{
				break;
			}

		}
						 
		//dealer goes
		while (cardSum(dealer) < 16)
		{
			std::cout << "\ndealer hits!\n";
			hitMe(deck, dealer);
			//viewHand(dealer);
			if (cardSum(dealer) > 21 && findAce(dealer))
			{
			changeAce(dealer);
			}
			else if (cardSum(dealer) > 21)
			{
				std::cout << "\nDealer busts!\n";
			}
			
		}
		
		std::cout << "\n\nDealer's hand:\n";
		viewHand(dealer);
		std::cout << "Players's hand:\n";
		viewHand(player);

		int dealerDiff = 21 - cardSum(dealer);
		int playerDiff = 21 - cardSum(player);
		//std::cout << dealerDiff << "\t" << playerDiff;


		if (playerDiff == dealerDiff && playerDiff > 0 && dealerDiff > 0)
		{
			std::cout << "\nDealer wins! Play Again (y or n)?";
		}
		else if ((playerDiff > dealerDiff && dealerDiff >= 0) || playerDiff < 0)
		{
			std::cout << "\nDealer wins! Play Again (y or n)?";
		}
		else 
		{
			std::cout << "\nCongratulations, you won! Play Again (y or n)?";
		}

		std::cin >> playAgain;
		system("cls");
	}
	return 0;
}

