//
//  main.cpp
//  BlackJack
//
//  Created by Marco Ramirez on 9/17/15.
//  Copyright (c) 2015 Ma. Guadalupe Roque. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "Hand.h"
#include "Deck.h"

using namespace std;

int screenWidth = 640, screenHeight = 420, gameZoneHeight = screenHeight * 0.8, textZoneHeight = screenHeight * 0.2, playerWins = 0, dealerWins = 0;
double cardWidth = screenWidth/6.0, cardHeight = gameZoneHeight/2.0;

Deck *deck;
Hand *player, *dealer;

bool inProgress = false, win = false, lose = false;

void drawText(std::string text,int x,int y, float size) {
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    float scale = size * ((float)screenWidth / (720.0 * 2.0));
    glScalef(scale, -scale, 0.0);
    //glScalef(1/screenWidth/0.01, -(1/screenHeight/0.01), 0.0);
    for (int c=0; c < text.length(); c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN , text[c]);
    }
    glPopMatrix();
}

void reshape(int w,int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w,h,0);
    screenHeight = h;
    screenWidth = w;
    if(screenHeight < 350 || screenWidth < 400) gameZoneHeight = screenHeight;
    else gameZoneHeight = screenHeight * 0.8;
    cardWidth = screenWidth/4.0;
    cardHeight = gameZoneHeight/4.0;
    glutPostRedisplay();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void deal() {
    inProgress = true;
    win = false;
    lose = false;
    
    Deck *d = new Deck();
    deck = d;
    d = nullptr;
    
    deck->shuffle();
    
    /*
     cout << "Deck ";
     for (int i = 0; i < 52; ++i) {
     cout << deck->getSuit(i) << deck->getValue(i) << " ";
     }
     cout << endl;
     
     cout << "Deck shuffle: ";
     for (int i = 0; i < 52; ++i) {
     cout << deck->getSuit(i) << deck->getValue(i) << " ";
     }
     cout << endl;
     */
    
    Hand *p = new Hand();
    player = p;
    p = nullptr;
    
    Hand *dl = new Hand();
    dealer = dl;
    dl = nullptr;
    
    player->addCard(deck->dealCard());
    dealer->addCard(deck->dealCard());
    player->addCard(deck->dealCard());
    dealer->addCard(deck->dealCard());
    
    cout << "Player hand: ";
    for (int i = 0; i < player->getNumCards(); ++i) {
        cout << player->getSuit(i) << player->getValue(i) << " ";
    }
    cout << endl;
    cout << "Player sum: " << player->getSum() << endl;
    
    cout << "Dealer hand: ";
    for (int i = 0; i < dealer->getNumCards(); ++i) {
        cout << dealer->getSuit(i) << dealer->getValue(i) << " ";
    }
    cout << endl;
    cout << "Dealer sum: " << dealer->getSum() << endl;
}

void hit() {
    //Add card to Player
    if(player->getSum() <= 21) {
        player->addCard(deck->dealCard());
        //Display new card and values
        
        cout << "Player hand: ";
        for (int i = 0; i < player->getNumCards(); ++i) {
            cout << player->getSuit(i) << player->getValue(i) << " ";
        }
        cout << endl;
        cout << "Player sum: " << player->getSum() << endl;
    }
    if (player->getSum() > 21) {
        //Player lost
        lose = true;
        dealerWins++;
        inProgress = false;
        cout << "You Lost!" << endl;
    }
}

void stand() {
    /*
     if(player->getSum() > 21) {
     //Player lost
     lose = true;
     dealerWins++;
     inProgress = false;
     cout << "You Lost!" << endl;
     } else {
     //Dealer's Turn
     while(dealer->getSum() < player->getSum() && dealer->getSum() <= 21) {
     dealer->addCard(deck->dealCard());
     //Display new card and values
     glutPostRedisplay();
     cout << "Dealer hand: ";
     for (int i = 0; i < dealer->getNumCards(); ++i) {
     cout << dealer->getSuit(i) << dealer->getValue(i) << " ";
     }
     cout << endl;
     cout << "Dealer sum: " << dealer->getSum() << endl;
     }
     glFlush();
     if (dealer->getSum() > 21) {
     //Dealer Lost
     win = true;
     playerWins++;
     inProgress = false;
     cout << "You Win!" << endl;
     } else if (dealer->getSum() > player->getSum()) {
     //Player lost
     lose = true;
     dealerWins++;
     inProgress = false;
     cout << "You Lost!" << endl;
     } else if (dealer->getSum() == player->getSum()) {
     //Player lost
     lose = true;
     dealerWins++;
     inProgress = false;
     cout << "You Lost!" << endl;
     }
     }
     */
    
    //Dealer's Turn
    while(dealer->getSum() < player->getSum() && dealer->getSum() <= 17) {
        dealer->addCard(deck->dealCard());
        //Display new card and values
        //glutPostRedisplay();
        cout << "Dealer hand: ";
        for (int i = 0; i < dealer->getNumCards(); ++i) {
            cout << dealer->getSuit(i) << dealer->getValue(i) << " ";
        }
        cout << endl;
        cout << "Dealer sum: " << dealer->getSum() << endl;
    }
    //glFlush();
    if (dealer->getSum() > 21) {
        //Dealer Lost
        win = true;
        playerWins++;
        inProgress = false;
        cout << "You Win!" << endl;
    } else if ((dealer->getSum() > player->getSum()) || (dealer->getSum() == player->getSum())) {
        //Player lost
        lose = true;
        dealerWins++;
        inProgress = false;
        cout << "You Lost!" << endl;
    } else {
        //Player Won
        win = true;
        playerWins++;
        inProgress = false;
        cout << "You Win!" << endl;
    }
}

void display() {
    
    //BKG Color
    glClearColor(0.1803921569,0.6784313725,0.01176470588, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    //BKG
    
    //Tablero
    glColor3f(1,1,1);
    drawText("Dealer:",screenWidth * 0.04,screenHeight * 0.25, 0.8);
    drawText("Player:",screenWidth * 0.04,screenHeight * 0.6, 0.8);
    drawText("Score Dealer: " + to_string(dealerWins) + " Player: " + to_string(playerWins),screenWidth * 0.05,screenHeight * 0.12, 0.4);
    
    //Instrucciones
    drawText("'D': Deal ",screenWidth * 0.08,screenHeight * 0.97, 0.3);
    drawText("'H': Hit",screenWidth * 0.219,screenHeight * 0.97, 0.3);
    drawText("'S': Stand",screenWidth * 0.3175,screenHeight * 0.97, 0.3);
    drawText("'Esc': Salir",screenWidth * 0.4575,screenHeight * 0.97, 0.3);
    
    //Autor
    drawText("Autor: Marco Antonio Ramirez Alarcon : A01191344",screenWidth * 0.08,screenHeight * 0.92, 0.3);
    
    //Si existe juego
    if (inProgress) {
        drawText("Hit or Stand?",screenWidth * 0.54,screenHeight * 0.15, 0.4);
        drawText("Points Dealer: " + to_string(dealer->getSum()),screenWidth * 0.68,screenHeight * 0.28, 0.4);
        drawText("Points Player: " + to_string(player->getSum()),screenWidth * 0.68,screenHeight * 0.6, 0.4);
        // pinta Cartas
        dealer->draw(0, screenWidth, screenHeight, cardWidth, cardHeight);
        player->draw((screenHeight * 0.3), screenWidth, screenHeight, cardWidth, cardHeight);
    }
    
    //Pinta Letrero Gano/Perdio
    if(win) {
        drawText("Points Dealer: " + to_string(dealer->getSum()),screenWidth * 0.68,screenHeight * 0.28, 0.4);
        drawText("Points Player: " + to_string(player->getSum()),screenWidth * 0.68,screenHeight * 0.6, 0.4);
        dealer->draw(0, screenWidth, screenHeight, cardWidth, cardHeight);
        player->draw((screenHeight * 0.3), screenWidth, screenHeight, cardWidth, cardHeight);
        inProgress = false;
        glColor3f(0.01176470588,0.3019607843,0.6784313725);
        glRectf(screenWidth * 0.07, screenHeight * 0.615,screenWidth * 0.91, screenHeight * 0.55);
        glColor3f(1,1,1);
        drawText("New Deal?",screenWidth * 0.54,screenHeight * 0.15, 0.4);
        drawText("You won! You have " + to_string(playerWins) + " win(s) and " + to_string(dealerWins) + " loses!", screenWidth * 0.1, screenHeight * 0.6, 0.4);
    } else if(lose) {
        drawText("Points Dealer: " + to_string(dealer->getSum()),screenWidth * 0.68,screenHeight * 0.28, 0.4);
        drawText("Points Player: " + to_string(player->getSum()),screenWidth * 0.68,screenHeight * 0.6, 0.4);
        dealer->draw(0, screenWidth, screenHeight, cardWidth, cardHeight);
        player->draw((screenHeight * 0.3), screenWidth, screenHeight, cardWidth, cardHeight);
        inProgress = false;
        glColor3f(0.01176470588,0.3019607843,0.6784313725);
        glRectf(screenWidth * 0.07, screenHeight * 0.615,screenWidth * 0.91, screenHeight * 0.55);
        glColor3f(1,1,1);
        drawText("New Deal?",screenWidth * 0.54,screenHeight * 0.15, 0.4);
        drawText("You Lost! You have " + to_string(playerWins) + " win(s) and " + to_string(dealerWins) + " loses!", screenWidth * 0.1, screenHeight * 0.6, 0.4);
    }
    
    //Intercambia los frame buffers
    glutSwapBuffers();//ya tiene integrado el glFlush
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY) {
    switch (theKey) {
            //Deal
        case 'd':
        case 'D':
            if (inProgress) {
                //Lost game
                glutPostRedisplay();
                lose = true;
                dealerWins++;
                glFlush();
                /*
                 cout << "You Lost!" << endl;
                 glColor3f(0.01176470588,0.3019607843,0.6784313725);
                 glRectf(screenWidth * 0.07, screenHeight * 0.615,screenWidth * 0.91, screenHeight * 0.55);
                 glColor3f(1,1,1);
                 drawText("You Lost! You have " + to_string(playerWins) + " win(s) and " + to_string(dealerWins) + " loses!", screenWidth * 0.1, screenHeight * 0.6, 0.4); */
                inProgress = false;
            }
            deal();
            break;
            
            //Hit
        case 'h':
        case 'H':
            if (inProgress) {
                hit();
            }
            break;
            
            //Stand
        case 's':
        case 'S':
            if (inProgress) {
                stand();
            }
            break;
            
            //Salir
        case 27:
            exit(-1);
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    srand(time(0));
    glutInit(&argc, argv);
    glutInitWindowSize(screenWidth,screenHeight);
    glutInitWindowPosition(100,100);
    //Double frame buffer
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutCreateWindow("Blackjack Marco Ramirez");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    return EXIT_SUCCESS;
}
