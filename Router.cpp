#include "Router.h"

void Router::agregarConexion(string destino, int costo) {
    conexiones[destino] = costo;
}

void Router::eliminarConexion(string destino) {
    conexiones.erase(destino);
}

bool Router::existeConexion(string destino) const {
    return conexiones.find(destino) != conexiones.end();
}

void Router::mostrarConexiones() const {
    cout << "Router " << id << " conexiones:\n";
    for (auto& c : conexiones)
        cout << c.first << " (costo " << c.second << ")\n";
}
