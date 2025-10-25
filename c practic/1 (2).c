#include <pthread.h>
#include <stdio.h>

void* foo(void* arg) {
    printf("Im working in thread");
    return NULL;
}

int main() {
    pthread_t thread1;

    pthread_create(&thread1, NULL, foo, NULL);
    pthread_join(thread1, NULL);
    printf("\nThread ended");
    return 0;
}