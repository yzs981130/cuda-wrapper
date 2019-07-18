#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cuda.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>


#define SIZE 10000

unsigned long long mod = 9973L;
static const char CONFIG_STRING[] = "WRAPPER_MAX_MEMORY";
static const char LIB_STRING[] = "libcuda.so";
static const char LOG_FILENAME[] = "/tmp/wrapper-log"

int open_flag = 0;
void *handle = NULL;
static size_t total_mem = 0L;
static size_t total_quota = 4217928960L; //default set to 4GB
static pthread_mutex_t mem_cnt_lock;
char *error;

struct HashArray
{
    unsigned long long key;
    size_t value;
    struct HashArray* next;
}allocsize[10000];

#define checkCudaErrors(err)  __checkCudaErrors (err, __FILE__, __LINE__)
CUresult __checkCudaErrors( CUresult err, const char *file, const int line ) {
    if( CUDA_SUCCESS != err) {
        fprintf(stderr,
                "CUDA Driver API error = %04d from file <%s>, line %i.\n",
                err, file, line );
        //exit(-1);
    }
    return err;
}

void getCurrentTime(char *buff) {
    time_t now = time (0);
    sTm = gmtime (&now);
    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
}

void addHash(unsigned long long key,size_t value) {
    int temp=key >> 19;
    if(allocsize[temp].key==0) {
        allocsize[temp].key=key;
        allocsize[temp].value=value;
	    printf("allocsize %lld %zu\n", key, value);
    } 
    else if(allocsize[temp].key==key) {
        allocsize[temp].value=value;     
    } 
    else {
        struct HashArray *p=&allocsize[temp]; 		
        while(p->key!=key&&p->next!=NULL) {  
            p=p->next;
        }
        if(p->key==key) {
            p->value=value;
        } 
        else {
            p->next=(struct HashArray*)malloc(sizeof(struct HashArray));
            p=p->next;
            p->key=key;
            p->value=value;
            p->next=NULL;
        }
    }   
}
size_t getHash(unsigned long long key) {
    int temp=key%mod;
    struct HashArray *p=&allocsize[temp];
    if (p == NULL) {
	    printf("miss\n");
    	return 0;
    }
    printf("pkey: %lld\n", p->key);
    while(p->key!=key&&p->next!=NULL) {
	    p=p->next;
    }		
    if (p->key == key) {
        printf("hit\n");
        return p->value;
    }
    else {
        printf("hash hit and miss\n");
        return 0;
    }
}

void set_quota() {
    char *q = NULL;
    q = getenv(CONFIG_STRING);
    if (q == NULL) {
        printf("set_quota: no env %s found. use default: %zu", CONFIG_STRING, total_quota);
    }
    else {
        total_quota = strtoull(q, NULL, 10);
        printf("set_quota: set total_quota: %zu", total_quota);
    }
}

void init_func() {
    int fd;
    fd = open(LOG_FILENAME, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open log file failed");
        exit(1);
    }

    if (dup2(fd, 1) == -1) {
        perror("dup2 failed"); 
        exit(1);
    }
    
    if(open_flag == 0 && handle == NULL) {
        //char *error;
    	handle = dlopen (LIB_STRING, RTLD_LAZY);
    	if (!handle) {
       	    fprintf (stderr, "%s\n", dlerror());
       	    exit(1);
    	}
	    open_flag = 1;
    	dlerror();
    }
    pthread_mutex_init(&mem_cnt_lock, NULL);
    set_quota();
}

void before_func() {
	
}


void post_func() {

}


CUresult cuInit(unsigned int Flags) {
    init_func();
    before_func();
    printf("init!!!\n");
    CUresult (*fakecuInit)(unsigned int);
    fakecuInit = dlsym(handle, "cuInit");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    post_func();
    CUresult r;
    r = checkCudaErrors((*fakecuInit)(Flags));
    return r;
}


CUresult cuMemGetInfo_v2(size_t *free, size_t *total) {
    before_func();
    CUresult (*fakecuMemGetInfo_v2)(size_t *, size_t *);
    fakecuMemGetInfo_v2 = dlsym(handle, "cuMemGetInfo_v2");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    r = checkCudaErrors((*fakecuMemGetInfo_v2)(free, total));
    //TODO: change free and total to proper value
    //*free =  *free / 2;
    //*total = *total / 2;
    printf("cumemgetinfo: free : %zu, total : %zu\n", *free, *total);
    post_func();
    return r;
}

int check_alloc_valid(size_t bytesize) {
    printf("lock mem in check_alloc_valid\n");
    pthread_mutex_lock(&mem_cnt_lock);	
    if(total_mem + bytesize > total_quota) {
        fprintf (stderr, "alloc %zu failed, total_mem %zu, quota %zu\n", bytesize, total_mem,  total_quota);
        printf("unlock mem in check_alloc_valid\n");
        pthread_mutex_unlock(&mem_cnt_lock);
        return 0;
    }
    printf("unlock mem in check\n");
    pthread_mutex_unlock(&mem_cnt_lock);
    return 1;
}

CUresult cuMemAlloc_v2(CUdeviceptr* dptr, size_t bytesize) {
    before_func();
    CUresult (*fakecuMemAlloc_v2)(CUdeviceptr* , size_t);
    fakecuMemAlloc_v2 = dlsym(handle, "cuMemAlloc_v2");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    post_func();

    if(check_alloc_valid(bytesize)) {
        printf("lock mem in cumemalloc\n");
        pthread_mutex_lock(&mem_cnt_lock);
        total_mem += bytesize;
        //printf("%d\n", dptr);
        //printf("bs: %zu\n", bytesize);
        pthread_mutex_unlock(&mem_cnt_lock);
        printf("unlock mem in cumemalloc\n");
        CUresult r = checkCudaErrors((*fakecuMemAlloc_v2)(dptr, bytesize));
        if(CUDA_SUCCESS != r) {
            printf("lock if r != CUDA_SUCCESS\n");
            pthread_mutex_lock(&mem_cnt_lock);
            total_mem -= bytesize;                  
            pthread_mutex_unlock(&mem_cnt_lock);
            printf("unlock if r != CUDA_SUCCESS\n ");
        }
        else {			
            addHash((unsigned long long)dptr,bytesize);
            //TODO: assert
            printf("cumemalloc: hash insert with bytesize %zu\n", bytesize);
            printf("cumemalloc: hash insert with bytesize %zu\n", getHash((unsigned long long)dptr));
        }
        return r;
    }
    else {
        return CUDA_ERROR_OUT_OF_MEMORY;
    }
}

CUresult cuMemFree_v2(CUdeviceptr dptr) {
    before_func();
    CUresult (*fakecuMemFree_v2)(CUdeviceptr);
    fakecuMemFree_v2 = dlsym(handle, "cuMemFree_v2");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    post_func();
    CUresult r = checkCudaErrors((*fakecuMemFree_v2)(dptr));
    if(CUDA_SUCCESS == r) {
        printf("lock mem in cumemfree\n");
        pthread_mutex_lock(&mem_cnt_lock);
        size_t tbytesize=getHash(dptr);
        printf("%lld %zu",dptr, tbytesize);
        total_mem -= tbytesize;
        printf("lock mem in cumemfree\n");
        pthread_mutex_unlock(&mem_cnt_lock);
    }
    return r;
}
