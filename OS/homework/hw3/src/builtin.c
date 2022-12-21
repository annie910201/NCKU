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
	task_create(function_name,task_name,pri);

	printf("Task %s is ready.\n", args[1]);
	return 1;
}

int del(char **args)//del {task name}
{
	char *task_name = args[1];
	// struct Task* tmp = head;
	// while(tmp != NULL){
	// 	if(strcmp(task_name, tmp->task_name)==0){
	// 		tmp->state = four_state[2];//terminated
	// 		break;
	// 	}
	// 	tmp = tmp->next;
	// }
	task_delete(task_name);
	printf("Task %s is killed.\n", task_name);
	// free(tmp);
	return 1;
}

int ps(char **args)//ps //show inforamtion
{
	//print title
	printf(" TID|       name|      state| running| waiting| turnaround| resources| priority\n");
	printf("-------------------------------------------------------------------------------\n");
	//print information
	Task  *tmp = head;
	char resource[10];
	while(tmp!=NULL){
		memset(resource, '\0', 10);
		char *turnaround = "none";
		if(tmp->resource_num ==0)
			strcat(resource, "none");
		else{
			for(int i=0;i<tmp->resource_num;i++){
				char s[3];
				sprintf(s," %d", tmp->resource[i]);//int to string
				strcat(resource, s);
			}
		}
		if(strcmp(tmp->state, "TERMINATED")==0){
			int total_time = tmp->waiting_time + tmp->runnung_time;
			if(tmp->waiting_time<0)total_time++;
			char num[10];
			memset(num,'\0',10);
			sprintf(num,"%d",total_time);
			turnaround = num;
			break;
		}
		int pos_wait_time=0;
		if(tmp->waiting_time >0)
		 	pos_wait_time= tmp->waiting_time;
		printf("%4d|%11s|%11s|%8d|%8d|%11s|%10s|%9d\n", tmp->tid, tmp->task_name, tmp->state, tmp->runnung_time, pos_wait_time, turnaround, resource, tmp->priority);
		if(tmp->next == NULL)
			break;
		else
			tmp = tmp->next;
	}
	return 1;
}

int start(char **args)//Start simulation
{
	Schedule *s = s_head;
	while(s!=NULL){
		if(strcmp(s->task->state, "READY")==0){
			break;
		}
		else
			if(s->next==NULL)
				break;
			s = s->next;
	}
	//after while, s only two possible: READY state or tail(may be TERMINATED)
	if(s!=s_tail || strcmp(s->task->state,"TERMINATED")!=0){
		printf("Task %s is running.", s->task->task_name);
		running = s;
		running->task->state = "RUNNING";
		timer();
		swapcontext(&initial_context, &running->task->new_task);
	}
	return 1;
}
void signal_handler(){
	if(alg == 1 && strcmp(running->task->state, "RUNNING")){
		count_RR_timer ++;
		if(count_RR_timer == 3){
			count_RR_timer =0;
		}
		else{
			running->task->runnung_time++;
			task_check();
			return;
		}
	}
	if(strcmp(running->task->state,"RUNNING")==0){
		running ->task->runnung_time++;
		running->task->state = "READY";
	}
	if(strcmp(running->task->state, "READY")!=0){//waiting
		count_RR_timer = 0;
		setcontext(&switch_context);
	}
	else	
		swapcontext(&running->task->new_task, &switch_context);
}
void timer(){
	signal(SIGVTALRM, signal_handler);
	struct itimerval it;
	it.it_interval.tv_sec = 0;
	it.it_interval.tv_usec = 10000;//10ms
	it.it_value.tv_sec =0 ;
	it.it_value.tv_usec =100000;//10ms
	setitimer(ITIMER_VIRTUAL, &it, NULL);
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
