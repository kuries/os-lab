#include <iostream>
#include<stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

int main()
{
    int p1[2], p2[2];

    char p1wmsg[50], p2wmsg[50];
    char p1rmsg[50], p2rmsg[50];

    cout<<"Enter string1: ";
    cin>>p1wmsg;

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
        cout<<"Unable to create pipe 2\n";
        return 0;
    }

    if(pid > 0)
    {
        close(p1[0]);
        close(p2[1]);

        write(p1[1], p1wmsg, sizeof(p1wmsg)+1);

        read(p2[0], p2rmsg, sizeof(p2rmsg)+1);
        cout<<"Printing the concatenated string: "<<p2rmsg<<'\n';
    }
    else
    {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], p1rmsg, sizeof(p1rmsg)+1);

        char input[50];
        cout<<"Enter string2: ";
        cin>>input;

        int n1 = strlen(p1rmsg), n2 = strlen(input);
        for(int i=0; i<n1; i++)
            p2wmsg[i] = p1rmsg[i];
        for(int i=0; i<n2; i++)
            p2wmsg[i+n1] = input[i];
        p2wmsg[n1+n2]='\0';

        write(p2[1], p2wmsg, sizeof(p2wmsg)+1);
    }
    return 0;
}






