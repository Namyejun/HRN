#include "hrrn_queue.h"
#include "scheduling_io.h"

int main() {

	struct Queue *hrrn_queue = (Queue*)malloc(sizeof(struct Queue)); //프로세스를 담고 있는 큐를 생성한다.
	
	int error_code = parseProcess(hrrn_queue);
	//텍스트 파일을 불러오는 데 실패하면 1을 반환하고 종료한다.
	if (error_code) {
		if (error_code == 1) {printf("Invalid input file: %s\n", INPUT_DATA_PATH);}
		else if (error_code == 2) {printf("Invalid form of contents in file: %s\n", INPUT_DATA_PATH);}
		return 1;
	}
	
	hrrn_queue = (Queue*)realloc(hrrn_queue, sizeof(struct Queue) + sizeof(char*) * hrrn_queue->max_size);	
	
	sortByArrival(hrrn_queue);

	printf("\nP#\tAT\tBT\tWT");
	printf("\tTAT\t Normalized TT \t Response Time\n");

	while (hrrn_queue->size > 0) {
		int prev_ended_time = 0; //전 프로세스의 종료시간을 저장한다.
		
		struct Process *target = updatePriority(hrrn_queue); //프로세스의 HRR 즉 우선순위를 얻는다.

		//전 프로세스와 시간간격이 없을 때
		if (target->arrive_t <= hrrn_queue->cur_time) {
			hrrn_queue->cur_time += target->burst_t; //현재 시간을 변경해준다.
			prev_ended_time = hrrn_queue->cur_time; //전 프로세스의 종료시간을 업데이트 해준다.
		}
		//전 프로세스와 시간간격이 존재할 때
		else {
			prev_ended_time = hrrn_queue->cur_time; //전 프로세스의 종료시간을 업데이트 해준다.
			hrrn_queue->cur_time = target->burst_t + target->arrive_t; //현재 시간을 변경해준다.
		}
		updateProcessInfo(target, hrrn_queue->cur_time);

		hrrn_queue->avgtt += target->tt; //각 프로세스의 반환시간을 전체 반환시간에 더해준다.
		hrrn_queue->avgwt += target->wait_t; //각 프로세스의 대기시간을 전체 대기시간에 더해준다.
		hrrn_queue->avgrt += target->rt; //각 프로세스의 응답시간을 전체 응답시간에 더해준다.
		
		printBursted(target);
		dequeue(hrrn_queue);
		parseGantt(hrrn_queue, target, prev_ended_time);
	}

	printf("\n대기시간 평균:%f\n", hrrn_queue->avgwt / hrrn_queue->max_size);
	printf("반환시간 평균:%f\n", hrrn_queue->avgtt / hrrn_queue->max_size);
	printf("반응시간 평균:%f\n", hrrn_queue->avgrt / hrrn_queue->max_size);
	printText(hrrn_queue);
	free(hrrn_queue);
	return 0;
}
