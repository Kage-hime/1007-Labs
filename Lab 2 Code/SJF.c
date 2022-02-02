#include <stdio.h>

int main()
{

    int i = 0, j = 0, numProcesses = 0, timeSlice = 0, leastBurstTime = 0, temp = 0, position;
    int burstTime[10],backupBurstTime[10], queue[10], waitTime[10], turnAroundTime[10], responseTime[10];

    float avgWaitTime = 0.0, avgTurnAroundTime = 0.0, avgResponseTime = 0.0;

    printf("\t CPU Scheduling Method: Shortest Job First \n");

    printf("\n\t Enter the no of processes: ");
    scanf("%d", &numProcesses);

    for( i = 0; i < numProcesses; i++)
    {
        printf("\n\t Enter Burst Time for process %d: ", i+1);
        scanf("%d", &burstTime[i]);
        backupBurstTime[i] = burstTime[i];
        queue[i] = i + 1;
    }


    for(i = 0 ; i < numProcesses; i++)
    {
        position = i;
        for ( j = i + 1; j < numProcesses; j++)
        {
            if(burstTime[j] < burstTime[position])
            {
                position = j;
            }
        }

        temp = burstTime[i];
        burstTime[i] = burstTime[position];
        burstTime[position] = temp;

        temp = queue[i];
        queue[i] = queue[position];
        queue[position] = temp;

       
        
    }

    waitTime[0] = 0;
    turnAroundTime[0] = burstTime[0];
    responseTime[0] = 0;

    for(i = 1 ; i < numProcesses; i++)
    {
        waitTime[i]=0;
        for(j=0;j<i;j++)
            waitTime[i] += burstTime[j];
        
        turnAroundTime[i] = burstTime[i] + waitTime[i];
        responseTime[i] = waitTime[i];
    }
 



    printf("\n\t PROCESS\t BURST TIME\t WAITING TIME\t TURNAROUND TIME\t RESPONSE TIME\n");
    for (i = 0 ; i < numProcesses; i++)
    {
           printf("\t P%d \t\t %d \t\t %d \t\t %d \t\t\t %d \n", queue[i], burstTime[i], waitTime[i],turnAroundTime[i],responseTime[i]);
           avgWaitTime += waitTime[i];
           avgTurnAroundTime += turnAroundTime[i];
           avgResponseTime += responseTime[i];
    }

     



    /* Calc and print avg wait, turnaround and response time*/
    printf("\n\t The Average Waiting time: %.2f\n", avgWaitTime / numProcesses);
    printf("\n\t The Average Turnaround time: %.2f\n", avgTurnAroundTime / numProcesses);
    printf("\n\t The Average Response time: %.2f\n", avgResponseTime / numProcesses);


    return 0;
}

