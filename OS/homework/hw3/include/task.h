#ifndef TASK_H
#define TASK_H
#include <ucontext.h>

//struct
typedef struct Task Task;
typedef struct Schedule Schedule;
typedef void (*task_fun)();
struct Task
{
	ucontext_t new_task;
	char task_name[20];
	char fun_name[20];
	char state[20];
	int priority;
    int wait_to_runnung;// WAITING can devide to two condition: sleep(no resource) / wait other process, if wait_to_running == 0 => sleep 
	int waiting_time;//waiting time after start simulation//程式運行時目前的waiting time
	int tid;
	int runnung_time;
	struct Task *next;
	int resource_num;
	int *resource;
	int turnaround_time;
    task_fun func;
};
struct Schedule{
	struct Task *task;
	struct Schedule *next;
    int wait_time;//the resource total need to wait time//task_sleep 完後給予的總wait time, 當wait time == waiting time代表等待結束, 進入READY
    int count_after_schedule;
};
Task *head;//point to head
Task *tail;//point to tail
Schedule *running;//point to running node
Schedule *s_head;//point to head
Schedule *s_tail;//point to tail

//function
void task_sleep(int);
void task_exit();
void task_create(char* fun_name, char* task_name, int priority);
void task_delete();
void task_create_idle();
void task_choose();
void task_check();

//ucontext variable
ucontext_t initial_context;
ucontext_t idle_context;
ucontext_t switch_context;

#endif
