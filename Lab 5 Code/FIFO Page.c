#include <stdio.h>

void main()
{

    int pageNumbers[25], frameContents[25];
    int i = 0, j = 0 , k = 0;
    int numPages = 0, numFrames = 0, totalPageFaults = 0;
    int frameNumber = 0;

    printf("\n Page Replacement Method: FIFO");
    printf("\n Enter the number of pages in the page sequence: ");
    // 20
    scanf("%d", &numPages);
    printf("\n Enter the page numbers in sequence as a string: ");
    // 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
    for (i = 0 ; i < numPages; i++)
        scanf("%d", &pageNumbers[i]);
    
    printf("\n Enter the number of frames: ");
    //3
    scanf("%d", &numFrames);
    for (i = 0 ; i < numFrames; i++)
        frameContents[i] = -1;

    printf("\n The Page Replacement Process is \n");
    printf("\t REF STRING");
    
    for (j = 0; j < numFrames; j++)
        printf("\tPAGE_FRAME_%d", j+1);

    printf("\tPAGE_FAULT_NUMBER\n");


    for(k = 0 ; k < numPages; k++)
    {
        int pageEntered = 0;

        //check for empty frame
        for (j = 0; j < numFrames; j++)
        {
            if (frameContents[j] == -1)
            {
                frameContents[j] = pageNumbers[k];
                totalPageFaults++;
                pageEntered = 1;
                printf("\t %d", pageNumbers[k]);
                for (j = 0; j < numFrames; j++)
                    printf("\t %d", frameContents[j]);
                printf("\t %d \n", totalPageFaults);
                break;
            }

            //if no empty frame, check if any of the frame matches the current frame
            if (frameContents[j] == pageNumbers[k])
            {
                pageEntered = 1;
                printf("\t %d", pageNumbers[k]);
                for (j = 0; j < numFrames; j++)
                    printf("\t %d", frameContents[j]);
                printf("\n ");
                break;
            }
        }

        if(pageEntered)
            continue;

        //if no empty frame and no matches, replace the first in frame

        frameContents[frameNumber] = pageNumbers[k];
        totalPageFaults++;
        printf("\t %d", pageNumbers[k]);
                for (j = 0; j < numFrames; j++)
                    printf("\t %d", frameContents[j]);
                printf("\t %d \n", totalPageFaults);

        if(frameNumber == numFrames - 1)
            frameNumber = 0;
        else
            frameNumber++;
        
    }

    /* Find the occurence of page faults and the total number of page faults */

    printf("\n\n Total number of page faults: %d \n", totalPageFaults);
}