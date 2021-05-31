#include<bits/stdc++.h>
using namespace std;

int main()
{
    int head;
    printf("Enter Head Position : ");
    cin>>head;

    int n, i;
    cout<<"\nEnter Total Requests : ";
    cin>>n;
    int queue1[n], done[n];
    printf("\nEnter Requests : ");
    for(i=0;i<n;i++)
    {
        scanf("%d", &queue1[i]);
        done[i]=0;
    }

    printf("%d-> ", head);
	done[0] = 1;	// 추가  
	
    int temp1 = head;
    int count1 = 1, j, sum = 0; // count1 : 0->1로 변경 
    while(count1 != n)
    {
    	int temp = 100000;
    	int k = -1;
    	for(j=0; j<n; j++)
   		{
        	if(temp1 != queue1[j] && done[j]==0)
        	{
        		if(temp>abs(temp1-queue1[j]))
        		{
           			temp = abs(temp1-queue1[j]);
           			k = j;
        		}
        	}
    	}
    	sum += temp;
    	printf("%d-> ", queue1[k]);
    	count1++;
    	temp1 = queue1[k];
    	done[k]=1;
    }
    cout<<endl;
    cout<<"Total Head Movement is : "<<sum<<endl;
}
