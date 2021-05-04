/*
   Banker's Algorithm
*/

#include <stdio.h>
#include <stdbool.h>	// to use 'bool', 'true', 'false'
#include <stdlib.h>

// ����ڿ�, ���� �Ҵ���ڿ��� ��, �ִ� �ڿ��� ��, ���� �����ڿ��� ��, ��ü �ڿ��� �� 
int expect[101][101], alloc[101][101], max[101][101], available[101], total;
bool finish[101];	// �� ���μ����� �۾��Ϸ� ���� 
int sequence[101];	// ���μ��� �۾� ���� 

/*
  Safety Algorithm:
  1) Let Work and Finish be vectors of length ��m�� and ��n�� respectively.
     Initialize: Work = Available
     Finish[i] = false; for i=1, 2, 3, 4��.n
  2) Find an i such that both
     a) Finish[i] = false
     b) expect[i] <= Work if no such i exists goto step (4)
  3) Work = Work + Allocation
     Finish[i] = true
     goto step (2)
  4) if finish [i] = true for all i
     then the system is in a safe state otherwise unsafe state
*/

void isSafe(int N, int M) {
	printf("\n<Checking...>\n");
	
	int i, j, count = 1;
	int work[101];		// ���� �ش� �ڿ�(Ÿ��)�� �����ڿ� �� 
	
	for (i=1; i<=M; i++)	
		work[i] = available[i]; 
	
	for (i=1; i<=100; i++)
		finish[i] = false; 
	
	while (count <= N) {
		bool canAllot = false;	// �ڿ��Ҵ� ���� ���� 
		
		for (i=1; i<=N; i++) {
			if (finish[i] == false) {			// �۾��� �Ϸ���� �ʾ����� 
				for (j=1; j<=M; j++) {
					if(work[j] < expect[i][j]) {	// ���� �����ڿ� < ����ڿ� 
						break;					// �Ҵ��� �� ����. 
					}
				}
				if (j > M) {					// ���� �����ڿ� >= ����ڿ� 
					for (j=1; j<=M; j++) {		// �ڿ� �Ҵ�(����) 
						work[j] += alloc[i][j];	// �Ҵ��ߴ� �ڿ� ��ȯ�� 
					}
					sequence[count++] = i;		// �۾� ���� 
					finish[i] = true;			// �۾� �Ϸ� ǥ�� 
					canAllot = true;			// �Ҵ� ������. 
				}
			}
		}
		
		// �Ҵ� �������� ������(= � ���μ����� ����ڿ��� ������ �� ������) 
		if (canAllot == false) {
			printf("System Is [not Safe]\n");	// �Ҿ��� ���� 
			return;
		}
	}
	
	printf("System is in [Safe] state\n");	// ���� ����  
	printf("[Safe] Sequence : ");			// ���� ���¸� ���� �ڿ��Ҵ� ���� 
	for (i=1; i<=N-1; i++) {
		printf("P[%d] -> ", sequence[i]);
	}
	printf("P[%d]\n", sequence[N]);
	printf("\n");
 }

void main()
{
	int n, m, i, j;
	
	printf("Enter Total Number of Resources : ");	// �ý��� �� ��ü�ڿ��� ��
	scanf("%d", &total);
		
	printf("Enter Number of Processes : ");		// ���μ����� ���� 
	scanf("%d", &n);
	
	printf("Enter Number of Resource Types : ");// �ڿ� ������ ���� 
	scanf("%d", &m);
	
	printf("Enter the Available Resources : ");	// ���� ���� �ڿ��� �� 
	for (i=1; i<=m; i++)
	    scanf("%d", &available[i]);
	    
	printf("Enter the Allocation Matrix : ");	// ���� �Ҵ�� �ڿ��� �� 
	for (i=1; i<=n; i++) {
		for (j=1; j<=m; j++) {
			scanf("%d", &alloc[i][j]);
		}
	}

	printf("Enter the Matrix for Maximum Demand of each Process : ");
	for (i=1; i<=n; i++) {
		for (j=1; j<=m; j++) {
			scanf("%d", &max[i][j]);	// (�� ���μ����� �����) �ִ� �ڿ��� �� 
		}
	} 
	
	// expect[] = �۾��� �Ϸ��ϱ���� �ʿ���(����) �ڿ��� �� =  max[] - alloc[] 
	// ����ڿ� = �ִ� �ڿ� - �Ҵ� �ڿ� 
	for (i=1; i<=n; i++) {
		for (j=1; j<=m; j++) {
			expect[i][j] = max[i][j] - alloc[i][j];
		}
	}
	
	// ���� �ý����� ���� ��� (�׸� 6-17, 6-18�� ����) 
	printf("\n+++++++++++++++����� �˰���+++++++++++++++\n");

	for (j=1; j<=m; j++) {
		printf("\tTotal = %d \t Available = %d\n", total, available[1]);
		printf("Process  Max \t Allocation \t Expect \n");
		for (i=1; i<=n; i++) {
			printf(" P[%d] \t %d \t %d \t\t %d \n", i, max[i][j], alloc[i][j], expect[i][j]);
		}
	}

	
	// to check safe or not
	isSafe(n, m);
	
	int indx, request[101];
	
	// �ڿ��� ��û�� ���μ��� ��ȣ�� �Է��ϼ��� :  
	printf("Enter the Process Number for Resource Request : ");
	scanf("%d", &indx);
	
	// �ν��Ͻ�(��û�� �ڿ� ��)�� �Է��ϼ��� :  
	printf("Enter the Requested Instances of each: ");
	for (i=1; i<=m; i++)
	    scanf("%d", &request[i]);
	
	
	/* 
		Resource-Request �˰��� :
		���μ����κ��� OS���� �ڿ��Ҵ� ��û�� ������,
		OS�� �ش� ���μ����� ��û�� �ڿ��� ���� �װ��� �Ҵ� �������� �Ǵ��ϰ�,
		If �Ҵ� �����ϴٸ� -> �Ҵ� ���־��ٰ� �����ϰ� -> Deadlock �߻� �˻� -> 
			if 1) Deadlock�� �߻��Ұ��̶�� �ǴܵǸ� -> �ڿ��Ҵ� X
			if 2) Deadlock�� �߻����� �ʴ´ٰ� �ǴܵǸ� -> �ڿ��Ҵ�.
	*/
	
	/*
       RESOURCE-REQUEST ALGORITHM 
       1) If Request(i) <= expect(i)
          Goto step (2) ; otherwise, raise an error condition, since the process has exceeded its maximum claim.
       2) If Request(i) <= Available Goto step (3); otherwise, Pi must wait, since the resources are not available.
       3) Have the system pretend to have allocated the requested resources to process P(i) by modifying the state as
          follows:
          Available = Available ? Request(i)
          Allocation(i) = Allocation(i) + Request(i)
          expect(i) = expect(i)? Request(i)
    */
    
    
    // Error Condition 
	for (i=1; i<=m; i++) {
		// �����ڿ� ���� ���� �ڿ��� �䱸�ϰų�, �ʿ��� �ڿ��� ���� �ʰ��ؼ� �䱸�ϸ�  
		// �ʿ��� �ڿ��� �� < ��û�� �ڿ��� �� or ��û�� �ڿ��� �� > �����ڿ��� �� �̸� 
		if ( expect[indx][i] < request[i] || request[i] > available[i] ) {
			printf("Cannot request\n");		// Error : "�ڿ� �Ҵ� �Ұ�" 
			break;
		}
	}
	
	if (i > m) {
		// �ڿ��� �Ҵ��ߴٰ� ������ �� -> Safe State �˻�. 
		for (i=1; i<=m; i++) {
			alloc[indx][i] += request[i];	// �Ҵ��ڿ� = �Ҵ��ڿ� + ��û�ڿ�  
			available[i] -= request[i];		// �����ڿ� = �����ڿ� - ��û�ڿ� 
			expect[indx][i] -= request[i];	// �ʿ��ڿ� = �ʿ��ڿ� - ��û�ڿ� 
		}
		isSafe(n, m);	// Safe State �˻� 
	}
}
