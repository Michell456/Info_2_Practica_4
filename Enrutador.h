#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <climits>
#include <queue>
using namespace std;

class Enrutador {
public:
    string idEnrut;
    std::vector<std::pair<Enrutador*, int>> vecinos;
    std::map<Enrutador*, std::vector<Enrutador*>> caminos;
    int distancia;
    bool visitado;

    Enrutador(string id);
    void nuevoVecino(Enrutador* vecino, int costo);
    void reinicio();
    void mostrarTabla() const;
};

void dijkstra(Enrutador* fuente, const std::vector<Enrutador*>& todos);

#endif

