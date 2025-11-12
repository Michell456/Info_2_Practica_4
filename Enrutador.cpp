#include "Enrutador.h"
#include <algorithm>
using namespace std;

Enrutador::Enrutador(string id): idEnrut(id), distancia(INT_MAX), visitado(false) {}

void Enrutador::nuevoVecino(Enrutador* vecino, int costo) {
    vecinos.emplace_back(vecino, costo);
}

void Enrutador::reinicio() {
    distancia = INT_MAX;
    visitado = false;
}

void Enrutador::mostrarTabla() const {
    cout << "Tabla de enrutamiento del enrutador " << idEnrut << ":\n";
    for (const auto& par : caminos) {
        cout << "  Destino " << par.first->idEnrut
             << " | Costo " << par.first->distancia
             << " | Camino: ";
        for (auto* paso : par.second) {
            cout << paso->idEnrut;
            if (paso != par.second.back()) cout << " -> ";
        }
        cout << '\n';
    }
}

void dijkstra(Enrutador* fuente, const std::vector<Enrutador*>& todos) {
    for (auto* r : todos) r->reinicio();
    fuente->distancia = 0;

    std::priority_queue<std::pair<int, Enrutador*>> cola;
    cola.push({0, fuente});

    std::map<Enrutador*, Enrutador*> anterior;

    while (!cola.empty()) {
        Enrutador* actual = cola.top().second;
        cola.pop();

        if (actual->visitado) continue;
        actual->visitado = true;

        for (auto& [vecino, costo] : actual->vecinos) {
            int nuevaDist = actual->distancia + costo;
            if (nuevaDist < vecino->distancia) {
                vecino->distancia = nuevaDist;
                anterior[vecino] = actual;
                cola.push({-nuevaDist, vecino});
            }
        }
    }

    fuente->caminos.clear();
    for (auto* destino : todos) {
        if (destino == fuente) continue;
        std::vector<Enrutador*> camino;
        for (Enrutador* at = destino; at != nullptr; at = anterior[at]) {
            camino.push_back(at);
            if (at == fuente) break;
        }
        std::reverse(camino.begin(), camino.end());
        if (!camino.empty() && camino.front() == fuente)
            fuente->caminos[destino] = camino;
    }
}

