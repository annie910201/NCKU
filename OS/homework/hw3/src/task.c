#include "../include/task.h"
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include "../include/builtin.h"
#include "../include/command.h"
#include "../include/function.h"
#include "../include/shell.h"
#include "../include/resource.h"
#define STACK_SIZE 65536

void task_create(char* fun_name, char* task_name, int priority){
    Task *task = (Task*)calloc(1,sizeof(Task));
	strcpy(task->fun_name, fun_name);
    //task->fun_name = fun_name;    //task->fun_name and fun_name will point to same address
	strcpy(task->task_name, task_name);
	task->state ="READY";
	task->priority = priority;
	task->waiting_time=-1;
    task -> wait_to_runnung = 0;
    task ->resource_num = 0;
    task->resource = (int*) calloc(3,sizeof(int));

	task->runnung_time=0;
	task->next = NULL;
    task->tid = count_tid++;
    for(int i=0;i<14;i++){
		if(strcmp(task->fun_name, task_str[i])==0){
			task->func = task_func[i];
		}
	}

    //initialize context
    getcontext(&task->new_task);
    task ->new_task.uc_stack.ss_sp = malloc(STACK_SIZE);
    task ->new_task.uc_stack.ss_size = STACK_SIZE;
    task ->new_task.uc_link = NULL;
    makecontext(&task->new_task, task->func, 0);

    task ->next = NULL;

    if(head==NULL){//set head
        head = task ;
        tail = task ;
    }
    else{//moving tail
        tail->next = task ;
        tail = tail->next;
    }
    Schedule *s = (Schedule*) calloc(1,sizeof(Schedule));
    s->task = task ;
    s->wait_time =0;
    s->count_after_schedule = 0;
    s->next = NULL;
    if(s_head==NULL){
        s_head = s;
        s_tail = s;
    }
    else{
        if(alg==2){//PP need to schedule
            if(s_tail->task->priority < s->task->priority ){//priority is larger than tail => least significant
                s_tail->next = s;
                s_tail = s_tail->next;
            }
            else if(s_head->task->priority>s->task->priority){//priority is less than head =>most significant
                s->next = s_head;
                s_head = s;
            }
            else{//between head and tail
                Schedule *tmp = s_head;
                while(tmp->next!=NULL){
                    if(tmp->next->task->priority > s->task->priority){
                        s->next = tmp->next;
                        tmp->next= s; 
                        break;
                    }
                    tmp = tmp->next;
                }
            }
        }
        else{//add to tail directly
            s_tail->next = s;
            s_tail = s_tail->next;
        }
    }

}

void task_delete(char* task_name){
    count_rr++;
    Schedule *tmp = s_head;
    if(strcmp(tmp->task->task_name , task_name)==0){
        tmp->task->state = "TERMINATED";//terminated
        s_head = s_head->next;
    }
    else{
        while(tmp->next!=NULL){
            if(strcmp(tmp->next->task->task_name , task_name)==0){
                tmp->next->task->state = "TERMINATED";//terminated
                Schedule *d = tmp->next;
                tmp->next = d->next;
                if(d == s_tail)
                    s_tail = tmp;
                free(d);
                break;
            }
            tmp = tmp->next;
        }
    }
}
void task_check(){
    Schedule *s = s_head;
    while(s!=NULL){
        if(strcmp(s->task->state, "WAITING")==0){
            s->task->waiting_time++;
            if(s->task->wait_to_runnung==0){
                if(s->task->waiting_time==s->wait_time)
                    s->task->state = "READY";
                else{
                    s->wait_time++;
                    int res_ava = 0;
                    for(int i=s->count_after_schedule; i<s->task->resource_num;i++){
                        if(resource_ava[s->task->resource[i]]){
                            res_ava = 1;
                            break;
                        }
                    }
                    if(res_ava == 0)
                        s->task->state = "READY";
                }
            }
        }
        if(s->next==NULL)
            break;
        s= s->next;
    }
}
//choose next task
void task_choose(){
    task_check();
    if(alg==1){//RR
        Schedule *s = running;
        int w= 0;
        if(count_rr!=count_tid){
            while(s!=NULL){
                if(s!=s_tail)
                    s = s->next;
                else
                    s= s_head;
                if(s==running && strcmp(s->task->state,"READY")!=0){
                    w= 1;
                    break;
                }
                else if(s == running)
                    break;
            }
            if(w==1){
                printf("CPU idle\n");
                setcontext(&idle_context);
            }
            else{
                if(s!=running)
                    printf("Task %s is running.", s->task->task_name);
                running = s;
                running->task->state="RUNNING";
                setcontext(&running->task->new_task);
            }
        }
        else    
            setcontext(&initial_context);
    }
    else{//not RR
        int over = 0;
        Schedule *s = s_head;
        while (s!=NULL)
        {
            if(strcmp(s->task->state, "READY")==0)
                break;
            else{
                if(strcmp(s->task->state, "WAITING")==0)
                    over++;
            }
            if(s->next == NULL) 
                break;
            s= s->next;
        }
        if(s==s_tail && strcmp(s->task->state, "READY")!=0 && over !=0){
            printf("CPU idle\n");
            setcontext(&idle_context);
        }
        else if(s==s_tail && strcmp(s->task->state, "TERMINATED")==0 && over ==0){
            setcontext(&initial_context);
        }
        else{
            if(s!=running)
                printf("Task %s is running,\n", s->task->task_name);
                running = s;
                running->task->state = "RUNNING";
                setcontext(&running->task->new_task);
        }
        
    }
}
void task_create_idle(){
    getcontext(&idle_context);
    idle_context.uc_stack.ss_sp = malloc(STACK_SIZE);
    idle_context.uc_stack.ss_size = STACK_SIZE;
    idle_context.uc_link = NULL;

    makecontext(&idle_context, idle, 0);
    getcontext(&switch_context);
    switch_context.uc_stack.ss_sp = malloc(STACK_SIZE);
    switch_context.uc_stack.ss_size = STACK_SIZE;
    switch_context.uc_link = NULL;

    makecontext(&switch_context, task_choose, 0);
}
void task_sleep(int ms)
{
    running ->task->state = "WAITING";
    running ->task->runnung_time++;
    running ->wait_time+=ms;
    swapcontext(&running->task->new_task, &idle_context);
}

void task_exit()
{
    count_rr++;

    running->task->state = "TERMINATED";
    running->task->runnung_time++;
    printf("Task %s has terminated.\n", running->task->task_name);
    swapcontext(&running->task->new_task, &idle_context);
}
