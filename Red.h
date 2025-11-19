#ifndef RED_H
#define RED_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "Enrutador.h"

using namespace std;

class Red {
private:
    map<string, Enrutador*> enrutadores;

public:
    // Constructor y destructor
    Red() = default;
    ~Red();

    // Operaciones básicas de enrutadores
    void agregarEnrutador(string id);
    void eliminarEnrutador(string id);

    // Operaciones de conexiones
    void conectar(string id1, string id2, int costo);
    void desconectar(string id1, string id2);

    // Funcionalidades de visualización
    void mostrarTopologia() const;
    void mostrarCamino(string origen, string destino) const;

    // Cálculo de rutas
    void calcularRutas();

    // Utilidades
    bool existeEnrutador(string id) const;
    void limpiarRed();
    Enrutador* getEnrutador(string id) const;
    const map<string, Enrutador*>& getEnrutadores() const { return enrutadores; }

    // Carga y guardado
    void cargarDesdeArchivo(const string& nombreArchivo);
    void guardarEnArchivo(const string& nombreArchivo) const;

    // Generación aleatoria
    void crearRedAleatoria(int numRouters, double probabilidadConexion, int costoMaximo);

    bool estanConectados(string id1, string id2) const;
};

#endif
