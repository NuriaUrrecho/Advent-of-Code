/*
ADVENT OF CODE (DÍA 1) 
Suma de la diferencia numérica entre dos listas
______________________________________________________________________

MIEMBROS: Nuria Urrecho Torres, Iván Rejas Cuevas y Rubén Pérez Gracia

*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath> // Para abs
using namespace std;

// Función para cargar datos desde el archivo
void load(vector<int> &v1, vector<int> &v2) {
    ifstream file("input.txt");
    string line, data;
    while (getline(file, line)) {
        stringstream iss(line);
        // Convertir string a int usando stringstream    
        iss >> data;
        v1.push_back(stoi(data));
        iss >> data;
        v2.push_back(stoi(data));
    }
}

// Implementación del SelectionSort
void selectionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minId = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minId]) {
                minId = j;
            }
        }
        // Intercambiar el elemento actual con el menor
        swap(arr[i], arr[minId]);
    }
}

int main() {
    vector<int> v1, v2;

    // Leer el archivo línea por línea y almacenarlo en dos vectores
    load(v1, v2);

    // Ordenar los vectores utilizando nuestra función de ordenamiento
    selectionSort(v1);
    selectionSort(v2);

    // Calcular la suma de las diferencias
    int sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        cout << v1[i] << " " << v2[i] << " " << abs(v1[i] - v2[i]) << endl;
        sum += abs(v2[i] - v1[i]);
    }

    // Imprimir la suma total
    cout << "Suma total de diferencias: " << sum << endl;
    return 0;
}

