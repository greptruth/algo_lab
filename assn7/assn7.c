#include <stdio.h>
#include <stdlib.h>
//#include <bits/stdc++.h>
#define RED		1
#define BLACK	2
typedef struct timestamp{
	int time;
	struct timestamp* next;
}timestamp;
typedef struct output{
	int pID,execTime,startTime,endTime,priority;
	timestamp *ts;
	//struct output* next;
}output;
/*typedef struct prioList{
	int priority,pID;
	struct prioList* next;
}prioList;*/
typedef struct node {
	int execTime,priority,pID;
	//prioList* list;
	struct node *left, *right, *p;
	int color;
}node;

//typedef struct node *NODEPTR;
struct node NIL;
node* NILPTR = &NIL;

node* createNode(int ptime,int priority,int pID)
{
	//printf("Here 0.2 \n");
	node* a=malloc(sizeof(node));
	a->execTime=ptime;
	//a->list=malloc(sizeof(prioList));
	a->priority=priority;
	a->pID=pID;
	//a->list->pID=pID;
	//a->list->next=NULL;
	a->color=RED;
	a->p=NULL;
	a->right=NULL;
	a->left=NULL;
	//printf("Here 0.3 %d %d %d\n",a->pID,a->execTime,a->priority);
	return a;

}

void inorder(node* x) {
	if (x != NILPTR) {
		inorder(x->left);
		printf("%d ", x->execTime);
		inorder(x->right);
	}
}

node* search(node* root, int k) {
	if (root == NILPTR || root->execTime == k)
		return root;
	if (k < root->execTime)
		return search(root->left, k);
	else
		return search(root->right, k);
}

node* minimum(node* root) {
	while (root->left != NILPTR)
		root = root->left;
	return root;
}


void leftrotate(node* *treeroot, node* x) {
	node* y = x->right;
	x->right = y->left;
	if (y->left != NILPTR)
		y->left->p = x;
	y->p = x->p;
	if (x->p == NILPTR)
		*treeroot = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void rightrotate(node* *treeroot, node* y) {
	node* x = y->left;
	y->left = x->right;
	if (x->right != NILPTR)
		x->right->p = y;
	x->p = y->p;
	if (y->p == NILPTR)
		*treeroot = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}

void rbinsertfixup(node* *treeroot, node* z) {
	while (z->p->color == RED) {
		if (z->p == z->p->p->left) {
			node* y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					leftrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				rightrotate(treeroot,z->p->p);
			}
		}
		else {
			node* y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					rightrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftrotate(treeroot,z->p->p);
			}
		}
	}
	(*treeroot)->color = BLACK;
}

void rbinsert(node* *treeroot,node* Z) {
	/*NODEPTR Z = (NODEPTR) malloc(sizeof(struct node));
	Z->execTime = z;*/
	//printf("Here 0.5 \n");
	node* y = NILPTR;
	node* x = *treeroot;
	//printf("Here 0.5 \n");
	while (x != NILPTR) {
		y = x;
		//printf("Here 0.6 \n");
		if (Z->execTime < x->execTime)
			x = x->left;
		else
			x = x->right;
	}
	Z->p = y;
	//printf("Here 0.7 \n");
	if (y == NILPTR)
		*treeroot = Z;
	else if (Z->execTime < y->execTime)
		y->left = Z;
	else
		y->right = Z;
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED;
	//printf("Here 0.8 \n");
	rbinsertfixup(treeroot,Z);
}

void rbtransplant(node* *treeroot, node* u, node* v) {
	if (u->p == NILPTR)
		*treeroot = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

void rbdeletefixup(node* *treeroot, node* x) {
	while (x != *treeroot && x->color == BLACK) {
		if (x == x->p->left) {
			node* w = x->p->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				leftrotate(treeroot,x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
			 	if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightrotate(treeroot,w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				leftrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
		else {
			node* w = x->p->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				rightrotate(treeroot,x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					leftrotate(treeroot,w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				rightrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
	}
	x->color = BLACK;
}

void rbdelete(node* *treeroot, node* Z) {
	//NODEPTR Z = search(*treeroot, z);
	if (Z == NILPTR) {
		return;
	}
	node* y = Z;
	int yoc = y->color;
	node* x;
	if (Z->left == NILPTR) {
		x = Z->right;
		rbtransplant(treeroot,Z,Z->right);
	}
	else if (Z->right == NILPTR) {
		x = Z->left;
		rbtransplant(treeroot,Z,Z->left);
	}
	else {
		y = minimum(Z->right);
		yoc = y->color;
		x = y->right;
		if (y->p == Z)
			x->p = y;
		else {
			rbtransplant(treeroot,y,y->right);
			y->right = Z->right;
			y->right->p = y;
		}
		rbtransplant(treeroot,Z,y);
		y->left = Z->left;
		y->left->p = y;
		y->color = Z->color;
	}
	if (yoc == BLACK)
		rbdeletefixup(treeroot,x);
}

node* createProcess(int pID)
{
	int ptime,priority;
	ptime =rand()%1000 +1;
	priority=rand()%4 +1;
	//printf("Here 0.1 %d %d \n",ptime,priority);
	return createNode(ptime,priority,pID);
}

/*void padding ( char ch, int n )
{
  int i;
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void structure(node *root, int level )
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
}*/
void printPTR1(FILE* fp,timestamp* ts)
{
	if(ts==NULL)
		return;
	else{
		printPTR1(fp,ts->next->next);
	}
	fprintf(fp,"_%d ",ts->time);
	return;
}
void printPTR2(FILE* fp,timestamp* ts)
{
	if(ts==NULL)
		return;
	else{
		printPTR2(fp,ts->next->next);
	}
	fprintf(fp,"_%d ",ts->next->time);
	return;
}

void printPTR(FILE* fp,timestamp* ts)
{
	if(ts==NULL)
		return;
	else{
		printPTR(fp,ts->next);
	}
	fprintf(fp,",%d ",ts->time);
	return;
}
int main()
{
	int N=34,M=10,currTime=0,activeProcess=0,_pID=0,currPID,priority,execTime;
	node *Tree=NILPTR,*Tnode;//=malloc(sizeof(RBnode));
	int zM=M;
	int satya;

	output *res=malloc(sizeof(output)*(M+1));




	currTime=0;
	while(activeProcess>0 || M>0)
	{
		//structure(Tree,1);
		//inorder(Tree);
		//printf("*******************************************\n");
		//scanf("%d",&satya);
		//printf("activeProcess M currTime: %d %d %d\n",activeProcess,M,currTime);
		if(activeProcess<N && M>0)
		{
			//tnode=createProcess(++pID);
			//printf("here\n");
			//tnode = (node *)malloc(sizeof(node));
			//printf("----------------------------------------------------------------\n");
			node* tnode =(node *)malloc(sizeof(node));
			//_pID=43;
			_pID=_pID+1;
			//printf("Here -0 %d %d %d\n",tnode->pID,tnode->execTime,tnode->priority);
			tnode->pID=_pID;
			tnode->execTime=rand()%1000 +1;
			tnode->priority=rand()%4 +1;
			tnode->color=RED;
			//printf("\n");
			res[_pID].pID=_pID;
			res[_pID].execTime=tnode->execTime;
			res[_pID].startTime=currTime;
			res[_pID].endTime=currTime;
			res[_pID].priority=tnode->priority;

			res[_pID].ts =NULL;malloc(sizeof(timestamp));
			/*res[_pID].ts->time = currTime;
			res[_pID].ts->next=NULL;*/

			//printf("Here -0 %d %d %d\n",tnode->pID,tnode->execTime,tnode->priority);
			rbinsert(&Tree,tnode);
			++activeProcess;
			M--;
			//printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

		}

		node* tnode ;//=(node *)malloc(sizeof(node));
		//printf("Here -1 \n");
		tnode=minimum(Tree);//based on pending execTimec time - priority
		


		//printf("Minimum : %d %d %d %d %d %d\n",tnode->pID,tnode->execTime,res[tnode->pID].priority,res[tnode->pID].startTime,res[tnode->pID].endTime,currTime);
		//printf("Here -2 \n");
		priority=tnode->priority;
		currPID=tnode->pID;
		execTime=tnode->execTime;

		timestamp* dog;//=malloc(sizeof(timestamp));
		dog = res[currPID].ts;
		res[currPID].ts = malloc(sizeof(timestamp));
		res[currPID].ts->time=currTime;
		//res[currPID].ts->next=NULL;
		res[currPID].ts->next = dog;

		/*if(tnode->list->next==NULL){
			priority=tnode->list->priority;
			currPID=tnode->list->pID;
			execTime=tnode->execTime;
			rbdelete(&Tree,tnode->execTime);
			//printf("Here -3 \n");
		}
		else{
			priority=tnode->list->priority;
			currPID=tnode->list->pID;
			execTime=tnode->execTime;
			tnode->list=tnode->list->next;
			//printf("Here -4 \n");
		}*/
		//time taken by this process
		rbdelete(&Tree,tnode);
		if(execTime<=priority*50){
			//printf("Here 1 \n");
			currTime+=execTime;
			//res[currPID].endTime=currTime;
			--activeProcess;
			//printf("Here -5 \n");
		}
		else{
			//printf("Here 2 %d \n",priority);
			currTime+=(priority*50);
			execTime-=(priority*50);
			//res[currPID].endTime=currTime;
			//res[currPID].endTime=currTime;
			//tnode=createNode(execTime,priority,pID);
			node* Tnode =(node *)malloc(sizeof(node));
			Tnode->pID=currPID;
			Tnode->execTime=execTime;
			Tnode->priority=priority;
			Tnode->color=RED;
			//Tnode = malloc(sizeof(node));

			rbinsert(&Tree,Tnode);
			//printf("Here -6 \n");
		}
		//timestamp* dog;//=malloc(sizeof(timestamp));
		dog = res[currPID].ts;
		res[currPID].ts = malloc(sizeof(timestamp));
		res[currPID].ts->time=currTime;
		//res[currPID].ts->next=NULL;
		res[currPID].ts->next = dog;

		res[currPID].endTime=currTime;
	}
	//printf("activeProcess M currTime: %d %d %d\n",activeProcess,M,currTime);

	FILE* fp;
	fp = fopen("res.csv","w");
	int i;
	fprintf(fp,"Process ID, Creation Time,Priority, time stamps when a process got scheduled,time stamps when a process got preempted from CPU,time stamp when a process completed execution. \n");
	for(i=1;i<=zM;i++){
		fprintf(fp,"%d, %d ,%d,",res[i].pID,res[i].startTime,res[i].priority);
		printPTR2(fp,res[i].ts);
		fprintf(fp,",");

		printPTR1(fp,res[i].ts);
		fprintf(fp,",");

		fprintf(fp,"%d",res[i].endTime);
		//printPTR(fp,res[i].ts);
		fprintf(fp,"\n");
		//printf("\n Result : %d %d %d %d \n",res[i].pID,res[i].execTime,res[i].startTime,res[i].endTime);

		/*while(res[i].ts!=NULL)
		{
			printf("%d ",res[i].ts->time);
			res[i].ts=res[i].ts->next;
		}*/
	}

}
 
