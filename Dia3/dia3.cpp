#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Estructura del nodo del árbol binario
struct Nodo {
    int dato;
    Nodo *der;
    Nodo *izq;
};

// Prototipos de funciones
Nodo *crearNodo(int);
void insertarNodo(Nodo*&, int);
int sumarNodos(Nodo*);

// Constantes para manejar las listas
const int MAX_OPERACIONES = 100;

// Función para crear un nodo del árbol binario
Nodo *crearNodo(int n) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->der = nullptr;
    nuevo_nodo->izq = nullptr;
    return nuevo_nodo;
}

// Función para insertar un nodo en el árbol binario
void insertarNodo(Nodo*& arbol, int n) {
    if (arbol == nullptr) {
        Nodo *nuevo_nodo = crearNodo(n);
        arbol = nuevo_nodo;
    } else {
        int valorRaiz = arbol->dato;
        if (n < valorRaiz) {
            insertarNodo(arbol->izq, n);
        } else {
            insertarNodo(arbol->der, n);
        }
    }
}

// Función para sumar los valores de todos los nodos del árbol
int sumarNodos(Nodo* arbol) {
    if (arbol == nullptr) {
        return 0;
    }
    return arbol->dato + sumarNodos(arbol->izq) + sumarNodos(arbol->der);
}

// Validar si un string representa un número válido
bool esNumeroValido(const string& str) {
    if (str.empty()) return false;

    size_t i = 0;
    if (str[0] == '-') i++; // Permitir un signo negativo al inicio

    for (; i < str.size(); ++i) {
        if (!isdigit(str[i])) return false; // Verificar que el resto sean dígitos
    }

    return true;
}

// Procesar operaciones mul() y obtener el resultado final
void processMulOperations(ifstream& inputFile, Nodo*& arbol) {
    string line;
    while (getline(inputFile, line)) {
        size_t pos = 0;
        while ((pos = line.find("mul(", pos)) != string::npos) {
            size_t start = pos + 4; // Después de "mul("
            size_t comma = line.find(',', start);
            size_t end = line.find(')', start);

            if (comma != string::npos && end != string::npos && comma < end) {
                string num1 = line.substr(start, comma - start);
                string num2 = line.substr(comma + 1, end - comma - 1);

                // Validar que ambos números sean válidos
                if (esNumeroValido(num1) && esNumeroValido(num2)) {
                    try {
                        int x = stoi(num1);
                        int y = stoi(num2);
                        int resultado = x * y;
                        insertarNodo(arbol, resultado); // Insertar el resultado en el árbol
                    } catch (...) {
                        // Si ocurre un error inesperado, no se hace nada
                    }
                }
            }
            pos += 4; // Avanzar para buscar el siguiente "mul("
        }
    }
}

int main() {
    ifstream inputFile("input3.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    Nodo *arbol = nullptr; // Inicializar el árbol binario vacío

    processMulOperations(inputFile, arbol); // Procesar las operaciones de multiplicación

    int sumaTotal = sumarNodos(arbol); // Sumar los valores de todos los nodos del árbol
    cout << "Suma total: " << sumaTotal << endl; // Imprimir solo el resultado final

    inputFile.close(); // Cerrar el archivo de entrada
    return 0;
}