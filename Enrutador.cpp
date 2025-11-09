#include <iostream>
#include "Enrutador.h"
#include <climits>
#include <queue>



Enrutador::Enrutador(int id): idEnrut(id),distancia(INT_MAX),visitado(false){}

void Enrutador::nuevoVecino(Enrutador* vecino, int costo){
    vecinos.emplace_back(vecino,costo);
}

void Enrutador::reinicio(){
    distancia = INT_MAX;
    visitado = false;
}


void dijkstra(Enrutador* fuente){

    fuente->distancia = 0;

    priority_queue<pair<int, Enrutador*>> colaEnrut; //El elemento con mayor prior (int) se pone al principio

    colaEnrut.push({0,fuente});

    while(!colaEnrut.empty()){
        Enrutador* actual = colaEnrut.top().second;
        colaEnrut.pop();

        if(actual->visitado) continue;
        actual->visitado = true;

        for(auto& veci : actual->vecinos){ //Leo vecinos del router actual
            Enrutador* sigEnrutador = veci.first;
            int costoEnlace = veci.second;
            int nuevaDist = actual->distancia + costoEnlace;
            if (nuevaDist< sigEnrutador->distancia){
                sigEnrutador->distancia = nuevaDist;
                colaEnrut.push({-nuevaDist,sigEnrutador});
            }
        }
    }


}
