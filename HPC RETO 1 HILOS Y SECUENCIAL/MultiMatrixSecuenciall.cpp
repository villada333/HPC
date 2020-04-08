#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <ctime>
using namespace std;

void fillmatrix(vector <vector <int>> &vy){
    int number=0;
    for (int i = 0; i < vy.size(); i++){ // loops through each row of vy
        for (int j = 0; j < vy[i].size(); j++) {// loops through each element of each row
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

void multiplication(vector <vector <int>> &a,vector <vector <int>> &b, vector <vector <int>> &c,int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    c[i][j]+=a[i][k]*b[k][j];
                }
        }
    }
}

int main(int argc, char const *argv[]){
    cout<<"Multiplicacion de matrices sin hilos, ingrese tamano de fila y columna: ";
	int n,m,p;
	unsigned t0, t1;
	cin>>n;
  m=n;
	vector< vector<int>> a (n, vector <int> (m));
	vector< vector<int>> b (n, vector <int> (m));
	vector< vector<int>> c (n, vector <int> (m));

	fillmatrix(a);
	fillmatrix(b);
    //display(a);
    //display(b);
    //display(c);

    t0=clock();
    multiplication(a,b,c,n);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    //display(a);
    //display(b);
    //display(c);

	return 0;
}