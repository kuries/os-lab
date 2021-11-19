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

    //first part
	printf("Data read from memory: %s\n",str);

    //second part
    cout<<"Enter a string: ";
    cin.getline(text, 100);

    int n=strlen(text);
    for(int i=0; i<n; i++)
        str[i+1] = text[i];
    str[n+1]='\0';
    str[0]='*';
	
	//detach from shared memory
	shmdt(str);
	
	return 0;
}
