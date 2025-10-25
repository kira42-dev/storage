#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* foo(void* arg) {
    printf("Thread created");
    int number = *(int*)arg;
    printf("\nHanded in thread: %d\n", number);

    int* result = malloc(sizeof(int));
    *result = number * 2;

    pthread_exit(result);
}

int main() {
    pthread_t thread1;
    int number = 5;
    int* result;

    pthread_create(&thread1, NULL, foo, &number);
    pthread_join(thread1, (void**)&result);

    printf("\nGet from thread: %d\n", *result);
    free(result);

    return 0;
}