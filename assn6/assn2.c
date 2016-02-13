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
	struct node *left,*right,*parent;
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
		printf("***********************************************************************************************************************\n");
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
		printf("1 Tree data %d %d\n",root->l,root->u);
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
		printf("2 Tree data %d %d\n",root->l,root->u);
		return;
	}
	if(up-low<length)
		return;
	Node* leftNode = malloc(sizeof(Node));
	Node* rightNode = malloc(sizeof(Node));
	//int length= ceil((u-l)/(n*1.00);
	int medianStart = low + (n/2)*length;
	int medianEnd = medianStart + length;

	printf("****************%d %d %d %d %d\n",medianStart,medianEnd,low,up,n/2);


	root->l=medianStart;
	root->u=medianEnd;
	root->list=NULL;
	root->left=leftNode;
	root->right=rightNode;
	leftNode->parent=root;
	rightNode->parent=root;


	//printf("Tree %d %d %d %d \n",low ,up ,medianStart,medianEnd );
	printf("3 Tree data %d %d\n",root->l,root->u);
	//printf("%d %d %d %d %d %d %d \n",low,up,n,length,level,medianStart,medianEnd);
	//scanf("%d",&as);
	//printf("Left %d %d \n",low,medianStart);
	//printf("Right %d %d \n",medianEnd,up);

	if(root->l==0 && root->u==0)
	{
		printf("***********************************************************************************************************************\n");
	}
	CREATE_INTERVAL_TREE(leftNode,low,medianStart,n/2,length,level+1);
	//scanf("%d",&as);
	
	CREATE_INTERVAL_TREE(rightNode,medianEnd,up,n/2 -1,length,level+1);

	
	

}

Node* _CREATE_INTERVAL_TREE(Node* root,int low,int up,int n,int length,int level)
{	

	//scanf("%d",&as);
	if(up==0 && low==0)
	{
		printf("***********************************************************************************************************************\n");
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
		printf("1 Tree data %d %d\n",root->l,root->u);
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
		printf("2 Tree data %d %d\n",root->l,root->u);
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

	printf("****************%d %d %d %d %d\n",medianStart,medianEnd,low,up,n/2);


	root->l=medianStart;
	root->u=medianEnd;
	root->list=NULL;
	root->left=leftNode;
	root->right=rightNode;
	leftNode->parent=root;
	rightNode->parent=root;


	//printf("Tree %d %d %d %d \n",low ,up ,medianStart,medianEnd );
	printf("3 Tree data %d %d\n",root->l,root->u);
	//printf("%d %d %d %d %d %d %d \n",low,up,n,length,level,medianStart,medianEnd);
	//scanf("%d",&as);
	//printf("Left %d %d \n",low,medianStart);
	//printf("Right %d %d \n",medianEnd,up);

	if(root->l==0 && root->u==0)
	{
		printf("***********************************************************************************************************************\n");
	}
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
	/*else
	{
		if()
	}
	else if(node->next->data > i)
	{
		List* curr=malloc(sizeof(List));
		curr->data = i;
		curr->next = node->next;
		node=curr;
	}
	else if(node->next==NULL)
	{
		List* curr=malloc(sizeof(List));
		curr->data = i;
		node->next=curr;
		curr->next=NULL;
	}
	else
		LIST_INSERT(node->next,i);*/
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
		printf("1>>>>>>> %d %d \n",root->l,root->u);
		LIST_MERGE(root->list,l,u,node->list);
		node->l=min(root->l,node->l);
		node->u=max(root->u,node->u);
	}	
	else if(root->u >=l && root->u <= u)//upper of root is inside range
	{
		printf("2>>>>>>> %d %d \n",root->l,root->u);
		printf("******%d %d \n",root->u,node->u);
		LIST_MERGE(root->list,l,u,node->list);
		node->l=l;
		
	}
	else if(root->l < u && root->l > l)//lower of root is inside range
	{
		printf("3>>>>>>> %d %d \n",root->l,root->u);
		printf("******%d %d \n",root->u,node->u);
		LIST_MERGE(root->list,l,u,node->list);
		node->u=u;
		
	}

	return;
}
int MERGE(Node* root,int l,int u,Node* node,Node* pare)
{

	int overlap=0;
	if(root==NULL)
		return 1;
	//printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++%d %d \n",root->l,root->u);
	/*if(pare==NULL)
		printf("Here if it %d %d \n\n",root->l,root->u);
	else
		printf("Here if it none %d %d %d %d \n\n",root->l,root->u,pare->l,pare->u);
*/
	//printf("YET TO BE SUPER CASE %d %d \n\n",root->l,root->u);
	if((root->u >= l && root->u <= u)||(root->l < u && root->l > l))//upper of interval is inside range or lower of interval is inside range
	{
		//printf("SUPER CASE %d %d \n\n",root->l,root->u);
		overlap=1;
		//printf("Satya %d %d \n",root->l,root->u);
			
		//ADD_MERGE(root,l,u,node);

		if((root->l >= l) && (root->u<= u))
		{
			if(node==NULL)
			{
				node=root;
				pare = root;
				//printf("\n\n\nHolster\n\n\n");
			}


			//parent = root;
			printf("1>>>>>>> %d %d \n",root->l,root->u);
			LIST_MERGE(root->list,l,u,node->list);
			node->l=min(root->l,node->l);
			node->u=max(root->u,node->u);
			root->l=0;
			root->u=0;
		}	
		else if(root->u >=l && root->u <= u)//upper of root is inside range LEFT CASE
		{
			overlap=0;
			if(node==NULL)
			{
				node=root;
				pare = root;
				//printf("\n\n\nHolster\n\n\n");
			}


			Node* tempNode = malloc(sizeof(Node));
			printf("2>>>>>>> %d %d \n",root->l,root->u);
			printf("******%d %d \n",root->u,node->u);
			LIST_MERGE(root->list,l,u,node->list);
			node->l=l;

			//new node things
			tempNode->u=l;
			tempNode->l=root->l;
			tempNode->list=NULL;
			tempNode->left=root->left;
			tempNode->right = NULL;
			tempNode->parent= pare;
			pare->left = tempNode;
			if(tempNode->left!=NULL)
				tempNode->left->parent = tempNode;

			printf("~~~~~~~~~~######### %d %d ~~~~~~~~~pare %d %d %d %d\n\n",tempNode->l,tempNode->u,pare->l,pare->u,pare->left->l,pare->left->u);
			
		}
		else if(root->l < u && root->l > l)//lower of root is inside range RIGHT CASE
		{
			overlap=0;

			if(node==NULL)
			{
				node=root;
				pare = root;
				//printf("\n\n\nHolster\n\n\n");
			}


			Node* tempNode = malloc(sizeof(Node));
			printf("3>>>>>>> %d %d \n",root->l,root->u);
			printf("******%d %d \n",root->u,node->u);
			LIST_MERGE(root->list,l,u,node->list);
			//printf("^^^^%d %d %d %d \n",root->l,root->u,tempNode->l,tempNode->u);

			
			//printf("^^^^%d %d %d %d \n",root->l,root->u,tempNode->l,tempNode->u);
			//new node things
			tempNode->l=u;
			tempNode->u=root->u;
			node->u=u;
			tempNode->list=NULL;
			tempNode->left=NULL;
			tempNode->right = root->right;
			if(tempNode->right!=NULL)
				tempNode->right->parent = tempNode;
			pare->right = tempNode;

			// tempNode->l=777;
			// tempNode->u=999;

			printf("~~~~~~~~~~&&&&&&&&&&%d %d %d %d ~~~~~~~~~pare %d %d %d %d \n\n",tempNode->l,tempNode->u,root->l,root->u,pare->l,pare->u,pare->right->l,pare->right->u);
			
		}
	}
	int ret1,ret2;
	//printf("right called \n");
	ret2 = MERGE(root->right,l,u,node,pare);
	//printf("left called \n");
	ret1 = MERGE(root->left,l,u,node,pare);
	
	//printf("Gargantuan ");
	
	/*if(!ret1 && pare!=NULL)
	{
		//printf("%d %d \n",root->l,root->u);
		//if(pare==NULL)
			//printf("misery all around \n");
		pare->left = root->left;
	}
	
	if(!ret2 && pare!=NULL)
	{
		// printf("%d %d \n",root->l,root->u);
		// if(pare==NULL)
		// 	printf("misery all around \n");
		pare->right = root->right;
	}
	//printf("gone \n");*/
	//printf("------------------------------------------------------------------------------------------%d %d \n",root->l,root->u);

	/*if(ret1==1 && ret2==1)
	{
		overlap = 1;
	}*/

	/*if(root->right!=NULL)
		if(root->right->l==0&&root->right->u==0)
			root->right=NULL;
	if(root->left!=NULL)
		if(root->left->l==0&&root->left->u==0)
			root->left=NULL;*/
			
	/*if(ret1==1 && ret2==1)//(overlap==1)
	{
		if(root->parent!=NULL)
			root->parent->
		//printf("%d((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((( %d %d\n",overlap,root->l,root->u);
		root->right=NULL;
		root->left=NULL;
		if(overlap==1)
			return 1;
	}*/
	
	return 0;
	
}

void CHANGE_TREE(Node* root,int l,int u,int n)
{
	int i,live;
	int length= ceil((u-l)/(n*1.00));
	//MERGE(root,65-,65,NULL,NULL);
	for(i=u+1;i>1;i=i-length)
	{
		MERGE(root,i-length,i,NULL,NULL);
		structure(root,2);
		printf("__%d %d_______________________________________________________________________________________\n",i-length,i);
		//scanf("%d",&live);
	}

}

int main()
{
	int l=1,up=32,n=8,i;
	//printf("%d %d %d  \n",l,up,n);
	int length= ceil((up-l)/(n*1.00));
	Node* root=malloc(sizeof(Node));
	//int upper=16;
	//printf("%d %d %d  \n",l,upper,n);
	printf(">> %d \n",length);
	_CREATE_INTERVAL_TREE(root,l,up+1,n,length,1);

	structure(root,2);

	for(i=l;i<=up;i++)
	{
		INSERT(root,i);
	}
	// INSERT(root,5);
	// INSERT(root,1);
	// INSERT(root,2);
	// INSERT(root,3);
	// INSERT(root,5);

	//structureList(root,2);


	// printf("\n\nMERGE PROCESSS STARTED \n");
	// MERGE(root,1,9,NULL,NULL);
	MERGE(root,16,25,NULL,NULL);
	//structure(root,2);

	//CHANGE_TREE(root,l,up,4);
	structure(root,2);

	//structureList(root,2);



	//structureList(root,2);

}