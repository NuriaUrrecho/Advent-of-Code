#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

// Estructura para representar una antena
struct Antenna {
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

int findAntiNodes(const vector<vector<char>>& grid) {
    vector<Antenna> antennas;
    int rows = grid.size();
    int cols = grid[0].size();

    // Recolectar todas las antenas
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (isalnum(grid[y][x])) {
                antennas.push_back({x, y, grid[y][x]});
            }
        }
    }

    // Conjunto para almacenar ubicaciones únicas de antinodos
    set<pair<int, int>> antiNodes;

    // Verificar todos los pares de antenas
    for (size_t i = 0; i < antennas.size(); ++i) {
        for (size_t j = i + 1; j < antennas.size(); ++j) {
            // Solo considerar antenas con la misma frecuencia
            if (antennas[i].frequency == antennas[j].frequency) {
                int dx = antennas[j].x - antennas[i].x;
                int dy = antennas[j].y - antennas[i].y;
                
                // Calcular posibles ubicaciones de antinodos
                vector<pair<int, int>> potentialAntiNodes = {
                    {antennas[i].x - dx, antennas[i].y - dy},
                    {antennas[j].x + dx, antennas[j].y + dy}
                };

                for (const auto& antiNode : potentialAntiNodes) {
                    int ax = antiNode.first;
                    int ay = antiNode.second;

                    // Verificar si el antinodo está dentro de los límites de la cuadrícula
                    if (ax >= 0 && ax < cols && ay >= 0 && ay < rows) {
                        // Verificar si el antinodo está en línea y a la distancia correcta
                        if (areCollinear(antennas[i].x, antennas[i].y, 
                                         ax, ay, 
                                         antennas[j].x, antennas[j].y)) {
                            int dist1 = manhattanDistance(antennas[i].x, antennas[i].y, ax, ay);
                            int dist2 = manhattanDistance(ax, ay, antennas[j].x, antennas[j].y);
                            
                            // Verificar que la distancia sea el doble
                            if (abs(dist1 - dist2 * 2) < 1e-9 || abs(dist2 - dist1 * 2) < 1e-9) {
                                antiNodes.insert({ax, ay});
                            }
                        }
                    }
                }
            }
        }
    }

    // Añadir ubicaciones de antenas con antinodos
    for (const auto& antenna : antennas) {
        for (const auto& antiNode : antiNodes) {
            if (antiNode.first == antenna.x && antiNode.second == antenna.y) {
                antiNodes.insert({antenna.x, antenna.y});
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
    cout << "Número de ubicaciones únicas de antinodos: " << result << endl;

    return 0;
}