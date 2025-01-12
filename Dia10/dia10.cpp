#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

// Estructura de un nodo del grafo
struct Nodo {
    int x, y, altura;
};

// Verifica si un movimeinto a una nueva posición es válido
bool esMovimientoValido(int x, int y, int alturaAnterior, int filas, int columnas, int** grafo, unordered_set<string>& visitados) {
    // Comprueba que las coordenadas estñan dentro de los límites de la cuadrilla
    bool dentroDeLimites = x >= 0 && x < filas && y >= 0 && y < columnas;
    if (!dentroDeLimites) {
        return false;
    }

    // Comprueba que la altura del nuevo nodo es la anterior + 1
    bool alturaValida = grafo[x][y] == alturaAnterior + 1;
    if (!alturaValida) {
        return false;
    }

    // Comprueba que el nodo no haya sido visitado
    bool noVisitado = visitados.find(to_string(x) + "," + to_string(y)) == visitados.end();
    if (!noVisitado) {
        return false;
    }

    return true;
}

// Calcula el nº de senderos válidos que empiezan en un nodo dado
int calcularSenderosDesdeNodo(int inicioX, int inicioY, int filas, int columnas, int** grafo) {
    // Cola para el algoritmo BFS
    Nodo* cola = new Nodo[filas * columnas];
    int frente = 0, fondo = 0;

    // Conjunto para registrar los nodos visitados
    unordered_set<string> visitados;
    cola[fondo++] = {inicioX, inicioY, 0};
    visitados.insert(to_string(inicioX) + "," + to_string(inicioY));

    int contadorSenderos = 0; // Senderos de altura 9

    // Bucle principal del BFS
    while (frente < fondo) {
        Nodo actual = cola[frente++];

        // Si el nodo alcanza altura 9: sendero completo
        if (actual.altura == 9) {
            contadorSenderos++;
            continue;
        }

        // Direcciones para moverse en la cuadrilla
        int direcciones[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // Explorar los nodos adyacentes
        for (int i = 0; i < 4; i++) {
            int nuevoX = actual.x + direcciones[i][0];
            int nuevoY = actual.y + direcciones[i][1];

            // Comprueba si el movimeinto a la nueva posición es válido
            if (esMovimientoValido(nuevoX, nuevoY, actual.altura, filas, columnas, grafo, visitados)) {
                cola[fondo++] = {nuevoX, nuevoY, grafo[nuevoX][nuevoY]}; // Añade a la cola
                visitados.insert(to_string(nuevoX) + "," + to_string(nuevoY)); // Marca como visitado
            }
        }
    }

    delete[] cola;
    return contadorSenderos; // Devuelve el número de senderos desde el nodo
}

// Calcula el puntaje total sumando los senderos válidos que empiezan en cada nodo
int calcularPuntajeTotalDeSenderos(int filas, int columnas, int** grafo) {
    int puntajeTotal = 0;

    // Recorre los nodos del grafo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            // Empezar BFS desde nodos con altura inicial 0
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

    // Determina el tamaño del grafo
    while (getline(archivoEntrada, linea)) {
        if (columnas == 0) columnas = linea.size();
        filas++;
    }
    archivoEntrada.clear();
    archivoEntrada.seekg(0); // Vuelve al inicio del archivo

    // Crea un grafo según el tamaño
    int** grafo = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        grafo[i] = new int[columnas];
    }

    // Rellena el grafo con los datos del input
    int fila = 0;
    while (getline(archivoEntrada, linea)) {
        for (int columna = 0; columna < columnas; ++columna) {
            grafo[fila][columna] = linea[columna] - '0'; // Convierte caracteres a enteros
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

