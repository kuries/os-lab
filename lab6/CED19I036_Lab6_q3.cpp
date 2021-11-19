#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

#include<iostream>

using namespace std;

int power(int x, unsigned int y)
{
    if (y == 0)
        return 1;
    if (y % 2 == 0)
        return power(x, y / 2) * power(x, y / 2);
    return x * power(x, y / 2) * power(x, y / 2);
}

int check_armstrong(int num)
{
    int num_of_digits = 0, temp = num, sum = 0;
    while (temp)
    {
        num_of_digits++;
        temp = temp / 10;
    }
    temp = num;
    while (temp)
    {
        int rem = temp%10;
        sum += power(rem, num_of_digits);
        temp = temp / 10;
    }
    if (sum == num)
        return 1;
    return 0;
}

int main()
{
	int fd1[2], fd2[2];
    //I/P and O/P messages for parent process
    int par_msg1[20], par_msg2[20];

    int child_msg1[20];

	if (pipe(fd1)==-1)
	{
		printf("Unable to create pipe 1\n");
		return 1;
	}
	if (pipe(fd2)==-1)
	{
		printf("Unable to create pipe 2\n");
		return 1;
	}

	pid_t pid = fork();

	if (pid < 0)
	{
		cout<<"Unable to create fork\n";
		return 1;
	}

	if (pid > 0)
	{
		close(fd1[1]);
        close(fd2[0]);

        printf("Enter numbers in the array (Parent process)\n");
        for (int i = 0; i < 5; i++)
        {
            scanf("%d", &par_msg1[i]);
        }

		//Write input array into pipe 2
		write(fd2[1], par_msg1, sizeof(par_msg1)+1);
        close(fd2[1]);

		// Wait for child to send a string
		wait(NULL);

		//Read boolean array from pipe 1
		read(fd1[0], par_msg2, sizeof(par_msg2)+1);
        for (int i = 0; i < 5; i++)
        {
            printf("%d: %d\n", par_msg1[i], par_msg2[i]);
        }
        
		close(fd1[0]);
	}
	else
	{
		close(fd1[0]);
        close(fd2[1]);

		read(fd2[0], child_msg1, sizeof(child_msg1)+1);
        close(fd2[0]);

        int check_arr[10];
        printf("Checking for Armstrong numbers (child process)\n");
        for (int i = 0; i < 5; i++)
            check_arr[i] = check_armstrong(child_msg1[i]);

		write(fd1[1], check_arr, sizeof(check_arr)+1);
		close(fd1[1]);
	}

    return 0;
}