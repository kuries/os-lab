#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
int main()
{   
    struct dirent *myfile;
    DIR *mydirectory;
    printf("Current Directory opened");
    //pointer to point at directory
    mydirectory = opendir("./");
    if(mydirectory)
    {
        //read all files in current directory
        while((myfile = readdir(mydirectory)))
        {
            printf("%s\n", myfile->d_name);
        }
    }
    closedir(mydirectory);
    printf("Current Directory Closed\n");
    return 0;
}