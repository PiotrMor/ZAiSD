#include <iostream>
#include <omp.h>
#include <ctime>


using namespace std;

double f1(double x) {
    return 1 / (1 + x * x);
}

int main() {
    double a = 0, b = 1;
    double dx = 0.00001;
    double result[256];
    int numberOfIterations = (b - a) / dx;
    clock_t startTimer, stopTimer;

    startTimer = clock();

#pragma omp parallel
    {
        int numberOfThreads = omp_get_num_threads();
        int threadID = omp_get_thread_num();
        double area = 0;
        for (int i = threadID; i < numberOfIterations; i += numberOfThreads) {
            area += f1(a + i * dx) * dx;
        }
        result[threadID] = area;
    }

    double totalArea = 0;
    for (int i = 0; i < 8; i ++) {
        totalArea += result[i];
    }
    totalArea *= 4;

    stopTimer = clock();

    cout << totalArea << "     "<< float( stopTimer - startTimer) / CLOCKS_PER_SEC<< endl;

    startTimer = clock();
    double singleThreadResult = 0;
    for (double i = a; i < b; i += dx) {
        singleThreadResult += f1(i) * dx;
    }
    singleThreadResult *= 4;
    stopTimer = clock();
    cout << singleThreadResult << "     "<< float( stopTimer - startTimer) / CLOCKS_PER_SEC<< endl;




    return 0;
}
// pragma  z petla for reduction (t, suma)

