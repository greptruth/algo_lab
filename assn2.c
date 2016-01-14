#include<stdio.h>
#include<stdlib.h>

int f=1,n;

void fill(int A[][50],int x,int y,int a,int b,int N)
{
	//printf("Recurse %d %d %d %d %d \n",x,y,a,b,N);
	int i,j;
	if(N == 2)
	{
		//printf("N=2 %d %d %d %d %d \n",x,y,a,b,N);
		if(a==x+1)
		{
			if(b==y+1)
			{
				//printf("Here using 1 \n");
				
				A[x][y]=A[x+1][y]=A[x][y+1]=1;
			}
			else if(b==y)
			{
				//printf("Here using 2 \n");
				
				A[x][y]=A[x][y+1]=A[x+1][y+1]=3;
			}
			else
			{
				printf("mess \n");
				exit(0);
			}
		}
		else if(a==x)
		{
			if(b==y+1)
			{
				//printf("Here using 3 \n");
				
				
				A[x][y]=A[x+1][y]=A[x+1][y+1]=2;
			}
			else if(b==y)
			{
				//printf("Here using 4 \n");
				
				A[x+1][y]=A[x][y+1]=A[x+1][y+1]=4;
			}
			else
			{
				printf("mess \n");
				exit(0);
			}
				
		
		}
		else
			{
				printf("mess \n");
				exit(0);
			}
		/*for(i=1;i<=n;++i)
		{
			for(j=1;j<=n;++j)
			{
				printf("%d  ",A[i][j]);
			}
			printf("\n");
		}*/

		return;

	}
	

		
	if(a >x + N/2-1)
	{
		//printf("a>N/2 %d %d %d %d %d \n",x,y,a,b,N);
		if(b > y+ N/2-1)
		{
			A[x-1+N/2][y-1+N/2]=A[N/2+x][y-1+N/2]=A[x-1+N/2][N/2+y]=1;
			int i,j;
			//printf("Here filling 1 \n");
			/*for(i=1;i<=N;++i)
			{
				for(j=1;j<=N;++j)
				{
					printf("%d  ",A[i][j]);
				}
				printf("\n");
			}*/
			fill(A,x,y,x-1+N/2,y-1+N/2,N/2);
			fill(A,N/2 +x,y,N/2 +x,y-1+N/2,N/2);
			fill(A,x,N/2+y,x-1+N/2,N/2+y,N/2);
			fill(A,N/2+x,N/2+y,a,b,N/2);
			
		}
		else
		{
			A[x-1+N/2][y-1+N/2]=A[N/2+x][N/2+y]=A[x-1+N/2][N/2+y]=2;
			int i,j;
			//printf("Here filling 2 \n");
			/*for(i=1;i<=N;++i)
			{
				for(j=1;j<=N;++j)
				{
					printf("%d  ",A[i][j]);
				}
				printf("\n");
			}*/
			fill(A,x,y,x-1+N/2,y-1+N/2,N/2);
			fill(A,N/2 +x,y,a,b,N/2);
			fill(A,x,N/2+y,x-1+N/2,N/2+y,N/2);
			fill(A,N/2+x,N/2+y,N/2+x,N/2+y,N/2);
			
		}
	}
	else
	{
		//printf("a<=N/2 %d %d %d %d %d \n",x,y,a,b,N);
		if(b>y + N/2-1)
		{
			A[N/2+x-1][N/2+y-1]=A[N/2+x][N/2+y-1]=A[N/2+x][N/2+y]=3;
			int i,j;
			//printf("Here filling 3 \n");
			/*for(i=1;i<=N;++i)
			{
				for(j=1;j<=N;++j)
				{
					printf("%d  ",A[i][j]);
				}
				printf("\n");
			}*/
			fill(A,x,y,x-1+N/2,y-1+N/2,N/2);
			fill(A,N/2 +x,y,N/2+x,y-1+N/2,N/2);
			fill(A,x,N/2+y,a,b,N/2);
			fill(A,N/2+x,N/2+y,N/2+x,N/2+y,N/2);
			
		}
		else
		{
			A[N/2+x][N/2+y-1]=A[N/2+x][N/2+y]=A[x-1+N/2][N/2+y]=4;
			int i,j;
			//printf("Here filling 4 \n");
			/*for(i=1;i<=N;++i)
			{
				for(j=1;j<=N;++j)
				{
					printf("%d  ",A[i][j]);
				}
				printf("\n");
			}*/
			fill(A,x,y,a,b,N/2);
			fill(A,N/2 +x,y,N/2 +x,y-1+N/2,N/2);
			fill(A,x,N/2+y,x-1+N/2,N/2+y,N/2);
			fill(A,N/2+x,N/2+y,N/2+x,N/2+y,N/2);
			
		}
	}

	/*printf("\n");
	for(i=1;i<=n;++i)
	{
		for(j=1;j<=n;++j)
		{
			printf("%d  ",A[i][j]);
		}
		printf("\n");
	}
	*/
	return;	
	
}


int main(int argc,char **argv)
{
	int A[50][50];
	int a,b,i,j,N,u,v;
	printf("Here \n");
	scanf("%d %d %d",&N,&a,&b);
	for(u=1;u<=N;u++)
	{
		for(v=1;v<=N;v++)
		{
			a=u;
			b=v;
			//printf("Here im %d %d %d \n",N,a,b);
			n=N;
			A[a][b] = 0;
			fill(A,1,1,a,b,N);
			printf("\n");
			for(i=1;i<=N;++i)
			{
				for(j=1;j<=N;++j)
				{
					printf("%d  ",A[i][j]);
				}
				printf("\n");
			}
		}
	}
	/*printf("Here im %d %d %d \n",N,a,b);
	n=N;
	A[a][b] = 0;
	fill(A,1,1,a,b,N);
	printf("\n");
	for(i=1;i<=N;++i)
	{
		for(j=1;j<=N;++j)
		{
			printf("%d  ",A[i][j]);
		}
		printf("\n");
	}*/
}

