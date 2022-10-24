#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista
{
    public:
        Lista();
        virtual ~Lista();
        void agregar(T & elemento);
        const T & tope() const;
        bool eliminar();
        bool es_vacia() const;

    protected:

    private:
        struct Nodo{
            T elemento;
            Nodo *siguiente;
        };

        Nodo *first;

        void vaciar();

        int cantidadElementos;
};

#endif // LISTA_H
