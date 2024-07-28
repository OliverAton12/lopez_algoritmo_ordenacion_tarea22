//fecha: 28/07/24
////Autor:Lopez Quiroz Wagner
//tema:  Utilice el programa que mide el tiempo de ejecución de los algoritmos de ordenación. a) Agregue el algoritmo de ordenación secuencial.
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace std::chrono;

const int MAX_SIZE = 60000;

// Función de ordenación secuencial (selection sort)
void ordenacion_secuencial(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

// Función de ordenación Burbuja Mejorado
void burbuja_mejorado(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// Función de ordenación Shell
void shell_sort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Función de ordenación Shell Optimizado (usa la misma lógica de shell_sort)
void shell_sort_optimizado(int arr[], int n) {
    shell_sort(arr, n); // Para simplificar, usamos la misma función shell_sort
}

// Función para particionar el arreglo para Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Función de ordenación Quick Sort
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Función para generar un arreglo aleatorio
void generate_random_array(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % size + 1;
    }
}

// Función para medir el tiempo de ejecución de un algoritmo de ordenación
void measure_time(void (*sort_function)(int[], int), int arr[], int size) {
    int* copy = new int[size];
    for (int i = 0; i < size; ++i) {
        copy[i] = arr[i];
    }
    
    auto start = high_resolution_clock::now();
    sort_function(copy, size);
    auto end = high_resolution_clock::now();
    
    duration<double> duration = end - start;
    cout << setw(10) << fixed << setprecision(6) << duration.count() << "\t";
    
    delete[] copy;
}

int main() {
    srand(time(0));
    
    int sizes_small[] = {10, 20, 30, 40, 50};
    int sizes_large[] = {5000, 15000, 30000, 45000, 60000};

    int* array = new int[MAX_SIZE];

    // Medidas para listas pequeñas
    cout << "Medidas para listas pequeñas:" << endl;
    cout << setw(20) << "ALGORITMO" 
         << setw(15) << "10" 
         << setw(15) << "20" 
         << setw(15) << "30" 
         << setw(15) << "40" 
         << setw(15) << "50" << endl;

    string algorithms[] = {"Secuencial", "Burbuja Mejorado", "Shell", "Shell Optimizado", "Quick Sort"};
    
    for (const auto& alg : algorithms) {
        cout << setw(20) << alg;
        for (const auto& size : sizes_small) {
            generate_random_array(array, size);
            if (alg == "Secuencial") {
                measure_time(ordenacion_secuencial, array, size);
            } else if (alg == "Burbuja Mejorado") {
                measure_time(burbuja_mejorado, array, size);
            } else if (alg == "Shell") {
                measure_time(shell_sort, array, size);
            } else if (alg == "Shell Optimizado") {
                measure_time(shell_sort_optimizado, array, size);
            } else if (alg == "Quick Sort") {
                measure_time([](int arr[], int n) { quick_sort(arr, 0, n - 1); }, array, size);
            }
        }
        cout << endl;
    }

    // Medidas para listas grandes
    cout << "Medidas para listas grandes:" << endl;
    cout << setw(20) << "ALGORITMO" 
         << setw(15) << "5000" 
         << setw(15) << "15000" 
         << setw(15) << "30000" 
         << setw(15) << "45000" 
         << setw(15) << "60000" << endl;

    for (const auto& alg : algorithms) {
        cout << setw(20) << alg;
        for (const auto& size : sizes_large) {
            generate_random_array(array, size);
            if (alg == "Secuencial") {
                measure_time(ordenacion_secuencial, array, size);
            } else if (alg == "Burbuja Mejorado") {
                measure_time(burbuja_mejorado, array, size);
            } else if (alg == "Shell") {
                measure_time(shell_sort, array, size);
            } else if (alg == "Shell Optimizado") {
                measure_time(shell_sort_optimizado, array, size);
            } else if (alg == "Quick Sort") {
                measure_time([](int arr[], int n) { quick_sort(arr, 0, n - 1); }, array, size);
            }
        }
        cout << endl;
    }

    delete[] array;

    return 0;
}

