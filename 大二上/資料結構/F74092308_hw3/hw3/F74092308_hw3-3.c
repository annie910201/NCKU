#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/* define some global variables */
int adj[100][100]={0};//input matric
bool visited[100]={false};//record the vertex if is visited
int output[100][100];//use a matric to record the result
int col=0;//the output column
int queue[100];//put the vertex by bfs

/* use dfs to find the vertex by breathe search */
void bfs(int start,int row,int len){   
    /* define some local variables */ 
    int rear=0, front=0;//represent the queue's front and end location               
    int now=0;//record that what location we take fwom the queue now

    /*put the start_index into queue and record it's visited */
    visited[start]=true;
    queue[rear++]=start;

    /* take out number from the queue and add something to it */
    while(front<=rear){
        
        /* put the queue's front to output */
        output[row][col]=queue[front++];
        col++;
        
        /* check the vertex if it still have children */
        for(int i=0;i<len;i++){
            
            if(visited[i]==false&&adj[start][i]==1){//the edge between the vertex take from the queue and other vertex exists and still not go to the other vertex 
                queue[rear++]=i;//put it into queue
                visited[i]=true;
            }
        }
        start=queue[++now];//next time we find the "start" branch
    }
}

/* reset some variables to use again */
void reset(int len){
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++){
            adj[i][j]=0;//input matric
        }
        visited[i]=false;//let all vertices to be not visited
        queue[i]=-1;
    }
}

int main(void){
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            output[i][j]=-1;//initialize the output matric to be -1
        }
        queue[i]=-1;
    }

    /*define some local variables */
    int round=0;//the first line to give the number of testcases
    int max_len=0;//in order not to check the output matric from 0 to 100, use max_len to record the longest testcase
    int len=0;
    int start_index=0;//start from what vertex
    char filename[20];//input file name
    char createfile[20];//output file name
    FILE *fp;
    char line[5];

    printf("please input the filemame : ");//get file name
    scanf("%s",&filename);
    if(fp=fopen(filename,"r")){
        fscanf(fp,"%d",&round);
        fscanf(fp,"%c",&line);
        for(int i=0;i<round;i++){
            if(len!=0)//if not the first testcase, we need to reset 
                reset(len);
            fscanf(fp,"%d %d",&len,&start_index);//second line give the testcase length and start vertex

            if(max_len<len)
                max_len=len;//use max_len to record the longest testcase
            fscanf(fp,"%c",&line);
            
            for(int j=0;j<len;j++){
                for(int k=0;k<len;k++){
                    fscanf(fp,"%d",&adj[j][k]);//read the testcase
                }
                fscanf(fp,"%c",&line);
            }
            bfs(start_index,i,len);//find path by bfs
            col=0;//reset the col
        }
        fclose(fp);
    }
    /* set outputfile's name */
    createfile[0]='o';
    createfile[1]='u';
    createfile[2]='t';
    for(int i=3;i<strlen(filename)+2;i++){
        createfile[i]=filename[i-1];
    }
    fp=fopen(createfile,"w+");//reset fp value

    /* output the result */
    for(int i=0;i<round;i++){
        for(int j=0;j<max_len;j++){
            if(output[i][j]!=-1)
                fprintf(fp,"%d ",output[i][j]);//print the result
        }
        if(i!=round-1)
            fprintf(fp,"\n");
    }
    return 0;
}