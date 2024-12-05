/*Se utiliza ChatGPT para saber para funciones como push_back 
o istringstream y para saber que bibliotecas incluir*/

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
        vector<int> niveles; //crea un vector que contiene enteros
        int nivel;

        while (stream >> nivel) { //cada entero lo mete en la variable nivel
            niveles.push_back(nivel); //si hay numero lo mete al final del vector
        }

        if (esSeguro(niveles)) {
            seguros++;
        }
    }

    archivo.close();
    cout << seguros << endl;

    return 0;
}
