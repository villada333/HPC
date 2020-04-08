#include <iostream>
#include <chrono>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int  **mt1, **mt2, **mt3;
int tam;

void llenar(int ** mt){
    for (int i=0; i<tam; i++){
        for (int j=0; j< tam; j++){
            mt[i][j]= 1+rand() % (20);  // de 1 a 20
        }           
    }
}

void imprimir(int **mt){
    for (int i=0; i<tam; i++){
        printf("\n");
        for (int j=0; j< tam; j++){
            printf("%i\t", mt[i][j]);
        }           
    }
    printf("\n------------------------------------------------------------------------------------------------------------------\n");
}

void multiplicacion(int j){
    for (int i=0; i<tam; i++){
        for(int k=0; k<tam; k++){
            mt3[i][j]+= mt1[i][k]*mt2[k][j];
        }
    }
}

int main(int argc, char *argv[]){
    if (argc==2){
        tam= atoi(argv[1]);  //Numero de filas, columnas y procesos (cada proceso calcula una columna)

        //Se definen las variables compartidas
        mt1=(int **)mmap(NULL,sizeof(int *)*tam, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //Reservar memoria para filas
        mt2=(int **)mmap(NULL,sizeof(int *)*tam, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //Reservar memoria para filas
        mt3=(int **)mmap(NULL,sizeof(int *)*tam, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //Reservar memoria para filas
        for (int i=0; i<tam; i++){
            mt1[i]=(int *)mmap(NULL,sizeof(int)*tam, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //Reservar memoria para filas
            mt2[i]=(int *)mmap(NULL,sizeof(int)*tam, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //Reservar memoria para filas
            mt3[i]=(int *)mmap(NULL,sizeof(int)*tam, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //Reservar memoria para filas
        }

        llenar(mt1);
        llenar(mt2);
        
        int t, status[tam];
        pid_t pid_children[tam];

        auto start = std::chrono::system_clock::now();

        for (t=0; t<tam; t++) {
          /*** error handling ***/
          if ((pid_children[t] = fork()) < 0 ) {
            printf ("No se pudo crear el subproceso\n");
            exit(0);
            }

          /*** this is the child of the fork ***/
          else if (pid_children[t] ==0) {
            multiplicacion(t);
            exit(0);
            }
          }
         //Esperamos a que todos los procesos terminen
         for (t=0; t< tam; t++){
            waitpid(pid_children[t], &status[t], 0);
         }
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<float,std::ratio<1>> duration = end - start;

        printf("%d\t%.3f\n", atoi(argv[1]), duration.count());
        
        //imprimir(mt3);
        //printf("Ultimo %i\n", mt3[tam-1][tam-1]);
        
        //Liberar memoria
        munmap(mt1, sizeof(int *)*tam);
        munmap(mt2, sizeof(int *)*tam);
        munmap(mt3, sizeof(int *)*tam);

    }
    else{
        printf("El numero de argumentos es incorrecto");
    }
}