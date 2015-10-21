//
//  Hand.h
//  BlackJack
//
//  Created by Ma. Guadalupe Roque on 29/07/14.
//  Copyright (c) 2014 Ma. Guadalupe Roque. All rights reserved.
//

#ifndef __BlackJack__Hand__
#define __BlackJack__Hand__

#include <iostream>
#include "Card.h"
using namespace std;

class Hand
{
public:
    Hand();
    
    char getSuit(int k); //Retorna el suit de la carta
    char getValue(int k);//retorna el valor de la carta k de
    char * str(); //retorna en todas las cartas de la mano
    void addCard(Card card); //añade una carta a la mano de cartas
    int getSum();//retorna el valor total de puntos de la mano
    void draw(int y, int screenWidth, int screenHeight, int cardWidth, int cardHeight);//dibuja todas las cartas desde la posición x,y, dependiendo de la cantidad de cartas
    int getNumCards();
    
private:
    vector<Card> hand={
        Card('z','z'), Card('z','z'),
        Card('z','z'),Card('z','z'),
        Card('z','z'),Card('z','z'),
        Card('z','z'),Card('z','z'),
        Card('z','z'), Card('z','z')
    };
    int cont=0;  //cantidad de cartas de la mano
    
};

Hand::Hand()
{
    hand={
        Card('z','z'), Card('z','z'),
        Card('z','z'),Card('z','z'),
        Card('z','z'),Card('z','z'),
        Card('z','z'),Card('z','z'),
        Card('z','z'), Card('z','z')
    };
    cont = 0;
}

char Hand::getSuit(int k) {
    return hand[k].getSuit();
}

char Hand::getValue(int k) {
    return hand[k].getValue();
}

char * Hand::str() {
    char *c = NULL;
    for (int i = 0; i < cont; i++) {
        char aux = hand[i].getValue() + ',';
        strcat(c, &aux);
    }
    return c;
}

void Hand::addCard(Card card) {
    hand[cont] = card;
    cont++;
}

int Hand::getSum() {
    int sum = 0;
    int numA = 0;
    
    char value;
    for (int x = 0; x < cont; x++) {
        value = hand[x].getValue();
        if(value == 'A') {
            numA++;
        } else if (value == 'T' || value == 'J' || value == 'Q' || value == 'K') {
            sum += 10;
        } else {
            sum += (value - '0');
        }
        /*
         switch (hand[x].getValue()) {
         case 'A':
         numA++;
         break;
         case '2':
         sum += 2;
         break;
         case '3':
         sum += 3;
         break;
         case '4':
         sum += 4;
         break;
         case '5':
         sum += 5;
         break;
         case '6':
         sum += 6;
         break;
         case '7':
         sum += 7;
         break;
         case '8':
         sum += 8;
         break;
         case '9':
         sum += 9;
         break;
         case 'T':
         sum += 10;
         break;
         case 'J':
         sum += 10;
         break;
         case 'Q':
         sum += 10;
         break;
         case 'K':
         sum += 10;
         break;
         
         default:
         break;
         } */
    }
    
    while (numA > 0) {
        numA--;
        if ((sum + 11 + numA) <= 21) {
            sum += 11;
        } else {
            sum++;
        }
    }
    
    return sum;
}

int Hand::getNumCards() {
    return cont;
}

void drawCardNum(string text,int x,int y, float size, int screenWidth) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x, y, 2.0);
    float scale = size * ((float)screenWidth / (screenWidth * 2.0));
    glScalef(scale, -scale, 1.0);
    for (int c=0; c < text.length(); c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN , text[c]);
    }
    glPopMatrix();
}

void Hand::draw(int y, int screenWidth, int screenHeight, int cardWidth, int cardHeight) {
    double x1 = (screenWidth * 0.15) + (cardWidth * 0.5), x2 = (screenWidth * 0.2) + (cardWidth * 0.65);
    double y1 = (screenHeight * 0.4) + y, y2 = cardHeight + y;
    string cardText = "";
    char s;
    char v;
    
    for (int x = 0; x < cont; x++) {
        cardText = "";
        glColor3f(1,1,1);
        // glRectf(x1,y1, x2, y2);
//        printf("COORDS: %f %f \n", x1, y1);
        //hand
        glPushMatrix();

        glTranslatef(x1, y1, 1.0);
        glRotatef (0.0, 0.0, 0.0, 1.0);
        glTranslatef (0.5, 0.0, 0.0);
        
        glPushMatrix();
        //    glColor3f(0, 1, 0);
        glScalef (60.0, 80.0, 1.0);
        glColor3f(1, 1, 1);
        glutSolidCube(1.0);
        
        glColor3f(0, 0, 0);
        glutWireCube (1.0);
        glPopMatrix();
        glPopMatrix();
        //hand -end
        
        
        x1 += (cardWidth * 0.5);
        x2 += (cardWidth * 0.5);
        
        // pinta numero
        glColor3f(0,0,0);
        s = this->getSuit(x);
        v = this->getValue(x);
        cardText = s;
        cardText += v;
        //cout << "carta: "<<cardText << endl;
        drawCardNum(cardText, x1 - (cardWidth * 0.5), y1, 0.7, screenWidth);


    }
}

#endif /* defined(__BlackJack__Hand__) */
