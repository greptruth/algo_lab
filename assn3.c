#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>

struct Point
{
	double x,y;
};

typedef struct Point point;

int compareX(const void* p,const void* q)
{
	const point *a=p,*b=q;
	if(a->x>b->x)
		return 1;
	else
		return -1;
	/*returns >0 if a>b*/
}

int compareY(const void* p,const void* q)
{
	const point *a=p,*b=q;
	if(a->y>b->y)
		return 1;
	else
		return -1;
	/*returns 1 if a>b*/
}

double distEucd(point a,point b)
{
	double a1=(a.x-b.x)*(a.x-b.x), a2=pow((a.y-b.y),2);
	double temp=sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
	//printf("%f %f %f %f %f %f %f\n", temp, a.x,a.y,b.x,b.y, a1, a2);
	return(sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)));
}
double min(double x,double y)
{
	if(x<y)
		return(x);
	return(y);
}
float bruteForce(point *P, long long N,point *u,point *v)
{
    double min = DBL_MAX;
    long long i,j;
    for (i = 0; i < N; ++i)
        for (j = i+1; j < N; ++j)
            if (distEucd(P[i], P[j]) < min)
            {
                min = distEucd(P[i], P[j]);
                u[0].x=P[i].x;u[0].y=P[i].y;
                v[0].x=P[j].x;v[0].y=P[j].y;
            }
    return min;
}

float stripClosest(point *strip, int size, float d,point *u,point *v)
{
    float min = d;  // Initialize the minimum distance as d
 
    qsort(strip, size, sizeof(point), compareY); 
    long long i,j;
 
    // Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    for (i = 0; i < size; ++i)
        for (j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (distEucd(strip[i],strip[j]) < min)
            {
                min = distEucd(strip[i], strip[j]);
                u[0].x=strip[i].x;u[0].y=strip[i].y;
                v[0].x=strip[j].x;v[0].y=strip[j].y;
            }
 
    return min;
}
 

float closest(point *A,long long N,point *u,point *v)
{
	if(N<3)
	{
		return bruteForce(A,N,u,v);
	}

	long long mid=N/2;
	point midPoint = A[mid];
	point a,b,r,s;
	long long i,j;


	double dl = closest(A, mid,&a,&b);
    double dr = closest(A + mid, N-mid,&r,&s);
    double d = min(dl, dr);
    if(dl<dr)
    {
    	u[0].x=a.x;u[0].y=a.y;
    	v[0].x=b.x;v[0].y=b.y;
    }
    else
    {
    	u[0].x=r.x;u[0].y=r.y;
    	v[0].x=s.x;v[0].y=s.y;
    }

    point strip[N];
    j=0;
    for (i = 0; i < N; i++)
        if (abs(A[i].x - midPoint.x) < d)
        {
            strip[j] = A[i];
            j++;
        }

    // return min(d, stripClosest(strip, j, d) );
    double minStrip = stripClosest(strip,j,d,&a,&b);
    if(d<minStrip)
    {
    	return d;
    }
    else
    {
    	u[0].x=a.x;u[0].y=a.y;
    	v[0].x=b.x;v[0].y=b.y;
    	return minStrip;
    }
}

void populate(point *A,long long N)
{
	for(;N>0;N--)
	{
		A[N].x=sqrt(rand());
		A[N].y=sqrt(rand());
	}
}

int main()
{
    point A[] = {{2, 3}, {3, 4}, {12, 30}, {40, 50}, {5, 1}, {12, 10},{2,2},{4,4},{8,8},{16,16},{32,32}};
    long long N = sizeof(A) / sizeof(A[0]);

    /*long long N;
    scanf("%lld",&N);
    if(N>63)
    	N=63;//my pc memory limitations 
    point *A = malloc(N*sizeof(point));
    populate(A,N);*/
    qsort(A,N, sizeof(point), compareX);
    point u,v;
    double dist=closest(A, N,&u,&v);
    printf("\n The smallest distance is %f between points(%f,%f) and (%f,%f) \n ",dist,u.x,u.y,v.x,v.y );

    //printf("%d \n",sizeof(point));
    
    //free(A);
    return 0;
}

