#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set> //Apuntes p.18 (Tabla Hash)
using namespace std;

// Estructura de la antena
struct Antena {
    int x, y;
    char frecuencia;
};

// Calcula la distancia de Manhattan entre dos puntos
int distanciaManhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Valida si tres puntos son colineales
bool sonColineales(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (long long)(y2 - y1) * (x3 - x2) == (long long)(y3 - y2) * (x2 - x1);
}

// Encuentra ubicaciones únicas de antinodos en una cuadrilla
int encontrarAntinodos(string* cuadrilla, int filas, int columnas) {
    Antena* antenas = new Antena[filas * columnas];
    int cantidadAntenas = 0;

    // Identifica todas las antenas en la cuadrilla
    for (int y = 0; y < filas; y++) {
        for (int x = 0; x < columnas; x++) {
            if (isalnum(cuadrilla[y][x])) {
                antenas[cantidadAntenas++] = {x, y, cuadrilla[y][x]};
            }
        }
    }
    // Almacena las coordenadas únicas de los antinodos
    unordered_set<string> antinodos;

    // Compara pares de antenas para buscar posibles antinodos
    for (int i = 0; i < cantidadAntenas; i++) {
        for (int j = i + 1; j < cantidadAntenas; j++) {
            if (antenas[i].frecuencia == antenas[j].frecuencia) {
                int dx = antenas[j].x - antenas[i].x;
                int dy = antenas[j].y - antenas[i].y;

                int posiblesX[] = {antenas[i].x - dx, antenas[j].x + dx};
                int posiblesY[] = {antenas[i].y - dy, antenas[j].y + dy};

                // Verifica las dos posiciones del antinodo
                for (int k = 0; k < 2; k++) {
                    int ax = posiblesX[k];
                    int ay = posiblesY[k];

                    // Comprueba si las coordenadas están dentro de los límites
                    if (ax >= 0 && ax < columnas && ay >= 0 && ay < filas) {
                        if (sonColineales(antenas[i].x, antenas[i].y, ax, ay, antenas[j].x, antenas[j].y)) {
                            int dist1 = distanciaManhattan(antenas[i].x, antenas[i].y, ax, ay);
                            int dist2 = distanciaManhattan(ax, ay, antenas[j].x, antenas[j].y);

                            // Comprueba si las distancias son proporcionales
                            if (abs(dist1 - dist2 * 2) < 1e-9 || abs(dist2 - dist1 * 2) < 1e-9) {
                                antinodos.insert(to_string(ax) + "," + to_string(ay));
                            }
                        }
                    }
                }
            }
        }
    }

    delete[] antenas;
    return antinodos.size();
}

int main() {
    ifstream entrada("input8.txt");

    string* cuadrilla = new string[100];
    int filas = 0;
    string linea;

    // Leer la cuadrilla desde el archivo
    while (getline(entrada, linea)) {
        cuadrilla[filas++] = linea;
    }

    int columnas = cuadrilla[0].size(); // Asumimos que todas las filas tienen la misma longitud
    int resultado = encontrarAntinodos(cuadrilla, filas, columnas);
    cout << "Número de ubicaciones únicas de antinodos: " << resultado << endl;

    delete[] cuadrilla;
    return 0;
}
