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

    return 0;
}

void *sorter(void *params) {
    parameters *p = (parameters *)params;
    
    // TODO: sort original_list by using from p->start_idx to p->end_index
    // You can choose any sorting algorithm prefered
    
    pthread_exit(0);
}

void *merger(void *params) {
    // TODO: merge original_list and store the result into sorted_list
    
    pthread_exit(0);
}