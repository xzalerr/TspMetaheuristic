#include <iostream>
#include "ProblemSolver.h"
#include "DataGenerator.h"
#include "Config.h"
#include "Runner.h"

// ml flow - mozna sprobowac uzyc do uruchamiania serii symulacji
// np zrobic zeby posortowac tam tylko wyniki gdzie blad wzgledny jest mniejszy niz 10% 
// albo ogolnie mozna tak sobie sortowac
// sa narzucone 3 macierze i symulacje robimy tylko na tych 3 plikach 
// w tych plikach algorytmy od zadania 3 nie gwarantuja znalezienia wymagania minimalnego rozwiazania
// w rozmiarze 170 np ciezko bedzie uzyskac dobry wynik, mniej niz 10% bledu to dobry wynik

int main() {
    Config config;
    std::string path = CONFIG_FILE_PATH;
    config.loadData(path);

    DataGenerator generator;
    ProblemSolver ps;
    Runner runner(config, generator, ps);

    if (config.mode == "test") {
        runner.executeTest();
    } else if (config.mode == "simulation") {
        runner.executeSimulation();
    } else {
        std::cerr << "Nie ma takiej opcji!\n";
    }

    return 0;
}
