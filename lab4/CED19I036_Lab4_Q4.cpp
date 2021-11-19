#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

using namespace std;

int main()
{
    int pid, n, i, sum=0;
    cout<<"Enter a number: ";
    cin>>n;
    pid = fork();

    if(pid < 0)
        perror("Fork failed\n");
    
    if(!pid)
        i=1;
    else
        i=0;
    
    for(; i<=n; i+=2)
        sum+=i;
    
    if(!pid)
        cout<<"Odd: "<<sum<<'\n';
    else
        cout<<"Even: "<<sum<<'\n';
    return 0;
}