#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

// Función para evaluar si el objetivo es alcanzable con combinaciones de + y *
bool canAchieveTarget(long long target, const vector<int>& nums, int index, long long currentValue) {
    if (index == nums.size()) {
        return currentValue == target;
    }
    // Opción 1: sumar el siguiente número
    if (canAchieveTarget(target, nums, index + 1, currentValue + nums[index])) {
        return true;
    }
    // Opción 2: multiplicar por el siguiente número
    if (canAchieveTarget(target, nums, index + 1, currentValue * nums[index])) {
        return true;
    }
    return false;
}

// Función para dividir una línea en objetivo y lista de números
bool parseLine(const string& line, long long& target, vector<int>& nums) {
    size_t colonPos = line.find(":");
    if (colonPos == string::npos) {
        return false; // Formato incorrecto
    }
    try {
        target = stoll(line.substr(0, colonPos)); // Cambiado a stoll para manejar números grandes
    } catch (const invalid_argument& e) {
        return false; // No se pudo convertir el objetivo
    } catch (const out_of_range& e) {
        return false; // Valor demasiado grande para manejarlo
    }

    stringstream ss(line.substr(colonPos + 1));
    int num;
    while (ss >> num) {
        nums.push_back(num);
    }
    return !nums.empty(); // Asegurarse de que hay números válidos
}

int main() {
    ifstream inputFile("input1.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo input1.txt" << endl;
        return 1;
    }

    string line;
    long long totalCalibrationResult = 0;

    // Leer cada línea del archivo
    while (getline(inputFile, line)) {
        if (line.empty()) continue; // Ignorar líneas vacías

        long long target;
        vector<int> nums;
        if (!parseLine(line, target, nums)) {
            cerr << "Error: Línea mal formateada o fuera de rango: " << line << endl;
            continue; // Saltar líneas mal formateadas
        }

        // Evaluar si el objetivo se puede alcanzar
        if (canAchieveTarget(target, nums, 1, nums[0])) {
            totalCalibrationResult += target;
        }
    }

    inputFile.close();

    // Imprimir el resultado total
    cout << "Total Calibration Result: " << totalCalibrationResult << endl;
    return 0;
}
