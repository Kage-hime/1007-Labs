#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>  
 
#define CIPHER_KEY 3 

int main()
{
    char test = 'a';
    test +=4;
    printf("%d", test);
    printf("%d", 123142);
    FILE *newfile;
    newfile = fopen("D:\\SIT School Files\\1007\\Labs\\1007-Labs\\Lab 4 Code\\Lab_Quick.txt", "r");
    char ch = fgetc(newfile);
    printf("%c",ch);
    return 0 ;
}