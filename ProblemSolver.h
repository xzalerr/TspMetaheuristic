#ifndef TSPMETAHEURISTIC_PROBLEMSOLVER_H
#define TSPMETAHEURISTIC_PROBLEMSOLVER_H

#include <vector>
#include <fstream>
#include "DataGenerator.h"

// Klasa zawierajaca metody do rozwiazywana problemu komiwojazera metoda podzialu i ograniczen
class ProblemSolver {
public:
    std::pair<int, int*> simAnnealing(int** matrix, int n);
    std::pair<int, int*> simAnnealing(int** matrix, int n, int count, std::fstream& output);
    std::pair<int, int*> tspNeighbour(int** matrix, int n);
    void changeParameters(double temp, double alpha, int definiton, double seconds, bool useNeighbour);
    double generateTemp(int** matrix, int n, double probability, int tests);
private:
    int definition;
    double temp, alpha, seconds;
    bool useNeighbour;

    static void shuffleArray(int* arr, int n);
    static int findNeighbour(int** matrix, int n, bool* visited, int city);
    static int findCost(int** matrix, int* path, int n);
    static void inverse(int* path, int n);
    static void swap(int* path, int n);
    static void insert(int* path, int n);
    static int* getNext(int* path, int n, int c);

};


#endif //TSPMETAHEURISTIC_PROBLEMSOLVER_H
