#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

struct Nodo {
    int x, y, altura;
};

bool esMovimientoValido(int x, int y, int alturaAnterior, int filas, int columnas, int** grafo, unordered_set<string>& visitados) {
    return x >= 0 && x < filas && y >= 0 && y < columnas &&
           grafo[x][y] == alturaAnterior + 1 &&
           visitados.find(to_string(x) + "," + to_string(y)) == visitados.end();
}

int calcularSenderosDesdeNodo(int inicioX, int inicioY, int filas, int columnas, int** grafo) {
    Nodo* cola = new Nodo[filas * columnas];
    int frente = 0, fondo = 0;

    unordered_set<string> visitados;
    cola[fondo++] = {inicioX, inicioY, 0};
    visitados.insert(to_string(inicioX) + "," + to_string(inicioY));

    int contadorSenderos = 0;

    while (frente < fondo) {
        Nodo actual = cola[frente++];
        
        if (actual.altura == 9) {
            contadorSenderos++;
            continue;
        }

        int direcciones[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < 4; i++) {
            int nuevoX = actual.x + direcciones[i][0];
            int nuevoY = actual.y + direcciones[i][1];

            if (esMovimientoValido(nuevoX, nuevoY, actual.altura, filas, columnas, grafo, visitados)) {
                cola[fondo++] = {nuevoX, nuevoY, grafo[nuevoX][nuevoY]};
                visitados.insert(to_string(nuevoX) + "," + to_string(nuevoY));
            }
        }
    }

    delete[] cola;
    return contadorSenderos;
}

int calcularPuntajeTotalDeSenderos(int filas, int columnas, int** grafo) {
    int puntajeTotal = 0;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (grafo[i][j] == 0) {
                puntajeTotal += calcularSenderosDesdeNodo(i, j, filas, columnas, grafo);
            }
        }
    }

    return puntajeTotal;
}

int main() {
    ifstream archivoEntrada("input10.txt");

    string linea;
    int filas = 0, columnas = 0;

    while (getline(archivoEntrada, linea)) {
        if (columnas == 0) columnas = linea.size();
        filas++;
    }
    archivoEntrada.clear();
    archivoEntrada.seekg(0);

    int** grafo = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        grafo[i] = new int[columnas];
    }

    int fila = 0;
    while (getline(archivoEntrada, linea)) {
        for (int columna = 0; columna < columnas; ++columna) {
            grafo[fila][columna] = linea[columna] - '0';
        }
        fila++;
    }
    archivoEntrada.close();

    int puntajeTotal = calcularPuntajeTotalDeSenderos(filas, columnas, grafo);
    cout << "El puntaje total de los senderos es: " << puntajeTotal << endl;

    for (int i = 0; i < filas; i++) {
        delete[] grafo[i];
    }
    delete[] grafo;

    return 0;
}

