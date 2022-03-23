#include <stdio.h>

void main()
{
    int numPages = 0, numFrames = 0, totalPageFaults = 0;
    int pageNumbers[25], frameContents[25];
    int i = 0, j = 0 , k = 0;
    int minArrivalIndex = 0, min_count = 0, next = 0;
    int framePageRepeatCount[25], arrivalIndex[25];

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
        
        for(i = 0 ; i < k+1 ; i++)
                if(pageNumbers[i] == pageNumbers[k])  
                    counter++;
            for(i = 0 ; i < k+1 ; i++)
                if(pageNumbers[i] == pageNumbers[k])
                    framePageRepeatCount[i] = counter;

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

                break;
            }
            //if no empty frame, check if any of the frame matches the current frame
            if (frameContents[j] == pageNumbers[k])
            {
                pageEntered = 1;
                arrivalIndex[j] = k;
                printf("\t %d", pageNumbers[k]);
                for (i = 0; i < numFrames; i++)
                    printf("\t %d", frameContents[i]);
                printf("\n ");
                break;
            }
        }

        
        if(pageEntered)
        {
            // for(i = 0 ; i < k+1 ; i++)
            //     if(pageNumbers[i] == pageNumbers[k])  
            //         counter++;
            // for(i = 0 ; i < k+1 ; i++)
            //     if(pageNumbers[i] == pageNumbers[k])
            //         framePageRepeatCount[i] = counter;
            continue;
        }
        //if no empty frame and no matches, apply LFU + FIFO here

        int min_index = 0;
        int sameminflag = 1;

        for(i = 0; i < numFrames; i++)
        {
            for(j = 0; j < numPages; j++)
                {
                    if(frameContents[i] == pageNumbers[j])
                    {
                        if(framePageRepeatCount[j] == min_count)
                        {
                            sameminflag = 1;
                            break;
                        }

                        if(framePageRepeatCount[j] < min_count)
                        {   
                            min_index = i;
                            sameminflag = 0;
                            min_count = framePageRepeatCount[j];
                            break;
                        }

                    }
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
                    smallestk = arrivalIndex[i];
                    smallestindex  = i;
                }
                           
            }

            frameContents[smallestindex] = pageNumbers[k];
            arrivalIndex[smallestindex] = k;
            totalPageFaults++;

            // for(i = 0 ; i < k+1 ; i++)
            //     if(pageNumbers[i] == pageNumbers[k])  
            //         counter++;
            // for(i = 0 ; i < k+1 ; i++)
            //     if(pageNumbers[i] == pageNumbers[k])
            //         framePageRepeatCount[i] = counter;
            printf("\t %d", pageNumbers[k]);
                for (j = 0; j < numFrames; j++)
                    printf("\t %d", frameContents[j]);
                printf("\t %d \n", totalPageFaults);
        }

        //non FIFO
        else
        {
        frameContents[min_index] = pageNumbers[k];
        totalPageFaults++;
        // for(i = 0 ; i < k+1; i++)
        //     if(pageNumbers[i] == pageNumbers[k])  
        //         counter++;
        // for(i = 0 ; i < k+1; i++)
        //     if(pageNumbers[i] == pageNumbers[k])
        //         framePageRepeatCount[i] = counter;
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