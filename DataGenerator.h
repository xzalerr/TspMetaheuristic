#ifndef TSPMETAHEURISTIC_DATAGENERATOR_H
#define TSPMETAHEURISTIC_DATAGENERATOR_H

#include <string>

// Klasa do generowania losowych grafów
class DataGenerator {
public:
    int** matrix;
    int matrixSize;

    DataGenerator() : matrix(nullptr) {}
    ~DataGenerator();

    // Funkcja wczytująca dane z zadanego pliku
    int loadData(std::string name, bool sym);

    void loadTSPLIB(std::string name);

    // Funkcja wypisująca macierz na ekranie
    void printData(bool sym);
private:
    // Funckja do zaalokowania pamięci potrzebnej dla dwuwymiarowej tablicy
    void allocateMatrix(int n);
    // Funkcja zwalniająca pamięć po dwuwymiarowej tablicy
    void deallocateMatrix();
};


#endif //TSPMETAHEURISTIC_DATAGENERATOR_H
