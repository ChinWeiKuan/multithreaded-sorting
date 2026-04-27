/*
 * Project: Multithreaed sorting implementation
 * * Contributors:
 * - Kuan, Chin-Wei (官京緯): Overall architecture
 * - Chen, Ban-Ban (陳半半): Sorting function algorithm
 * Date: Apr 25, 2026
 * Description: 
 * This project implements a multithreaded sorting algorithm. The program divides the original list into two halves, which are sorted by separate threads.
 * After both sorting threads complete, a merging thread combines the sorted halves into a single sorted list.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int original_list[SIZE] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
int sorted_list[SIZE];

typedef struct{
    int start_idx;
    int end_idx;
} parameters;


void *sorter(void *params);
void *merger(void *params);

int main(){
    // Initialization
    pthread_t tid_0, tid_1, tid_merge;
    parameters *data_0, *data_1;

    // 1.Print orginal list before partially sorted
    printf("Original List: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", original_list[i]);
    }
    printf("\n");

    // 2. Create first sorting thread (execute first half list)
    data_0 = (parameters *) malloc(sizeof(parameters));
    data_0->start_idx = 0;
    data_0->end_idx = (SIZE / 2) - 1;
    pthread_create(&tid_0, NULL, sorter, data_0);

    // 3. Create second sorting thread (execute second half list)
    data_1 = (parameters *) malloc(sizeof(parameters));
    data_1->start_idx = SIZE / 2;
    data_1->end_idx = SIZE - 1;
    pthread_create(&tid_1, NULL, sorter, data_1);

    // 4. Main thread await sorting threads complete
    pthread_join(tid_0, NULL);
    pthread_join(tid_1, NULL);

    // 5. Create the merging thread
    pthread_create(&tid_merge, NULL, merger, NULL);
    pthread_join(tid_merge, NULL);

    // 6. Print result
    printf("Sorted List: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", sorted_list[i]);
    }
    printf("\n");
    
    free(data_0); 
    free(data_1);

    return 0;
}


void swap(int *a, int *b){
    int temp=0;
    temp=*a;
    *a=*b;
    *b=temp;
}

void print_range(char *msg, int arr[], int left, int right);

int PARTITION(int arr[], int left, int right){
    int x,i=0;
    x=arr[right];
    i=left-1;
    
    for(int j=left;j<right;j++){
        if (arr[j]<=x){
            i++;
            swap(&arr[i],&arr[j]);
        }
        //printf("[Check A]Loop finished. Pivot value is %d\n",x);
       // print_range("Range before final swap", arr,left,right);
        
    }
    swap(&arr[i+1], &arr[right]);
   // printf("[Check B] Pivot swapped to index %d\n", i + 1);
   // print_range("Range after final swap", arr, left, right);
    
    return i+1;
}

int MEDIAN3_PARTITION(int arr[], int left , int right){
    int mid = left+(right-left)/2;
    // Sorting arr[left],arr[mid],arr[right]
    if (arr[left]>arr[mid]) swap(&arr[left],&arr[mid]);
    if (arr[left]>arr[right]) swap(&arr[left],&arr[right]);
    if (arr[mid]>arr[right]) swap(&arr[mid],&arr[right]);
    
    swap(&arr[mid],&arr[right]);
    
    return PARTITION(arr,left,right);
 
}

void MEDIAN3_QUICKSORT(int arr[],int left, int right){
    int mid=0;
    if (left<right){
        mid=MEDIAN3_PARTITION(arr, left ,right);
        MEDIAN3_QUICKSORT(arr,left,mid-1);
        MEDIAN3_QUICKSORT(arr,mid+1,right);
    }
    return; 
}
// Quicksort
void *sorter(void *params) {
    
    parameters *p=(parameters *)params;
    
    int left,right=0;
    left=p->start_idx;
    right=p->end_idx;
    
    MEDIAN3_QUICKSORT(original_list, left,right);    
    pthread_exit(0);
}



void *merger(void *params) {
    // TODO: merge original_list and store the result into sorted_list
    int size = sizeof(original_list)/sizeof((original_list[0]));
    int i=0;
    int j=(size/2);
    int k=0;
    
    while (i<size/2 && j<size){
        if (original_list[i]<=original_list[j]){
            sorted_list[k]=original_list[i];
            i++;
        }else{
            sorted_list[k]=original_list[j];
            j++;
        }
        k++;
    }
    while (i<size/2){
        sorted_list[k]=original_list[i];
        i++;
        k++;
    }
    while (j<size){
        sorted_list[k]=original_list[j];
        j++;
        k++;
    }

    pthread_exit(0);
}


void print_range(char *msg, int arr[], int left, int right){
    printf("%s: ",msg);
    for (int i=left;i<=right;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}