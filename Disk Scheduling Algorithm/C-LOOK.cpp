#include<bits/stdc++.h>

int find(int d[], int n, int disk)
{
	for(int i=0; i<n-1; i++)
  	{
    	if(d[i] > disk)
		{
      		return i;
      		break;
    	}
  	}
}

int main()
{
 int i, j, n, temp, no_t;
 int disk;   //loc of head	(디스크헤드의 위치) 

 printf("Enter Total Number of Tracks : ");	// 총 트랙의 수(25) 
 scanf("%d", &no_t);

 printf("\nEnter Number of Location : ");	// 요청받은 트랙 수(9) 
 scanf("%d", &n);

 int d[n+1]; // disk queue (요청 큐) 

 printf("\nEnter Position of Head : ");	// 헤드의 위치 -> disk 
 scanf("%d", &disk);
 
 // 요청 받은 (n개의)트랙 번호를 요청 큐 d[0]~d[n-1] 에 입력 
 printf("\nEnter elements of Disk Queue : ");
 for(i=0; i<n; i++)
 	scanf("%d", &d[i]);

 // 요청 큐 오름차순 정렬 후 출력 
 for(i=0; i<n-1; i++)    // sorting disk locations
 {
  for(j=i+1; j<n; j++) {
    if(d[i] > d[j]) {
    	temp = d[i];
    	d[i] = d[j];
    	d[j] = temp;
    }
  }
 }
 printf("\nElements after Sorting : ");
 for(i=0;i<n;i++)
 	printf("%d ", d[i]);


 // 디스크헤드가 왼쪽 or 오른쪽으로 갈지 방향 결정 
 int dir;
 printf("\n\n---1: LEFT,  2: RIGHT---");
 printf("\nEnter Direction Head Move : ");
 scanf("%d", &dir);
 
  int c, sum=0;
  
//go towards left (헤드가 왼쪽으로 이동)
 if(dir == 1)
 {
// 트랙번호d[0]~d[n-1]은 이미 오름차순 정렬 되어있음. 
  int previous = find(d,n,disk);	// 5
   previous = previous-1;			// 4

   sum+=abs(disk-d[previous]);

   for(i=previous; i>=0; i--)		// i=4,3,2,1,0
   {
    printf("%d-> ", d[i]);		// 15->14->11->8->3
    
    if(i != 0)
    {
       int dr = abs(d[i]-d[i-1]);
       sum += dr;
    }
   }
   
   // 다시 요청 큐의 오른쪽 끝(d[n-1])까지 이동한 거리 계산 
   sum += abs(d[n-1] - d[0]); 

   for(i=n-1; i>=previous+1; i--)	// i=8,7,6,5
   {
       printf("%d-> ", d[i]);	// 23->20->19->17

       if(i != previous+1)
        sum += abs(d[i] - d[i-1]);
   }
   printf("\nMovement of Total Cylinders %d\n",sum);
 }


 //go towards right (헤드가 오른쪽으로 이동) 
else if(dir==2)
{
  int previous = find(d,n,disk);
   printf("%d\n",previous);

   sum+=abs(d[previous]-disk);

   printf("%d-> ",disk);

   for(i=previous;i<n;i++)
   {
    printf("%d-> ",d[i]);
    if(i!=n-1)
       sum+=abs(d[i+1]-d[i]);
   }

   for(i=0;i<=previous-1;i++)
   {
       printf("%d-> ",d[i]);

       if(i!=previous-1)
        sum+=abs(d[i+1]-d[i]);
   }
   printf("\nMovement of total cylinders %d\n",sum);
}

return 0;
}
