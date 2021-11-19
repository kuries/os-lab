#include <iostream>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
using namespace std;

int main()
{
	int shmid = shmget((key_t)1823,1024,0666);
	char *str = (char*) shmat(shmid, NULL, 0);
    char text[100];

    int n=strlen(str);
    int limit=n/2, yes=1;

    for(int i=0; i<limit; i++)
    {
        if(str[i] != str[n-i-1])
        {
            yes=0;
            break;
        }
    }
    str[1] = yes+'0';
    str[0]='*';
	
	//detach from shared memory
	shmdt(str);
	
	return 0;
}
