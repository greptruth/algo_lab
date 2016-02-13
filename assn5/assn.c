#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

struct node
{
    int data;
    struct node *right,*left,*parent;
};
typedef struct node Node;

struct triplet
{
	struct node *left,*top,*right;
	int sum;
};
typedef struct triplet Triplet;
struct doublet
{
	struct node *top,*bottom;
	int sum;
};
typedef struct doublet Doublet;
Triplet Max;
//Doublet MaX;




int p =1;
//int level=1;
void createTree(Node* root,int N,int level)
{
	//printf("Here  %d \n",p);
	if(N>0)
	{
		root->data = rand()%201 - 100;
		//printf("data = %d \n",root->data);
		root->left = NULL;
		root->right = NULL;
	}
	else
		return;
	if(N==1)
		return;

	float div = 0.4 + (rand()%20)/100.0;
	div= 0.5;
	//printf("div = %f \n",div);
	Node* leftNode = (Node*)malloc(sizeof(Node));
	Node* rightNode = (Node*)malloc(sizeof(Node));

	leftNode->data = 777;
	rightNode->data = 777;

	leftNode->right=NULL;
	leftNode->left=NULL;
	rightNode->left=NULL;
	rightNode->right=NULL;

	root->left = leftNode;
	root->right = rightNode;


	int LN=ceil((N-1)*div>=1);
	int RN=floor((N-1)*(1.0-div)>=1);

	if((int)ceil((N-1)*div)>=1)
	{
		//printf("creating left  %d(%d) \n",(int)ceil((N-1)*div),level);
		createTree(root->left,(int)ceil((N-1)*div),level+1);
	}
	else
		root->left = NULL;
	
	if((int)floor((N-1)*(1.0-div))>=1)
	{
		//printf("creating right %d(%d) \n",(int)floor((N-1)*(1.0-div)),level);
		createTree(root->right,(int)floor((N-1)*(1.0-div)),level+1);
	}
	else
		root->right = NULL;
	if(root->right!=NULL)
		root->right->parent = root;
	if(root->left!=NULL)
		root->left->parent = root;

	return;
}

void printTree(Node* root,int level)
{
	//printf("p =  %d \n",p++);
	if(root==NULL)
		return;
	printf("-%d ",root->data);
	//printf("-%d(%d) ",root->data,level);
	//printf("-%d %d %d \n",root->data,root->left->data,root->right->data);
	printTree(root->left,level+1);
	printTree(root->right,level+1);
	

	return;
	

}

void inorderTraversal(Node* root,int level)
{
	//printf("p =  %d \n",p++);
	if(root==NULL)
		return;
	
	//printf("-%d(%d) ",root->data,level);
	//printf("-%d %d %d \n",root->data,root->left->data,root->right->data);
	inorderTraversal(root->left,level+1);
	printf("%d ",root->data);
	inorderTraversal(root->right,level+1);
	

	return;
	

}

void preorderTraversal(Node* root,int level)
{
	//printf("p =  %d \n",p++);
	if(root==NULL)
		return;
	printf("%d ",root->data);
	//printf("-%d(%d) ",root->data,level);
	//printf("-%d %d %d \n",root->data,root->left->data,root->right->data);
	preorderTraversal(root->left,level+1);
	preorderTraversal(root->right,level+1);
	

	return;
	

}

void postorderTraversal(Node* root,int level)
{
	//printf("p =  %d \n",p++);
	if(root==NULL)
		return;
	
	//printf("-%d(%d) ",root->data,level);
	//printf("-%d %d %d \n",root->data,root->left->data,root->right->data);
	preorderTraversal(root->left,level+1);
	preorderTraversal(root->right,level+1);
	printf("%d ",root->data);
	

	return;
	

}

void maxLeaf(Node* root,int *max_sum,int sum,Node **theMaxLeaf)
{
	if(root==NULL)
		return;
	sum+=root->data;

	if(root->right==NULL&&root->left==NULL)
	{
		if(sum>*max_sum)
		{
			*max_sum=sum;
			*theMaxLeaf = root;
		}
	}

	maxLeaf(root->left,max_sum,sum,theMaxLeaf);
	maxLeaf(root->right,max_sum,sum,theMaxLeaf);
}

bool printLeafPath(Node* root,Node *theMaxLeaf)
{
	if(root==NULL)
		return false;
	if(root==theMaxLeaf )
	{
		printf("%d ",root->data);
		return true;
	}
	else if(printLeafPath(root->left,theMaxLeaf) || printLeafPath(root->right,theMaxLeaf))
	{
		printf("%d ",root->data);
		return true;
	}

	return false;

}

void maxLeafPath(Node* root)
{
	int max_sum=INT_MIN;
	Node* theMaxLeaf=malloc(sizeof(Node));

	maxLeaf(root,&max_sum,0,&theMaxLeaf);

	printLeafPath(root,theMaxLeaf);
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
    printf ( "%d\n", root->data );
    structure ( root->left, level + 1 );
  }
}


// Triplet MaxPath(Node *root)
// {
// 	if(root==NULL)
// 	{
// 		Triplet ret;//= malloc(sizeof(Triplet));
// 		ret.sum=INT_MIN;
// 		ret.left=NULL;
// 		ret.top=NULL;
// 		ret.right=NULL;
// 		return ret;

// 	}

// 	Triplet leftTreeMax,rightTreeMax,mineMax;
// 	leftTreeMax=MaxPath(root->left);
// 	rightTreeMax=MaxPath(root->right);

// 	/*if(leftTreeMax.sum<root->data && rightTreeMax.sum<root->data)
// 	{
// 		mineMax.sum=root->data;
// 		mineMax.left=root;
// 		mineMax.top=root;
// 		mineMax.right=root;
// 		storage(mineMax);//add checking in storage
// 		return mineMax;
// 	}*/
// 	if(leftTreeMax.sum>rightTreeMax.sum)
// 	{
// 		if(leftTreeMax.sum + root->data < root->data)
// 		{
// 			mineMax.sum=root->data;
// 			mineMax.left=root;
// 			mineMax.top=root;
// 			mineMax.right=root;
// 			storage(mineMax);//add checking in storage
// 			return mineMax;
// 		}

// 		mineMax.sum = leftTreeMax.sum + root->data;
// 		mineMax.left=leftTreeMax.left;
// 		mineMax.top=root;
// 		if(mineMax.sum>mineMax.sum+rightTreeMax.sum)
// 		{
// 			mineMax.right=root;
// 			storage(mineMax);
// 		}
// 		else
// 		{
// 			Max.right=rightTreeMax.right;
// 			storage(mineMax);
			
// 		}
// 	}
// 	else
// 	{
// 		if(rightTreeMax.sum + root->data < root->data)
// 		{
// 			mineMax.sum=root->data;
// 			mineMax.left=root;
// 			mineMax.top=root;
// 			mineMax.right=root;
// 			storage(mineMax);//add checking in storage
// 			return mineMax;
// 		}

// 		mineMax.sum = rightTreeMax.sum + root->data;
// 		mineMax.right = rightTreeMax.right;
// 		mineMax.top=root;
// 		if(mineMax.sum>mineMax.sum+leftTreeMax.sum)
// 		{
// 			mineMax.right=root;
// 			storage(mineMax);
// 		}
// 		else
// 		{
// 			Max.left=leftTreeMax.left;
// 			storage(mineMax);
			
// 		}
// 	}
// 	return mineMax;

// } 

void storage(Triplet got)
{
	Max.sum=got.sum;
	Max.left=got.left;
	Max.right=got.right;
	Max.top=got.top;
}

void storagE(Doublet got)
{
	if(Max.sum< got.sum)
	{
		Max.sum=got.sum;
		Max.left=got.bottom;
		Max.top=got.top;
		Max.right=NULL;
	}
}

void storaGE(int sum,Node* top,Node* left,Node* right)
{
	if(Max.sum<sum)
	{
		Max.sum=sum;
		Max.top=top;
		Max.left=left;
		Max.right=right;
	}

}


Doublet maxPath(Node *root)
{
	Doublet mineMax,leftTreeMax,rightTreeMax;

	/*if(root!=NULL)
		printf("Hodor1 %d \n",root->data);
	else
		printf("Hodor1 \n");*/	


	if(root==NULL)
	{
		//printf("Hodor2.0 \n");
		mineMax.sum=0;
		mineMax.top=NULL;
		mineMax.bottom=NULL;

		return mineMax;
		//printf("Hodor2 \n");

	}

	leftTreeMax=maxPath(root->left);
	rightTreeMax=maxPath(root->right);

	if(leftTreeMax.sum>rightTreeMax.sum)
	{

		if(leftTreeMax.sum <=0)
		{
			mineMax.sum=root->data;
			mineMax.top=root;
			mineMax.bottom=root;
			storagE(mineMax);
			//return mineMax;//
		}
		else
		{
			mineMax.sum = leftTreeMax.sum + root->data;
			mineMax.top=root;
			mineMax.bottom=leftTreeMax.bottom;
			storagE(mineMax);
			//return mineMax;//

		}
	}
	else
	{
		if(rightTreeMax.sum <=0)
		{
			mineMax.sum=root->data;
			mineMax.top=root;
			mineMax.bottom=root;
			storagE(mineMax);

		}
		else
		{
			mineMax.sum= rightTreeMax.sum + root->data;
			mineMax.top=root;
			mineMax.bottom=rightTreeMax.bottom;
			storagE(mineMax);

		}
	}

	storaGE(leftTreeMax.sum+root->data+rightTreeMax.sum,root,leftTreeMax.bottom,rightTreeMax.bottom);
	return mineMax;

}
void bottomUpPrint(Node* root)
{
	if(root==NULL ||root==Max.top)
		return;
	printf("%d ",root->data);
	bottomUpPrint(root->parent);
	
}

void topDownPrint(Node* root)
{
	if(root==NULL || root==Max.top)
		return;
	topDownPrint(root->parent);
	printf("%d ",root->data);
}
void printNode()
{
	Node* tempNode;
	// printf("Here satya \n");

	// printf("\n hsadkasd %d %d %d \n",Max.top->data,Max.left->data,Max.right->data);

	
	tempNode=Max.right;
	if(tempNode!=NULL)
	{
		bottomUpPrint(tempNode);
	}

	printf("%d ",Max.top->data);

	tempNode=Max.left;
	if(tempNode!=NULL)
	{
		topDownPrint(tempNode);
	}

	

	
}

int main(int argc,char *argv[])
{
	Node *treeRoot = (Node*)malloc(sizeof(Node));;
	treeRoot->parent=NULL;

	Max.left=NULL;
	Max.right=NULL;
	Max.top=NULL;
	Max.sum=INT_MIN;

	//printf("createTree \n");
	createTree(treeRoot,100,2);

	inorderTraversal(treeRoot,1);
	printf("\n\n");
	preorderTraversal(treeRoot,1);
	printf("\n\n");
	postorderTraversal(treeRoot,1);
	printf("\n\n");
	maxLeafPath(treeRoot);
	printf("\n\n");
	maxPath(treeRoot);
	printNode(treeRoot);
	printf("\n\n");

	/*p=1;
	printf("printfTree \n");
	printTree(treeRoot,1);*/

	/*if(argv[1][0]=='1')
	{
		printf("\ninorder treversal :\n");
		inorderTraversal(treeRoot,1);
	}

	if(argv[2][0]=='1')
	{
		printf("\n \npreorder treversal :\n");
		preorderTraversal(treeRoot,1);
	}

	if(argv[3][0]=='1')
	{
		printf("\n \npostorder treversal :\n");
		postorderTraversal(treeRoot,1);
	}
	if(argv[4][0]=='1')
	{
		printf("\n \nMax sum path from root to leaf \n");
		maxLeafPath(treeRoot);

		printf("\nSum of max sum path from root to leaf = %d \n",MaxPathSum(treeRoot));
	}
	
	if(argv[5][0]=='1')
	{
		maxPath(treeRoot);
		printf("\nSum of max sum path between any 2 nodes = %d \n",Max.sum);

		printf("Max sum path between any 2 nodes \n");
		printNode(treeRoot);
	}
	if(argv[6][0]=='1')
		structure(treeRoot,0);*/

	//**************************************************
	/*Node* tempNode;
	// tempNode=treeRoot->left->left->left;
	tempNode=treeRoot->left->right->left;
	while(tempNode!=Max.top || tempNode!=NULL)
	{
		printf("Here satya1 \n");
		printf("->%d \n",tempNode->data);
		tempNode=tempNode->parent;
	}*/
	//*******************************************************

	//printf("starting thing \n");

	

	//printf("finished what was started \n");


	
	

	

}







