#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Estructura del nodo del árbol
struct Nodo {
    int dato;
    Nodo *der;
    Nodo *izq;
};

// Prototipos de las funciones
Nodo *crearNodo(int);
void insertarNodo(Nodo*&, int);
int sumarNodos(Nodo*);

// Constante límite para manejar las listas
const int MAX_OPERACIONES = 100;

// Función para crear un nodo del árbol
Nodo *crearNodo(int n) {
    Nodo *nuevo_nodo = new Nodo(); 
    nuevo_nodo->dato = n; 
    nuevo_nodo->der = nullptr;
    nuevo_nodo->izq = nullptr;
    return nuevo_nodo;
}

// Función para insertar un nodo en el árbol
void insertarNodo(Nodo*& arbol, int n) {
    if (arbol == nullptr) {
        // Si el árbol está vacío crea un nodo como raíz
        Nodo *nuevo_nodo = crearNodo(n);
        arbol = nuevo_nodo;
    } else {
        int valorRaiz = arbol->dato; // Obtiene el valor de la raíz
        // Se inserta n en el subárbol izq o der según si es < o >=
        if (n < valorRaiz) {
            insertarNodo(arbol->izq, n);
        } else {
            insertarNodo(arbol->der, n);
        }
    }
}

// Función para sumar los valores de todos los nodos
int sumarNodos(Nodo* arbol) {
    if (arbol == nullptr) {
        return 0;
    }
    return arbol->dato + sumarNodos(arbol->izq) + sumarNodos(arbol->der);
}

// Comprueba si un string representa un número válido
bool esNumeroValido(const string& str) {
    if (str.empty()) return false;

    size_t i = 0;
    if (str[0] == '-') i++; 
    // Verifica que los caracteres sean dígitos
    for (; i < str.size(); ++i) {
        if (!isdigit(str[i])) return false; 
    }
    return true;
}

// Procesa las operaciones mul() y obtiene el resultado final
void operacionMul(ifstream& inputFile, Nodo*& arbol) {
    string line;
    while (getline(inputFile, line)) {
        size_t pos = 0;
        while ((pos = line.find("mul(", pos)) != string::npos) {
            size_t start = pos + 4; // Posición inicial después de mul(
            size_t comma = line.find(',', start);
            size_t end = line.find(')', start);

            if (comma != string::npos && end != string::npos && comma < end) {
                // Extrae los dos números entre los paréntesis
                string num1 = line.substr(start, comma - start);
                string num2 = line.substr(comma + 1, end - comma - 1);

                // Comprueba que ambos números sean validos
                if (esNumeroValido(num1) && esNumeroValido(num2)) {
                    try {
                        int x = stoi(num1);
                        int y = stoi(num2);
                        // Multiplica los dos números e inserta el resultado en el árbol
                        int resultado = x * y;
                        insertarNodo(arbol, resultado);
                    } catch (...) {
                        
                    }
                }
            }
            pos += 4; // Avanza para buscar el siguiente mul(
        }
    }
}

int main() {
    ifstream inputFile("input3.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    Nodo *arbol = nullptr; // Incializa el árbol

    operacionMul(inputFile, arbol); 

    int sumaTotal = sumarNodos(arbol);
    cout << "Suma total: " << sumaTotal << endl;

    inputFile.close();
    return 0;
}
