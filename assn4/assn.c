#include <stdio.h>
#include <stdlib.h>

long long printSequence(long long N)
{
	
	long long a,b,m,i,ans;
	a=1;
	b=0;
	m=N;
	i=2;
	for(m;m>0;)
	{
		
		for(;i <= m;i+=2)
		{
			//if(N%2==0 &&  )
			ans =a*i+b;
			printf("%lld \n",a*i+b);
		}
		if(m%2!=0)
		{
			ans = a*1+b;
			printf("%lld \n",a*1+b);
		}	
		
		if(m%2==0)//n=2m even
		{
			
			//printf("            case 1\n");
			b = -a + b;
			a*=2;
			i=2;
			m=m/2;
		}
		else//n=2m+1 odd
		{
			
			//printf("              case 2\n");
			b= b +a;
			a*=2;
			i=2;
			m=m/2;
		}
	}
	return ans;
}

long long Sequence(long long N)
{
	long long a,b,m,i,ans;
	a=1;
	b=0;
	m=N;
	i=2;
	for(m;m>0;)
	{
		
		for(;i <= m;i+=2)
		{
			//if(N%2==0 &&  )
			ans =a*i+b;
			//printf(" %lld %lld %lld %lld %lld \n",m,i,a,b,a*i+b);
		}
		if(m%2!=0)
		{
			ans = a*1+b;
			//printf("^%lld %lld %lld %lld %lld \n",m,i,a,b,a*1+b);
		}	
		
		if(m%2==0)//n=2m even
		{
			
			//printf("            case 1\n");
			b = -a + b;
			a*=2;
			i=2;
			m=m/2;
		}
		else//n=2m+1 odd
		{
			
			//printf("              case 2\n");
			b= b +a;
			a*=2;
			i=2;
			m=m/2;
		}
	}
	return ans;
}

long long Formulae(long long N)
{
	long long i=1,r=0,m;
	m=N;
	while (N >>= 1) // unroll for more speed...
	{
  		r++;
	}
	i=1<<r;
	//printf("%lld %lld \n",r,m);
	return 2*(m-i) +1;
} 
int main(int argc,char *argv[])
{
	long long N,i;
	//scanf("%lld",&N);
	printf("%d \n",argc);
	printf("%d \n",atoi(argv[1]));

	switch(atoi(argv[1]))
	{
		case 1:
			scanf("%lld",&N);
			printSequence(N);
			break;
		case 2:
			for(i=1;i<1000;i++)
			{
				printf("%lld %lld %lld \n",i,Sequence(i),Formulae(i));
			}
			break;
		case 3:
			
			scanf("%lld",&N);
			printf("%lld %lld %lld \n",N,Sequence(N),Formulae(N));
			break;

	}
	




	
	


	
}