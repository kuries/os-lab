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

vector<int> str_to_arr(char s[])
{
    vector<int> vec;
    int temp=0;
    for(int i=0; s[i] != '\0'; i++)
    {
        if(s[i] != ' ')
            vec.push_back(s[i]-'0');
    }
    return vec;
}

void arr_to_str(char nums[], const vector<int> &vec)
{
    int i=0;
    for(i=0; i<vec.size(); i++)
    {
        nums[2*i] = (char)(vec[i]+'0');
        nums[2*i+1] = ' ';
    }
    nums[2*i] = '\0';
}


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

        vector<int> asc = str_to_arr(p1wmsg);
        sort(asc.begin(), asc.end());

        arr_to_str(p1wmsg, asc);
        write(p1[1], p1wmsg, sizeof(p1wmsg)+1);
        close(p1[1]);

        read(p2[0], p2rmsg, sizeof(p2rmsg)+1);
        close(p2[0]);

        asc = str_to_arr(p2rmsg);

        cout<<"Printing from parent in descending order\n";
        for(auto it: asc)
            cout<<it<<" ";
        cout<<'\n';

        wait(NULL);
    }
    else
    {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], p1rmsg, sizeof(p1rmsg)+1);
        close(p1[0]);

        cout<<"Printing from child in ascending order\n";
        for(int i=0; p1rmsg[i] != '\0'; i++)
            cout<<p1rmsg[i];
        cout<<'\n';

        vector<int> dsc = str_to_arr(p1rmsg);
        sort(dsc.begin(), dsc.end(), greater<int>{});

        arr_to_str(p2wmsg, dsc);
        write(p2[1], p2wmsg, sizeof(p2wmsg)+1);
        close(p2[1]);
    }
    return 0;
}