#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define METHOD "SEQUENTIAL"
#define TOTAL_DISK_BLOCKS 32
#define TOTAL_DISK_INODES 8
#define BLOCK_SIZE 1

int blockStatus[TOTAL_DISK_BLOCKS]; //free = 0
int blockStart;

struct file_table 
{
    char fileName[20];
    int startBlock;
    int fileSize;
    int allotStatus;
};

struct file_table fileTable[TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES];

int AllocateBlocks(int size)
{
    int i = 0, count = 0, inList = 0, nextBlock = 0;
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

    while (count < size)
    {
        nextBlock = (rand()% (allocEndBlock - allocStartBlock + 1)) + allocStartBlock;
        for (i = nextBlock; i < (nextBlock + size); i++)
            {
                if(blockStatus[i] == 0)
                    count = count + 1;
                else
                {
                    count = 0;
                    break;
                }
            }
    }

    blockStart = nextBlock;

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
            fileTable[i].startBlock = blockStart;
            fileTable[i].allotStatus = 1;
            for(j = blockStart ; j < blockStart + newFile.fileSize; j++)
            {
                blockStatus[j] = 1;
            }

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

        for(j = 0; j < fileTable[i].fileSize; ++j)
        {
            if(j < fileTable[i].fileSize -1)
            {
                printf("%d-", fileTable[i].startBlock + j);
            }
            else{
                printf("%d\n", fileTable[i].startBlock + j);
            }
        }
    }

    //pseudorandom seed
    srand(1234);


}