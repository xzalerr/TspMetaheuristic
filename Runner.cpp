//#include "Runner.h"
//#include <fstream>
//#include <chrono>
//
//
//Runner::Runner(Config& config, DataGenerator& generator, ProblemSolver& ps) {
//    this->config = config;
//    this->generator = generator;
//    this->ps = ps;
//}
//
//double Runner::measureDfs(int &minCost, int size, bool sym) {
//    // Zmierz czas przed i po wykonaniu funkcji i oblicz różnice w ms
//    auto start = std::chrono::high_resolution_clock::now();
//    if(!sym) minCost = ps.dfs(generator.matrix, size);
//    else minCost = ps.dfsSym(generator.symMatrix, size);
//    auto end = std::chrono::high_resolution_clock::now();
//    return std::chrono::duration<double, std::milli>(end - start).count();
//}
//
//double Runner::measureBfs(int &minCost, int size, bool sym) {
//    // Zmierz czas przed i po wykonaniu funkcji i oblicz różnice w ms
//    auto start = std::chrono::high_resolution_clock::now();
//    if(!sym) minCost = ps.bfs(generator.matrix, size);
//    else minCost = ps.bfsSym(generator.symMatrix, size);
//    auto end = std::chrono::high_resolution_clock::now();
//    return std::chrono::duration<double, std::milli>(end - start).count();
//}
//
//double Runner::measureBfsZ(int &minCost, int size, bool sym) {
//    // Zmierz czas przed i po wykonaniu funkcji i oblicz różnice w ms
//    auto start = std::chrono::high_resolution_clock::now();
//    if(!sym) minCost = ps.bfsZ(generator.matrix, size);
//    else minCost = ps.bfsZSym(generator.symMatrix, size);
//    auto end = std::chrono::high_resolution_clock::now();
//    return std::chrono::duration<double, std::milli>(end - start).count();
//}
//
//void Runner::executeTest() {
//    /* Sprawdź czy użytkownik zadał generowanie czy wczytanie grafu
//     * Jeśli generowanie sprawdź czy symetryczne czy nie i wygeneruj
//     * W przeciwnym wypadku wczytaj
//     */
//    bool sym;
//    int size;
//    if (config.generateRandom) {
//        if (config.testType == "symmetric") {
//            generator.generateDataSymmetric(config.generatorProblemSize);
//            sym = true;
//            size = config.generatorProblemSize;
//        } else {
//            generator.generateDataAsymmetric(config.generatorProblemSize);
//            sym = false;
//            size = config.generatorProblemSize;
//        }
//        generator.printData(sym);
//    } else {
//        if (config.testType == "symmetric") {
//            sym = true;
//            size = generator.loadData(config.dataFile, sym);
//        } else {
//            sym = false;
//            size = generator.loadData(config.dataFile, sym);
//        }
//        generator.printData(sym);
//    }
//    // Oblicz czasy i wyniki algorytmów i wypisz na ekranie
//    int minCostDfs, minCostBfs, minCostBfsZ;
//    double timeDfs = measureDfs(minCostDfs, size, sym);
//    double timeBfs = measureBfs(minCostBfs, size, sym);
//    double timeBfsZ = measureBfsZ(minCostBfsZ, size, sym);
//    std::cout << "Minimum Cost (DFS): " << minCostDfs << " [czas: " << timeDfs << " ms]" << std::endl;
//    std::cout << "Minimum Cost (BFS): " << minCostBfs << " [czas: " << timeBfs << " ms]" << std::endl;
//    std::cout << "Minimum Cost (BFSZ): " << minCostBfsZ << " [czas: " << timeBfsZ << " ms]" << std::endl;
//}
//
//void Runner::executeSimulation() {
//    /* Mapy do przechowywania wyników w formacie gdzie klucz to rozmiar problemu
//     * a wartość jest wektorem z przechowanymi czasami dla danego rozmiaru w ms
//     */
//    std::map<int, std::vector<double>> resultsDfs;
//    std::map<int, std::vector<double>> resultsBfs;
//    std::map<int, std::vector<double>> resultsBfsZ;
//
//    /* Przeiteruj po zadanych w pliku konfiguracyjnym rozmiarach problemu
//     * Sprawdź czy generować graf symetryczny czy nie
//     * Wykonaj algorytmy i zapisz ich czas w mapie dla odpowiedniego klucza
//     */
//    for(int size : config.problemSizes) {
//        double sumDurationDfs = 0;
//        double sumDurationBfs = 0;
//        double sumDurationBfsZ = 0;
//        bool sym;
//        for(int i = 0; i < config.iterations; i++) {
//            if (config.matrixType == "symmetric") {
//                generator.generateDataSymmetric(size);
//                sym = true;
//            } else if (config.matrixType == "asymmetric") {
//                generator.generateDataAsymmetric(size);
//                sym = false;
//            } else {
//                std::cerr << "Nieznany typ danych: " << config.simulationRandomType << std::endl;
//                break;
//            }
//
//            int minCostDfs = 0;
//            int minCostBfs = 0;
//            int minCostBfsZ = 0;
//
//            double durationDfs = measureDfs(minCostDfs, size, sym);
//            double durationBfs = measureBfs(minCostBfs, size, sym);
//            double durationBfsZ = measureBfsZ(minCostBfsZ, size, sym);
//
//            resultsDfs[size].emplace_back(durationDfs);
//            resultsBfs[size].emplace_back(durationBfs);
//            resultsBfsZ[size].emplace_back(durationBfsZ);
//
//            sumDurationDfs += durationDfs;
//            sumDurationBfs += durationBfs;
//            sumDurationBfsZ += durationBfsZ;
//
//            /* Jeśli użytkownik zaznaczył pokazywanie postępu to
//             * pokaż rozmiar problemu, nr iteracji oraz średni czas każdego
//             * z algorytmów, w przeciwnym razie pokaż tylko średnie czasy
//             */
//            if (config.showProgress) {
//                double averageDurationDfs = sumDurationDfs / (i + 1);
//                double averageDurationBfs = sumDurationBfs / (i + 1);
//                double averageDurationBfsZ= sumDurationBfsZ / (i + 1);
//
//                std::cout << "Rozmiar problemu: " << size << "\n";
//                std::cout << "Iteracja: " << (i + 1) << "/" << config.iterations << "\n";
//                std::cout << "Średni czas DFS: " << averageDurationDfs << " ms\n";
//                std::cout << "Średni czas BFS: " << averageDurationBfs << " ms\n";
//                std::cout << "Średni czas BFSZ: " << averageDurationBfsZ << " ms\n";
//            } else {
//                double averageDurationDfs = sumDurationDfs / (i + 1);
//                double averageDurationBfs = sumDurationBfs / (i + 1);
//                double averageDurationBfsZ= sumDurationBfsZ / (i + 1);
//
//                std::cout << "Średni czas DFS: " << averageDurationDfs << " ms\n";
//                std::cout << "Średni czas BFS: " << averageDurationBfs << " ms\n";
//                std::cout << "Średni czas BFSZ: " << averageDurationBfsZ << " ms\n";
//            }
//        }
//    }
//    // Zapisz do plików .csv
//    saveToCSV(resultsDfs, "results_dfs");
//    saveToCSV(resultsBfs, "results_bfs");
//    saveToCSV(resultsBfsZ, "results_bfsz");
//}
//
//void Runner::saveToCSV(std::map<int, std::vector<double>> &results, std::string alg) {
//    // Utwórz plik o nazwie "nazwa_algorytmu_symetrycznosc_csv"
//    std::string file = alg + "_" + (config.matrixType == "symmetric" ? "symmetric" : "asymmetric") + ".csv" ;
//    std::ofstream out(file);
//    // W pierwszym wierszu napisz kolejne zbadane rozmiary
//    out << "rozmiar:";
//    for(auto& kv : results) {
//        out << ";"<< kv.first;
//    }
//    out << "\n";
//
//    // Zapisuj wyniki w odpowiednich kolumnach wiersz po wierszu
//    for(int i = 0; i < config.iterations; i++) {
//        out<< i + 1;
//        for (auto& kv : results) {
//            if (i < kv.second.size()) {
//                out << ";" << kv.second[i];
//            } else {
//                out << ";";
//            }
//        }
//        out << "\n";
//    }
//}