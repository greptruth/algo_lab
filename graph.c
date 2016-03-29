// C Program for Floyd Warshall Algorithm
#include<stdio.h>
#include<limits.h>
// Number of vertices in the graph
#define V 4
#define INF INT_MAX

// A function to print the distance matrix
void printSolution(int dist[][V]);

// A function to print the path matrix
void printPath(int path[][V]);

// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshell (int graph[][V])
{
    /* dist[][] will be the output matrix that will finally have the shortest 
    distances between every pair of vertices
    
    path[][] will be the output matrix that will finally have the shortest 
    path between every pair of vertices
    */
    int dist[V][V], path[V][V], i, j, k;

    /* Initialize the solution matrix same as input graph matrix. Or 
    we can say the initial values of shortest distances are based
    on shortest paths considering no intermediate vertex. 
    
    Initialize the path matrix as i if path exists from i to j in 
    input graph matrix considering no intermediate vertex. 
    */
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
            
            if(dist[i][j]!=INF && i!=j) {
                path[i][j] = i;
            } else {
                path[i][j] = -1;
            }
        }   
    }
    /* Add all vertices one by one to the set of intermediate vertices.
    ---> Before start of a iteration, we have shortest distances between all
    pairs of vertices such that the shortest distances consider only the
    vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
    ----> After the end of a iteration, vertex no. k is added to the set of
    intermediate vertices and the set becomes {0, 1, 2, .. k} */
    for (k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++)
            {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j], path[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF &&
                        dist[i][k] + dist[k][j] < dist[i][j]) { 
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
            // if diagonal elements become negative, 
            // graph contains negative weight cycle
            if(dist[i][i] < 0) {
                printf("Graph contains negative weight cycle\n");
                return;
            }
        }
    }
    
    
    // Print the shortest distance matrix
    printSolution(dist);
    
    // Print the shortest path matrix
    printPath(path);
}

/* A utility function to print solution */
void printSolution(int dist[][V])
{
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

void printPathUtil(int path[][V],int i, int j)
{
    if(path[i][j] == i)
        return;

    printPathUtil(path, i,  path[i][j]);
    printf ("%d ", path[i][j]);
}

/* A utility function to print solution */
void printPath(int path[][V])
{
    printf ("\nFollowing matrix shows the shortest path"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (path[i][j] == -1)
                printf("%5s ", "INF");
            else {
                printf (" (%d ", i);
                printPathUtil(path, i, j);
                printf ("%d)", j);
            }
        }
        printf("\n");
    }
}

// driver program to test above function
int main()
{
    /* Let us create the following weighted graph
            10
    (0)------->(3)
        |        /|\
    5 |      |
        |        | 1
    \|/      |
    (1)------->(2)
            3        */
    int graph[V][V] = { {0, 5, INF, 10},
                        {INF, 0, 3, INF},
                        {INF, INF, 0, 1},
                        {INF, INF, INF, 0}
                    };

    // Print the solution
    floydWarshell(graph);
    return 0;
}

void BellmanFord(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
 
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++)
        dist[i]   = INT_MAX;
    dist[src] = 0;
 
    // Step 2: Relax all edges |V| - 1 times. A simple shortest 
    // path from src to any other vertex can have at-most |V| - 1 
    // edges
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
 
    // Step 3: check for negative-weight cycles.  The above step 
    // guarantees shortest distances if graph doesn't contain 
    // negative weight cycle.  If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }
 
    printArr(dist, V);
 
    return;
}
 

void dijkstra(int graph[V][V], int src)
{
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i
 
     bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized
 
     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
 
     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet);
 
       // Mark the picked vertex as processed
       sptSet[u] = true;
 
       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)
 
         // Update dist[v] only if is not in sptSet, there is an edge from 
         // u to v, and total weight of path from src to  v through u is 
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
 
     // print the constructed distance array
     printSolution(dist, V);
}




#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
typedefstruct node
{ 
int data;
struct node *left,*right;
intht;
}node;
node *insert(node *,int);
node *Delete(node *,int);
void 
preorder(node *);
void 
inorder(node *);
int  
height( node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int BF(node *);
int main()
{
               node
*root=NULL;
               intx,n,i,op;
               do
                              {
                                             printf(“n1)Create:”);
                                             printf(“n2)Insert:”);
                                             printf(“n3)Delete:”);
                                             printf(“n4)Print:”);
                                             printf(“n5)Quit:”);
                                             printf(“nnEnter
Your Choice:”);
                                             scanf(“%d”,&op);
                                             switch(op)
                                                 {
                                                            case
1:printf(“nEnter no. of elements:”);
                                                            scanf(“%d”,&n);
                                                            printf(“nEnter
tree data:”);
                                                            root=NULL;
                                                            for(i=0;i<n;i++)
                                                                              {
                                                                                          scanf(“%d”,&x);
                                                                                          root=insert(root,x);
                                                                              }
                                                            break;
                                                            case
2:printf(“nEnter a data:”);
                                                            scanf(“%d”,&x);
                                                            root=insert(root,x);
                                                            break;
                                                            case
3:printf(“nEnter a data:”);
                                                            scanf(“%d”,&x);
                                                            root=Delete(root,x);
                                                            break;
                                                            case
4:  printf(“nPreorder
sequence:n”);
                                                                           preorder(root);
                                                                           printf(“nnInorder
sequence:n”);
                                                                           inorder(root);
                                                                           printf(“n”);
                                                                           break;
                                                  }
               }while(op!=5);
return 0;
}
node * insert(node *T,int x)
{
               if(T==NULL)
               {
                              T=(node*)malloc(sizeof(node));
                              T->data=x;
                              T->left=NULL;
                              T->right=NULL;
               }
               else
                              if(x
> T->data)                // insert
in right subtree
                              {
                                             T->right=insert(T->right,x);
                                             if(BF(T)==-2)
                                                            if(x>T->right->data)
                                                                           T=RR(T);
                                                            else
                                                                           T=RL(T);
                              }
                              else
                                             if(x<T->data)
                                             {
                                                            T->left=insert(T->left,x);
                                                            if(BF(T)==2)
                                                                           if(x
< T->left->data)
                                                                                          T=LL(T);
                                                                           else
                                                                                          T=LR(T);
                                             }
                                             T->ht=height(T);
                                             return(T);
}
node * Delete(node *T,int x)
{      
node *p;
               if(T==NULL)
               {
                              return
NULL;
               }
               else
                              if(x
> T->data)                // insert
in right subtree
                              {
                                             T->right=Delete(T->right,x);
                                             if(BF(T)==2)
                                                            if(BF(T->left)>=0)
                                                                           T=LL(T);
                                                            else
                                                                           T=LR(T);
                              }
                              else
                                             if(x<T->data)
                                                            {
                                                                           T->left=Delete(T->left,x);
                                                                           if(BF(T)==-2)//Rebalance
during windup
                                                                                          if(BF(T->right)<=0)
                                                                                                         T=RR(T);
                                                                                          else
                                                                                                         T=RL(T);
                                                            }
                                             else
                                               {
                                                 //data to be deleted is found
                                             if(T->right
!=NULL)
                                                            {  //delete its inordersuccesor
                                                                  p=T->right;
                                                            while(p->left
!= NULL)
                                                                             p=p->left;
                                                                  T->data=p->data;
                                                                 
T->right=Delete(T->right,p->data);
                                                            if(BF(T)==2)//Rebalance
during windup
                                                                                          if(BF(T->left)>=0)
                                                                                                         T=LL(T);
                                                                                          else
                                                                                                         T=LR(T);
                                                               }
                                             else
                                                            return(T->left);
                                               }
               T->ht=height(T);
               return(T);
}
int height(node *T)
{
               intlh,rh;
               if(T==NULL)
                              return(0);
               if(T->left==NULL)
                              lh=0;
               else
                              lh=1+T->left->ht;
               if(T->right==NULL)
                              rh=0;
               else
                              rh=1+T->right->ht;
               if(lh>rh)
                              return(lh);
               return(rh);
}
node * rotateright(node *x)
{
               node
*y;
               y=x->left;
               x->left=y->right;
               y->right=x;
               x->ht=height(x);
               y->ht=height(y);
               return(y);
}
node * rotateleft(node *x)
{
               node
*y;
               y=x->right;
               x->right=y->left;
               y->left=x;
               x->ht=height(x);
               y->ht=height(y);
               return(y);
}
node * RR(node *T)
{
               T=rotateleft(T);
               return(T);
}
node * LL(node *T)
{
               T=rotateright(T);
               return(T);
}
node * LR(node *T)
{
               T->left=rotateleft(T->left);
               T=rotateright(T);
               return(T);
}
node * RL(node *T)
{
               T->right=rotateright(T->right);
               T=rotateleft(T);
               return(T);
}
int BF(node *T)
{
               intlh,rh;
               if(T==NULL)
               return(0);
               if(T->left==NULL)
                              lh=0;
               else
                              lh=1+T->left->ht;
               if(T->right==NULL)
                              rh=0;
               else
                              rh=1+T->right->ht;
               return(lh-rh);
}
void preorder(node *T)
{
               if(T!=NULL)
               {
                              printf(“%d(Bf=%d)
“,T->data,BF(T));
                              preorder(T->left);
                              preorder(T->right);
               }
}
void inorder(node *T)
{
               if(T!=NULL)
               {
                              inorder(T->left);
                              printf(“%d(Bf=%d)
“,T->data,BF(T));
                              inorder(T->right);
               }
}