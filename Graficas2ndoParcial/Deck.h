//
//  Deck.h
//  BlackJack
//
//  Created by Ma. Guadalupe Roque on 21/07/14.
//  Copyright (c) 2014 Ma. Guadalupe Roque. All rights reserved.
//

#ifndef __BlackJack__Deck__
#define __BlackJack__Deck__

#include <iostream>
#include <string.h>
#include "Card.h"

using namespace std;

class Deck
{
public:
    // Constructor
    Deck();
    
    // Otros Metodos
    char getSuit(int k);
    char getValue(int k);
    void shuffle();
    Card dealCard();
    //char * str();
    
    
private:
    // Atributos
    vector<Card> d={
        Card('C','A'), Card('C','2'), Card('C','3'), Card('C','4'),Card('C','5'),
        Card('C','6'), Card('C','7'), Card('C','8'), Card('C','9'),Card('C','T'),
        Card('C','J'), Card('C','Q'), Card('C','K'), Card('S','A'),Card('S','2'),
        Card('S','3'), Card('S','4'), Card('S','5'), Card('S','6'),Card('S','7'),
        Card('S','8'), Card('S','9'), Card('S','T'), Card('S','J'),Card('S','Q'),
        Card('S','K'), Card('H','A'), Card('H','2'), Card('H','3'),Card('H','4'),
        Card('H','5'), Card('H','6'), Card('H','7'), Card('H','8'),Card('H','9'),
        Card('H','T'), Card('H','J'), Card('H','Q'), Card('H','K'),Card('D','A'),
        Card('D','2'), Card('D','3'), Card('D','4'), Card('D','5'),Card('D','6'),
        Card('D','7'), Card('D','8'), Card('D','9'), Card('D','T'),Card('D','J'),
        Card('D','Q'), Card('D','K')
    };
    
};

//Clubs (♣) Spades (♠), Hearts (♥), Diamonds (♦) //string SUITS ="CSHD";
//T-Tens J-jack , Q-queen, K-king
//string RANKS="A23456789TJQK";

Deck::Deck() {
    d={
        Card('C','A'), Card('C','2'), Card('C','3'), Card('C','4'),Card('C','5'),
        Card('C','6'), Card('C','7'), Card('C','8'), Card('C','9'),Card('C','T'),
        Card('C','J'), Card('C','Q'), Card('C','K'), Card('S','A'),Card('S','2'),
        Card('S','3'), Card('S','4'), Card('S','5'), Card('S','6'),Card('S','7'),
        Card('S','8'), Card('S','9'), Card('S','T'), Card('S','J'),Card('S','Q'),
        Card('S','K'), Card('H','A'), Card('H','2'), Card('H','3'),Card('H','4'),
        Card('H','5'), Card('H','6'), Card('H','7'), Card('H','8'),Card('H','9'),
        Card('H','T'), Card('H','J'), Card('H','Q'), Card('H','K'),Card('D','A'),
        Card('D','2'), Card('D','3'), Card('D','4'), Card('D','5'),Card('D','6'),
        Card('D','7'), Card('D','8'), Card('D','9'), Card('D','T'),Card('D','J'),
        Card('D','Q'), Card('D','K')
    };
}

char Deck::getSuit(int k) {
    return d[k].getSuit();
}

char Deck::getValue(int k) {
    return d[k].getValue();
}

int randomGen (int i) { return rand()%i;}

void Deck::shuffle() {
    
    random_shuffle(d.begin(), d.end(), randomGen);
    
    /*
     cout << "SHUFFLE vector contains: ";
     for (vector<int>::iterator it=num.begin(); it!=num.end(); ++it)
     cout << ' ' << *it;
     cout << endl; */
}

Card Deck::dealCard() {
    Card temp = d.front();
    d.erase(d.begin());
    
    return temp;
}

#endif /* defined(__BlackJack__Deck__) */
