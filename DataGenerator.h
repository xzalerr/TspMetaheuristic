#ifndef TSPMETAHEURISTIC_DATAGENERATOR_H
#define TSPMETAHEURISTIC_DATAGENERATOR_H

#include <vector>
#include <string>

// Klasa do generowania losowych grafów
class DataGenerator {
public:
    int** matrix;
    int* symMatrix;
    int matrixSize;
    int symMatrixSize;

    DataGenerator() : matrix(nullptr), symMatrix(nullptr) {}
    ~DataGenerator();

    // Funkcja generująca graf asymetryczny
    void generateDataAsymmetric(int n);

    // Funkcja generująca graf symetryczny
    void generateDataSymmetric(int n);

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
    // Funckja do zaalokowania pamięci potrzebnej dla jednowymiarowej tablicy
    void allocateSymMatrix(int n);
    // Funkcja zwalniająca pamięć po jednowymiarowej tablicy
    void deallocateSymMatrix();
};


#endif //TSPMETAHEURISTIC_DATAGENERATOR_H
