
#include <stdio.h>
#include <stdlib.h>

typedef struct actividad{
 int ini;
 int fin;
 int id;
} tAct;
typedef struct actividad tAct;

int m;
int cantidadMaxActividades;

int obtenerN(char nombreArchivo[1000]){
    FILE *archivo;
    int n;
    if (fopen(nombreArchivo, "r") != NULL){
        archivo = fopen(nombreArchivo, "r");
    }else{
        printf("El archivo no existe!... el programa se va a cerrar");
        exit(1);
    }
    fscanf(archivo,"%i", &n);
    fscanf(archivo,"%i", &m);
    fclose(archivo);
    return n;
}

void llenarActividades(int n,tAct actividades[n], char nombreArchivo[1000]){
    FILE *archivo;
    int aux;
    int i = 0;
    if (fopen(nombreArchivo, "r") != NULL){
        archivo = fopen(nombreArchivo, "r");
    }else{
        printf("El archivo no existe!... el programa se va a cerrar");
        exit(1);
    }
    fscanf(archivo,"%i", &aux);
    fscanf(archivo,"%i", &aux);//se leen las dos primeras filas
    do{
        actividades[i].id = i;
        fscanf(archivo,"%i",&actividades[i].ini);
        //printf("entre...... y n era %i",n);
        i++;
    }while(i<n);//este do while llena la posicion de inicio
    i = 0;
    do{
        fscanf(archivo,"%i",&actividades[i].fin);
        //printf("entre...... y n era %i",n);
        i++;
    }while(i<n);//este do while llena la posicion de fin

}
void ordenarActividades(int n, tAct actividades[n]){
    int i = 0, j = 0, indice = -1;
    int idOcupadas[n];
    int tMax = -1;
    tAct actividadesOrdenadas[n];
    while(i < n){//se inicializa idOcuypadas en 0, ya que ninguna se a ocupado
        idOcupadas[i] = -1;
        i++;
    }
    while(j < n){
        i = 0;
        while(i < n){
            if(idOcupadas[i] == -1 && tMax < actividades[i].fin){//posiciona indice en el elemento a insertar
                tMax = actividades[i].fin;
                indice = i;
            }
            i++;
        }
        actividadesOrdenadas[j] = actividades[indice];
        idOcupadas[indice] = 1;// 1 ya que ya fue insertara
        tMax = - 1;
        j++;
    }
    i = 0;
    while (i < n){//se copia nuevamente a actividades, pero asendentemente
        actividades[i] = actividadesOrdenadas[n-1-i];
        i++;
    }




}
void seleccionActividades(int n, tAct actividades[n], int solucion[n]){
    int i = 0, j = 0, k = 0, tiempo = 0;
    int t = -1;
    int inicio = -1, termino = -1;
    int salasOcupadas = -1;
    int actividadesParalelas[actividades[n-1].fin];//tiene el numero de salas ocupadas en el tiempo i
    while(i < actividades[n-1].fin){
        actividadesParalelas[i] = 0;//se inicializa con todas las salas desocupadas
        i++;
    }
    i = 0;
    int indiceSolucion = 0;
    while(i < n){
        if(i == 0){//no habian soluciones aun
            solucion[i] = actividades[i].id;
            t = actividades[i].ini;
            indiceSolucion++;
            while(t < actividades[i].fin){
                actividadesParalelas[t]++;
                t++;
            }
        }else{//ya hay al menos 1 solucion
            inicio = actividades[i].ini;
            termino = actividades[i].fin;
            salasOcupadas = -1;
            while(inicio < termino){
                if(actividadesParalelas[inicio] > salasOcupadas){//se obtiene el maximo de actividades paraleras en el intervalo inicio,termino
                    salasOcupadas = actividadesParalelas[inicio];
                }
                inicio++;
            }
            if(salasOcupadas < m){//analisis factibilidad ¿hay menos actividas paralelas que salas?
                solucion[indiceSolucion]=actividades[i].id;
                indiceSolucion++;
                t = actividades[i].ini;
                while(t < actividades[i].fin){
                    actividadesParalelas[t]++;
                    t++;
                }

            }
        }
        i++;
    }
    int q;
    for(q = 0 ; q < actividades[n-1].fin ; q++){
        if(cantidadMaxActividades < actividadesParalelas[q]){
            cantidadMaxActividades = actividadesParalelas[q];
        }
    }
}
void imprimirSoluciones(int n, tAct actividades[n],int solucion[n]){
    int i = 0, j = 0;
    int salas[cantidadMaxActividades][actividades[n-1].fin];
    int actividadesPorSala[cantidadMaxActividades][n];
    int indicesSalas[n];
    int v;
    for(v = 0; v < n ; v++){
        indicesSalas[v]=0;//apunta a la posicion donde debo insertar en la sala v
    }
    int k;
    int u;
    for(k = 0 ; k < cantidadMaxActividades ; k++){
        for(u = 0; u < actividades[n-1].fin ; u++){
            salas[k][u]=-1;//ninguna actividad en la sala k, en el tiempo u
        }
    }

    for(k = 0 ; k < cantidadMaxActividades ; k++){
        for(u = 0; u < n ; u++){
            actividadesPorSala[k][u]=-1;//ninguna actividad en la sala k
        }
    }
    i = 0;
    while(i < n){//i recorre las soluciones
        j = 0;
        while(j < cantidadMaxActividades){//j recorre las salas
            if(salaDisponible(n,actividades,salas,solucion[i],j) == 1){//1 la sala esta disponible -1 no
                actividadesPorSala[j][indicesSalas[j]] = solucion[i];
                indicesSalas[j]++;
                break;
            }
            j++;
        }
        i++;
    }
    int g;
    int d;
    for(g = 0 ; g < cantidadMaxActividades ; g++){
        printf("Sala %i: ",g);
        for(d = 0 ; d < n ; d++){
            if(actividadesPorSala[g][d] != -1){
                printf("%3i",actividadesPorSala[g][d]);
            }
        }
        printf("\n");
    }
}
int salaDisponible(int n, tAct actividades[n], int salas[cantidadMaxActividades][actividades[n-1].fin], int idSolucion, int sala){
    int i = 0;
    int inicio = -1, termino = -1;
    while(i < n){
        if(actividades[i].id == idSolucion){
            inicio = actividades[i].ini;
            termino = actividades[i].fin;
            break;
        }
        i++;
    }
    while(inicio < termino){
        if(salas[sala][inicio] == 1){
            return 0;
        }
        inicio++;
    }
    inicio = actividades[i].ini;
    while(inicio < termino){
        salas[sala][inicio] = 1;
        inicio++;
    }
    return 1;
}




