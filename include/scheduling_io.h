#ifndef __SCHEDULING_IO_H
#define __SCHEDULING_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "hrrn_queue.h"

#define MAX_CNT 5
#define MAX_LINE_LENGTH 20
#define INPUT_DATA_PATH "./data/hrrn_task_data.txt" //프로세스 정보를 포함한 텍스트 파일의 위치
#define OUTPUT_DATA_DIR "./data/gantt"
#define OUTPUT_DATA_NAME "hrrn_gantt.txt"

int parseProcess(struct Queue *queue);
void printBursted(struct Process *p);
void printText(struct Queue *queue);

#endif


