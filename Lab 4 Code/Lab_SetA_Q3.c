#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>  
 
#define CIPHER_KEY 7 

int main()
{

    char originalText[100] = "NYLHA MLLS SPRL PU ZLCLUAO OLHCLU";
    char decryptedText[100] = "";
    FILE *newFile;
    int length , i;
    char ch;

    newFile = fopen("Lab_SetA1_Q3.txt","w");

    length = strlen(originalText);
    for (i = 0; i < length; i++) { 
        ch = originalText[i];  
     
        //using shifting key cipher of 7
        // Perform Caesar Cipher substitution decryption 
        if (ch != ' ') 
        { 
            {
                ch -= 'A';
                ch -= CIPHER_KEY;
                ch += 26;
                ch = (ch%26);
                ch += 'A';
            }
        }
        strncat(decryptedText, &ch, 1);
        fputc(ch, newFile);  
    } 
    
    printf("\nDecrypted content: %s\n", decryptedText); 


    return 0;
}