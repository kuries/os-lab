//M.Binesh
//CED19I036

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main()
{
    FILE *fp1, *fp2;
    char ch;
    fp1 = fopen("source.txt", "r");
    if (fp1 == NULL)
    {
        puts("File does not exist\n");
        return 0;
    }
    fp2 = fopen("target.txt", "w");
    if (fp2 == NULL)
    {
        puts("File does not exist\n");
        fclose(fp1);
        return 0;
    }

    //loop until you reach the end of the file
    while((ch=fgetc(fp1))!=EOF)
    {
        if(isupper(ch))
            ch = tolower(ch);
        else if(islower(ch))
            ch = toupper(ch);
        fputc(ch,fp2);
    }
    printf("File copied\n");
    fclose(fp1);
    fclose(fp2);
    return 0;
}