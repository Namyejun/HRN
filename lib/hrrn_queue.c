#include "hrrn_queue.h"

//프로세스들이 도착한 시간 순으로 정렬한다.
void sortByArrival(struct Queue *queue) {
	
	struct Node *node_array[queue->size];
	int size = queue->size;
	struct Node *temp;

	//큐를 초기화 시킨다.
	queue->avgtt = 0;
	queue->avgwt = 0;
	queue->hrr = -9999;
	queue->cursor = 0;

	for (int i = 0; queue->head != NULL; i++) {
		node_array[i] = queue->head;
		dequeue(queue);
	}

	for (int i = 0; i < size-1; i++) {
		for (int j = i+1; j < size; j++) {
			//도착 시간이 더 작은 프로세스를 체크한다.
			if (node_array[i]->p->arrive_t > node_array[j]->p->arrive_t) {
				
				//먼저 도착한 프로세스를 앞에 배치한다.
				temp = node_array[i];
				node_array[i] = node_array[j];
				node_array[j] = temp;
			}
		}
	}

	for (int i = 0; i < size; i++) {
		enqueue(queue, node_array[i]);
	}

	queue->cur_time = queue->head->p->arrive_t;
}

//프로세스를 큐에 넣는다.
void enqueue(struct Queue *queue, struct Node *new_node) {

	if (queue->head == NULL || queue->tail == NULL) {
		queue->head = new_node;
		queue->tail = new_node;
	}
	else {
		queue->tail->next = new_node;
		queue->tail = new_node;
	}
	
	queue->size++;
}

//큐에서 프로세스를 제거한다.
void dequeue(struct Queue *queue) {
	
	struct Node *dequeued;
	if (queue->cursor == 0) {
		if (queue->head != NULL) {
			dequeued = queue->head;
			queue->head = queue->head->next;
			if(queue->head == NULL) {
				queue->tail = NULL;		
			}
			dequeued->next = NULL;
		}
	}
	else {
		struct Node *prevNode = getNode(queue, queue->cursor-1);
		dequeued = getNode(queue, queue->cursor);
		prevNode->next = getNode(queue, queue->cursor)->next;
		if (queue->cursor == queue->size-1) {
			queue->tail = prevNode;
		}
		dequeued->next = NULL;
	}

	queue->size--;
}

//주어진 인덱스를 가진 노드를 큐에서 반환한다.
struct Node *getNode(struct Queue *queue, int cursor) {

	struct Node *cur_node = queue->head;

	for (int i = 0; i < cursor; i++) {
		if (cur_node != NULL) {
			cur_node = cur_node->next;
		}
	}

	return cur_node;

}

//커서를 가장 높은 response ratio를 가지고 있는 노드로 옮겨주고 그 프로세스를 반환한다.
struct Process *updatePriority(struct Queue *queue) {
	queue->cursor = 0;
	struct Node *cur_node = queue->head;
	queue->hrr = 0;

	float temp; //현재 커서의 response ratio
	int i = 0; //hrr을 가진 프로세서의 인덱스

	while (cur_node != NULL && queue->size > 1) {

		//프로세스가 도착한 상태이며 실행이 완료되지 않았는지 체크한다.
		if (cur_node->p->arrive_t <= queue->cur_time && cur_node->p->completed != 1) {
			temp = ((float)cur_node->p->burst_t + ((float)queue->cur_time - (float)cur_node->p->arrive_t) + 1) / (float)cur_node->p->burst_t;
			
			//temp가 hrr인지 체크한다.
			if (queue->hrr < temp) {
				queue->hrr = temp;
				queue->cursor = i;
			}
		}

		cur_node = cur_node->next;
		i++;
	}
	
	return getNode(queue, queue->cursor)->p;
}

void parseGantt(struct Queue *queue, struct Process *p, int ended_time) {
	char data_token[10] = "";
	
	sprintf(data_token, "%d ", p->p_num);

	int token_len = strlen(data_token);
	char *data_line = (char*)calloc(token_len * p->burst_t + 1, sizeof(char));

	//첫 번째 프로세스일 경우
	if (queue->size+1 == queue->max_size) {
		data_line = realloc(data_line, sizeof(char) * (token_len * (p->arrive_t + p->burst_t) + 1));
		for (int i = 0; i < p->arrive_t; i++) {
			strcat(data_line, "0 "); //첫 번째 프로세스가 도착하기 전에 도착시간을 체크하고 시간에 0을 저장한다.
		}
	}
	//전 프로세스와 시간 간격이 존재할 때
	else if (ended_time < p->arrive_t) {
		data_line = realloc(data_line, sizeof(char) * (token_len * ((p->arrive_t - ended_time) + p->burst_t) + 1));
		for (int i = 0; i < p->arrive_t - ended_time; i++) {
			strcat(data_line, "0 "); //공백인 간격에 0을 저장한다.
		}		
	}
	else {
		data_line = (char*)calloc(token_len * p->burst_t + 1, sizeof(char));
	}

	for (int i = 0; i < p->burst_t; i++) {
		strcat(data_line, data_token); //시간에 프로세스 id를 저장한다.
	}
	
	queue->data[queue->max_size - queue->size - 1] = data_line;
}
