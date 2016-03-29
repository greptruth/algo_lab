/* Author: Prakhar Jain */
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#define RED		1
#define BLACK	2

typedef struct output{
	int pID,execTime,startTime,endTime,priority;
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
	node()
	{
		pID=33;
	}
}node;

typedef struct node *NODEPTR;
struct node NIL;
NODEPTR NILPTR = &NIL;

node* createNode(int ptime,int priority,int pID)
{
	//printf("Here 0.2 \n");
	//node* a=(node *)malloc(sizeof(node));
	node *a=new node();
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
	printf("Here 0.3 %d %d %d\n",a->pID,a->execTime,a->priority);
	return a;

}

void inorder(NODEPTR x) {
	if (x != NILPTR) {
		inorder(x->left);
		printf("%d ", x->execTime);
		inorder(x->right);
	}
}

NODEPTR search(NODEPTR root, int k) {
	if (root == NILPTR || root->execTime == k)
		return root;
	if (k < root->execTime)
		return search(root->left, k);
	else
		return search(root->right, k);
}

NODEPTR minimum(NODEPTR root) {
	while (root->left != NILPTR)
		root = root->left;
	return root;
}

NODEPTR maximum(NODEPTR root) {
	while (root->right != NILPTR)
		root = root->right;
	return root;
}

NODEPTR successor(NODEPTR root, int x) {
	NODEPTR temp = search(root, x);
	if (temp == NILPTR) {
		printf("%d not in tree\n", x);
		return temp;
	}
	if (temp->right != NILPTR)
		return minimum(temp->right);
	NODEPTR y = temp->p;
	while (y != NILPTR && temp == y->right) {
		temp = y;
		y = y->p;
	}
	return y;
}

NODEPTR predecessor(NODEPTR root, int x) {
	NODEPTR temp = search(root, x);
	if (temp == NILPTR) {
		printf("%d not in tree\n", x);
		return temp;
	}
	if (temp->left != NILPTR)
		return maximum(temp->left);
	NODEPTR y = temp->p;
	while (y != NILPTR && temp == y->left) {
		temp = y;
		y = y->p;
	}
	return y;
}
void leftrotate(NODEPTR *treeroot, NODEPTR x) {
	NODEPTR y = x->right;
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

void rightrotate(NODEPTR *treeroot, NODEPTR y) {
	NODEPTR x = y->left;
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

void rbinsertfixup(NODEPTR *treeroot, NODEPTR z) {
	while (z->p->color == RED) {
		if (z->p == z->p->p->left) {
			NODEPTR y = z->p->p->right;
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
			NODEPTR y = z->p->p->left;
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

void rbinsert(NODEPTR *treeroot,NODEPTR Z) {
	/*NODEPTR Z = (NODEPTR) malloc(sizeof(struct node));
	Z->execTime = z;*/
	//printf("Here 0.5 \n");
	NODEPTR y = NILPTR;
	NODEPTR x = *treeroot;
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

void rbtransplant(NODEPTR *treeroot, NODEPTR u, NODEPTR v) {
	if (u->p == NILPTR)
		*treeroot = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

void rbdeletefixup(NODEPTR *treeroot, NODEPTR x) {
	while (x != *treeroot && x->color == BLACK) {
		if (x == x->p->left) {
			NODEPTR w = x->p->right;
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
			NODEPTR w = x->p->left;
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

void rbdelete(NODEPTR *treeroot, NODEPTR Z) {
	//NODEPTR Z = search(*treeroot, z);
	if (Z == NILPTR) {
		printf("Node to be deleted not found\n");
		return;
	}
	NODEPTR y = Z;
	int yoc = y->color;
	NODEPTR x;
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
	printf("Here 0.1 %d %d \n",ptime,priority);
	return createNode(ptime,priority,pID);
}

void padding ( char ch, int n )
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
}


int main()
{
	int N=34,M=1,currTime=0,activeProcess=0,_pID=0,currPID,priority,execTime;
	node *Tree=NILPTR;//=malloc(sizeof(RBnode));
	int zM=M;
	int satya;

	output *res=(output *)malloc(sizeof(output)*M);




	currTime=0;
	while(activeProcess>0 || M>0)
	{
		scanf("%d",&satya);
		printf("activeProcess M currTime: %d %d %d\n",activeProcess,M,currTime);
		if(activeProcess<N && M>0)
		{
			//tnode=createProcess(++pID);
			//printf("here\n");
			//tnode = (node *)malloc(sizeof(node));
			node *tnode =new node();
			_pID=43;
			_pID++;
			printf("Here -0 %d %d %d\n",tnode->pID,tnode->execTime,tnode->priority);
			tnode->pID=_pID;
			tnode->execTime=rand()%1000 +1;
			tnode->priority=1;//rand()%4 +1;
			tnode->color=RED;
			//printf("\n");
			res[_pID].pID=_pID;
			res[_pID].execTime=tnode->execTime;
			res[_pID].startTime=currTime;
			res[_pID].endTime=currTime;
			res[_pID].priority=tnode->priority;
			printf("Here -0 %d %d %d\n",tnode->pID,tnode->execTime,tnode->priority);
			rbinsert(&Tree,tnode);
			++activeProcess;
			M--;
			//delete[] tnode;
		}

		node *tnode2=new node();
		//printf("Here -1 \n");
		tnode2=minimum(Tree);//based on pending execTimec time - priority
		printf("Minimum : %d %d %d %d %d %d\n",tnode2->pID,tnode2->execTime,res[tnode2->pID].priority,res[tnode2->pID].startTime,res[tnode2->pID].endTime,currTime);
		//printf("Here -2 \n");
		priority=tnode2->priority;
		currPID=tnode2->pID;
		execTime=tnode2->execTime;

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
		rbdelete(&Tree,tnode2);
		if(execTime<=priority*50){
			printf("Here 1 \n");
			currTime+=execTime;
			//res[currPID].endTime=currTime;
			--activeProcess;
			//printf("Here -5 \n");
		}
		else{
			printf("Here 2 %d \n",priority);
			currTime+=(priority*50);
			execTime-=(priority*50);
			//res[currPID].endTime=currTime;
			//res[currPID].endTime=currTime;
			//tnode=createNode(execTime,priority,pID);
			tnode2->pID=currPID;
			tnode2->execTime=execTime;
			tnode2->priority=priority;
			tnode2->color=RED;
			//tnode = (node *)malloc(sizeof(node));
			//tnode =new node();

			rbinsert(&Tree,tnode2);
			//printf("Here -6 \n");
		}
		res[currPID].endTime=currTime;
	}
	printf("activeProcess M currTime: %d %d %d\n",activeProcess,M,currTime);

	int i;
	for(i=1;i<=zM;i++){
	printf("Result : %d %d %d %d \n",res[i].pID,res[i].execTime,res[i].startTime,res[i].endTime);
	}

}
 

/*main()
{
	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK;
	NODEPTR tree = NILPTR;
	int n;
	while (1) {
		printf("1.Insert\n2.Search\n3.Inorder Walk\n4.Minimum\n5.Maximum\n6.Successor\n7.Predecessor\n8.Delete\n9.Exit\n");
		scanf("%d", &n);
		if (n == 1) {
			printf("Enter any number:\n");
			int num;
			scanf("%d", &num);
			rbinsert(&tree, num);
		}
		else if (n == 2) {
			printf("Enter the number to be search\n");
			int num;
			scanf("%d", &num);
			if (search(tree, num) == NILPTR)
				printf("%d not found\n", num);
			else
				printf("%d found\n", num);
		}
		else if (n == 3) {
			inorder(tree);
			printf("\n");
		}
		else if (n == 4)
			printf("%d\n", minimum(tree)->key);
		else if (n == 5)
			printf("%d\n", maximum(tree)->key);
		else if (n == 6) {
			printf("Enter the number whose successor needs to be found\n");
			int num;
			scanf("%d", &num);
			NODEPTR t = successor(tree, num);
			if (t != NULL)
				printf("%d\n", t->key);
		}
		else if (n == 7) {
			printf("Enter the number whose predecessor needs to be found\n");
			int num;
			scanf("%d", &num);
			NODEPTR t = predecessor(tree, num);
			if (t != NULL)
				printf("%d\n", t->key);
		}
		else if (n == 8) {
			printf("Enter the number to be deleted\n");
			int num;
			scanf("%d", &num);
			rbdelete(&tree, num);
		}
		else 
			break;
	}
	return 0;
}*/
