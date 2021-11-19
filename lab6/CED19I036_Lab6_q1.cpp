#include <iostream>
#include<stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    int p1[2], p2[2];

    char p1wmsg[50], p2wmsg[50];
    char p1rmsg[50], p2rmsg[50];

    if(pipe(p1) == -1)
    {
        cout<<"Unable to create pipe 1\n";
        return 0;
    }

    if(pipe(p2) == -1)
    {
        cout<<"Unable to create pipe 2\n";
        return 0;
    }

    int pid = fork();
    if(pid<0)
    {
        cout<<"Unable to create fork\n";
        return 0;
    }

    if(pid > 0)
    {
        close(p1[0]);
        close(p2[1]);

        cout<<"Enter the input string: ";
        scanf("%[^\n]s", p1wmsg);

        write(p1[1], p1wmsg, sizeof(p1wmsg)+1);
        close(p1[1]);

        wait(NULL);

        read(p2[0], p2rmsg, sizeof(p2rmsg)+1);
        close(p2[0]);

        cout<<"Total sum of the ascii (in parent)\n";
        cout<<p2rmsg<<'\n';
    }
    else
    {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], p1rmsg, sizeof(p1rmsg)+1);
        close(p1[0]);

        int sum=0;
        cout<<"Received the string (in child)\n\n";
        for(int i=0; p1rmsg[i] != '\0'; i++)
            sum += (int)(p1rmsg[i]);
        
        sprintf(p2wmsg, "%d", sum);

        write(p2[1], p2wmsg, sizeof(p2wmsg)+1);
        close(p2[1]);
    }
    return 0;
}