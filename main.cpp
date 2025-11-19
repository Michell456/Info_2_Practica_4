#include "Red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <string>
#include <limits>

using namespace std;

void cargarDesdeArchivo(Red& red, const string& nombreArchivo) {
    red.cargarDesdeArchivo(nombreArchivo);
}

void crearRedAleatoria(Red& red, int numRouters, double probabilidadConexion, int costoMaximo) {
    red.crearRedAleatoria(numRouters, probabilidadConexion, costoMaximo);
}

void mostrarMenu() {
    cout << "\n=== SIMULADOR DE RED DE ENRUTADORES ===\n" << endl;
    cout << "1. Cargar topologia desde archivo" << endl;
    cout << "2. Crear red aleatoria" << endl;
    cout << "3. Agregar enrutador" << endl;
    cout << "4. Eliminar enrutador" << endl;
    cout << "5. Conectar enrutadores" << endl;
    cout << "6. Desconectar enrutadores" << endl;
    cout << "7. Mostrar topologia" << endl;
    cout << "8. Calcular rutas mas cortas" << endl;
    cout << "9. Mostrar camino entre dos enrutadores" << endl;
    cout << "10. Guardar topologia en archivo" << endl;
    cout << "11. Limpiar red" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Red red;
    int opcion;

    do {
        mostrarMenu();

        if (!(cin >> opcion)) {
            cout << "Error: Por favor ingrese un numero valido." << endl;
            limpiarBuffer();
            continue;
        }

        if (opcion == 1) {
            string nombreArchivo;
            cout << "Ingrese el nombre del archivo: ";
            cin >> nombreArchivo;
            cargarDesdeArchivo(red, nombreArchivo);
        }
        else if (opcion == 2) {
            int numRouters, costoMaximo;
            double probabilidad;
            cout << "Numero de enrutadores (max 26): ";
            if (!(cin >> numRouters)) {
                cout << "Error: Numero invalido." << endl;
                limpiarBuffer();
            } else {
                cout << "Probabilidad de conexion (0-1): ";
                if (!(cin >> probabilidad)) {
                    cout << "Error: Probabilidad invalida." << endl;
                    limpiarBuffer();
                } else {
                    cout << "Costo maximo: ";
                    if (!(cin >> costoMaximo)) {
                        cout << "Error: Costo maximo invalido." << endl;
                        limpiarBuffer();
                    } else {
                        crearRedAleatoria(red, numRouters, probabilidad, costoMaximo);
                    }
                }
            }
        }
        else if (opcion == 3) {
            string id;
            cout << "ID del nuevo enrutador (ej: A, B, C, R1, etc.): ";
            if (!(cin >> id)) {
                cout << "Error: ID invalido." << endl;
                limpiarBuffer();
            } else {
                red.agregarEnrutador(id);
            }
        }
        else if (opcion == 4) {
            string id;
            cout << "ID del enrutador a eliminar: ";
            if (!(cin >> id)) {
                cout << "Error: ID invalido." << endl;
                limpiarBuffer();
            } else {
                red.eliminarEnrutador(id);
            }
        }
        else if (opcion == 5) {
            string id1, id2;
            int costo;
            cout << "ID del primer enrutador: ";
            if (!(cin >> id1)) {
                cout << "Error: ID invalido." << endl;
                limpiarBuffer();
            } else {
                cout << "ID del segundo enrutador: ";
                if (!(cin >> id2)) {
                    cout << "Error: ID invalido." << endl;
                    limpiarBuffer();
                } else {
                    cout << "Costo del enlace: ";
                    if (!(cin >> costo)) {
                        cout << "Error: Costo invalido." << endl;
                        limpiarBuffer();
                    } else {
                        red.conectar(id1, id2, costo);
                    }
                }
            }
        }
        else if (opcion == 6) {
            string id1, id2;
            cout << "ID del primer enrutador: ";
            if (!(cin >> id1)) {
                cout << "Error: ID invalido." << endl;
                limpiarBuffer();
            } else {
                cout << "ID del segundo enrutador: ";
                if (!(cin >> id2)) {
                    cout << "Error: ID invalido." << endl;
                    limpiarBuffer();
                } else {
                    red.desconectar(id1, id2);
                }
            }
        }
        else if (opcion == 7) {
            red.mostrarTopologia();
        }
        else if (opcion == 8) {
            red.calcularRutas();
        }
        else if (opcion == 9) {
            string origen, destino;
            cout << "ID del enrutador origen: ";
            if (!(cin >> origen)) {
                cout << "Error: ID invalido." << endl;
                limpiarBuffer();
            } else {
                cout << "ID del enrutador destino: ";
                if (!(cin >> destino)) {
                    cout << "Error: ID invalido." << endl;
                    limpiarBuffer();
                } else {
                    red.mostrarCamino(origen, destino);
                }
            }
        }
        else if (opcion == 10) {
            string nombreArchivo;
            cout << "Ingrese el nombre del archivo para guardar: ";
            cin >> nombreArchivo;
            red.guardarEnArchivo(nombreArchivo);
        }
        else if (opcion == 11) {
            red.limpiarRed();
        }
        else if (opcion == 0) {
            cout << "Saliendo del programa..." << endl;
        }
        else {
            cout << "Opcion no valida Por favor ingrese una opcion entre 0 y 11." << endl;
        }

        limpiarBuffer();

    } while (opcion != 0);

    return 0;
}
