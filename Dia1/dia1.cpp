#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void cargar(int*& arreglo1, int*& arreglo2, int& tamano) {
    ifstream archivo("input.txt");

    tamano = 0;
    string linea;

    while (getline(archivo, linea)) {
        tamano++;
    }

    archivo.clear();
    archivo.seekg(0, ios::beg);

    arreglo1 = new int[tamano];
    arreglo2 = new int[tamano];

    int indice = 0;
    while (getline(archivo, linea)) {
        int valor1, valor2;
        sscanf(linea.c_str(), "%d %d", &valor1, &valor2);
        arreglo1[indice] = valor1;
        arreglo2[indice] = valor2;
        indice++;
    }

    archivo.close();
}

void selectionsort(int* arreglo, int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        int minimo = i;
        for (int j = i + 1; j < tamano; j++) {
            if (arreglo[j] < arreglo[minimo]) {
                minimo = j;
            }
        }
        int temporal = arreglo[i];
        arreglo[i] = arreglo[minimo];
        arreglo[minimo] = temporal;
    }
}

int main() {
    int* arreglo1 = nullptr;
    int* arreglo2 = nullptr;
    int tamano = 0;

    cargar(arreglo1, arreglo2, tamano);

    selectionsort(arreglo1, tamano);
    selectionsort(arreglo2, tamano);

    int suma = 0;
    for (int i = 0; i < tamano; i++) {
        int diferencia = (arreglo1[i] > arreglo2[i]) ? (arreglo1[i] - arreglo2[i]) : (arreglo2[i] - arreglo1[i]);
        suma += diferencia;
    }

    cout << suma << endl;

    delete[] arreglo1;
    delete[] arreglo2;

    return 0;
}

