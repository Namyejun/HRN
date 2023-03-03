#include <stdio.h>
#include <stdlib.h>

typedef struct Process {

	int p_num; //프로세스 아이디
	int arrive_t, burst_t, wait_t, tt, rt; //도착 시간, 수행 시간, 대기 시간, 반환 시간, 응답 시간
	int completed;
	float ntt; //정규 반환 시간

} Process;

struct Process *createProcess(int id, int arrive_t, int burst_t);
void updateProcessInfo(struct Process *p, int cur_time);
