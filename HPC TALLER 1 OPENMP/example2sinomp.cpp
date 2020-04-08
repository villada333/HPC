#include <stdio.h>
#include <omp.h>
#include <iostream>

using namespace std;

int main(){
	int x;
	x=20;

//	#pragma omp parallel num_threads(12) shared(x)

		if(omp_get_thread_num()==0){
			x=5;
		}else{
			cout<<"1: Thread #: "<<x<<" = "<<omp_get_thread_num()<<endl;
		}
//		#pragma omp barrier
			if(omp_get_thread_num()==0){
				cout<<"2: Thread #: "<<x<<" = "<<omp_get_thread_num()<<endl;
			}else{
				cout<<"3: Thread #: "<<x<<" = "<<omp_get_thread_num()<<endl;
			}
	
	
	return 0;


}