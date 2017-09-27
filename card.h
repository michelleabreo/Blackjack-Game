//card.h

//card.h

#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>


class card
{
private:

	std::string m_suit;
	int m_number;

public:
	card();
	//card(std::string suit, int number);
	void setSuit(std::string suit);
	std::string getSuit();
	void setVal(int number);
	int getVal();
	~card(){}

};


card::card()
{
	m_suit = "";
	m_number = 0;
}

/*card::card(std::string suit, int number)
{
m_suit = suit;
m_number = number;
}*/

void card::setSuit(std::string suit)
{
	m_suit = suit;
}

std::string card::getSuit()
{
	return m_suit;
}

void card::setVal(int number)
{
	m_number = number;
}

int card::getVal()
{
	return m_number;
}

