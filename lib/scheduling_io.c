#include "scheduling_io.h"

//텍스트 파일에서 프로세스 정보를 파싱한다.
int parseProcess(struct Queue *queue) {
	printf("Opening data file from: \"%s\"...\n", INPUT_DATA_PATH);
	char *resource_path = INPUT_DATA_PATH;
    	char buffer[MAX_LINE_LENGTH];
    	FILE * fp;

	if ((fp = fopen(resource_path, "rb")) == NULL) {
		return 1;
	}

	for(int i = 0; fgets(buffer, MAX_LINE_LENGTH, fp) != NULL; i++){

		struct Node *new_node = malloc(sizeof(struct Node));
		char *temp = strtok(buffer, " ");

		if (temp == NULL || temp[0] == 10 || temp[0] == 21) {continue;}
		int p_num = atoi(temp); //프로세스 id

        	temp = strtok(NULL, " ");
		if (temp == NULL) {return 2;}
		int p_at = atoi(temp); //프로세스의 도착 시간

        	temp = strtok(NULL, " ");
		if (temp == NULL) {return 2;}
		int p_bt = atoi(temp); //프로세스의 수행 시간
		
		new_node->p = createProcess(p_num, p_at, p_bt);

		queue->sum_bt += new_node->p->burst_t; //전체 프로세스의 수행 시간에 각 프로세스의 수행 시간을 더해준다
		queue->max_size++;
		enqueue(queue, new_node);
	}

	fclose(fp);
	return 0;
}

//완료된 프로세스의 정보를 출력한다.
void printBursted(struct Process *p) {
	
	printf("%d\t%d\t", p->p_num, p->arrive_t);
	printf("%d\t%d\t", p->burst_t, p->wait_t);
	printf("%d\t%f\t%d\n", p->tt, p->ntt, p->rt);
}

void printText(struct Queue *queue) {
	char *path = malloc(sizeof(char) * (strlen(OUTPUT_DATA_DIR) + strlen(OUTPUT_DATA_NAME)) + 2);
	strcpy(path, OUTPUT_DATA_DIR);
	strcat(path, "/");
	strcat(path, OUTPUT_DATA_NAME);

	if (mkdir(OUTPUT_DATA_DIR, 0755) == -1 && errno != EEXIST) {
		printf("Can't create directory in: \"%s\"\nError detected: %s\n", OUTPUT_DATA_DIR, strerror(errno));
		return;
	}
	FILE *fp = fopen(path, "w+");
	
	if (fp == NULL) {
		printf("Can't write gantt data in directory: \"%s\"\n", path);
		return;	
	}

	for (int i = 0; i < queue->max_size; i++) {
		fputs(queue->data[i], fp);
		free(queue->data[i]);
	}

	fclose(fp);
}
