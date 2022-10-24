#ifndef PILA_H
#define PILA_H

using namespace std;

template <typename T>
    class Pila
{
        public:
            Pila(); // Constructor
            ~Pila(); // Destructor
            void agregar(T & elemento);
            const T & tope() const;
            bool eliminar();
            bool es_vacia() const;


        private:
        struct Nodo {
            T elemento;
            Nodo * previo;
        };

        void vaciar();

        Nodo * primero;
};

#endif // PILA_H
