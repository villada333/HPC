#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <chrono>
#include <iostream>

using namespace std;



void jacobi(int nsweeps, int n, double* u, double* f){
    double h  = 1.0 / n;
    double h2 = h*h;
    double* utmp;
    utmp = new double[n+1];

    /* Fill boundary conditions into utmp */
    utmp[0] = u[0];
    utmp[n] = u[n];

    for (int sweep = 0; sweep < nsweeps; sweep += 2) {

        /* Old data in u; new data in utmp */
        for (int i = 1; i < n; ++i){
            utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;
        }

        /* Old data in utmp; new data in u */
        for (int i = 1; i < n; ++i){
            u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;
        }
    }

    delete [] utmp;
}


int main(int argc, char** argv){
    if(argc < 2){
		printf("There should be 3 or 2 arguments! (outputfile is optional)-> nameexecute.exe $n $steps $outputfile\n");
		exit(1);
	}
    int n, nsteps;
    double* u;
    double* f;
    double h;
    char* fname;

    /* Process arguments */
    n      = (argc > 1) ? std::stoll(argv[1], nullptr) : (int)100;
    nsteps = (argc > 2) ? std::stoll(argv[2], nullptr) : (int)100;
    fname  = (argc > 3) ? argv[3] : NULL;
    h      = 1.0/n;

    /* Allocate and initialize arrays */
    u = new double[n+1];
    f = new double[n+1];
    memset(u, 0, (n+1) * sizeof(double));
    for (int i = 0; i <= n; ++i){
        f[i] = i * h;
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    jacobi(nsteps, n, u, f);


    end = std::chrono::system_clock::now();
    double time = std::chrono::duration_cast<std::chrono::nanoseconds>
    (end-start).count();

    cout << time << ",";

    delete [] f;
    delete [] u;
    return 0;
}
