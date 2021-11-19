#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *thread_function(void *args);

int main()
{
    pthread_t tid1, tid2, tid3, tid4, tid5;
    int n;
    printf("Enter the value n: ");
    scanf("%d", &n);
    pthread_create(&tid1, NULL, thread_function, (void *)&n);

    pthread_join(tid1, NULL);
    pthread_exit(NULL);
    return 0;
}

void *thread_function(void *args)
{
    int *n = (int *)args;
    for(int i=0; i<=*n; i++)
        printf("%d\n", i);
}