#include "funciones.h"





int main(){
    char nombreArchivo[1000];
    int n;
    printf("Ingrese el nombre de archivo: ");
    gets(nombreArchivo);
    n = obtenerN(nombreArchivo);
    int solucion[n];
    int i;
    for(i = 0; i < n ; i++){//se inicializa para saber cuando terminan las soluciones
        solucion[i] = -1;
    }
    tAct actividades[n];
    llenarActividades(n,actividades,nombreArchivo);
    ordenarActividades(n, actividades);
    seleccionActividades(n,actividades,solucion);
    printf("Total Salas Ocupadas: %i (de %i)\n\n",cantidadMaxActividades,m);
    printf("ASIGNACION:\n\n");
    imprimirSoluciones(n,actividades,solucion);
    //printf("\n\nahora las soluciones y ocupe solo %i !!\n\n",cantidadMaxActividades);
    /*int p;
    for(p = 0; p < n ; p++){
        if(solucion[p]!=-1){
            printf(" %3i ", solucion[p]);
        }
    }*/
    return 0;
}
