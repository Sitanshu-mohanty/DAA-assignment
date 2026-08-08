/*
 * Dictionary ADT benchmark
 * Implements the seven operations on:
 * 1) unsorted array
 * 2) sorted array
 * 3) singly linked unsorted list
 * 4) singly linked sorted list
 * 5) doubly linked unsorted list
 * 6) doubly linked sorted list
 *
 * The benchmark writes CSV data for plotting.
 * Complexity assumptions are documented in README.md.
 */

#ifdef _WIN32
#include <windows.h>
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct { int key; int value; } Item;
static volatile long long sink = 0;

static double now_sec(void)
{
#ifdef _WIN32
    static LARGE_INTEGER frequency;
    LARGE_INTEGER counter;

    if (frequency.QuadPart == 0)
        QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&counter);

    return (double)counter.QuadPart /
           (double)frequency.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (double)ts.tv_sec +
           (double)ts.tv_nsec / 1e9;
#endif
}

/* -------------------- Unsorted Array -------------------- */
typedef struct {
    Item *a;
    int n, cap;
} UArray;

static UArray ua_create(int cap) {
    UArray d = {malloc((size_t)cap * sizeof(Item)), 0, cap};
    if (!d.a) { perror("malloc"); exit(EXIT_FAILURE); }
    return d;
}
static void ua_free(UArray *d) { free(d->a); d->a=NULL; d->n=d->cap=0; }
static Item *ua_search(UArray *d, int key) {
    for (int i=0;i<d->n;i++) if (d->a[i].key==key) return &d->a[i];
    return NULL;
}
static void ua_insert(UArray *d, Item x) {
    if (d->n == d->cap) { d->cap *= 2; d->a = realloc(d->a, (size_t)d->cap*sizeof(Item)); }
    d->a[d->n++] = x;
}
/* Given pointer x. Order is not preserved: replace x with last item. */
static void ua_delete(UArray *d, Item *x) {
    int idx = (int)(x - d->a);
    if (idx < 0 || idx >= d->n) return;
    d->a[idx] = d->a[d->n-1];
    d->n--;
}
static Item *ua_min(UArray *d) {
    if (!d->n) return NULL;
    int p=0; for (int i=1;i<d->n;i++) if(d->a[i].key<d->a[p].key) p=i;
    return &d->a[p];
}
static Item *ua_max(UArray *d) {
    if (!d->n) return NULL;
    int p=0; for (int i=1;i<d->n;i++) if(d->a[i].key>d->a[p].key) p=i;
    return &d->a[p];
}
static Item *ua_pred(UArray *d, Item *x) {
    if (!x) return NULL;
    int k=x->key, p=-1;
    for(int i=0;i<d->n;i++) if(d->a[i].key<k && (p<0 || d->a[i].key>d->a[p].key)) p=i;
    return p<0?NULL:&d->a[p];
}
static Item *ua_succ(UArray *d, Item *x) {
    if (!x) return NULL;
    int k=x->key, p=-1;
    for(int i=0;i<d->n;i++) if(d->a[i].key>k && (p<0 || d->a[i].key<d->a[p].key)) p=i;
    return p<0?NULL:&d->a[p];
}

/* -------------------- Sorted Array -------------------- */
typedef struct {
    Item *a;
    int n, cap;
} SArray;

static SArray sa_create(int cap) {
    SArray d = {malloc((size_t)cap * sizeof(Item)), 0, cap};
    if (!d.a) { perror("malloc"); exit(EXIT_FAILURE); }
    return d;
}
static void sa_free(SArray *d) { free(d->a); d->a=NULL; d->n=d->cap=0; }
static Item *sa_search(SArray *d, int key) {
    int lo=0, hi=d->n-1;
    while(lo<=hi) {
        int mid=lo+(hi-lo)/2;
        if(d->a[mid].key==key) return &d->a[mid];
        if(d->a[mid].key<key) lo=mid+1; else hi=mid-1;
    }
    return NULL;
}
static void sa_insert(SArray *d, Item x) {
    if(d->n==d->cap){ d->cap*=2; d->a=realloc(d->a,(size_t)d->cap*sizeof(Item)); }
    int i=d->n;
    while(i>0 && d->a[i-1].key>x.key){ d->a[i]=d->a[i-1]; i--; }
    d->a[i]=x; d->n++;
}
static void sa_delete(SArray *d, Item *x) {
    int idx=(int)(x-d->a);
    if(idx<0 || idx>=d->n) return;
    for(int i=idx;i<d->n-1;i++) d->a[i]=d->a[i+1];
    d->n--;
}
static Item *sa_min(SArray *d){ return d->n?&d->a[0]:NULL; }
static Item *sa_max(SArray *d){ return d->n?&d->a[d->n-1]:NULL; }
static Item *sa_pred(SArray *d, Item *x){
    if(!x) return NULL;
    int i=(int)(x-d->a);
    return i>0?&d->a[i-1]:NULL;
}
static Item *sa_succ(SArray *d, Item *x){
    if(!x) return NULL;
    int i=(int)(x-d->a);
    return i+1<d->n?&d->a[i+1]:NULL;
}

/* -------------------- Singly Linked List -------------------- */
typedef struct SNode { Item item; struct SNode *next; } SNode;
typedef struct { SNode *head; int n; } SList;

static SNode *sn_new(int key){ SNode *p=malloc(sizeof(*p)); if(!p){perror("malloc");exit(EXIT_FAILURE);} p->item=(Item){key,key}; p->next=NULL; return p; }
static void sl_free(SList *d){ SNode *p=d->head; while(p){SNode *q=p->next;free(p);p=q;} d->head=NULL;d->n=0; }
static SNode *slu_search(SList *d,int key){ for(SNode*p=d->head;p;p=p->next)if(p->item.key==key)return p;return NULL; }
static void slu_insert(SList*d,Item x){SNode*p=sn_new(x.key);p->item=x;p->next=d->head;d->head=p;d->n++;}
static void slu_delete(SList*d,SNode*x){
    if(!x||!d->head)return;
    if(d->head==x){d->head=x->next;free(x);d->n--;return;}
    SNode*p=d->head;while(p->next && p->next!=x)p=p->next;
    if(p->next==x){p->next=x->next;free(x);d->n--;}
}
static SNode *slu_min(SList*d){SNode*r=NULL;for(SNode*p=d->head;p;p=p->next)if(!r||p->item.key<r->item.key)r=p;return r;}
static SNode *slu_max(SList*d){SNode*r=NULL;for(SNode*p=d->head;p;p=p->next)if(!r||p->item.key>r->item.key)r=p;return r;}
static SNode *slu_pred(SList*d,SNode*x){SNode*p=d->head,*prev=NULL;while(p&&p!=x){prev=p;p=p->next;}return p==x?prev:NULL;}
static SNode *slu_succ(SList*d,SNode*x){(void)d;return x?x->next:NULL;}

static SNode *sls_search(SList*d,int key){for(SNode*p=d->head;p;p=p->next){if(p->item.key==key)return p;if(p->item.key>key)break;}return NULL;}
static void sls_insert(SList*d,Item x){
    SNode*n=sn_new(x.key);n->item=x;
    if(!d->head||x.key<d->head->item.key){n->next=d->head;d->head=n;d->n++;return;}
    SNode*p=d->head;while(p->next&&p->next->item.key<x.key)p=p->next;
    n->next=p->next;p->next=n;d->n++;
}
static void sls_delete(SList*d,SNode*x){ /* pointer supplied; find predecessor */
    if(!x||!d->head)return;
    if(d->head==x){d->head=x->next;free(x);d->n--;return;}
    SNode*p=d->head;while(p->next&&p->next!=x)p=p->next;
    if(p->next==x){p->next=x->next;free(x);d->n--;}
}
static SNode *sls_min(SList*d){return d->head;}
static SNode *sls_max(SList*d){SNode*p=d->head;if(!p)return NULL;while(p->next)p=p->next;return p;}
static SNode *sls_pred(SList*d,SNode*x){return slu_pred(d,x);}
static SNode *sls_succ(SList*d,SNode*x){(void)d; return x?x->next:NULL;}

/* -------------------- Doubly Linked List -------------------- */
typedef struct DNode { Item item; struct DNode *prev,*next; } DNode;
typedef struct { DNode *head; int n; } DList;

static DNode *dn_new(int key){DNode*p=malloc(sizeof(*p));if(!p){perror("malloc");exit(EXIT_FAILURE);}p->item=(Item){key,key};p->prev=p->next=NULL;return p;}
static void dl_free(DList*d){DNode*p=d->head;while(p){DNode*q=p->next;free(p);p=q;}d->head=NULL;d->n=0;}
static DNode *dlu_search(DList*d,int key){for(DNode*p=d->head;p;p=p->next)if(p->item.key==key)return p;return NULL;}
static void dlu_insert(DList*d,Item x){DNode*p=dn_new(x.key);p->item=x;p->next=d->head;if(d->head)d->head->prev=p;d->head=p;d->n++;}
static void dlu_delete(DList*d,DNode*x){if(!x)return;if(x->prev)x->prev->next=x->next;else d->head=x->next;if(x->next)x->next->prev=x->prev;free(x);d->n--;}
static DNode *dlu_min(DList*d){DNode*r=NULL;for(DNode*p=d->head;p;p=p->next)if(!r||p->item.key<r->item.key)r=p;return r;}
static DNode *dlu_max(DList*d){DNode*r=NULL;for(DNode*p=d->head;p;p=p->next)if(!r||p->item.key>r->item.key)r=p;return r;}
static DNode *dlu_pred(DList*d,DNode*x){(void)d;return x?x->prev:NULL;}
static DNode *dlu_succ(DList*d,DNode*x){(void)d;return x?x->next:NULL;}

static DNode *dls_search(DList*d,int key){for(DNode*p=d->head;p;p=p->next){if(p->item.key==key)return p;if(p->item.key>key)break;}return NULL;}
static void dls_insert(DList*d,Item x){
    DNode*n=dn_new(x.key);n->item=x;
    if(!d->head||x.key<d->head->item.key){n->next=d->head;if(d->head)d->head->prev=n;d->head=n;d->n++;return;}
    DNode*p=d->head;while(p->next&&p->next->item.key<x.key)p=p->next;
    n->next=p->next;n->prev=p;p->next=n;if(n->next)n->next->prev=n;d->n++;
}
static void dls_delete(DList*d,DNode*x){dlu_delete(d,x);}
static DNode *dls_min(DList*d){return d->head;}
static DNode *dls_max(DList*d){DNode*p=d->head;if(!p)return NULL;while(p->next)p=p->next;return p;}
static DNode *dls_pred(DList*d,DNode*x){(void)d;return x?x->prev:NULL;}
static DNode *dls_succ(DList*d,DNode*x){(void)d;return x?x->next:NULL;}

/* -------------------- Benchmark helpers -------------------- */
enum { OP_SEARCH, OP_INSERT, OP_DELETE, OP_MAX, OP_MIN, OP_PRED, OP_SUCC, OP_COUNT };
static const char *op_name[OP_COUNT]={"search","insert","delete","maximum","minimum","predecessor","successor"};

typedef enum { DS_UA, DS_SA, DS_SLU, DS_SLS, DS_DLU, DS_DLS, DS_COUNT } DS;
static const char *ds_name[DS_COUNT]={
    "unsorted_array","sorted_array","singly_unsorted","singly_sorted",
    "doubly_unsorted","doubly_sorted"
};

static int repeats_for(int n){
    int r=10000000/n;
    if(r<5) r=5;
    if(r>100000) r=100000;
    return r;
}

/* Build helpers: keys 1..n, in sorted or shuffled insertion order as needed. */
static void build_ua(UArray*d,int n){for(int i=1;i<=n;i++)ua_insert(d,(Item){i,i});}
static void build_sa(SArray*d,int n){
    for(int i=1;i<=n;i++) d->a[d->n++] = (Item){i,i};
}
static void build_slu(SList*d,int n){for(int i=n;i>=1;i--)slu_insert(d,(Item){i,i});}
static void build_sls(SList*d,int n){
    for(int i=n;i>=1;i--){
        SNode*p=sn_new(i); p->item=(Item){i,i}; p->next=d->head; d->head=p; d->n++;
    }
}
static void build_dlu(DList*d,int n){for(int i=n;i>=1;i--)dlu_insert(d,(Item){i,i});}
static void build_dls(DList*d,int n){
    for(int i=n;i>=1;i--){
        DNode*p=dn_new(i); p->item=(Item){i,i}; p->next=d->head;
        if(d->head) d->head->prev=p;
        d->head=p; d->n++;
    }
}

/* Time one operation. For insert/delete, preparation and undo are outside the timer. */

/* Clean benchmark implementation: returns average nanoseconds per operation.
   Preparation/undo is outside the timed interval. */
#define TIME_LOOP(CODE, UNDO) \
    do { \
        double _start=now_sec(); \
        for(int _r=0; _r<reps; _r++){ CODE; } \
        double _end=now_sec(); \
        (void)(_end-_start); \
    } while(0)

/*
 * To keep the source readable and reliable, each operation is benchmarked
 * in a dedicated function. We use repetitions for timing resolution.
 */
static double bench(int ds, int op, int n) {
    int reps = repeats_for(n);
    double total = 0.0, t0, t1;

#define ADD_TIMED(OPCODE) do { t0=now_sec(); OPCODE; t1=now_sec(); total += t1-t0; } while(0)

    if(ds==DS_UA){
        UArray d=ua_create(n+2); build_ua(&d,n);
        if(op==OP_SEARCH) for(int r=0;r<reps;r++){ ADD_TIMED(Item*x=ua_search(&d,n+1); sink+=x?x->key:1;); }
        else if(op==OP_INSERT) for(int r=0;r<reps;r++){ ADD_TIMED(ua_insert(&d,(Item){0,0}); sink+=d.n;); Item*x=ua_search(&d,0); ua_delete(&d,x); }
        else if(op==OP_DELETE) for(int r=0;r<reps;r++){ Item*x=ua_search(&d,n); ADD_TIMED(ua_delete(&d,x); sink+=d.n;); ua_insert(&d,(Item){n,n}); }
        else if(op==OP_MAX) for(int r=0;r<reps;r++){ ADD_TIMED(Item*x=ua_max(&d); sink+=x->key;); }
        else if(op==OP_MIN) for(int r=0;r<reps;r++){ ADD_TIMED(Item*x=ua_min(&d); sink+=x->key;); }
        else if(op==OP_PRED) { Item*z=ua_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(Item*x=ua_pred(&d,z); sink+=x?x->key:0;); } }
        else { Item*z=ua_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(Item*x=ua_succ(&d,z); sink+=x?x->key:0;); } }
        ua_free(&d);
    } else if(ds==DS_SA){
        SArray d=sa_create(n+2); build_sa(&d,n);
        if(op==OP_SEARCH) for(int r=0;r<reps;r++){ ADD_TIMED(Item*x=sa_search(&d,n+1); sink+=x?x->key:1;); }
        else if(op==OP_INSERT) for(int r=0;r<reps;r++){ ADD_TIMED(sa_insert(&d,(Item){0,0}); sink+=d.n;); Item*x=sa_search(&d,0); sa_delete(&d,x); }
        else if(op==OP_DELETE) for(int r=0;r<reps;r++){ Item*x=sa_search(&d,1); ADD_TIMED(sa_delete(&d,x); sink+=d.n;); sa_insert(&d,(Item){1,1}); }
        else if(op==OP_MAX) for(int r=0;r<reps;r++){ ADD_TIMED(Item*x=sa_max(&d); sink+=x->key;); }
        else if(op==OP_MIN) for(int r=0;r<reps;r++){ ADD_TIMED(Item*x=sa_min(&d); sink+=x->key;); }
        else if(op==OP_PRED) { Item*z=sa_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(Item*x=sa_pred(&d,z); sink+=x?x->key:0;); } }
        else { Item*z=sa_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(Item*x=sa_succ(&d,z); sink+=x?x->key:0;); } }
        sa_free(&d);
    } else if(ds==DS_SLU){
        SList d={0}; build_slu(&d,n);
        if(op==OP_SEARCH) for(int r=0;r<reps;r++){ ADD_TIMED(SNode*x=slu_search(&d,n+1); sink+=x?x->item.key:1;); }
        else if(op==OP_INSERT) for(int r=0;r<reps;r++){ ADD_TIMED(slu_insert(&d,(Item){0,0}); sink+=d.n;); SNode*x=d.head; slu_delete(&d,x); }
        else if(op==OP_DELETE) for(int r=0;r<reps;r++){ SNode*x=slu_search(&d,n); ADD_TIMED(slu_delete(&d,x); sink+=d.n;); slu_insert(&d,(Item){n,n}); }
        else if(op==OP_MAX) for(int r=0;r<reps;r++){ ADD_TIMED(SNode*x=slu_max(&d); sink+=x->item.key;); }
        else if(op==OP_MIN) for(int r=0;r<reps;r++){ ADD_TIMED(SNode*x=slu_min(&d); sink+=x->item.key;); }
        else if(op==OP_PRED) { SNode*z=slu_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(SNode*x=slu_pred(&d,z); sink+=x?x->item.key:0;); } }
        else { SNode*z=slu_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(SNode*x=slu_succ(&d,z); sink+=x?x->item.key:0;); } }
        sl_free(&d);
    } else if(ds==DS_SLS){
        SList d={0}; build_sls(&d,n);
        if(op==OP_SEARCH) for(int r=0;r<reps;r++){ ADD_TIMED(SNode*x=sls_search(&d,n+1); sink+=x?x->item.key:1;); }
        else if(op==OP_INSERT) for(int r=0;r<reps;r++){ ADD_TIMED(sls_insert(&d,(Item){n+1,n+1}); sink+=d.n;); SNode*x=sls_search(&d,n+1); sls_delete(&d,x); }
        else if(op==OP_DELETE) for(int r=0;r<reps;r++){ SNode*x=sls_search(&d,n); ADD_TIMED(sls_delete(&d,x); sink+=d.n;); sls_insert(&d,(Item){n,n}); }
        else if(op==OP_MAX) for(int r=0;r<reps;r++){ ADD_TIMED(SNode*x=sls_max(&d); sink+=x->item.key;); }
        else if(op==OP_MIN) for(int r=0;r<reps;r++){ ADD_TIMED(SNode*x=sls_min(&d); sink+=x?x->item.key:0;); }
        else if(op==OP_PRED) { SNode*z=sls_search(&d,n); for(int r=0;r<reps;r++){ ADD_TIMED(SNode*x=sls_pred(&d,z); sink+=x?x->item.key:0;); } }
        else { SNode*z=sls_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(SNode*x=sls_succ(&d,z); sink+=x?x->item.key:0;); } }
        sl_free(&d);
    } else if(ds==DS_DLU){
        DList d={0}; build_dlu(&d,n);
        if(op==OP_SEARCH) for(int r=0;r<reps;r++){ ADD_TIMED(DNode*x=dlu_search(&d,n+1); sink+=x?x->item.key:1;); }
        else if(op==OP_INSERT) for(int r=0;r<reps;r++){ ADD_TIMED(dlu_insert(&d,(Item){0,0}); sink+=d.n;); DNode*x=d.head; dlu_delete(&d,x); }
        else if(op==OP_DELETE) for(int r=0;r<reps;r++){ DNode*x=dlu_search(&d,n); ADD_TIMED(dlu_delete(&d,x); sink+=d.n;); dlu_insert(&d,(Item){n,n}); }
        else if(op==OP_MAX) for(int r=0;r<reps;r++){ ADD_TIMED(DNode*x=dlu_max(&d); sink+=x->item.key;); }
        else if(op==OP_MIN) for(int r=0;r<reps;r++){ ADD_TIMED(DNode*x=dlu_min(&d); sink+=x->item.key;); }
        else if(op==OP_PRED) { DNode*z=dlu_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(DNode*x=dlu_pred(&d,z); sink+=x?x->item.key:0;); } }
        else { DNode*z=dlu_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(DNode*x=dlu_succ(&d,z); sink+=x?x->item.key:0;); } }
        dl_free(&d);
    } else {
        DList d={0}; build_dls(&d,n);
        if(op==OP_SEARCH) for(int r=0;r<reps;r++){ ADD_TIMED(DNode*x=dls_search(&d,n+1); sink+=x?x->item.key:1;); }
        else if(op==OP_INSERT) for(int r=0;r<reps;r++){ ADD_TIMED(dls_insert(&d,(Item){n+1,n+1}); sink+=d.n;); DNode*x=dls_search(&d,n+1); dls_delete(&d,x); }
        else if(op==OP_DELETE) for(int r=0;r<reps;r++){ DNode*x=dls_search(&d,n); ADD_TIMED(dls_delete(&d,x); sink+=d.n;); dls_insert(&d,(Item){n,n}); }
        else if(op==OP_MAX) for(int r=0;r<reps;r++){ ADD_TIMED(DNode*x=dls_max(&d); sink+=x->item.key;); }
        else if(op==OP_MIN) for(int r=0;r<reps;r++){ ADD_TIMED(DNode*x=dls_min(&d); sink+=x?x->item.key:0;); }
        else if(op==OP_PRED) { DNode*z=dls_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(DNode*x=dls_pred(&d,z); sink+=x?x->item.key:0;); } }
        else { DNode*z=dls_search(&d,n/2); for(int r=0;r<reps;r++){ ADD_TIMED(DNode*x=dls_succ(&d,z); sink+=x?x->item.key:0;); } }
        dl_free(&d);
    }
#undef ADD_TIMED
    return total*1e9/reps;
}

int main(void){
    const int sizes[] = {100,500,1000,5000,10000,50000,100000};
    const int ns=(int)(sizeof(sizes)/sizeof(sizes[0]));
    FILE *fp=fopen("results/benchmark.csv","w");
    if(!fp){perror("results/benchmark.csv");return EXIT_FAILURE;}
    fprintf(fp,"data_structure,operation,n,time_ns\n");
    fprintf(stderr,"Benchmarking...\n");
    for(int d=0;d<DS_COUNT;d++){
        for(int op=0;op<OP_COUNT;op++){
            for(int i=0;i<ns;i++){
                int n=sizes[i];
                double t=bench(d,op,n);
                fprintf(fp,"%s,%s,%d,%.3f\n",ds_name[d],op_name[op],n,t);
                fflush(fp);
            }
            fprintf(stderr,"done: %-20s %-12s\n",ds_name[d],op_name[op]);
        }
    }
    fclose(fp);
    fprintf(stderr,"Done. sink=%lld\n",sink);
    return EXIT_SUCCESS;
}
