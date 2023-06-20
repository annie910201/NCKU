#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define max 1024//the queue and stack space 

/*record whether to print the message*/
bool canFind=true;
bool canDel=true;
bool canInsert=true;

/* define root */
struct node* root =NULL;

/* record the mode */
int mode=0;

/*define the node */
typedef struct node{
    int data;
    struct node *right, *left;
};

/* when insert a node, it may need to create a new node */
struct  node* newNode(int data)
{
    /* create a new node and return it */
    struct node *tmp=(struct node*)malloc(sizeof(struct node));
    tmp->data=data;//insert number
    tmp->left=NULL;
    tmp->right=NULL;
    return tmp;
};

/* when insert a node ,if it's in the buttom ,add it directly,else, change the link */ 
struct node* insert(struct node *node,int data){

    /* if the insert one is in the buttom */
    if(node==NULL){
        canInsert=true;
        return newNode(data);
    }

    /* if data is smaller than node->data, find left  side of the node */
    if(data<node->data)
        node->left=insert(node->left,data);

    /* if data is bigger than node->data, find right  side of the node */
    else if(data > node->data)
        node->right=insert(node->right,data);

    /* if find the number is equal to the node->number, can't insert the node and return origianl one */
    else if(data == node->data){
        printf("Error. Number %d exists.\n",data);
        canInsert=false;//not to print the message
    }
    return node;
}

/* when delect the node we may delete the one which is the parent of its child, we neew to find the child to replace it */
struct node* minValue(struct node *node){
    struct node *current=node;
    while(current && current->left!=NULL)
        current =current ->left;
    return current;
}

/* when delete the node, if it's in the buttom, delete it directly, else, delete and replace the node */
struct node* delete(struct node *root,int data){
    /*if input a number doesn't exist*/
    if(root==NULL){ // it represent we can't find the node
        printf("Number %d is not exists.\n",data);
        canDel=false;//not to print the message
        return  root;
    }
    if(data<root->data)//find the node's left side
        root->left=delete(root->left,data);
    else if(data>root->data)//find the node's right side
        root->right=delete(root->right,data);
    else{ //if find the delete node

        /* if the node doesn't have child */
        if(root->left==NULL&&root->right==NULL){
            return NULL;
        }
        /* node with one child or no child ,for one child,we put the bigger child(right) first*/
        if(root->left==NULL){//find the right side child
            struct node* tmp=root->right;
            free(root);// free the space of delete node
            canDel=true;
            return tmp;//replace the delete node
        }

        else if(root->right==NULL){//find the left side child
            struct node* tmp=root->left;
            free(root);
            canDel=true;
            return tmp;
        }

        /* node with two child */
        struct node* tmp=minValue(root->right);//find the smallest of right side,therefore,new node's right side is bigger than itself. */
        root->data=tmp->data;//only replace, not delete
        root->right=delete(root->right,tmp->data);// continue to find the node and delete
    }
    return root;
}

bool find(struct node *root,int data){
    while(root!=NULL){
        if(root->data==data){//find the data
            return true;
        }
        else if(root->data<data){//data is bigger than root->data,find the right side 
            root=root->right;
        }
        else if(root->data>data){ //data is smaller than root->data,find the left side 
            root=root->left;
        }
    }
    if(mode==1)// mode2 doesn't need to print this message
        printf("SORRY. %d is not found.\n",data);
    return false;//it means when we find the buttom, still can't find the data
}

/* find the location of sword and meat */
void cappofind(struct node *root,int sword,int meat){
    /* use stack to record the path */
    struct node** stack = (struct node**)malloc(sizeof(struct node*) *max);
    
    /* use tmp to point the top of the stack, top is record location */
    struct node *tmp=root;
    int top=0;
    while(true){//until find the sword
        printf("%d->",tmp->data);
        stack[top]=tmp;//put it in the stack

        /* first,find the sword */ 
        if(tmp->data<sword){//if sword is bigger than tmp->data
            tmp=tmp->right;//move the pointer
            top++;
        }
        else if(tmp->data>sword){//if sword is smaller than tmp->data
            tmp=tmp->left;
            top++;
        }
        else{//if find the sword
            top--;//because original top has added 1 
            break;
        }
    }

    /*after find the sword, we need to find meat */
    while(true){//until find the meat
        /* find the meat under tmp */
        if(find(tmp,meat)){
            while(true){//until find the meat
                if(tmp->data<meat){//if meat is bigger
                    tmp=tmp->right;//move to right
                    if(tmp->data!=meat)
                        printf("%d->",tmp->data);
                    else{//find the meat
                        printf("%d\n",tmp->data);
                        break;
                    }
                }
                else if(tmp->data>meat){//if meat is smaller 
                    tmp=tmp->left;//move to left
                    if(tmp->data!=meat)
                        printf("%d->",tmp->data);
                    else{//find the meat 
                        printf("%d\n",tmp->data);
                        break;
                    }
                }
            }
        }

        /* if we can't find the meat, find its parent, so we take out the node before the tmp */ 
        if(tmp->data!=meat){
            tmp=stack[top--];
            printf("%d->",tmp->data);
        }
        else
            break;//end the function
    }
}

/* find the index and delete it */
void cappoFindIndex(struct node* root,struct node* tmp,int index){
    if(tmp==NULL)return;//if tmp is point to the buttom, end the function, and not return anything
    cappoFindIndex(root,tmp->left,index);
    cappoFindIndex(root,tmp->right,index);
    int findIndex=tmp->data;//use findIndex to find the last digit      //find=10
    int remain=tmp->data;//use remain to record the last number     //remain=10
    while(findIndex!=0||remain!=0){
        if(findIndex==index){//find the number which contain index
            printf("Number %d is deleted.\n",tmp->data);
            root=delete(root,tmp->data);
            break;
        }
        else{//number still have digit to compare 
            findIndex=remain%10;//find=0//find=1
            remain/=10;//remain=1//remain=0
        }
    }
}

/* preorder is print first,than go left, than go right */
void printPrefix(struct node *root){
    if(root==NULL)//is in the buttom
        return;
    printf("%d ",root->data);
    printPrefix(root->left);//use recursive
    printPrefix(root->right);//use recursive
    
}

/*postorder is go left first, than go right, than print */
void printPostfix(struct node *root){
    if(root==NULL)//is in the buttom
        return;
    printPostfix(root->left);//use recursive
    printPostfix(root->right);//use recursive
    printf("%d ",root->data);
}

/*inorder is go left first, than print, than go right */
void printInfix(struct node *root){
    if(root==NULL)//is in the buttom
        return;
    printInfix(root->left);//use recursive
    printf("%d ",root->data);
    printInfix(root->right);//use recursive
}

/* level order is print according to level */
void printLevel(struct node *root){

    /*use queue to solve, define queue and front.rear */
    int rear=0,front=0;
    struct node** queue = (struct node**)malloc(sizeof(struct node*) *max);
    
    /*use tmp to go the tree */
    struct node *tmp=root;

    while(tmp){//until tmp is null
        printf("%d ",tmp->data);
        if(tmp->left){//go left first
            queue[rear]=tmp->left;
            rear++;
        }
        if(tmp->right){//than go right
            queue[rear]=tmp->right;
            rear++;
        }
        front++;//than pop the front queue out 
        tmp=queue[front-1];
    }
}

int main(void){
    while(true){//until we input zero
        printf("(1)Binary searching Tree.\n");
        printf("(2)Finding Meaty.\n");
        printf("(0)Escape and face to music next year.\n");
        scanf("%d",&mode);//choose the mode
        getchar();//scan the newline
        if(mode==1){
            root=NULL;//reset the root
            while(true){
                char action;//record the action
                printf("(I)nsert a number.\n");
                printf("(D)elete a number.\n");
                printf("(S)earch a number.\n");
                printf("(P)rint 4 kinds of orders.\n");
                printf("(R)eturn\n");
                scanf("%c",&action);
                getchar();
                if(action=='i'){//insert
                    printf("Enter numbers: ");
                    int input;
                    while(true){
                       scanf("%d",&input);
                       if(input==-1){//the end condition
                           getchar();
                           break;
                        }
                        root=insert(root,input);//insert the number and return the root of a binary tree
                        if(canInsert){//input is not the repeat number
                           printf("Number %d is inserted.\n",input);
                        }
                    }
                }
                else if(action=='d'){//delete
                    printf("Enter numbers to deleted : ");
                    int input;
                    while(true){
                        scanf("%d",&input);
                        if(input==-1){//the end condition
                           getchar();
                           break;
                        }
                        root=delete(root,input);//delete the number and return the root of a binary tree
                        if(canDel)//input is not the repeat number
                            printf("Number %d is deleted.\n",input);
                    }
                }
                else if(action=='s'){//search
                    printf("Enter numbers to searching : ");
                    int input;
                    while(true){
                        scanf("%d",&input);
                        if(input==-1){//the end condition
                           getchar();
                           break;
                        }
                        if(canFind= find(root,input))//if can find the input
                            printf("Bingo! %d is found.\n",input);
                    }
                }
                else if(action=='p'){//print the tree in different type

                    /* preorder type */
                    printf("The tree in prefix order : ");
                    printPrefix(root);

                    /* inorder type */
                    printf("\nThe tree in infix order : ");
                    printInfix(root);

                    /* postorder type */
                    printf("\nThe tree in postfix order : ");
                    printPostfix(root); 

                    /* level order type */
                    printf("\nThe tree in level order : ");
                    printLevel(root);

                    putchar('\n');
                }
                else if(action=='r'){//return
                    break;
                }
            }
        }
        else if(mode==2){
            root=NULL;//reset the root

            /* record the location of sword,meat, and index to delete */
            int locSword,locMeat,index;

            /*define the file name to get the file */
            char filename[10];

            printf("Please input the map file : ");
            scanf("%s",&filename);            
            FILE *fp;
            if(fp=fopen(filename,"r")){//the file is exist

                char before[10];
                int fileTxt[100];
                int i=0;
                while(true){
                    memset(before,'0',strlen(before));//reset before to scan the next number
                    if(fgets(before,sizeof(before),fp)==NULL)break;//end until the final line
                    else{
                        if(before[strlen(before)-1]=='\n')//remove the newline
                            before[strlen(before)-1]=='\0';
                        fileTxt[i]=atoi(before);//convert to integer
                        root=insert(root,fileTxt[i]);//build a tree
                        i++;
                    }
                }

                printf("Load file success.\n");
                putchar('\n');
                
                /* get the location of sword */
                printf("Please input the sword location : ");
                scanf("%d",&locSword);
                getchar();
                
                /* get the location of meat */
                printf("Please input the Meaty's location : ");
                scanf("%d",&locMeat);
                getchar();

                /* get the index number */
                printf("Please input the broccoli traps' index (0~9) : ");
                scanf("%d",&index);
                getchar();
                putchar('\n');

                /* delete the node which cotains index in postorder */
                struct node* tmp=root;

                /* use a function to check if the node's data has the index */
                cappoFindIndex(root,tmp,index);
                
                putchar('\n');
                printf("Capoo successfully found his favorite meaty<3.\n");
                putchar('\n');

                printf("Shortest path to find the meaty : \n");
                cappofind(root,locSword,locMeat);//find the fast path
                
                fclose(fp);//close the file
            }
        }
        else{//if mode is other
            break;
        }
    }
    return 0;
}

