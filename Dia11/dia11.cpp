#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Resultado {
    string* valores;
    int tamano;
};

struct MemoEntry {
    long long clave;
    Resultado resultado;
};

class Memo {
private:
    MemoEntry* entries;
    int capacidad;
    int tamano;

    void expandir() {
        capacidad *= 2;
        MemoEntry* nuevos = new MemoEntry[capacidad];
        for (int i = 0; i < tamano; i++) {
            nuevos[i] = entries[i];
        }
        delete[] entries;
        entries = nuevos;
    }

public:
    Memo() : capacidad(100), tamano(0) {
        entries = new MemoEntry[capacidad];
    }

    ~Memo() {
        for (int i = 0; i < tamano; i++) {
            delete[] entries[i].resultado.valores;
        }
        delete[] entries;
    }

    bool buscar(long long clave, Resultado& resultado) {
        for (int i = 0; i < tamano; i++) {
            if (entries[i].clave == clave) {
                resultado = entries[i].resultado;
                return true;
            }
        }
        return false;
    }

    void agregar(long long clave, Resultado resultado) {
        if (tamano >= capacidad) {
            expandir();
        }
        entries[tamano++] = {clave, resultado};
    }
};

Resultado dividirNumero(long long numero) {
    string numCadena = to_string(numero);
    int mitad = numCadena.size() / 2;

    string izquierda = numCadena.substr(0, mitad);
    string derecha = numCadena.substr(mitad);

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

    string* resultado = new string[2];
    resultado[0] = to_string(izq);
    resultado[1] = to_string(der);

    return {resultado, 2};
}

Resultado transformarPiedra(long long piedra, Memo& memo) {
    Resultado resultadoMemo;
    if (memo.buscar(piedra, resultadoMemo)) {
        return resultadoMemo;
    }

    if (piedra == 0) {
        string* resultado = new string[1]{"1"};
        memo.agregar(piedra, {resultado, 1});
        return {resultado, 1};
    }

    if (to_string(piedra).size() % 2 == 0) {
        Resultado resultadoDividir = dividirNumero(piedra);
        memo.agregar(piedra, resultadoDividir);
        return resultadoDividir;
    } else {
        string* resultado = new string[1]{to_string(piedra * 2024)};
        memo.agregar(piedra, {resultado, 1});
        return {resultado, 1};
    }
}

void transformarRecursivo(string* piedras, int tamano, int parpadeos, string*& resultadoFinal, int& tamanoFinal, Memo& memo) {
    if (parpadeos == 0) {
        resultadoFinal = new string[tamano];
        for (int i = 0; i < tamano; i++) {
            resultadoFinal[i] = piedras[i];
        }
        tamanoFinal = tamano;
        return;
    }

    int capacidad = tamano * 2;
    string* nuevasPiedras = new string[capacidad];
    int nuevoTamano = 0;

    for (int i = 0; i < tamano; i++) {
        long long piedra = stoll(piedras[i]);
        Resultado resultado = transformarPiedra(piedra, memo);
        for (int j = 0; j < resultado.tamano; j++) {
            if (nuevoTamano >= capacidad) {
                capacidad *= 2;
                string* temp = new string[capacidad];
                for (int k = 0; k < nuevoTamano; k++) {
                    temp[k] = nuevasPiedras[k];
                }
                delete[] nuevasPiedras;
                nuevasPiedras = temp;
            }
            nuevasPiedras[nuevoTamano++] = resultado.valores[j];
        }
    }

    transformarRecursivo(nuevasPiedras, nuevoTamano, parpadeos - 1, resultadoFinal, tamanoFinal, memo);
    delete[] nuevasPiedras;
}

int main() {
    ifstream entrada("input11.txt");

    string* piedras = new string[100];
    int tamano = 0;
    int capacidad = 100;

    long long numero;
    while (entrada >> numero) {
        if (tamano >= capacidad) {
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

    Memo memo;
    string* resultadoFinal;
    int tamanoFinal;

    transformarRecursivo(piedras, tamano, parpadeos, resultadoFinal, tamanoFinal, memo);

    cout << tamanoFinal << endl;

    delete[] resultadoFinal;
    delete[] piedras;

    return 0;
}

