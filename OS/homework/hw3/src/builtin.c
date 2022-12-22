#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <ucontext.h>
#include "../include/builtin.h"
#include "../include/command.h"
#include "../include/function.h"
#include "../include/task.h"
#include "../include/shell.h"
# define STACK_SIZE 65536
const char *task_str[] = {"task1", "task2", "task3", "task4", "task5", "task6", "task7", "task8", "task9", "test_exit", "test_sleep", "test_resource1", "test_resource2", "idle" };
const void (*task_func[])(void)={&task1, &task2, &task3, &task4, &task5, &task6, &task7, &task8, &task9, &test_exit, &test_sleep, &test_resource1, &test_resource2, &idle };


void timer();
void signal_handler();

int help(char **args)
{
	int i;
    printf("--------------------------------------------------\n");
  	printf("My Little Shell!!\n");
	printf("The following are built in:\n");
	for (i = 0; i < num_builtins(); i++) {
    	printf("%d: %s\n", i, builtin_str[i]);
  	}
	printf("%d: replay\n", i);
    printf("--------------------------------------------------\n");
	return 1;
}

int cd(char **args)
{
	if (args[1] == NULL) {
    	fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  	} else {
    	if (chdir(args[1]) != 0)
      		perror("lsh");
	}
	return 1;
}

int echo(char **args)
{
	bool newline = true;
	for (int i = 1; args[i]; ++i) {
		if (i == 1 && strcmp(args[i], "-n") == 0) {
			newline = false;
			continue;
		}
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
	}
	if (newline)
		printf("\n");

	return 1;
}

int exit_shell(char **args)
{
	// printf("over\n");
	return 0;
}

int record(char **args)
{
	if (history_count < MAX_RECORD_NUM) {
		for (int i = 0; i < history_count; ++i)
			printf("%2d: %s\n", i + 1, history[i]);
	} else {
		for (int i = history_count % MAX_RECORD_NUM; i < history_count % MAX_RECORD_NUM + MAX_RECORD_NUM; ++i)
			printf("%2d: %s\n", i - history_count % MAX_RECORD_NUM + 1, history[i % MAX_RECORD_NUM]);
	}
	return 1;
}

bool isnum(char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
    	if(str[i] >= 48 && str[i] <= 57)
			continue;
        else
		    return false;
  	}
  	return true;
}

int mypid(char **args)
{
	char fname[BUF_SIZE];
	char buffer[BUF_SIZE];
	if(strcmp(args[1], "-i") == 0) {

	    pid_t pid = getpid();
	    printf("%d\n", pid);
	
	} else if (strcmp(args[1], "-p") == 0) {
	
		if (args[2] == NULL) {
      		printf("mypid -p: too few argument\n");
      		return 1;
    	}

    	sprintf(fname, "/proc/%s/stat", args[2]);
    	int fd = open(fname, O_RDONLY);
    	if(fd == -1) {
      		printf("mypid -p: process id not exist\n");
     		return 1;
    	}

    	read(fd, buffer, BUF_SIZE);
	    strtok(buffer, " ");
    	strtok(NULL, " ");
	    strtok(NULL, " ");
    	char *s_ppid = strtok(NULL, " ");
	    int ppid = strtol(s_ppid, NULL, 10);
    	printf("%d\n", ppid);
	    
		close(fd);

  	} else if (strcmp(args[1], "-c") == 0) {

		if (args[2] == NULL) {
      		printf("mypid -c: too few argument\n");
      		return 1;
    	}

    	DIR *dirp;
    	if ((dirp = opendir("/proc/")) == NULL){
      		printf("open directory error!\n");
      		return 1;
    	}

    	struct dirent *direntp;
    	while ((direntp = readdir(dirp)) != NULL) {
      		if (!isnum(direntp->d_name)) {
        		continue;
      		} else {
        		sprintf(fname, "/proc/%s/stat", direntp->d_name);
		        int fd = open(fname, O_RDONLY);
        		if (fd == -1) {
          			printf("mypid -p: process id not exist\n");
          			return 1;
        		}

        		read(fd, buffer, BUF_SIZE);
        		strtok(buffer, " ");
        		strtok(NULL, " ");
        		strtok(NULL, " ");
		        char *s_ppid = strtok(NULL, " ");
		        if(strcmp(s_ppid, args[2]) == 0)
		            printf("%s\n", direntp->d_name);

        		close(fd);
     		}
	   	}
    	
		closedir(dirp);
	
	} else {
    	printf("wrong type! Please type again!\n");
  	}
	
	return 1;
}

int add(char **args)//add {task name} {function name} {priority}
{
	int pri = atoi(args[3]);
	char* function_name = args[2];
	char* task_name = args[1];
	// printf("This is bad!");
	task_create(function_name,task_name,pri);
	// fflush(stdout);
	printf("Task %s is ready.\n", args[1]);
	// fflush(stdout);
	return 1;
}

int del(char **args)//del {task name}
{
	char *task_name = args[1];
	Task *tmp = head;
	while(tmp!=NULL){
		if(strcmp(tmp->task_name, task_name)==0){
			// strcpy(tmp->state, "TERMINATED");
			tmp->state=TERMINATED;
			break;
		}
		tmp = tmp->next;
	}
	task_delete(task_name);
	printf("Task %s is killed.\n", task_name);
	return 1;
}

int ps(char **args)//ps //show inforamtion
{
	//variable
	char print_resource[10];//get resource from resource.c and print it
	//print title
	printf(" TID|       name|      state| running| waiting| turnaround| resources| priority\n");
	printf("-------------------------------------------------------------------------------\n");
	//use tmp pointer to point to the node want to print
	Task  *tmp = head;
	while(tmp!=NULL){
		/*deal resource*/
		memset(print_resource, '\0', 10);//initialize
		if(tmp->resource_num ==0)	//no resource
			strcat(print_resource, "none");
		else						//have resource
		{
			for(int i=0;i<tmp->resource_num;i++){
				char s[3];
				sprintf(s," %d", tmp->resource[i]);//int to string //sprintf(string,tostring, int)
				strcat(print_resource, s);
			}
		}

		/* deal waiting time */
		int pos_wait_time=0;//time need to be positive
		if(tmp->waiting_time >= 0)
		 	pos_wait_time= tmp->waiting_time;

		/*deal turnaround*/
		char *turnaround = "none";//turnaround = total time = waiting time + running time, 
		if(tmp->state==TERMINATED){//if state = TERMINATED, have turnaround
			int total_time = tmp->waiting_time + tmp->runnung_time;
			if(tmp->waiting_time<0)//initial is -1 //represent context don't have to wait
				total_time++;// offset the -1
			char char_time[10];
			memset(char_time,'\0',10);
			sprintf(char_time, "%d" , total_time);
			turnaround = char_time;
			// break;
		}

		/* deal state string */
		char* state_char;
		if(tmp->state== WAITING)
			state_char = "WAITING";
		else if(tmp->state== READY)
			state_char = "READY";
		else if(tmp->state== TERMINATED)
			state_char = "TERMINATED";
		else if(tmp->state== RUNNING)
			state_char = "RUNNING";

		/* print */
		printf("%4d|%11s|%11s|%8d|%8d|%11s|%10s|%9d\n", tmp->tid, tmp->task_name, state_char, tmp->runnung_time, pos_wait_time, turnaround, print_resource, tmp->priority);
		
		/* moving pointer */
		if(tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	return 1;
}

int start(char **args)//Start simulation
{
	// stop = 0;
	Schedule *s = s_head;

	/* find READY state context */
	while(s!=NULL){
		if(s->task->state==READY)
			break;
		else{
			if(s->next!=NULL)
				s = s->next;
			else
				break;	
		}
	}
	//after while, s only two possible: READY state or tail(may be TERMINATED)
	if(s!=s_tail || s->task->state!=TERMINATED){//avoid s is tail and state is TERMINATED
		printf("Task %s is running.\n", s->task->task_name);
		running = s;
		// strcpy(running->task->state , "RUNNING");
		running->task->state=RUNNING;
		task_create_idle();
		timer();
		swapcontext(&initial_context, &running->task->new_task);//change to running context and store current context in initial_context, will change back in the end
	}
	printf("Simulation over\n");
	return 1;
}
void signal_handler(){

	/* if algorithm is RR and running context is in RUNNING state */
	if(alg == 1 && running->task->state==RUNNING){
		count_RR_timer ++;
		// printf("%d\n", count_RR_timer);
		if(count_RR_timer == 3){ //change every 30ms
			count_RR_timer =0;
		}
		else{
			running->task->runnung_time++;
			task_check();//check other process, and moving them
			return;
		}
	}

	/* if running context is in RUNNING state, change to READY, and choose next context later */
	if(running->task->state==RUNNING){
		// printf("Go to ready queue\n");
		running->task->runnung_time++;
		// strcpy(running->task->state , "READY"); 
		running->task->state=READY;
	}
	
	if(running->task->state!=READY){//if running context is in WAITING state 
		count_RR_timer = 0;
		setcontext(&switch_context);
	}
	else//if running context is in READY state, save current context to running, and jump to switch_context
		swapcontext(&running->task->new_task, &switch_context);
}
void ctrl_z(){
	// stop = 1;
	setcontext(&initial_context);
}
void timer(){
	signal(SIGVTALRM, signal_handler);
	signal(SIGTSTP,ctrl_z);
	signal(SIGCONT, ctrl_z);
	struct itimerval it1,it2;
	it1.it_interval.tv_sec = 0;
	it1.it_interval.tv_usec = 10000;//10ms
	it1.it_value.tv_sec =0 ;
	it1.it_value.tv_usec =100000;//10ms
	if(setitimer(ITIMER_VIRTUAL, &it1, &it2)!=0){//successful -> 0, not success->-1
		perror("timer is error");
	}
	//ITIMER_VIRTUAL-> only decrement when process running
	//ITIMER_REAL -> decrement always
}

const char *builtin_str[] = {
 	"help",
 	"cd",
	"echo",
 	"exit",
 	"record",
	"mypid",
	"add",
	"del",
	"ps",
	"start"
};

const int (*builtin_func[]) (char **) = {
	&help,
	&cd,
	&echo,
	&exit_shell,
  	&record,
	&mypid,
	&add,
	&del,
	&ps,
	&start
};

int num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}
