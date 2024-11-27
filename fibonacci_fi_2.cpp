#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

//versión_recursiva
long long fibonacciRecursive(int n) {
    if (n <= 1) return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

//versión_iterativa
long long fibonacciIterative(int n) {
    if (n <= 1) return n;
    long long prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        long long temp = curr;
        curr += prev;
        prev = temp;
    }
    return curr;
}

//versión de división y conquista
void matrixMultiply(long long F[2][2], long long M[2][2]) {
    long long x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    long long y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    long long z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    long long w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void matrixPower(long long F[2][2], int n) {
    if (n <= 1) return;
    long long M[2][2] = {{1, 1}, {1, 0}};
    matrixPower(F, n / 2);//divide %2
    matrixMultiply(F, F);
    if (n % 2 != 0) matrixMultiply(F, M);
}

long long fibonacciMatrix(int n) {
    if (n <= 1) return n;
    long long F[2][2]={{1, 1}, {1, 0}};
    matrixPower(F,n - 1);
    return F[0][0];
}

//medición_de_tiempos
double measureExecutionTime(long long (*fibonacciFunction)(int), int n) {
    auto start = chrono::high_resolution_clock::now();
    fibonacciFunction(n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}

//guardar_csv
void saveResultsToCSV(const string& filename, const vector<tuple<string, int, double>>& results) {
    ofstream file(filename);
    file << "Algorithm,Input Size,Time(ms)\n";
    for (const auto& [algorithm, inputSize, time] : results) {
        file << algorithm << "," << inputSize << "," << fixed << setprecision(6) << time << "\n";
    }
    file.close();
}

int main() {
    vector<int> testSizes = {5,10,15,20,25,30,35,40,45,50,55,60,100,1000, 10000, 100000, 1000000};
    vector<tuple<string, int, double>> results;

    for (int n : testSizes) {
        if (n <= 60) {
            double recursiveTime = measureExecutionTime(fibonacciRecursive, n);
            results.emplace_back("Recursive", n, recursiveTime);
        }

        double iterativeTime = measureExecutionTime(fibonacciIterative, n);
        results.emplace_back("Iterative", n,iterativeTime);

        double matrixTime = measureExecutionTime(fibonacciMatrix, n);
        results.emplace_back("Matrix", n,matrixTime);
    }

    saveResultsToCSV("fibonacci_results_02.csv", results);
    cout << "Results saved to fibonacci_results.csv" << endl;

    return 0;
}
