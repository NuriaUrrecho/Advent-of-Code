#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Representación de un bloque de archivo o espacio libre
struct Block {
    int length;
    int fileId; // -1 para espacio libre
};

// Función para parsear el mapa de disco
vector<Block> parseDiskMap(const string& diskMap) {
    vector<Block> diskBlocks;
    int fileId = 0;
    bool isFileLength = true;

    for (char c : diskMap) {
        int length = c - '0';
        if (isFileLength) {
            diskBlocks.push_back({length, fileId++});
        } else {
            diskBlocks.push_back({length, -1}); // Espacio libre
        }
        isFileLength = !isFileLength;
    }

    return diskBlocks;
}

// Función para compactar el disco
vector<Block> compactDisk(vector<Block>& diskBlocks) {
    vector<Block> compactedBlocks;
    
    // Primero, mover todos los bloques de archivo juntos
    for (const auto& block : diskBlocks) {
        if (block.fileId != -1) { // Es un bloque de archivo
            compactedBlocks.push_back(block);
        }
    }
    
    // Añadir espacio libre al final
    int totalFreeSpace = 0;
    for (const auto& block : diskBlocks) {
        if (block.fileId == -1) {
            totalFreeSpace += block.length;
        }
    }
    
    if (totalFreeSpace > 0) {
        compactedBlocks.push_back({totalFreeSpace, -1});
    }
    
    return compactedBlocks;
}

// Calcular el checksum del sistema de archivos
long long calculateChecksum(const vector<Block>& diskBlocks) {
    long long checksum = 0;
    int position = 0;
    
    for (const auto& block : diskBlocks) {
        if (block.fileId != -1) { // Ignorar espacio libre
            // Multiplicar posición por ID de archivo
            checksum += (long long)position * block.fileId;
            
            // Avanzar la posición por la longitud del bloque
            position += block.length;
        }
    }
    
    return checksum;
}

int main() {
    // Reemplazar con tu input
    string diskMap = "2333133121414131402";
    
    // Parsear el mapa de disco
    vector<Block> diskBlocks = parseDiskMap(diskMap);
    
    // Compactar el disco
    diskBlocks = compactDisk(diskBlocks);
    
    // Calcular el checksum
    long long checksum = calculateChecksum(diskBlocks);
    
    cout << "Checksum del sistema de archivos: " << checksum << endl;
    
    return 0;
}