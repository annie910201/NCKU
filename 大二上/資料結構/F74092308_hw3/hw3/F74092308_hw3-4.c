#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define max 1000000

/* ddefine global variables*/
int insertEdges[max+1][3];//record the edge between two vertices
int parent[max+1];//record the vertices' parent(after set a chain, parent is the smallest number)

/* find the parent and change the parent by while loop if its parent have parent */
int find(int i){
    while(parent[i])
        i=parent[i];
    return i;
}

/* check when two vertices have edge between them whether make a cycle */
bool check_cycle(int front,int back){
    if(front!= back){//if not make a cycle
        parent[back]=front;
        return true;
    }
    return false;
}

int main(void){
    /* define some local variables */
    int vertices=0,edges=0;//the input vertices and edges
    int node1=0,node2=0,weight=0;//remember every input vertices and cost
    int record_edge=0; //record what row of insert_edges
    int minWeight=0;//the output result
    int u=0,v=0;//record two vertices when they have minmum cost to check whether have cycle
    int min=max;//find minnimun path 
    int count=1;//if have n vertices, there are n-1 edges
    char filename[20];//input file name
    char createfile[20];//output file name 
    FILE *fp;
    char line[5];

    printf("please input the filemame : ");//get file name
    scanf("%s",&filename);

    if(fp=fopen(filename,"r")){
        fscanf(fp,"%d %d",&vertices,&edges);
        fscanf(fp,"%c",&line);

        /*scan the data input */
        for(int i=0;i<edges;i++){
            fscanf(fp,"%d %d %d",&node1,&node2,&weight);//scan the edges between vertices
            fscanf(fp,"%c",&line);
            insertEdges[i][0]=node1;//column 0 record the vertex front
            insertEdges[i][1]=node2;//column 1 record the vertex back
            insertEdges[i][2]=weight;//column 2 record two vertices' weight
        }

        while(count<vertices){
            min=max;//reset the min
                for(int k=0;k<edges;k++){
                    if(insertEdges[k][2]<min){//if find min cost 
                        min=insertEdges[k][2];//change min
                        record_edge=k;//record now row
                        u=insertEdges[k][0];//record row
                        v=insertEdges[k][1];//record col
                    }
                }
            u=find(u);//find u's parent
            v=find(v);//find v's parent
            if(check_cycle(u,v)){//if not make a cycle
                minWeight+=min;
                count++;//add 1 to count
            }
            insertEdges[record_edge][2]=max;//because has take the number, make the weight to max avoid to take it again
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
    fprintf(fp,"%d\n",minWeight);
    fclose(fp);

    return 0;
}