#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
using namespace std;



void fillmatrix(vector <vector <int>> &vy){
        int number=0;
        for (int i = 0; i < vy.size(); i++){ // loops through each row of vy
                for (int j = 0; j < vy[i].size(); j++) {// loops through eachelement of each row
                        number = rand() % 1000 + 1;
                        vy[i][j]=number;
                }
        }
}

void display (const vector <vector <int>> vy){
        for (int i = 0; i < vy.size(); i++){ // loops through each row of vy
                for (int j = 0; j < vy[i].size(); j++) // loops through each element of each row
                        cout << " " << vy[i][j];           // prints the jth element of the ith row
                cout << endl;
        }
        cout << endl;
}

void multiplication(vector< vector<int>> &va,vector< vector<int>> &vb,vector< vector<int>> &vc,int i,int j,int n){
        for (int i = 0; i < n; i++){
                for (int k = 0; k < n; k++) {
                        vc[i][j]+=va[i][k]*vb[k][j];
                }
        }
}


int main(int argc, char const *argv[]){
        cout<<"Multiplicacion de matrices con hilos en cada Multiplicacion, ingrese tamano de fila y columna: ";
        int n;int m;int i;int j;

        cin>>n;
        m=n;

        vector< vector<int>> a (n, vector <int> (m));
        vector< vector<int>> b (n, vector <int> (m));
        vector< vector<int>> c (n, vector <int> (m));

        fillmatrix(a);
        fillmatrix(b);

//      display(a);
//      display(b);
//      display(c);

        vector<thread> ths;

        auto start = std::chrono::system_clock::now();
    	
//      for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++) {
                        ths.push_back(thread(multiplication,ref(a),ref(b),ref(c),i,j,n));
//              }
        }
        for(thread &t:ths){t.join();}


    	auto end = std::chrono::system_clock::now();
 
    	std::chrono::duration<double> elapsed_seconds = end-start;
    	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    	std::cout << "finished computation at " << std::ctime(&end_time)<< "elapsed time: " << elapsed_seconds.count() << "s\n";


//      display(a);
//      display(b);
//      display(c);

        return 0;
}

//g++ -std=c++11 -pthread -o main multimatrixallthreads.cpp