#include "DataGenerator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

DataGenerator::~DataGenerator() {
    deallocateMatrix();
}

void DataGenerator::allocateMatrix(int n) {
    // zwalniamy pamięć jeśli macierz już jakąś zajmowała wcześniej
    deallocateMatrix();
    // tworzymy dynamicznie tablice tablic o rozmiarze n
    this->matrixSize = n;
    matrix = new int*[n];
    for(int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
}

void DataGenerator::deallocateMatrix() {
    // jeśli macierz istnieje to usuwamy tablice z tablicy głównej, a następnie usuwamy tą tablice a wskaźnik ustawiamy na null
    if (matrix != nullptr) {
        for (int i = 0; i < matrixSize; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
        matrixSize = 0;
    }
}

int DataGenerator::loadData(std::string name, bool sym) {
    // Otwórz plik o zadanej nazwie
    std::fstream input(name);

    if(!input.is_open()) {
        std::cerr << "Nie udało się zlokalizować pliku o podanej nazwie!\n";
        return -1;
    }
    // Z pierwszej linii wczytaj rozmiar instancji
    int n;
    input >> n;
    // Wyczyść graf i zredefiniuj jego rozmiar
    allocateMatrix(n);
    // Kolejne dane wczytuj w porządku wiersz po wierszu
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            input >> matrix[i][j];
        }
    }
    input.close();
    return n;
}

void DataGenerator::loadTSPLIB(std::string name) {
    // otwórz plik
    std::fstream input(name);
    if (!input.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku!\n";
        return;
    }

    std::string line;
    int n = 0;  // rozmiar macierzy

    // pomijanie nagłówka, wyszukiwanie DIMENSION
    while (std::getline(input, line)) {
        if (line.rfind("DIMENSION") == 0) {
            // parsowanie rozmiaru
            std::sscanf(line.c_str(), "DIMENSION: %d", &n);
        } else if (line == "EDGE_WEIGHT_SECTION") {
            break;  // przerwij, gdy znajdziesz sekcję wag
        }
    }

    // alokacja pamięci na macierz
    allocateMatrix(n);

    // wczytywanie wartości macierzy wag
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> matrix[i][j];
        }
    }

    input.close();
}

void DataGenerator::printData(bool sym) {
    int n = this->matrixSize;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

