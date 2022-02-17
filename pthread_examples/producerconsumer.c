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
pthread_mutex_t test_mutex;
//1 indicates full, 0 indicates not full
int full = 0;
//1 indicates empty, 0 indicates not empty
int empty = 1;
time_t msec ;
int lock = 0;



void *producer(int number)
{
    printf("Producer%d thread created successfully\n", number);

    do
    {
        sleep((rand()%2) + 1);
        
        //insert mutex check here
        //if(sem_getvalue(semaphorePointer, &value) != 0  )
        //if(lock == 0  )
        pthread_mutex_lock(&test_mutex);
        {
            //sem_wait(semaphorePointer);
            lock = 1;
            for(int i = 0 ; i < 5 ; i++)
            {
                if(bufferList[i] == 0)
                {
                    
                    srand(time(0));
                    produced = (rand() ) % 999 ;
                    bufferList[i] = produced;
                    printf("Producer%d made %d\n", number, bufferList[i]);

                 
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
                //printf("LOL FULL\n");         
            }

            //sem_post(semaphorePointer);  
            //lock = 0;    
            pthread_mutex_unlock(&test_mutex);          
        }
       
       
        

    } while (1);
    
   
    

}


void *consumer(int number)
{
    printf("Consumer%d thread created successfully\n", number);
    
    do
    {
         sleep((rand()%2) + 1);

        //insert mutex check here
        //if(sem_getvalue(semaphorePointer, &value) != 0  )
        //if(lock == 0  )
        pthread_mutex_lock(&test_mutex);
        {
            //sem_wait(semaphorePointer);
            lock = 1;
            if(empty != 1)
            {
                printf("Consumer%d took %d\n", number, bufferList[0]);

                
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
 
            //sem_post(semaphorePointer);
            //lock = 0;
            pthread_mutex_unlock(&test_mutex);
                
        }
        
        
        
       
        

    } while (1);
    

}


int main(int argc, char *argv[])
{   
    //unnamed semaphore creation
    //pointer, accesstype, default value
    //sem_init(semaphorePointer, 1, 10); 

    pthread_mutex_init(&test_mutex, NULL);

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
       
        threadID = pthread_create(&threads[i],NULL,producer,(int) i+1);
        
        //pthread_join(threads[i],NULL);
        

    }

    //loop for creating consumer threads
    for(int i = 0 ; i < consumerCount; i ++)
    {
        
        threadID = pthread_create(&threads[i+producerCount],NULL,consumer,(int) i+1);
        
        //pthread_join(threads[i+producerCount],NULL);
    }


   
    sleep(waitTime);

    for(int i = 0 ; i < producerCount + consumerCount; i ++)
    {
        
        pthread_cancel(threads[i]);
        
        //pthread_join(threads[i+producerCount],NULL);
    }

    printf("Sleep time elapsed. Producers and Consumers terminated\n");

    int itemCount = 0 ;
    for(int i = 0 ; i < 5 ; i++)
    {
        if(bufferList[i] != 0)
            itemCount +=1;
    }

    printf("Number of remaining items on buffer = %d\n" , itemCount);

    for(int i = 0 ; i < 5 ; i++)
    {
       printf("%d\n" , bufferList[i]);
    }

    pthread_mutex_destroy(&test_mutex);
    
    return 0;
}

