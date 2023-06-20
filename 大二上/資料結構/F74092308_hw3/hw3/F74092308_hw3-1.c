#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* define some global variables */
int preIndex=0;//the location in array [pre] 
int postIndex=0;//the location in array [post] 
int output[1000][1000]={0};//the matric print to show the result
int row=0,col=0;//output location
int maxLen=0;//the longest datacase length
bool changeSide[1000]={false};//either 

/* find the data in arr */
int search(int arr[],int start ,int end,int data){
    int i=0;
    for(i=start;i<=end;i++){
        if(arr[i]==data)
            return i;
    }
    return i;//if can't find return end
}

/* if given preorder and inorder, need to find postorder */
void findPostOrder(int in[],int pre[],int startIn,int endIn){

    /* if start location is smaller than end location, end this recursive branch */
    if(startIn>endIn)return;

    int index=search(in,startIn,endIn,pre[preIndex++]);//the location in array [in] 

    /* if left side have numbers */
    findPostOrder(in,pre,startIn,index-1);
    /* if right side have number */
    findPostOrder(in,pre,index+1,endIn);
    
    /* save the data in output matric */
    output[row][col]=in[index];
    col++;
}

/* if given postorder and inorder, need to find preorder */
/*because post order is check from the back side,so it will deal with the right side first */
void findPreOrder(int in[],int post[],int startIn,int endIn){

    /* if start location is smaller than end location, end this recursive branch */
    if(startIn>endIn)return;

    int index=search(in,startIn,endIn,post[postIndex--]);//the location in array [in] 
    
    /* if right side have number */
    findPreOrder(in,post,index+1,endIn);

    /* if left side have numbers */
    findPreOrder(in,post,startIn,index-1);
    
    /* save the data in output matric */
    output[row][col]=in[index];
    col++;
}

/* reset some variable to use again */
void reset(int in[],int pre[],int post[],int length){
    for(int i=0;i<length;i++){
        in[i]=0;
        pre[i]=0;
        post[i]=0;
    }
    /* reset postIndex and preIndex if the distruction not only once */
    postIndex=0;
    preIndex=0;
}

int main(void){
    /* Input consists of 1 + 4𝑚 line */
    /*define some local variables */
    int round=0;//the number of datacase
    int pre[1000]={0};/* if given preorder*/
    int in[1000]={0};/* if given inorder*/
    int post[1000]={0};/* if given postorder*/
    int length=0;/* m=2,represent the numbers datacase contains */
    char instruction[20];/* m=1, represent if it's preorder-inorder or postorder-inorder */
    char filename[20];//input file name
    char createfile[20];//output file name 
    FILE *fp;
    char line[5];

    printf("please input the filemame : ");//get file name
    scanf("%s",&filename);

    if(fp=fopen(filename,"r")){
        fscanf(fp,"%d",&round);

        /*use for loop to repeat solve instruction */
        for(int j=0;j<round;j++){
            fscanf(fp,"%c",&line);

            /*reset the variables avoid error */ 
            reset(in,pre,post,length);
            for(int i =0;i<20;i++){
                instruction[i]='\0';
            }

            /*scan the data we need */
            fgets(instruction,20,fp);
            fscanf(fp,"%d",&length);

            if(length>maxLen)//promote the speed, or it will need to find to 1000 everytime 
            maxLen=length;

            if(strcmp(instruction,"preorder-inorder\n")==0){//if is preorder-inorder
                for(int i=0;i<length;i++){
                    fscanf(fp,"%d",&pre[i]);//set the preorder number
                }
                fgets(line,1,fp);
                for(int i=0;i<length;i++){
                    fscanf(fp,"%d",&in[i]);//set the inorder number
                }
                fgets(line,1,fp);

                findPostOrder(in,pre,0,length-1);
            
                col=0;//reset the location col to save the next datacase
                row+=1;//one datacase  result occupy one row */
            }
            else if(strcmp(instruction,"postorder-inorder\n")==0){//if is postorder-inorder
            /*if is postorder-inorder, becase index find from back, it will need to find right side but reverse the correct answer, so we need to save upside-down */ 
                changeSide[row]=true;

                for(int i=0;i<length;i++){//set the postorder number
                    fscanf(fp,"%d",&post[i]);
                }
                fgets(line,1,fp);
                for(int i=0;i<length;i++){//set the inorder number
                    fscanf(fp,"%d",&in[i]);
                }

                /* find the postorder from back side */
                postIndex=length-1;
                findPreOrder(in,post,0,length-1);
            
                col=0;//reset the location col to save the next datacase
                row+=1;//one datacase  result occupy one row */
            }
            
        }
        fclose(fp);//remember to close file stream
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
        if(!changeSide[i]){//if is preorder-inorder
            for(int j=0;j<maxLen;j++){
                if(output[i][j]!=0)
                    fprintf(fp,"%d ",output[i][j]);
            }
        }
        else{//if is postorder-inorder
            for(int j=maxLen;j>=0;j--){//change the output side
                if(output[i][j]!=0)
                    fprintf(fp,"%d ",output[i][j]);
            }
        }
        if(i!=round-1) 
            fprintf(fp,"\n");
    }
    fclose(fp);//remember to close file stream
    return 0;
}