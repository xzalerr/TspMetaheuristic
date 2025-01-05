#include <iostream>
#include "ProblemSolver.h"
#include "DataGenerator.h"

// ml flow - mozna sprobowac uzyc do uruchamiania serii symulacji
// np zrobic zeby posortowac tam tylko wyniki gdzie blad wzgledny jest mniejszy niz 10% 
// albo ogolnie mozna tak sobie sortowac
// sa narzucone 3 macierze i symulacje robimy tylko na tych 3 plikach 
// w tych plikach algorytmy od zadania 3 nie gwarantuja znalezienia wymagania minimalnego rozwiazania
// w rozmiarze 170 np ciezko bedzie uzyskac dobry wynik, mniej niz 10% bledu to dobry wynik

int main() {
    DataGenerator dg;
    ProblemSolver ps;
    dg.loadTSPLIB("/Users/rafalzalecki/CLionProjects/TspMetaheuristic/graphs/ftv47.atsp");
    // dg.printData(false);
    // parametry do liczenia temperatury opracowałem empirycznie i 500 testow okazalo sie byc najdokladniejsze
    ps.changeParameters(ps.generateTemp(dg.matrix, dg.matrixSize, 0.8, 500), 0.99, 120, true);
    auto result = ps.simAnnealing(dg.matrix, dg.matrixSize, -1);
    std::cout << "Cost: " << result.first << "\n";
    return 0;
}
