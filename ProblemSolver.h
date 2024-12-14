#ifndef TSPMETAHEURISTIC_PROBLEMSOLVER_H
#define TSPMETAHEURISTIC_PROBLEMSOLVER_H

#include <vector>
#include "DataGenerator.h"

// Klasa zawierajaca metody do rozwiazywana problemu komiwojazera metoda podzialu i ograniczen
class ProblemSolver {
public:
    int simAnnealing(int** matrix, int n, double t, double a, double seconds);
private:
    static int findCost(int** matrix, int* path, int n);
    static void inverse(int* path, int n);
    static void swap(int* path, int n);
    static void insert(int* path, int n);
    static int* getNext(int* path, int n);
};


#endif //TSPMETAHEURISTIC_PROBLEMSOLVER_H
