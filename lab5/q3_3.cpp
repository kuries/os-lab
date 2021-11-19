#include<stdio.h>
#include<malloc.h>
#include <unistd.h>
#include<sys/wait.h>
#include<string.h>
#include <fcntl.h>
int main()
{
    int fd, sz;
    char *c = (char *) calloc(100, sizeof(char));
    //open hello file in read-write and append mode
    fd = open("test.txt", O_APPEND | O_RDWR);

    //error opening file
    if (fd < 0) 
    {
        printf("Error\n");
        return 0;
    }
    printf("File opened\n");

    //read 16 bytes of data from hello.txt and store it in variable c
    sz = read(fd, c, 16);
    printf("16 bytes are as follows: %s\n", c);
    //write message to file hello.txt
    sz = write(fd, "\nYou Are Correct", strlen("\nYou Are Correct"));
    //close file hello.txt
    close(fd);
    printf("File closed\n");
    return 0;
}