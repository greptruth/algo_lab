#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#define REP(i, n) for(i=0; i<n; ++i)
#define flsh fflush(stdout);
#define pri(n) printf("%d ", n);flsh; 
#define prs(s) printf("%s", s);flsh ;
#define pr_arr(arr, n) {{int i; REP(i, n)pri(arr[i]); endl;flsh;}}
#define space putchar(' ');flsh ;
#define endl putchar('\n');flsh ;
#define MAX 100
#define swap(a, b, T) {{T tmp = (a); (a) = (b); (b) = tmp;}}
int comp(const void* a, const void* b) { return *(int*)(a)-*(int*)(b); }
int INF = (1 << 30);
int partition(int arr[], int l, int r, int x)
{
	// Search for x in arr[l..r] and move it to end
	int i;
	for (i = l; i<r; i++)
	if (arr[i] == x)
		break;
	swap(arr[i], arr[r], int);

	// Standard partition algorithm
	i = l;
	for (int j = l; j <= r - 1; j++)
	{
		if (arr[j] <= x)
		{
			swap(arr[i], arr[j], int);
			i++;
		}
	}
	swap(arr[i], arr[r], int);
	return i;
}
int findMedian(int arr[], int n)
{
//	prs("sorting : ");
//	pr_arr(arr, n); endl;
	if (n>5) {
		prs("U shud not use it for n>5\n");
		return -1;
	}
	if (n < 1) {
		printf("HOOOOOOOOOOOOOOOOOOOOO\n");
		return -(1 << 24);
	}
	if (n == 1) {
		return arr[0];
	}
	qsort(arr, n, sizeof(int), comp);  // Sort the array
	return arr[n / 2];   // Return middle element
}
int* kthSmallest(int arr[], int l, int r, int k)
{
	if (r - l == 0 && k == 1)
		return &arr[r];
	// If k is smaller than number of elements in array
	if (k > 0 && k <= r - l + 1)
	{
		int n = r - l + 1;
		int i, median[MAX];
		for (i = 0; i<n / 5; i++)
			median[i] = findMedian(arr + l + i * 5, 5);
		if (i * 5 < n) //For last group with less than 5 elements
		{
			median[i] = findMedian(arr + l + i * 5, n % 5);
			i++;
		}
		int medOfMed = (i == 1) ? median[i - 1] :
			*kthSmallest(median, 0, i - 1, i / 2);
		int pos = partition(arr, l, r, medOfMed);
		if (pos - l == k - 1)
			return &arr[pos];
		if (pos - l > k - 1)  // If position is more, recur for left
			return kthSmallest(arr, l, pos - 1, k);
		return kthSmallest(arr, pos + 1, r, k - pos + l - 1);
	}
	return &INF;
}
int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int getkfrom2arr(int arr1[], int arr2[], const int n1, const int n2, const int k)
{
/*	if (n1 <= 1) {
		return max(*kthSmallest(arr2, 0, n2 - 1, k - n1), n1 == 0 ? INT_MIN : arr1[0]);
	} else if (n2 <= 1) {
		return max(*kthSmallest(arr1, 0, n1 - 1, k - n2), n2 == 0 ? INT_MIN : arr2[0]);
	}*/
	int k2 = max(1, (k - 1) / 2);
	int src[2] = { min(k2, n1), min(k2, n2) };
	int a = *kthSmallest(arr1, 0, n1 - 1, src[0]);// -arr1;
	int b = *kthSmallest(arr2, 0, n2 - 1, src[1]);// -arr2;
//	int a = arr1[ida], b = arr2[idb];
/*	pri(a); pri(b); pri(k);endl
	pr_arr(arr1, n1);
	pr_arr(arr2, n2);
	endl;*/
	if (k < 2)
		return min(a, b);
//	else if (k == 2)
//		return max(a, b);
	int last1 = min(n1, n1 );
	if (arr1[last1] == -999 || arr1[last1] >(1 << 15));
//		last1--;
	int last2 = min(n2, n2 );
	if (arr2[last2] == -999 || arr2[last2] > (1 << 15));
///		last2--;
	if (b == a) {
		return getkfrom2arr(arr1 + src[0], arr2 + src[1], n1 - src[0], n2 - src[1], k - k2 * 2); // ?
	}
	else if (b < a) {
		return getkfrom2arr(arr1, arr2 + src[1], last1, n2 - src[1], k - k2);
	}
	else {
		return getkfrom2arr(arr1+src[0], arr2 , n1-src[0], last2, k - k2);
	}
}
void gen(int *arr1, int*arr2, const int n)
{
	int done[1000] = { 0 },i;
	REP(i, n) {
		do{
			arr1[i] = rand() % 100;
		} while (done[arr1[i]] == 1);
		done[arr1[i]] = 1;
	}
	REP(i, n) {
		do{
			arr2[i] = rand() % 100;
		} while (done[arr2[i]] == 1);
		done[arr2[i]] = 1;
	}
}
int main(int argc,char** argv) 
{
	int *arr1,*arr2,*arr; 
	int n,i;//=atoi(argv[1]) 
	if(argc==2){
		//generate arrays with distinct values
		n=atoi(argv[1]);
		arr1=(int*)malloc(sizeof(int)*n);
		arr2=(int*)malloc(sizeof(int)*n);
		arr=(int*)malloc(sizeof(int)*2*n);
		for(i=0;i<n;i++){
			int pos=rand()%(2*n);
			arr1[i]=i+1;
		}
		for(i=n;i<2*n;i++){
			int pos=rand()%(2*n);
			arr2[i-n]=i+1;
		}
		for int i=0;i<n+m;i++
		int k=rand()%2*n;
		int ans=getkfrom2arr(arr1,arr2,n,n,k);
		for(i=0;i<n;i++){
			printf("%d,",arr1[i]);
		}
		printf("\n\n");
		for(i=0;i<n;i++){
			printf("%d,",arr2[i]);
		}
		printf("%dth %delement= %d\n",k,n,ans);

	}
	else{
		int k=atoi(argv[1]);
		n=atoi(argv[2]);
		arr1=(int*)malloc(sizeof(int)*n);
		arr2=(int*)malloc(sizeof(int)*n);
		for(i=0;i<n;i++){
			arr1[i]=atoi(argv[i+3]);
		}
		for(i=n;i<2*n;i++){
			arr2[i-n]=atoi(argv[i+3]);
		}

		for(i=0;i<n;i++){
			printf("%d,",arr1[i]);
		}
		printf("\n\n");
		for(i=0;i<n;i++){
			printf("%d,",arr2[i]);
		}
		printf("\n\n");
		int ans=getkfrom2arr(arr1,arr2,n,n,k);
		printf("%dth element= %d\n",k,ans);
	}
	return 0;
}