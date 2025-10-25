
//Задание 1-2
#include <stdlib.h>
#include <stdio.h>

void fill_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i+1;
    }
}

void show_array(int arr[], int size) {
    printf("Array: [");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]");
}

void find_smallest(int arr[], int size) {
    int min = arr[0];
    for (int i = 0; i < size; i++) {
        if(arr[i] <= min)
        min = arr[i];
    }
    printf("\nSmallest %d", min);
}

void find_biggest(int arr[], int size) {
    int max = arr[0];
    for (int i = 0; i < size; i++) {
        if(arr[i] > max)
        max = arr[i];
    }
    printf("\nBiggest %d", max);
}

int main(){
    int size;

    printf("Enter array size: ");
    scanf(" %d", &size);

    int arr[size];

    fill_array(arr, size);
    show_array(arr, size);
    find_smallest(arr, size);
    find_biggest(arr, size);

    return 0;
}

/*
//Задание 3-4
#include <stdlib.h>
#include <stdio.h>

void copy_array(int original[], int copy[], int size) {
    for (int i = 0; i < size; i++) {
        copy[i] = original[i];
    }

    printf("\nCopied array: [");
    for (int i = 0; i < size; i++) {
        printf(" %d", copy[i]);
    }
    printf("]\n");

    copy[0] = 100;
     printf("\nEdited copied array: [");
    for (int i = 0; i < size; i++) {
        printf(" %d", copy[i]);
    }
    printf("]\n");

}

int main() {
    int n;
    int *dynamic_array;
    int *dynamic_array_copy;

    printf("Enter array size: ");
    scanf("%d", &n);

    dynamic_array = (int*)malloc(n * sizeof(int));
    dynamic_array_copy = (int*)malloc(n * sizeof(int));

    if(dynamic_array == NULL){
        printf("Error");
        return 1;
    }

    printf("Array: [");
    for (int i = 0; i < n; i++)
    {
        dynamic_array[i] = (i+1) * 10;
        printf(" %d", dynamic_array[i]);
    }
    printf("]\n");

    copy_array(dynamic_array, dynamic_array_copy, n);

    free(dynamic_array);
    printf("Memory erased");
    dynamic_array = NULL;

    return 0;
}*/