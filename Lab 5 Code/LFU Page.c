#include <stdio.h>

void main()
{
    int numPages = 0, numFrames = 0, totalPageFaults = 0;
    int pageNumbers[25], frameContents[25];
    int i = 0, j = 0 , k = 0;
    int minArrivalIndex = 0, min_count = 0, next = 0;
    int framePageRepeatCount[25], arrivalIndex[25];
    int min_index = 0;
    int sameminflag = 1;

    printf("\n Page Replacement Method: Least Frequently Used (LFU) with FIFO");
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
    {
        frameContents[i] = -1;
        framePageRepeatCount[i] = -1;
        arrivalIndex[i] = -1;
    }

    printf("\n The Page Replacement Process is \n");
    printf("\t REF STRING");
    
    for (j = 0; j < numFrames; j++)
        printf("\tPAGE_FRAME_%d", j+1);

    printf("\tPAGE_FAULT_NUMBER\n");


    for(k = 0 ; k < numPages; k++)
    {
        int pageEntered = 0, counter = 0;
        min_count = 25;
        
        
            

        //check for empty frame
        for (j = 0; j < numFrames; j++)
        {
            //if frame is empty
            if (frameContents[j] == -1)
            {
                frameContents[j] = pageNumbers[k];
                arrivalIndex[j] = k;
                totalPageFaults++;
                pageEntered = 1;
                printf("\t %d", pageNumbers[k]);
                for (i = 0; i < numFrames; i++)
                    printf("\t %d", frameContents[i]);
                printf("\t %d \n", totalPageFaults);

                framePageRepeatCount[j] ++;

                break;
            }
            //if no empty frame, check if any of the frame matches the current frame
            if (frameContents[j] == pageNumbers[k])
            {
                pageEntered = 1;
                //arrivalIndex[j] = k;
                printf("\t %d", pageNumbers[k]);
                for (i = 0; i < numFrames; i++)
                    printf("\t %d", frameContents[i]);
                printf("\n ");

                framePageRepeatCount[j] ++;
                
                break;
            }
        }

        
        if(pageEntered)
        {
            continue;
        }
        //if no empty frame and no matches, apply LFU + FIFO here

        //smallest

        for(i = 0; i < numFrames; i++)
        {
            //sameminflag minindex
            if(framePageRepeatCount[i] < min_count)
            {
                sameminflag = 0;
                min_index = i;
                min_count = framePageRepeatCount[i];
            }

            if(framePageRepeatCount[i] == min_count)
            {
                sameminflag = 1;
            }
                
        }


        //FIFO
        //check arrivalindex 
        //if not -1, take over
        
        if(sameminflag)
        {
            int smallestk = 25;
            int smallestindex = -1;
            for(i = 0 ; i < numFrames ; i++)
            {
                if(arrivalIndex[i] < smallestk)
                {
                    //check if frame content's use count is equal to min_count
                        if(framePageRepeatCount[i] == min_count)
                        {
                            smallestk = arrivalIndex[i];
                            smallestindex  = i;
                        }   
                 
                }
                
                //0 is used because since 3 and 2 have same use count, it enters here
                //then 0 gets removed because it was the oldest despite having higher use count
            }

            framePageRepeatCount[smallestindex] = 0;
            frameContents[smallestindex] = pageNumbers[k];
            arrivalIndex[smallestindex] = k;
            totalPageFaults++;
            printf("\t %d", pageNumbers[k]);
                for (j = 0; j < numFrames; j++)
                    printf("\t %d", frameContents[j]);
                printf("\t %d \n", totalPageFaults);
        }

        //non FIFO
        else
        {
        
        framePageRepeatCount[min_index] = 0;
        frameContents[min_index] = pageNumbers[k];
        totalPageFaults++;
        arrivalIndex[min_index] = k;
        printf("\t %d", pageNumbers[k]);
                for (j = 0; j < numFrames; j++)
                    printf("\t %d", frameContents[j]);
                printf("\t %d \n", totalPageFaults);
        }
        
       
    }

    /* Find the occurence of page faults and the total number of page faults */

    printf("\n\n Total number of page faults: %d \n", totalPageFaults);
}