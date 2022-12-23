#include "../include/resource.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/task.h"
#include <ucontext.h>
bool resource_ava[8] = {false,false,false,false,false,false,false,false }; // initial to can get
void get_resources(int count, int *resources)
{
    bool get_res = true;
    running->task->resource_num = running->count_after_schedule;
    running->task->wait_to_runnung = 0;//sleep

    for(int i=running->count_after_schedule; i<(running->count_after_schedule+count) ;i++){
        if(resource_ava[resources[i]] == true)//can't get resource
            get_res = false;
        
        running->task->resource[i] = resources[i - (running->count_after_schedule)];//update resource to running->task->resource[i]
    }
    
    if(get_res){
        printf("Task %s gets resources", running->task->task_name );
        fflush(stdout);
        for(int i=0;i<count;i++){
            printf(" %d",resources[i]);
            fflush(stdout);
            resource_ava[resources[i]] = true;//resource has been taken
        }
        printf("\n");
        fflush(stdout);

        running->task->resource_num += count;
        running->count_after_schedule = running->task->resource_num;
    }
    else{
        running->task->wait_to_runnung = 1;//not all resource is available
        running->task->runnung_time ++;//when take resource ,it also counted to run time
        running->task->resource_num += count;
        running->task->state=WAITING;
        printf("Task %s is waiting resource.\n", running->task->task_name);
        fflush(stdout);
        setcontext(&idle_context);
    }
}

void release_resources(int count, int *resources)
{
    for(int i=0;i<count;i++){
        resource_ava[resources[i]] = false;
        running->task->resource[i] = resources[i];
    }
    printf("Task %s releases resource", running->task->task_name);
    fflush(stdout);
    for(int i=0;i<count;i++){
        printf(" %d", resources[i]);
        fflush(stdout);
    }  
    printf("\n");
    fflush(stdout);
}
