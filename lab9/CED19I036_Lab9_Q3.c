#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

typedef struct sum_of_arr{
    int *arr;
    int len;
    int res;
} sum_of_arr;

void *thread_function(void *args);

int main()
{
    pthread_t tid1, tid2, tid3, tid4, tid5;
    int status;
    sum_of_arr ins;
    
    // int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n;
    printf("Enter the size: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the numbers: ");
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);

    ins.arr = arr;
    ins.len = sizeof(arr)/sizeof(arr[0]);

    pthread_create(&tid1, NULL, thread_function, (void *)&ins);
    pthread_join(tid1, NULL);

    printf("%d\n", ins.res);
    pthread_exit(NULL);
    return 0;
}

void *thread_function(void *args)
{
    sum_of_arr *ins = (sum_of_arr *)args;
    int sum=0;
    for(int i=0; i<ins->len; i++)
        sum += ins->arr[i];
    ins->res = sum;
}