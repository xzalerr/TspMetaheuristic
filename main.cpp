#include <iostream>
#include "ProblemSolver.h"
#include "DataGenerator.h"

int main() {
    DataGenerator dg;
    ProblemSolver ps;
    dg.loadData("/Users/rafalzalecki/CLionProjects/TravellingSalesmanProblemBruteForce/matrix_6x6.atsp", false);
    std::cout << "Cost found:" << ps.simAnnealing(dg.matrix, 6, 5000, 0.99, 5) << "\n";
    return 0;
}
