#include "ProblemSolver.h"
#include <random>
#include <iostream>
#include <chrono>

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

int* ProblemSolver::getNext(int* path, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);

    int* newPath = new int[n];
    for(int i = 0; i < n; i++) {
        newPath[i] = path[i];
    }

    int choice = dist(gen);

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

int ProblemSolver::simAnnealing(int** matrix, int n, double t, double a, double seconds) {
    double temp = t;
    double alpha = a;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    int* path = new int[n];
    for(int i = 0; i < n; i++) {
        path[i] = i;
    }
    int count = 0;

    auto startTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - startTime;
    while(elapsedTime.count() < seconds) {
        currentTime = std::chrono::steady_clock::now();
        elapsedTime = currentTime - startTime;
        int* newPath = getNext(path, n);

        int costDiff = findCost(matrix, newPath, n) - findCost(matrix, path, n);

        if(costDiff < 0) {
            delete[] path;
            path = newPath;
        } else if(costDiff == 0) {
            delete[] path;
            path = newPath;
        } else {
            double rand = dist(gen);
            double prob = std::exp(-costDiff / temp);
            if(rand <= prob) {
                delete[] path;
                path = newPath;
            }
        }
        temp *= alpha;
        count++;
    }
    return findCost(matrix, path, n);
}