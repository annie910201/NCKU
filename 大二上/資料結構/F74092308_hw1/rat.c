#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <string.h>

#define max_stack_size 100000
#define length 17

/* "input" represent the file read in the code, "route" record the road we go from avoid we repeatly try the same road.*/ 
char  input[length][length+1];/* Because when the file read in will also scan the new line(enter), so we have to add a column in order not to be read error. */ 
int route[length][length];

/* Use "location" to package the x.y point, superimpose stack to record the point we go. */
typedef struct {
    int x;
    int y;
}location;
location stack[max_stack_size];
int top = -1; /* Top is like an arrow point to the peak of the stack. */

int startX,startY; /*the point we start */
int exitX,exitY; /*the point we have to go */

/* Ensure the array is not overflow. */
_Bool isFull() {
    if (top >= max_stack_size - 1)return true;
    else return false;
}
/*Avoid we take the stack without restriction. */
_Bool isEmpty() {
    if (top < 0)return true;
    else return false;
}

/* Take out the peak of the stack. */
location pop() {					
    return stack[top--];            /* move from the stack first and substract the "top" value later */
}

/*Add the stack on the top. */
void push(location loc) {		/* add the "top" value to ensure the stack space is enough then push onto the stack */
    stack[++top] = loc;
}

/*Definite the peak of the stack */
location lastOne;

/*Find the road which is request to obey the rule */
void findPath(int x,int y) {
    int i=1; /* Use i to count the path. */
    while (true) { /*Check the four directions, the priority is right -> down -> up -> left .*/ 
        route[x][y] = 1; /*represent the point we have already go */
        /* Before we push data on the stack, we have to check the point is exist */
        if(x==exitX&&y==exitY){ 
            lastOne.x = x;  /* Althought we find the road,stil needing to set the lastOne to print the successful message */
            lastOne.y = y;
            push(lastOne);
            break;      /*If we reach the end point,  we have to break the loop. */
        }
        if (y + 1 < length && input[x][y + 1] == '0' && route[x][y + 1] == 0) { /*Check the right */
            if (!isFull()) { 
                y++;                    /*If the right road is allowed, we go this direction first and add the Y coordinate */
                lastOne.x = x;          /* After add the coordinate, let the top of the stack is the point */ 
                lastOne.y = y;
                push(lastOne);          /*Push the  lastOne into the stack. */
                printf("%d:%d,%d\n",i,x,y);
                i++;
            }
        }
        else if (x + 1 < length && input[x + 1][y] == '0' && route[x + 1][y]==0) {
            if (!isFull()) {
                x++;                    /*If the down road is allowed but the right road isn't allowed, we go this direction first and add the X coordinate. */
                lastOne.x = x;
                lastOne.y = y;
                push(lastOne);
                printf("%d:%d,%d\n",i,x,y);
                i++;
            }
        }
        else if (x - 1 >= 0 && input[x - 1][y] == '0' && route[x - 1][y] == 0) {
            if (!isFull()) {
                x--;                    /*If the up road is allowed but the right and down road isn't allowed, we go this direction first and substract the X coordinate. */
                lastOne.x = x;
                lastOne.y = y;
                push(lastOne);
                printf("%d:%d,%d\n",i,x,y);
                i++;
            }
        }
        else if (y - 1 < length && input[x][y - 1] == '0' && route[x][y - 1] == 0) {
            if (!isFull()) {
                y--;                    /*If the left road is allowed but the right, down, and up road isn't allowed, we go this direction first and substract the Y coordinate. */
                lastOne.x = x;
                lastOne.y = y;
                push(lastOne);
                printf("%d:%d,%d\n",i,x,y);
                i++;
            }
        }
        else{
            pop();                      /* If there isn't any road to go, it means we go to the blind alley, we have to pop the peak of the stack until find the point which have some branch which is never go. */
            if(isEmpty())break;         /* If we still back the pace until to the starting point, it means the path is impossiblly to find the exit point */
            x=stack[top].x;
            y=stack[top].y;
            printf("%d:%d,%d\n",i,x,y);
            i++;
        }
    }
}
int main(void) {
    char filename[9]; /* "filename" is a variable represent the file name */ 
    printf("Please enter filename : ");
    scanf("%s",&filename);
    FILE *fp;
    fp = fopen("maze.txt", "r"); /* "r" means the file can read. */
    if(fp){
        for(int i=0;i<length;i++){
            for(int j=0;j<length+1 ;j++){
                input[i][j]=fgetc(fp);    /*We have to read the file data in and store into an array */
                if(j==length&&i==length-1)input[i][j]=' '; /* Because after we read the last data, there isn't a new line, we have to set a value aviod being wrong. */
                route[i][j]=0; /* In the begining, we have to initialize the route, if route[2][3] equals to 1, it means we already go the point */
            }
        }
        fclose(fp); /*After read the file, remember to close.*/
    }
    else{
        printf("no");
    }
    for(int i=0;i<length;i++){
        for(int j=0;j<length;j++){
            printf("%c",input[i][j]);
        }
        printf("\n");
    }
  
    do{     /* We have to execute the code at least one time. */
        printf("enter start position : ");
        scanf("%d %d",&startX,&startY);
        if(startY==-1 && startX==-1) /*the end condition */
            printf("end the code.");
        else{
            printf("enter exit position : ");
            scanf("%d %d",&exitX,&exitY);
            /*Because the file doesn't set the start and exit point at first, and the outer layer is 1(represent the hall), we have to change the data in array. */
            input[startX][startY]='0';
            input[exitX][exitY]='0';
            /*Because the code logic in findPath is add first and push later, we have to push the starting point in advance. */
            route[startX][startY]=1;
            lastOne.x=startX;
            lastOne.y=startY;
            push(lastOne);
            printf("0:%d,%d\n",startX,startY);
            findPath(startX,startY);
            if(lastOne.x==exitX && lastOne.y==exitY) /*the successful condition(the last point is exit point) */
                printf("successfully escaped!!\n");
            else printf("failed to escape.\n");
        }
    }while(startY!=-1&&startX!=-1);/*the end condition */
    return 0;
}