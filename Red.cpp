#include "Red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>
#include <random>

Red::~Red() {
    limpiarRed();
}

void Red::agregarEnrutador(string id) {
    if (enrutadores.find(id) == enrutadores.end()) {
        enrutadores[id] = new Enrutador(id);
        cout << "Enrutador " << id << " agregado exitosamente." << endl;
    } else {
        cout << "El enrutador " << id << " ya existe." << endl;
    }
}

void Red::eliminarEnrutador(string id) {
    auto it = enrutadores.find(id);
    if (it != enrutadores.end()) {
        // Remover este enrutador de las listas de vecinos de otros routers
        for (auto& par : enrutadores) {
            if (par.first != id) {
                auto& vecinos = par.second->vecinos;
                vecinos.erase(
                    remove_if(vecinos.begin(), vecinos.end(),
                              [&](auto& conexion) { return conexion.first == it->second; }),
                    vecinos.end()
                    );
            }
        }

        // Liberar memoria y eliminar del mapa
        delete it->second;
        enrutadores.erase(it);
        cout << "Enrutador " << id << " eliminado exitosamente." << endl;
    } else {
        cout << "El enrutador " << id << " no existe." << endl;
    }
}

void Red::conectar(string id1, string id2, int costo) {
    if (enrutadores.find(id1) == enrutadores.end()) {
        cout << "Error: El enrutador " << id1 << " no existe." << endl;
        return;
    }
    if (enrutadores.find(id2) == enrutadores.end()) {
        cout << "Error: El enrutador " << id2 << " no existe." << endl;
        return;
    }
    if (costo <= 0) {
        cout << "Error: El costo debe ser un valor positivo." << endl;
        return;
    }

    Enrutador* r1 = enrutadores[id1];
    Enrutador* r2 = enrutadores[id2];

    // Verificar si ya están conectados
    for (const auto& conexion : r1->vecinos) {
        if (conexion.first == r2) {
            cout << "Los enrutadores ya están conectados. Actualizando costo..." << endl;
            // Actualizar costo en ambas direcciones
            for (auto& conexion : r1->vecinos) {
                if (conexion.first == r2) {
                    conexion.second = costo;
                }
            }
            for (auto& conexion : r2->vecinos) {
                if (conexion.first == r1) {
                    conexion.second = costo;
                }
            }
            return;
        }
    }

    // Crear conexión bidireccional
    r1->nuevoVecino(r2, costo);
    r2->nuevoVecino(r1, costo);

    cout << "Conectado " << id1 << " <-> " << id2 << " con costo " << costo << endl;
}

void Red::desconectar(string id1, string id2) {
    if (enrutadores.find(id1) == enrutadores.end() ||
        enrutadores.find(id2) == enrutadores.end()) {
        cout << "Error: Uno o ambos enrutadores no existen." << endl;
        return;
    }

    Enrutador* r1 = enrutadores[id1];
    Enrutador* r2 = enrutadores[id2];

    // Función lambda para eliminar conexión
    auto eliminarConexion = [](Enrutador* origen, Enrutador* destino) {
        auto& vecinos = origen->vecinos;
        vecinos.erase(
            remove_if(vecinos.begin(), vecinos.end(),
                      [&](auto& conexion) { return conexion.first == destino; }),
            vecinos.end()
            );
    };

    eliminarConexion(r1, r2);
    eliminarConexion(r2, r1);

    cout << "Desconectado " << id1 << " <-> " << id2 << endl;
}

void Red::mostrarTopologia() const {
    cout << "\n=== TOPOLOGÍA DE LA RED ===" << endl;
    if (enrutadores.empty()) {
        cout << "La red está vacía." << endl;
        return;
    }

    for (const auto& par : enrutadores) {
        cout << "Enrutador " << par.first << " conectado a:" << endl;
        if (par.second->vecinos.empty()) {
            cout << "  (sin conexiones)" << endl;
        } else {
            for (const auto& conexion : par.second->vecinos) {
                cout << "  -> Enrutador " << conexion.first->idEnrut
                     << " (costo: " << conexion.second << ")" << endl;
            }
        }
    }
    cout << "=============================" << endl;
}

void Red::mostrarCamino(string origen, string destino) const {
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        cout << "Error: Uno o ambos enrutadores no existen." << endl;
        return;
    }

    Enrutador* rOrigen = enrutadores.at(origen);
    Enrutador* rDestino = enrutadores.at(destino);

    auto it = rOrigen->caminos.find(rDestino);
    if (it != rOrigen->caminos.end() && !it->second.empty()) {
        cout << "Camino más corto de " << origen << " a " << destino << ": ";
        for (size_t i = 0; i < it->second.size(); ++i) {
            cout << it->second[i]->idEnrut;
            if (i < it->second.size() - 1) cout << " -> ";
        }
        cout << " | Costo total: " << rDestino->distancia << endl;
    } else {
        cout << "No hay camino disponible de " << origen << " a " << destino << endl;
    }
}

void Red::calcularRutas() {
    if (enrutadores.empty()) {
        cout << "La red está vacía. No hay rutas para calcular." << endl;
        return;
    }

    cout << "\n=== CALCULANDO RUTAS MÁS CORTAS ===" << endl;

    // Convertir el mapa a vector para Dijkstra
    vector<Enrutador*> todos;
    for (const auto& par : enrutadores) {
        todos.push_back(par.second);
    }

    // Ejecutar Dijkstra para cada enrutador como fuente
    for (Enrutador* fuente : todos) {
        dijkstra(fuente, todos);
        fuente->mostrarTabla();
        cout << endl;
    }
    cout << "===================================" << endl;
}

bool Red::existeEnrutador(string id) const {
    return enrutadores.find(id) != enrutadores.end();
}

void Red::limpiarRed() {
    for (auto& par : enrutadores) {
        delete par.second;
    }
    enrutadores.clear();
    cout << "Red limpiada exitosamente." << endl;
}

Enrutador* Red::getEnrutador(string id) const {
    auto it = enrutadores.find(id);
    return (it != enrutadores.end()) ? it->second : nullptr;
}

void Red::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string comando;
        ss >> comando;

        if (comando == "ROUTER") {
            string id;
            if (ss >> id) {
                agregarEnrutador(id);
            }
        }
        else if (comando == "CONNECT") {
            string id1, id2;
            int costo;
            if (ss >> id1 >> id2 >> costo) {
                conectar(id1, id2, costo);
            }
        }
    }
    archivo.close();
    cout << "Topología cargada desde " << nombreArchivo << " exitosamente." << endl;
}

void Red::guardarEnArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    // Guardar enrutadores
    for (const auto& par : enrutadores) {
        archivo << "ROUTER " << par.first << endl;
    }

    // Guardar conexiones (evitando duplicados)
    for (const auto& par1 : enrutadores) {
        for (const auto& conexion : par1.second->vecinos) {
            string id2 = conexion.first->idEnrut;
            if (par1.first < id2) { // Solo guardar una vez por par
                archivo << "CONNECT " << par1.first << " " << id2
                        << " " << conexion.second << endl;
            }
        }
    }

    archivo.close();
    cout << "Topología guardada en " << nombreArchivo << " exitosamente." << endl;
}

void Red::crearRedAleatoria(int numRouters, double probabilidadConexion, int costoMaximo) {
    if (numRouters > 26) {
        cout << "Error: Máximo 26 enrutadores para usar letras A-Z." << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> disProb(0.0, 1.0);
    uniform_int_distribution<> disCosto(1, costoMaximo);

    // Crear routers con letras (A, B, C, ...)
    for (int i = 0; i < numRouters; ++i) {
        string id = string(1, 'A' + i);
        agregarEnrutador(id);
    }

    // Crear conexiones aleatorias
    int conexionesCreadas = 0;
    for (int i = 0; i < numRouters; ++i) {
        for (int j = i + 1; j < numRouters; ++j) {
            if (disProb(gen) < probabilidadConexion) {
                string id1 = string(1, 'A' + i);
                string id2 = string(1, 'A' + j);
                int costo = disCosto(gen);
                conectar(id1, id2, costo);
                conexionesCreadas++;
            }
        }
    }

    cout << "Red aleatoria creada con " << numRouters << " enrutadores y "
         << conexionesCreadas << " conexiones." << endl;
}
