/* producer consumer problem */
/* Modified by Yoo Seung Yeong, 2021.4.11 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>	// pthread support library
#include <semaphore.h>	// semaphore support library
#include <unistd.h>		// for 'sleep' function

#define N 8				// Size of Buffer

int buffer[N];			// buffer
int in = 0, out = 0;	// in : 버퍼에 삽입할 위치,  out : 버퍼에서 꺼낼 위치 
int sum = 0;			// 현재 버퍼에 있는 item의 개수 

sem_t mutex, full, empty;	// semaphores for producer consumer problem
							// mutex : 0 or 1 (used to provide mutual exclusion in critical section)
							// full : Number of filled slots
							// empty : Number of vacant slots	

/**
 *  initialize semaphore variables
 */
void initSemaphores() {

    // sem_init(semaphore variable reference, 0 to share semaphore between all threads, initial value)
	// sem_init (sem_t *sem, int pshared, unsigned value);
	// sem : 초기화 할 대상 semaphore
	// pshared : 프로세스/스레드간 semaphore 공유 여부 설정 
	// pshared == 0  -> 스레드간에 semaphore 공유 가능 / pshared == 1  ->  프로세스들간에 공유 가능 
	// initial value : 초기값 
	
    // mutex (mutual exclusion) variable
    sem_init(&mutex, 0, 1);

    // full check semaphore
    sem_init(&full, 0, 0);

    // empty check semaphore
    sem_init(&empty, 0, N);
}

/**
 *  Procuder program with semaphores
 */
void *producer() {

    // run finite length
    int i;
    for (i = 0; i < N; i++) {

        // check for full buffer
        // if buffer is full then put this process in sleep queue
        // else add a item by using mutex semaphore
        sem_wait(&empty);

        // check whether any other process is accessing buffer
        // if yes put this process to sleep
        // else add the element to the buffer
        sem_wait(&mutex);

        // produced item
        printf("Produced item is: %d\n",i);

        // add element to the buffer
        buffer[in] = i;
        in = (in + 1) % N;
        sum++;
        
        // print status
		printf("producer가 가리키는 위치: %d\t", in);
		printf("Item 개수: %d\t", sum);
		printf("빈 슬롯 개수: %d\n", N-sum);
		printf("\n");
        sleep(1);

        // free the mutex semaphore and and wake up a process in the sleep queue
        sem_post(&mutex);

        // increment the full semaphore indicating the addition of new element to the buffer is complete
        sem_post(&full);
    }
}

/**
 *  Consumer program with semaphores
 */
void *consumer() {

    int item;

    // run finite length
    int i;
    for (i = 0; i < N; i++) {

        // check for empty buffer
        // if buffer is empty then put this process to sleep
        // else remove a item by using mutex semaphore
        sem_wait(&full);

        // check whether any other process is accessing buffer
        // if yes put this process to sleep
        // else add the element to the buffer
        sem_wait(&mutex);

        // remove element from the buffer
        item = buffer[out];
        
        // consumed item
        printf("Consumed item is: %d\n", item);
        out = (out + 1) % N;
        sum--;
        
        // print status
        printf("consumer가 가리키는 위치: %d\t", out);
        printf("Item 개수: %d\t", sum);
        printf("빈 슬롯 개수: %d\n", N-sum);
        printf("\n");
        sleep(1);

        // free the mutex semaphore and and wake up a process in the sleep queue
        sem_post(&mutex);	// critical section 탈출 신호를 보낸다  

        // increment the empty semaphore indicating the removal of new element to the buffer is complete
        sem_post(&empty);	// 
    }
}

int main() {

    printf("*** Producer-Consumer *** \n");
    printf("Buffer Size: %d\n\n", N);
    
    initSemaphores();

    // declare pthread (POSIX threads) ids
    // A thread is a single sequence stream within in a process
    pthread_t produce, consume;

    // create threads
    pthread_create(&produce ,NULL, producer, NULL);
    pthread_create(&consume, NULL, consumer, NULL);

    // join thread
    pthread_join(produce, NULL);
    pthread_join(consume, NULL);

    return 0;
}
