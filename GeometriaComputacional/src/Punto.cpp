#include "Punto.h"
#include <math.h>

Punto::Punto(float x,float y)
{
    this->x = x;
    this->y = y;
}

Punto::Punto()
{
    this->x = 0;
    this->y = 0;
}

float Punto::CoordX() const
{
    return this->x;
}

float Punto::distancia(const Punto & otroPunto)const
{
    return (sqrt(pow((CoordX()-otroPunto.CoordX()),2)+(pow(CoordY()-otroPunto.CoordY(),2))));
}

float Punto::CoordY() const
{
    return this->y;
}

bool Punto::operator==(const Punto & otroPunto)const
{
    return ((x == otroPunto.x) && (y == otroPunto.y));
}

void Punto::operator=(Punto & otroPunto)
{
    this->x = otroPunto.CoordX();
    this->y = otroPunto.CoordY();
}

void Punto::trasladar(float x, float y) {
    this->x += x;
    this->y += y;
}

Punto::~Punto()
{
    //dtor
}
