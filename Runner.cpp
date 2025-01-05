#include "Runner.h"
#include <climits>
#include <cstddef>
#include <string>
#include <fstream>
#include <utility>


Runner::Runner(Config& config, DataGenerator& generator, ProblemSolver& ps) {
   this->config = config;
   this->generator = generator;
   this->ps = ps;
}

void Runner::executeTest() {
    generator.loadTSPLIB(config.dataFile);
    ps.changeParameters(
        ps.generateTemp(generator.matrix, generator.matrixSize, config.worseAcceptanceProbability, 500),
        config.alpha, 
        config.neighbourDefinition, 
        config.stopSeconds, 
        config.initialPathFromNearestNeighbour
    );
    ps.simAnnealing(generator.matrix, generator.matrixSize);
}

void Runner::executeSimulation() {
    std::string outputName = config.outputFileName;
    std::fstream output(outputName, std::ios::out);

    output << "nr;czas;koszt\n";

    generator.loadTSPLIB(config.dataFile);
    ps.changeParameters(
        ps.generateTemp(generator.matrix, generator.matrixSize, config.worseAcceptanceProbability, 500),
        config.alpha, 
        config.neighbourDefinition, 
        config.stopSeconds, 
        config.initialPathFromNearestNeighbour
    );

    std::pair<int, int*> minResult = std::make_pair(INT_MAX, nullptr);

    for(int i = 0; i < config.runsNumber; i++) {
        if(config.showProgress) std::cout << "Currently running test " << i+1 << "/" << config.runsNumber << "\n";
        auto temp = ps.simAnnealing(generator.matrix, generator.matrixSize, i, output);
        if(temp.first < minResult.first) minResult = temp;
    }

    output << "\nNajlepsza znaleziona ścieka:\n";
    for(int i = 0; i < generator.matrixSize; i++) {
        output << minResult.second[i];
    }

    output.close();
}

