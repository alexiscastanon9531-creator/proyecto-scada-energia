#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura que representa una lectura de sensor energético
typedef struct {
    int id_sensor;
    float valor; // Presión (PSI) para Shellsort | Consumo (MW) para QuickSort
} LecturaEnergia;

// Variables globales para métricas
long comparaciones = 0;
long movimientos = 0;

// ---------------------------------------------------------
// 1. SHELLSORT: Ordenamiento de Presión en Tuberías por Intervalos
// ---------------------------------------------------------
void shellSort(LecturaEnergia arr[], int n) {
    comparaciones = 0;
    movimientos = 0;
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            LecturaEnergia temp = arr[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                comparaciones++;
                if (arr[j - gap].valor > temp.valor) {
                    arr[j] = arr[j - gap];
                    movimientos++;
                } else {
                    break;
                }
            }
            arr[j] = temp;
            movimientos++;
        }
    }
}

// ---------------------------------------------------------
// 2. QUICKSORT: Detección Rápida de Picos de Demanda Eléctrica
// ---------------------------------------------------------
int particion(LecturaEnergia arr[], int bajo, int alto) {
    float pivote = arr[alto].valor;
    int i = (bajo - 1);

    for (int j = bajo; j <= alto - 1; j++) {
        comparaciones++;
        if (arr[j].valor < pivote) {
            i++;
            LecturaEnergia temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            movimientos++;
        }
    }
    LecturaEnergia temp = arr[i + 1];
    arr[i + 1] = arr[alto];
    arr[alto] = temp;
    movimientos++;
    return (i + 1);
}

void quickSort(LecturaEnergia arr[], int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(arr, bajo, alto);
        quickSort(arr, bajo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

int main() {
    LecturaEnergia datos[] = {
        {101, 88.5}, {102, 42.1}, {103, 95.8}, {104, 60.0}, {105, 77.3}
    };
    int n = 5;

    clock_t inicio = clock();
    shellSort(datos, n);
    clock_t fin = clock();
    double tiempo_ms = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;

    printf("Shellsort finalizado en %.4f ms | Comparaciones: %ld | Movimientos: %ld\n", 
           tiempo_ms, comparaciones, movimientos);
    return 0;
}