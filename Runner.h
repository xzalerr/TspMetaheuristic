#ifndef TSPMETAHEURISTIC_RUNNER_H
#define TSPMETAHEURISTIC_RUNNER_H

#include "Config.h"
#include "DataGenerator.h"
#include "ProblemSolver.h"

// Kasa Runner odpowiada za uruchamianie tryby testowania algorytmów lub symulacji do wykonania pomiarów
class Runner {
public:
    Config config; // Obiekt przechowujący konfigurację programu
    DataGenerator generator; // Obiekt generujący dane grafów
    ProblemSolver ps; // Obiekt rozwiązujący problem komiwojażera różnymi algorytmami

    // Konstruktor przyjmujący konfigurację, generator danych oraz solver jako argumenty
    Runner(Config& config, DataGenerator& generator, ProblemSolver& ps);

    // Wykonuje program gdy wybrano tryb "test"
    void executeTest();

    // Wykonuje program gdy wybrano tryb "simulation"
    void executeSimulation();
};


#endif //TSPMETAHEURISTIC_RUNNER_H
