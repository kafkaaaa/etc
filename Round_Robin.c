#include <stdio.h>
#include <stdlib.h>		// to use 'system' function
#include <windows.h>	// to use 'Sleep' function

int num_process = 0;    // process�� ���� 
int tmp = 0;			// process�� ���� temp
int q = 0;				// time quantum
int r = 0;				// round ȸ�� 

int burst_time[10];		// �� process�� CPU �۾� �ð� 
int z[10];				// �۾� �ð� temp 
int arrival_time[10];	// �� process�� ���� �ð� 
int wait_time = 0;		// ��� �ð� 
int total_time = 0;		// �� ���� �ð� 

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
	
	// ���μ����� ���� �Է� 
    printf("\nEnter how many jobs: ");
    scanf("%d", &num_process);
    tmp = num_process;
    
	// ���� �ð� �Է� 
    printf("\nEnter ARRIVAL TIME for corresponding job...\n");
	for (i = 1; i <= num_process; i++)
	{
		printf("\nProcess %d: ", i);
		scanf("%d", &arrival_time[i]);
	}
	// �۾� �ð� �Է� 
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
	// �ִ� burst_time ���ϱ� 
	int max = 0;
	max = burst_time[1];
	for (j = 1; j <= num_process; j++) {
		if (max <= burst_time[j])
			max = burst_time[j];
	}

	// round Ƚ�� ���ϱ� (�ִ� burst_time / time quantum)
	if ( (max % q) == 0 )
		r = (max / q);
	else
		r = (max / q) + 1;
		
	for (i = 1; i <= r; i++) {
		printf("\n-------------Round %d-------------", i);
		
		for (j = 1; j <= num_process; j++) {
			
			// Ÿ�� �����̽����� ���� �۾��ð��� �������� �� 
			if (burst_time[j] > q)
			{
				burst_time[j] -= q;
				total_time += q;
				// ���� �۾��ð� ��� 
				printf("\nProcess[%d] remaining time is %d", j, burst_time[j]);
			}
			// Ÿ�� �����̽����� ���� �۾��ð��� �������� �� 
			else if (burst_time[j] < q && burst_time[j] > 0)
			{
				burst_time[j] = 0;
				total_time += burst_time[j];
			}
			
			// ���� �۾��ð��� 0 ���ϰ� �Ǹ� 
			if (burst_time[j] <= 0)
			{
				burst_time[j] = 0;
				// ���μ��� �Ϸ� ��� 
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
	
	// �� ����� �����ð��� ������� �ʾ����Ƿ� 
	// �������� ���μ������� ���� �ð���ŭ�� ���ش�  
	for (i = 1; i <= num_process; i++) {
		wait_time -= arrival_time[i];
	}

	printf("\nTotal WAITING TIME: %d", wait_time);
	printf("\nAverage WAITING TIME: %f\n\n", (float) wait_time / num_process);
	
	// ���μ��� �۾� ���� ����ϱ� 
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

