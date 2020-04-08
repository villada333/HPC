#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

void imprimir(string a, double *u, int n){


    cout<<a<<endl;
    for(int i=0;i<=n;i++){

        
        cout<<u[i]<<" ";
    }
    cout << endl;
}


void runbychunk(int i, int j, int n, int h2,  double *u, double *utmp, double *f){


    if(n+1 % 2 == 0){ //es par
        if(i == 0){
                //primera parte del arreglo
                for(int h = 1; h < (n+1)/2; ++h)
                    utmp[h] = (u[h-1] + u[h+1] + h2*f[h])/2;
        }else{
            //segunda parte del arreglo
                for(int h = (n+1)/2; h < n; ++h)
                    utmp[h] = (u[h-1] + u[h+1] + h2*f[h])/2;
        }
    }else{//es impar
        if(i == 0){
            //primera parte del arreglo
                for(int h = 1; h <= j; ++h)
                    utmp[h] = (u[h-1] + u[h+1] + h2*f[h])/2;

        }else{
            //segunda parte del arreglo
            for(int h = ((n+1)/2)+1; h < n; ++h)
                utmp[h] = (u[h-1] + u[h+1] + h2*f[h])/2;
        }   

    }
    
      
}

void jacobi(int nsweeps, int n, double* u, double* f){
    double h  = 1.0 / n;
    double h2 = h*h;
    double* utmp;
    utmp = new double[n+1];

    /* Fill boundary conditions into utmp */
    utmp[0] = u[0];
    utmp[n] = u[n];

    /*cout << "h2 "<< h2 << endl;
    imprimir("inicio f: ", f, n);
    imprimir("inicio: ", utmp, n);
    imprimir("inicio: ", u, n);*/
    for (int sweep = 0; sweep < nsweeps; sweep += 2) {
        vector<thread> th1;
        th1.push_back(thread(runbychunk,0,(n+1)/2, n,h2,u,utmp,f));
        th1.push_back(thread(runbychunk,(n+1)/2,n,n,h2,u,utmp,f));
        //primer chunk
        for(int i = 0; i < th1.size(); i++)
            th1[i].join();
        vector<thread> th2;
        //segundo chunk

        th2.push_back(thread(runbychunk,0,(n+1)/2,n,h2,utmp,u,f));
        th2.push_back(thread(runbychunk,(n+1)/2 +1, n+1, n,h2,utmp,u,f));
        //primer chunk
        for(int i = 0; i < th2.size(); i++)
            th2[i].join();
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
