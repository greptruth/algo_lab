#include <stdio.h>
#include <stdlib.h>
#define RED 1
#define BLACK 0

typedef struct output{
	int pID,startTime,endTime;
	struct output* next;
}output;
typedef struct prioList{
	int priority,pID;
	struct prioList* next;
}prioList;
typedef struct RBnode{//set defaults each time
	int execTime;
	prioList *list;
	int color;//0-BLACK 1-RED
	struct RBnode *left,*right,*parent;
}RBnode;

RBnode* createNode(int ptime,int priority,int pID)
{
	RBnode* a=malloc(sizeof(RBnode));
	a->execTime=ptime;
	a->list->priority=priority;
	a->list->pID=pID;
	a->list->next=NULL;
	a->color=RED;
	a->parent=NULL;
	a->right=NULL;
	a->left=NULL;

	return a;

}

void LeftRotate(RBnode **root,RBnode *x)
{
    //y stored pointer of right child of x
    RBnode *y = x->right;
 
    //store y's left subtree's pointer as x's right child
    x->right = y->left;
 
    //update parent pointer of x's right
    if (x->right != NULL)
        x->right->parent = x;
 
    //update y's parent pointer
    y->parent = x->parent;
 
    // if x's parent is null make y as root of tree
    if (x->parent == NULL)
        (*root) = y;
 
    // store y at the place of x
    else if (x == x->parent->left)
        x->parent->left = y;
    else    x->parent->right = y;
 
    // make x as left child of y
    y->left = x;
 
    //update parent pointer of x
    x->parent = y;
}
 
 
// Right Rotation (Similar to LeftRotate)
void rightRotate(RBnode **root,RBnode *y)
{
    RBnode *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent =y->parent;
    if (x->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void insertFixUp(struct RBnode **root,struct RBnode *z)
{
    // iterate until z is not the root and z's parent color is red
    while (z != *root && z->parent->color == 'R')
    {
        RBnode *y;
 
        // Find uncle and store uncle in y
        if (z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;
 
        // If uncle is RED, do following
        // (i)  Change color of parent and uncle as BLACK
        // (ii) Change color of grandparent as RED
        // (iii) Move z to grandparent
        if (y->color == 'R')
        {
            y->color = 'B';
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
        }
 
        // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
        else
        {
            // Left-Left (LL) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Right Rotate Grandparent
            if (z->parent == z->parent->parent->left &&
                z == z->parent->left)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent->parent);
            }
 
            // Left-Right (LR) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Left Rotate Parent
            // (iii) Right Rotate Grand Parent
            if (z->parent == z->parent->parent->left &&
                z == z->parent->right)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent);
                rightRotate(root,z->parent->parent);
            }
 
            // Right-Right (RR) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Left Rotate Grandparent
            if (z->parent == z->parent->parent->right &&
                z == z->parent->right)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent->parent);
            }
 
            // Right-Left (RL) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Right Rotate Parent
            // (iii) Left Rotate Grand Parent
            if (z->parent == z->parent->parent->right &&
                z == z->parent->left)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent);
                LeftRotate(root,z->parent->parent);
            }
        }
    }
    (*root)->color = 'B'; //keep root always black
}
 
// Utility function to insert newly node in RedBlack tree
void insertNode(struct RBnode **root, RBnode* z)
{
    // Allocate memory for new node
    /*struct node *z = (struct node*)malloc(sizeof(struct node));
    z->data = data;
    z->left = z->right = z->parent = NULL;*/
 
     //if root is null make z as root
    if (*root == NULL)
    {
        z->color = 'B';
        (*root) = z;
    }
    else
    {
        RBnode *y = NULL;
        RBnode *x = (*root);
 
        // Follow standard BST insert steps to first insert the node
        while (x != NULL)
        {
            y = x;
            if (z->execTime < x->execTime)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (z->execTime > y->execTime)
            y->right = z;
        else
            y->left = z;
        z->color = RED;
 
        // call insertFixUp to fix reb-black tree's property if it
        // is voilated due to insertion.
        insertFixUp(root,z);
    }
}

// void leftRotate(RBnode* root,RBnode* x){//check for NULL
// 	RBnode* y=x->right;
// 	//y
// 	if(x->parent->right==x)
// 		x->parent->right=y;
// 	else
// 		x->parent->left=y;
// 	y->parent=x->parent;
// 	//beta
// 	x->right=y->left;
// 	x->right->parent=x;
// 	//x
// 	y->left=x;
// 	x->parent=y;
// }

// void rightRotate(RBnode* root,RBnode* x){//check for NULL
// 	RBnode* x= y->left;
// 	//x
// 	if(y->parent->right==y)
// 		y->parent->right=x;
// 	else
// 		y->parent->left=x;
// 	//beta
// 	y->left=x->right;
// 	y->left->parent=y;
// 	//y
// 	x->right=y;
// 	y->parent=x;
// }

// void insert(RBnode* root,RBnode* x){
// 	while(x!=root && root->parent==RED){
// 		if(x->parent==x->parent->parent->left){
// 			node* y=x->parent->parent->right;
// 			if(y.color==RED){
// 				x->parent->color=BLACK;
// 				y->color=BLACK;
// 				x->parent->parent->color=BLACK;
// 				x=x->parent->parent;
// 			}
// 		}
// 		else if(x==x->parent->right){
// 			x=x->parent;
// 			leftRotate(root,x);
// 			x->parent->color=BLACK;
// 			x->parent->parent->color=RED;
// 			rightRotate(root.x->parent->parent);
// 		}
// 		else{//TO DO
// 			rightRotate(root,x);
// 			/*x->parent->color = BLACK;
// 			x->parent->parent->color=RED;
// 			leftRotate*/
// 		}
// 	}
// }

RBnode* extractMin(RBnode* root)
{
	if(root==NULL)
		return NULL;
	if(root->left==NULL)
		return root;
	else
		return extractMin(root->left);
}

RBnode* createProcess(int pID)
{
	int ptime,priority;
	ptime =rand()%1000 +1;
	priority=rand()%4 +1;
	return createNode(ptime,priority,pID);
}

void padding ( char ch, int n )
{
  int i;
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void structure( RBnode *root, int level )
{
  int i;
  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    structure ( root->right, level + 1 );
    padding ( '\t', level );
    // if(root->l==0)
    // 	printf("here\n");
    printf ( "(%d)\n", root->execTime);
    structure ( root->left, level + 1 );
  }
}



//int highestPriority

int main()
{
	int N=34,M=854,currTime=0,activeProcess=0,pID=1,currPID,priority,execTime;
	RBnode *Tree,*tnode;//=malloc(sizeof(RBnode));




	currTime=0;
	while(N>0 || M>0)
	{
		if(activeProcess<N && M>0)
		{
			tnode=createProcess(++pID);
			insertNode(&Tree,tnode);
			++activeProcess;
			M--;
		}


		tnode=extractMin(Tree);//based on pending execTimec time - priority
		if(tnode->list->next==NULL){
			priority=tnode->list->priority;
			currPID=tnode->list->pID;
			execTime=tnode->execTime;
			deleteNode(tnode);
		}
		else{
			priority=tnode->list->priority;
			currPID=tnode->list->pID;
			execTime=tnode->execTime;
			tnode->list=tnode->list->next;
		}
		//time taken by this process
		if(execTime<=priority*50){
			currTime+=execTime;
			--activeProcess;
		}
		else{
			currTime+=priority*50;
			execTime-=priority*50;
			tnode=createNode(execTime,priority,pID);
			insertNode(&Tree,tnode);
		}
	}

}