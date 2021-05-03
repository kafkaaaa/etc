#include <stdio.h>
#include <stdlib.h>		// to use 'system' function
#include <windows.h>	// to use 'Sleep' function

void main()
{
	int i, j;
	int t, tt, ttt;			// temp �ӽ� ����� 
	int w[10], a[10];
	
	int n;					// process�� ����  			
	int b[10];				// process�� CPU �۾� �ð� 
	int arrival_time[10];	// process�� ���� �ð�  
	int p[10];				// process�� �켱 ����  

	float avg = 0;			// �� ��� �ð� 
	
	system("cls");	// clear screen
	
	printf("\n\tPRIORITY SCHEDULING ALGORITHM");
	printf("\n\t********************************\n");
	
	// ���μ����� ���� �Է�  
	printf("\nEnter how many jobs: ");
	scanf("%d", &n);
	
	// ���� �ð� �Է� 
    printf("\nEnter ARRIVAL TIME for corresponding job...\n");
	for (i = 1; i <= n; i++)
	{
		printf("\nProcess %d: ", i);
		scanf("%d", &arrival_time[i]);
	}
	
	// �۾� �ð� & �켱���� �Է� 
	printf("\nEnter burst time & priority for corresponding job...\n");
	for(i = 1; i <= n; i++)
	{
		printf("\nProcess %d: ", i);
		scanf("%d %d", &b[i], &p[i]);
		a[i] = i;
	}

	// �켱������ ������ ���μ����� ����(��) ġȯ 
	for (i=2; i<n; i++)
	{ 
		// i+1 �� �켱������ i���� ������ (���� ������)
		// ���μ���[i+1]�� [i]���� ������ ġȯ 
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
	
	// ó�� ��� �ð� 0�� ���μ����� �ٷ� ���� 
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
	
	// ���μ��� �۾� ���� (Gaunt Chart) ��� 
	for(i=1; i<=n; i++)
	{
	 	printf("%d", b[i]);
		for(j=1; j<=b[i]; j++)
			printf("%c", 22);	
		Sleep(1000);
	}

}

