#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <Punto.h>
#include <math.h>
#include <stack>


using namespace std;

int const N = 36; //Cantidad de puntos almacenados en el archivo

float distancia (Punto p1, Punto p2){
    return sqrt((p1.CoordX() - p2.CoordX())*(p1.CoordX() - p2.CoordX()) + (p1.CoordY() - p2.CoordY())*(p1.CoordY() - p2.CoordY()));
}

int direction(Punto PI,Punto PJ,Punto PK) //PI es el ancla, si < 0 -> PJ esta a derecha de PK, sino al reves. Si = 0, son colineales
{
    return(((PK.CoordX()-PI.CoordX())*(PJ.CoordY()-PI.CoordY())-(PJ.CoordX()-PI.CoordX())*(PK.CoordY()-PI.CoordY())));
}

void intercambio(Punto *puntos, int inicio, int fin, int medio, Punto ancla){ //puntos contiene todos los puntos menos el ancla
    int i = inicio, j = medio+1, k = inicio;
    Punto aux[fin];
    while (i <= medio && j <= fin){
        if (direction(ancla,puntos[i],puntos[j]) < 0){ //puntos[i] esta mas a derecha que puntos[j]
            aux[k] = puntos[i];
            k++;
            i++;
        } else if (direction(ancla,puntos[i],puntos[j]) == 0){  //si son colineales
            if (distancia(ancla,puntos[i]) > distancia(ancla,puntos[j])) {
                aux[k] = puntos[i];
                k++;
                i++;
            }else{
                aux[k] = puntos[j];
                k++;
                j++;
            }
        } else{ // si puntos[j] esta mas a derecha
            aux[k] = puntos[j];
            k++;
            j++;
        }
    }
    while (i <= medio) {
        aux[k] = puntos[i];
        k++;
        i++;
    }
    while (j <= fin) {
        aux[k] = puntos[j];
        k++;
        j++;
    }
    for (i = inicio; i < k; i++)  {
        puntos[i] = aux[i];
    }
}

void merge_sort (Punto *puntos, int inicio, int fin, Punto ancla){ //inicio+1, porq ancla es el primer punto
    int medio;
    if (inicio < fin){
        medio = (inicio+fin)/2;
        merge_sort(puntos,inicio,medio,ancla);
        merge_sort(puntos,medio+1,fin,ancla);
        intercambio(puntos,inicio,fin,medio,ancla);
    }
}

Punto nextToTop (stack<Punto> &pila){ //agarro el anterior al tope de la pila
    Punto p = pila.top();
    pila.pop();
    Punto anterior = pila.top();
    pila.push(p);
    return anterior;
}

void cambio (Punto &p1, Punto &p2){
    Punto temp = p1;
    p1 = p2;
    p2 = temp;
}

void GrahamScan (Punto *puntos, int n){

    int ymin = puntos[0].CoordY();
    int minimo = 0;

    for(int i=1;i<n;i++){ //tomo el punto de menor y
        int y = puntos[i].CoordY();
        if ((y < ymin) || (ymin == y && puntos[i].CoordX() < puntos[minimo].CoordX())){
            ymin = puntos[i].CoordY();
            minimo = i;
        }
    }

    cambio(puntos[0],puntos[minimo]); //pongo el punto de menor y en la primera posicion del arreglo

    Punto p0 = puntos[0];

    merge_sort(puntos,1,n-1,p0); //ordeno los puntos segun el angulo con p0


    int m = 1;

    for(int i=1;i<n;i++){ //si son colineales los saco
        while (i < n-1 && direction(p0,puntos[i],puntos[i+1]) == 0)
            i++;
        puntos[m] = puntos[i];
        m++; // m va a ser el tamaño del arreglo de puntos, siendo este los puntos posibles del convex hull
    }

    cout<<"Puntos procesados por el algoritmo de Graham Scan: "<<endl;
    for (int i=0;i<m;i++)
        cout << "(" << puntos[i].CoordX() << "," << puntos[i].CoordY() << ")" << endl;

    stack<Punto> pila;
    pila.push(p0);
    pila.push(puntos[1]);
    pila.push(puntos[2]);

    for(int i=3;i<m;i++){
        while(direction(nextToTop(pila),pila.top(),puntos[i]) > 0) //mientras sea un giro no a izquierda, elimino de la pila
            pila.pop();
        pila.push(puntos[i]);
    }

    cout<<"\nPuntos que forman parte del convex hull: "<<endl;

    while(!pila.empty()){ //pila ahora contiene todos los puntos del convex hull
        Punto p = pila.top();
        cout << "(" << p.CoordX() << "," << p.CoordY() << ")" << endl;
        pila.pop();
    }
}

void BuscarMenor(Punto *puntos,int N) //Funcion que busca el menor punto de coordenada Y, si existe mas de uno,
{                                     //se queda con el que esta mas a la "izquierda" y lo almacena en la primera
    Punto menor = puntos[0];          //posicion del arreglo
    int indice = 0;
    for(int i=1;i<N;i++){
        if(puntos[i].CoordY() < menor.CoordY()){
            menor = puntos[i];
            indice = i;
        }else if(puntos[i].CoordY() == menor.CoordY()){
                if(puntos[i].CoordX() < menor.CoordX()){
                    menor = puntos[i];
                    indice = i;
                }
            }
    }

    Punto aux1 = puntos[0];
    puntos[0] = menor;
    puntos[indice] = aux1;

}

void cargarNube_desdeArchivo(Punto All_Points[]){

    string linea;
    float x,y;
    int k=0;

    ifstream archivo("Nube_Puntos.txt",ios::in);



    if(archivo.fail()){
        cerr<<"Error al intentar abrir el archivo Nube_Puntos.txt"<<endl;
    }else{
        while (!archivo.eof()){
            getline(archivo,linea,'\n');
            for(unsigned int i=0; i<linea.size();i++){
                if(linea[i] == '('){
                    if(linea[i+1] == '-'){
                        x = ((linea[i+2]) - '0') * (-1); // Coordenadas de un solo digito
                    }else{
                        x = linea[i+1] - '0';
                    }
                }else if(linea[i] == ','){
                    if(linea[i+1] == '-'){
                        y = ((linea[i+2]) - '0') * (-1);
                    }else{
                        y = linea[i+1] - '0';
                    }
                }
            }
            if(k < N){
                Punto P(x,y);
                All_Points[k] = P;
                k++;
            }
        }
    }

    archivo.close();

    cout<<"Nube de puntos almacenada en el archivo: "<<endl;
    for (int i=0;i<N;i++)
        cout << "(" << All_Points[i].CoordX() << "," << All_Points[i].CoordY() << ")" << endl;

    cout<<"Presione enter para continuar...";
    cin.get();
    system("clear");

}

void eliminacionPuntosInternos(Punto A[]){
    int MayorSuma = -999999999, MayorResta = -999999999;
    int MenorSuma = 999999999, MenorResta = 999999999;

    unsigned int indiceMenorSuma,indiceMenorResta,indiceMayorSuma,indiceMayorResta;

    for(int i=0;i<N;i++){
        int aux1 = A[i].CoordX()+A[i].CoordY();
        int aux2 = A[i].CoordX()-A[i].CoordY();

        if(MayorSuma < aux1){
            MayorSuma = aux1;
            indiceMayorSuma = i;
        }
        if(MenorSuma > aux1){
            MenorSuma = aux1;
            indiceMenorSuma = i;
        }
        if(MenorResta > aux2){
            MenorResta = aux2;
            indiceMenorResta = i;
        }
        if(MayorResta < aux2){
            MayorResta = aux2;
            indiceMayorResta = i;
        }

    }

    Punto aux = A[indiceMayorResta]; //Almaceno en el indice 0 el punto mas "abajo" y mas a la "derecha"
    A[indiceMayorResta] = A[0];
    A[0] = aux;

    aux = A[indiceMayorSuma];   //Almaceno en el indice 1 el punto mas "arriba" y mas a la "derecha"
    A[indiceMayorSuma] = A[1];
    A[1] = aux;

    aux = A[indiceMenorResta];  //Almaceno en el indice 2 el punto mas "arriba" y mas a la "izquierda"
    A[indiceMenorResta] = A[2];
    A[2] = aux;

    aux = A[indiceMenorSuma];   //Almaceno en el indice 3 el punto mas "abajo" y mas a la "izquierda"
    A[indiceMenorSuma] = A[3];
    A[3] = aux;

    int opc;
    cout<<"Digite que opcion desea realizar para eliminar los puntos internos: "<<endl;
    cout<<"1.Descartar puntos internos por productos cruzados"<<endl;
    cout<<"2.Descartar puntos internos con respecto a los ejes coordenados"<<endl;
    cin>>opc;

    system("clear");

    if(opc == 1){
        int nuevoTamanio = N;
        int i=4;

        while(i<nuevoTamanio){
            if((direction(A[0],A[1],A[i]) <= 0) && (direction(A[1],A[2],A[i]) <= 0) && (direction(A[2],A[3],A[i]) <= 0) && (direction(A[3],A[0],A[i]) <= 0)){
                Punto auxiliar = A[i];
                A[i] = A[nuevoTamanio - 1];
                A[nuevoTamanio - 1] = auxiliar;
                nuevoTamanio--;
            }else
                i++;
        }
        GrahamScan(A,nuevoTamanio);
    }else if (opc == 2){

        int nuevoTamanio = N;
        int i=4;

        int YSuperior;
        if(A[1].CoordY() <= A[2].CoordY())
            YSuperior = A[1].CoordY();
        else
            YSuperior = A[2].CoordY();

        int YInferior;
        if(A[0].CoordY() >= A[3].CoordY())
            YInferior = A[0].CoordY();
        else
            YInferior = A[3].CoordY();

        int XSuperior;
        if(A[0].CoordX() <= A[1].CoordX())
            XSuperior = A[0].CoordX();
        else
            XSuperior = A[1].CoordX();

        int Xinferior;
        if(A[2].CoordX() >= A[3].CoordX())
            Xinferior = A[2].CoordX();
        else
            Xinferior = A[3].CoordX();


       while(i<nuevoTamanio){
            if((A[i].CoordX() >= Xinferior) && (A[i].CoordX() <= XSuperior) && (A[i].CoordY() <= YSuperior) && (A[i].CoordY() >= YInferior)){
                Punto auxiliar = A[i];
                A[i] = A[nuevoTamanio - 1];
                A[nuevoTamanio - 1] = auxiliar;
                nuevoTamanio--;
            }else
                i++;
        }
        GrahamScan(A,nuevoTamanio);
    }

}

int main()
{
    Punto NubePuntos[N];

    cargarNube_desdeArchivo(NubePuntos);
    int opc;

    cout<<"\tMenu Principal"<<endl;
    cout<<"1.Graham Scan"<<endl;
    cout<<"2.Graham Scan con eliminacion de puntos internos"<<endl;
    cout<<"3.Salir"<<endl;
    cout<<"Digite lo que desea realizar: ";cin>>opc;
    system("clear");

    switch(opc){
        case 1: GrahamScan(NubePuntos,N);
                break;
        case 2: eliminacionPuntosInternos(NubePuntos);
                break;
        case 3:break;

    }

    return 0;
}
