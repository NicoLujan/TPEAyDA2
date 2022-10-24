#include <iostream>
#include <Grafo.h>
#include<ConjuntosDisjuntos.h>
#include <iostream>



using namespace std;

//Dado un grafo no dirigido conexo y rotulado con costos positivos, determine el árbol de
//recubrimiento de costo mínimo. Implemente el algoritmo Kruskal.

struct Aristas{
    int Vertice1;
    int Vertice2;
    int costo;
};

void PasarAArreglo(list<Aristas> LA,Aristas A[]){
    list<Aristas>::iterator itA = LA.begin();
    int i=0;
    while (itA != LA.end()){
        Aristas aux;
        aux = *itA;
        A[i] = aux;
        i++;
        itA++;
    }
}

void Quicksort(Aristas arreglo[],int primero, int ultimo){
    int i,j;
    Aristas aux,pivote;
    i=primero;
    j=ultimo;
    pivote=arreglo[(primero+ultimo)/2];//es el elemento medio del arreglo
    do{
        while(pivote.costo>arreglo[i].costo)
        i++;
        while(pivote.costo<arreglo[j].costo)
        j--;
        if(i<=j){
            aux=arreglo[i];
            arreglo[i]=arreglo[j];
            arreglo[j]=aux;
            i++;
            j--;
        }
     }while(i<=j);
     if(primero<j)
       Quicksort(arreglo,primero,j);
     if(ultimo>i)
       Quicksort(arreglo,i,ultimo);

  }


template<typename C>
ostream & operator << (ostream & salida, const Grafo<C> & Grafo)
    {
	// Recorremos todos los vertices
	list<int> vertices;
	Grafo.devolverVertices(vertices);
	list<int>::iterator v = vertices.begin();

	while (v != vertices.end()) {
		salida << "    " << *v << "\n";
		// Recorremos todos los adyacentes de cada vertice
		list< typename Grafo<C>::Arco> adyacentes;
		Grafo.devolverAdyacentes(*v, adyacentes);
		typename list< typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "   " <<  *v << "---"  << ady->devolverAdyacente() << " (" << ady->devolverCosto () << ")\n";
			ady++;
		}
		v++;
	}
	return salida;
}

template<typename C>
void Kruskal(Grafo<C> & grafo,list<Aristas> & List_Arist){

    Aristas ArregloDeAristas[List_Arist.size()],ArbolDeRecubrimiento[grafo.cantidadVertices()-1]; //Almacena en un arreglo el arbol de recubrimiento de costo minimo
    PasarAArreglo(List_Arist,ArregloDeAristas);
    Quicksort(ArregloDeAristas,0,List_Arist.size()-1);
    ConjuntosDisjuntos Componentes(grafo.cantidadVertices());
    int i=0,k=0;

   while(Componentes.Count() > 1){
        Aristas aux = ArregloDeAristas[i];
        int componente_u = Componentes.Find(aux.Vertice1);
        int componente_v = Componentes.Find(aux.Vertice2);
        if(componente_u != componente_v){
            ArbolDeRecubrimiento[k] = aux;
            Componentes.Union(componente_u,componente_v);
            k++;
        }
        i++;
    }

    cout<<"\nÁrbol de recubrimiento de minimo costo: "<<endl;
    for(int j=0;j<grafo.cantidadVertices()-1;j++){
        cout<<"   "<<ArbolDeRecubrimiento[j].Vertice1<<"---"<<ArbolDeRecubrimiento[j].Vertice2<<" ("<<ArbolDeRecubrimiento[j].costo<<") "<<endl;
    }

}

//-----------------   M A I N  ------------------

int main(int argc, char **argv)
{

	Grafo<int> g;
	list<Aristas> ListaDeAristas;
	Aristas arista;


	// Cargamos un GrafoDirigido dirigido
	// Primero los vértices
	g.agregarVertice(1);
	g.agregarVertice(2);
	g.agregarVertice(3);
	g.agregarVertice(4);
	g.agregarVertice(5);

    // Luego los arcos
	g.agregarArco(1, 2, 10);
	g.agregarArco(2, 1, 10);
	arista.Vertice1 = 1; arista.Vertice2 = 2; arista.costo = 10;
	ListaDeAristas.push_back(arista);

	g.agregarArco(1, 4, 30);
	g.agregarArco(4, 1, 30);
	arista.Vertice1 = 1; arista.Vertice2 = 4; arista.costo = 30;
	ListaDeAristas.push_back(arista);

	g.agregarArco(1, 5, 100);
	g.agregarArco(5, 1, 100);
	arista.Vertice1 = 1; arista.Vertice2 = 5; arista.costo = 100;
	ListaDeAristas.push_back(arista);

	g.agregarArco(2, 3, 50);
	g.agregarArco(3, 2, 50);
	arista.Vertice1 = 2; arista.Vertice2 = 3; arista.costo = 50;
	ListaDeAristas.push_back(arista);

	g.agregarArco(3, 5, 10);
	g.agregarArco(5, 3, 10);
	arista.Vertice1 = 3; arista.Vertice2 = 5; arista.costo = 10;
	ListaDeAristas.push_back(arista);

	g.agregarArco(3, 4, 60);
	g.agregarArco(4, 3, 60);
	arista.Vertice1 = 3; arista.Vertice2 = 4; arista.costo = 60;
	ListaDeAristas.push_back(arista);

	g.agregarArco(4, 5, 20);
	g.agregarArco(5, 4, 20);
	arista.Vertice1 = 4; arista.Vertice2 = 5; arista.costo = 20;
	ListaDeAristas.push_back(arista);

	cout<<"Grafo no dirigido conexo ingresado por teclado: "<<endl;
	cout<<g;

	Kruskal(g,ListaDeAristas);

}
