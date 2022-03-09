#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define METHOD "LINKED LIST"
#define TOTAL_DISK_BLOCKS 32
#define TOTAL_DISK_INODES 8
#define BLOCK_SIZE 1

int blockStatus[TOTAL_DISK_BLOCKS]; //free = 0
struct block *blockList[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES];

struct file_table 
{
    char fileName[20];
    int fileSize;
    struct block *sb;
};

struct block
{
    int blockNumber;
    struct block *next;
};

struct file_table fileTable[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES];
struct block *startPointer;

int AllocateBlocks(int size)
{
    //startPointer = malloc(sizeof(*startPointer));
    int i = 0, count = 0, nextBlock = 0;
    struct block *linktracker;
    linktracker = malloc(sizeof(*linktracker));
    linktracker->blockNumber = -1;
    linktracker->next = NULL;
    //start index of disk list that can be allocated after reserved space
    int allocStartBlock = TOTAL_DISK_INODES;
    //end index of disk list
    int allocEndBlock = TOTAL_DISK_BLOCKS - 1;

    //check whether sufficient free blocks are available
    for(i = 0; i < (TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES); i++)
        if(blockStatus[i] == 0)
            count ++;
    if (count < size)
        return 1; //not enough free blocks
    count = 0;

    struct block *temp, *new;
    while (count < size)
    {   
        nextBlock = (rand()% (allocEndBlock - allocStartBlock + 1)) + allocStartBlock;

        if(blockStatus[nextBlock] == 0)
        {
            if(linktracker->blockNumber == -1)
            {
                linktracker->blockNumber = nextBlock;
                blockList[nextBlock - 8] = linktracker; 
                blockStatus[nextBlock] = 1;
                count++;
            }
               
            else
            {
                temp = malloc(sizeof(*temp));
                new = malloc(sizeof(*new));
                new->blockNumber = nextBlock;
                new->next = NULL;
                blockList[nextBlock - 8] = new; 
                blockStatus[nextBlock] = 1;

                //set pointer chain
                temp = linktracker;
                while(temp->next != NULL)
                    temp = temp->next;
                temp->next = new;
                count++;

                
            }
            
        }
    }

    startPointer = linktracker;

    if (count == size)
        return 0; //success
    else
        return 1; //fail
    

}


void main()
{
    printf("File allocation method: %s\n", METHOD);
    printf("Total blocks: %d\n", TOTAL_DISK_BLOCKS);
    printf("File allocation starts at block: %d\n", TOTAL_DISK_INODES);
    printf("File allocation ends at block: %d\n", TOTAL_DISK_BLOCKS - 1);
    printf("Size (kB) of each block: %d\n", BLOCK_SIZE);

    int i = 0 , j = 0, numFiles = 0, nextBlock = 0, ret = 1;
    char s[20];
    struct block *temp;


    printf("Enter no of files: ");
    scanf("%d",&numFiles);

    for(i = 0; i < numFiles; i++)
    {
        struct file_table newFile;

        printf("Enter the name of file #%d: ", i+1);
        scanf("%s", &newFile.fileName);
        printf("Enter the size (kB) of file #%d: ", i+1);
        scanf("%d", &newFile.fileSize);
        fileTable[i] = newFile;
        ret = AllocateBlocks(fileTable[i].fileSize);
        //for successful finding of continuous
        if(ret == 0)
        {  
            fileTable[i].sb = malloc(sizeof(*startPointer));
            fileTable[i].sb->blockNumber = startPointer->blockNumber;
            fileTable[i].sb->next = startPointer->next;
           
        }

        else
        {
            printf("Not enough space for file");
        }
        
        
        
    }

    

    printf("FILE_fileName\tFILE_SIZE\tBLOCKS_OCCUPIED\n");
    for(i = 0; i < numFiles; i++)
    {
        printf("%s\t%d\t\t", fileTable[i].fileName, fileTable[i].fileSize);
        temp = malloc(sizeof(*fileTable[i].sb));
        temp->blockNumber = fileTable[i].sb->blockNumber;
        temp->next= fileTable[i].sb->next;
        for (j = 0; j < fileTable[i].fileSize; j++)
        {
            if(j != fileTable[i].fileSize - 1)
                printf("%d-", temp->blockNumber);
            else
                printf("%d\n", temp->blockNumber);
            temp = temp->next;
        }
        
    }

    //pseudorandom seed
    srand(1234);


}