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
 int i, j, n, disk, temp, no_t;

 printf("Enter total number of tracks : ");	// �� Ʈ���� ��(25) 
 scanf("%d", &no_t);

 printf("\nEnter number of location : ");	// ��û���� Ʈ�� ��(9) 
 scanf("%d", &n);

 int d[n+1]; // disk queue (��û ť) 

 printf("\nEnter position of head : ");	// ����� ��ġ -> disk 
 scanf("%d", &disk);
 
 // ��û ���� (n����)Ʈ�� ��ȣ�� ��û ť d[0]~d[n-1] �� �Է� 
 printf("\nEnter elements of disk queue\n");
 for(i=0; i<n; i++)
 	scanf("%d", &d[i]);

 // ��û ť �������� ���� �� ��� 
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

 // ��ũ��尡 ���� or ���������� ���� ���� ���� 
 int dir;
 printf("\n\n---1: LEFT,  2: RIGHT---");
 printf("\nEnter Direction Head Move : ");
 scanf("%d", &dir);

 int c, sum=0;

//go towards left (��尡 �������� �̵�) 
 if(dir == 1)
 {
// Ʈ����ȣd[0]~d[n-1]�� �̹� �������� ���� �Ǿ�����. 
  int previous = find(d,n,disk);	// 5
  previous = previous-1;			// 4

   sum += abs(disk - d[previous]);

   for(i=previous; i>=0; i--)	// i=4,3,2,1,0
   {
    printf("%d-> ", d[i]);		// 15->14->11->8->3
    
    if(i != 0)
    {
       int dr = abs(d[i] - d[i-1]);
       sum += dr;
    }
    else if(i == 0)
	{
		printf("0-> ");
		sum += d[i]; 	// d[1] ���� ���� ��(0) ���� �̵��� �Ÿ� 
	}
   }
 
	// �ٽ� ������ ������ �̵��� �ϰ�(����X) �Ÿ� ��� 
	printf("%d-> ", no_t - 1);
   	sum += d[n-1];

   for(i=n-1; i>=previous+1; i--)	// i=8,7,6,5
   {
       printf("%d-> ", d[i]);		// 23->20->19->17

       if(i != previous+1)
        sum += abs(d[i] - d[i-1]);

       if(i == previous+1)
       	sum += abs(d[i] - d[i-1]);	// ���������� �̵��� �Ÿ� 
   }
   printf("\nMovement of Total Cylinders %d\n",sum);
 }


//go towards right (��尡 ���������� �̵�) 
 else if(dir == 2)
 {
  int previous = find(d, n, disk);
   printf("%d\n", previous);

   sum += abs(d[previous]- disk);
   printf("%d-> ", disk);

   for(i=previous; i<n; i++)
   {
    printf("%d-> ", d[i]);
    if(i != n-1)
       sum += abs(d[i+1] - d[i]);
    else if(i == n-1)
       sum += abs(no_t - 1 - d[i]);
   }
   printf("%d-> ", no_t - 1);
   printf("0-> ");

   sum += d[0];

   for(i=0; i<=previous-1; i++)
   {
       printf("%d->", d[i]);

       if(i != previous-1)
        sum += abs(d[i+1] - d[i]);
   }
   printf("\nMovement of Total Cylinders %d\n",sum);
}

return 0;
}
