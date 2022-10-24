#include "Pila.h"
#include <Punto.h>
#include <iostream>
#include<assert.h>

using namespace std;

template<typename T>
Pila<T>::Pila()
{
    this->primero = NULL;
}

template<typename T>
Pila<T>::~Pila(){
    vaciar();
}

template <typename T> void Pila<T>::agregar(T & elemento){
    Nodo * aux = new Nodo;
    aux->elemento = elemento;
    aux->previo = primero;
    primero = aux;
}

template <typename T> const T & Pila<T>::tope() const{
    assert(!es_vacia());
    return primero->elemento;
}

template <typename T> bool Pila<T>::eliminar(){
    if (primero != NULL) {
        Nodo * aux = primero;
        primero = primero->previo;
        delete aux;
        return true;
    } else
        return false;
}

template <class T> bool Pila<T>::es_vacia() const{
    return (primero == NULL);
}

template <typename T> void Pila<T>::vaciar() {
    Nodo * aux;
    while (primero != NULL) {
        aux = primero->previo;
        delete primero;
        primero = aux;
    }

    primero = NULL;
}

template class Pila<Punto>;
