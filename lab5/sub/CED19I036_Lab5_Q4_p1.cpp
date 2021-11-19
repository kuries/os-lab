#include <iostream>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
using namespace std;

int main()
{
	int shmid = shmget((key_t)1823,1024,0666|IPC_CREAT);
	char *str = (char*) shmat(shmid, NULL, 0);

    //first part
	cout<<"Write Data (now in p1): ";
	cin.getline(str, 100);

    //second part
    while(str[0] != '*')
        sleep(1);
    
    cout<<"Data read from memory: ";
    for(int i=1; str[i] != '\0'; i++)
        cout<<str[i];
	cout<<'\n';

    //close the connection
	shmdt(str);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
