//
//  Card.h
//  BlackJack
//
//  Created by Ma. Guadalupe Roque on 21/07/14.
//  Copyright (c) 2014 Ma. Guadalupe Roque. All rights reserved.
//

#ifndef BlackJack_Card_h
#define BlackJack_Card_h

#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

class Card
{
public:
    // Constructor
     Card(char ss, char vv);
    
    // metodos modificadores
    void setSuit(char ss);
    void setValue(char vv);
    
    // metodos de acceso
    char getSuit();
    char getValue();
    
    
    // otros métodos
    void muestra();
    static void dibujaPoligono(int xMin, int xMax, int yMin, int yMax);
    void draw(int x, int y);
    
    
private:
    // Atributos
    char s, v;
};

Card::Card(char ss, char vv)
{
    s = ss;
    v = vv;
}

// metodos modificadores
void Card::setSuit(char ss)
{
    s=ss;
}

void Card::setValue(char vv)
{
    v=vv;
}

char Card::getSuit()
{
    return s;
}

char Card::getValue()
{
    return v;
}

void Card::muestra()
{
    cout << s << ":" << v << endl;
}

 void Card::dibujaPoligono(int xMin, int xMax, int yMin, int yMax)
{
    glBegin(GL_POLYGON);
    glVertex2d( xMin,yMin);
    glVertex2d( xMax,yMin );
    glVertex2d( xMax,yMax);
    glVertex2d( xMin,yMax);
    glEnd();
    
}

void Card::draw(int x, int y)
{
    glColor3ub(0, 0, 255);
    dibujaPoligono(x, x+50, y, y+100);

}

#endif

