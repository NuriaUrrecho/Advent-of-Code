#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Nodo {
    int dato;
    Nodo *der;
    Nodo *izq;
};

Nodo *crearNodo(int);
void insertarNodo(Nodo*&, int);
int sumarNodos(Nodo*);

const int MAX_OPERACIONES = 100;

Nodo *crearNodo(int n) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->der = nullptr;
    nuevo_nodo->izq = nullptr;
    return nuevo_nodo;
}

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

int sumarNodos(Nodo* arbol) {
    if (arbol == nullptr) {
        return 0;
    }
    return arbol->dato + sumarNodos(arbol->izq) + sumarNodos(arbol->der);
}

bool esNumeroValido(const string& str) {
    if (str.empty()) return false;

    size_t i = 0;
    if (str[0] == '-') i++; 

    for (; i < str.size(); ++i) {
        if (!isdigit(str[i])) return false; 
    }

    return true;
}

void operacionMul(ifstream& inputFile, Nodo*& arbol) {
    string line;
    while (getline(inputFile, line)) {
        size_t pos = 0;
        while ((pos = line.find("mul(", pos)) != string::npos) {
            size_t start = pos + 4; 
            size_t comma = line.find(',', start);
            size_t end = line.find(')', start);

            if (comma != string::npos && end != string::npos && comma < end) {
                string num1 = line.substr(start, comma - start);
                string num2 = line.substr(comma + 1, end - comma - 1);

                if (esNumeroValido(num1) && esNumeroValido(num2)) {
                    try {
                        int x = stoi(num1);
                        int y = stoi(num2);
                        int resultado = x * y;
                        insertarNodo(arbol, resultado);
                    } catch (...) {
                        
                    }
                }
            }
            pos += 4;
        }
    }
}

int main() {
    ifstream inputFile("input3.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    Nodo *arbol = nullptr;

    operacionMul(inputFile, arbol);

    int sumaTotal = sumarNodos(arbol);
    cout << "Suma total: " << sumaTotal << endl;

    inputFile.close();
    return 0;
}
