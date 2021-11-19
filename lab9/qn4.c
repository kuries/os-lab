#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

//Buffer has value 0 for being empty
int buffer = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void *prod_fn()
{
    int x;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    x = buffer;
    printf("Producer reads an empty buffer with value %d\n", x);
    x += 5;
    printf("Producer updated the local buffer with a value %d\n", x);
    buffer = x;
    printf("Producer has finished inserting %d in the shared buffer\n\n", buffer);
    sleep(1);

    pthread_mutex_unlock(&mutex); 
    sem_post(&full);
    return 0;
}

void *con_fn()
{
    int x;
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    x = buffer;
    printf("Consumer reads the buffer with value %d\n", x);
    x -= 5;
    printf("Consumer consumed the buffer value to %d\n", x);
    buffer = x;
    printf("Consumer has finished removing value in the shared buffer\n\n");

    pthread_mutex_unlock(&mutex); 
    sem_post(&empty);
    return 0;


}

int main()
{
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t prod, con;
    pthread_create(&prod, NULL, prod_fn, NULL);
    pthread_create(&con, NULL, con_fn, NULL);

    pthread_join(prod, NULL);
    pthread_join(con, NULL);

    printf("The final value of the consumed shared buffer: %d\n", buffer);
    return 0;
}