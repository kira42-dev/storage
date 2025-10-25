#include <pthread.h>
#include <stdio.h>

void* foo(void* arg) {
    printf("%s\n", (char*)arg);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, foo, (void*)"Thread 1 working");
    pthread_create(&thread2, NULL, foo, (void*)"Thread 2 working");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads ended");
    return 0;
}