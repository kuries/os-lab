#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *thread_function(void *args);
int sum=0;

int main()
{
    pthread_t tid1, tid2, tid3, tid4, tid5;
    int a=1;
    pthread_create(&tid1, NULL, thread_function, (void *)&a);
    pthread_create(&tid2, NULL, thread_function, (void *)&a);
    pthread_create(&tid3, NULL, thread_function, (void *)&a);
    pthread_create(&tid4, NULL, thread_function, (void *)&a);
    pthread_create(&tid5, NULL, thread_function, (void *)&a);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);

    printf("%d\n", sum);
    pthread_exit(NULL);
    return 0;
}

void *thread_function(void *args)
{
    int *start = (int *)args;
    int end = *start+200;
    for(int i=*start; i<end; i++)
        sum += i;
    *start += 200;
}