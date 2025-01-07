#include "ProblemSolver.h"
#include <cmath>
#include <random>
#include <iostream>
#include <chrono>
#include <utility>

void ProblemSolver::changeParameters(double temp, double alpha, int definiton, double seconds, bool useNeighbour) {
    this->temp = temp;
    this->alpha = alpha;
    this->definition = definiton;
    this->seconds = seconds;
    this->useNeighbour = useNeighbour;
}

double ProblemSolver::generateTemp(int** matrix, int n, double probability, int tests) {
    int* path = new int[n];
    int costDiff = 0;

    if(useNeighbour) {
        path = tspNeighbour(matrix, n).second;
    } else {
        for(int i = 0; i < n; i++) {
            path[i] = i;
        }
    }

    int currCost = findCost(matrix, path, n);

    for(int i = 0; i < tests; i++) {
        int* newPath = new int[n];
        newPath = getNext(path, n, -1);
        int newCost = findCost(matrix, newPath, n);

        costDiff += std::abs(newCost - currCost);
        
        delete[] path;
        path = newPath;
        currCost = newCost;
    }
    delete[] path;

    double avg = double(costDiff) / tests;

    double temp = -avg / std::log(probability);

    return temp;
}

int ProblemSolver::findNeighbour(int** matrix, int n, bool* visited, int city) {
    int min = INT_MAX;
    int nearest = -1;
    // Znajdź najbliższe miasto od zadanego city, które nie jest jeszcze odwiedzone
    for(int i = 0; i < n; i++) {
        if((matrix[city][i] < min) && !visited[i]) {
            min = matrix[city][i];
            nearest = i;
        }
    }
    return nearest;
}

std::pair<int, int*> ProblemSolver::tspNeighbour(int** matrix, int n) {
    int minCost = 0;
    // Utwórz tablice kontrolujaca odwiedzone miasta
    bool* visited = new bool[n];
    for(int i = 0; i < n; i++) {
        visited[i] = false;
    }
    // Utwórz tablice kontrolujaca sciezke
    int* path = new int[n];
    path[0] = 0;
    for(int i = 1; i < n; i++) {
        path[i] = -1;
    }
    int currCity = 0;

    /* Dodaj obence miasto jako odwiedzone
     * Następnie jako kolejne ustal najbliższe miasto
     * Zwiększ koszt o droge z obecnego do następnego
     * Zmień obecne miasto na nowo dodane
     */
    for(int i = 0; i < n-1; i++) {
        visited[currCity] = true;
        int nextCity = findNeighbour(matrix, n, visited, currCity);
        minCost += matrix[currCity][nextCity];
        currCity = nextCity;
        path[i+1] = currCity;
    }
    // Komiwojażer musi powrócić do miasta startowego więc dodaj koszt przejścia z ostatniego do pierwszego
    minCost += matrix[currCity][0];
    path[n] = 0;
    delete[] visited;

    return std::make_pair(minCost, path);
}

int ProblemSolver::findCost(int **matrix, int *path, int n) {
    int cost = 0;

    for(int i = 0; i < n-1; i++) {
        cost += matrix[path[i]][path[i+1]];
    }

    cost += matrix[path[n-1]][path[0]];
    return cost;
}

void ProblemSolver::inverse(int *path, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, n-1);
    int low = dist(gen);

    int high = dist(gen);
    while(high == low) {
        high = dist(gen);
    }
    if (low > high) {
        std::swap(low, high);
    }

    for (int i = low, j = high; i < j; i++, j--) {
        std::swap(path[i], path[j]);
    }
}

void ProblemSolver::swap(int* path, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, n-1);

    int first = dist(gen);
    int second = dist(gen);
    while(second == first) {
        second = dist(gen);
    }

    std::swap(path[first], path[second]);
}

void ProblemSolver::insert(int* path, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, n-1);

    int first = dist(gen);
    int nodeFirst = path[first];

    int second = dist(gen);
    while(second == first) {
        second = dist(gen);
    }
    int nodeSecond = path[second];

    for(int i = first; i < n-1; i++) {
        path[i] = path[i+1];
    }
    
    for(int i = n-1; i > second; i--) {
        path[i] = path[i-1];
    }
    path[second] = nodeFirst;
}

int* ProblemSolver::getNext(int* path, int n, int c) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);

    int* newPath = new int[n];
    for(int i = 0; i < n; i++) {
        newPath[i] = path[i];
    }

    int choice;
    if(c == -1) {
        choice = dist(gen);
    } else {
        choice = c;
    }

    if(choice == 0) {
        inverse(newPath, n);
    } else if(choice == 1) {
        swap(newPath, n);
    } else if(choice == 2) {
        insert(newPath, n);
    } else {
        std::cerr << "Function getNext() random error!\n";
    }

    return newPath;
}

std::pair<int, int*> ProblemSolver::simAnnealing(int** matrix, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    int* path = new int[n];
    if(useNeighbour) {
        auto result = tspNeighbour(matrix, n);
        int* tempPath = result.second;
        std::copy(tempPath, tempPath + n, path);
        delete[] tempPath;
    } else {
        for(int i = 0; i < n; i++) {
            path[i] = i;
        }
    }

    int bestCost = findCost(matrix, path, n);
    int* bestPath = new int[n];
    std::copy(path, path + n, bestPath);

    auto startTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - startTime;
    while(elapsedTime.count() < seconds) {
        currentTime = std::chrono::steady_clock::now();
        elapsedTime = currentTime - startTime;
        int* newPath = getNext(path, n, definition);
        int newCost = findCost(matrix, newPath, n);
        int costDiff = newCost - findCost(matrix, path, n);

        if(costDiff <= 0) {
            delete[] path;
            path = newPath;
            if (newCost < bestCost) {
                bestCost = newCost;
                std::copy(path, path + n, bestPath);
            }
        } else {
            double rand = dist(gen);
            double prob = std::exp(-costDiff / temp);
            if(rand <= prob) {
                delete[] path;
                path = newPath;
            } else {
                delete[] newPath;
            }
        }
        temp *= alpha;
    }
    delete[] path;
    std::cout << "Best solution found has a cost: " << bestCost << "\nIt is:\n";
    for(int i = 0; i < n; i++) {
        std::cout << bestPath[i] << "-";
    }
    std::cout << bestPath[0] << "\n";
    return std::make_pair(bestCost, bestPath);
}

std::pair<int, int*> ProblemSolver::simAnnealing(int** matrix, int n, int count, std::fstream& output) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    int* path = new int[n];
    if(useNeighbour) {
        auto result = tspNeighbour(matrix, n);
        int* tempPath = result.second;
        std::copy(tempPath, tempPath + n, path);
        delete[] tempPath;
    } else {
        for(int i = 0; i < n; i++) {
            path[i] = i;
        }
    }

    int bestCost = findCost(matrix, path, n);
    int* bestPath = new int[n];
    std::copy(path, path + n, bestPath);

    auto startTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - startTime;
    std::chrono::duration<double> bestTime;
    while(elapsedTime.count() < seconds) {
        currentTime = std::chrono::steady_clock::now();
        elapsedTime = currentTime - startTime;
        int* newPath = getNext(path, n, definition);
        int newCost = findCost(matrix, newPath, n);
        int costDiff = newCost - findCost(matrix, path, n);

        if(costDiff <= 0) {
            delete[] path;
            path = newPath;
            if (newCost < bestCost) {
                bestCost = newCost;
                std::copy(path, path + n, bestPath);
                bestTime = elapsedTime;

                output << count << ";" << bestTime.count() << ";" << bestCost << "\n";
            }
        } else {
            double rand = dist(gen);
            double prob = std::exp(-costDiff / temp);
            if(rand <= prob) {
                delete[] path;
                path = newPath;
            } else {
                delete[] newPath;
            }
        }
        temp *= alpha;
    }
    delete[] path;
    std::cout << "Best solution found has a cost: " << bestCost << "\nIt is:\n";
    for(int i = 0; i < n; i++) {
        std::cout << bestPath[i] << "-";
    }
    std::cout << bestPath[0] << "\n";
    return std::make_pair(bestCost, bestPath);
}