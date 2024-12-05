//ChatGPT para la funcion erase y begin

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

bool esSeguro(const vector<int>& niveles) {
    bool creciente = true, decreciente = true;

    for (int i = 1; i < niveles.size(); i++) {
        int diferencia = niveles[i] - niveles[i - 1];
        if (diferencia > 3 || diferencia < -3) return false;
        if (diferencia <= 0) creciente = false;
        if (diferencia >= 0) decreciente = false;
    }

    return creciente || decreciente;
}

bool esSeguroConDampener(const vector<int>& niveles) {
    if (esSeguro(niveles)) return true;

    for (int i = 0; i < niveles.size(); i++) {
        vector<int> copia = niveles;
        copia.erase(copia.begin() + i); //elimina un elemento
        if (esSeguro(copia)) return true;
    }

    return false;
}

int main() {
    ifstream archivo("2.txt");
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return -1;
    }

    string linea;
    int seguros = 0;

    while (getline(archivo, linea)) {
        istringstream stream(linea);
        vector<int> niveles;
        int nivel;

        while (stream >> nivel) {
            niveles.push_back(nivel);
        }

        if (esSeguroConDampener(niveles)) {
            seguros++;
        }
    }

    archivo.close();
    cout << seguros << endl;

    return 0;
}
