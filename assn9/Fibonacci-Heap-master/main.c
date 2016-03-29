#include <stdio.h>
// #include "heap.h"
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

typedef struct node node;
struct node{
  node* left;
  node* right;
  node* parent; // NULL iff this node is a root
  node* kid; // Any kid
  int key;
  void* value; // Arbitrary heap client data
  int hasLostKid; //Boolean, aka "mark"
  int degree; //number of kids
};

typedef node heap;
typedef node elem;
typedef struct{
    int key;     // Indicates the minimum
    void* value; //Arbitrary client data
} data;
data  elem_data(elem* x);


node* node_init(int key, void* value){
    node* newNode =(node*) malloc(sizeof(node));
    newNode->left = newNode->right = newNode;
    newNode->key = key;
    newNode->value = value;
    newNode->parent = NULL;
    newNode->kid = NULL;
    newNode->hasLostKid = 0;
    newNode->degree = 0;
    return newNode;
}

void node_free(node* toFree){
    toFree->degree = -1;
    free(toFree);
}

void node_kill(node* toKill){
    node* kid = toKill->kid;
    if (kid){
        kid->left->right = NULL;
        while(kid->right != NULL){
            kid = kid->right;
            node_kill(kid->left);
        }
        node_kill(kid);
    }
    node_free(toKill);
}

void node_add(node* old, node* newRight){
    node* oldRight = old->right;
    assert(old != newRight);
    assert(oldRight != newRight);
    old->right = newRight;
    oldRight->left = newRight;
    newRight->left = old;
    newRight->right = oldRight;
}


void print_data(data d){
    printf("%d,", d.key);
}
heap* heap_init(){
    return NULL;
}
elem* heap_add(heap** H, node* newNode);

elem* heap_insert(heap** H, int key, void* value){
    node* newNode = node_init(key, value);
    return heap_add(H, newNode);
}

int is_empty(heap* H){
    return H == NULL;
}

elem* heap_add(heap** H, node* newNode){
    assert(H);
    assert(newNode);
    node* oldNode = *H;
    newNode->parent = NULL;
    newNode->hasLostKid = 0;
    if (oldNode){ //nonempty heap
        node_add(oldNode, newNode);
        if (oldNode->key > newNode->key){ //new smallest
            *H = newNode;
        }
    }else{ //previously empty heap
        newNode->left = newNode;
        newNode->right = newNode;
        *H = newNode;
    }
    return newNode;
}

data  heap_min(heap* H){
    assert(H);
    data d;
    node* head = H;
    d.key = head->key;
    d.value = head->value;
    return d;
}

void  heap_consolidate(heap** H);
void  heap_match_degrees(heap** H, node** A, node* x);
node* heap_link(heap** H, node* x, node* y);
void  heap_remove_from(heap** H, node* x);

heap* heap_union(heap* H1, heap* H2){
    if(!H1) return H2;
    if(!H2) return H1;
    if (heap_min(H2).key < heap_min(H1).key){
        return heap_union(H2, H1);
    }

    node* H1first = H1;
    node* H1last = H1first->left;
    node* H2first = H2;
    node* H2last = H2first->left;

    H1last->right = H2first;
    H2first->left = H1last;
    H2last->right = H1first;
    H1first->left = H2last;

    return H1first;
}

data  heap_extract_min(heap** H){
    assert(H && *H);
    node* z = *H;
    data d = elem_data(z);
    node* first = z->kid;
    heap_remove_from(H, z);
    node_free(z);
    if (first){
        node* current = first->right;
        while (current != first){
            current->parent = NULL;
            current = current->right;
        }
        first->parent = NULL;
        *H = heap_union(*H, first);
    }
    heap_consolidate(H);
    return d;
}

void  heap_remove_from(heap** H, node* x){
    assert(!x->parent);
    if (x->right == x){
        *H = NULL;
    }else{
        x->left->right = x->right;
        x->right->left = x->left;
        *H = x->right;
    }
    x->left = x;
    x->right = x;
    x->parent = NULL;
}
void  heap_consolidate(heap** H){
    node* x = *H;
    int i;
    if (!x) return;
    node** A = (node**)calloc(100, sizeof(node));
    memset(A, '\0', 100);
    assert(x->degree >= 0);
    node* last = x->left;
    while(x != last){
        node* next = x->right;
        heap_match_degrees(H, A, x);
        x = next;
    }
    heap_match_degrees(H, A, last);
    *H = heap_init();
    for ( i=0; i<100; i++){
        if (A[i]){
            heap_add(H, A[i]);
        }
    }
    free(A);
}

void heap_match_degrees(heap** H, node** A, node* x){
    int d = x->degree;
    while(A[d]){
        if (d > 99){
            exit(1);
        }
        node* y = A[d];
        if (y != x){
            x = heap_link(H, x, y);
            A[d] = NULL;
            d++;
        }else{
            break;
        }
    }
    A[d] = x;
}
node* heap_link(heap** H, node* x, node* y){
    assert(x);
    assert(y);
    assert(x->degree == y->degree);
    if (x->key > y->key){
        return heap_link(H, y, x);
    }
    heap_remove_from(H, y);
    if (x->kid){
        node* z = x->kid;
        y->right = z;
        y->left = z->left;
        z->left->right = y;
        z->left = y;
    }
    y->parent = x;
    x->kid = y;
    x->degree++;
    y->hasLostKid = 0;
    return x;
}



void  heap_decrease_key(heap** H, elem* x, int newKey){
    assert(H && *H);
    assert(x && x->key >= newKey);
    x->key = newKey;
    if(x->parent && x->parent->key > newKey){
        if (x->left == x){
            assert(x->parent->degree == 2);
            x->parent->kid = NULL;
        }else{
            assert(x->parent->degree > 2);
            x->left->right = x->right;
            x->right->left = x->left;
            x->parent->kid = x->left;
        }
        x->parent->degree--;
        heap_add(H, x);
        if (! x->parent->hasLostKid){
            x->parent->hasLostKid = 1;
        }else{
            heap_decrease_key(H, x->parent, x->parent->key);
        }

    }else{
        if (newKey < (*H)->key){
            assert(!x->parent);
            *H = x;
        }
    }
}

void  heap_delete(heap** H, elem* x){
    heap_decrease_key(H, x, INT_MIN);
    heap_extract_min(H);
}

data  elem_data(elem* x){
    assert(x);
    data d;
    d.key = x->key;
    d.value = x->value;
    return d;
}

void heap_free(heap** H){
    node* header = *H;
    node* first = header;
    if (header){
        while(header != first){
            node* next = header->right;
            node_kill(header);
            header = next;
        }
    }
    *H = NULL;
}
int main(){
    // heap* myheap = heap_init();
    int i,j;
    heap* myheap[20],*Uheap;
    for(i=0;i<20;i++){
        // myheap[i]=(heap*)malloc(sizeof(heap*));
        myheap[i]=heap_init();
    }
    int k=10 + rand()%6;
    int m=100 + rand()%401;
    int *Nos = (int *)malloc(k*m*sizeof(int));
    // m=10;
    printf("k=%d m=%d \n",k,m);
    for(i=0;i<k*m;i++){
        Nos[i]=0;
    }
    for(i=1;i<=k;i++){
        for( j=0;j<m;j++){
            int pos=rand()%(k*m);
            while(Nos[pos]!=0){
                if(pos==k*m-1)
                    pos=0;
                else
                    pos++;
            }
            Nos[pos]=i;
            // printf("%d %d %d %d\n",i,j,pos,Nos[pos]);

        }
    }
    // for(int i=0;i<k*m;i++){
    //     printf("%d  ",Nos[i]);
    // }
    for( i=0;i<k*m;i++){
        heap_insert(&myheap[Nos[i]-1],i+1,NULL);
    }
    // for(int i=0;i<k;i++){
    //     while(!is_empty(myheap[i])){
    //         print_data(heap_extract_min(&myheap[i]));
    //     }
    //     printf("\n \n");
    // }
    Uheap=heap_init();
    Uheap=myheap[0];
    for(i=0;i<k;i++){
        Uheap=heap_union(Uheap,myheap[i]);
    }
    heap_consolidate(&Uheap);
    // printf("Union : \n \n");
    // while(!is_empty(Uheap)){
    //     print_data(heap_extract_min(&Uheap));
    // }
    for(i=0;i<k;i++)
        myheap[i]=heap_init();

    for( i=0;i<k;i++){
        for( j=0;j<m;j++){
            data temp=heap_extract_min(&Uheap);
            heap_insert(&myheap[i],temp.key,NULL);
        }
    }
    for( i=0;i<k;i++){
        while(!is_empty(myheap[i])){
            print_data(heap_extract_min(&myheap[i]));
        }
        printf("\n \n");
    }

    // int maxKey = 10; //100 to 100 thousand by power of 10
    // for (int i = 0; i<maxKey; i+=5){
    //     heap_insert(&myheap, i, NULL);
    // }
    // for (int i = 1; i<maxKey; i+=5){
    //     heap_insert(&myheap, i, NULL);
    // }
    // for (int i = 2; i<maxKey; i+=5){
    //     heap_insert(&myheap, i, NULL);
    // }
    // for (int i = 3; i<maxKey; i+=5){
    //     heap_insert(&myheap, i, NULL);
    // }
    // for (int i = 4; i<maxKey; i+=5){
    //     heap_insert(&myheap, i, NULL);
    // }
    // while (!is_empty(myheap)){
    //     print_data(heap_extract_min(&myheap));
    // }
    // heap_free(&myheap);
    return 0;
}
