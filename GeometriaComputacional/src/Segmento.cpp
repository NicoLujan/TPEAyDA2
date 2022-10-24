#include "Segmento.h"
#include<assert.h>

Segmento::Segmento(Punto& ext1,Punto& ext2)
{
    assert(ext1 == ext2);
    this->ext1 = ext1;
    this->ext2 = ext2;
}

const Punto & Segmento::extremo1() const
{
    return this->ext1;
}

const Punto & Segmento::extremo2() const
{
    return this->ext2;
}

float Segmento::longitud() const
{
    return (ext1.distancia(ext2));
}

void Segmento::trasladar(float x,float y)
{
    ext1.trasladar(x,y);
    ext2.trasladar(x,y);
}

bool Segmento::operator==(const Segmento & otroSegmento) const {
    return((ext1 == otroSegmento.ext1) && (ext2 == otroSegmento.ext2)) ||
                                ((ext1 == otroSegmento.ext2) && (ext2 == otroSegmento.ext1)) ;
}
