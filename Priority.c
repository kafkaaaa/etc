#include <stdio.h>
#include <stdlib.h>		// to use 'system' function
#include <windows.h>	// to use 'Sleep' function

void main()
{
	int i, j;
	int t, tt, ttt;			// temp 임시 저장용 
	int w[10], a[10];
	
	int n;					// process의 개수  			
	int b[10];				// process의 CPU 작업 시간 
	int arrival_time[10];	// process의 도착 시간  
	int p[10];				// process의 우선 순위  

	float avg = 0;			// 총 대기 시간 
	
	system("cls");	// clear screen
	
	printf("\n\tPRIORITY SCHEDULING ALGORITHM");
	printf("\n\t********************************\n");
	
	// 프로세스의 개수 입력  
	printf("\nEnter how many jobs: ");
	scanf("%d", &n);
	
	// 도착 시간 입력 
    printf("\nEnter ARRIVAL TIME for corresponding job...\n");
	for (i = 1; i <= n; i++)
	{
		printf("\nProcess %d: ", i);
		scanf("%d", &arrival_time[i]);
	}
	
	// 작업 시간 & 우선순위 입력 
	printf("\nEnter burst time & priority for corresponding job...\n");
	for(i = 1; i <= n; i++)
	{
		printf("\nProcess %d: ", i);
		scanf("%d %d", &b[i], &p[i]);
		a[i] = i;
	}

	// 우선순위가 높으면 프로세스의 정보(값) 치환 
	for (i=2; i<n; i++)
	{ 
		// i+1 의 우선순위가 i보다 높으면 (값이 작으면)
		// 프로세스[i+1]과 [i]번의 정보를 치환 
		if (p[i+1] < p[i]) {
			t = b[i];
			tt = a[i];
			ttt = arrival_time[i];
			
			b[i] = b[i+1];
			a[i] = a[i+1];
			arrival_time[i] = arrival_time[i+1];
			
			b[i+1] = t;
			a[i+1] = tt;
			arrival_time[i+1] = ttt;
		}
	}
	
	// 처음 대기 시간 0인 프로세스는 바로 실행 
	w[1] = 0;
	printf("\nProcess[%d] waiting time is 0", a[1]);
	 
	for(i=2; i<=n; i++)
	{
		w[i] = b[i-1] + w[i-1]; 
	  	printf("\nProcess[%d] waiting time: %d", a[i], w[i] - arrival_time[i]);
	  	avg += w[i] - arrival_time[i];
	}
	
	printf("\n\nTotal WAITING TIME is: %f", avg);
	printf("\n\nAverage WAITING TIME is: %f\n", avg / n);
	printf("\nGaunt Chart\n**********\n");
	
	// 프로세스 작업 과정 (Gaunt Chart) 출력 
	for(i=1; i<=n; i++)
	{
	 	printf("%d", b[i]);
		for(j=1; j<=b[i]; j++)
			printf("%c", 22);	
		Sleep(1000);
	}

}

