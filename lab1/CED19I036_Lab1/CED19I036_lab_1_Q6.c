//M.Binesh
//CED19I036

#include<stdio.h>

int main()
{
    int integer=5;
    int arr[] = {0,1,2,3,4,5};
    int *ptr = arr;
    printf("Address of single integer: %p\n\n", &integer);
    for(int i=0; i<5; i++)
        printf("Address of %dth integer: %p\n", i, arr+i);
    return 0;
}