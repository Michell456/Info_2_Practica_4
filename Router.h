#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <map>
#include <string>
using namespace std;

class Router {
private:
    string id;
    map<string, int> conexiones;          //vecinos y costos

public:
    Router() = default;
    Router(string id) : id(id) {}

    string getId() const { return id; }
    map<string, int> getConexiones() const { return conexiones; }

    void agregarConexion(string destino, int costo);
    void eliminarConexion(string destino);
    bool existeConexion(string destino) const;
    void mostrarConexiones() const;
};

#endif
