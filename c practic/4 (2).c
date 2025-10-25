#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* foo(void* arg) {
    printf("Thread started\n");
    pthread_t currentThread = pthread_self();
    printf("ID inside thread: %lu\n", (unsigned long)currentThread);
    
    return NULL;
}

int main() {
    pthread_t thread1;

    pthread_create(&thread1, NULL, foo, NULL);
    printf("ID created thread: %lu\n", (unsigned long)thread1);
    pthread_join(thread1, NULL);
    printf("ID equal\n");

    return 0;
}