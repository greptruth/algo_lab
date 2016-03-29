#include <stdio.h>
// #include "heap.h"
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <float.h>

int main(){
	double exchRate[30][30];//={{100,200,400},{50,100,220},{25,45,100}};
	int N;
	int i,j,k;
	scanf("%d",&N);
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("Enter A[%d][%d]",i,j);
			scanf("%lf",&exchRate[i][j]);
		}
	}
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			exchRate[i][j]=-log(exchRate[i][j]/100.0);
	}

	// double dist[30][30],
	double dis[N], pre[N];

	for ( i = 0; i < N; ++i)
	   dis[i] = DBL_MAX, pre[i] = -1;

	dis[0] = 0;

	for (k = 0; k < N; ++k)
	  for ( i = 0; i < N; ++i)
	    for ( j = 0; j < N; ++j)
	      if (dis[i] + exchRate[i][j] < dis[j])
	        dis[j] = dis[i] + exchRate[i][j], pre[j] = i;
	for ( i = 0; i < N; ++i)
	  for ( j = 0; j < N; ++j)
	    if (dis[i] + exchRate[i][j] < dis[j]){
	      printf("There exists such a path \n");
	      return;
	    }
}