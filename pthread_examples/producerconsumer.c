#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


int waitTime, producerCount, consumerCount, threadID;
int bufferList[5];
int produced;
//0 means not in use, 1 means critical process inside
int value;
sem_t* semaphorePointer;
//1 indicates full, 0 indicates not full
int full = 0;
//1 indicates empty, 0 indicates not empty
int empty = 1;



void *producer(int number)
{
    printf("Producer%d thread created successfully\n", number);

    do
    {
        sleep(rand()%3);
        produced = (rand() % 999);
        //insert mutex check here
        if(sem_getvalue(semaphorePointer, &value) != 0  )
        {
            sem_wait(semaphorePointer);
            for(int i = 0 ; i < 5 ; i++)
            {
                if(bufferList[i] == 0)
                {
                    bufferList[i] = produced;
                    printf("Producer made %d\n", bufferList[i]);
                    full = 0;
                    empty = 0;
                    break;
                }
                
            }

            if(bufferList[0] != 0 && bufferList[4] != 0)
            {
                full = 1;
            }

            if(full)
            {
                printf("LOL FULL\n");         
            }

            sem_post(semaphorePointer);                
        }
       
       
        

    } while (1);
    
   
    

}


void *consumer(int number)
{
    printf("Consumer%d thread created successfully\n", number);

    do
    {
        sleep(rand()%3);

        //insert mutex check here
        if(sem_getvalue(semaphorePointer, &value) != 0  )
        {
            sem_wait(semaphorePointer);
    
            if(empty != 1)
            {
                printf("Consumer took %d\n", bufferList[0]);
                
                for(int i = 1 ; i < 5 ; i++)
                {
                    bufferList[i-1] = bufferList[i];
                }

                bufferList[4] = 0;

                if(bufferList[0] == 0)
                {
                    empty = 1;
                }

            }
 
            sem_post(semaphorePointer);
                
        }

        
        
        
        

    } while (1);
    

}


int main(int argc, char *argv[])
{   
    //unnamed semaphore creation
    
    //pointer, accesstype, default value
    sem_init(semaphorePointer, 1, 10); 

    //get parameters from user
    waitTime = atoi(argv[1]);
    producerCount = atoi(argv[2]);
    consumerCount = atoi(argv[3]);

    printf("Number of arguments = %d\n" , argc);
    printf("Main Process sleep time = %d\n",waitTime);
    printf("Number of producer(s) = %d\n",producerCount);
    printf("Number of consumer(s) = %d\n",consumerCount);
    

    pthread_t threads[producerCount + consumerCount];

    //loop for creating producer threads
    for(int i = 0 ; i < producerCount; i ++)
    {
       
        threadID = pthread_create(&threads[i],NULL,producer,i+1);
        //pthread_join(threads[i],NULL);
        

    }

    //loop for creating consumer threads
    for(int i = 0 ; i < consumerCount; i ++)
    {
        
        threadID = pthread_create(&threads[i+producerCount],NULL,consumer,i+producerCount);
        //pthread_join(threads[i+producerCount],NULL);
    }


   
    getch();
    
    return 0;
}

