#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void dividirNumero(long long numero, string*& nuevasPiedras, int& nuevoTamano, int& nuevaCapacidad) {
    string numCadena = to_string(numero);
    int mitad = numCadena.size() / 2;

    string izquierda = numCadena.substr(0, mitad);
    string derecha = numCadena.substr(mitad);

    long long izq;
    if (izquierda.empty()) {
        izq = 0;
    } else {
        izq = stoll(izquierda);
    }

    long long der;
    if (derecha.empty()) {
        der = 0;
    } else {
        der = stoll(derecha);
    }

    if (nuevoTamano + 2 > nuevaCapacidad) {
        nuevaCapacidad *= 2;
        string* temp = new string[nuevaCapacidad];
        for (int i = 0; i < nuevoTamano; ++i) {
            temp[i] = nuevasPiedras[i];
        }
        delete[] nuevasPiedras;
        nuevasPiedras = temp;
    }

    nuevasPiedras[nuevoTamano++] = to_string(izq);
    nuevasPiedras[nuevoTamano++] = to_string(der);
}

void transformarPiedras(string* piedras, int tamano, string*& nuevasPiedras, int& nuevoTamano, int& nuevaCapacidad) {
    nuevoTamano = 0;
    for (int i = 0; i < tamano; ++i) {
        long long piedra = stoll(piedras[i]);

        if (piedra == 0) {
            if (nuevoTamano >= nuevaCapacidad) {
                nuevaCapacidad *= 2;
                string* temp = new string[nuevaCapacidad];
                for (int j = 0; j < nuevoTamano; ++j) {
                    temp[j] = nuevasPiedras[j];
                }
                delete[] nuevasPiedras;
                nuevasPiedras = temp;
            }
            nuevasPiedras[nuevoTamano++] = "1";
        } else if (to_string(piedra).size() % 2 == 0) {
            dividirNumero(piedra, nuevasPiedras, nuevoTamano, nuevaCapacidad);
        } else {
            if (nuevoTamano >= nuevaCapacidad) {
                nuevaCapacidad *= 2;
                string* temp = new string[nuevaCapacidad];
                for (int j = 0; j < nuevoTamano; ++j) {
                    temp[j] = nuevasPiedras[j];
                }
                delete[] nuevasPiedras;
                nuevasPiedras = temp;
            }
            nuevasPiedras[nuevoTamano++] = to_string(piedra * 2024);
        }
    }
}

int main() {
    ifstream entrada("input11.txt");
    if (!entrada) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    string* piedras = new string[100];
    int tamano = 0;
    int capacidad = 100;

    long long numero;
    while (entrada >> numero) {
        if (tamano >= capacidad) {
            capacidad *= 2;
            string* temp = new string[capacidad];
            for (int i = 0; i < tamano; ++i) {
                temp[i] = piedras[i];
            }
            delete[] piedras;
            piedras = temp;
        }
        piedras[tamano++] = to_string(numero);
    }
    entrada.close();

    const int parpadeos = 25;

    for (int i = 0; i < parpadeos; ++i) {
        int nuevaCapacidad = capacidad;
        string* nuevasPiedras = new string[nuevaCapacidad];
        int nuevoTamano = 0;

        transformarPiedras(piedras, tamano, nuevasPiedras, nuevoTamano, nuevaCapacidad);

        delete[] piedras;
        piedras = nuevasPiedras;
        tamano = nuevoTamano;
        capacidad = nuevaCapacidad;
    }

    cout << tamano << endl;

    delete[] piedras;
    return 0;
}


