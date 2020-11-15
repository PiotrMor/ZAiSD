#include <iostream>
#include <omp.h>
#include <ctime>

using namespace std;

double f1(double x) {
    return 1 / (1 + x * x);
}

int main() {
    //VARIABLES
    int a = 0, b = 1;
    double result[256];
    clock_t startTimer, stopTimer;

    cout<<"-----MULTI THREAD-----" <<endl;
    startTimer = clock();
#pragma omp parallel
    {
        int numberOfThreads = omp_get_num_threads();
        cout<<numberOfThreads<<endl;
        int threadID = omp_get_thread_num();
        double dx = 0.000000001;
        int numberOfIterations = (b - a) / dx;

        double area = 0;
        for (int i = threadID; i <= numberOfIterations; i += numberOfThreads) {
            area += f1(i * dx) * dx;
        }
        result[threadID] = area;
    }
    double dx = 0.000000001;
    int numberOfIterations = (b - a) / dx;

    double totalArea = 0;
    for (int i = 0; i < 8; i ++) {
        totalArea += result[i];
    }
    totalArea *= 4;
    stopTimer = clock();
    cout << totalArea << "     "<< float( stopTimer - startTimer) / CLOCKS_PER_SEC<< endl;

    cout<<"-----SINGE THREAD-----" <<endl;
    startTimer = clock();
    double singleThreadResult = 0;
    for (int i = a; i <= numberOfIterations; i++) {
        singleThreadResult += f1(i * dx) * dx;
    }
    singleThreadResult *= 4;
    stopTimer = clock();
    cout << singleThreadResult << "     "<< float( stopTimer - startTimer) / CLOCKS_PER_SEC<< endl;

    cout<<"-----FOR REDUCTION-----" <<endl;
    double forReductionResult = 0.0;
    startTimer = clock();

#pragma omp parallel for reduction(+ : forReductionResult)
    for (int i = a; i <= numberOfIterations; i++) {
        forReductionResult = forReductionResult + f1(i * dx) * dx;
    }
    forReductionResult *= 4;
    stopTimer = clock();

    cout << forReductionResult << "     " << float(stopTimer - startTimer) / CLOCKS_PER_SEC << endl;

    return 0;
}
// pragma  z petla for reduction (t, suma)

