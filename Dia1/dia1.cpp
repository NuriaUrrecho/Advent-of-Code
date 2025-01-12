#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Implementación del InsertionSort
void insertionSort(int* arreglo, int tamano) {
    for (int i = 1; i < tamano; i++) { // Recorrer desde el segundo elemento hasta el final
        int actual = arreglo[i]; // Guardar el valor actual
        int j = i - 1;  // Inicializar el índice para comparar

        // Mover los elementos mayores que v hacia adelante
        while (j >= 0 && arreglo[j] > actual) {
            arreglo[j + 1] = arreglo[j];
            j--;
        }

        // Insertar el valor actual en la posición correcta
        arreglo[j + 1] = actual;
    }
}

int main() {
    ifstream archivo("input.txt");
    string linea;

    int tamano = 0;

    // Determinar el nº de líneas del archivo
    while (getline(archivo, linea)) {
        tamano++;
    }

    archivo.close();
    archivo.open("input.txt");

    // Arreglos dinámicos para almacenar los datos
    int* arreglo1 = new int[tamano];
    int* arreglo2 = new int[tamano];

    int indice = 0;

    // Dividir los datos en dos arreglos
    while (getline(archivo, linea)) {
        int valor1, valor2;
        // Extraer dos valores de cada línea
        sscanf(linea.c_str(), "%d %d", &valor1, &valor2);
        arreglo1[indice] = valor1;
        arreglo2[indice] = valor2;
        indice++;
    }

    archivo.close();

    // Ordenar cada arreglo
    insertionSort(arreglo1, tamano);
    insertionSort(arreglo2, tamano);

    int suma = 0;

    // Calcula diferencia entre los elementos de los dos arreglos
    for (int i = 0; i < tamano; i++) {
        int diferencia;
        if (arreglo1[i] > arreglo2[i]) {
            diferencia = arreglo1[i] - arreglo2[i];
        } else {
            diferencia = arreglo2[i] - arreglo1[i];
        }
        suma += diferencia; // acumular la suma
    }

    cout << suma << endl;

    delete[] arreglo1;
    delete[] arreglo2;

    return 0;
}
