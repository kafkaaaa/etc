#include <stdio.h>
#include <stdlib.h>		// to use 'system' function
#include <windows.h>	// to use 'Sleep' function

int num_process = 0;    // process의 개수 
int tmp = 0;			// process의 개수 temp
int q = 0;				// time quantum
int r = 0;				// round 회수 

int burst_time[10];		// 각 process의 CPU 작업 시간 
int z[10];				// 작업 시간 temp 
int arrival_time[10];	// 각 process의 도착 시간 
int wait_time = 0;		// 대기 시간 
int total_time = 0;		// 총 수행 시간 

int i, j, e;
int m[50];

// function prototype
void RR();
void average();

void main()
{
	system("cls");	// clear screen
	
	printf("\nJOB SCHEDULING ALGORITHM[RR]");
	printf("\n*******************************************************\n");
	
	// 프로세스의 개수 입력 
    printf("\nEnter how many jobs: ");
    scanf("%d", &num_process);
    tmp = num_process;
    
	// 도착 시간 입력 
    printf("\nEnter ARRIVAL TIME for corresponding job...\n");
	for (i = 1; i <= num_process; i++)
	{
		printf("\nProcess %d: ", i);
		scanf("%d", &arrival_time[i]);
	}
	// 작업 시간 입력 
    printf("\nEnter BURST TIME for corresponding job...\n");
	for (i = 1; i <= num_process; i++)
	{
		printf("\nProcess %d: ", i);
		scanf("%d", &burst_time[i]);
		z[i] = burst_time[i];
	}
	
	printf("\nENTER THE TIME SLICE VALUE: ");
	scanf("%d", &q);

	RR();
	average();
}


void RR()
{
	// 최대 burst_time 구하기 
	int max = 0;
	max = burst_time[1];
	for (j = 1; j <= num_process; j++) {
		if (max <= burst_time[j])
			max = burst_time[j];
	}

	// round 횟수 구하기 (최대 burst_time / time quantum)
	if ( (max % q) == 0 )
		r = (max / q);
	else
		r = (max / q) + 1;
		
	for (i = 1; i <= r; i++) {
		printf("\n-------------Round %d-------------", i);
		
		for (j = 1; j <= num_process; j++) {
			
			// 타임 슬라이스보다 많은 작업시간이 남아있을 때 
			if (burst_time[j] > q)
			{
				burst_time[j] -= q;
				total_time += q;
				// 남은 작업시간 출력 
				printf("\nProcess[%d] remaining time is %d", j, burst_time[j]);
			}
			// 타임 슬라이스보다 적은 작업시간이 남아있을 때 
			else if (burst_time[j] < q && burst_time[j] > 0)
			{
				burst_time[j] = 0;
				total_time += burst_time[j];
			}
			
			// 남은 작업시간이 0 이하가 되면 
			if (burst_time[j] <= 0)
			{
				burst_time[j] = 0;
				// 프로세스 완료 출력 
				printf("\nProcess[%d] is Completed**", j);
			}
		}
		printf("\n");
	}
	
	Sleep(1000);
}


void average()
{
	for (i = 1; i <= num_process; i++)
	{
		e = 0;
		for (j = 1; j <= r; j++)
		{
			if (z[i] != 0)
			{
				if (z[i] >= q)
				{
					m[i + e] = q;  z[i] -= q;
				}
				else
				{
					m[i + e] = z[i];  z[i] = 0;
				}
			}
			else
				m[i + e] = 0;
			e = e + num_process;
		}
	}
	
	for (i = 2; i <= num_process; i++)
		for (j = 1; j <= i - 1; j++)
			wait_time += m[j];
			
	for (i = num_process + 1; i <= r * num_process; i++)
	{
		if (m[i] != 0)
		{
			for (j = i - (num_process - 1); j <= i - 1; j++)
				wait_time += m[j];
		}
	}
	
	// 위 계산은 도착시간을 고려하지 않았으므로 
	// 마지막에 프로세스들의 도착 시간만큼을 빼준다  
	for (i = 1; i <= num_process; i++) {
		wait_time -= arrival_time[i];
	}

	printf("\nTotal WAITING TIME: %d", wait_time);
	printf("\nAverage WAITING TIME: %f\n\n", (float) wait_time / num_process);
	
	// 프로세스 작업 과정 출력하기 
	for (i = 1; i <= r * num_process; i++)
	{
		if (m[i] != 0)
			if (i%num_process == 0) {
				printf("P%d", (i%num_process) + (num_process));
			}
			else
				printf("P%d", (i%num_process));
				
		for (j = 1; j <= m[i]; j++)
			printf("%c", 22);
	}
	
}

