/* 페이지 교체 알고리즘 
*  2021. 5. 19 유승영 
*/ 

#include<bits/stdc++.h>
using namespace std;

int i, j, k, pos = 0;
int pgFault = 0; 	// 페이지 부재 발생 횟수 
char memory[10] = {'\0'};	// 메모리(프레임). 초기값 = NULL 

/* 그림 9-9 공통으로 사용할 메모리 접근 패턴 */
int nf;				// 물리 메모리의 프레임 크기(3)   
int n;				// 요구 페이지 개수(10) 
char reqPages[20];	// 각 요구 페이지 이름 (ABCD...)

void getInfo()	// 사용자로부터 초기 정보 입력받음 
{
	printf("Enter Number of Frames : ");
    scanf("%d", &nf);
    
    printf("Enter Total Number of Page Requests : ");
    scanf("%d", &n);
    
    // 각 요구 페이지 이름 입력받기 (n개) 
    printf("Enter Reference String : ");
    scanf("%s", reqPages);
    printf("\n");
}

// 메모리(큐)에 요구한 페이지가 있는지 확인 
bool isPresent(char memory[], int nf, char page)
{
	for(int i=0; i<nf; i++)
		if(page == memory[i])
			return true;	// Success
	return false;	// Fail (Page Fault)
}

// 메모리(큐) 상태 출력 
void printTable(char memory[], int nf)
{
	for(int i=0; i<nf; i++)
	{
		if(memory[i] == '\0')
			printf("  ");
		else
			printf("%c ", memory[i]);
	}
	printf("|| ");
}

int findpos(char memory[], int nf, char reqPages[], int curr, int np)
{
	// 메모리에 빈 공간이 있으면 바로 위치 반환 
	for(int i=0; i<nf; i++)
		if(memory[i] == '\0')
			return i;

	int pos[nf] = {0};
	for(int i=0; i<nf; i++)	//  i = {0,1,2} 
	{
		pos[i] = -1e9;	// -1 x 10^9 (매우 작은 값 표현)
		for(int j=curr-1; j>=0; j--) 
			if(reqPages[j] == memory[i]) // 요구페이지가 메모리 i번에 있으면.. 
			{
				pos[i] = j;
				break;
			}
	}

	int min1 = 1000000, returnPos = -1;
	for(int i=0; i<nf; i++)
		if(min1 > pos[i])
		{
			min1 = pos[i];
			returnPos = i;
		}

	return returnPos;
}

int getHitIndex(char reqPage)
{
	int idx;
	for (int k=0; k<nf; k++) {
		if (memory[k] == reqPage) {
			idx = k;
			break;
		}
	}
	return idx;
}

// 페이지 부재 횟수 출력 
void printPGfault() {
	printf("\nTotal Number of Page Faults : %d\n", pgFault);
    printf("----------------------------------------------------------\n\n"); 
}

// 초기화 & 기타 출력 (교재와 같이 표현하기 위함) 
void init() {
	
	pgFault = 0; 	// 페이지 부재 발생 횟수 초기화 
	
	pos = 0;
	
	for (i=0; i<nf; i++) {	// 메모리(페이지) 초기화 
		memory[i] = '\0';
	}
	
	printf("====Position of Frame table after each Request====\n\n");
    
    // 요구 페이지 순서(번호) 출력 
	for (i=0; i<n; i++) printf("%d\t", i+1);
	printf("\n\n");
	
	// 요구 페이지 출력    
    for (i=0; i<n; i++) printf("%c\t", reqPages[i]);
    printf("\n\n"); 
}

void FIFO()
{
    init();
	int nElements = 0;	// 큐의 원소의 개수 
   	
    for (i=0; i<n; i++)
    {
        printf("Page table after Request from %c || ", reqPages[i]);
        
        // 메모리(큐)에 요구한 페이지가 없으면.. (Fage Fault) 
        if ( !isPresent(memory, nf, reqPages[i]) )
        {       	
        	if ( nElements == nf )	// 큐가 꽉찼으면..
			{
				// 가장 오래된 페이지를 삭제하고 (스왑영역으로 옮김)
				// 나머지 원소를 앞으로 한 칸씩 밀어줌
				for (k=0; k<nf-1; k++) {
					memory[k] = memory[k+1];
				}
				memory[k] = reqPages[i]; // 큐의 맨 뒤에 요구 페이지 삽입 
			}
			else {	// 큐가 비어있으면.. 
				memory[pos] = reqPages[i];	// 빈 공간에 요구한 페이지 삽입.
				nElements++;	// 큐 원소의 개수 카운팅 
				pos = (pos+1)%nf;	// 다음 번 삽입 위치 조정 (큐) : {0,1,2}
			}
			printTable(memory, nf);	// 큐 출력 
			printf("Page Fault!\n");
			pgFault++;	// 페이지 부재 횟수 카운팅 
			continue;	// 이하 실행하지 않고 다음 요구페이지로 넘어감 
        }
		// 메모리(큐)에 요구한 페이지가 있으면.. 
        printTable(memory, nf);
		printf("\n");
    }
	printPGfault();
}

// Optimal 알고리즘에서 사용 
int findpos2(char memory[], int nf, char reqPages[], int curr, int np)
{
	int i, j;
	// 메모리에 빈 공간이 있으면 바로 위치 반환 
    for (i=0; i<nf; i++)
    {
        if (memory[i] == '\0')
            return i;
    }
    int pos[nf] = {0};
    for(i=0; i<nf; i++)
    {
        pos[i] = 1e9;	// 1 x 10^9 (무한대 값 비슷하게 표현) 
        
        // 미래의 요구 페이지 중에서.. 
        for(j=curr+1; j<np; j++)
        {
        	// 현재 메모리에 있으면 
            if(reqPages[j] == memory[i])
            {
                pos[i] = j;
                break;
            }
        }
    }
    int max1 = -1;
    int returnpos = -1;
    for(i=0; i<nf; i++)
    {
        if(pos[i] > max1)
        {
            max1 = pos[i];
            returnpos = i;
        }
    }
    return returnpos;
}

void Optimal()
{ 
    init();
    
    for(i=0; i<n; i++)
    {
        printf("Page table after Request from %c || ", reqPages[i]);
        
        // 요구한 페이지가 없으면..
        if( !isPresent(memory, nf, reqPages[i]) )
        {
			// 앞으로 가장 오랫동안 사용하지 않을 페이지를 스왑영역으로.. 
			pos = findpos2(memory, nf, reqPages, i, n);
			memory[pos] = reqPages[i];
  
        	printTable(memory, nf);
        	printf("Page Fault!\n");
        	pgFault++;
        	continue;
        }
        
        // 요구한 페이지가 있으면..
		printTable(memory, nf);
		printf("\n");
	}
	printPGfault();
}

void LRU()
{
	init();
	
 	for(i=0; i<n; i++)
    {
        printf("Page table after Request from %c || ", reqPages[i]);
        if( !isPresent(memory, nf, reqPages[i]) )
        {
            int pos = findpos(memory, nf, reqPages, i, n);
            memory[pos] = reqPages[i];

            printTable(memory, nf);
            printf("Page Fault!\n");
            pgFault++;
            continue;
        }
        printTable(memory, nf);
		printf("\n");
    }
	printPGfault();
}

void Second_Chance()
{ 
    init();
	int nElements = 0;	// 큐의 원소의 개수 
	
	for(i=0; i<n; i++)
	{
		printf("Page table after Request from %c || ", reqPages[i]);

		// 메모리(큐)에 요구한 페이지가 없으면..  (Fage Fault)
        if ( !isPresent(memory, nf, reqPages[i]) )
        {       	
        	if ( nElements == nf )	// 큐가 꽉찼으면..
			{
				// 가장 오래된 페이지를 삭제하고 (스왑영역으로 옮김)
				// 나머지 원소를 앞으로 한 칸씩 밀어줌
				for (k=0; k<nf-1; k++) {
					memory[k] = memory[k+1];
				}
				memory[k] = reqPages[i]; // 큐의 맨 뒤에 요구 페이지 삽입 
			}
			else {
				memory[pos] = reqPages[i];	// 요구한 페이지 삽입.
				nElements++;	// 큐 원소의 개수 카운팅 
				pos = (pos+1)%nf;	// 다음 번 삽입 위치 조정 {0,1,2}
			}
			
			printTable(memory, nf); 
			printf("Page Fault!\n");
			pgFault++;	// 페이지 부재 횟수 카운팅 
			continue;	// 이하 실행하지 않고 다음 요구페이지로 넘어감 
        }
        
        // 메모리에 요구한 페이지가 있으면.. (Success)
		// 해당(성공한) 페이지를 큐의 맨 뒤로 옮김 (기회를 1번 더 주는것)
		// 큐의 중간에 있는 값은 뒤로 이동 
        else 
        {
			int hitIdx = getHitIndex(reqPages[i]);	// 메모리의 어떤 위치에 있는지 알아내서 
        	for (k = hitIdx; k<nf-1; k++) {	// 큐의 중간에 있는 값을 뒤로 이동하고 
				memory[k] = memory[k+1];
			}
			memory[k] = reqPages[i];		// 성공한 페이지는 큐의 맨 뒤로 옮김 
 
        }
        
		printTable(memory, nf);
		printf("\n");
    }
	printPGfault();
}

int main() {
	
	printf("====Page Replacement Algorithm====\n");
	getInfo(); 
	
	int select;
	while(1)
	{
	    printf("===SELECT Algorithm===\n");
		printf("1. FIFO\n2. Optimal\n3. LRU\n4. Second Chance\n5. Exit\n");
		printf("======================\n");
		printf("Choose : ");
		scanf("%d", &select);
		printf("\n");
		switch(select) {
			case 1 : FIFO(); break;
			case 2 : Optimal(); break;
			case 3 : LRU(); break;
			case 4 : Second_Chance(); break;
			case 5 : return 0;
			default : printf("Invaild Input. Please Try again.\n\n"); break;
		}
	}
}

