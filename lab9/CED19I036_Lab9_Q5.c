#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

void *A(void *args), *B(void *args);

sem_t first, second;

int main()
{
    pthread_t tid1, tid2;

    sem_init(&first, 0, 0);
    sem_init(&second, 0, 0);

    pthread_create(&tid1, NULL, A, NULL);
    pthread_create(&tid1, NULL, B, NULL);

    sem_destroy(&first);
    sem_destroy(&second);
    
    pthread_exit(NULL);
    return 0;
}

void *A(void *args)
{
    printf("a1\n");
    sem_post(&second);

    sem_wait(&first);
    printf("a2\n");
}

void *B(void *args)
{
    printf("b1\n");
    sem_post(&first);
    
    sem_wait(&second);
    printf("b2\n");
}