/*
   Banker's Algorithm
*/

#include <stdio.h>
#include <stdbool.h>	// to use 'bool', 'true', 'false'
#include <stdlib.h>

// 기대자원, 현재 할당된자원의 수, 최대 자원의 수, 현재 가용자원의 수, 전체 자원의 수 
int expect[101][101], alloc[101][101], max[101][101], available[101], total;
bool finish[101];	// 각 프로세스의 작업완료 여부 
int sequence[101];	// 프로세스 작업 순서 

/*
  Safety Algorithm:
  1) Let Work and Finish be vectors of length ‘m’ and ‘n’ respectively.
     Initialize: Work = Available
     Finish[i] = false; for i=1, 2, 3, 4….n
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
	int work[101];		// 현재 해당 자원(타입)의 가용자원 수 
	
	for (i=1; i<=M; i++)	
		work[i] = available[i]; 
	
	for (i=1; i<=100; i++)
		finish[i] = false; 
	
	while (count <= N) {
		bool canAllot = false;	// 자원할당 가능 여부 
		
		for (i=1; i<=N; i++) {
			if (finish[i] == false) {			// 작업이 완료되지 않았으면 
				for (j=1; j<=M; j++) {
					if(work[j] < expect[i][j]) {	// 현재 가용자원 < 기대자원 
						break;					// 할당할 수 없음. 
					}
				}
				if (j > M) {					// 현재 가용자원 >= 기대자원 
					for (j=1; j<=M; j++) {		// 자원 할당(가정) 
						work[j] += alloc[i][j];	// 할당했던 자원 반환됨 
					}
					sequence[count++] = i;		// 작업 순서 
					finish[i] = true;			// 작업 완료 표시 
					canAllot = true;			// 할당 가능함. 
				}
			}
		}
		
		// 할당 가능하지 않으면(= 어떤 프로세스의 기대자원도 충족할 수 없으면) 
		if (canAllot == false) {
			printf("System Is [not Safe]\n");	// 불안정 상태 
			return;
		}
	}
	
	printf("System is in [Safe] state\n");	// 안정 상태  
	printf("[Safe] Sequence : ");			// 안정 상태를 위한 자원할당 순서 
	for (i=1; i<=N-1; i++) {
		printf("P[%d] -> ", sequence[i]);
	}
	printf("P[%d]\n", sequence[N]);
	printf("\n");
 }

void main()
{
	int n, m, i, j;
	
	printf("Enter Total Number of Resources : ");	// 시스템 내 전체자원의 수
	scanf("%d", &total);
		
	printf("Enter Number of Processes : ");		// 프로세스의 개수 
	scanf("%d", &n);
	
	printf("Enter Number of Resource Types : ");// 자원 종류의 개수 
	scanf("%d", &m);
	
	printf("Enter the Available Resources : ");	// 현재 가용 자원의 수 
	for (i=1; i<=m; i++)
	    scanf("%d", &available[i]);
	    
	printf("Enter the Allocation Matrix : ");	// 현재 할당된 자원의 수 
	for (i=1; i<=n; i++) {
		for (j=1; j<=m; j++) {
			scanf("%d", &alloc[i][j]);
		}
	}

	printf("Enter the Matrix for Maximum Demand of each Process : ");
	for (i=1; i<=n; i++) {
		for (j=1; j<=m; j++) {
			scanf("%d", &max[i][j]);	// (각 프로세스가 사용할) 최대 자원의 수 
		}
	} 
	
	// expect[] = 작업을 완료하기까지 필요한(남은) 자원의 수 =  max[] - alloc[] 
	// 기대자원 = 최대 자원 - 할당 자원 
	for (i=1; i<=n; i++) {
		for (j=1; j<=m; j++) {
			expect[i][j] = max[i][j] - alloc[i][j];
		}
	}
	
	// 현재 시스템의 상태 출력 (그림 6-17, 6-18과 같이) 
	printf("\n+++++++++++++++은행원 알고리즘+++++++++++++++\n");

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
	
	// 자원을 요청한 프로세스 번호를 입력하세요 :  
	printf("Enter the Process Number for Resource Request : ");
	scanf("%d", &indx);
	
	// 인스턴스(요청한 자원 수)를 입력하세요 :  
	printf("Enter the Requested Instances of each: ");
	for (i=1; i<=m; i++)
	    scanf("%d", &request[i]);
	
	
	/* 
		Resource-Request 알고리즘 :
		프로세스로부터 OS에게 자원할당 요청이 들어오면,
		OS는 해당 프로세스가 요청한 자원에 대해 그것이 할당 가능한지 판단하고,
		If 할당 가능하다면 -> 할당 해주었다고 가정하고 -> Deadlock 발생 검사 -> 
			if 1) Deadlock이 발생할것이라고 판단되면 -> 자원할당 X
			if 2) Deadlock이 발생하지 않는다고 판단되면 -> 자원할당.
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
		// 가용자원 보다 많은 자원을 요구하거나, 필요한 자원의 수를 초과해서 요구하면  
		// 필요한 자원의 양 < 요청한 자원의 양 or 요청한 자원의 양 > 가용자원의 수 이면 
		if ( expect[indx][i] < request[i] || request[i] > available[i] ) {
			printf("Cannot request\n");		// Error : "자원 할당 불가" 
			break;
		}
	}
	
	if (i > m) {
		// 자원을 할당했다고 가정한 뒤 -> Safe State 검사. 
		for (i=1; i<=m; i++) {
			alloc[indx][i] += request[i];	// 할당자원 = 할당자원 + 요청자원  
			available[i] -= request[i];		// 가용자원 = 가용자원 - 요청자원 
			expect[indx][i] -= request[i];	// 필요자원 = 필요자원 - 요청자원 
		}
		isSafe(n, m);	// Safe State 검사 
	}
}
