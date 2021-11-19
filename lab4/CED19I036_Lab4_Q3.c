#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
 
int main() {
    pid_t pid;
    int res;

    pid = fork();

    if (pid == 0) 
	{
        printf("child\n");
        exit(3);
    }

    pid = wait(&res);
    printf("raw res=%d\n", res);

    if (WIFEXITED(res))
        printf("exit status = %d\n", WEXITSTATUS(res));
    return 0;
}