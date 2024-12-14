#include "DataGenerator.h"
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

DataGenerator::~DataGenerator() {
    deallocateMatrix();
    deallocateSymMatrix();
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

void DataGenerator::allocateSymMatrix(int n) {
    // zwalniamy pamięć jeśli macierz już jakąś zajmowała wcześniej
    deallocateSymMatrix();
    // tworzymy dynamicznie tablice o rozmiarze (n*n-n)/2, tyle potrzeba aby zmieścić górną połowę macierzy
    this->matrixSize = n;
    symMatrix = new int[(n*n-n)/2];
    symMatrixSize = (n*n-n)/2;
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

void DataGenerator::deallocateSymMatrix() {
    // jeśli macierz istnieje to usuwamy tablice, a wskaźnik ustawiamy na null
    if (symMatrix != nullptr) {
        delete[] symMatrix;
        symMatrix = nullptr;
    }
    symMatrixSize = 0;
}

void DataGenerator::generateDataAsymmetric(int n) {
    // Utwórz generator losowych liczb z zakresu 1 - 100
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    // Zaalokuj odpowienią ilość miejsca w pamięci
    allocateMatrix(n);
    // Przypisz do grafu losowe wartości, poza przekątną gdzie jest -1
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) this->matrix[i][j] = -1;
            else this->matrix[i][j] = dist(gen);
        }
    }
}

void DataGenerator::generateDataSymmetric(int n) {
    // Utwórz generator losowych liczb z zakresu 1 - 100
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    // Zaalokuj odpowienią ilość miejsca w pamięci
    allocateSymMatrix(n);
    for(int i = 0; i < (n*n-n)/2; i++) {
        symMatrix[i] = dist(gen);
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
    // Jeśli macierz jest symetryczna to przepisz górną połowę z dwuwymiarowej do jednowymiarowej i usuń dwuwymiarową
    if(sym) {
        allocateSymMatrix(n);
        int count = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                symMatrix[count] = matrix[i][j];
                count++;
            }
        }
        deallocateMatrix();
    }
    return n;
}

void DataGenerator::printData(bool sym) {
    // jeśli macierz asymetryczna to wypisz po kolei wartości macierzy
    if (!sym) {
        int n = this->matrixSize;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << std::setw(3) << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
        /* jeśli symetryczna to na przekątnych wypisz -1,
         * na górnej połowie kolejne wartości,
         * a na dolnej połowie puste miejsca
         */
    } else {
        int n = 1;
        while((n*n-n)/2 < this->symMatrixSize) n++;
        int index = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    std::cout << std::setw(3) << -1 << " ";
                } else if (i < j) {
                    std::cout << std::setw(3) << symMatrix[index++] << " ";
                } else {
                    std::cout << std::setw(4) << " ";
                }
            }
            std::cout << "\n";
        }
    }
}

