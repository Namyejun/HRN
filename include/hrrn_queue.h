#ifndef __HRRN_QUEUE_H
#define __HRRN_QUEUE_H

#include "hrrn_process.h"
#include <string.h>

typedef struct Node {

	struct Node *next;
	struct Process *p;
} Node;

 
typedef struct Queue {

	int sum_bt;	//프로세스들의 전체 수행 시간
	int size;	//큐에 존재하는 프로세스들의 개수
	int max_size;	//전체 프로세스의 개수
	int cursor;	//현재 실행 중인 프로세스의 인덱스
	int cur_time;	//현재 시간
	float hrr;	//Highest response ratio : 우선순위 개념
	float avgwt;	//전체 대기 시간
	float avgtt;	//전체 반환 시간
	float avgrt;	//전체 응답 시간

	struct Node *head;
	struct Node *tail;

	char* data[];
} Queue;

void enqueue(struct Queue *queue, struct Node *new_node);
void dequeue(struct Queue *queue);
void sortByArrival(struct Queue *queue);
struct Node *getNode(struct Queue *queue, int cursor);
struct Process *updatePriority(struct Queue *queue);
void parseGantt(struct Queue *queue, struct Process *p, int ended_time);

#endif
