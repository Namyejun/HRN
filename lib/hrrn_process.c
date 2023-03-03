#include "hrrn_process.h"

//프로세스 생성
struct Process *createProcess(int id, int arrive_t, int burst_t) {

	struct Process *new_process = malloc(sizeof(struct Process));

	new_process->p_num = id;
	new_process->arrive_t = arrive_t;
	new_process->burst_t = burst_t;
	new_process->completed = 0;

	return new_process;
}

//프로세스의 각 정보를 계산
void updateProcessInfo(struct Process *p, int cur_time) {
	
	p->wait_t = cur_time - p->arrive_t - p->burst_t; if (p->wait_t < 0) {p->wait_t = 0;}//대기 시간 계산
	p->tt = cur_time - p->arrive_t; //반환 시간 계산
	p->ntt = ((float)p->tt / p->burst_t); //정규 반환 시간 계산
	p->rt = p->wait_t; //응답 시간 계산
	p->completed = 1; //프로세스의 실행 완료 여부 변경
}
