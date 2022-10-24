#include <iostream>

using namespace std;

const int N=3;
int TotalCosto=999999999,ArregloSolucion[] = {-1,-1,-1};

void calcularsolucion(int A[],int C){

    if(TotalCosto > C){
        for(int i=0;i<N;i++){
            ArregloSolucion[i] = A[i];
        }
        TotalCosto = C;
    }
}

bool Poda(int solucion[],int i,int CM){
    int j=0;
    if(CM < TotalCosto){ //Poda por costo
        while(j<i){
            if(solucion[j] == solucion[i]){ //Poda por repeticion de tareas
                return 1;
            }
            j++;
        }
    }else{
        return 1;
    }
    return 0;
}


void BackAsignacionDeTareas(int Costos[][N],int nroPersona,int CostoMomento,int solucionMomento[]){

    if(nroPersona == N){
        calcularsolucion(solucionMomento,CostoMomento);
    }else{
        int tarea = 0;

        while(tarea < N){
            solucionMomento[nroPersona] = tarea;
            CostoMomento += Costos[nroPersona][tarea];
            if(!Poda(solucionMomento,nroPersona,CostoMomento)){
                BackAsignacionDeTareas(Costos,nroPersona+1,CostoMomento,solucionMomento);
                CostoMomento -= Costos[nroPersona][tarea];
            }
            tarea++;
        }
    }
}

int main()
{
    int Costos[N][N] = {{4,9,1},{7,2,3},{6,3,5}} ,costo = 0 ,A[] = {-1,-1,-1} ,persona=0;

    cout<<"Matriz de costos: "<<endl; //Donde cada columna representa una tarea (0-2) y cada fila una persona(0-2)
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<Costos[i][j]<<" ";
        }
        cout<<"\n";
    }

    BackAsignacionDeTareas(Costos,persona,costo,A);

    cout<<"\n";
    for(int i=0;i<N;i++){
        cout<<"Se le asigna a la persona "<<i+1<<" la tarea: "<<ArregloSolucion[i]+1<<endl;
    }
    cout<<"\nCon un costo total: "<<TotalCosto<<endl;

    return 0;
}
