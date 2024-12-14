#ifndef TSPMETAHEURISTIC_CONFIG_H
#define TSPMETAHEURISTIC_CONFIG_H

#include <iostream>
#include <vector>

// Klasa służąca do wczytania danych z pliku konfiguracyjnego i przechowywanie danych
class Config {
public:
    std::string mode;

    std::string dataFile;
    bool generateRandom;
    int generatorProblemSize;
    std::string testType;

    std::vector<int> problemSizes;
    std::string matrixType;
    int iterations;
    std::string simulationRandomType;
    bool showProgress;

    // Metoda wczytująca konfigurację z pliku JSON o podanej nazwie
    void loadData(const std::string& fileName);
};


#endif //TSPMETAHEURISTIC_CONFIG_H
