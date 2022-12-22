#include "../include/resource.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/task.h"
#include <ucontext.h>
bool resource_ava[8] = {false,false,false,false,false,false,false,false }; // initial to can get
void get_resources(int count, int *resources)
{
    // printf("false of %s\n", running->task->task_name);
    bool get_res = true;
    running->task->resource_num = running->count_after_schedule;
    running->task->wait_to_runnung = 0;//sleep

    // for(int i=0;i<8;i++){
    //     printf("===================================\n") ;
    //     printf("%d %d %d %d %d %d %d %d\n", resource_ava[0], resource_ava[1], resource_ava[2], resource_ava[3],resource_ava[4],resource_ava[5],resource_ava[6],resource_ava[7]) ;
    //     printf("===================================\n") ;
    // }
    /* find resource */
    printf("%d\n", running->count_after_schedule);
    for(int i=running->count_after_schedule; i<(running->count_after_schedule+count) ;i++){
        printf("i:%d\n", i);
        if(resource_ava[resources[i]] == true)//can't get resource
        {
            get_res = false;
            printf("false of %s\n", running->task->task_name);
        } 
        
        running->task->resource[i] = resources[i - (running->count_after_schedule)];//update resource to running->task->resource[i]
    }
    // for(int i=0;i<8;i++){
    //     printf("===================================\n") ;
    //     printf("%d %d %d %d %d %d %d %d\n", resource_ava[0], resource_ava[1], resource_ava[2], resource_ava[3],resource_ava[4],resource_ava[5],resource_ava[6],resource_ava[7]) ;
    //     printf("===================================\n") ;
    // }
    // printf("%s get_res is %d\n", running->task->task_name, get_res);
    /* check if all resource is availiable */
    if(get_res){
        printf("Task %s gets resources", running->task->task_name );
        for(int i=0;i<count;i++){
            printf(" %d",resources[i]);
            resource_ava[resources[i]] = true;//resource has been taken
        }
        printf("\n");

        running->task->resource_num += count;
        running->count_after_schedule = running->task->resource_num;
    }
    else{
        running->task->wait_to_runnung = 1;//not all resource is available
        running->task->runnung_time ++;//when take resource ,it also counted to run time
        running->task->resource_num += count;
        // strcpy(running->task->state , "WAITING");
        running->task->state=WAITING;
        printf("Task %s is waiting resource.\n", running->task->task_name);
        // printf("res_num=%d\n", running->task->resource_num);
        setcontext(&idle_context);
    }
    // for(int i=0;i<8;i++){
    //     printf("===================================\n") ;
    //     printf("%d %d %d %d %d %d %d %d\n", resource_ava[0], resource_ava[1], resource_ava[2], resource_ava[3],resource_ava[4],resource_ava[5],resource_ava[6],resource_ava[7]) ;
    //     printf("===================================\n") ;
    // }
    // printf("res_num=%d\n", running->task->resource_num);
}

void release_resources(int count, int *resources)
{
    for(int i=0;i<count;i++){
        resource_ava[resources[i]] = false;
        running->task->resource[i] = resources[i];
    }
    printf("Task %s releases resource", running->task->task_name);
    for(int i=0;i<count;i++)
        printf(" %d", resources[i]);
    
    printf("\n");
}
