#include <stdio.h>
#include <time.h>


void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;
    
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];  
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    
    while (i < leftSize) {
        arr[k] = left[i];
        i++;
        k++;
    }

   
    while (j < rightSize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int n) {
    if (n > 1) {
        int mid = n / 2;
        int left[mid];
        int right[n - mid];
        
   
        for (int i = 0; i < mid; i++) {
            left[i] = arr[i];
        }
        
        for (int i = mid; i < n; i++) {
            right[i - mid] = arr[i];
        }

   
        mergeSort(left, mid);
        mergeSort(right, n - mid);

        
        merge(arr, left, mid, right, n - mid);
    }
}

int main() {
    int arr[] = {82,34,90,58,97,21};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    clock_t start_time = clock();
    mergeSort(arr, n);
    clock_t end_time = clock();

    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nTime taken: %f seconds\n", time_taken);

    return 0;
}
