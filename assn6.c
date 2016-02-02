#include <stdio.h>
#include <stdlib.h>
#include <float.h>


struct pair
{
	double x,y;
};

struct Building
{
	double start,end,hs,he;
};

typedef double LD;
typedef struct Building Bldg;
typedef struct pair Pair;

int jsd;

double slope(Pair a,Pair b)
{
	if(a.x==b.x)
	{
		if(b.y>a.y)
			return DBL_MAX;
		else
			return -DBL_MAX;
	}
	else
		return (double)((b.y-a.y)/(b.x-a.x));
}

long long max(long long a,long long b)
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

int intersect(Pair a,Pair b,Pair c,Pair d)
{
	
	if((a.y<c.y && b.y>d.y) || (a.y>c.y && b.y<d.y))//if not intersects
		return 1;
	
	
	double m1,m2,off1,off2;
	Pair ret;
	m1=(b.y-a.y)/(b.x-a.x);
	m2=(d.y-c.y)/(d.x-c.x);
	off1=a.y/(m1*a.x);
	off2 = c.y/(m2*c.x);
	ret.x= (c.y-a.y -m2*c.x+m1*a.x)/(m1-m2);
	ret.y = m1*(ret.x-a.x) + a.y;
	if(ret.x>max(a.x,c.x) && ret.x<min(b.x,d.x))
		return 1;
	else return 0;
}

Pair predict(Pair a,Pair b,long long X)
{
	double m,off;
	Pair ret;
	m = (b.y-a.y)/(b.x-a.x);
	off = a.y/(m*a.x);
	ret.x = X;
	ret.y = m*(X - a.x) + a.y;
	//printf("_______Predict %f %f %f %f--- %f %f %f %f \n \n",m,off,ret.x,ret.y,a.x,a.y,b.x,b.y);
	return ret;

}
Pair ret;
Pair intersection(Pair a,Pair b,Pair c,Pair d)
{
	if(a.x==b.x)
		return predict(c,d,a.x);
	else if(c.x==d.x)
		return predict(a,b,c.x);
	printf(">>>%f %f %f %f %f %f %f %f \n" ,a.x,a.y,b.x,b.y,c.x,c.y,d.x,d.y);
	double m1,m2,off1,off2;
	
	m1=(b.y-a.y)/(b.x-a.x);
	m2=(d.y-c.y)/(d.x-c.x);
	off1=a.y/(m1*a.x);
	off2 = c.y/(m2*c.x);
	//ret.x = (off1-off2)/(m2-m1);
	ret.x= (c.y-a.y -m2*c.x+m1*a.x)/(m1-m2);
	ret.y = m1*(ret.x-a.x) + a.y;
	printf("%f %f %f %f \n",ret.x,ret.y,m1,m2);
	return ret;

}
Pair higher(Pair a,Pair b)
{
	Pair ret;
	if(a.y>b.y)
	{
		ret.x=a.x;
		ret.y=a.y;
	}
	else
	{
		ret.x=b.x;
		ret.y=b.y;
	}
	return ret;
}

Pair* Skyline_1(Bldg *rawBldg,long long lIdx,long long rIdx,long long *N)
{
	Pair * mergedSky=malloc(sizeof(Pair)*3);

	//printf("indexes %lld %lld \n",lIdx,rIdx);
	int i;
	//printf("values %f %f %f \n",rawBldg[lIdx].start,rawBldg[lIdx].height,rawBldg[lIdx].end);

	mergedSky[0].x=(long long)rawBldg[lIdx].start;

	mergedSky[0].y=(long long)rawBldg[lIdx].hs;

	mergedSky[1].x=(long long)rawBldg[lIdx].end;
	mergedSky[1].y=(long long)rawBldg[lIdx].he;

	mergedSky[2].x=(long long)rawBldg[lIdx].end;
	mergedSky[2].y=0;

	//printf("return values %f %f %f  \n",rawBldg[lIdx].start ,rawBldg[lIdx].height , rawBldg[lIdx].end);
	//printf("Skyline_1 return values %f %f %f %f \n",mergedSky[0].x , mergedSky[0].y , mergedSky[1].x , mergedSky[1].y);

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

	//printf("****************Here before \n");
	Pair *mergedSky = malloc(sizeof(Pair)*(len1+len2)*2);
	//long long prev1=0,prev2=0,Max=0,X;
	Pair prev2,prev1,Max,ret;
	prev1.x=prev2.x=prev1.y=prev2.y=0;

	
	//printf("len1  len2 %lld %lld \n",len1,len2);



	for(;leftSky[idx1].x<rightSky[idx2].x && idx1<len1;idx1++)
	{
		//printf("Here1 \n");
		//printf()
		mergedSky[idx3].x=leftSky[idx1].x;
		mergedSky[idx3].y=leftSky[idx1].y;
		idx3++;
		prev1.y = leftSky[idx1].y;
		prev1.x = leftSky[idx1].x;
		//printf("Added values over here %lld %f %f \n \n",idx3,leftSky[idx1].x,leftSky[idx1].y);
	}
	if(1)
	{
		//printf("I'm here \n\n");
		Pair temp;
		temp = predict(prev1,leftSky[idx1],rightSky[idx2].x);
		//printf("insider %f %f \n",leftSky[idx1].x,leftSky[idx1].y);
		//culprit
		if(rightSky[idx2].y>temp.y)
		{
			mergedSky[idx3] = temp;
			if(mergedSky[idx3].y < 0)
				mergedSky[idx3].y=0;
			idx3++;
			mergedSky[idx3].x = temp.x;
			mergedSky[idx3].y = rightSky[idx2].y;
			idx3++;
			
		}
		prev2 = rightSky[idx2];
		idx2++;
		//printf("Initiated 2nd skyline %lld %f %f \n ",idx3,rightSky[idx2-1].x,rightSky[idx2-1].y);
		//printf("Initiated 2nd skyline %lld %f %f \n \n",idx3,mergedSky[idx3-1].x,mergedSky[idx3-1].y);
			
	}
	//printf("data %lld %lld %lld %lld \n",idx1,len1,idx2,len2);
	while(idx1<len1 && idx2<len2)
	{
		//printf("Here2 %f %f \n",leftSky[idx1].x,rightSky[idx2].x);
		if(leftSky[idx1].x < rightSky[idx2].x)
		{
			if(intersect(prev1,leftSky[idx1],prev2,rightSky[idx2]))
			{
				ret = intersection(prev1,leftSky[idx1],prev2,rightSky[idx2]);
				printf("++++++++++++Debug %f %f %lld %lld \n",ret.x,ret.y,idx1,idx2);
				//printf("%f %f %f %f %f %f %f %f \n\n",prev1.x,prev1.y,leftSky[idx1].x,leftSky[idx1].y,prev2.x,prev2.y,rightSky[idx2].x,rightSky[idx2].y);
			}
			else
			{
				ret = higher(leftSky[idx1],rightSky[idx2]);
				printf("++++++++++++Debug %f %f \n",ret.x,ret.y);
			}
			prev1.x=leftSky[idx1].x;
			prev1.y=leftSky[idx1].y;
			idx1++;
			/*Max=max(leftSky[idx1].y,prev2);
			X = leftSky[idx1].x;
			prev1 = leftSky[idx1].y;
			idx1++;*/
			//printf("^^^^^^^^^^case 1 %lld \n",idx1);
			
		}
		else if(leftSky[idx1].x > rightSky[idx2].x)
		{
			if(intersect(prev1,leftSky[idx1],prev2,rightSky[idx2]))
			{
				printf("%%%%%%%%%%%%%% \n");
				ret = intersection(prev1,leftSky[idx1],prev2,rightSky[idx2]);
				printf("---++++++++++++Debug %f %f %lld %lld \n",ret.x,ret.y,idx1,idx2);
			}
			else
			{
				ret = higher(leftSky[idx1],rightSky[idx2]);
				printf("++++++++++++Debug %f %f \n",ret.x,ret.y);
			}
			prev2.x=rightSky[idx2].x;
			prev2.y=rightSky[idx2].y;
			idx2++;
			/*Max = max(prev1,rightSky[idx2].y);
			X = rightSky[idx2].x;
			prev2 = rightSky[idx2].y;
			idx2++;
			printf("^^^^^^^^^^case 2\n");
			*/
			//printf("^^^^^^^^^^case 2 %lld \n",idx2);
		}
		else
		{
			ret = higher(leftSky[idx1],rightSky[idx2]);
			prev1.x=leftSky[idx1].x;
			prev1.y=leftSky[idx1].y;
			idx1++;
			/*prev2.x=leftSky[idx2].x;
			prev2.y=leftSky[idx2].y;
			idx2++;*/
			/*Max = max(leftSky[idx1].y,rightSky[idx2].y);
			X = rightSky[idx2].x;
			prev1 = leftSky[idx1].y;
			prev2 = rightSky[idx2].y;
			idx1++;
			idx2++;
			printf("^^^^^^^^^^case 3\n");*/
			//printf("^^^^^^^^^^case 3 %lld \n",idx1);
		}
		if(mergedSky[idx3-1].y==ret.y && mergedSky[idx3-1].x==ret.x)
		{
			printf("matching values terminated \n");
		}
		else if((mergedSky[idx3-1].y!=ret.y || mergedSky[idx3-1].y!=ret.x) || ret.x!=0)
		{
			mergedSky[idx3].x = ret.x;
			mergedSky[idx3].y = ret.y;
			if(mergedSky[idx3-1].y==ret.y)
				printf("y matched \n");
			if(mergedSky[idx3-1].x==ret.x)
				printf("x matched \n");
			idx3++;

			//printf("Added values %lld %f %f \n \n",idx3,ret.x,ret.y);
		}
		else
			printf("this is same \n \n");
	}
	for(;idx1<len1;idx1++)
	{
		if((mergedSky[idx3-1].x==leftSky[idx1].x && mergedSky[idx3-1].y==leftSky[idx1].y) || leftSky[idx1].x==0)
			continue;
		mergedSky[idx3].x=leftSky[idx1].x;
		mergedSky[idx3].y=leftSky[idx1].y;
		idx3++;
	}
	for(;idx2<len2;idx2++)
	{
		if((mergedSky[idx3-1].x==rightSky[idx2].x && mergedSky[idx3-1].y==rightSky[idx2].y) || rightSky[idx2].x==0)
			continue;
			
		mergedSky[idx3].x=rightSky[idx2].x;
		mergedSky[idx3].y=rightSky[idx2].y;
		idx3++;
		//printf("O'oh %lld %lld %f %f\n \n",idx2,len2,rightSky[idx2].x,rightSky[idx2].y);
	}

	N[0]=idx3;
	int i;
	for(i=0;i<idx3;i++)
	{
		//printf("merge valuesvalues returned %f %f %lld \n",mergedSky[i].x , mergedSky[i].y,idx3);
		//printf("len1 and len2 for merge  %lld %lld \n",len1,len2);
	}
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
			*N=3;
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
		A[i].hs=rand()%1000;
		A[i].he=rand()%1000;
		a=rand()%1000;
		b=rand()%1000;
		A[i].start=min(a,b);
		A[i].end=max(a,b);
	}

	/*for(i=0;i<N;i++)
	{
		printf("%f %f %f %f\n",A[i].start,A[i].end,A[i].hs,A[i].he);
	}*/
	//scanf("%lf",&a);
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

Pair* append(Pair* a,long long N)
{
	Pair* ret=malloc(sizeof(Pair)*(N+1));
	long long i=1;
	ret[0].x = a[0].x;
	ret[0].y=0;
	for(;i<N+1;i++)
	{
		ret[i]=a[i-1];
	}
	
	return ret;
}
//Pair hull[10];
Pair* convexHull(Pair *Points,long long *N)
{
	Pair* hull=malloc(sizeof(Pair)*(*	N));
	
	double p,q;
	long long i=2,idx=1;
	/*printf("I got it0 \n");
	printf("%lld \n",*N);
	printf("%f %f %d \n",hull[0].x,hull[0].y,sizeof(hull)/sizeof(hull[0]));
	*/
	hull[0]=Points[0];
	hull[1]=Points[1];

	/*printf("ab to ho ja \n");
	for(i=0;i<*N;i++)
	{
		printf("%f %f \n",Points[i].x,Points[i].y);
	}*/
	//printf("N value %lld \n",*N);
	while(i<*N)
	{
		//printf("points %f %f \n",Points[i].x,Points[i].y);
		/*printf("I got it1 %lld %lld \n",i,idx);
		if(slope(hull[idx],Points[i]) <= slope(hull[idx-1],hull[idx]))
		{
			printf("doing this %f %f \n",Points[i].x,Points[i].y);
			printf("%f %f \n",slope(hull[idx-1],hull[idx]),slope(hull[idx],Points[i]));
			idx++;
			hull[idx]=Points[i];
		}
		else
		{
			printf("doing that %f %f \n",Points[i].x,Points[i].y);
			//hull[idx]=Points[i];
			idx--;
			i--;
		}
		i++;*/
		p=slope(hull[idx-1],hull[idx]);
		q=slope(hull[idx],Points[i]);
		if(idx==0||Points[i].y==0)
		{
			idx++;
			hull[idx]=Points[i];
			//printf("1a1 \n");
		}
		else if(hull[idx].y==0)
		{
			idx++;
			hull[idx]=Points[i];
		}
		else if((p>0 && q<0)||(p<0&&q>0))
		{
			//printf("1b1 \n");
			if(q<p)
			{
				idx++;
				hull[idx]=Points[i];
			}
			else
			{
				idx--;
			}
		}
		else if(p<0)
		{
			//printf("1c1 \n");
			idx--;
		}
		else if (p>0)
		{
			//printf("1d1 \n");
			idx++;
			hull[idx]=Points[i];
		}
		i++;
	}
	//printf("good \n");
	*N=idx+1;
	return hull;
}

int main()
{

	//Bldg A[]={{1,1,1},{2,2,2},{3,3,3},{4,4,4},{5,5,5}};
	//Bldg A[]={{1,2,3,4}};
	//Bldg A[]={{1,4,10,4},{2,6,20,12}};
	//Bldg A[]={{1,4,10,4},{2,6,20,12},{6,8,16,60},{7,8,200,100}};
	//long long N=4;
	//Bldg A[]={{15,77,87,83},{86,92,35,93}};

	Pair *retSky;
	long long i,N=2;

	//create buildings
	scanf("%lld",&N);
	Bldg* A=malloc(sizeof(Bldg)*N);
	populate(A,N);
	//printf("%lld",N);
	//sort buildings by start x
	
	qsort(A,N,sizeof(Bldg),compare);
	//printf("\n \n \n");
	for(i=0;i<N;i++)
		printf("%f %f %f %f \n",A[i].start,A[i].end,A[i].hs,A[i].he);
	printf("\n \n \n");
	
	//create skyline
	retSky=Skyline(A,0,N-1,&N);
	//append last ground point
	retSky=append(retSky,N);

	//print the Skyline without hull
	printf("printing skyline \n");
	N=N+1;
	for(i=0;i<N;i++)
	{
		printf("%f %f  \n",retSky[i].x,retSky[i].y);
	}

	//test data for hull only
	/*Pair *forHull,hullData[]={{1,0},{1,10},{2,14},{3,9},{4,20},{5,8},{6,18},{7,21},{8,16},{9,11},{9,0}};
	forHull=hullData;
	printf("hello \n");
	N=10;
	forHull = convexHull(forHull,&N);
	for(i=0;i<N;i++)
	{
		printf("%f %f \n",forHull[i].x,forHull[i].y);
	}*/

	Pair *forHull;

	forHull = convexHull(retSky,&N);
	printf("\n \n printing convex hull of skyline \n");
	for(i=0;i<N;i++)
	{
		printf("%f %f \n",forHull[i].x,forHull[i].y);
	}

	
}

	
