#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Estructura de un array de cadenas y su tamaño
struct Resultado {
    string* valores;
    int tamano;
};

// Estructura de la memoria
struct MemoEntry {
    long long clave;
    Resultado resultado;
};

// Clase para implementar una memoria
class Memo {
private:
    MemoEntry* entries;
    int capacidad;
    int tamano;

    // Método para expandir la capacidad de la memoria
    void expandir() {
        capacidad *= 2;
        MemoEntry* nuevos = new MemoEntry[capacidad]; // Nuevo array con mayor capacidad
        for (int i = 0; i < tamano; i++) {
            nuevos[i] = entries[i]; // Copia los elementos antiguos
        }
        // Libera el array antiguo y lo reemplaza por el nuevo
        delete[] entries;
        entries = nuevos;
    }

public:
    // Inicializa constructor con capacidad 100
    Memo() : capacidad(100), tamano(0) {
        entries = new MemoEntry[capacidad];
    }

    // Destructor para liberar la memoria dinámica
    ~Memo() {
        for (int i = 0; i < tamano; i++) {
            delete[] entries[i].resultado.valores; // Libera cad array en las entradas
        }
        delete[] entries;
    }

    // Busca si una clave ya está almacenada en memoria
    bool buscar(long long clave, Resultado& resultado) {
        for (int i = 0; i < tamano; i++) {
            // Si la clave coincide retorna el resultado asociado
            if (entries[i].clave == clave) {
                resultado = entries[i].resultado;
                return true;
            }
        }
        return false;
    }

    // Agrega una nueva entrada en la memoria
    void agregar(long long clave, Resultado resultado) {
        if (tamano >= capacidad) {
            expandir();
        }
        entries[tamano++] = {clave, resultado}; // Inserta la entrada
    }
};

// Divide un número en dos mitades y las devuelve como cadenas
Resultado dividirNumero(long long numero) {
    string numCadena = to_string(numero); // Convierte a cadena
    int mitad = numCadena.size() / 2; 

    // División en dos mitades
    string izquierda = numCadena.substr(0, mitad);
    string derecha = numCadena.substr(mitad);

    // Convierte las partes a enteros
    long long izq;
    if (izquierda.empty()) {
        izq = 0;
    } else {
        izq = stoll(izquierda);
    }

    
    long long der;
    if (derecha.empty()) {
        der = 0;
    } else {
        der = stoll(derecha);
    }

    // Crea el array resultado con las dos mitades
    string* resultado = new string[2];
    resultado[0] = to_string(izq);
    resultado[1] = to_string(der);

    return {resultado, 2}; // Resultado con el array y el tamaño
}

// Transforma una piedra mediante mediante memoria
Resultado transformarPiedra(long long piedra, Memo& memo) {
    Resultado resultadoMemo;
    //Si el valor ya estaba en memoria
    if (memo.buscar(piedra, resultadoMemo)) {
        return resultadoMemo;
    }

    // Caso base: la piedra es 0
    if (piedra == 0) {
        string* resultado = new string[1]{"1"};
        memo.agregar(piedra, {resultado, 1});
        return {resultado, 1};
    }

    // Si el número tiene longitud par se divide en dos
    if (to_string(piedra).size() % 2 == 0) {
        Resultado resultadoDividir = dividirNumero(piedra);
        memo.agregar(piedra, resultadoDividir);
        return resultadoDividir;
    } else { // Si no, se multiplica por 2024
        string* resultado = new string[1]{to_string(piedra * 2024)};
        memo.agregar(piedra, {resultado, 1});
        return {resultado, 1};
    }
}

// Hace la transformación recursiva de las piedras
void transformarRecursivo(string* piedras, int tamano, int parpadeos, string*& resultadoFinal, int& tamanoFinal, Memo& memo) {
    if (parpadeos == 0) { // Caso base: no quedan más parpadeos
        resultadoFinal = new string[tamano];
        for (int i = 0; i < tamano; i++) {
            resultadoFinal[i] = piedras[i];
        }
        tamanoFinal = tamano;
        return;
    }

    int capacidad = tamano * 2; // Capacidad ini del nuevo array
    string* nuevasPiedras = new string[capacidad];
    int nuevoTamano = 0;

    // Procesa cada piedra en el array actual
    for (int i = 0; i < tamano; i++) {
        long long piedra = stoll(piedras[i]); // Convierte piedra a entero
        Resultado resultado = transformarPiedra(piedra, memo); // Transforma la piedra
        for (int j = 0; j < resultado.tamano; j++) {
            // Expande el array si es necesario
            if (nuevoTamano >= capacidad) {
                capacidad *= 2;
                string* temp = new string[capacidad];
                for (int k = 0; k < nuevoTamano; k++) {
                    temp[k] = nuevasPiedras[k];
                }
                delete[] nuevasPiedras;
                nuevasPiedras = temp;
            }
            nuevasPiedras[nuevoTamano++] = resultado.valores[j]; // Añade el resultado
        }
    }

    // Llamada recursiva para el siguiente parpadeo
    transformarRecursivo(nuevasPiedras, nuevoTamano, parpadeos - 1, resultadoFinal, tamanoFinal, memo);
    delete[] nuevasPiedras;
}

int main() {
    ifstream entrada("input11.txt");

    string* piedras = new string[100]; // Array inicial
    int tamano = 0;
    int capacidad = 100;

    long long numero;

    // Lee las piedras del input
    while (entrada >> numero) {
        if (tamano >= capacidad) { // Expande el array si es necesario
            capacidad *= 2;
            string* temp = new string[capacidad];
            for (int i = 0; i < tamano; i++) {
                temp[i] = piedras[i];
            }
            delete[] piedras;
            piedras = temp;
        }
        piedras[tamano++] = to_string(numero);
    }
    entrada.close();

    const int parpadeos = 25;

    Memo memo; // Crea la memoria
    string* resultadoFinal;
    int tamanoFinal;

    transformarRecursivo(piedras, tamano, parpadeos, resultadoFinal, tamanoFinal, memo);

    cout << tamanoFinal << endl;

    delete[] resultadoFinal;
    delete[] piedras;

    return 0;
}

