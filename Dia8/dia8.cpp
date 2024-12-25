#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set> // LibrerÃ­a HashTable (apuntes pÃ¡g 18)
#include <cmath>
#include <algorithm>

using namespace std;

// Estructura para representar una antena
struct Antena {
    int x, y;
    char frequency;
};

// Calcular distancia de Manhattan
int manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Verificar si tres puntos son colineales
bool areCollinear(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (long long)(y2 - y1) * (x3 - x2) == (long long)(y3 - y2) * (x2 - x1);
}

// FunciÃ³n optimizada para encontrar antinodos utilizando tablas hash
int findAntiNodes(const vector<vector<char>>& grid) {
    vector<Antena> antenas;
    int rows = grid.size();
    int cols = grid[0].size();

    // Recolectar todas las antenas
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (isalnum(grid[y][x])) {
                antenas.push_back({x, y, grid[y][x]});
            }
        }
    }

    // Tabla hash para almacenar ubicaciones Ãºnicas de antinodos
    unordered_set<string> antiNodes;

    // Verificar todos los pares de antenas
    for (size_t i = 0; i < antenas.size(); ++i) {
        for (size_t j = i + 1; j < antenas.size(); ++j) {
            if (antenas[i].frequency == antenas[j].frequency) {
                int dx = antenas[j].x - antenas[i].x;
                int dy = antenas[j].y - antenas[i].y;

                // Calcular posibles ubicaciones de antinodos
                vector<pair<int, int>> potentialAntiNodes = {
                    {antenas[i].x - dx, antenas[i].y - dy},
                    {antenas[j].x + dx, antenas[j].y + dy}
                };

                for (const auto& antiNode : potentialAntiNodes) {
                    int ax = antiNode.first;
                    int ay = antiNode.second;

                    // Verificar si el antinodo estÃ¡ dentro de los lÃ­mites de la cuadrÃ­cula
                    if (ax >= 0 && ax < cols && ay >= 0 && ay < rows) {
                        // Verificar si el antinodo estÃ¡ en lÃ­nea y a la distancia correcta
                        if (areCollinear(antenas[i].x, antenas[i].y, ax, ay, antenas[j].x, antenas[j].y)) {
                            int dist1 = manhattanDistance(antenas[i].x, antenas[i].y, ax, ay);
                            int dist2 = manhattanDistance(ax, ay, antenas[j].x, antenas[j].y);

                            // Verificar que la distancia sea el doble
                            if (abs(dist1 - dist2 * 2) < 1e-9 || abs(dist2 - dist1 * 2) < 1e-9) {
                                antiNodes.insert(to_string(ax) + "," + to_string(ay));
                            }
                        }
                    }
                }
            }
        }
    }

    return antiNodes.size();
}

int main() {
    ifstream input("input8.txt");
    if (!input) {
        cerr << "No se pudo abrir el archivo de entrada" << endl;
        return 1;
    }

    vector<vector<char>> grid;
    string line;
    while (getline(input, line)) {
        grid.push_back(vector<char>(line.begin(), line.end()));
    }

    int result = findAntiNodes(grid);
    cout << "NÃºmero de ubicaciones Ãºnicas de antinodos: " << result << endl;

    return 0;
}