#include <stdio.h>
#include <time.h>

void bubbleSort(int arr[], int n) {
    int temp; 
    int swapped; 
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j]; 
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1; 
            }
        }
        if (swapped == 0)
            break;
    }
}

int main() {
    int arr[] = {23,73,54,92,90,34};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    
    printf("\n");

    clock_t start_time = clock();
    bubbleSort(arr, n);
    clock_t end_time = clock();

    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\nTime taken: %f seconds\n", time_taken);

    return 0;
}
