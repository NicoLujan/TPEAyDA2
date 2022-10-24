#ifndef CONJUNTOSDISJUNTOS_H
#define CONJUNTOSDISJUNTOS_H


class ConjuntosDisjuntos
{
    public:
        ConjuntosDisjuntos(int n);
        virtual ~ConjuntosDisjuntos();
        int Count();
        bool Connected(int i,int j);
        void Union(int i, int j);
        int Find(int j);

    protected:

    private:
        int *p;
        int contar;
};

#endif // CONJUNTOSDISJUNTOS_H
