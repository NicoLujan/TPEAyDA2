#ifndef SEGMENTO_H
#define SEGMENTO_H
#include <Punto.h>


class Segmento
{
    public:
        Segmento(Punto & ext1,Punto & ext2);
        const Punto & extremo1() const;
        const Punto & extremo2() const;
        float longitud() const;
        void trasladar(float x, float y);
        bool operator==(const Segmento &
        otroSegmento) const;

    private:
        Punto ext1,ext2;
};

#endif // SEGMENTO_H
