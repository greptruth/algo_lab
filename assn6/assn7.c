#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//typedef long long int;
struct list
{
	struct list *next;
	int data;
};
typedef struct list List;
struct node
{
	struct node *left,*right,*parent,*next,*prev;
	List *list;
	int l,u;

};
typedef struct node Node;

int min(int a,int b)
{
	if(a<b)
		return a;
	return b;
}
int max(int a,int b)
{
	if(a>b)
		return a;
	return b;
}
int as;
Node* CREATE_INTERVAL_TREE(Node* root,int low,int up,int n,int length,int level)
{	

	//scanf("%d",&as);
	if(up==0 && low==0)
	{
		//printf("***********************************************************************************************************************\n");
	}
	if(up-low == length)
	{
		//printf("Tree data %d %d\n",root->l,root->u);
		//printf("Tree %d %d %d %d \n",low ,up ,low ,up );
		root->l=low;
		root->u=up;
		root->list=NULL;
		root->left=NULL;
		root->right=NULL;
		//printf("1 Tree data %d %d\n",root->l,root->u);
		return;
		/*printf("Reject %d %d \n",low,up);
		root->parent->right=NULL;
		root->parent->left=NULL;
		return;
*/
	}
	if(up-low < length && up!=low)
	{
		//printf("Tree data %d %d\n",root->l,root->u);
		//printf("Tree %d %d %d %d \n",low ,up ,low ,up );
		root->l=low;
		root->u=up;
		root->list=NULL;
		root->left=NULL;
		root->right=NULL;
		//printf("2 Tree data %d %d\n",root->l,root->u);
		return;
	}
	if(up-low<length)
		return;
	Node* leftNode = malloc(sizeof(Node));
	Node* rightNode = malloc(sizeof(Node));
	//int length= ceil((u-l)/(n*1.00);
	int medianStart = low + (n/2)*length;
	int medianEnd = medianStart + length;

	//printf("****************%d %d %d %d %d\n",medianStart,medianEnd,low,up,n/2);


	root->l=medianStart;
	root->u=medianEnd;
	root->list=NULL;
	root->left=leftNode;
	root->right=rightNode;
	leftNode->parent=root;
	rightNode->parent=root;


	//printf("Tree %d %d %d %d \n",low ,up ,medianStart,medianEnd );
	//printf("3 Tree data %d %d\n",root->l,root->u);
	//printf("%d %d %d %d %d %d %d \n",low,up,n,length,level,medianStart,medianEnd);
	//scanf("%d",&as);
	//printf("Left %d %d \n",low,medianStart);
	//printf("Right %d %d \n",medianEnd,up);

	// if(root->l==0 && root->u==0)
	// {
	// 	printf("***********************************************************************************************************************\n");
	// }
	CREATE_INTERVAL_TREE(leftNode,low,medianStart,n/2,length,level+1);
	//scanf("%d",&as);
	
	CREATE_INTERVAL_TREE(rightNode,medianEnd,up,n/2 -1,length,level+1);

	
	

}

Node* _CREATE_INTERVAL_TREE(Node* root,int low,int up,int n,int length,int level)
{	

	//scanf("%d",&as);
	/*if(up==0 && low==0)
	{
		printf("***********************************************************************************************************************\n");
	}*/
	if(up-low == length)
	{
		//printf("Tree data %d %d\n",root->l,root->u);
		//printf("Tree %d %d %d %d \n",low ,up ,low ,up );
		root->l=low;
		root->u=up;
		root->list=NULL;
		root->left=NULL;
		root->right=NULL;
		//printf("1 Tree data %d %d\n",root->l,root->u);
		return;
		/*printf("Reject %d %d \n",low,up);
		root->parent->right=NULL;
		root->parent->left=NULL;
		return;
*/
	}
	if(up-low < length && up!=low)
	{
		//printf("Tree data %d %d\n",root->l,root->u);
		//printf("Tree %d %d %d %d \n",low ,up ,low ,up );
		root->l=low;
		root->u=up;
		root->list=NULL;
		root->left=NULL;
		root->right=NULL;
		//printf("2 Tree data %d %d\n",root->l,root->u);
		return;
	}
	if(up-low<length)
	{
		if(root== root->parent->right)
			root->parent->right = NULL;
		else if(root== root->parent->left)
			root->parent->left = NULL;
		return;
	}
	Node* leftNode = malloc(sizeof(Node));
	Node* rightNode = malloc(sizeof(Node));
	//int length= ceil((u-l)/(n*1.00);
	int medianStart = low + (n/2)*length;
	int medianEnd = medianStart + length;

	//printf("****************%d %d %d %d %d\n",medianStart,medianEnd,low,up,n/2);


	root->l=medianStart;
	root->u=medianEnd;
	root->list=NULL;
	root->left=leftNode;
	root->right=rightNode;
	leftNode->parent=root;
	rightNode->parent=root;


	//printf("Tree %d %d %d %d \n",low ,up ,medianStart,medianEnd );
	//printf("3 Tree data %d %d\n",root->l,root->u);
	//printf("%d %d %d %d %d %d %d \n",low,up,n,length,level,medianStart,medianEnd);
	//scanf("%d",&as);
	//printf("Left %d %d \n",low,medianStart);
	//printf("Right %d %d \n",medianEnd,up);

	/*if(root->l==0 && root->u==0)
	{
		printf("***********************************************************************************************************************\n");
	}*/
	_CREATE_INTERVAL_TREE(leftNode,low,medianStart,n/2,length,level+1);
	//scanf("%d",&as);
	
	_CREATE_INTERVAL_TREE(rightNode,medianEnd,up,n/2 -1,length,level+1);

	//return root;

	
	

}
void padding ( char ch, int n )
{
  int i;
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void structure( Node *root, int level )
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
    printf ( "[%d,%d)\n", root->l,root->u );
    structure ( root->left, level + 1 );
  }
}

void structureList( Node *root, int level )
{
  int i;
  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    structureList ( root->right, level + 1 );
    padding ( '\t', level );
    List *temp;
    temp=root->list;
    printf("[");
    while(temp!=NULL)
    {
    	printf("%d,",temp->data);
    	temp=temp->next;
    }
    printf("]\n");
    structureList ( root->left, level + 1 );
  }
}
void LIST_INSERT(List *node,int i)
{
	if(node->next==NULL)
	{	
		if(node->data>i)
		{
			List* curr=malloc(sizeof(List));
			curr->data = i;
			curr->next=node;
			node=curr;
			curr->next=NULL;
		}
		else
		{
			List* curr=malloc(sizeof(List));
			curr->data = i;
			node->next=curr;
			curr->next=NULL;
		}
		//printf("Goinf to insert \n");
		
	}
	if(node->data < i)
	{
		if(node->next->data < i)
		{
			LIST_INSERT(node->next,i);
		}
		else
		{
			List* curr=malloc(sizeof(List));
			curr->data = i;
			curr->next = node->next;
			node=curr;
		}
	}
	
}
void INSERT(Node* root,int i)
{

	if(root->l <= i  && root->u > i)
	{
		//printf("Here %d %d \n",root->l,root->u);
		if(root->list==NULL)
		{
			List* curr=malloc(sizeof(List));
			curr->data = i;
			//printf("ERROR \n");
			root->list=curr;
			//printf("ERROR \n");
			curr->next=NULL;
		}
		else
			LIST_INSERT(root->list,i);
		
	}
	else if(root->l > i)
	{
		INSERT(root->left,i);
	}
	else
		INSERT(root->right,i);
}
void FORCE_MERGE(Node* root,int l,int u)
{
	//printf("ERROR \n");
	if(root==NULL)
		return;

	FORCE_MERGE(root->left,l,u);
	FORCE_MERGE(root->right,l,u);

	root->parent->l = min(root->l,root->parent->l);
	root->parent->u = max(root->u,root->parent->u);

	if(root->parent->list==NULL)
		root->parent->list = root->list;
	else
	{
		//printf("ERROR 1 \n");
		List* curr ;
		curr= root->parent->list;

		while(curr->next!=NULL)
		{
			curr=curr->next;
		}
		curr->next=root->list;
		//printf("ERROR 2 \n");
	}
	return;
}
void LIST_MERGE(List *root,int l,int u,List *node)
{
	return;
}
void ADD_MERGE(Node* root,int l,int u,Node* node)
{
	if((root->u >=l && root->u <= u)&&(root->l < u && root->l > l))
	{
		//printf("1>>>>>>> %d %d \n",root->l,root->u);
		LIST_MERGE(root->list,l,u,node->list);
		node->l=min(root->l,node->l);
		node->u=max(root->u,node->u);
	}	
	else if(root->u >=l && root->u <= u)//upper of root is inside range
	{
		//printf("2>>>>>>> %d %d \n",root->l,root->u);
		//printf("******%d %d \n",root->u,node->u);
		LIST_MERGE(root->list,l,u,node->list);
		node->l=l;
		
	}
	else if(root->l < u && root->l > l)//lower of root is inside range
	{
		//printf("3>>>>>>> %d %d \n",root->l,root->u);
		//printf("******%d %d \n",root->u,node->u);
		LIST_MERGE(root->list,l,u,node->list);
		node->u=u;
		
	}

	return;
}

void _LIST_MERGE(List** Rlist,int l,int u,List** Nlist)
{
	//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	//return;
	List *temp,*tmp,*pstart;
	List *rlist,*nlist;
	rlist=*Rlist;
	nlist=*Nlist;
	//printf("0$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	///////////////////////////////////////
	temp=rlist;
	while(temp->next!=NULL)
	{	
		printf("%d ",temp->data);
		temp=temp->next;
	}
	printf("\n");
	temp=nlist;
	if(temp!=NULL)
	{
		while(temp->next!=NULL)
		{	
			printf("%d ",temp->data);
			temp=temp->next;
		}
		printf("\n");
	}
	/////////////////////////////////////////
	if(rlist==NULL)
	{	
		//printf("1$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
		*Nlist=nlist;
		return;

	}
	if(nlist==NULL)
	{
		//printf("2$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
		nlist=rlist;
		*Nlist=*Rlist;
		return;
	}
	
	if((rlist)->data<(nlist)->data)
	{
		//printf("3$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
		pstart=nlist;
		while(pstart->next!=NULL)
		{
			pstart=pstart->next;
		}
		pstart->next=nlist;
		nlist = rlist;
		*Nlist=nlist;
		return;
	}
	//printf("4$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	pstart=nlist;
	while(pstart->next!=NULL || pstart->next->data>(rlist)->data)
	{
		pstart=pstart->next;
	}
	//printf("5$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	temp = rlist;
	while(temp->next!=NULL)
	{	
		temp=temp->next;
	}
	temp->next=pstart->next;
	pstart->next=rlist;
	//printf("6$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	*Nlist=nlist;
	return;
	/*
	if(rlist->data < pstart->data)
	{
		temp = rlist;
		while(temp->next!=NULL)
		{	
			temp=temp->next;
		}
				temp->next=nlist;
		nlist=rlist;
		return nlist;
	}
	else
	{
		temp=nlist;
		while(temp->next!=NULL)
		{	temp=temp->next;}
		temp->next=rlist;
		return nlist;
	}*/
}



int countNodes(Node *head)
{
    int count = 0;
    Node *temp = head;
    while(temp!=NULL)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

Node* listToTree(Node **head,int n)
{
    /* Base Case */
    if (n <= 0)
        return NULL;
 
    /* Recursively construct the left subtree */
    Node *left = listToTree(head, n/2);
 
    /* Allocate memory for root, and link the above constructed left 
       subtree with root */
    Node *root = malloc(sizeof(Node));
    root->l=(*head)->l;
    root->u=(*head)->u;
    root->left=NULL;
    root->right=NULL;
    root->list=(*head)->list;

    root->left = left;
 
    /* Change head pointer of Linked List for parent recursive calls */
    *head = (*head)->next;
 
    /* Recursively construct the right subtree and link it with root 
      The number of nodes in right subtree  is total nodes - nodes in 
      left subtree - 1 (for root) which is n-n/2-1*/
    root->right = listToTree(head, n-n/2-1);
 
    return root;
}

void PUSH(Node** subTree,Node* ret)
{
	//printf("goliath %d %d\n",ret->l,ret->u);
	if(ret==NULL)
		return;

	else if(*subTree==NULL)
		*subTree=ret;
	else
	{
		ret->next=*subTree;
		(*subTree)->prev=ret;
		*subTree=ret;
	}
	//printf("Exit \n");
}

List* _LIST_INSERT(List *node,int i)
{
	List* tdata=malloc(sizeof(List));
	tdata->data=i;
	tdata->next=NULL;
	List* temp;
	temp=node;
	if(node==NULL)
		return tdata;
	while(temp->next!=NULL)
	{
		temp=temp->next;
	}
	temp->next=tdata;
	return node;

}
Node* _MERGE(Node* root,int l,int u,Node* node,Node** subTree,int gotSubtree,Node** treeEnd)
{
	
	if(root==NULL)
		return;

	//printf("Start %d %d \n",root->l,root->u);
	if((root->u >= l && root->u <= u)||(root->l < u && root->l > l))
	{
		//printf("Here1 \n");
		if(gotSubtree==0)
		{
			//if(root->parent!=NULL)
			*treeEnd=root->parent;//could be NULL
			gotSubtree=1;
		}

		//printf("Here2 \n");
		//////////////////////////////////////////////////////////////////////////
		/*_LIST_MERGE(&(root->list),l,u,&(node->list));
		List *temp;
		temp=node->list;

		while(temp!=NULL)
		{
			printf("|%d| ",temp->data);
			temp=temp->next;
		}
		printf("\n");*/


		//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		//return;
		List *temp,*tmp,*pstart;
		List *rlist,*nlist;
		rlist=root->list;
		nlist=node->list;
		//node->list = root->list;

		

		temp=root->list;
		tmp=NULL;
		while(temp!=NULL)
		{
			//printf("00000$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			if(temp->data >=l && temp->data<u)
			{
				node->list = _LIST_INSERT(node->list,temp->data);

			}
			else
			{
				tmp = _LIST_INSERT(tmp,temp->data);
			}
			//printf("11111$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			temp=temp->next;
		}
		root->list = tmp;

		temp=node->list;
		while(temp!=NULL)
		{	
			//printf("\\\\ %d ",temp->data);
			temp=temp->next;
		}




		
		
		//////////////////////////////////////////////////////////
		if(root->l >= l && root->u <= u)
		{
			root->l=0;
			root->u=0;
		}
		else if(root->u >= l && root->u <= u)//LEFT CASE
		{
			root->u=l;
		}
		else if(root->l < u && root->l > l)
		{
			root->l=u;
		}
		//printf("Here3 \n");
		
	}

	//printf("End \n");
	if(gotSubtree==1)
	{
		//printf("Start %d %d \n",root->l,root->u);

		_MERGE(root->right,l,u,node,subTree,gotSubtree,treeEnd);
		root->next=NULL;
		PUSH(subTree,root);
		_MERGE(root->left,l,u,node,subTree,gotSubtree,treeEnd);
		/*root->l=0;
		root->u=0;*/
	}
	else
	{
		//printf("End %d %d \n",root->l,root->u);
		_MERGE(root->right,l,u,node,subTree,gotSubtree,treeEnd);
		_MERGE(root->left,l,u,node,subTree,gotSubtree,treeEnd);
	}
	return;
	

}

void Q_MERGE(Node** root,int l,int u)
{
	Node *node=malloc(sizeof(Node));
	Node *subTree=NULL,*temp,*tmp;
	Node* treeEnd;
	_MERGE(*root,l,u,node,&subTree,0,&treeEnd);

	//printf("[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[\n");
	List* atemp=node->list;
	while(atemp!=NULL)
	{	
		//printf("... %d ",atemp->data);
		atemp=atemp->next;
	}
	node->l=l;
	node->u=u;
	//node->list=NULL;

	
	temp=subTree;
	while(temp!=NULL)
	{
		//printf("1Subtree  %d %d \n",temp->l,temp->u);
		temp=temp->next;
	}

	temp=subTree;///////////////////removing 0's from start
	if(temp!=NULL)
	{
		while(temp->l==0&& temp->u==0)
		{
			if(temp->l==0&& temp->u==0)
			{
				temp=temp->next;
				if(temp==NULL)
					break;
			}
		}
	}
	subTree=temp;
	/////////////////////////////////////////////////////////////////

	//printf("Hola guys \n");
	temp=subTree;
	while(temp!=NULL)
	{
		//printf("2Subtree  %d %d \n",temp->l,temp->u);
		temp=temp->next;
	}
	///////////////////////////////////////////////////////////////////
	//printf("Hola guys 2 \n");
	/////////////////////////////////////////////////////removing [0,0) from between
	if(subTree!=NULL)
		subTree->prev=NULL;
	temp=subTree;
	while(temp!=NULL)
	{
		if(temp->l==0&& temp->u==0)
		{
			//printf("sfhhdsfh %d %d \n",temp->l,temp->u);
			temp->prev->next=temp->next;
			if(temp->next!=NULL)
				temp->next->prev=temp->prev;
		}
		//printf("satya3 \n");
		temp=temp->next;

	}

	/////////////////////////////////////////////////////////////////////////////////
	//printf("Hola guys 3\n");
	//printf("HERE \n");
	/////////////////////////////////////////////////////////adding node to list
	temp=subTree;
	if(temp!=NULL)
	tmp=temp->next;
	if(subTree==NULL)
	{
		//printf("satya 7 \n");
		subTree=node;

	}
	else
	{
		//printf("satya 0 \n");
		if(subTree->l>node->l)
		{
			//printf("satya1 \n");
			node->next=subTree;
			subTree->prev=node;
			subTree=node;
		}
		else
		{
			//printf("satya2 \n");
			while(1)
			{
				if(tmp==NULL)
				{
					temp->next=node;
					node->prev=temp;
					break;
				}
				else if(tmp->l>node->l)
				{
					temp->next=node;
					node->prev=temp;
					node->next=tmp;
					tmp->prev=node;
					break;
				}
				temp=temp->next;
				tmp=tmp->next;
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////
	//printf("Hola guys 4\n");
	
	temp=subTree;
	while(temp!=NULL)
	{
		//printf("Subtree  %d %d \n",temp->l,temp->u);
		temp=temp->next;
	}

	///////////////////////////////////////////////creating subtree
	node = listToTree(&subTree,countNodes(subTree));
	//structure(node,2);

	//printf("go to hell %d %d \n",treeEnd->l,treeEnd->u);
	if(treeEnd==NULL)
		*root=node;
	else
	{
		if(treeEnd->right->l < node->l)
		{	
			treeEnd->right=node;
			//printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		}
		else
		{
			treeEnd->left=node;
			//printf("??????????????????????????????????????\n");
		}

	}

}

void CHANGE_TREE(Node** root,int l,int u,int n)
{
	int i,live;
	int length= ceil((u-l)/(n*1.00));
	//MERGE(root,65-,65,NULL,NULL);
	/*for(i=u+1;i>1;i=i-length)
	{
		Q_MERGE(root,i-length,i);
		//printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
		printf("__%d %d_______________________________________________________________________________________\n",i-length,i);
		//
		structure(*root,2);
		//printf("__%d %d_______________________________________________________________________________________\n",i-length,i);
		//scanf("%d",&live);
	}*/

	for(i=1;i<=u;i=i+length)
	{
		Q_MERGE(root,i,i+length);
		//printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
		//





		//printf("__%d %d_______________________________________________________________________________________\n",i-length,i);
		//
		//structure(*root,2);
		//printf("__%d %d_______________________________________________________________________________________\n",i-length,i);
		//scanf("%d",&live);
	}

}

int main()
{
	int l=1,up=20,n=8,i;
	//printf("%d %d %d  \n",l,up,n);
	int length= ceil((up-l)/(n*1.00));
	Node* root=malloc(sizeof(Node));
	//int upper=16;
	//printf("%d %d %d  \n",l,upper,n);
	//printf(">> %d \n",length);
	scanf("%d %d %d",&l,&up,&n);
	_CREATE_INTERVAL_TREE(root,l,up+1,n,length,1);
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	structure(root,2);
	scanf("%d",&i);
	for(;i>0;i++)
	{
		INSERT(root,rand()%(up-l)+l);
	}
	// INSERT(root,5);
	// INSERT(root,1);
	// INSERT(root,2);
	// INSERT(root,3);
	// INSERT(root,5);
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	structureList(root,2);


	// printf("\n\nMERGE PROCESSS STARTED \n");
	// MERGE(root,1,9,NULL,NULL);
	//MERGE(root,16,25,NULL,NULL);
	//structure(root,2);
	//Q_MERGE(&root,1,4);
	//Q_MERGE(&root,1,9);
	scanf("%d",&n);
	CHANGE_TREE(&root,l,up,n);
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	structure(root,2);
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	structureList(root,2);

	//structureList(root,2);



	//structureList(root,2);

}