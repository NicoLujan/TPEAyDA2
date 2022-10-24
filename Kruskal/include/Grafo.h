#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <map>
#include <iostream>
#include <assert.h>

using namespace std;

template <typename C> class Grafo{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolverAdyacente() const;
		const C & devolverCosto() const;
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool estaVacio() const;

	// Devuelve la cantidad de vértices del grafo
	int cantidadVertices() const;

	bool existeVertice(int vertice) const;

	bool existeArco(int origen, int destino) const;

	// PRE CONDICION: existeArco(origen, destino)
	const C & costoArco(int origen, int destino) const;

	void devolverVertices(list<int> & vertices) const;

	void devolverAdyacentes(int origen, list<Arco> & adyacentes) const;//anda
	void devolverAdyacentes(int origen, list<int> & adyacentes) const;

	void agregarVertice(int vertice);//anda

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminarVertice(int vertice);//anda

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	//return true si se pudo agregar el arco y falso en caso contrario
	bool agregarArco(int origen, int destino, const C & costo);//anda

	// POST CONDICION: !existeArco(origen, destino)
	void eliminarArco(int origen, int destino);//anda

	// PRE CONDICION: existeArco(origen, destino)
	void modificarCostoArco(int origen, int destino, const C & costo);//anda

	void grafoReverso(Grafo<C> & reverso) ;//anda


	void vaciar();//anda

private:
	/*
	 * Definir la estructura interna
	 */
    map<int, map<int, C> > grafo;

}; // class Grafo


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco()
{
}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
    this->vertice = adyacente;
    this->costo = costo;
}

template <typename C> int Grafo<C>::Arco::devolverAdyacente() const
{
    return vertice;
}

template <typename C> const C & Grafo<C>::Arco::devolverCosto() const
{
    return costo;
}


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo()
{
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{
    this->operator=(otroGrafo);
}

template <typename C> Grafo<C>::~Grafo()
{

}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{
    grafo.clear();
    typename map<int, map<int, C> >::const_iterator itOtro = otroGrafo.grafo.begin();
    while (itOtro != otroGrafo.grafo.end()) {
        grafo[itOtro->first] = itOtro->second;
        itOtro++;
    }
    return *this;
}

template <typename C> bool Grafo<C>::estaVacio() const
{
    return (grafo.empty());
}

template <typename C> int Grafo<C>::cantidadVertices() const
{
    return (grafo.size());
}

template <typename C> bool Grafo<C>::existeVertice(int vertice) const
{
    return (grafo.find(vertice) != grafo.end());
}

template <typename C> bool Grafo<C>::existeArco(int origen, int destino) const
{
    bool result = false;
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            result = true;
    }
    return result;
}

template <typename C> const C & Grafo<C>::costoArco(int origen, int destino) const
{
    typename map<int,map<int, C>>::const_iterator itV = grafo.find(origen);
    if((itV != grafo.end()) && (existeArco(origen,destino))){
        typename map<int,C>::const_iterator itA = itV->second.find(destino);
        return itA->second;
    }
    return NULL;
}

template <typename C> void Grafo<C>::devolverVertices(list<int> & vertices) const
{
    vertices.clear();
    typename map<int, map<int, C> >::const_iterator itV = grafo.begin();
    while (itV != grafo.end()) {
        vertices.push_back(itV->first);
        itV++;
    }
}

template <typename C> void Grafo<C>::devolverAdyacentes(int origen, list<Arco> & adyacentes) const
{
    adyacentes.clear();
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.begin();
        while (itA != itV->second.end()) {
            adyacentes.push_back(Arco(itA->first, itA->second));
            itA++;
        }
    }
}

template <typename C> void Grafo<C>::devolverAdyacentes(int origen, list<int> & adyacentes) const
{
    adyacentes.clear();
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.begin();
        while (itA != itV->second.end()) {
            adyacentes.push_back(itA->first);
            itA++;
        }
    }
}

template <typename C> void Grafo<C>::agregarVertice(int vertice)
{
    if (grafo.find(vertice) == grafo.end()) {
        map<int, C> adyacentes;
        grafo[vertice] = adyacentes;
    }
}

template <typename C> void Grafo<C>::eliminarVertice(int vertice)
{
    typename map<int,map<int,C>>::iterator itV = grafo.begin();
    while (itV != grafo.end()){
        if(itV->first == vertice)
            grafo.erase(vertice);
        else{
            typename map<int,C>::iterator itA = itV->second.begin();
            while(itA != itV->second.end()){
                if(existeArco(itV->first,vertice))
                    eliminarArco(itV->first,vertice);
                itA++;
            }
        }
        itV++;
    }
}

template <typename C> void Grafo<C>::modificarCostoArco(int origen, int destino, const C & costo)
{
   assert(existeArco(origen,destino));
   typename map<int, map<int, C> >:: iterator itV = grafo.find(origen);
   typename map<int, C> :: iterator itA = itV->second.find(destino);
   itA->second = costo;

}

template <typename C> bool Grafo<C>::agregarArco(int origen, int destino, const C & costo)
{
    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    if ( (itV != grafo.end() ) and existeVertice(destino)){
        itV->second[destino] = costo;
        return true;
        }
    else return false;
}

template <typename C> void Grafo<C>::eliminarArco(int origen, int destino)
{
    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            itV->second.erase(itA);
    }
}

template <typename C>  void Grafo<C>::grafoReverso(Grafo<C> & reverso)
{
    reverso.grafo.clear();
    typename map<int, map<int, C> >::iterator itV = grafo.begin();

    // agrego los vértices a reverso
    while (itV != grafo.end())
        {reverso.agregarVertice(itV->first); cout << "vertice "  << itV->first; itV++;}

    itV = grafo.begin();
    while (itV!= grafo.end())
    {
        typename map<int,C>::iterator itA = itV->second.begin();
        while (itA!= itV->second.end())
        {
            reverso.agregarArco(  itA->first, itV->first, itA->second);
            itA++;
        }
        itV++;
    }

}


template <typename C> void Grafo<C>::vaciar()
{
    grafo.clear();
}

#endif /* GRAFOD_H_ */
