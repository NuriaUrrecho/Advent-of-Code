#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// Función para construir el grafo de las reglas
unordered_map<int, vector<int>> construirGrafo(const vector<string>& reglas) {
    unordered_map<int, vector<int>> grafo;
    for (const string& regla : reglas) {
        stringstream ss(regla);
        int x, y;
        char sep;
        ss >> x >> sep >> y; // Parsear la regla "X|Y"
        grafo[x].push_back(y);
    }
    return grafo;
}

// Función para verificar si una actualización está en el orden correcto
bool esOrdenCorrecto(const unordered_map<int, vector<int>>& grafo, const vector<int>& actualizacion) {
    unordered_map<int, int> posiciones;
    for (size_t i = 0; i < actualizacion.size(); ++i) {
        posiciones[actualizacion[i]] = i;
    }

    for (const auto& [x, destinos] : grafo) {
        if (posiciones.find(x) != posiciones.end()) {
            for (int y : destinos) {
                if (posiciones.find(y) != posiciones.end() && posiciones[x] > posiciones[y]) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Función para calcular el número central de una actualización
int calcularCentro(const vector<int>& actualizacion) {
    return actualizacion[actualizacion.size() / 2];
}

int main() {
    ifstream archivo("input.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo 'input.txt'" << endl;
        return 1;
    }

    vector<string> reglas;
    vector<string> actualizaciones;
    string linea;

    // Leer las reglas de ordenación
    while (getline(archivo, linea)) {
        if (linea.empty()) break; // Las reglas terminan con una línea vacía
        reglas.push_back(linea);
    }

    // Leer las actualizaciones
    while (getline(archivo, linea)) {
        actualizaciones.push_back(linea);
    }

    archivo.close();

    unordered_map<int, vector<int>> grafo = construirGrafo(reglas);
    int sumaCentros = 0;

    // Procesar cada actualización
    for (const string& actualizacionStr : actualizaciones) {
        vector<int> actualizacion;
        stringstream ss(actualizacionStr);
        string token;

        // Parsear la lista de páginas
        while (getline(ss, token, ',')) {
            actualizacion.push_back(stoi(token));
        }

        // Verificar si la actualización está en orden correcto
        if (esOrdenCorrecto(grafo, actualizacion)) {
            sumaCentros += calcularCentro(actualizacion);
        }
    }

    // Imprimir el resultado
    cout << "La suma de los números de página centrales es: " << sumaCentros << endl;

    return 0;
}
