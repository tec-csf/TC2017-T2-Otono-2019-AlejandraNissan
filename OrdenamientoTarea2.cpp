/*
Alejandra Nissan
A01024682
Tarea 2 analisis de algoritmos de ordenamiento
Fecha: 6/09/2019
*/

#include"Bst.h"//Para binary search tree
#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <ctime>
#include <vector>
#include <algorithm> 
#include <bits/stdc++.h> 
#include <chrono>

using namespace std;
using namespace std::chrono;

class Ordenador{
public:
    void Intercambia(int, int, int*);
    virtual void Ordena(int*, int);
    void imprimirArreglo(int*, int);
    void OrdenaCounting(int[], int, int);
};

void Ordenador::Ordena(int*, int){
}

void Ordenador::Intercambia(int i, int j, int* arreglo){
int temporal=arreglo[i];
arreglo[i]=arreglo[j];
arreglo[j]=temporal;
}

void Ordenador::imprimirArreglo(int* a, int length){
   
    std:: cout<<"\n\n Arreglo ordenado: "<<endl;
    for(int i=0; i<=length-1; i++){
        std::cout<<*(a+i)<<endl;
    }//End of for
}

//Counting sort
//Se encuentra en la super clase ya que es utilizado por bucketSort
void Ordenador::OrdenaCounting(int arr[],int n,int RANGE){
    int count[RANGE]={0};

    int i;

    int out[n];

    for(i=0;i<n;i++)
    ++count[arr[i]];

    for(i=1;i<RANGE;i++)
    count[i]+=count[i-1];

    for(i=n-1;i>=0;i--){
        out[count[arr[i]]-1]=arr[i];
        --count[arr[i]];
    }

    
    for(i=0;i<n;i++)
    arr[i]=out[i];
}//End of counting sort

class OrdenamientoBubbleSort : public Ordenador{
    public:
    void Ordena(int *, int);
};

//BUBBLE SORT
void OrdenamientoBubbleSort::Ordena(int *a, int length){
    int i, j, inter;

    for(int i=0; i< length; i++){
        for(int j=0; j < length-1; j++){
            if (*(a+j)>*(a+j+1)){
                inter = *(a+j);
                *(a+j)= *(a+j+1);
                *(a+j+1)=inter;
            }//end of if
        }//End of first for
    }//End of second for
}//End of bubble sort

//COCKTAIL SORT su nivel de complejidad es igual al de bubble aunque lo derrota por tiempo. 
//Igual a bubble pero va de ida y de vuelta
class OrdenamientoCocktailSort : public Ordenador{
    public:
    void Ordena(int *, int);
};

void OrdenamientoCocktailSort::Ordena(int*a, int length){
    bool swapped = true; 
    int start = 0; 
    int end = length - 1; 
    int temp = 0;
  
    while (swapped) { 
        //Se hace falsa y si se hace switch se vuelve verdadera para permanecer en el while
        swapped = false; 
  
        // Recorrido de izquierda a derecha
        for (int i = start; i < end; ++i) { 
            if (*(a+i) > *(a+i+1)){ 
                temp=  *(a+i);
                *(a+i)=*(a+i+1);
                *(a+i+1)=temp;
                swapped = true;
            } 
        } 
  
        // Si no entra al if significa que ya se encuentra ordenado 
        if (!swapped) 
            break; 
  
        // Sino hacer swapped falso otra vez
        swapped = false; 
  
        // Se resta a end, para evitar repetir numeros ya ordenados
        --end; 
  
        // Recorrido de derecha a izquierda  
        for (int i = end - 1; i >= start; --i) { 
            if (*(a+i) > *(a + i + 1)) { 
                temp=  *(a+i);
                *(a+i)=*(a+i+1);
                *(a+i+1)=temp;
                swapped = true; 
            } 
        } 
  
        // Sumar al principio del recorrido para no repetir numeros ya ordenados
        ++start; 
    } 
}//End of CocktailSort
  
    


//INSERTION SORT
class OrdenamientoInsertionSort : public Ordenador{
    public:
    void Ordena (int*, int);
};

void OrdenamientoInsertionSort::Ordena(int* a, int length){
    int i = 1, j=0, guardar=0, veces=0;
    
    for(i=1; i<=length-1; i++){
        guardar = *(a+i);
            for(j=i; j>=1; j--){
                if (*(a+j-1)>guardar){
                    *(a+j)= *(a+j-1);
                    if((j-1)==0 ){
                        *a = guardar;
                    };
                }//End of if
                
                else if((*(a+j-1)<=guardar)&&(*(a+j+1)>guardar)){
                    *(a+j)=guardar;
                }//End of else if
            }//End of for
    }//End of for
}//End of insertion sort

/*
//BUCKET SORT
class OrdenamientoBucketSort : public Ordenador{
    public:
    void Ordena (int*, int);
    void OrdenaMasParametros(int[], int, int);
    //void OrdenaMasParametros(int*, int, int);
};

void OrdenamientoBucketSort::Ordena(int* a, int){
}//End of Ordena

void OrdenamientoBucketSort::OrdenaMasParametros(int arr[], int n, int k) 
{ 
    
    // 1) Create n empty buckets 
    vector<int> b[n]; 
     
    // 2) Put array elements in different buckets 
    for (int i=0; i<n; i++) 
    { 
       int bi = (n*arr[i])/k; // Index in bucket 
       b[bi].push_back(arr[i]); 
       //AQUI SE TRABA CHECAR N
    } 
  
    // 3) Sort individual buckets 
    for (int i=0; i<n; i++) 
       sort(b[i].begin(), b[i].end()); 
  
    // 4) Concatenate all buckets into arr[] 
    int index = 0; 
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < b[i].size(); j++) 
          arr[index++] = b[i][j]; 
} 
// void OrdenamientoBucketSort::OrdenaMasParametros(int* a, int length, int k){
    
//     //Se crean las cubetas para el numero de elementos en el arreglo
//     vector<int> buckets[length]; 
    
     
//     //Colocar los elementos en las cubetas
//     for (int i=0; i<length; i++) 
//     { 
//        int bi = length*(*(a+i)); // Index in bucket 
//        buckets[bi].push_back(*(a+i)); 
//     } 
  
//     // 3) Sort individual buckets 
//     for(int i=0; i<length; i++){
//         sort(buckets[i].begin(), buckets[i].end());
//     };
    

//     //Concatenar las cubetas
//     int index = 0; 
//     for (int i = 0; i < length; i++) {
//         for (int j = 0; j < buckets[i].size(); j++) {
//           *(a+index++)= buckets[i][j]; 
//         }
//     }   
// } 
*/
//MERGE SORT
class OrdenamientoMergeSort : public Ordenador{
    public:
    void Ordena (int*, int);
    void mergeSort(int*, int, int);
    void merge(int *, int, int, int);
};

void OrdenamientoMergeSort::Ordena(int* a, int length){
    mergeSort(a, 0, length-1);
}
void OrdenamientoMergeSort::mergeSort(int *array, int l, int r) {
   int m;
   if(l < r) {
      int m = l+(r-l)/2;
      // Sort first and second arrays
      mergeSort(array, l, m);
      mergeSort(array, m+1, r);
      merge(array, l, m, r);
   }
}

void OrdenamientoMergeSort::merge(int *array, int l, int m, int r) {
   int i, j, k, nl, nr;
   //size of left and right sub-arrays
   nl = m-l+1; nr = r-m;
   int larr[nl], rarr[nr];
   //fill left and right sub-arrays
   for(i = 0; i<nl; i++)
      larr[i] = array[l+i];
   for(j = 0; j<nr; j++)
      rarr[j] = array[m+1+j];
   i = 0; j = 0; k = l;
   //marge temp arrays to real array
   while(i < nl && j<nr) {
      if(larr[i] <= rarr[j]) {
         array[k] = larr[i];
         i++;
      }else{
         array[k] = rarr[j];
         j++;
      }
      k++;
   }
   while(i<nl) {       //extra element in left array
      array[k] = larr[i];
      i++; k++;
   }
   while(j<nr) {     //extra element in right array
      array[k] = rarr[j];
      j++; k++;
   }
} 

//RADIX SORT
class OrdenamientoRadixSort : public Ordenador{
    public:
    void Ordena (int*, int);
    void radixsort(int[], int);
    int getMax(int [], int);
    void countSort(int[], int, int);
};

void OrdenamientoRadixSort::Ordena(int* a, int length){

}

void OrdenamientoRadixSort::radixsort(int arr[], int n) 
{ 
    // Find the maximum number to know number of digits 
    int m = getMax(arr, n); 
  
    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; m/exp > 0; exp *= 10) 
        countSort(arr, n, exp); 
} 

int OrdenamientoRadixSort::getMax(int arr[], int n){
    int mx = arr[0]; 
    for (int i = 1; i < n; i++) 
        if (arr[i] > mx) 
            mx = arr[i]; 
    return mx; 
}
                            
void OrdenamientoRadixSort::countSort(int arr[], int n, int exp){
    int output[n]; // output array 
    int i, count[10] = {0}; 
  
    // Store count of occurrences in count[] 
    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 
  
    // Change count[i] so that count[i] now contains actual 
    //  position of this digit in output[] 
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    // Build the output array 
    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
  
    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
}


//SHELL SORT
class OrdenamientoShellSort : public Ordenador{
    public:
    void Ordena (int*, int);
    void Ordena2 (int[], int);
};

void OrdenamientoShellSort::Ordena(int* a, int length){

}

void OrdenamientoShellSort::Ordena2(int arr[], int n){
    // Start with a big gap, then reduce the gap 
     cout<<"Entre"<<endl;
    for (int gap = n/2; gap > 0; gap /= 2) 
    { 
       
        // Do a gapped insertion sort for this gap size. 
        // The first gap elements a[0..gap-1] are already in gapped order 
        // keep adding one more element until the entire array is 
        // gap sorted  
        for (int i = gap; i < n; i += 1) 
        { 
            // add a[i] to the elements that have been gap sorted 
            // save a[i] in temp and make a hole at position i 
            int temp = arr[i]; 
  
            // shift earlier gap-sorted elements up until the correct  
            // location for a[i] is found 
            int j;             
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap]; 
            }
            //  put temp (the original a[i]) in its correct location 
            arr[j] = temp; 
        } 
    } 
}//End of shell short

//SELECTION SORT
class OrdenamientoSelectionSort : public Ordenador{
    public:
    void Ordena (int*, int);
};

void OrdenamientoSelectionSort::Ordena(int * a, int length){
    int min = *a;
    int minPos = 0, temp=0;
    int guardar = 0, i=0, j=0;

    for (i = 0; i <= length-1; i++){
        min = *(a+i);
        minPos= i;
       for (j = i; j <= length-2; j++){
            if (min>*(a+j+1)){
                min = *(a+j+1);
                minPos = j+1;
            }   //End of if  
           
       }//End of for
    }//End of for

}//End of selectionSort

//HEAP SORT
class OrdenamientoHeapSort : public Ordenador{
    public:
    void Ordena (int*, int);
    void heapSort(int[], int);
    void heapify(int[], int, int);
};

void OrdenamientoHeapSort::Ordena(int * a, int length){
}

void OrdenamientoHeapSort::heapSort(int arr[], int n) {
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>=0; i--) 
    { 
        // Move current root to end 
        //swap(arr[0], arr[i]); 
        int temp = arr[0];
        arr[0]=arr[i];
        arr[i]=temp;
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0); 
    } 
} 

void OrdenamientoHeapSort::heapify(int arr[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
        //swap(arr[i], arr[largest]); 
        int temp = arr[i];
        arr[i]=arr[largest];
        arr[largest]=temp;
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
    } 
} 
  
//QUICK SORT
class OrdenamientoQuickSort : public Ordenador{
    public:
    void Ordena (int*, int);
    void quickSort(int[], int, int);
    int partition (int[], int, int);
    void swap(int*, int*);
};

void OrdenamientoQuickSort::Ordena(int * a, int length){
}

void OrdenamientoQuickSort::quickSort(int arr[], int low, int high){
if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}

int OrdenamientoQuickSort::partition (int arr[], int low, int high){
int pivot = arr[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}

void OrdenamientoQuickSort::swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  

//MAIN
int main(){
/*Es importante correr cada algoritmo por separado para no sobrecargar a la computadora, es por eso que mucho código se encuentra comentado*/

//Creación del arreglo
int length = 10;
int k=length*10;
double t;


int arregloBubbleSort[length] = {};
int arregloInsertionSort[length] = {};
// int arregloSelectionSort[length] = {};
int arregloCocktailSort[length] = {};
// int arregloCountingSort[length] = {};
// //int arregloBucketSort[length] = {};
// int arregloMergeSort[length]={};
// int arregloRadixSort[length]={};
// int arregloShellSort[length]={};
// int arregloHeapSort[length]={};
// int arregloQuickSort[length]={};


srand(time(NULL));

for(int i=0; i<length; i++){
    arregloBubbleSort[i]=rand()%k;
    arregloInsertionSort[i]=arregloBubbleSort[i];
    //arregloSelectionSort[i]=arregloInsertionSort[i];
     arregloCocktailSort [i]=arregloInsertionSort[i];
    //arregloCountingSort [i]=arregloInsertionSort[i];
    // //arregloBucketSort[i]=arregloInsertionSort[i];
    // arregloMergeSort [i]=arregloInsertionSort[i];
    // arregloRadixSort[i]=arregloInsertionSort[i];
    // arregloShellSort [i]=arregloInsertionSort[i];
    // arregloHeapSort[i]=arregloInsertionSort[i];
    // arregloQuickSort[i]=arregloInsertionSort[i];
}//End of for

// int* aBubbleSort = arregloBubbleSort;
// int* aInsertionSort = arregloInsertionSort;
// int* aSelectionSort = arregloInsertionSort;
 int * aCocktailSort = arregloCocktailSort;
// int * aCountingSort = arregloCountingSort;
// //int* aBucketSort = arregloBucketSort;
// int * aMergeSort = arregloMergeSort;
// int * aRadixSort = arregloRadixSort;
// int * aShellSort = arregloShellSort;
// int* aHeapSort = arregloHeapSort;
// int* aQuickSort = arregloQuickSort;

//Creación de los objetos
// OrdenamientoBubbleSort pruebaBubbleSort;
// OrdenamientoInsertionSort pruebaInsertionSort;
// OrdenamientoSelectionSort pruebaSelectionSort;
 OrdenamientoCocktailSort pruebaCocktailSort;
// Ordenador pruebaCountingSort;
// //OrdenamientoBucketSort pruebaBucketSort;
// OrdenamientoMergeSort pruebaMergeSort;
// OrdenamientoRadixSort pruebaRadixSort;
// OrdenamientoShellSort pruebaShellSort;
// OrdenamientoHeapSort pruebaHeapSort;
// OrdenamientoQuickSort pruebaQuickSort;

/*for(int i=0; i<length; i++){
    cout<<*(aBubbleSort+i)<<" ";
}//End of for que imprime el arreglo
cout<<""<<endl;*/

//Llamadas a los métodos
// auto start = high_resolution_clock::now();
// pruebaBubbleSort.Ordena(aBubbleSort, length);
// auto stop = high_resolution_clock::now();
// auto duration = duration_cast<microseconds>(stop-start);
// cout<<"Bubble sort: "<<duration.count()<<" microsegundos"<<endl;


auto start = high_resolution_clock::now();
pruebaCocktailSort.Ordena(aCocktailSort, length);
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop-start);
cout<<"Cocktail sort: "<<duration.count()<<" microsegundos"<<endl; 


// auto start = high_resolution_clock::now();
// pruebaInsertionSort.Ordena(aInsertionSort, length);
// auto stop = high_resolution_clock::now();
// auto duration = duration_cast<microseconds>(stop-start);
// cout<<"Insertion sort: "<<duration.count()<<" microsegundos"<<endl; 


// auto start = high_resolution_clock::now();
// pruebaSelectionSort.Ordena(aSelectionSort, length);
// auto stop = high_resolution_clock::now();
// auto duration = duration_cast<microseconds>(stop-start);
// cout<<"Selection sort: "<<duration.count()<<" microsegundos"<<endl;

// auto start = high_resolution_clock::now();
// pruebaCountingSort.OrdenaCounting(arregloCountingSort, length, k);
// auto stop = high_resolution_clock::now();
// auto duration = duration_cast<microseconds>(stop-start);
// cout<<"Counting sort: "<<duration.count()<<" microsegundos"<<endl;

//pruebaBucketSort.OrdenaMasParametros(arregloBucketSort, length, k);

// auto start = high_resolution_clock::now();
// pruebaMergeSort.Ordena(aMergeSort, length);
// auto stop = high_resolution_clock::now();
// auto duration = duration_cast<microseconds>(stop-start);
// cout<<"Merge sort: "<<duration.count()<<" microsegundos"<<endl;

/*
auto start = high_resolution_clock::now();
pruebaRadixSort.radixsort(arregloRadixSort, length);
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop-start);
cout<<"Radix sort: "<<duration.count()<<" microsegundos"<<endl;
*/

// auto start = high_resolution_clock::now();
// pruebaShellSort.Ordena2(arregloShellSort, length);
// auto stop = high_resolution_clock::now();
// auto duration = duration_cast<microseconds>(stop-start);
// cout<<"Shell sort: "<<duration.count()<<" microsegundos"<<endl;


// auto start = high_resolution_clock::now();
// pruebaHeapSort.heapSort(arregloHeapSort, length);
// auto stop = high_resolution_clock::now();
// auto duration = duration_cast<microseconds>(stop-start);
// cout<<"Heap sort: "<<duration.count()<<" microsegundos"<<endl;


// auto start = high_resolution_clock::now();
// pruebaQuickSort.quickSort(arregloQuickSort,0, length-1);
// auto stop = high_resolution_clock::now();
// auto duration = duration_cast<microseconds>(stop-start);
// cout<<"Quick sort: "<<duration.count()<<" microsegundos"<<endl;

/*for(int i=0; i<length; i++){
    cout<<*(aSelectionSort+i)<<" ";
}//End of for que imprime el arreglo*/

cout<<""<<endl;

return 0;
}//End of main


//REFERENCIAS
/*
Bubble sort, insertion sort y selection sort fueron realizados por mi
Cocktail sort fue obtenido de //https://www.geeksforgeeks.org/cpp-program-for-cocktail-sort/
Bucket sort fue obtenido de https://www.geeksforgeeks.org/bucket-sort-2/
Counting sort fue obtenido de https://gist.github.com/0001vrn/0dc4491331a2753a0ecbce6d66566cbf
Merge sort https://www.tutorialspoint.com/cplusplus-program-to-implement-merge-sort
Radix sort fue obtenido de https://www.geeksforgeeks.org/radix-sort/
Heap Sort fue obtenido de https://www.geeksforgeeks.org/heap-sort/
Quick Sort fue obtenido de https://www.geeksforgeeks.org/quick-sort/
Shell sort fue obtenido de https://www.geeksforgeeks.org/shellsort/
*/