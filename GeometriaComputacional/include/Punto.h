#ifndef PUNTO_H
#define PUNTO_H


class Punto
{
    public:
        Punto(float,float);
        Punto();
        float CoordX()const;
        float CoordY()const;
        float distancia(const Punto & otroPunto)const;
        virtual ~Punto();
        bool operator==(const Punto & otroPunto)const;
        void operator=(Punto & otroPunto);
        void trasladar(float x, float y);

    private:
        float x,y;
};

#endif // PUNTO_H
