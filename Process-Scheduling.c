#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
#define workload_size 2

void FCFS(int workload_id, int size, int burstTime[], int arrivalTime[], int process[], int algoNum, float *avgWaitingTime, float *avgTurnAroundTime, float *cpuUsage);
void SJF(int workload_id, int size, int burstTime[], int arrivalTime[], int process[], int algoNum, float *avgWaitingTime, float *avgTurnAroundTime, float *cpuUsage);
void RR(int workload_id, int size, int burstTime[], int arrivalTime[], int process[], int overhead, int quantum, int algoNum, float *avgWaitingTime, float *avgTurnAroundTime, float *cpuUsage);
int askBurstTime(int i);
int askArrivalTime(int i);
int askOverheadTime(void);
int askCheckNoOverhead(int overhead);
int askQuantumTime(void);
float cpuUtilization(int size, int burstTime[], int completionTime[]);
void printDetails(int workload_i, int size, int burstTime[], int arrivalTime[], int process[], int waitingTime[], int serviceTime[], int turnAroundTime[], int completionTime[]);
void printComparison(int numOfAlgo, int whichAlgo, float *avgWaitingTime, float *avgTurnAroundTime, float *cpuUsage);


int main(void)
{
	int choice1, choice2, i, j;
	int maxsize, size[2], *burstTime, *arrivalTime, *process, overhead[2], quantum[2];
  int checkNoOverhead[workload_size];
	int *w1burstTime, *w1arrivalTime, *w1process;
	int *w2burstTime, *w2arrivalTime, *w2process;
  float *w1AvgWaitingTime, *w1AverageTurnAroundTime, *w1CpuUsage;
  float *w2AvgWaitingTime, *w2AverageTurnAroundTime, *w2CpuUsage;
	
	// Ask user to run all algorithms or 1 specific algorithm
	printf("Would you like to run comparison for all scheduling algorithm or on just one specific scheduling algorithm?\n");
	printf("1 - All scheduling algorithm\n");
	printf("2 - Only one scheduling algorithm\n");
	scanf("%d", &choice1);
	while(choice1 != 1 && choice1 != 2)
	{
		printf("Your input can either be 1 or 2\n");
		printf("Please select again which mode you would like to run?\n");
		scanf("%d",&choice1);
	}
	if(choice1 == 1)
	{
		for(i = 0; i < workload_size ;i++)
		{
			printf("How many processes would you like to have (min 7, max 10) for workload %d?\n",i+1);
			scanf("%d",&size[i]);
			
			while(size[i] < 7 || size[i] > 10)
			{
				printf("Process number cannot be less than 7 or more than 10!\n");
				printf("How many processes would you like to have (min 7, max 10)?\n");
				scanf("%d", &size[i]);
			}
		}
	}
	else
	{
		// Ask for which scheduling algorithm to run
		printf("Please select which process scheduling algorithm you want to run?\n");
		printf("1 - First Come First Serve\n");
		printf("2 - Shortest Job First Non-Preemptive Version\n");
		printf("3 - Round Robin (With and Without an Overheads)\n");
		scanf("%d",&choice2);
		while(choice2 != 1 && choice2 != 2 && choice2 != 3)
		{
			printf("Your input can either be 1 or 2 or 3\n");
			printf("Please select again which process scheduling algorithm you want to run?\n");
			scanf("%d",&choice2);
		}
		for(i = 0; i < workload_size ;i++)
		{
			printf("How many processes would you like to have (min 7, max 10) for workload %d?\n",i+1);
			scanf("%d",&size[i]);
			
			while(size[i] < 7 || size[i] > 10)
			{
				printf("Process number cannot be less than 7 or more than 10!\n");
				printf("How many processes would you like to have (min 7, max 10)?\n");
				scanf("%d",&size[i]);
			}
			
		}
	}
	
	//
	//Manipulate the input data
	//
	
	if(size[0] > size[1])
		maxsize = size[0];
	else
		maxsize = size[1];
	
	burstTime = (int *)malloc(2 * maxsize * sizeof(int));
	arrivalTime = (int *)malloc(2 * maxsize * sizeof(int));
	process = (int *)malloc(2 * maxsize * sizeof(int));
	
	for(i = 0; i < 2; i++)
	{
    printf("\n\n=================\n");
		printf("W O R K L O A D %d\n", i + 1);
    printf("=================\n\n");
		for(j = 0; j < size[i]; j++)
		{
			*(burstTime + i*maxsize + j) = askBurstTime(j);
			*(arrivalTime + i*maxsize + j) = askArrivalTime(j);
			*(process + i*maxsize + j) = j+1;
		}
		
		if((choice1 == 1) || (choice1 == 2 && choice2 == 3))
		{
			overhead[i] = askOverheadTime();
      checkNoOverhead[i] = askCheckNoOverhead(overhead[i]);
			quantum[i] = askQuantumTime();
		}
	}

  //Prepare arrays for individual workloads
  if(choice1 == 1)
  {
    if(checkNoOverhead[0] != 1)
    {
      w1AvgWaitingTime = (float *)malloc(3 * sizeof(float));
      w1AverageTurnAroundTime = (float *)malloc(3 * sizeof(float));
      w1CpuUsage = (float *)malloc(3 * sizeof(float));
    }
    else
    {
      w1AvgWaitingTime = (float *)malloc(4 * sizeof(float));
      w1AverageTurnAroundTime = (float *)malloc(4 * sizeof(float));
      w1CpuUsage = (float *)malloc(4 * sizeof(float));
    }

    if(checkNoOverhead[1] != 1)
    {
      w2AvgWaitingTime = (float *)malloc(3 * sizeof(float));
      w2AverageTurnAroundTime = (float *)malloc(3 * sizeof(float));
      w2CpuUsage = (float *)malloc(3 * sizeof(float));
    }
    else
    {
      w2AvgWaitingTime = (float *)malloc(4 * sizeof(float));
      w2AverageTurnAroundTime = (float *)malloc(4 * sizeof(float));
      w2CpuUsage = (float *)malloc(4 * sizeof(float));
    }
  }
  else
  {
    if(choice2 == 3)
    {
      if(checkNoOverhead[0] != 1)
      {
        w1AvgWaitingTime = (float *)malloc(1 * sizeof(float));
        w1AverageTurnAroundTime = (float *)malloc(1 * sizeof(float));
        w1CpuUsage = (float *)malloc(1 * sizeof(float));
      }
      else
      {
        w1AvgWaitingTime = (float *)malloc(2 * sizeof(float));
        w1AverageTurnAroundTime = (float *)malloc(2 * sizeof(float));
        w1CpuUsage = (float *)malloc(2 * sizeof(float));
      }

      if(checkNoOverhead[1] != 1)
      {
        w2AvgWaitingTime = (float *)malloc(1 * sizeof(float));
        w2AverageTurnAroundTime = (float *)malloc(1 * sizeof(float));
        w2CpuUsage = (float *)malloc(1 * sizeof(float));
      }
      else
      {
        w2AvgWaitingTime = (float *)malloc(2 * sizeof(float));
        w2AverageTurnAroundTime = (float *)malloc(2 * sizeof(float));
        w2CpuUsage = (float *)malloc(2 * sizeof(float));
      }
    }
    else
    {
      w1AvgWaitingTime = (float *)malloc(1 * sizeof(float));
      w1AverageTurnAroundTime = (float *)malloc(1 * sizeof(float));
      w1CpuUsage = (float *)malloc(1 * sizeof(float));

      w2AvgWaitingTime = (float *)malloc(1 * sizeof(float));
      w2AverageTurnAroundTime = (float *)malloc(1 * sizeof(float));
      w2CpuUsage = (float *)malloc(1 * sizeof(float));
    }
  }
	
	w1burstTime = (int *)malloc(size[0] * sizeof(int));
	w1arrivalTime = (int *)malloc(size[0] * sizeof(int));
	w1process = (int *)malloc(size[0] * sizeof(int));
	
	w2burstTime = (int *)malloc(size[1] * sizeof(int));
	w2arrivalTime = (int *)malloc(size[1] * sizeof(int));
	w2process = (int *)malloc(size[1] * sizeof(int));
	
	for(i = 0; i < size[0]; i++)
	{
		w1burstTime[i] = *(burstTime + 0*maxsize + i);
		w1arrivalTime[i] = *(arrivalTime + 0*maxsize + i);
		w1process[i] = *(process + 0*maxsize + i);
	}
	
	for(i = 0; i < size[1]; i++)
	{
		w2burstTime[i] = *(burstTime + 1*maxsize + i);
		w2arrivalTime[i] = *(arrivalTime + 1*maxsize + i);
		w2process[i] = *(process + 1*maxsize + i);
	}
	
  system("@cls||clear");
  
	// Run all algorithms
	if(choice1 == 1)
	{
    printf("\n\n=================\n");
    printf("W O R K L O A D 1\n");
    printf("=================\n\n");
		printf("\nFIRST COME FIRST SERVE\n");
    printf("======================\n\n");
		FCFS(1, size[0], w1burstTime, w1arrivalTime, w1process, 0, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
    printf("\n\nSHORTEST JOB FIRST\n");
    printf("==================\n\n");
		SJF(1, size[0], w1burstTime, w1arrivalTime, w1process, 1, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
    if(checkNoOverhead[0] != 1)
    {
      printf("\n\nROUND ROBIN\n");
      printf("===========\n\n");
      RR(1, size[0], w1burstTime, w1arrivalTime, w1process, overhead[0], quantum[0], 2, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
      printComparison(3, 0, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
    }
    else
    {
      printf("\n\nROUND ROBIN WITHOUT OVERHEAD\n");
      printf("============================\n\n");
      RR(1, size[0], w1burstTime, w1arrivalTime, w1process, 0, quantum[0], 2, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
      printf("\n\nROUND ROBIN WITH OVERHEAD\n");
      printf("=========================\n\n");
      RR(1, size[0], w1burstTime, w1arrivalTime, w1process, overhead[0], quantum[0], 3, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
      printComparison(4, 0, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
    }

    printf("\n\n=================\n");
    printf("W O R K L O A D 2\n");
    printf("=================\n\n");
		printf("\nFIRST COME FIRST SERVE\n");
    printf("======================\n\n");
		FCFS(2, size[1], w2burstTime, w2arrivalTime, w2process, 0, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
		printf("\n\nSHORTEST JOB FIRST\n");
    printf("==================\n\n");
		SJF(2, size[1], w2burstTime, w2arrivalTime, w2process, 1, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
    if(checkNoOverhead[1] != 1)
    {
      printf("\n\nROUND ROBIN\n");
      printf("===========\n\n");
		  RR(2, size[1], w2burstTime, w2arrivalTime, w2process, overhead[1], quantum[1], 2, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
      printComparison(3, 0, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
    }
    else
    {
      printf("\n\nROUND ROBIN WITHOUT OVERHEAD\n");
      printf("============================\n\n");
		  RR(2, size[1], w2burstTime, w2arrivalTime, w2process, 0, quantum[1], 2, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
      printf("\n\nROUND ROBIN WITH OVERHEAD\n");
      printf("=========================\n\n");
      RR(2, size[1], w2burstTime, w2arrivalTime, w2process, overhead[1], quantum[1], 3, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
      printComparison(4, 0, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
    }
	}
  // run 1 specific algorithm
	else
	{
		switch(choice2)
		{
			case 1:
        printf("\nFIRST COME FIRST SERVE\n");
        printf("======================\n");
        printf("\n\n=================\n");
        printf("W O R K L O A D 1\n");
        printf("=================\n\n");
				FCFS(1, size[0], w1burstTime, w1arrivalTime, w1process, 0, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
        printComparison(1, choice2, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
        printf("\n\n=================\n");
        printf("W O R K L O A D 2\n");
        printf("=================\n\n");
				FCFS(2, size[1], w2burstTime, w2arrivalTime, w2process, 0, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
        printComparison(1, choice2, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
				break;
			case 2:
        printf("\nSHORTEST JOB FIRST\n");
        printf("==================\n");
        printf("\n\n=================\n");
        printf("W O R K L O A D 1\n");
        printf("=================\n\n");
				SJF(1, size[0], w1burstTime, w1arrivalTime, w1process, 0, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
        printComparison(1, choice2, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
        printf("\n\n=================\n");
        printf("W O R K L O A D 2\n");
        printf("=================\n\n");
				SJF(2, size[1], w2burstTime, w2arrivalTime, w2process, 0, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
        printComparison(1, choice2, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
				break;
			case 3:
        printf("\nROUND ROBIN\n");
        printf("===========\n");
        printf("\n\n=================\n");
        printf("W O R K L O A D 1\n");
        printf("=================\n\n");
        if(checkNoOverhead[0] != 1)
        {
          RR(1, size[0], w1burstTime, w1arrivalTime, w1process, overhead[0], quantum[0], 0, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
          printComparison(1, choice2, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
        }
        else
        {
          printf("\n\nWITHOUT OVERHEAD\n");
          printf("================\n\n");
          RR(1, size[0], w1burstTime, w1arrivalTime, w1process, 0, quantum[0], 0, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
          printf("\n\nWITH OVERHEAD\n");
          printf("=============\n\n");
          RR(1, size[0], w1burstTime, w1arrivalTime, w1process, overhead[0], quantum[0], 1, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
          printComparison(2, choice2, w1AvgWaitingTime, w1AverageTurnAroundTime, w1CpuUsage);
        }
        printf("\n\n=================\n");
				printf("W O R K L O A D 2\n");
        printf("=================\n\n");
        if(checkNoOverhead[1] != 1)
        {
          RR(2, size[1], w2burstTime, w2arrivalTime, w2process, overhead[1], quantum[1], 0, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
          printComparison(1, choice2, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
        }
        else
        {
          printf("\n\nWITHOUT OVERHEAD\n");
          printf("================\n\n");
          RR(2, size[1], w2burstTime, w2arrivalTime, w2process, 0, quantum[1], 0, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
          printf("\n\nWITH OVERHEAD\n");
          printf("=============\n\n");
          RR(2, size[1], w2burstTime, w2arrivalTime, w2process, overhead[1], quantum[1], 1, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
          printComparison(2, choice2, w2AvgWaitingTime, w2AverageTurnAroundTime, w2CpuUsage);
        }
				break;
		}
	}

	return 0;
}

void FCFS(int workload_id, int size, int burstTime[], int arrivalTime[], int process[], int algoNum, float *avgWaitingTime, float *avgTurnAroundTime, float *cpuUsage)
{
	int temp = 0, i = 0, j = 0;
	int turnAroundTime[size], completionTime[size], waitingTime[size], serviceTime[size];
	int totalWaitingTime = 0, totalTurnAroundTime = 0;

	//Rearrange array based on arrival time
	for(i = 0; i < size - 1;i++)
	{
		//min = arrivalTime[i];
		for (j = i + 1; j < size; j++)
		{
			if(arrivalTime[i] > arrivalTime[j])
			{
				temp = arrivalTime[j];
				arrivalTime[j] = arrivalTime[i];
				arrivalTime[i] = temp;
				temp = burstTime[j];
				burstTime[j] = burstTime[i];
				burstTime[i] = temp;
				temp = process[j];
				process[j] = process[i];
				process[i] = temp;
			}
		}
	}
		
 //find the service time for each process
 	for(i = 0; i < size; i++)
	{
		if(i == 0)
			serviceTime[i] = arrivalTime[i]	;
		else
			serviceTime[i] = serviceTime[i-1] + burstTime[i-1];
	}
		
 	//calculate waiting time for each process
 	for(i = 0; i < size; i++)
	{
		if(i == 0)
			waitingTime[0] = 0;
		else
		{
			waitingTime[i] = serviceTime[i] - arrivalTime[i];
			if(waitingTime[i] < 0)
	 			waitingTime[i] = 0;
		}
	}
	    
    //calculate turnaround time, total turnaround time and total waiting time
    for (i = 0; i < size; i++)
    {
    	turnAroundTime[i] = burstTime[i] + waitingTime[i];
   		totalWaitingTime = totalWaitingTime + waitingTime[i];
      totalTurnAroundTime = totalTurnAroundTime + turnAroundTime[i];
      completionTime[i] = turnAroundTime[i] + arrivalTime[i];
      if(i > 0){
      	if(completionTime[i-1] < arrivalTime[i])
      		serviceTime[i] = arrivalTime[i];
      }
    }
		
	//calculate average waiting time and turnaround time
  avgWaitingTime[algoNum] = (float) totalWaitingTime / (float) size;
 	avgTurnAroundTime[algoNum] = (float) totalTurnAroundTime / (float) size;

  //calculate CPU Utilization
  cpuUsage[algoNum] = cpuUtilization(size, burstTime, completionTime);
	
  printDetails(workload_id, size, burstTime, arrivalTime, process, waitingTime, serviceTime, turnAroundTime, completionTime);
}


void SJF(int workload_id, int size, int burstTime[], int arrivalTime[], int process[], int algoNum, float *avgWaitingTime, float *avgTurnAroundTime, float *cpuUsage)
{
	  int hold[size], i, count = 0, smallA, totalArrivalTime, addIndex = 0, ganttOrder[size][6];
    int serviceTime[size], completionTime[size], turnAroundTime[size], waitingTime[size];
    int checker, temp, totalBurst = 0, totalCompletion = 0;
    float averageWaiting = 0.0, averageTurnAround = 0.0, utilization = 0.0;
    
    for(i = 0; i < size; i++){
		  count += burstTime[i];
		  count += arrivalTime[i];
		  hold[i] = -1;
	  }
	
    checker = arrivalTime[0];
    
    for(i = 0; i < size; i++)
	{
        if(arrivalTime[i] < checker)
		{
            checker = arrivalTime[i];
        }
    }
    
    count = count + checker;
    totalArrivalTime = checker;
    temp = 0;
    
    while(totalArrivalTime < count)
	{
        //find the smallest arrival time
        for(i = 0; i < size; i++)
		{
            if(hold[i] == -1 && arrivalTime[i] <= totalArrivalTime)
			{
                smallA = i;
                temp = 1;
                break;
            }
        }
        
        //find the smallest burst time if found any
        for(i = 0; i < size; i++){
            if(hold[i] == -1 && arrivalTime[i] <= totalArrivalTime){
                if(burstTime[smallA] > burstTime[i]){
                    smallA = i;
                    temp = 1;
                }
            }
        }
        
       //store the process in order
       if(temp == 1){
        temp = 0;
        totalArrivalTime = totalArrivalTime + burstTime[smallA];
        hold[smallA] = 0;
        ganttOrder[addIndex][0] = process[smallA];  //processID
        ganttOrder[addIndex][1] = arrivalTime[smallA]; //arrivalTime
        ganttOrder[addIndex][2] = burstTime[smallA];  //burstTIme
        ganttOrder[addIndex][3] = totalArrivalTime;  //completionTime
        addIndex++;
      
       }else{
           temp = 0;
           totalArrivalTime = totalArrivalTime + 1;
       }
        
    }

    serviceTime[0] = checker; 
    for(i = 1; i < size; i++){
		int serTime = serviceTime[i - 1] + burstTime[i - 1];
		int arrTime = arrivalTime[i];
		int time_diff = 0;
		while(serTime < arrTime){
			time_diff++;
			serTime++;
		}
        serviceTime[i] = time_diff + ganttOrder[i - 1][2] + serviceTime[i - 1]; //getting each of service time
    }
    ganttOrder[0][5] = 0;
    
    for(i = 1; i < size; i++){
        ganttOrder[i][5] = serviceTime[i] - ganttOrder[i][1]; //service - arrival = waiting
        if(ganttOrder[i][5] < 0){
            ganttOrder[i][5] = abs(ganttOrder[i][5]);
        }
        averageWaiting += ganttOrder[i][5];
    }
    averageWaiting = averageWaiting / size;

    //find turnaroundtime
    for(i = 0; i < size; i++){
        ganttOrder[i][4] = ganttOrder[i][2] + ganttOrder[i][5]; //burst time + waiting = turnaround
        averageTurnAround += ganttOrder[i][4];
    }
    averageTurnAround = averageTurnAround / size;
    totalCompletion = ganttOrder[0][3];
    
    for(i = 0; i < size; i++)
    {
   		process[i] = ganttOrder[i][0];
   		arrivalTime[i] = ganttOrder[i][1];
   		burstTime[i] = ganttOrder[i][2];
   		completionTime[i] = ganttOrder[i][3];
   		turnAroundTime[i] = ganttOrder[i][4];
   		waitingTime[i] = ganttOrder[i][5];
    }
  
  //Calculate CPU Utilization
  utilization = cpuUtilization(size, burstTime, completionTime);

  avgWaitingTime[algoNum] = averageWaiting;
  avgTurnAroundTime[algoNum] = averageTurnAround;
  cpuUsage[algoNum] = cpuUtilization(size, burstTime, completionTime);

  printDetails(workload_id, size, burstTime, arrivalTime, process, waitingTime, serviceTime, turnAroundTime, completionTime);
}

void RR(int workload_id, int size, int burstTime[], int arrivalTime[], int process[], int overhead, int quantum, int algoNum, float *avgWaitingTime, float *avgTurnAroundTime, float *cpuUsage)
{
	int i, j, k, rearrange, rearrangeind, temp, skip;
	int turnAroundTime[size], completionTime[size], rem_bt[size], waitingTime[size], firstServiceTime[size];
	int totalWaitingTime = 0, totalTurnAroundTime = 0;
	
	// Variables for rearrange order
	int ind, min;
	
	// Variables for algorithm
	int prevt, t, p;
	
	// Variables for loop
	bool pdone[size], alldone;

	for(i = 0; i < size; i++)
  {
    firstServiceTime[i] = -1;
  }
	
	//Rearrange array based on arrival time
	for(i = 0; i < size - 1;i++)
	{
		min = arrivalTime[i];
		for (j = i + 1; j < size; j++)
		{
			if(arrivalTime[j] < min)
			{
				min = arrivalTime[j];
				ind = j;
			}
		}
		
		if (min != arrivalTime[i])
		{
			temp = arrivalTime[i];
			arrivalTime[i] = arrivalTime[ind];
			arrivalTime[ind] = temp;
			
			temp = burstTime[i];
			burstTime[i] = burstTime[ind];
			burstTime[ind] = temp;
			
			temp = process[i];
			process[i] = process[ind];
			process[ind] = temp;
		}
	}
			
	
	// Skip time to arrival time of first process
	t = arrivalTime[0];
	p = -1;

  /*
	 Calculate Waiting Time and Turnaround Time
	*/

	// Copy burst time into another will be edited list
	for (i = 0 ; i < size; i++)
		rem_bt[i] = burstTime[i];

	// Loop processes in Round Robin method
	while (1) 
	{
		prevt = t;
		
		// Loop processes in arrival time order
		for (i = 0 ; i < size; i++)
		{
			// skip if task has yet to arrive
			if (t < arrivalTime[i])
			{
				pdone[i] = false;
        p = -1;
				continue;
			}
      else if(rem_bt[i] == 0)
      {
        pdone[i] = true;
        p = -1;
        continue;
      }
			
			pdone[i] = true;
			
			//If process is not yet complete
			if (rem_bt[i] > 0) 
			{
				pdone[i] = false;
				
				// If remaining time is more than time quantum
				if (rem_bt[i] > quantum) 
				{
          // check if switching occurs
          if(p == -1)
          {
            p = process[i];
          }
					else if (p != process[i])
					{
						p = process[i];
						t += overhead;
					}

          // set first service time if not available yet
          if(firstServiceTime[i] == -1)
            firstServiceTime[i] = t;

					// Add total running time by time quantum and minus remaining time
					t += quantum;
					
					rem_bt[i] -= quantum;
				} 
				// Else if remaining time is less than time quantum
				else
				{
          // if switching occurs
          if(p == -1)
          {
            p = process[i];
          }
					else if (p != process[i])
					{
						p = process[i];
						t += overhead;
					}

          // set first service time if not available yet
          if(firstServiceTime[i] == -1)
            firstServiceTime[i] = t;

					// Add total running time by remaining time
					t += rem_bt[i];
					
					// Remaining time becomes zero as process is completed
					rem_bt[i] = 0;

					// Waiting time will be current time minus by running time
					waitingTime[i] = t - burstTime[i] - arrivalTime[i];
					
					// Turnaround Time will be the total run time
					turnAroundTime[i] = t - arrivalTime[i];
				}
			}
		
			// check if need to change arrangement of processes
			if(rem_bt[i] != 0)
			{
				for(k = i + 1; k < size; k++)
				{
					if(t < arrivalTime[k])
					{
						rearrange = 1;
						rearrangeind = k;
						break;
					}
				}

				if(rearrange == 1)
				{
					for(k = i; k < rearrangeind; k++)
					{
						temp = arrivalTime[k];
						arrivalTime[k] = arrivalTime[k + 1];
						arrivalTime[k + 1] = temp;
						
						temp = burstTime[k];
						burstTime[k] = burstTime[k + 1];
						burstTime[k + 1] = temp;
						
						temp = process[k];
						process[k] = process[k + 1];
						process[k + 1] = temp;
						
						temp = rem_bt[k];
						rem_bt[k] = rem_bt[k + 1];
						rem_bt[k + 1] = temp;

            temp = waitingTime[k];
						waitingTime[k] = waitingTime[k + 1];
						waitingTime[k + 1] = temp;

            temp = turnAroundTime[k];
						turnAroundTime[k] = turnAroundTime[k + 1];
						turnAroundTime[k + 1] = temp;

            temp = completionTime[k];
						completionTime[k] = completionTime[k + 1];
						completionTime[k + 1] = temp;

            temp = firstServiceTime[k];
						firstServiceTime[k] = firstServiceTime[k + 1];
						firstServiceTime[k + 1] = temp;
					}
					
					rearrange = 0;
					i = i - 1;
				}
			}
		}
		
		// if time did not change, add time by 1
		if(prevt == t)
		{
			t += 1;
		}
		
		alldone = true;
		
		// If all processes are done
		for(i = 0; i < size; i++)
		{
			if(pdone[i] == false)
			{
				alldone = false;
				break;
			}
		}
		if (alldone)
			break;
	}
	
	//calculate turnaround time, total turnaround time and total waiting time
    for (i = 0; i < size; i++)
    {
    	totalWaitingTime = totalWaitingTime + waitingTime[i];
      totalTurnAroundTime = totalTurnAroundTime + turnAroundTime[i];
      completionTime[i] = turnAroundTime[i] + arrivalTime[i];
	}
	
	// calculate average waiting time and turnaround time
	avgWaitingTime[algoNum] = (float)totalWaitingTime / size;
 	avgTurnAroundTime[algoNum] = (float)totalTurnAroundTime / size;
 	
 	//Rearrange array based on process id
	for(i = 0; i < size - 1; i++)
	{
		min = process[i];
		for (j = i + 1; j < size; j++)
		{
			if(process[j] < min)
			{
				min = process[j];
				ind = j;
			}
		}
		
		if (min != process[i])
		{
			temp = arrivalTime[i];
			arrivalTime[i] = arrivalTime[ind];
			arrivalTime[ind] = temp;
			
			temp = burstTime[i];
			burstTime[i] = burstTime[ind];
			burstTime[ind] = temp;
			
			temp = process[i];
			process[i] = process[ind];
			process[ind] = temp;
			
			temp = waitingTime[i];
			waitingTime[i] = waitingTime[ind];
			waitingTime[ind] = temp;
			
			temp = turnAroundTime[i];
			turnAroundTime[i] = turnAroundTime[ind];
			turnAroundTime[ind] = temp;
			
			temp = completionTime[i];
			completionTime[i] = completionTime[ind];
			completionTime[ind] = temp;

      temp = firstServiceTime[i];
			firstServiceTime[i] = firstServiceTime[ind];
			firstServiceTime[ind] = temp;
		}
	}

  //Calculate CPU Utilization
  cpuUsage[algoNum] = cpuUtilization(size, burstTime, completionTime);
		
	// Print results
  printf("Time quantum = %d\n",quantum);
  printf("Overhead = %d\n",overhead);
  printDetails(workload_id, size, burstTime, arrivalTime, process, waitingTime, firstServiceTime, turnAroundTime, completionTime);
  printf("\n** Note that the service time for Round Robin represents the first service time for each process **\n\n");
}

int askBurstTime(int i)
{
	int burstTime;
	
	printf("What is the burst time for process %d (in seconds)?\n",i+1);
	scanf("%d",&burstTime);
	while(burstTime < 0)
	{
		printf("The burst time of process cannot be less than 0.\n");
		printf("What is the burst time for process %d (in seconds)?\n",i+1);
		scanf("%d",&burstTime);
	}
	
	return burstTime;
}

int askArrivalTime(int i)
{
	int arrivalTime;
	
	printf("What is the arrival time for process %d (in seconds)?\n",i+1);
	scanf("%d",&arrivalTime);
	while(arrivalTime < 0)
	{
		printf("The arrival time of process cannot be less than 0.\n");
		printf("What is the arrival time for process %d (in seconds)?\n",i+1);
		scanf("%d",&arrivalTime);
	}
	
	return arrivalTime;
}

int askOverheadTime()
{
	int overhead;
	
	printf("What is the overhead time for all processes (in seconds)? (put 0 if don't want overhead)\n");
	scanf("%d",&overhead);
	while(overhead < 0)
	{
		printf("The overhead time of work cannot be less than 0.\n");
		printf("What is the overhead time for all processes (in seconds)? (put 0 if don't want overhead)\n");
		scanf("%d",&overhead);
	}
	
	return overhead;
}

int askCheckNoOverhead(int overhead)
{
  int checkNoOverhead;

  if(overhead > 0)
  {
    printf("Would you like to see an output with no overhead as well?\n");
    printf("1 - Yes\n");
    printf("2 - No\n");
    scanf("%d",&checkNoOverhead);
    while(checkNoOverhead < 1 || checkNoOverhead > 2)
    {
      printf("Please enter either option 1 or 2 only!\n");
      printf("Would you like to see an output with no overhead as well?\n");
      printf("1 - Yes\n");
      printf("2 - No\n");
      scanf("%d",&checkNoOverhead);
    }

    return checkNoOverhead;
  }
  else
  {
    return 2;
  }
}

int askQuantumTime()
{
	int quantum;
	
	printf("What is the time quantum for both workloads (in seconds)?\n");
	scanf("%d",&quantum);
	while(quantum < 0)
	{
		printf("The time quantum cannot be less than 0.\n");
		printf("What is the time quantum for both workloads (in seconds)?\n");
		scanf("%d",&quantum);
	}
	
	return quantum;
}

float cpuUtilization(int size, int burstTime[], int completionTime[])
{
  int i, totalBurstTime = 0, finalCompletion;
  float utilization;
  //Calculate total burst time
  for(i = 0; i < size; i++)
  {
    totalBurstTime += burstTime[i];
  }

  //Find final completion time (because RR is arranged differently)
  finalCompletion = completionTime[0];
  for(i = 1; i < size; i++)
  {
    if(finalCompletion < completionTime[i])
    {
      finalCompletion = completionTime[i];
    }
  }

  //Calculate utilization time
  utilization = ((float)totalBurstTime / (float) finalCompletion) * 100.00;

  return utilization;
}

void printDetails(int workload_i, int size, int burstTime[], int arrivalTime[], int process[], int waitingTime[], int serviceTime[], int turnAroundTime[], int completionTime[])
{
	int i;
	
	//print the details
  printf("STARTING TIME = 0\n");
  printf("--------------------------------------------------------------------------------------------------------------------------\n");
  printf("|%-15s|","PROCESS ID");
  printf("%-15s|","BURST TIME");
  printf("%-15s|","ARRIVAL TIME");
  printf("%-15s|","WAITING TIME");
  printf("%-15s|","SERVICE TIME");
  printf("%-20s|","TURN AROUND TIME");
  printf("%-20s|\n","COMPLETION TIME");
  printf("--------------------------------------------------------------------------------------------------------------------------\n");
  
  for (i = 0 ; i < size; i++)
  {
      printf("|%-15d|",process[i]);
      printf("%-15d|",burstTime[i]);
      printf("%-15d|",arrivalTime[i]);
      printf("%-15d|",waitingTime[i]);
      printf("%-15d|", serviceTime[i]);
      printf("%-20d|",turnAroundTime[i]);
      printf("%-20d|\n",completionTime[i]);
      printf("--------------------------------------------------------------------------------------------------------------------------\n");
  }
}

void printComparison(int numOfAlgo, int whichAlgo, float *avgWaitingTime, float *avgTurnAroundTime, float *cpuUsage)
{
  int i, ind, indWait, indTurnAround, status;
  int algoStatus[numOfAlgo];
  float minWait, minTurnAround;
  char *algoNames[numOfAlgo];
  char bestAlgo[150] = "";
  char fcfs[] = "First Come First Serve";
  char sjf[] = "Shortest Job First";
  char rr[] = "Round Robin";
  char rrno[] = "Round Robin without Overhead";
  char rrwo[] = "Round Robin with Overhead";

  //set algoStatus all to 0 if there's more than 1
  if(numOfAlgo > 1)
  {
    for(i = 0; i < numOfAlgo; i++)
    {
      algoStatus[i] = 0;
    }
  }


  //create array of algorithm names
  if(numOfAlgo == 1)
  {
    if(whichAlgo == 1)
      algoNames[0] = fcfs;
    else if(whichAlgo == 2)
      algoNames[0] = sjf;
    else
      algoNames[0] = rr;
  }
  else if(numOfAlgo == 2)
  {
    algoNames[0] = rrno;
    algoNames[1] = rrwo;
  }
  else if(numOfAlgo == 3)
  {
    algoNames[0] = fcfs;
    algoNames[1] = sjf;
    algoNames[2] = rr;
  }
  else
  {
    algoNames[0] = fcfs;
    algoNames[1] = sjf;
    algoNames[2] = rrno;
    algoNames[3] = rrwo;
  }
	
	//print the details
  printf("\n------------------------------------------------------------------------------------------------------------------\n");
  printf("|%-35s|","ALGORITHM");
  printf("%-25s|","AVERAGE WAITING TIME");
  printf("%-25s|","AVERAGE TURNAROUND TIME");
  printf("%-25s|\n","CPU UTILIZATION");
  printf("------------------------------------------------------------------------------------------------------------------\n");
  
  for (i = 0 ; i < numOfAlgo; i++)
  {
    printf("|%-35s|", algoNames[i]);
    printf("%-25.2f|", avgWaitingTime[i]);
    printf("%-25.2f|", avgTurnAroundTime[i]);
    printf("%-25.2f|\n", cpuUsage[i]);
    printf("------------------------------------------------------------------------------------------------------------------\n");
  }

  //compare algorithms
  if(numOfAlgo > 1)
  {
    // find smallest average waiting time and average turnaround time
    minWait = avgWaitingTime[0];
    minTurnAround = avgTurnAroundTime[0];
    indWait = 0;
    indTurnAround = 0;
    strcat(bestAlgo, algoNames[0]);
    for(i = 1; i < numOfAlgo; i++)
    {
      if(avgWaitingTime[i] < minWait || avgTurnAroundTime[i] < minTurnAround)
      {
        strcpy(bestAlgo, "");
        strcat(bestAlgo, algoNames[i]);
      }
      else if(avgWaitingTime[i] == minWait && avgTurnAroundTime[i] == minTurnAround)
      {
        strcat(bestAlgo, " & ");
        strcat(bestAlgo, algoNames[i]);
      }
    }

    printf("\nBest Algorithm: %s\n", bestAlgo);
  }
}