/* ������ ��ü �˰��� 
*  2021. 5. 19 ���¿� 
*/ 

#include<bits/stdc++.h>
using namespace std;

int i, j, k, pos = 0;
int pgFault = 0; 	// ������ ���� �߻� Ƚ�� 
char memory[10] = {'\0'};	// �޸�(������). �ʱⰪ = NULL 

/* �׸� 9-9 �������� ����� �޸� ���� ���� */
int nf;				// ���� �޸��� ������ ũ��(3)   
int n;				// �䱸 ������ ����(10) 
char reqPages[20];	// �� �䱸 ������ �̸� (ABCD...)

void getInfo()	// ����ڷκ��� �ʱ� ���� �Է¹��� 
{
	printf("Enter Number of Frames : ");
    scanf("%d", &nf);
    
    printf("Enter Total Number of Page Requests : ");
    scanf("%d", &n);
    
    // �� �䱸 ������ �̸� �Է¹ޱ� (n��) 
    printf("Enter Reference String : ");
    scanf("%s", reqPages);
    printf("\n");
}

// �޸�(ť)�� �䱸�� �������� �ִ��� Ȯ�� 
bool isPresent(char memory[], int nf, char page)
{
	for(int i=0; i<nf; i++)
		if(page == memory[i])
			return true;	// Success
	return false;	// Fail (Page Fault)
}

// �޸�(ť) ���� ��� 
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
	// �޸𸮿� �� ������ ������ �ٷ� ��ġ ��ȯ 
	for(int i=0; i<nf; i++)
		if(memory[i] == '\0')
			return i;

	int pos[nf] = {0};
	for(int i=0; i<nf; i++)	//  i = {0,1,2} 
	{
		pos[i] = -1e9;	// -1 x 10^9 (�ſ� ���� �� ǥ��)
		for(int j=curr-1; j>=0; j--) 
			if(reqPages[j] == memory[i]) // �䱸�������� �޸� i���� ������.. 
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

// ������ ���� Ƚ�� ��� 
void printPGfault() {
	printf("\nTotal Number of Page Faults : %d\n", pgFault);
    printf("----------------------------------------------------------\n\n"); 
}

// �ʱ�ȭ & ��Ÿ ��� (����� ���� ǥ���ϱ� ����) 
void init() {
	
	pgFault = 0; 	// ������ ���� �߻� Ƚ�� �ʱ�ȭ 
	
	pos = 0;
	
	for (i=0; i<nf; i++) {	// �޸�(������) �ʱ�ȭ 
		memory[i] = '\0';
	}
	
	printf("====Position of Frame table after each Request====\n\n");
    
    // �䱸 ������ ����(��ȣ) ��� 
	for (i=0; i<n; i++) printf("%d\t", i+1);
	printf("\n\n");
	
	// �䱸 ������ ���    
    for (i=0; i<n; i++) printf("%c\t", reqPages[i]);
    printf("\n\n"); 
}

void FIFO()
{
    init();
	int nElements = 0;	// ť�� ������ ���� 
   	
    for (i=0; i<n; i++)
    {
        printf("Page table after Request from %c || ", reqPages[i]);
        
        // �޸�(ť)�� �䱸�� �������� ������.. (Fage Fault) 
        if ( !isPresent(memory, nf, reqPages[i]) )
        {       	
        	if ( nElements == nf )	// ť�� ��á����..
			{
				// ���� ������ �������� �����ϰ� (���ҿ������� �ű�)
				// ������ ���Ҹ� ������ �� ĭ�� �о���
				for (k=0; k<nf-1; k++) {
					memory[k] = memory[k+1];
				}
				memory[k] = reqPages[i]; // ť�� �� �ڿ� �䱸 ������ ���� 
			}
			else {	// ť�� ���������.. 
				memory[pos] = reqPages[i];	// �� ������ �䱸�� ������ ����.
				nElements++;	// ť ������ ���� ī���� 
				pos = (pos+1)%nf;	// ���� �� ���� ��ġ ���� (ť) : {0,1,2}
			}
			printTable(memory, nf);	// ť ��� 
			printf("Page Fault!\n");
			pgFault++;	// ������ ���� Ƚ�� ī���� 
			continue;	// ���� �������� �ʰ� ���� �䱸�������� �Ѿ 
        }
		// �޸�(ť)�� �䱸�� �������� ������.. 
        printTable(memory, nf);
		printf("\n");
    }
	printPGfault();
}

// Optimal �˰��򿡼� ��� 
int findpos2(char memory[], int nf, char reqPages[], int curr, int np)
{
	int i, j;
	// �޸𸮿� �� ������ ������ �ٷ� ��ġ ��ȯ 
    for (i=0; i<nf; i++)
    {
        if (memory[i] == '\0')
            return i;
    }
    int pos[nf] = {0};
    for(i=0; i<nf; i++)
    {
        pos[i] = 1e9;	// 1 x 10^9 (���Ѵ� �� ����ϰ� ǥ��) 
        
        // �̷��� �䱸 ������ �߿���.. 
        for(j=curr+1; j<np; j++)
        {
        	// ���� �޸𸮿� ������ 
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
        
        // �䱸�� �������� ������..
        if( !isPresent(memory, nf, reqPages[i]) )
        {
			// ������ ���� �������� ������� ���� �������� ���ҿ�������.. 
			pos = findpos2(memory, nf, reqPages, i, n);
			memory[pos] = reqPages[i];
  
        	printTable(memory, nf);
        	printf("Page Fault!\n");
        	pgFault++;
        	continue;
        }
        
        // �䱸�� �������� ������..
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
	int nElements = 0;	// ť�� ������ ���� 
	
	for(i=0; i<n; i++)
	{
		printf("Page table after Request from %c || ", reqPages[i]);

		// �޸�(ť)�� �䱸�� �������� ������..  (Fage Fault)
        if ( !isPresent(memory, nf, reqPages[i]) )
        {       	
        	if ( nElements == nf )	// ť�� ��á����..
			{
				// ���� ������ �������� �����ϰ� (���ҿ������� �ű�)
				// ������ ���Ҹ� ������ �� ĭ�� �о���
				for (k=0; k<nf-1; k++) {
					memory[k] = memory[k+1];
				}
				memory[k] = reqPages[i]; // ť�� �� �ڿ� �䱸 ������ ���� 
			}
			else {
				memory[pos] = reqPages[i];	// �䱸�� ������ ����.
				nElements++;	// ť ������ ���� ī���� 
				pos = (pos+1)%nf;	// ���� �� ���� ��ġ ���� {0,1,2}
			}
			
			printTable(memory, nf); 
			printf("Page Fault!\n");
			pgFault++;	// ������ ���� Ƚ�� ī���� 
			continue;	// ���� �������� �ʰ� ���� �䱸�������� �Ѿ 
        }
        
        // �޸𸮿� �䱸�� �������� ������.. (Success)
		// �ش�(������) �������� ť�� �� �ڷ� �ű� (��ȸ�� 1�� �� �ִ°�)
		// ť�� �߰��� �ִ� ���� �ڷ� �̵� 
        else 
        {
			int hitIdx = getHitIndex(reqPages[i]);	// �޸��� � ��ġ�� �ִ��� �˾Ƴ��� 
        	for (k = hitIdx; k<nf-1; k++) {	// ť�� �߰��� �ִ� ���� �ڷ� �̵��ϰ� 
				memory[k] = memory[k+1];
			}
			memory[k] = reqPages[i];		// ������ �������� ť�� �� �ڷ� �ű� 
 
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

