#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map> // Para memoización
#include <stdexcept> // Para manejar excepciones

// Función para dividir un número en dos partes según las reglas
void splitNumber(long long number, std::vector<long long>& new_stones) {
    std::string num_str = std::to_string(number);
    int half = num_str.size() / 2;

    // Manejo seguro de subcadenas
    std::string left_str = num_str.substr(0, half);
    std::string right_str = num_str.substr(half);

    long long left = left_str.empty() ? 0 : std::stoll(left_str);
    long long right = right_str.empty() ? 0 : std::stoll(right_str);

    new_stones.push_back(left);
    new_stones.push_back(right);
}

// Función para aplicar las reglas de transformación con memoización
std::vector<long long> transformStones(const std::vector<long long>& stones, std::unordered_map<long long, std::vector<long long>>& memo) {
    std::vector<long long> new_stones;
    for (long long stone : stones) {
        // Si el resultado ya está en memo, lo usamos
        if (memo.find(stone) != memo.end()) {
            new_stones.insert(new_stones.end(), memo[stone].begin(), memo[stone].end());
            continue;
        }

        // Calculamos el resultado si no está en memo
        std::vector<long long> current_result;
        if (stone == 0) {
            current_result.push_back(1);
        } else if (std::to_string(stone).size() % 2 == 0) {
            splitNumber(stone, current_result);
        } else {
            current_result.push_back(stone * 2024);
        }

        // Guardamos el resultado en memo
        memo[stone] = current_result;
        new_stones.insert(new_stones.end(), current_result.begin(), current_result.end());
    }
    return new_stones;
}

int main() {
    // Leer el archivo de entrada
    std::ifstream input_file("input11.txt");
    std::vector<long long> stones;
    if (input_file.is_open()) {
        long long number;
        while (input_file >> number) {
            stones.push_back(number);
        }
        input_file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo de entrada." << std::endl;
        return 1;
    }

    // Configurar número de parpadeos
    const int blinks = 25;

    // Mapa para memoización
    std::unordered_map<long long, std::vector<long long>> memo;

    // Aplicar las transformaciones durante los parpadeos
    for (int i = 0; i < blinks; ++i) {
        stones = transformStones(stones, memo);
    }

    // Imprimir el número total de piedras después de 25 parpadeos
    std::cout << stones.size() << std::endl;

    return 0;
}
