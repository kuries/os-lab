#include <iostream>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
using namespace std;

int main()
{
	int shmid = shmget((key_t)1823, 1024, 0666|IPC_CREAT);
	char *str = (char*) shmat(shmid, NULL, 0);

    //first part
	cout<<"Write Data (now in p1): ";
	scanf("%[^\n]s", str);

    //second part
    while(str[0] != '*')
        sleep(1);
    
    if(str[1] == '1')
        cout<<"It is a pallindrome\n";
    else
        cout<<"It is not a pallindrome\n";

    //close the connection
	shmdt(str);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
