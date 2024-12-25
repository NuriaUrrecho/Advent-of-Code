/*#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// Representa un nodo del árbol binario
struct Node {
    int x, y; // Coordenadas en el mapa
    int height; // Altura del nodo actual

    Node(int x, int y, int height) : x(x), y(y), height(height) {}
};

// Función para verificar si una posición es válida para moverse
bool isValidMove(int x, int y, int prevHeight, const vector<vector<int>>& map, const set<pair<int, int>>& visited) {
    return x >= 0 && x < map.size() && y >= 0 && y < map[0].size() &&
           map[x][y] == prevHeight + 1 && visited.find({x, y}) == visited.end();
}

// BFS para calcular las rutas válidas desde un punto de inicio
int calculateTrails(int startX, int startY, const vector<vector<int>>& map) {
    int rows = map.size();
    int cols = map[0].size();

    queue<Node> q;
    set<pair<int, int>> visited;
    q.push(Node(startX, startY, 0));
    visited.insert({startX, startY});

    int trailCount = 0;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        // Si hemos llegado a una posición con altura 9, incrementamos el contador de rutas
        if (current.height == 9) {
            trailCount++;
            continue;
        }

        // Movimientos posibles: arriba, abajo, izquierda, derecha
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (auto [dx, dy] : directions) {
            int newX = current.x + dx;
            int newY = current.y + dy;

            if (isValidMove(newX, newY, current.height, map, visited)) {
                q.push(Node(newX, newY, map[newX][newY]));
                visited.insert({newX, newY});
            }
        }
    }

    return trailCount;
}

// Función principal para calcular la puntuación de todos los trailheads
int calculateTrailheadScores(const vector<vector<int>>& map) {
    int rows = map.size();
    int cols = map[0].size();

    int totalScore = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == 0) { // Trailhead encontrado
                totalScore += calculateTrails(i, j, map);
            }
        }
    }

    return totalScore;
}

int main() {
    ifstream inputFile("input10.txt");
    if (!inputFile) {
        cerr << "Error: No se pudo abrir el archivo input10.txt" << endl;
        return 1;
    }

    vector<vector<int>> map;
    string line;

    // Leer el archivo y construir el mapa
    while (getline(inputFile, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0'); // Convertir carácter a entero
        }
        map.push_back(row);
    }

    inputFile.close();

    int totalScore = calculateTrailheadScores(map);
    cout << "El puntaje total de los trailheads es: " << totalScore << endl;

    return 0;
}*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

// Define a type for representing a node in the graph
struct Node {
    int x, y; // Coordinates of the node
    int height; // Height value of the node

    Node(int x, int y, int height) : x(x), y(y), height(height) {}
};

// Function to check if moving to a specific node is valid
bool isValidMove(int x, int y, int prevHeight, const vector<vector<int>>& graph, const unordered_set<string>& visited) {
    return x >= 0 && x < graph.size() && y >= 0 && y < graph[0].size() &&
           graph[x][y] == prevHeight + 1 && visited.find(to_string(x) + "," + to_string(y)) == visited.end();
}

// BFS to find all reachable nodes with a height of 9 from a starting node
int calculateTrailsUsingGraph(int startX, int startY, const vector<vector<int>>& graph) {
    queue<Node> q;
    unordered_set<string> visited;

    q.push(Node(startX, startY, 0));
    visited.insert(to_string(startX) + "," + to_string(startY));

    int trailCount = 0;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        // If the current node is at height 9, count it as a trail and continue
        if (current.height == 9) {
            trailCount++;
            continue;
        }

        // Possible moves: up, down, left, right
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (auto [dx, dy] : directions) {
            int newX = current.x + dx;
            int newY = current.y + dy;

            if (isValidMove(newX, newY, current.height, graph, visited)) {
                q.push(Node(newX, newY, graph[newX][newY]));
                visited.insert(to_string(newX) + "," + to_string(newY));
            }
        }
    }

    return trailCount;
}

// Calculate scores for all trailheads in the graph
int calculateTrailheadScoresUsingGraph(const vector<vector<int>>& graph) {
    int totalScore = 0;

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[0].size(); ++j) {
            if (graph[i][j] == 0) { // If it's a trailhead
                totalScore += calculateTrailsUsingGraph(i, j, graph);
            }
        }
    }

    return totalScore;
}

int main() {
    ifstream inputFile("input10.txt");
    if (!inputFile) {
        cerr << "Error: Could not open the file input10.txt" << endl;
        return 1;
    }

    vector<vector<int>> graph;
    string line;

    // Read the file to construct the graph
    while (getline(inputFile, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0'); // Convert character to integer
        }
        graph.push_back(row);
    }

    inputFile.close();

    int totalScore = calculateTrailheadScoresUsingGraph(graph);
    cout << "The total score of the trailheads is: " << totalScore << endl;

    return 0;
}
