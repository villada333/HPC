#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;


void simple(int n, double *a, double *b){
	int i;
	#pragma omp parallel for
	for (i=1; i<n; i++) /* i is private by default */
		b[i] = (a[i] + a[i-1]) / 2.0;
		string str="";
		str+=to_string(i);
		str+=" b = ";
		str+='\n';
		str+=to_string(b[i]);
		cout<<str;
}

int main(){
	int n=1000000;
	double *a=nullptr,*b=nullptr;
	a=new double[n];
	b=new double[n];


	simple(n,a,b);
	return 0;
}