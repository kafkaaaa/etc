#include<bits/stdc++.h>

int main()
{

 int n, head, i,j, seek=0, max1,diff;
 float avg;

 printf("Enter the Max Range of Disk : ");
 scanf("%d", &max1);

 printf("\nEnter the Size of Queue Request : ");
 scanf("%d", &n);

 int queue[n+1];

 printf("\nEnter the Request Track Queue : ");
 for(i=1; i<=n; i++)
 {
    scanf("%d", &queue[i]);
 }

 printf("\nEnter the Initial Disk Head Position : ");
 scanf("%d", &head);
 queue[0] = head;
 
 printf("\n=======FCFS Disk Scheduling=======\n");

 for(j=0; j<=n-1; j++)
 {
 	diff = abs(queue[j+1]-queue[j]);
 	seek += diff;
 	printf("Move is from [%d] to [%d] with Seek %d\n", queue[j], queue[j+1], diff);
 }

 printf("\nTotal Seek Time is : %d\n", seek);
 avg = seek/(float)n;

 printf("Average Seek Time is : %f", avg);

 return 0;
}
