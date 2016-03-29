#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*#define VALID 1;
#define INVALID 0;*/
int VALID=1;
int INVALID=0;
double GLOBAL_TIME=0;
int ballNos=5,eventNos=0,N=0;
double width=1000,height=1000,wallNos=4,radius=3;
#define Precision 0.0000000001

struct event{
    int ballID0,ballID1;
    double Time;
    int valid;
    double x,y;
    //struct event *left,*right;
};
typedef struct event event;
struct reln{
    int ballID ,valid;//-4,-3,-2,-1for walls and 0,1,2,3,4 for balls
    event* ev;
};
typedef struct reln reln;
struct balls{
	int ballID;
    double vx,vy,x,y;
    double r,M;
    reln* list;
};
typedef struct balls balls;
struct walls{
	int  wallID;
	double x1,y1,x2,y2;
};
typedef struct walls walls;
void putEventData(event* a,event data){
    //copies collosion data of the two ball in a  the heap psoition found
    // printf("PUT DATA: %d %d \n",data.ballID0,data.ballID1);
    a->ballID0=data.ballID0;
    a->ballID1=data.ballID1;
    a->Time=data.Time;
    a->valid=data.valid;
    // printf("PUT DATA: %d %d \n",a->ballID0,a->ballID1);

}
double min(double a,double b){ (a>b)?b:a;}
double max(double a,double b){
	if(a>=b)
		return a;
	return b;
}
double minEv(event* a,event* b,double i,double j){ (a->Time<b->Time)?j:i;}
int estimateWallCollision(event* a,balls Ball,walls *wallData){
	// printf("%d %d %d %d %d %d\n",wallData->x1,wallData->y1,wallData->x2,wallData->y2,min(wallData->y1,wallData->y2),max(wallData->y1,wallData->y2));
	//return 1 if collision possible else 0
	double Time;
	if(wallData->x1==wallData->x2){
		if(Ball.vx>0)
	    {

	        Time=(width-Ball.x-Ball.r)/(Ball.vx);

	    }
	    else
	    {
	        Time= ((Ball.r-Ball.x)/(Ball.vx));
	    }

	    if(Time>Precision)
	    {
	        a->Time=GLOBAL_TIME+Time;
			a->ballID0=Ball.ballID;
			a->valid=VALID;
			a->ballID1=ballNos+wallData->wallID;
			// printf("KOALA %d %d\n",a->ballID0,a->ballID1);
			return 1;
	    }
	    else
	    {
	        return 0;
	    }
	}
	else{
		if(Ball.vy>0)
	    {

	        Time= (height-Ball.y-Ball.r)/Ball.vy;
	    }
	    else
	    {

	        Time=(Ball.r-Ball.y)/(Ball.vy);
	    }
	    if(Time>Precision)
	    {
	        a->Time=GLOBAL_TIME+Time;
			a->ballID0=Ball.ballID;
			a->valid=VALID;
			a->ballID1=ballNos+wallData->wallID;
			// printf("KOALA %d %d\n",a->ballID0,a->ballID1);
			return 1;
	    }
	    else
	    {

	        return 0;
	    }
	}
	// if(wallData->x1==wallData->x2 && ballData.vx!=0){
	// 	double T= (wallData->x1-ballData.x)/ballData.vx;
	// 	if(T>0){
	// 			double _y=ballData.y + ballData.vy*T;
	// 			if(_y>=min(wallData->y1,wallData->y2)-1&&_y<=max(wallData->y1,wallData->y2)+1){
	// 				a->Time=GLOBAL_TIME+T;
	// 				a->ballID0=ballData.ballID;
	// 				a->valid=VALID;
	// 				a->ballID1=ballNos+wallData->wallID;
	// 				a->x=wallData->x1;
	// 				a->y=_y;
	// 				// printf("XXX %d %d %d \n",T,wallData->x1,_y);	
	// 				return 1;
	// 			}
	// 			else{
	// 				a->valid=INVALID;
	// 				// printf("XXX %d %d %d \n",T,wallData->x1,_y);
	// 				return 0;
	// 			}
	// 		}
	// }
	// else if(ballData.vy!=0){
	// 	double T=(wallData->y1-ballData.y)/ballData.vy;
	// 	if(T>0){
	// 			double _x=ballData.x +ballData.vx*T;
	// 			if(_x>=min(wallData->x1,wallData->x2)-1 && _x<=max(wallData->x1,wallData->x2)+1){
	// 				//fill data
	// 				a->Time=GLOBAL_TIME+T;
	// 				a->ballID0=ballData.ballID;
	// 				a->valid=VALID;
	// 				a->ballID1=ballNos+wallData->wallID;
	// 				a->x=_x;
	// 				a->y=wallData->y1;
	// 				// printf("YYY %d %d %d \n",T,_x,wallData->y1);
	// 				return 1;
	// 			}
	// 			else{
	// 				a->valid=VALID;
	// 				// printf("YYY %d %d %d \n",T,_x,wallData->y1);
	// 				return 0;
	// 			}
	// 		}
	// }
}
void velocityUpdateWall(balls* Ball,walls* wallData)
{
	if(wallData->x1==wallData->x2)
		Ball->x=-Ball->x;
	else
		Ball->y=-Ball->y;

}
int estimateBallCollision(event* a,int ballID0,int ballID1,balls* ballData){
	double Delta_x,Delta_y,Delta_vx,Delta_vy,Delta_d_v,Delta_v_v,Delta_d_d,Distance_Ball,Distance;
    double Time;
     if(ballID0==ballID1)
     {
     	// printf("1 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
         return 0;
     }
     else
     {

         Delta_x=ballData[ballID0].x-ballData[ballID1].x;
         Delta_y=ballData[ballID0].y-ballData[ballID1].y;
         Delta_vx=ballData[ballID0].vx-ballData[ballID1].vx;
         Delta_vy=ballData[ballID0].vy-ballData[ballID1].vy;
         Delta_d_v=((Delta_x*Delta_vx)+(Delta_y*Delta_vy));
         if(Delta_d_v>0)
         {
         	// printf("2 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
             return 0;
         }
         Delta_d_d=((Delta_x*Delta_x)+(Delta_y*Delta_y));
         Delta_v_v=((Delta_vx*Delta_vx)+(Delta_vy*Delta_vy));
         Distance_Ball=ballData[ballID0].r+ballData[ballID1].r;

         Distance=((Delta_d_v*Delta_d_v)-(Delta_v_v*(Delta_d_d-(Distance_Ball*Distance_Ball))));
         if(Distance<=0)
         {
         	// printf("3 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
             return 0;
         }
         else
         {
             Time= -((Delta_d_v+sqrt(Distance))/Delta_v_v);

              if(Time<=Precision)
              {
              		// printf("4 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
                  return 0;
              }
              else
              {
					a->Time=GLOBAL_TIME+Time;
					a->ballID0=ballID0;
					a->valid=VALID;
					a->ballID1=ballID1;
					// printf("5 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
					return 1;

              }
         }
     }

}
void velocityUpdateBall(balls *Ball1,balls *Ball2)
{
    double Delta_X,Delta_Y,Delta_Vx,Delta_Vy,Delta_D_V,Distance_Ball,Force,Force_X,Force_Y;
    // printf("satya 1\n");
    Delta_X=Ball1->x-Ball2->x;
    Delta_Y=Ball1->y-Ball2->y;
    // printf("satya 2\n");
    Delta_Vx=Ball1->vx-Ball2->x;
    Delta_Vy=Ball1->vy-Ball2->vy;

    Delta_D_V=(Delta_X*Delta_Vx)+(Delta_Y*Delta_Vy);

    Distance_Ball=Ball1->r+Ball2->r;
    
    Force=(2*Ball1->M*Ball2->M*Delta_D_V)/((Ball1->M+Ball2->M)*Distance_Ball);
    Force_X=(Force*Delta_X)/Distance_Ball;
    Force_Y=(Force*Delta_Y)/Distance_Ball;


    Ball2->x+=(Force_X/Ball2->M);
    Ball2->y+=(Force_Y/Ball2->M);

    Ball1->x-=(Force_X/Ball1->M);
    Ball1->y-=(Force_Y/Ball1->M);
}
void updatePosition(balls* ball,double Time){
	ball->x+=ball->vx*Time;
    ball->y+=ball->vy*Time;
}
void addCollisions(event* events,int ballID,balls* ballData){
	//add al collisions of ballID
}
void voidAllCollisions(event* events,int ballID,int ballNos,balls* ballData){
	int i;
	for(i=0;i<ballNos;i++){
		if(ballData[ballID].list[i].valid==VALID){
			ballData[ballID].list[i].ev->valid=INVALID;
			ballData[ballID].list[i].ev->valid=INVALID;
		}
	}
}

void minHeapify(event* events,int N){
	int i;
	event temp;
	while(i>1){
		if(events[i].Time<events[i/2].Time){
			putEventData(&temp,events[i/2]);
            putEventData(&events[i/2],events[i]);
            putEventData(&events[i],temp);
		}
		else
			break;
	}
}
void createHeap(event* events,int N){
	int i;
	for(i=N/2;i>1;i++){
		minHeapify(events,i);
	}
}
event* insert(event* events,int *N,event data){
    event temp;
    int n=*N,i,pos;
    // printf("insert start %d\n",*N);
    if(n==0){
    	// printf("case 1: %d %d \n",data.ballID0,data.ballID1);
        putEventData(&events[1],data);
        // printf("case 1: %d %d \n",events[i].ballID0,events[1].ballID1);
        *N=*N+1;//*N+1;
        return &events[1];
    }
    *N=*N+1;
    putEventData(&events[n+1],data);
    i=(int)(*N);
    pos=i;
    while(i>1){
        if(events[(int)i/2].Time>events[i].Time){
            putEventData(&temp,events[i/2]);
            putEventData(&events[i/2],events[i]);
            putEventData(&events[i],temp);
            i=i/2;
        }
        else
            break;
    }
    // printf("insert %d %d\n",*N,i);
    return &events[i];
}
event extractMin(event *events,int *N){
	// printf("extractMin %d \n",*N);
	int n=*N,i,pos;
	event min,temp,*minEvent;
	if(N==0){
		printf("want something out of zeroes? all you get is NULL  \n");
	}
	putEventData(&min,events[1]);
	n--;
	*N--;
	events[1]=events[n+1];
	i=1;
	while(i<=n/2){
		if(2*i+1<=n){
			pos=minEv(&events[2*i],&events[2*i+1],2*i,2*i+1);//define This function
			minEvent=&events[pos];
			if(minEvent->Time<events[i].Time){
				putEventData(&temp,*minEvent);
            	putEventData(minEvent,events[i]);
            	putEventData(&events[i],temp);
            	i=pos;
			}
			else break;
		}
		else{
			if(events[2*i].Time<events[i].Time){
				putEventData(&temp,events[2*i]);
            	putEventData(&events[2*i],events[i]);
            	putEventData(&events[i],temp);
            	i=2*i;
			}
			else break;
		}
	}
	// printf("OLa %d \n",min.y);
	return min;
}

int main()
{
	int i,j,s;
    reln BBlink[5][5],BWlink[5];
    balls* ballData=malloc(ballNos*sizeof(balls));
    walls* wallData=malloc(wallNos*sizeof(walls));
    event events[100000],toEst,*ptr,minEv;
    event happen[100000];
    int happenNo=0;

    FILE *File_Ball_1,*File_Ball_2,*File_Ball_3,*File_Ball_4,*File_Ball_5;
    File_Ball_1=fopen("Ball_1.txt","w");
    File_Ball_2=fopen("Ball_2.txt","w");
    File_Ball_3=fopen("Ball_3.txt","w");
    File_Ball_4=fopen("Ball_4.txt","w");
    File_Ball_5=fopen("Ball_5.txt","w");

    //set wall data according to gtk drawing area
    wallData[0].wallID=0;
    wallData[0].x1=0;
    wallData[0].y1=0;
    wallData[0].x2=0;
    wallData[0].y2=height;
    wallData[1].wallID=1;
    wallData[1].x1=0;
    wallData[1].y1=height;
    wallData[1].x2=width;
    wallData[1].y2=height;
    wallData[2].wallID=2;
    wallData[2].x1=width;
    wallData[2].y1=height;
    wallData[2].x2=width;
    wallData[2].y2=0;
    wallData[3].wallID=3;
    wallData[3].x1=width;
    wallData[3].y1=0;
    wallData[3].x2=0;
    wallData[3].y2=0;

    //set random ball data
    for(i=0;i<ballNos;i++){
    	// printf("gyfysfsf\n");
    	ballData[i].ballID=i;
    	ballData[i].r=radius +1;
    	int r=1;//ballData[i].r;
    	ballData[i].vx=rand()%3000 +10;
    	ballData[i].vy=rand()%3000 +10;
    	ballData[i].x=rand()%((int)width-r)+r;
    	ballData[i].y=rand()%((int)height-r)+r;
    	ballData[i].M=5;
    	// ballData[i].list= malloc(sizeof(reln)*(ballNos+4));
    	// for(j=0;j<ballNos-1+wallNos;j++){
    	// 	ballData[i].list[j].ev=NULL;
    	// 	ballData[i].list[j].ballID=j-4;
    	// 	ballData[i].list[j].valid=INVALID;
    	// }  		    	
    }

    //finding all ball ball possible colooisions initially
    for(i=0;i<ballNos;i++){
    	for( j=0;j<ballNos;j++){
    		if(i==j){
    			BBlink[i][j].valid=INVALID;
    			BBlink[i][j].ev=NULL;
    			continue;
    		}

    		int s=estimateBallCollision(&toEst,i,j,ballData);
    		if(s==1){

    			ptr=insert(events,&N,toEst);
    			BBlink[i][j].valid=VALID;
    			BBlink[i][j].ev=ptr;
    			BBlink[j][i].valid=VALID;
    			BBlink[j][i].ev=ptr;

    		}

    	}
    }
    // printf("HERE \n");
    //finding all ball wall collisions initially
    for(i=0;i<ballNos;i++){
    	for(j=0;j<wallNos;j++){

    		s=estimateWallCollision(&toEst,ballData[i],& wallData[j]);
    		if(s==1){
    			// printf("sshkaj %d %d\n",toEst.ballID0,toEst.ballID1);
	    		ptr=insert(events,&N,toEst);
	    		BWlink[i].valid=VALID;
	    		BWlink[i].ev=ptr;
	    	}

    	}
    	
    }
    // int m;
    // for(m=1;m<=N;m++)
    // 	printf("DO %d %d \n",events[m].ballID0,events[m].ballID1);
    //return 0;
    // printf("HERE \n");
    while(GLOBAL_TIME<=1000){
    	fprintf(File_Ball_1,"(%lf,%lf)\n",ballData[0].x,ballData[0].y);
        fprintf(File_Ball_2,"(%lf,%lf)\n",ballData[1].x,ballData[1].y);
        fprintf(File_Ball_3,"(%lf,%lf)\n",ballData[2].x,ballData[2].y);
        fprintf(File_Ball_4,"(%lf,%lf)\n",ballData[3].x,ballData[3].y);
        fprintf(File_Ball_5,"(%lf,%lf)\n",ballData[4].x,ballData[4].y);
    	// printf("HERE 1\n");
    	if(N>0){
    		minEv=extractMin(events,&N);
    		if(minEv.valid==INVALID)
    			continue;
    		printf("%d__%d_%d________________________________________________________________________\n",N,minEv.ballID0,minEv.ballID1);
	    	if(minEv.ballID1<ballNos)
	    		{
	    			// printf("ppp\n");
	    			velocityUpdateBall(&ballData[minEv.ballID0],&ballData[minEv.ballID1]);
	    		}
	    	else
	    		velocityUpdateWall(&ballData[minEv.ballID0],&wallData[minEv.ballID1]);
	    	// printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	    	for(i=0;i<ballNos;i++){
	    		updatePosition(&ballData[i],minEv.Time-GLOBAL_TIME);
	    	}
	    	GLOBAL_TIME=minEv.Time;
	    	
    	}
    	// printf("HERE 2\n");
    	if(minEv.valid==INVALID)
    		continue;
    	// printf("HERE 3\n");
    	putEventData(&happen[happenNo],minEv);
    	happenNo++;
    	// printf("HERE %d 4\n",minEv.y);
    	//invalidate all connected collisions
    	for( i=0;i<ballNos;i++){
    		// printf("OHO %d %d %d\n",minEv.ballID0,i,minEv.y);
    		if(BBlink[minEv.ballID0][i].ev!=NULL){
    			BBlink[minEv.ballID0][i].ev->valid=INVALID;
	    		BBlink[i][minEv.ballID0].ev->valid=INVALID;
    		}
    		

    	}
    	
    	// printf("HERE 5\n");
    	//find new collisions
    	for( i=0;i<ballNos;i++){
    		int s=estimateBallCollision(&toEst,i,j,ballData);
    		if(s==1){
    			// printf("inserting \n");
    			ptr=insert(events,&N,toEst);
    			// GLOBAL_TIME=ptr->Time;
    			BBlink[i][j].valid=VALID;
    			BBlink[i][j].ev=ptr;
    			BBlink[j][i].valid=VALID;
    			BBlink[j][i].ev=ptr;

    		}
    	}
    	// printf("shit \n");
    	for(i=0;i<wallNos;i++){
    		// printf("tada\n");
    		int s=estimateWallCollision(&toEst,ballData[i],&wallData[i]);
    		if(s==1){
	    		// printf("inserting wall\n");
	    		ptr=insert(events,&N,toEst);
	    		// GLOBAL_TIME=ptr->Time;
	    		BWlink[i].valid=VALID;
	    		BWlink[i].ev=ptr;
	    	}
    	}
    	

    	printf("GLOBAL_TIME********** N %f %d\n",GLOBAL_TIME,N);
    }

    



    //craete events for all combination of i=-4,-3,-2,-1 and j=0,1,2,3,4
    //create all events for i=0,1,2,3,4 j=i+1 to 4
    //create heap

    
    
}
