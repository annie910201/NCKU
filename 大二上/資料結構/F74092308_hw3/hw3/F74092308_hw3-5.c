#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define max 100

/* record the shortest path */
int shortestLen[max+2];
/* record the input edge */
int inputGraph[max+2][3];

/*define the type Node */
struct Node{
    int dur;//represent the edge weight 
    struct Node* link;//represent every vertex in graph link to where(in order to find path by topological,we let the pointer point point to contrary)
};

struct Node* graph[max+2];//put the Node's pointer


int main(void){
    /* define some local variable */
    int vertex=0;//represent how many vertex
    int sourse=0;//the root to begin find path
    char filename[20];//input file name
    char createfile[20];//output file name 
    FILE *fp;
    char line[5];

    printf("please input the filemame : ");//get file name
    scanf("%s",&filename);

    if(fp=fopen(filename,"r")){
        /* scan the data input */
        fscanf(fp,"%d",&vertex);
        fscanf(fp,"%c",&line);
        for(int i=1;i<vertex;i++){
            fscanf(fp,"%d %d %d",&inputGraph[i][0],&inputGraph[i][1],&inputGraph[i][2]);//set the data of inputGraph
            fscanf(fp,"%c",&line);
        }
        fscanf(fp,"%d",&sourse);//root

        /* initialize the graph */
        for(int i=0;i<=vertex;i++){
            graph[i]=(struct Node*)malloc(sizeof(struct Node));//notice to give the pointer a space
            graph[i]->dur=0;
            graph[i]->link=NULL;
        }

        /* set the root Node */
        graph[sourse]->dur=0;//root's duration with its front vertex is 0(because it's on the head)
        graph[sourse]->link=NULL;//root's link is point to NULL
        
        /* set the other data */
        for(int i=1;i<vertex;i++){
            if(inputGraph[i][1]==sourse){//we need to contrary to set the pointer to let the root is on the head
                graph[inputGraph[i][0]]->link=graph[sourse];
                graph[inputGraph[i][0]]->dur=inputGraph[i][2];
            }
            else {//we let the back node point to the front node
                graph[inputGraph[i][1]]->link=graph[inputGraph[i][0]];
                graph[inputGraph[i][1]]->dur=inputGraph[i][2];
            }
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
    
    /* calculate the duration */
    for(int i=1;i<=vertex;i++){
        int duration=0;
        struct Node* tmp=(struct Node*)malloc(sizeof(struct Node));
        tmp=graph[i];
        while(tmp!=NULL){//if still have node, find the front node's duration with its front node
            duration+=(tmp->dur);
            tmp=tmp->link;//move to its front node
        }
        if(i!=vertex)
            fprintf(fp,"%d %d\n",i,duration);//print the result
        else
            fprintf(fp,"%d %d",i,duration);//print the result
    }
    fclose(fp);
}