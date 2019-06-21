#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cuda.h>
#include <string.h>
#include <pthread.h>

static const char LIB_STRING[] = "libcuda.so";

bool open_flag = false;
void *handle = NULL;
static size_t total_alloc = 0L;
static size_t total_free = 0L;
static size_t total_quota = 3821390336L;
static pthread_mutex_t alloc_cnt_lock;
static pthread_mutex_t free_cnt_lock;

#define checkCudaErrors(err)  __checkCudaErrors (err, __FILE__, __LINE__)
CUresult __checkCudaErrors( CUresult err, const char *file, const int line )
{
    if( CUDA_SUCCESS != err) {
        fprintf(stderr,
                "CUDA Driver API error = %04d from file <%s>, line %i.\n",
                err, file, line );
        //exit(-1);
    }
	return err;
}

void init_func() {
	if(open_flag == false && handle != NULL) {
		char *error;
    	handle = dlopen (LIB_STRING, RTLD_LAZY);
    	if (!handle) {
        	fprintf (stderr, "%s\n", dlerror());
        	exit(1);
    	}
		open_flag = true;
    	dlerror();
	}
	pthread_mutex_init(&alloc_cnt_lock, NULL);
	pthread_mutex_init(&free_cnt_lock, NULL);
}

void before_func() {
	
}


void post_func() {
    //dlclose(handle);
}


CUresult cuInit(unsigned int Flags) {
	init_func();
    before_func();
    CUresult (*fakecuInit)(unsigned int);
    fakecuInit = dlsym(handle, "cuInit");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	post_func();
    return checkCudaErrors((*fakecuInit)(Flags));
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
    *free =  *free / 2;
    *total = *total / 2;
    printf("free : %zu, total : %zu\n", *free, *total);
	post_func();

	return r;

}

bool check_alloc_valid(size_t bytesize) {
	pthread_mutex_lock(&alloc_cnt_lock);	
	pthread_mutex_lock(&free_cnt_lock);
	if(total_alloc + bytesize - total_free > total_quota) {
		fprintf (stderr, "alloc %zu failed, total_alloc %zu, total_free %zu, quota %zu\n", bytesize, total_alloc, total_free, total_quota);
		pthread_mutex_unlock(&free_cnt_lock, NULL);
		pthread_mutex_unlock(&alloc_cnt_lock, NULL);
		return false;
	}
	pthread_mutex_unlock(&free_cnt_lock, NULL);
	pthread_mutex_unlock(&alloc_cnt_lock, NULL);
	return true;
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
		CUresult r = checkCudaErrors((*fakecuMemAlloc_v2)(dptr, bytesize));
		if(CUDA_SUCCESS == r) {
			pthread_mutex_lock(&alloc_cnt_lock);
			total_alloc += bytesize;
			pthread_mutex_unlock(&alloc_cnt_lock, NULL);
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
		pthread_mutex_lock(&free_cnt_lock);
		total_free = 0;
		pthread_mutex_unlock(&free_cnt_lock, NULL);
	}
	return r;
}