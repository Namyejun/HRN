# HRN

## OS IC-PBL team project
### 운영체제론 전공 팀 프로젝트

프로세스 스케줄링 기법들에 대해 이해하고 각 스케즐링 기법을 구현할 수 있도록 함.

```bash
├── data
│   ├── gantt
│   │   ├── hrrn_gantt.txt : 간트 차트를 출력하기 위한 텍스트 파일
│   └── hrrn_task_data.txt : 프로세스의 시작 시간과 작업 시간을 알고 있는 텍스트 파일
│
├── hrrn_main
│   ├── Makefile : Makefile
│   └── hrrn.c : HRN 스케줄링 기법을 구현한 메인 코드
│
├── include : 헤더 파일들을 모아놓은 디렉터리
│
├── lib
│   ├── hrrn_process.c : 프로세스 구조체에 대한 코드
│   ├── hrrn_queue.c : 실직적인 동작 구성이 작성된 코드
│   └── scheduling_io.c : 텍스트의 input, output을 담당하는 코드
│
└── gantt.py : c 코드로 출력된 텍스트 결과를 시각화 하는 파이썬 코드
``` 
