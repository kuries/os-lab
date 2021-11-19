#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

using namespace std;

int main()
{
    int pid, pid2, pid3;
    pid = fork();
    pid2 = fork();
    pid3 = fork();

    if(pid < 0 || pid2 < 0 || pid3 < 0)
        perror("Fork failed\n");

    if(pid == 0 || pid2 == 0 || pid3 == 0)
    {
        cout<<"Parent: "<<getppid()<<"\t";
        cout<<"Child: "<<getpid()<<"\n";
    }
    else
        cout<<"Origin: "<<getpid()<<"\n";
    wait(NULL);
    return 0;
}