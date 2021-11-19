#include<iostream>
#include<algorithm>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

using namespace std;

int main()
{
    char directory[] = "/home/kuries/Desktop/sem/osp";
    int pid = fork();
    
    if(pid == 0)
        execl("/bin/ls", "ls", "-la", directory, NULL);
    else    
        execl("/bin/pstree", "pstree", NULL);
    
    return 0;
}