//M.Binesh
//CED19I036

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main()
{
    FILE *fp1, *fp2;
    char ch;
    char vowels[10] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    fp1 = fopen("source.txt", "r");
    if (fp1 == NULL)
    {
        printf("File does not exist\n");
        return 0;
    }
    fp2 = fopen("target.txt", "w");
    if (fp2 == NULL)
    {
        printf("File does not exist\n");
        fclose(fp1);
        return 0;
    }
    while((ch=fgetc(fp1))!=EOF)
    {
        int flag = 0;
        for(int i=0; i<10; i++)
            if(ch == vowels[i])
            {
                flag = 1;
                break;
            }
        if(flag)
            continue;
        fputc(ch,fp2);
    }
    printf("File copied\n");
    fclose(fp1);
    fclose(fp2);
    return 0;
}