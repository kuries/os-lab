#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define BUFFER_SIZE 5
// #define ITEMS 1

void *producer(void *args), *consumer(void *args);

sem_t full, empty;
pthread_mutex_t mutex;
int buffer[BUFFER_SIZE] = {1, 2, 3, 4, 5}, top=-1;

int main()
{
    pthread_t tid1, tid2;

    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid1, NULL, consumer, NULL);

    sem_destroy(&full);
    sem_destroy(&empty);

    pthread_exit(NULL);
    return 0;
}

void *producer(void *args)
{
    for(int i=0; i<9; i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        top++;
        printf("Producer: ");
        for(int i=0; i<=top; i++)
            printf("%d ", buffer[i]);
        printf("\n\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *args)
{
    for(int i=0; i<5; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        top--;
        printf("Consumer: ");
        for(int i=0; i<=top; i++)
            printf("%d ", buffer[i]);
        printf("\n\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}