// 201614004 유승영
// 인접 리스트로 표현된 그래프에 대한 너비 우선 탐색 프로그램

#include <stdio.h>
#include <stdlib.h>

// ***원형 큐 프로그램 포함***
#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10
#define MAX_VERTICES 50

typedef int element;

// 큐 타입
typedef struct {		
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// 오류 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 큐 초기화 함수
void queue_init(QueueType* q) {
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태 입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태 입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

// ***너비우선탐색 프로그램*** (인접리스트로 표현된 그래프)
typedef struct {
	int vertex;		// 정점의 개수
	struct GraphNode* link;
} GraphNode;

typedef struct {
	int n;			// 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];		// 정점의 방문여부를 표시할 배열

// 그래프 초기화
void graph_init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if ( ((g->n) + 1) > MAX_VERTICES ) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

// 간선 삽입 연산
// (정점v를 u의 인접 리스트에 삽입)
void insert_edge(GraphType* g, int u, int v) {
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	GraphNode* node;
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void bfs_list(GraphType* g, int v) {
	GraphNode* w;
	QueueType q;
	queue_init(&q);		// 큐 초기화

	visited[v] = TRUE;	// 정점 v 방문 표시
	printf("%d 방문 -> ", v);

	enqueue(&q, v);		// 시작 정점을 큐에 저장

	while (!is_empty(&q)) {
		v = dequeue(&q);	// 큐에 저장된 정점 선택
		for (w = g->adj_list[v]; w; w = w->link)	// 인접한 정점 탐색
			if (!visited[w->vertex]) {			// 미방문 정점 탐색
				visited[w->vertex] = TRUE;			// 방문 표시
				printf("%d 방문 -> ", w->vertex);
				enqueue(&q, w->vertex);				// 정점을 큐에 삽입
			}
	}
}

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	for (int i = 0; i < 7; i++) {
		insert_vertex(g, i);
	}

	insert_edge(g, 0, 2);
	insert_edge(g, 0, 1);
	insert_edge(g, 2, 6);
	insert_edge(g, 2, 5);
	insert_edge(g, 1, 3);
	insert_edge(g, 1, 4);

	printf("너비 우선 탐색\n");
	bfs_list(g, 0);

	printf("\n");

	free(g);

	return 0;
}