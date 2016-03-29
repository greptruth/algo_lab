#include  <stdio.h>
#include <stdlib.h>
#include <math.h>


#define Length 100
#define Width 100
#define Black 1
#define Blue 2
#define Red 3
#define White 4
#define Orange 5
#define Infinite  1000000
#define Balls 5
#define Precision 0.0000000001


int Heap_s=0;
typedef struct Object{
    double Radius;
    double X_coordinate;
    double Y_coordinate;
    double X_velocity;
    double Y_velocity;
    double Mass;
    int color;
} Object;

struct {
    double X_Min;
    double Y_Min;
    double X_Max;
    double Y_Max;
}Plane ;

typedef struct Collision{
    Object Target[2];
    double time_stamp;
    int Invalid_flag;

}Collision;

Collision *Extracted;
int Parent(int i)
{
    return (int)(i-1)/2;
}

int Right(int i)
{
    return 2*i+2;
}
int Left(int i)
{
    return 2*i+1;
}
void Print_Object(Object *Ball)
{
    printf("\nRadius=%lf\nMass=%lf\nColor=%d\nX_Coor=%lf\nY_Coor=%lf\nVx=%lf\nVy=%lf\n",Ball->Radius,Ball->Mass,Ball->color,Ball->X_coordinate,Ball->Y_coordinate,Ball->X_velocity,Ball->Y_velocity);
}
Object Update_Position(Object ball,double Time)
{
    ball.X_coordinate+=ball.X_velocity*Time;
    ball.Y_coordinate+=ball.Y_velocity*Time;
    return ball;
}

double Collision_Time_Ball_Ball(Object Ball1,Object Ball2)
{
    double Delta_x,Delta_y,Delta_vx,Delta_vy,Delta_d_v,Delta_v_v,Delta_d_d,Distance_Ball,Distance;
    double Time;
     if(Ball1.color==Ball2.color)
     {
         return Infinite;
     }
     else
     {

         Delta_x=Ball1.X_coordinate-Ball2.X_coordinate;
         Delta_y=Ball1.Y_coordinate-Ball2.Y_coordinate;
         Delta_vx=Ball1.X_velocity-Ball2.X_velocity;
         Delta_vy=Ball1.Y_velocity-Ball2.Y_velocity;
         Delta_d_v=((Delta_x*Delta_vx)+(Delta_y*Delta_vy));
         if(Delta_d_v>0)
         {

             return Infinite;
         }
         Delta_d_d=((Delta_x*Delta_x)+(Delta_y*Delta_y));
         Delta_v_v=((Delta_vx*Delta_vx)+(Delta_vy*Delta_vy));
         Distance_Ball=Ball1.Radius+Ball2.Radius;

         Distance=((Delta_d_v*Delta_d_v)-(Delta_v_v*(Delta_d_d-(Distance_Ball*Distance_Ball))));
         if(Distance<=0)
         {
             return Infinite;
         }
         else
         {
             Time= -((Delta_d_v+sqrt(Distance))/Delta_v_v);

              if(Time<=Precision)
              {

                  return Infinite;
              }
              else
              {
                  return Time;
              }
         }
     }
}


double time_Vertical_wall_collision(Object Ball)
{
    double Time;

    if(Ball.X_velocity>0)
    {

        Time=(Length-Ball.X_coordinate-Ball.Radius)/(Ball.X_velocity);

    }
    else
    {
        Time= ((Ball.Radius-Ball.X_coordinate)/(Ball.X_velocity));
    }

    if(Time>Precision)
    {
        return Time;
    }
    else
    {
        return Infinite;
    }

}

double time_horizontal_wall_collision(Object Ball)
{
    double Time;
    if(Ball.Y_velocity>0)
    {

        Time= (Width-Ball.Y_coordinate-Ball.Radius)/Ball.Y_velocity;
    }
    else
    {

        Time=(Ball.Radius-Ball.Y_coordinate)/(Ball.Y_velocity);
    }
    if(Time>Precision)
    {
        return Time;
    }
    else
    {

        return Infinite;
    }
}

Object velocity_Change_vertical(Object Ball)
{
    Ball.X_velocity=-Ball.X_velocity;
    return Ball;
}

Object velocity_Change_horizontal(Object Ball)
{
    Ball.Y_velocity=-Ball.Y_velocity;
    return Ball;
}

void velocity_Update(Object *Ball1,Object *Ball2)
{
    double Delta_X,Delta_Y,Delta_Vx,Delta_Vy,Delta_D_V,Distance_Ball,Force,Force_X,Force_Y;

    Delta_X=Ball1->X_coordinate-Ball2->X_coordinate;
    Delta_Y=Ball1->Y_coordinate-Ball2->Y_coordinate;

    Delta_Vx=Ball1->X_velocity-Ball2->X_velocity;
    Delta_Vy=Ball1->Y_velocity-Ball2->Y_velocity;

    Delta_D_V=(Delta_X*Delta_Vx)+(Delta_Y*Delta_Vy);

    Distance_Ball=Ball1->Radius+Ball2->Radius;

    Force=(2*Ball1->Mass*Ball2->Mass*Delta_D_V)/((Ball1->Mass+Ball2->Mass)*Distance_Ball);
    Force_X=(Force*Delta_X)/Distance_Ball;
    Force_Y=(Force*Delta_Y)/Distance_Ball;


    Ball2->X_velocity+=(Force_X/Ball2->Mass);
    Ball2->Y_velocity+=(Force_Y/Ball2->Mass);

    Ball1->X_velocity-=(Force_X/Ball1->Mass);
    Ball1->Y_velocity-=(Force_Y/Ball1->Mass);
}

Collision *Exchange(Collision *A,int Large,int Small)
{
     Collision temp;
     temp.Target[0]=A[Large].Target[0];
     temp.Target[1]=A[Large].Target[1];
     temp.time_stamp=A[Large].time_stamp;
     temp.Invalid_flag=A[Large].Invalid_flag;

     A[Large].Target[0]=A[Small].Target[0];
     A[Large].Target[1]=A[Small].Target[1];
     A[Large].time_stamp=A[Small].time_stamp;
     A[Large].Invalid_flag=A[Small].Invalid_flag;

     A[Small].Target[0]=temp.Target[0];
     A[Small].Target[1]=temp.Target[1];
     A[Small].time_stamp=temp.time_stamp;
     A[Small].Invalid_flag=temp.Invalid_flag;

     return A;


}

void Print_Heap(Collision *A)
{
    int i=0;
    printf("\nheap size===%d\n",Heap_s);
    for(i=0;i<Heap_s;i++)
    {
        printf("%lf\t",A[i].time_stamp);
    }
}

Collision* Heapify(Collision * A,int i,int ArraySize)
{
    int L,R,Smallest;
    L=Left(i);
    R=Right(i);

    if((L<=Heap_s)&&(A[L].time_stamp<A[i].time_stamp))
    {
        Smallest=L;
    }
    else
    {
        Smallest=i;
    }

    if((R<=Heap_s)&&(A[R].time_stamp<A[Smallest].time_stamp))
    {
        Smallest=R;
    }
    if(Smallest!=i)
    {
        A=Exchange(A,i,Smallest);
        A=Heapify(A,Smallest,ArraySize);
    }
    return A;
}

Collision *Insert(Collision *A,Collision Element,int ArraySize)
{
    int i=0;
   // printf("%d\t%d\n",Heap_s,ArraySize);
   A[Heap_s].Target[0]=Element.Target[0];
   A[Heap_s].Target[1]=Element.Target[1];
   A[Heap_s].time_stamp=Element.time_stamp;
   A[Heap_s].Invalid_flag=Element.Invalid_flag;

   for(i=Heap_s/2;i>=0;i--)
   {
      // printf("%lf",Element.time_stamp);
       A=Heapify(A,i,ArraySize);
   }
   Heap_s++;

   return A;
}

Collision  Extract_Min(Collision *A,int ArraySize)
{

    Extracted->Target[0]=A[0].Target[0];

    Extracted->Target[1]=A[0].Target[1];
    Extracted->Invalid_flag=A[0].Invalid_flag;
    Extracted->time_stamp=A[0].time_stamp;

    A[0].Target[0]=A[Heap_s-1].Target[0];
    A[0].Target[1]=A[Heap_s-1].Target[1];
    A[0].time_stamp=A[Heap_s-1].time_stamp;
    A[0].Invalid_flag=A[Heap_s-1].Invalid_flag;
    Heap_s--;
    Heapify(A,0,ArraySize);
}
void Init_Ball(Object *Ball,double Radius,double Mass,int color,double X,double Y,double Vx,double Vy)
{
    Ball->Radius=Radius;
    Ball->Mass=Mass;
    Ball->color=color;
    Ball->X_coordinate=X;
    Ball->Y_coordinate=Y;
    Ball->X_velocity=Vx;
    Ball->Y_velocity=Vy;
}

int main()
{
    int i=0,j=0,ArraySize=1000000,invalid_count=0;
    Object Ball[Balls],Walls[2];
    Collision Element,*HeapArr;
    double Runtime=0;
    double Time_User=0;
    HeapArr=(Collision *)malloc(ArraySize*sizeof(Collision));
    Extracted=(Collision *)malloc(sizeof(Collision));
    FILE *File_Ball_1,*File_Ball_2,*File_Ball_3,*File_Ball_4,*File_Ball_5;
    File_Ball_1=fopen("Ball_1.txt","w");
    File_Ball_2=fopen("Ball_2.txt","w");
    File_Ball_3=fopen("Ball_3.txt","w");
    File_Ball_4=fopen("Ball_4.txt","w");
    File_Ball_5=fopen("Ball_5.txt","w");

    printf("Please Enter the Simulation time:");
    scanf("%lf",&Time_User);

    Init_Ball(&Ball[0],1,1,1,9,18,-5,1);
    Init_Ball(&Ball[1],1,1,2,4,30,4,2);
    Init_Ball(&Ball[2],1,1,3,8,60,9,5);
    Init_Ball(&Ball[3],1,1,4,2,90,1,6);
    Init_Ball(&Ball[4],1,1,5,17,10,-1,7);
    Init_Ball(&Walls[0],1,Infinite,6,Width,1,0,0);
    Init_Ball(&Walls[1],1,Infinite,7,Length,0,0,0);


    for(i=0;i<Balls;i++)
    {
        for(j=0;j<Balls;j++)
        {
            Element.Target[0]=Ball[i];
            Element.Target[1]=Ball[j];
            Element.time_stamp=Collision_Time_Ball_Ball(Ball[i],Ball[j]);

            Element.Invalid_flag=0;
            if(Element.time_stamp!=Infinite)
            {
                HeapArr=Insert(HeapArr,Element,ArraySize);
            }
        }

    }
    for(i=0;i<Balls;i++)
    {
        Element.time_stamp=time_horizontal_wall_collision(Ball[i]);

        Element.Target[0]=Ball[i];
        Element.Target[1]=Walls[0];
        Element.Invalid_flag=0;
        if(Element.time_stamp!=Infinite)
        {
            HeapArr=Insert(HeapArr,Element,ArraySize);
        }

        Element.time_stamp=time_Vertical_wall_collision(Ball[i]);

        Element.Target[0]=Ball[i];
        Element.Target[1]=Walls[1];
        Element.Invalid_flag=0;
        if(Element.time_stamp!=Infinite)
        {
            HeapArr=Insert(HeapArr,Element,ArraySize);
        }
    }


    while(Runtime<=Time_User)
    {

        Extract_Min(HeapArr,ArraySize);
        if(Heap_s==1)
        {
                break;
        }
        if((Extracted->Invalid_flag!=1)&&(Extracted->time_stamp>Precision))
        {


            Runtime+=Extracted->time_stamp;


            for(i=0;i<Balls;i++)
            {

                Ball[i]=Update_Position(Ball[i],Extracted->time_stamp);


            }

          

                fprintf(File_Ball_1,"(%lf,%lf)\n",Ball[0].X_coordinate,Ball[0].Y_coordinate);
                fprintf(File_Ball_2,"(%lf,%lf)\n",Ball[1].X_coordinate,Ball[1].Y_coordinate);
                fprintf(File_Ball_3,"(%lf,%lf)\n",Ball[2].X_coordinate,Ball[2].Y_coordinate);
                fprintf(File_Ball_4,"(%lf,%lf)\n",Ball[3].X_coordinate,Ball[3].Y_coordinate);
                fprintf(File_Ball_5,"(%lf,%lf)\n",Ball[4].X_coordinate,Ball[4].Y_coordinate);   


            for(i=0;i<Heap_s;i++)
            {
                if(Extracted->Target[1].color<6)
                {

                    if((Extracted->Target[0].color==HeapArr[i].Target[0].color)||(Extracted->Target[1].color==HeapArr[i].Target[0].color)||(Extracted->Target[0].color==HeapArr[i].Target[1].color)||(Extracted->Target[1].color==HeapArr[i].Target[1].color)&&(HeapArr[i].Invalid_flag!=1))
                    {
                        HeapArr[i].Invalid_flag=1;
                        invalid_count++;
                    }
                }
                else
                {
                    if((Extracted->Target[0].color==HeapArr[i].Target[0].color)&&(HeapArr[i].Invalid_flag!=1))
                    {
                        HeapArr[i].Invalid_flag=1;
                        invalid_count++;
                    }
                }
            }

            if(Extracted->Target[1].color==6)
            {
                Ball[Extracted->Target[0].color-1]=velocity_Change_horizontal(Ball[Extracted->Target[0].color-1]);
            }
            else if(Extracted->Target[1].color==7)
            {
                Ball[Extracted->Target[0].color-1]=velocity_Change_vertical(Ball[Extracted->Target[0].color-1]);
            }
            else
            {
                velocity_Update(&Ball[Extracted->Target[0].color-1],&Ball[Extracted->Target[1].color-1]);
            }

            for(i=0;i<Balls;i++)
            {
                for(j=0;j<Balls;j++)
                {
                    Element.Target[0]=Ball[i];
                    Element.Target[1]=Ball[j];
                    Element.time_stamp=Collision_Time_Ball_Ball(Ball[i],Ball[j]);
                    Element.Invalid_flag=0;

                    if(Element.time_stamp!=Infinite)
                    {
                        HeapArr=Insert(HeapArr,Element,ArraySize);

                    }
                }
            }

            for(i=0;i<Balls;i++)
            {

                Element.time_stamp=time_horizontal_wall_collision(Ball[i]);
                Element.Target[0]=Ball[i];
                Element.Target[1]=Walls[0];
                if(Element.time_stamp!=Infinite)
                {
                    HeapArr=Insert(HeapArr,Element,ArraySize);
                }

                Element.time_stamp=time_Vertical_wall_collision(Ball[i]);
                Element.Target[0]=Ball[i];
                Element.Target[1]=Walls[1];
                Element.Invalid_flag=0;
                if(Element.time_stamp!=Infinite)
                {
                    HeapArr=Insert(HeapArr,Element,ArraySize);
                }
            }
        }
    }
    printf("Heap_s=%d\nTotal_Invalid_Count=%d",Heap_s,invalid_count);

    return 0;


}

