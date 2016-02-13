#include <stdio.h>
#include <stdlib.h>


struct pair
{
	double x,y;
};

struct Building
{
	double start,end,height;
};

typedef double LD;
typedef struct Building Bldg;
typedef struct pair Pair;

int jsd;

double max(double a,double b)
{
	if(a>b)
		return a;
	else 
		return b;
}
double min(double a,double b)
{
	if(a>b)
		return b;
	else 
		return a;
}

Pair* Skyline_1(Bldg *rawBldg,long long lIdx,long long rIdx,long long *N)
{
	Pair * mergedSky=malloc(sizeof(Pair)*2);

	//printf("indexes %lld %lld \n",lIdx,rIdx);
	int i;
	//printf("values %f %f %f \n",rawBldg[lIdx].start,rawBldg[lIdx].height,rawBldg[lIdx].end);

	mergedSky[0].x=rawBldg[lIdx].start;

	mergedSky[0].y=rawBldg[lIdx].height;

	mergedSky[1].x=rawBldg[lIdx].end;
	mergedSky[1].y=(double)0;

	//printf("return values %f %f %f  \n",rawBldg[lIdx].start ,rawBldg[lIdx].height , rawBldg[lIdx].end);
	//printf("Skyline_1 return values %lld %lld %lld %lld \n",mergedSky[0].x , mergedSky[0].y , mergedSky[1].x , mergedSky[1].y);

	return mergedSky;

}
Pair* mergeSkyline(Pair* leftSky,Pair* rightSky,long long len1,long long len2,long long *N)
{
	//printf("mergeSkyline called \n");
	//idx3 will contain length of mergedSky at end
	//long long len1,len2;
	//len1=sizeof(leftSky)/sizeof(leftSky[0]);
	//len2=sizeof(rightSky)/sizeof(rightSky[0]);
	long long idx1=0,idx2=0,idx3=0;
	Pair *mergedSky = malloc(sizeof(Pair)*(len1+len2));
	double prev1=0,prev2=0,Max=0,X;
	
	//printf("len1  len2 %lld %lld \n",len1,len2);



	for(;leftSky[idx1].x<rightSky[idx2].x && idx1<len1;idx1++)
	{
		//printf("Here1 \n");
		mergedSky[idx3].x=leftSky[idx1].x;
		mergedSky[idx3].y=leftSky[idx1].y;
		idx3++;
		prev1 = leftSky[idx1].y;
		//printf("Added values %lld %lld %lld \n \n",idx3,leftSky[idx1].x,leftSky[idx1].y);
	}
	//printf("data %lld %lld %lld %lld \n",idx1,len1,idx2,len2);
	while(idx1<len1 && idx2<len2)
	{
		//printf("Here2 \n");
		//printf("Here2 %lld %lld \n",leftSky[idx1].x,rightSky[idx2].x);
		if(leftSky[idx1].x < rightSky[idx2].x)
		{
			Max=max(leftSky[idx1].y,prev2);
			X = leftSky[idx1].x;
			prev1 = leftSky[idx1].y;
			idx1++;
			//printf("^^^^^^^^^^case 1 %lld %lld \n",idx1,Max);
			/*if(mergedSky[idx3].y<leftSky[idx1].y)
			{
				mergedSky[idx3].x=leftSky[idx1].x;
				mergedSky[idx3].y=leftSky[idx1].y;
				idx3++;
				idx1++;
			}*/
		}
		else if(leftSky[idx1].x > rightSky[idx2].x)
		{
			Max = max(prev1,rightSky[idx2].y);
			X = rightSky[idx2].x;
			prev2 = rightSky[idx2].y;
			idx2++;
			//printf("^^^^^^^^^^case 2\n");
			/*if(mergedSky[idx3].y<rightSky[idx1].y)
			{
				mergedSky[idx3].x=rightSky[idx1].x;
				mergedSky[idx3].y=rightSky[idx1].y;
				idx3++;
				idx2++;
			}*/
		}
		else
		{
			Max = max(leftSky[idx1].y,rightSky[idx2].y);
			X = rightSky[idx2].x;
			prev1 = leftSky[idx1].y;
			prev2 = rightSky[idx2].y;
			idx1++;
			idx2++;
			//printf("^^^^^^^^^^case 3\n");
		}

		if(mergedSky[idx3-1].y!=Max)
		{
			mergedSky[idx3].x = X;
			mergedSky[idx3].y = Max;
			idx3++;
			//printf("Added values %lld %lld %lld \n \n",idx3,X,Max);
		}
		else
			continue;
	//printf("this is same \n \n");
	}
	for(;idx1<len1;idx1++)
	{
		//printf("Here3 \n");
		mergedSky[idx3].x=leftSky[idx1].x;
		mergedSky[idx3].y=leftSky[idx1].y;
		idx3++;
	}
	for(;idx2<len2;idx2++)
	{
		//printf("Here3 \n");
		mergedSky[idx3].x=rightSky[idx2].x;
		mergedSky[idx3].y=rightSky[idx2].y;
		idx3++;
	}

	N[0]=idx3;
	int i;
	/*for(i=0;i<idx3;i++)
	{
		printf("merge valuesvalues returned %lld %lld %lld\n",mergedSky[i].x , mergedSky[i].y,idx3);
		printf("len1 and len2 for merge  %lld %lld \n",len1,len2);
	}*/

	//printf("returning merged sky \n");
	return mergedSky;
}

Pair * Skyline(Bldg * rawBldg,long long lIdx,long long rIdx,long long *N)
{
	//printf("lIdx rIdx %lld %lld \n",lIdx,rIdx);
	Bldg * rightBldg,leftBldg;
	Pair * mergedSky;
	Pair * leftSky,*rightSky;
	long long midIdx = (lIdx+rIdx)/2,Nl,Nr;

	int i;
	/*for(i=lIdx;i<=rIdx;i++)
	{
		printf("Skyline for %f %f %f \n",rawBldg[i].start,rawBldg[i].end,rawBldg[i].height);
	}*/

	if(rIdx==lIdx)
		{
			//printf("Skyline_1 called \n");
			mergedSky = Skyline_1(rawBldg,lIdx,rIdx,N);
			*N=2;
			/*for(i=0;i<*N;i++)
			{
				printf("Skyline_1 gotcha values %d %lld %lld  \n \n",i,mergedSky[i].x,mergedSky[i].y);
			}*/
		}
	else
	{
		//printf("left skyline called\n");
		leftSky = Skyline(rawBldg,lIdx,midIdx,&Nl);
		/*for(i=0;i<Nl;i++)
		{
			printf("#################leftSky ret values %d %lld %lld \n \n",i,leftSky[i].x,leftSky[i].y);
		}*/
		//printf("right skyline called\n");
		rightSky = Skyline(rawBldg,midIdx+1,rIdx,&Nr);
		//printf("rightSky values %lld %lld %lld %lld %lld\n",Nr,rightSky[0].x,rightSky[0].y,rightSky[1].x,rightSky[1].y);
		//printf("mergeSkyline called\n");
		mergedSky = mergeSkyline(leftSky,rightSky,Nl,Nr,N);
	}
	
	return mergedSky;


}

void populate(Bldg* A,long long N)
{
	long long i;
	double a,b;
	for(i=0;i<N;i++)
	{
		A[i].height=rand()%1000;
		a=rand()%1000;
		b=rand()%1000;
		A[i].start=min(a,b);
		A[i].end=max(a,b);
	}

	
}

int compare(const void* p,const void* q)
{
	const Bldg *a=p,*b=q;
	if(a->start>b->start)
		return 1;
	else
		return -1;
	/*returns >0 if a>b*/
}

int main()
{

	//Bldg A[]={{1,1,1},{2,2,2},{3,3,3},{4,4,4},{5,5,5}};
	//Bldg A[]={{1,2,3}};
	//Bldg A[]={{1,4,3},{3,5,1}};
	//Bldg A[]={{1,4,3},{3,5,1},{5,7,3},{6,8,4}};

	Pair *retSky;
	long long i,N=4;

	scanf("%lld",&N);
	Bldg* A=malloc(sizeof(Bldg)*N);
	populate(A,N);
	qsort(A,N,sizeof(Bldg),compare);

	printf("printing buildings \n");
	for(i=0;i<N;i++)
		{
			printf("%f,%f,%f \n",A[i].start,A[i].end,A[i].height);
		}
	printf("\n\n");

	retSky=Skyline(A,0,N-1,&N);
	printf("printing Skyline \n");
	for(i=0;i<N;i++)
	{
		printf("%f %f  \n",retSky[i].x,retSky[i].y);
	}
}

	























	#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node
{
    int data;
    struct node *right,*left;
};

typedef struct node Node;

int p =1;
//int level=1;
void createTree(Node* root,int N,int level)
{
	//printf("Here  %d \n",p);
	if(N>0)
	{
		root->data = p++;
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

	if(LN>0)
	{
		printf("creating left  %d(%d) \n",LN,level);
		createTree(root->left,LN,level+1);
	}
	else
		root->left = NULL;
	
	if(RN>0)
	{
		printf("creating right %d(%d) \n",RN,level);
		createTree(root->right,RN,level+1);
	}
	else
		root->right = NULL;

	return;
}

void printTree(Node* root,int level)
{
	//printf("p =  %d \n",p++);
	if(root==NULL)
		return;
	printf("-%d(%d) ",root->data,level);
	//printf("-%d %d %d \n",root->data,root->left->data,root->right->data);
	printTree(root->left,level+1);
	printTree(root->right,level+1);
	

	return;
	

}

int main()
{
	Node *treeRoot = (Node*)malloc(sizeof(Node));;

	printf("createTree \n");
	createTree(treeRoot,33,2);
	p=1;
	printf("printfTree \n");
	printTree(treeRoot,1);

}










////////////////////

////////////

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
		mineMax.sum=INT_MIN;
		mineMax.top=NULL;
		mineMax.bottom=NULL;

		return mineMax;
		//printf("Hodor2 \n");

	}

	leftTreeMax=maxPath(root->left);
	rightTreeMax=maxPath(root->right);

	if(leftTreeMax.sum>rightTreeMax.sum)
	{

		if(leftTreeMax.sum + root->data <= root->data)
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
		if(rightTreeMax.sum + root->data <= root->data)
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