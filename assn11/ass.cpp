// C++ implementation of worst case linear time algorithm
// to find k'th smallest element
#include<iostream>
#include<algorithm>
#include<climits>
#include <stdio.h>
// #include "heap.h"
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <float.h>
using namespace std;
 int arr1[] = {1,4,7,2,8,5,9,3,10,6};
 int arr2[]={11,12,13,14,15,16,17,18,19,20};
int partition(int arr[], int l, int r, int k);
 
// A simple function to find median of arr[].  This is called
// only for an array of size 5 in this program.
int findMedian(int arr[], int n)
{
    sort(arr, arr+n);  // Sort the array
    return arr[n/2];   // Return middle element
}
 
// Returns k'th smallest element in arr[l..r] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
int util(int arr[],int l,int r){

    int n=r-l+1;
    int i, median[(n+4)/5]; // There will be floor((n+4)/5) groups;
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n) //For last group with less than 5 elements
        {
            median[i] = findMedian(arr+l+i*5, n%5); 
            i++;
        }    
 
        // Find median of all medians using recursive call.
        // If median[] has only one element, then no need
        // of recursive call
        // printf("SATYA %d %d %d \n",k,l,r);
        int medOfMed = (i == 1)? median[i-1]:
                                 util(median, 0, i-1);
        return medOfMed;
}
int kthSmallest(int arr[], int l, int r, int k)
{
    // If k is smaller than number of elements in array
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1; // Number of elements in arr[l..r]
 
        // Divide arr[] in groups of size 5, calculate median
        // of every group and store it in median[] array.
        
 
        // Partition the array around a random element and
        // get position of pivot element in sorted array
        int medOfMed=util(arr,l,r);

        int pos = partition(arr, l, r, medOfMed);
 
        // If position is same as k
        if (pos-l == k-1)
            return pos;
        if (pos-l > k-1)  // If position is more, recur for left
            return kthSmallest(arr, l, pos-1, k);
 
        // Else recur for right subarray
        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }
 
    // If k is more than number of elements in array
    return INT_MAX;
}
 
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
// It searches for x in arr[l..r], and partitions the array 
// around x.
int partition(int arr[], int l, int r, int x)
{
    // // Search for x in arr[l..r] and move it to end
    // for(int m=0;m<10;m++)
    //         printf("%d,",arr1[m]);
    //     printf("\nB%d %d %d  \n",x,l,r);
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == x)
           break;
    swap(&arr[i], &arr[r]);
    // for(int m=0;m<10;m++)
    //         printf("%d,",arr1[m]);
    //     printf("\nC%d %d %d %d \n",x,i,l,r);
 
    // Standard partition algorithm
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    for(int m=0;m<10;m++)
            printf("%d,",arr1[m]);
    for(int m=0;m<10;m++)
            printf("%d,",arr2[m]);
        printf("\nD\n");
    return i;
}
 
// Driver program to test above methods
 
int main()
{
   
    // int arr1[]={1,2,3,4,5,6,7,8,9};
    // int arr1[]={1,2,3,4,5};
    int n1 = sizeof(arr1)/sizeof(arr1[0]), k1 = -1;
    // int arr2[] = {11,14,12,19,13,17,16,15,20,18};
    
    // int arr2[]={6,7,8,9,10};

    int n2 = sizeof(arr1)/sizeof(arr1[0]), k2 = -1;
    int k=2;

    scanf("%d",&k);
    // k--;
    int curr1 =-1,curr2=-1,c1=-1,c2=-1,curr=-1,step,ans;
    step=k1=k2=k;
    int s1=0,e1=n1-1,s2=0,e2=n2-1;

    // printf("%dth smalles= %d\n",k,arr1[kthSmallest(arr1,0,n1-1,k)]);
    // for(int i=0;i<n1;i++)
    //     printf("%d,",arr1[i]);
    // printf("\n");

    while(1){
        // printf("A %d %d curr1-%d %d %d curr2-%d curr-%d %d %d\n",s1,e1,curr1,s2,e2,curr2,curr,c1,c2);

        // curr1=kthSmallest(arr1,s1,e1,step);
        // curr2=kthSmallest(arr2,s2,e2,step);
        // for(int i=0;i<n1;i++)
        //     printf("A%d,",arr1[i]);
        // printf("\n");
        c1=kthSmallest(arr1,s1,e1,step/2);
        c2=kthSmallest(arr2,s2,e2,step/2);
        // for(int i=0;i<n1;i++)
        //     printf("A%d,",arr1[i]);
        // printf("\n");
        
        // printf("B %d %d curr1-%d %d %d curr2-%d curr-%d %d %d\n",s1,e1,curr1,s2,e2,curr2,curr,c1,c2);
        // if(c1>n1 || c2>n2){
        //     printf("error %d %d \n\n\n",step,k);
        //     // Return 0;
        //     c1=c2=1;
        // }
        if(c1>n1 || c2>n2){
            printf("error %d  ",step);
            printf("k=%d s1=%d e1=%d s2=%d e2=%d\n\n\n\n ",k,s1,e1,s2,e2);
            // if(arr1[s1]<arr2[s2]){
            //     ans=arr1[curr1];
            // }
            // else{
            //     ans=arr2[curr2];
            // }
            // break;
        }

        else{
            if(arr1[c1]>arr2[c2]){
                printf("CASE 1\n");
                e1=c1-1;
                s2=c2+1;
                if(e1<0)
                    e1=0;
                if(s2>n2)
                    s2=n2;
                if(e1<s1)
                    e1=c1;
                if(s2>e2)
                    s2=c2;
                // curr2=c2;
                // curr=curr+c2-s2+1;
                // curr=s1+s2;
                // ans=arr2[c2];
                // step=step-(c2-s2+1);
            }
            else if(arr1[c1]<arr2[c2]){
                printf("CASE 2\n");
                s1=c1+1;
                e2=c2-1;
                if(s1>n1)
                    s1=n1;
                if(e2<0)
                    e2=0;
                if(s1>e1)
                    s1=c1;
                if(e2<s2)
                    e2=c2;
                // curr1=c1;
                // curr+=c1-s1+1;
                // curr=curr1+curr2;
                // curr=s1+s2;
                // ans=arr1[c1];
                // step=step-(c1-s1+1);
            }
            else{
                printf("CASE 3\n");
                s1=c1+1;
                s2=c2+1;
                if(s1>n1)
                    s1=n1;
                if(s2>n2)
                    s2=n2;
                if(s1>e1)
                    s1=c1;
                if(s2>e2)
                    s2=c2;
                // if(s1>e1)
                //     s1=c1;
                // if(s2>e2)
                //     s2=0;
                // curr1=c1;
                // curr2=c2;
                // curr+=c1-s1+1 + c2-s2+1;
                // curr=curr1+curr2;
                // curr=s1+s2;
                // ans=arr1[c1];
                // step=step-(c1-s1+1 + c2-s2+1);
            }
        }
        // printf("C %d %d curr1-%d %d %d curr2-%d curr-%d %d %d\n",s1,e1,curr1,s2,e2,curr2,curr,c1,c2);
        for(int i=s1;i<=e1;i++)
            printf("%d-",arr1[i]);
        printf("\n");
        for(int i=s2;i<=e2;i++)
            printf("%d-",arr2[i]);
        // printf("\n REQUI %d %d %d %d\n",curr1,curr2,curr,k);
        printf("\n");
        

        if(s2==e2){
            printf("\n EQUAL @2\n");
            curr=s1+s2;
            int temp=kthSmallest(arr1,s1,e1,k-curr);
            printf("curr=%d k=%d temp=%d s1=%d e1=%d s2=%d e2=%d\n ",curr,k,temp,s1,e1,s2,e2);

            // for(int i=s1;i<=e1;i++)
            //     printf("%d,",arr1[i]);
            // printf("\n");
            // int temp=kthSmallest(arr1,s1,e1,k-curr+1);
            // printf("\n DOING %d %d %d %d curr-%d k-%d valOFk-%d temp-%d\n",s1,e1,curr1,curr2,curr,k,k-curr+1,temp);
            // for(int i=s1;i<=e1;i++)
            //     printf("%d,",arr1[i]);
            // printf("\n");
            ans=arr1[temp];
            // printf("HERE0 %d \n",ans);
            // if(arr2[s2]>temp){
            //     ans=arr1[temp];
            //     printf("HERE1 %d \n",ans);
            // }
            // else if(temp-1>=s1){
            //     ans=max(arr1[temp-1],arr2[s2]);
            //     printf("HERE2 %d \n",ans);
            // }
            // else{
            //     ans=arr2[s2];
            //     printf("HERE3 %d \n",ans);
            // }
            break;
        }
        else if(s1==e1){
            printf("\n EQUAL @1\n");
            curr=s1+s2;
            int temp=kthSmallest(arr2,s2,e2,k-curr);
            printf("curr=%d k=%d temp=%d s1=%d e1=%d s2=%d e2=%d\n ",curr,k,temp,s1,e1,s2,e2);
            ans=arr2[temp];
            break;

        }
        if(s1+s2==k || s1+s2==k+1){
            printf("REAHED END\n");
            break;
        }
        // if(s1+s2)
        printf("STEP= %d\n",step);
        step=(step+1)/2;
        getchar();



    }
    // step=k;
    // while(curr!=1){
    //     printf("A %d %d curr1-%d  curr-%d %d\n",s1,e1,curr1,curr,c1);

    //     curr1=kthSmallest(arr1,s1,e1,step);
    //     c1=kthSmallest(arr1,s1,e1,step/2);
    //     printf("A %d %d curr1-%d  curr-%d %d\n",s1,e1,curr1,curr,c1);
    //     // if(c1>n1 || c2>n2){
    //     //     printf("error %d %d \n\n\n",step,k);
    //     //     // Return 0;
    //     //     c1=c2=1;
    //     // }
        
    //     printf("A %d %d curr1-%d  curr-%d %d\n",s1,e1,curr1,curr,c1);
    //     for(int i=s1;i<=e1;i++)
    //         printf("%d,",arr1[i]);
    //     printf("\n");
    //     for(int i=s2;i<=e2;i++)
    //         printf("%d,",arr2[i]);
    //     printf("\n");
    //     step/=2;
    //     getchar();



    // }
    printf("ANS=%d %d\n",arr1[s1],arr2[s2]);
    return 0;
}