#include<iostream>
#include<algorithm>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

using namespace std;

int main()
{
    int pid, sum=0;
    int arr[10];

    cout<<"Enter Numbers:";
    for(int i=0; i<10; i++)
        cin>>arr[i];
    
    pid = fork();

    if(pid < 0)
        perror("Fork failed\n");

    //child
    if(!pid)
    {
        printf("Descending: ");
        sort(arr, arr+10, greater<int>{});
    }
    //parent
    else
    {
        printf("Ascending: ");
        sort(arr, arr+10);
    }
    
    wait(NULL);

    for(int i=0; i<10; i++)
        cout<<arr[i]<<' ';

    cout<<'\n';
    
    return 0;
}