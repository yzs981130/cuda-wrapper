#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cuda.h>
#include <string.h>
#include <pthread.h>
#include <cuda_runtime.h>
#include <nvml.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
//#include <helper_cuda.h>
#define SIZE 10000

unsigned long long mod = 9973L;

static const char LIB_STRING[] = "libcudart.so";
static const char CONFIG_STRING[] = "WRAPPER_MAX_MEMORY";
static const char LOG_FILENAME[] = "/tmp/wrapper-log";

int open_flag = 0;
void *handle = NULL;
static size_t total_mem = 0L;
static size_t total_quota = 4217928960L;
static pthread_mutex_t mem_cnt_lock;
char *error;
char timebuf[30];
nvmlReturn_t nvmlresult;
nvmlDevice_t nvmldevice;
long long cnt=0;


/*struct HashArray
{
    unsigned long long key;
    size_t value;
    struct HashArray* next;
}allocsize[10000];

void addHash(unsigned long long key,size_t value) {
    int temp=key >> 19;
    if(allocsize[temp].key==0) {
        allocsize[temp].key=key;
        allocsize[temp].value=value;
        //printf("allocsize %lld %zu\n", key, value);
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
    getCurrentTime(timebuf);
    printf("addHash\nTime: %s  addHash: key: %lld value: %zu\n", timebuf, key, value);  
}
size_t getHash(unsigned long long key) {
    int temp=key%mod;
    struct HashArray *p=&allocsize[temp];
    if (p == NULL) {
        printf("getHash miss\n");
        getCurrentTime(timebuf);
        printf("Time: %s  key: %lld \n", timebuf, key );
        return 0;
    }
    //printf("pkey: %lld\n", p->key);
    while(p->key!=key&&p->next!=NULL) {
        p=p->next;
    }       
    if (p->key == key) {
        printf("getHash hit\n");
        getCurrentTime(timebuf);
        printf("Time: %s  key: %lld value: %zu \n", timebuf, key ,p->value);
        return p->value;
    }
    else {
        printf("hash hit and miss\n");
        getCurrentTime(timebuf);
        printf("Time: %s  key: %lld \n", timebuf, key );        
        return 0;
    }
}

void set_quota() {
    char *q = NULL;
    q = getenv(CONFIG_STRING);
    if (q == NULL) {
        //printf("set_quota: no env %s found. use default: %zu", CONFIG_STRING, total_quota);
    }
    else {
        total_quota = strtoull(q, NULL, 10);
        //printf("set_quota: set total_quota: %zu", total_quota);
    }
}

void nvml_memquery() {
	nvmlMemory_t nvmlmemory;
    nvmlresult = nvmlDeviceGetMemoryInfo(nvmldevice, &nvmlmemory);
    printf("\nTotal installed FB memory %lld bytes \n", nvmlmemory.total);
    printf("Unallocated FB memory  %lld bytes \n", nvmlmemory.free);
    printf("Allocated FB memory %lld bytes \n\n", nvmlmemory.used);
}*/

void init_func() {
    if(open_flag == 0 && handle == NULL) {
        /*int fd;
        fd = open(LOG_FILENAME, O_WRONLY | O_CREAT, 0644);
        if (fd == -1) {
            perror("open log file failed");
            exit(1);
        }

        if (dup2(fd, 1) == -1) {
            perror("dup2 failed"); 
            exit(1);
        }*/

        //char *error;
    	handle = dlopen (LIB_STRING, RTLD_LAZY);
    	if (!handle) {
       	    fprintf (stderr, "%s\n", dlerror());
       	    exit(1);
    	}
	    open_flag = 1;
    	dlerror();
    	pthread_mutex_init(&mem_cnt_lock, NULL);
	    //set_quota();
	    //printf("Init:\n");
        //nvmlresult = nvmlInit();
	    //if (NVML_SUCCESS != nvmlresult)
	    //{
      	//     printf("Failed to initialize NVML: %s\n", nvmlErrorString(nvmlresult));

	    //}
	    //nvmlresult = nvmlDeviceGetHandleByIndex(0, &nvmldevice);
        //if (NVML_SUCCESS != nvmlresult)
        //{
        //     printf("Failed to get handle for device: %s\n",  nvmlErrorString(nvmlresult));
        //}
	    //nvml_memquery();
	    //pid_t procpid = getpid();
	    //printf("PID:%d\n", procpid);
	    //procpid = getppid();
	    //printf("PPID:%d\n", procpid);
	    //unsigned int infoCount;
        //nvmlProcessInfo_t infos[999];
        //nvmlresult = nvmlDeviceGetComputeRunningProcesses(nvmldevice, &infoCount, infos);
	    //int i;
	    //printf("infocount:%d\n", infoCount);
	    //for (i = 0; i < infoCount; i++)
        //{
            // printf("PID: %d ,usedGPUMem:%lld bytes   ", infos[i].pid, infos[i].usedGpuMemory);
	    //}
	    
        printf("Init!\n");

    }
    cnt++;
    printf("%lld\n",cnt);
}

int check_alloc_valid(size_t bytesize) {
    //printf("lock mem in check_alloc_valid\n");
    pthread_mutex_lock(&mem_cnt_lock);	
    //printf("&&&&&&&&&&&&total_mem %zu\n", total_mem);
    if(total_mem + bytesize  > total_quota) {
        fprintf (stderr, "alloc %zu failed, total_mem %zu, quota %zu\n", bytesize, total_mem,  total_quota);
	    //printf("unlock mem in check_alloc_valid:1\n");
	    pthread_mutex_unlock(&mem_cnt_lock);
	    return 0;
    }
    //printf("unlock mem in check\n");
    pthread_mutex_unlock(&mem_cnt_lock);
    return 1;
}


cudaError_t cudaMalloc( void** devPtr, size_t bytesize) {
	init_func();
	cudaError_t (*fakecudaMalloc)( void** , size_t );
	fakecudaMalloc = dlsym(handle, "cudaMalloc");
	if ((error = dlerror()) != NULL)  {    
		fprintf (stderr, "%s\n", error);                                                        
		exit(1); 
        }                                       
	
	printf("cudaMalloc:\n");
    //nvml_memquery();
    cudaError_t r= (*fakecudaMalloc)( devPtr , bytesize);
	//dlclose(handle);
    return r;
}

cudaError_t cudaFree( void* devPtr ) {
        
	init_func();
	cudaError_t (*fakecudaFree)( void* );
    fakecudaFree = dlsym(handle, "cudaFree");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	printf("cudaFree:\n");
	//nvml_memquery();
    cudaError_t r= (*fakecudaFree)( devPtr );
    dlclose(handle);	
    return r;
}

cudaError_t cudaMemGetInfo( size_t* free , size_t* total) {
        
    init_func();
    cudaError_t (*fakecudaMemGetInfo)( size_t* , size_t* );
    fakecudaMemGetInfo = dlsym(handle, "cudaMemGetInfo");
    printf("cudaMemGetInfo\n");
    
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaMemGetInfo)( free, total );
    return r;
}

cudaError_t cudaMallocPitch( void** devPtr, size_t* pitch, size_t width, size_t height) {

    init_func();
    cudaError_t (*fakecudaMallocPitch)( void** , size_t* , size_t , size_t);
    fakecudaMallocPitch = dlsym(handle, "cudaMallocPitch");
    printf("cudaMallocPitch\n");
    
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
        
	//dlclose(handle);
	
	cudaError_t r= (*fakecudaMallocPitch)( devPtr, pitch, width, height );
    return r;
}


cudaError_t cudaMallocManaged( void** devPtr, size_t bytesize, unsigned int flags) {
    init_func();
    cudaError_t (*fakecudaMallocManaged)( void** , size_t , unsigned int);
    fakecudaMallocManaged = dlsym(handle, "cudaMallocManaged");
    printf("cudaMallocManaged\n");
    
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
        
	//dlclose(handle);
	cudaError_t r= (*fakecudaMallocManaged)( devPtr, bytesize, flags);
    return r;
}


cudaError_t cudaMalloc3D(struct cudaPitchedPtr* pitchedDevPtr, struct cudaExtent extent ) {

    init_func();
    cudaError_t (*fakecudaMalloc3D)(struct cudaPitchedPtr*, struct cudaExtent);
    fakecudaMalloc3D = dlsym(handle, "cudaMalloc3D");
    printf("cudaMalloc3D\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaMalloc3D)( pitchedDevPtr, extent);
	//dlclose(handle);
	return r;
	
}

cudaError_t cudaMalloc3DArray(cudaArray_t* array, const struct cudaChannelFormatDesc* desc, struct cudaExtent extent, unsigned int  flags) {

    init_func();
    cudaError_t (*fakecudaMalloc3DArray)( cudaArray_t* , const struct cudaChannelFormatDesc* , struct cudaExtent, unsigned int);
    fakecudaMalloc3DArray = dlsym(handle, "cudaMalloc3DArray");
    printf("cudaMalloc3DArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaMalloc3DArray)( array, desc, extent, flags);
	//dlclose(handle);
	return r;
	
}

cudaError_t cudaMallocHost(void** ptr, size_t size) {

    init_func();
    cudaError_t (*fakecudaMallocHost)(void**, size_t);
    fakecudaMallocHost = dlsym(handle, "cudaMallocHost");
    printf("cudaMallocHost\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaMallocHost)( ptr, size);
	//dlclose(handle);
	return r;
	
}

cudaError_t cudaMallocArray(cudaArray_t* array, const struct cudaChannelFormatDesc* desc, size_t width, size_t height, unsigned int  flags) {

    init_func();
    cudaError_t (*fakecudaMallocArray)(cudaArray_t* , const struct cudaChannelFormatDesc* , size_t, size_t, unsigned int);
    fakecudaMallocArray = dlsym(handle, "cudaMallocArray");
    printf("cudaMallocArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaMallocArray)( array, desc,width,height,flags);
	//dlclose(handle);
	return r;
	
}

cudaError_t cudaMallocMipmappedArray(cudaMipmappedArray_t* mipmappedArray, const struct cudaChannelFormatDesc* desc, struct cudaExtent extent, unsigned int  numLevels, unsigned int flags) {

    init_func();
    cudaError_t (*fakecudaMallocMipmappedArray)(cudaMipmappedArray_t* , const struct cudaChannelFormatDesc* , struct cudaExtent, unsigned int, unsigned int);
    fakecudaMallocMipmappedArray = dlsym(handle, "cudaMallocMipmappedArray");
    printf("cudaMallocMipmappedArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaMallocMipmappedArray)(mipmappedArray, desc, extent,numLevels, flags);
	//dlclose(handle);
	return r;
	
}

cudaError_t cudaChooseDevice ( int* device, const struct cudaDeviceProp* prop ) {
        
    init_func();
    cudaError_t (*fakecudaChooseDevice)( int* , const struct cudaDeviceProp* );
    fakecudaChooseDevice = dlsym(handle, "cudaChooseDevice");
    printf("cudaChooseDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaChooseDevice)( device, prop );
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceGetAttribute ( int* value, enum cudaDeviceAttr attr, int  device ) {
        
    init_func();
    cudaError_t (*fakecudaDeviceGetAttribute)( int* , enum cudaDeviceAttr , int );
    fakecudaDeviceGetAttribute = dlsym(handle, "cudaDeviceGetAttribute");
    printf("cudaDeviceGetAttribute\n");
    //printf("cudaDeviceGetAttribute:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaDeviceGetAttribute)( value, attr, device);
	//nvml_memquery();	
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceGetByPCIBusId ( int* device, const char* pciBusId ) {
        
    init_func();
    cudaError_t (*fakecudaDeviceGetByPCIBusId)( int* , const char* );
    fakecudaDeviceGetByPCIBusId = dlsym(handle, "cudaDeviceGetByPCIBusId");
    printf("cudaDeviceGetByPCIBusId\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceGetByPCIBusId)( device, pciBusId);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceGetCacheConfig( enum cudaFuncCache * pCacheConfig ) {
        
    init_func();
    cudaError_t (*fakecudaDeviceGetCacheConfig)( enum cudaFuncCache * );
    fakecudaDeviceGetCacheConfig = dlsym(handle, "cudaDeviceGetCacheConfig");
    printf("cudaDeviceGetCacheConfig\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceGetCacheConfig)( pCacheConfig);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceGetLimit( size_t* pValue, enum cudaLimit limit ) {
        
    init_func();
    cudaError_t (*fakecudaDeviceGetLimit)( size_t* , enum cudaLimit);
    fakecudaDeviceGetLimit = dlsym(handle, "cudaDeviceGetLimit");
    printf("cudaDeviceGetLimit\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceGetLimit)( pValue, limit);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceGetP2PAttribute(int* value, enum cudaDeviceP2PAttr attr, int srcDevice, int dstDevice) {
        
    init_func();
    cudaError_t (*fakecudaDeviceGetP2PAttribute)(int* , enum cudaDeviceP2PAttr, int, int);
    fakecudaDeviceGetP2PAttribute = dlsym(handle, "cudaDeviceGetP2PAttribute");
    printf("cudaDeviceGetP2PAttribute\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceGetP2PAttribute)( value, attr, srcDevice, dstDevice);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceGetPCIBusId(char* pciBusId, int len, int device) {
        
    init_func();
    cudaError_t (*fakecudaDeviceGetPCIBusId)(char* , int, int);
    fakecudaDeviceGetPCIBusId = dlsym(handle, "cudaDeviceGetPCIBusId");
    printf("cudaDeviceGetPCIBusId\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceGetPCIBusId)( pciBusId, len, device);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceGetSharedMemConfig( enum cudaSharedMemConfig * pConfig) {
        
    init_func();
    cudaError_t (*fakecudaDeviceGetSharedMemConfig)( enum cudaSharedMemConfig * );
    fakecudaDeviceGetSharedMemConfig = dlsym(handle, "cudaDeviceGetSharedMemConfig");
    printf("cudaDeviceGetSharedMemConfig\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceGetSharedMemConfig)( pConfig);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceGetStreamPriorityRange( int* leastPriority, int* greatestPriority) {
        
    init_func();
    cudaError_t (*fakecudaDeviceGetStreamPriorityRange)(int* , int* );
    fakecudaDeviceGetStreamPriorityRange = dlsym(handle, "cudaDeviceGetStreamPriorityRange");
    printf("cudaDeviceGetStreamPriorityRange:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaDeviceGetStreamPriorityRange)(leastPriority, greatestPriority);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceReset () {
        
    init_func();
    cudaError_t (*fakecudaDeviceReset)(void );
    fakecudaDeviceReset = dlsym(handle, "cudaDeviceReset");
    printf("cudaDeviceReset\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceReset)();
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceSetCacheConfig( enum cudaFuncCache cacheConfig) {
        
    init_func();
    cudaError_t (*fakecudaDeviceSetCacheConfig)( enum cudaFuncCache);
    fakecudaDeviceSetCacheConfig = dlsym(handle, "cudaDeviceSetCacheConfig");
    printf("cudaDeviceSetCacheConfig\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceSetCacheConfig)( cacheConfig);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceSetLimit( enum cudaLimit limit, size_t value) {
        
    init_func();
    cudaError_t (*fakecudaDeviceSetLimit)( enum cudaLimit, size_t);
    fakecudaDeviceSetLimit = dlsym(handle, "cudaDeviceSetLimit");
    printf("cudaDeviceSetLimit\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceSetLimit)(limit, value);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceSetSharedMemConfig( enum cudaSharedMemConfig config) {
        
    init_func();
    cudaError_t (*fakecudaDeviceSetSharedMemConfig)( enum cudaSharedMemConfig );
    fakecudaDeviceSetSharedMemConfig = dlsym(handle, "cudaDeviceSetSharedMemConfig");
    printf("cudaDeviceSetSharedMemConfig\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceSetSharedMemConfig)(config);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceSynchronize() {
        
    init_func();
    cudaError_t (*fakecudaDeviceSynchronize)(void);
    fakecudaDeviceSynchronize = dlsym(handle, "cudaDeviceSynchronize");
    printf("cudaDeviceSynchronize\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceSynchronize)();
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetDevice( int* device) {
        
    init_func();
    cudaError_t (*fakecudaGetDevice)(int*);
    fakecudaGetDevice = dlsym(handle, "cudaGetDevice");
    printf("cudaGetDevice:\n");
	//nvml_memquery();
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaGetDevice)(device);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetDeviceCount( int* count ) {
        
    init_func();
    cudaError_t (*fakecudaGetDeviceCount)(int*);
    fakecudaGetDeviceCount = dlsym(handle, "cudaGetDeviceCount");
    printf("cudaGetDeviceCount:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaGetDeviceCount)(count);
	//nvml_memquery();
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetDeviceFlags( unsigned int* flags ) {
        
    init_func();
    cudaError_t (*fakecudaGetDeviceFlags)(unsigned int*);
    fakecudaGetDeviceFlags = dlsym(handle, "cudaGetDeviceFlags");
    printf("cudaGetDeviceFlags\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaGetDeviceFlags)(flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetDeviceProperties( struct cudaDeviceProp* prop, int device) {
        
    init_func();
    cudaError_t (*fakecudaGetDeviceProperties)( struct cudaDeviceProp* , int );
    fakecudaGetDeviceProperties = dlsym(handle, "cudaGetDeviceProperties");
    printf("cudaGetDeviceProperties:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaGetDeviceProperties)( prop,device);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaIpcCloseMemHandle( void* devPtr) {
        
    init_func();
    cudaError_t (*fakecudaIpcCloseMemHandle)(void*);
    fakecudaIpcCloseMemHandle = dlsym(handle, "cudaIpcCloseMemHandle");
    printf("cudaIpcCloseMemHandle\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaIpcCloseMemHandle)(devPtr);
    //dlclose(handle);
    return r;
}

cudaError_t cudaIpcGetEventHandle( cudaIpcEventHandle_t* handle, cudaEvent_t event) {
        
    init_func();
    cudaError_t (*fakecudaIpcGetEventHandle)( cudaIpcEventHandle_t* , cudaEvent_t);
    fakecudaIpcGetEventHandle = dlsym(handle, "cudaIpcGetEventHandle");
    printf("cudaIpcGetEventHandle\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaIpcGetEventHandle)( handle, event);
    //dlclose(handle);
    return r;
}

cudaError_t cudaIpcGetMemHandle( cudaIpcMemHandle_t* handle, void* devPtr) {
        
    init_func();
    cudaError_t (*fakecudaIpcGetMemHandle)( cudaIpcMemHandle_t* , void* );
    fakecudaIpcGetMemHandle = dlsym(handle, "cudaIpcGetMemHandle");
    printf("cudaIpcGetMemHandle\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaIpcGetMemHandle)( handle, devPtr);
    //dlclose(handle);
    return r;
}

cudaError_t cudaIpcOpenEventHandle( cudaEvent_t* event,  cudaIpcEventHandle_t hand) {
        
    init_func();
    cudaError_t (*fakecudaIpcOpenEventHandle)(cudaEvent_t* , cudaIpcEventHandle_t );
    fakecudaIpcOpenEventHandle = dlsym(handle, "cudaIpcOpenEventHandle");
    printf("cudaIpcOpenEventHandle\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaIpcOpenEventHandle)( event, hand);
    //dlclose(handle);
    return r;
}

cudaError_t cudaIpcOpenMemHandle( void** devPtr, cudaIpcMemHandle_t hand, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaIpcOpenMemHandle)(void** , cudaIpcMemHandle_t , unsigned int );
    fakecudaIpcOpenMemHandle = dlsym(handle, "cudaIpcOpenMemHandle");
    printf("cudaIpcOpenMemHandle\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaIpcOpenMemHandle)( devPtr, hand, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaSetDevice (int  device) {
        
    init_func();
    cudaError_t (*fakecudaSetDevice)(int );
    fakecudaSetDevice = dlsym(handle, "cudaSetDevice");
    printf("cudaSetDevice:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaSetDevice)( device);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaSetDeviceFlags( unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaSetDeviceFlags)(unsigned int );
    fakecudaSetDeviceFlags = dlsym(handle, "cudaSetDeviceFlags");
    printf("cudaSetDeviceFlags\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaSetDeviceFlags)( flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaSetValidDevices( int* device_arr, int  len) {
        
    init_func();
    cudaError_t (*fakecudaSetValidDevices)(int* , int );
    fakecudaSetValidDevices = dlsym(handle, "cudaSetValidDevices");
    printf("cudaSetValidDevices\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaSetValidDevices)(device_arr, len);
    //dlclose(handle);
    return r;
}

const char* cudaGetErrorName ( cudaError_t err ) {
        
    init_func();
    const char* (*fakecudaGetErrorName)( cudaError_t );
    fakecudaGetErrorName = dlsym(handle, "cudaGetErrorName");
    printf("cudaGetErrorName\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    const char* r= (*fakecudaGetErrorName)( err );
    //dlclose(handle);
    return r;
}

const char* cudaGetErrorString ( cudaError_t err) {
        
    init_func();
    const char* (*fakecudaGetErrorString)( cudaError_t );
    fakecudaGetErrorString = dlsym(handle, "cudaGetErrorString");
    printf("cudaGetErrorString\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    const char* r= (*fakecudaGetErrorString)( err );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetLastError () {
        
    init_func();
    cudaError_t (*fakecudaGetLastError)(void );
    fakecudaGetLastError = dlsym(handle, "cudaGetLastError");
    printf("cudaGetLastError:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaGetLastError)();
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaPeekAtLastError () {
        
    init_func();
    cudaError_t (*fakecudaPeekAtLastError)(void );
    fakecudaPeekAtLastError = dlsym(handle, "cudaPeekAtLastError");
    printf("cudaPeekAtLastError\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaPeekAtLastError)();
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamAddCallback( cudaStream_t stream, cudaStreamCallback_t callback, void* userData, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaStreamAddCallback)(cudaStream_t , cudaStreamCallback_t , void* , unsigned int );
    fakecudaStreamAddCallback = dlsym(handle, "cudaStreamAddCallback");
    printf("cudaStreamAddCallback\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamAddCallback)(stream,  callback, userData,flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamAttachMemAsync(cudaStream_t stream, void* devPtr, size_t length, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaStreamAttachMemAsync)(cudaStream_t , void* , size_t , unsigned int );
    fakecudaStreamAttachMemAsync = dlsym(handle, "cudaStreamAttachMemAsync");
    printf("cudaStreamAttachMemAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamAttachMemAsync)( stream, devPtr, length, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamBeginCapture( cudaStream_t stream ) {
        
    init_func();
    cudaError_t (*fakecudaStreamBeginCapture)(cudaStream_t );
    fakecudaStreamBeginCapture = dlsym(handle, "cudaStreamBeginCapture");
    printf("cudaStreamBeginCapture\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamBeginCapture)( stream );
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamCreate ( cudaStream_t* pStream) {
        
    init_func();
    cudaError_t (*fakecudaStreamCreate)(cudaStream_t* );
    fakecudaStreamCreate = dlsym(handle, "cudaStreamCreate");
    printf("cudaStreamCreate\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamCreate)( pStream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamCreateWithFlags( cudaStream_t* pStream, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaStreamCreateWithFlags)(cudaStream_t* , unsigned int );
    fakecudaStreamCreateWithFlags = dlsym(handle, "cudaStreamCreateWithFlags");
    printf("cudaStreamCreateWithFlags:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaStreamCreateWithFlags)(pStream,  flags);
    //nvml_memquery();
	//printf("\n\n");
	//dlclose(handle);
    return r;
}

cudaError_t cudaStreamCreateWithPriority( cudaStream_t* pStream, unsigned int  flags, int  priority) {
        
    init_func();
    cudaError_t (*fakecudaStreamCreateWithPriority)(cudaStream_t* , unsigned int  , int  );
    fakecudaStreamCreateWithPriority = dlsym(handle, "cudaStreamCreateWithPriority");
    printf("cudaStreamCreateWithPriority:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaStreamCreateWithPriority)(pStream,  flags,  priority);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamDestroy ( cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaStreamDestroy)(cudaStream_t );
    fakecudaStreamDestroy = dlsym(handle, "cudaStreamDestroy");
    printf("cudaStreamDestroy\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaStreamDestroy)(stream);
	//nvml_memquery();
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamEndCapture ( cudaStream_t stream, cudaGraph_t* pGraph) {
        
    init_func();
    cudaError_t (*fakecudaStreamEndCapture)( cudaStream_t , cudaGraph_t* );
    fakecudaStreamEndCapture = dlsym(handle, "cudaStreamEndCapture");
    printf("cudaStreamEndCapture\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamEndCapture)( stream, pGraph);
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamGetCaptureInfo ( cudaStream_t stream, enum cudaStreamCaptureStatus ** pCaptureStatus, unsigned long long* pId) {
        
    init_func();
    cudaError_t (*fakecudaStreamGetCaptureInfo)( cudaStream_t , enum cudaStreamCaptureStatus ** , unsigned long long* );
    fakecudaStreamGetCaptureInfo = dlsym(handle, "cudaStreamGetCaptureInfo");
    printf("cudaStreamGetCaptureInfo\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamGetCaptureInfo)( stream, pCaptureStatus, pId);
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamGetFlags( cudaStream_t hStream, unsigned int* flags) {
        
    init_func();
    cudaError_t (*fakecudaStreamGetFlags)(cudaStream_t , unsigned int* );
    fakecudaStreamGetFlags = dlsym(handle, "cudaStreamGetFlags");
    printf("cudaStreamGetFlags\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamGetFlags)(hStream, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamGetPriority ( cudaStream_t hStream, int* priority) {
        
    init_func();
    cudaError_t (*fakecudaStreamGetPriority)(cudaStream_t , int* );
    fakecudaStreamGetPriority = dlsym(handle, "cudaStreamGetPriority");
    printf("cudaStreamGetPriority\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamGetPriority)(hStream, priority);
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamIsCapturing(cudaStream_t stream, enum cudaStreamCaptureStatus *pCaptureStatus) {
        
    init_func();
    cudaError_t (*fakecudaStreamIsCapturing)(cudaStream_t, enum cudaStreamCaptureStatus * );
    fakecudaStreamIsCapturing = dlsym(handle, "cudaStreamIsCapturing");
    printf("cudaStreamIsCapturing\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamIsCapturing)( stream, pCaptureStatus);
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamQuery ( cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaStreamQuery)(cudaStream_t);
    fakecudaStreamQuery = dlsym(handle, "cudaStreamQuery");
    printf("cudaStreamQuery\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamQuery)(stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamSynchronize ( cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaStreamSynchronize)(cudaStream_t);
    fakecudaStreamSynchronize = dlsym(handle, "cudaStreamSynchronize");
    printf("cudaStreamSynchronize:\n");
	//nvml_memquery();
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaStreamSynchronize)(stream);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaStreamWaitEvent ( cudaStream_t stream, cudaEvent_t event, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaStreamWaitEvent)(cudaStream_t, cudaEvent_t, unsigned int);
    fakecudaStreamWaitEvent = dlsym(handle, "cudaStreamWaitEvent");
    printf("cudaStreamWaitEvent\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    //nvml_memquery();
	cudaError_t r= (*fakecudaStreamWaitEvent)(stream,event,flags);
	//nvml_memquery();
    //dlclose(handle);
    return r;
}

/*cudaError_t cudaThreadExchangeStreamCaptureMode ( enum cudaStreamCaptureMode **mode) {
        
    init_func();
    cudaError_t (*fakecudaThreadExchangeStreamCaptureMode)( enum cudaStreamCaptureMode **);
    fakecudaThreadExchangeStreamCaptureMode = dlsym(handle, "cudaThreadExchangeStreamCaptureMode");
    printf("cudaThreadExchangeStreamCaptureMode\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaThreadExchangeStreamCaptureMode)( mode);
    //dlclose(handle);
    return r;
}*/

cudaError_t cudaEventCreate ( cudaEvent_t* event) {
        
    init_func();
    cudaError_t (*fakecudaEventCreate)(cudaEvent_t*);
    fakecudaEventCreate = dlsym(handle, "cudaEventCreate");
    printf("cudaEventCreate:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaEventCreate)(event);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaEventCreateWithFlags ( cudaEvent_t* event, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaEventCreateWithFlags)(cudaEvent_t*, unsigned int);
    fakecudaEventCreateWithFlags = dlsym(handle, "cudaEventCreateWithFlags");
    printf("cudaEventCreateWithFlags:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaEventCreateWithFlags)(event, flags);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaEventDestroy ( cudaEvent_t event) {
        
    init_func();
    cudaError_t (*fakecudaEventDestroy)(cudaEvent_t);
    fakecudaEventDestroy = dlsym(handle, "cudaEventDestroy");
    printf("cudaEventDestroy\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaEventDestroy)(event);
	//nvml_memquery();
    //dlclose(handle);
    return r;
}

cudaError_t cudaEventElapsedTime ( float* ms, cudaEvent_t start, cudaEvent_t end) {
        
    init_func();
    cudaError_t (*fakecudaEventElapsedTime)(float* , cudaEvent_t , cudaEvent_t);
    fakecudaEventElapsedTime = dlsym(handle, "cudaEventElapsedTime");
    printf("cudaEventElapsedTime\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEventElapsedTime)( ms, start, end);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEventQuery ( cudaEvent_t event) {
        
    init_func();
    cudaError_t (*fakecudaEventQuery)(cudaEvent_t);
    fakecudaEventQuery = dlsym(handle, "cudaEventQuery");
    printf("cudaEventQuery\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEventQuery)( event);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEventRecord ( cudaEvent_t event, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaEventRecord)(cudaEvent_t, cudaStream_t);
    fakecudaEventRecord = dlsym(handle, "cudaEventRecord");
    printf("cudaEventRecord:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaEventRecord)( event, stream);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaEventSynchronize ( cudaEvent_t event) {
        
    init_func();
    cudaError_t (*fakecudaEventSynchronize)(cudaEvent_t);
    fakecudaEventSynchronize = dlsym(handle, "cudaEventSynchronize");
    printf("cudaEventSynchronize\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEventSynchronize)( event);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDestroyExternalMemory ( cudaExternalMemory_t extMem) {
        
    init_func();
    cudaError_t (*fakecudaDestroyExternalMemory)(cudaExternalMemory_t);
    fakecudaDestroyExternalMemory = dlsym(handle, "cudaDestroyExternalMemory");
    printf("cudaDestroyExternalMemory\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaDestroyExternalMemory)( extMem);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDestroyExternalSemaphore ( cudaExternalSemaphore_t extSem) {
        
    init_func();
    cudaError_t (*fakecudaDestroyExternalSemaphore)(cudaExternalSemaphore_t);
    fakecudaDestroyExternalSemaphore = dlsym(handle, "cudaDestroyExternalSemaphore");
    printf("cudaDestroyExternalSemaphore\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaDestroyExternalSemaphore)( extSem);
    //dlclose(handle);
    return r;
}

cudaError_t cudaExternalMemoryGetMappedBuffer ( void** devPtr, cudaExternalMemory_t extMem, const struct cudaExternalMemoryBufferDesc* bufferDesc) {
        
    init_func();
    cudaError_t (*fakecudaExternalMemoryGetMappedBuffer)( void** , cudaExternalMemory_t , const struct cudaExternalMemoryBufferDesc* );
    fakecudaExternalMemoryGetMappedBuffer = dlsym(handle, "cudaExternalMemoryGetMappedBuffer");
    printf("cudaExternalMemoryGetMappedBuffer\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaExternalMemoryGetMappedBuffer)( devPtr, extMem, bufferDesc);
    //dlclose(handle);
    return r;
}

cudaError_t cudaExternalMemoryGetMappedMipmappedArray ( cudaMipmappedArray_t* mipmap, cudaExternalMemory_t extMem, const struct cudaExternalMemoryMipmappedArrayDesc* mipmapDesc) {
        
    init_func();
    cudaError_t (*fakecudaExternalMemoryGetMappedMipmappedArray)( cudaMipmappedArray_t* , cudaExternalMemory_t , const struct cudaExternalMemoryMipmappedArrayDesc* );
    fakecudaExternalMemoryGetMappedMipmappedArray = dlsym(handle, "cudaExternalMemoryGetMappedMipmappedArray");
    printf("cudaExternalMemoryGetMappedMipmappedArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaExternalMemoryGetMappedMipmappedArray)( mipmap, extMem, mipmapDesc);
    //dlclose(handle);
    return r;
}

cudaError_t cudaImportExternalMemory ( cudaExternalMemory_t* extMem_out, const struct cudaExternalMemoryHandleDesc* memHandleDesc) {
        
    init_func();
    cudaError_t (*fakecudaImportExternalMemory)(cudaExternalMemory_t* , const struct cudaExternalMemoryHandleDesc* );
    fakecudaImportExternalMemory = dlsym(handle, "cudaImportExternalMemory");
    printf("cudaImportExternalMemory\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaImportExternalMemory)( extMem_out, memHandleDesc);
    //dlclose(handle);
    return r;
}

cudaError_t cudaImportExternalSemaphore ( cudaExternalSemaphore_t* extSem_out, const struct cudaExternalSemaphoreHandleDesc* semHandleDesc) {
        
    init_func();
    cudaError_t (*fakecudaImportExternalSemaphore)(cudaExternalSemaphore_t* , const struct cudaExternalSemaphoreHandleDesc* );
    fakecudaImportExternalSemaphore = dlsym(handle, "cudaImportExternalSemaphore");
    printf("cudaImportExternalSemaphore\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaImportExternalSemaphore)( extSem_out, semHandleDesc);
    //dlclose(handle);
    return r;
}

cudaError_t cudaSignalExternalSemaphoresAsync ( const cudaExternalSemaphore_t* extSemArray, const struct cudaExternalSemaphoreSignalParams* paramsArray, unsigned int numExtSems, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaSignalExternalSemaphoresAsync)(const cudaExternalSemaphore_t* , const struct cudaExternalSemaphoreSignalParams* , unsigned int , cudaStream_t );
    fakecudaSignalExternalSemaphoresAsync = dlsym(handle, "cudaSignalExternalSemaphoresAsync");
    printf("cudaSignalExternalSemaphoresAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaSignalExternalSemaphoresAsync)( extSemArray, paramsArray, numExtSems, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaWaitExternalSemaphoresAsync ( const cudaExternalSemaphore_t* extSemArray, const struct cudaExternalSemaphoreWaitParams* paramsArray, unsigned int numExtSems, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaWaitExternalSemaphoresAsync)(const cudaExternalSemaphore_t* , const struct cudaExternalSemaphoreWaitParams* , unsigned int , cudaStream_t);
    fakecudaWaitExternalSemaphoresAsync = dlsym(handle, "cudaWaitExternalSemaphoresAsync");
    printf("cudaWaitExternalSemaphoresAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaWaitExternalSemaphoresAsync)( extSemArray, paramsArray, numExtSems, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaFuncGetAttributes ( struct cudaFuncAttributes* attr, const void* func) {
        
    init_func();
    cudaError_t (*fakecudaFuncGetAttributes)( struct cudaFuncAttributes* , const void* );
    fakecudaFuncGetAttributes = dlsym(handle, "cudaFuncGetAttributes");
    printf("cudaFuncGetAttributes\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaFuncGetAttributes)(attr, func);
    //dlclose(handle);
    return r;
}

cudaError_t cudaFuncSetAttribute ( const void* func, enum cudaFuncAttribute attr, int  value) {
        
    init_func();
    cudaError_t (*fakecudaFuncSetAttribute)( const void* , enum cudaFuncAttribute, int );
    fakecudaFuncSetAttribute = dlsym(handle, "cudaFuncSetAttribute");
    printf("cudaFuncSetAttribute\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaFuncSetAttribute)( func, attr, value);
    //dlclose(handle);
    return r;
}

cudaError_t cudaFuncSetCacheConfig ( const void* func, enum cudaFuncCache cacheConfig) {
        
    init_func();
    cudaError_t (*fakecudaFuncSetCacheConfig)( const void* , enum cudaFuncCache );
    fakecudaFuncSetCacheConfig = dlsym(handle, "cudaFuncSetCacheConfig");
    printf("cudaFuncSetCacheConfig\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaFuncSetCacheConfig)( func, cacheConfig);
    //dlclose(handle);
    return r;
}

cudaError_t cudaFuncSetSharedMemConfig ( const void* func, enum cudaSharedMemConfig config) {
        
    init_func();
    cudaError_t (*fakecudaFuncSetSharedMemConfig)( const void* , enum cudaSharedMemConfig );
    fakecudaFuncSetSharedMemConfig = dlsym(handle, "cudaFuncSetSharedMemConfig");
    printf("cudaFuncSetSharedMemConfig\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);        
    }    
    cudaError_t r= (*fakecudaFuncSetSharedMemConfig)( func, config);
    //dlclose(handle);
    return r;
}

void* cudaGetParameterBuffer ( size_t alignment, size_t size) {
        
    init_func();
    void* (*fakecudaGetParameterBuffer)(size_t , size_t );
    fakecudaGetParameterBuffer = dlsym(handle, "cudaGetParameterBuffer");
    printf("cudaGetParameterBuffer\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    void* r= (*fakecudaGetParameterBuffer)(alignment, size);
    //dlclose(handle);
    return r;
}

void* cudaGetParameterBufferV2 ( void* func, dim3 gridDimension, dim3 blockDimension, unsigned int  sharedMemSize) {
        
    init_func();
    void* (*fakecudaGetParameterBufferV2)(void* , dim3 , dim3 , unsigned int );
    fakecudaGetParameterBufferV2 = dlsym(handle, "cudaGetParameterBufferV2");
    printf("cudaGetParameterBufferV2\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    void* r= (*fakecudaGetParameterBufferV2)(func, gridDimension, blockDimension, sharedMemSize);
    //dlclose(handle);
    return r;
}

cudaError_t cudaLaunchCooperativeKernel( const void* func, dim3 gridDim, dim3 blockDim, void** args, size_t sharedMem, cudaStream_t stream) {
    init_func();
    cudaError_t (*fakecudaLaunchCooperativeKernel)(const void* , dim3 , dim3 , void** , size_t , cudaStream_t );
    fakecudaLaunchCooperativeKernel = dlsym(handle, "cudaLaunchCooperativeKernel");
    printf("cudaLaunchCooperativeKernel\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaLaunchCooperativeKernel)( func,  gridDim,  blockDim,  args, sharedMem, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaLaunchCooperativeKernelMultiDevice ( struct cudaLaunchParams* launchParamsList, unsigned int  numDevices, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaLaunchCooperativeKernelMultiDevice)( struct cudaLaunchParams* , unsigned int , unsigned int );
    fakecudaLaunchCooperativeKernelMultiDevice = dlsym(handle, "cudaLaunchCooperativeKernelMultiDevice");
    printf("cudaLaunchCooperativeKernelMultiDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaLaunchCooperativeKernelMultiDevice)( launchParamsList, numDevices, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaLaunchHostFunc ( cudaStream_t stream, cudaHostFn_t fn, void* userData) {
        
    init_func();
    cudaError_t (*fakecudaLaunchHostFunc)(cudaStream_t , cudaHostFn_t , void* );
    fakecudaLaunchHostFunc = dlsym(handle, "cudaLaunchHostFunc");
    printf("cudaLaunchHostFunc\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaLaunchHostFunc)( stream, fn, userData);
    //dlclose(handle);
    return r;
}

static const unsigned int crc32_table[] =
{
  0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9,
  0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
  0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
  0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
  0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9,
  0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
  0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011,
  0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
  0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
  0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
  0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81,
  0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
  0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49,
  0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95,
  0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
  0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
  0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae,
  0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
  0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16,
  0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
  0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
  0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02,
  0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066,
  0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
  0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e,
  0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692,
  0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
  0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
  0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e,
  0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
  0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686,
  0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
  0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
  0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb,
  0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f,
  0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
  0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47,
  0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b,
  0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
  0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
  0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7,
  0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
  0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f,
  0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
  0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
  0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b,
  0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f,
  0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
  0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640,
  0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
  0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
  0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
  0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30,
  0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
  0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088,
  0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
  0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
  0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c,
  0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18,
  0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
  0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0,
  0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c,
  0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
  0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

unsigned int
xcrc32 (const unsigned char *buf, int len)
{
  unsigned int crc = 0xFFFF;
  while (len--)
    {
      crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ *buf) & 255];
      buf++;
    }
  return crc;
}

cudaError_t cudaLaunchKernel ( const void* func, dim3 gridDim, dim3 blockDim, void** args, size_t sharedMem, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaLaunchKernel)(const void* , dim3 , dim3 , void** , size_t, cudaStream_t );
    fakecudaLaunchKernel = dlsym(handle, "cudaLaunchKernel");
    printf("cudaLaunchKernel\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    const int nbytes = 40;
    unsigned int crc = xcrc32(func, nbytes);
    printf("%lld\n", crc);

	//nvml_memquery();
    cudaError_t r= (*fakecudaLaunchKernel)( func, gridDim, blockDim, args, sharedMem, stream);
	//nvml_memquery();
    //dlclose(handle);
    return r;
}

cudaError_t cudaSetDoubleForDevice ( double* d) {
        
    init_func();
    cudaError_t (*fakecudaSetDoubleForDevice)(double* );
    fakecudaSetDoubleForDevice = dlsym(handle, "cudaSetDoubleForDevice");
    printf("cudaSetDoubleForDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaSetDoubleForDevice)(d);
    //dlclose(handle);
    return r;
}

cudaError_t cudaSetDoubleForHost ( double* d) {
        
    init_func();
    cudaError_t (*fakecudaSetDoubleForHost)(double* );
    fakecudaSetDoubleForHost = dlsym(handle, "cudaSetDoubleForHost");
    printf("cudaSetDoubleForHost\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaSetDoubleForHost)(d);
    //dlclose(handle);
    return r;
}

cudaError_t cudaOccupancyMaxActiveBlocksPerMultiprocessor ( int* numBlocks, const void* func, int blockSize, size_t dynamicSMemSize) {
        
    init_func();
    cudaError_t (*fakecudaOccupancyMaxActiveBlocksPerMultiprocessor)(int* , const void* , int , size_t );
    fakecudaOccupancyMaxActiveBlocksPerMultiprocessor = dlsym(handle, "cudaOccupancyMaxActiveBlocksPerMultiprocessor");
    printf("cudaOccupancyMaxActiveBlocksPerMultiprocessor\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaOccupancyMaxActiveBlocksPerMultiprocessor)( numBlocks, func, blockSize, dynamicSMemSize);
    //dlclose(handle);
    return r;
}

cudaError_t cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags ( int* numBlocks, const void* func, int  blockSize, size_t dynamicSMemSize, unsigned int flags) {
        
    init_func();
    cudaError_t (*fakecudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)(int* , const void* , int , size_t , unsigned int);
    fakecudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags = dlsym(handle, "cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags");
    printf("cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)( numBlocks, func, blockSize, dynamicSMemSize, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaArrayGetInfo ( struct cudaChannelFormatDesc* desc, struct cudaExtent* extent, unsigned int* flags, cudaArray_t array) {
        
    init_func();
    cudaError_t (*fakecudaArrayGetInfo)( struct cudaChannelFormatDesc* , struct cudaExtent* , unsigned int* , cudaArray_t );
    fakecudaArrayGetInfo = dlsym(handle, "cudaArrayGetInfo");
    printf("cudaArrayGetInfo\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaArrayGetInfo)( desc, extent, flags, array);
    //dlclose(handle);
    return r;
}

cudaError_t cudaFreeArray ( cudaArray_t array) {
        
    init_func();
    cudaError_t (*fakecudaFreeArray)(cudaArray_t );
    fakecudaFreeArray = dlsym(handle, "cudaFreeArray");
    printf("cudaFreeArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaFreeArray)( array);
    //dlclose(handle);
    return r;
}

cudaError_t cudaFreeHost ( void* ptr) {
        
    init_func();
    cudaError_t (*fakecudaFreeHost)(void* );
    fakecudaFreeHost = dlsym(handle, "cudaFreeHost");
    printf("cudaFreeHost\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    //nvml_memquery();
	cudaError_t r= (*fakecudaFreeHost)( ptr);
	//nvml_memquery();
    //dlclose(handle);
    return r;
}

cudaError_t cudaFreeMipmappedArray ( cudaMipmappedArray_t mipmappedArray) {
        
    init_func();
    cudaError_t (*fakecudaFreeMipmappedArray)(cudaMipmappedArray_t );
    fakecudaFreeMipmappedArray = dlsym(handle, "cudaFreeMipmappedArray");
    printf("cudaFreeMipmappedArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaFreeMipmappedArray)( mipmappedArray);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetMipmappedArrayLevel (cudaArray_t* levelArray, cudaMipmappedArray_const_t mipmappedArray, unsigned int level) {
        
    init_func();
    cudaError_t (*fakecudaGetMipmappedArrayLevel)(cudaArray_t* , cudaMipmappedArray_const_t, unsigned int );
    fakecudaGetMipmappedArrayLevel = dlsym(handle, "cudaGetMipmappedArrayLevel");
    printf("cudaGetMipmappedArrayLevel\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGetMipmappedArrayLevel)( levelArray, mipmappedArray, level);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetSymbolAddress ( void** devPtr, const void* symbol) {
        
    init_func();
    cudaError_t (*fakecudaGetSymbolAddress)( void** , const void* );
    fakecudaGetSymbolAddress = dlsym(handle, "cudaGetSymbolAddress");
    printf("cudaGetSymbolAddress\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGetSymbolAddress)(devPtr, symbol);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetSymbolSize ( size_t* size, const void* symbol) {
        
    init_func();
    cudaError_t (*fakecudaGetSymbolSize)( size_t* , const void* );
    fakecudaGetSymbolSize = dlsym(handle, "cudaGetSymbolSize");
    printf("cudaGetSymbolSize\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGetSymbolSize)(size, symbol);
    //dlclose(handle);
    return r;
}

cudaError_t cudaHostAlloc ( void** pHost, size_t size, unsigned int flags) {
        
    init_func();
    cudaError_t (*fakecudaHostAlloc)(void** , size_t , unsigned int );
    fakecudaHostAlloc = dlsym(handle, "cudaHostAlloc");
    printf("cudaHostAlloc:\n");
	//nvml_memquery();
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaHostAlloc)(pHost, size, flags);
    //nvml_memquery();
    //printf("\n\n");
	//dlclose(handle);
    return r;
}

cudaError_t cudaHostGetDevicePointer ( void** pDevice, void* pHost, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaHostGetDevicePointer)(void** , void* , unsigned int );
    fakecudaHostGetDevicePointer = dlsym(handle, "cudaHostGetDevicePointer");
    printf("cudaHostGetDevicePointer:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaHostGetDevicePointer)(pDevice, pHost, flags);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaHostGetFlags ( unsigned int* pFlags, void* pHost) {
        
    init_func();
    cudaError_t (*fakecudaHostGetFlags)(unsigned int* , void* );
    fakecudaHostGetFlags = dlsym(handle, "cudaHostGetFlags");
    printf("cudaHostGetFlags\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaHostGetFlags)(pFlags, pHost);
    //dlclose(handle);
    return r;
}

cudaError_t cudaHostRegister ( void* ptr, size_t size, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaHostRegister)( void* , size_t, unsigned int);
    fakecudaHostRegister = dlsym(handle, "cudaHostRegister");
    printf("cudaHostRegister\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaHostRegister)(ptr,size, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaHostUnregister ( void* ptr) {
        
    init_func();
    cudaError_t (*fakecudaHostUnregister)( void* );
    fakecudaHostUnregister = dlsym(handle, "cudaHostUnregister");
    printf("cudaHostUnregister\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaHostUnregister)(ptr);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemAdvise ( const void* devPtr, size_t count, enum cudaMemoryAdvise advice, int  device) {
        
    init_func();
    cudaError_t (*fakecudaMemAdvise)( const void*, size_t, enum cudaMemoryAdvise, int );
    fakecudaMemAdvise = dlsym(handle, "cudaMemAdvise");
    printf("cudaMemAdvise\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemAdvise)( devPtr, count, advice, device);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemPrefetchAsync ( const void* devPtr, size_t count, int  dstDevice, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemPrefetchAsync)( const void* , size_t , int  , cudaStream_t );
    fakecudaMemPrefetchAsync = dlsym(handle, "cudaMemPrefetchAsync");
    printf("cudaMemPrefetchAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemPrefetchAsync)(devPtr, count, dstDevice, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemRangeGetAttribute ( void* data, size_t dataSize, enum cudaMemRangeAttribute attribute, const void* devPtr, size_t count) {
        
    init_func();
    cudaError_t (*fakecudaMemRangeGetAttribute)(void* , size_t , enum cudaMemRangeAttribute, const void* , size_t );
    fakecudaMemRangeGetAttribute = dlsym(handle, "cudaMemRangeGetAttribute");
    printf("cudaMemRangeGetAttribute\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemRangeGetAttribute)( data, dataSize, attribute, devPtr, count);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemRangeGetAttributes ( void** data, size_t* dataSizes, enum cudaMemRangeAttribute *attributes, size_t numAttributes, const void* devPtr, size_t count) {
        
    init_func();
    cudaError_t (*fakecudaMemRangeGetAttributes)(void** , size_t* , enum cudaMemRangeAttribute *, size_t, const void*, size_t );
    fakecudaMemRangeGetAttributes = dlsym(handle, "cudaMemRangeGetAttributes");
    printf("cudaMemRangeGetAttributes\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemRangeGetAttributes)( data, dataSizes, attributes, numAttributes , devPtr, count);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy ( void* dst, const void* src, size_t count, enum cudaMemcpyKind kind) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy)(void* , const void* , size_t, enum cudaMemcpyKind);
    fakecudaMemcpy = dlsym(handle, "cudaMemcpy");
    printf("cudaMemcpy\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy)( dst, src, count, kind);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy2D ( void* dst, size_t dpitch, const void* src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy2D)(void* , size_t, const void* , size_t, size_t, size_t, enum cudaMemcpyKind);
    fakecudaMemcpy2D = dlsym(handle, "cudaMemcpy2D");
    printf("cudaMemcpy2D\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy2D)( dst, dpitch, src, spitch,width,height, kind);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy2DArrayToArray ( cudaArray_t dst, size_t wOffsetDst, size_t hOffsetDst, cudaArray_const_t src, size_t wOffsetSrc, size_t hOffsetSrc, size_t width, size_t height, enum cudaMemcpyKind kind) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy2DArrayToArray)(cudaArray_t , size_t, size_t, cudaArray_const_t, size_t, size_t, size_t, size_t, enum cudaMemcpyKind);
    fakecudaMemcpy2DArrayToArray = dlsym(handle, "cudaMemcpy2DArrayToArray");
    printf("cudaMemcpy2DArrayToArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy2DArrayToArray)( dst, wOffsetDst, hOffsetDst, src, wOffsetSrc,hOffsetSrc,width,height, kind);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy2DAsync ( void* dst, size_t dpitch, const void* src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy2DAsync)(void* , size_t, const void* , size_t, size_t, size_t, enum cudaMemcpyKind, cudaStream_t);
    fakecudaMemcpy2DAsync = dlsym(handle, "cudaMemcpy2DAsync");
    printf("cudaMemcpy2DAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy2DAsync)( dst, dpitch, src, spitch,width,height, kind, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy2DFromArray ( void* dst, size_t dpitch, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t width, size_t height, enum cudaMemcpyKind kind) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy2DFromArray)(void* , size_t , cudaArray_const_t, size_t, size_t, size_t, size_t, enum cudaMemcpyKind);
    fakecudaMemcpy2DFromArray = dlsym(handle, "cudaMemcpy2DFromArray");
    printf("cudaMemcpy2DFromArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy2DFromArray)( dst, dpitch, src, wOffset, hOffset,width,height, kind);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy2DFromArrayAsync ( void* dst, size_t dpitch, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t width, size_t height, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy2DFromArrayAsync)(void* , size_t , cudaArray_const_t, size_t, size_t, size_t, size_t, enum cudaMemcpyKind, cudaStream_t);
    fakecudaMemcpy2DFromArrayAsync = dlsym(handle, "cudaMemcpy2DFromArrayAsync");
    printf("cudaMemcpy2DFromArrayAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy2DFromArrayAsync)( dst, dpitch, src, wOffset, hOffset,width,height, kind, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy2DToArray ( cudaArray_t dst, size_t wOffset, size_t hOffset, const void* src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy2DToArray)(cudaArray_t , size_t , size_t, const void*, size_t, size_t, size_t, enum cudaMemcpyKind);
    fakecudaMemcpy2DToArray = dlsym(handle, "cudaMemcpy2DToArray");
    printf("cudaMemcpy2DToArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy2DToArray)( dst,wOffset, hOffset, src,spitch, width,height, kind);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy2DToArrayAsync ( cudaArray_t dst, size_t wOffset, size_t hOffset, const void* src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy2DToArrayAsync)(cudaArray_t , size_t , size_t, const void*, size_t, size_t, size_t, enum cudaMemcpyKind, cudaStream_t);
    fakecudaMemcpy2DToArrayAsync = dlsym(handle, "cudaMemcpy2DToArrayAsync");
    printf("cudaMemcpy2DToArrayAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy2DToArrayAsync)( dst,wOffset, hOffset, src,spitch, width,height, kind, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy3D ( const struct cudaMemcpy3DParms* p) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy3D)(const struct cudaMemcpy3DParms*);
    fakecudaMemcpy3D = dlsym(handle, "cudaMemcpy3D");
    printf("cudaMemcpy3D\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy3D)(p);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy3DAsync ( const struct cudaMemcpy3DParms* p, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy3DAsync)(const struct cudaMemcpy3DParms*, cudaStream_t);
    fakecudaMemcpy3DAsync = dlsym(handle, "cudaMemcpy3DAsync");
    printf("cudaMemcpy3DAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy3DAsync)(p, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy3DPeer ( const struct cudaMemcpy3DPeerParms* p) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy3DPeer)(const struct cudaMemcpy3DPeerParms*);
    fakecudaMemcpy3DPeer = dlsym(handle, "cudaMemcpy3DPeer");
    printf("cudaMemcpy3DPeer\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy3DPeer)(p);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpy3DPeerAsync ( const struct cudaMemcpy3DPeerParms* p, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemcpy3DPeerAsync)(const struct cudaMemcpy3DPeerParms*, cudaStream_t);
    fakecudaMemcpy3DPeerAsync = dlsym(handle, "cudaMemcpy3DPeerAsync");
    printf("cudaMemcpy3DPeerAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpy3DPeerAsync)(p, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpyAsync ( void* dst, const void* src, size_t count, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemcpyAsync)(void* , const void* , size_t , enum cudaMemcpyKind , cudaStream_t );
    fakecudaMemcpyAsync = dlsym(handle, "cudaMemcpyAsync");
    printf("cudaMemcpyAsync:\n");
    //nvml_memquery();
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpyAsync)( dst, src, count, kind, stream);
    //nvml_memquery();
	//printf("\n\n");
	//dlclose(handle);
    return r;
}

cudaError_t cudaMemcpyFromSymbol( void* dst, const void* symbol, size_t count, size_t offset , enum cudaMemcpyKind kind) {
        
    init_func();
    cudaError_t (*fakecudaMemcpyFromSymbol)(void* , const void* , size_t , size_t , enum cudaMemcpyKind );
    fakecudaMemcpyFromSymbol = dlsym(handle, "cudaMemcpyFromSymbol");
    printf("cudaMemcpyFromSymbol\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpyFromSymbol)( dst, symbol, count,offset,kind);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpyFromSymbolAsync ( void* dst, const void* symbol, size_t count, size_t offset, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemcpyFromSymbolAsync)(void* , const void* , size_t, size_t, enum cudaMemcpyKind, cudaStream_t);
    fakecudaMemcpyFromSymbolAsync = dlsym(handle, "cudaMemcpyFromSymbolAsync");
    printf("cudaMemcpyFromSymbolAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpyFromSymbolAsync)( dst, symbol, count, offset,  kind, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpyPeer ( void* dst, int dstDevice, const void* src, int srcDevice, size_t count) {
        
    init_func();
    cudaError_t (*fakecudaMemcpyPeer)(void*, int , const void* , int, size_t);
    fakecudaMemcpyPeer = dlsym(handle, "cudaMemcpyPeer");
    printf("cudaMemcpyPeer\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpyPeer)( dst, dstDevice, src,srcDevice, count);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpyPeerAsync( void* dst, int dstDevice, const void* src, int srcDevice, size_t count, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemcpyPeerAsync)(void* , int , const void*, int, size_t, cudaStream_t);
    fakecudaMemcpyPeerAsync = dlsym(handle, "cudaMemcpyPeerAsync");
    printf("cudaMemcpyPeerAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpyPeerAsync)(dst, dstDevice, src,srcDevice, count, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpyToSymbol ( const void* symbol, const void* src, size_t count, size_t offset, enum cudaMemcpyKind kind) {
        
    init_func();
    cudaError_t (*fakecudaMemcpyToSymbol)(const void* , const void* , size_t, size_t, enum cudaMemcpyKind);
    fakecudaMemcpyToSymbol = dlsym(handle, "cudaMemcpyToSymbol");
    printf("cudaMemcpyToSymbol\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpyToSymbol)( symbol, src, count,offset, kind);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemcpyToSymbolAsync(const void* symbol, const void* src, size_t count, size_t offset, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemcpyToSymbolAsync)(const void* , const void* , size_t, size_t, enum cudaMemcpyKind, cudaStream_t);
    fakecudaMemcpyToSymbolAsync = dlsym(handle, "cudaMemcpyToSymbolAsync");
    printf("cudaMemcpyToSymbolAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemcpyToSymbolAsync)( symbol, src, count,offset, kind, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemset (void* devPtr, int value, size_t count) {
    
    init_func();
    cudaError_t (*fakecudaMemset)(void* , int , size_t);
    fakecudaMemset = dlsym(handle, "cudaMemset");
    printf("cudaMemset\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemset)(devPtr, value,count);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemset2D ( void* devPtr, size_t pitch, int  value, size_t width, size_t height) {
        
    init_func();
    cudaError_t (*fakecudaMemset2D)(void* ,size_t, int , size_t, size_t);
    fakecudaMemset2D = dlsym(handle, "cudaMemset2D");
    printf("cudaMemset2D\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemset2D)(devPtr,pitch, value,width, height);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemset2DAsync( void* devPtr, size_t pitch, int  value, size_t width, size_t height, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemset2DAsync)(void* ,size_t, int , size_t, size_t, cudaStream_t);
    fakecudaMemset2DAsync = dlsym(handle, "cudaMemset2DAsync");
    printf("cudaMemset2DAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemset2DAsync)(devPtr,pitch, value,width, height, stream);
    //dlclose(handle);
    return r;
}
cudaError_t cudaMemset3D ( struct cudaPitchedPtr pitchedDevPtr, int value, struct cudaExtent extent) {
        
    init_func();
    cudaError_t (*fakecudaMemset3D)( struct cudaPitchedPtr, int, struct cudaExtent);
    fakecudaMemset3D = dlsym(handle, "cudaMemset3D");
    printf("cudaMemset3D\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemset3D)( pitchedDevPtr,value, extent);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemset3DAsync ( struct cudaPitchedPtr pitchedDevPtr, int  value, struct cudaExtent extent, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemset3DAsync)( struct cudaPitchedPtr, int, struct cudaExtent, cudaStream_t);
    fakecudaMemset3DAsync = dlsym(handle, "cudaMemset3DAsync");
    printf("cudaMemset3DAsync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaMemset3DAsync)( pitchedDevPtr,value, extent, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaMemsetAsync ( void* devPtr, int  value, size_t count, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaMemsetAsync)(void* , int , size_t, cudaStream_t);
    fakecudaMemsetAsync = dlsym(handle, "cudaMemsetAsync");
    printf("cudaMemsetAsync:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
	//nvml_memquery();
    cudaError_t r= (*fakecudaMemsetAsync)(devPtr, value,count, stream);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaPointerGetAttributes ( struct cudaPointerAttributes* attributes, const void* ptr) {
        
    init_func();
    cudaError_t (*fakecudaPointerGetAttributes)( struct cudaPointerAttributes* , const void* );
    fakecudaPointerGetAttributes = dlsym(handle, "cudaPointerGetAttributes");
    printf("cudaPointerGetAttributes\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaPointerGetAttributes)( attributes,ptr);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceCanAccessPeer ( int* canAccessPeer, int device, int peerDevice) {
        
    init_func();
    cudaError_t (*fakecudaDeviceCanAccessPeer)(int*, int, int);
    fakecudaDeviceCanAccessPeer = dlsym(handle, "cudaDeviceCanAccessPeer");
    printf("cudaDeviceCanAccessPeer\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceCanAccessPeer)(canAccessPeer,device, peerDevice);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceDisablePeerAccess ( int peerDevice) {
        
    init_func();
    cudaError_t (*fakecudaDeviceDisablePeerAccess)(int);
    fakecudaDeviceDisablePeerAccess = dlsym(handle, "cudaDeviceDisablePeerAccess");
    printf("cudaDeviceDisablePeerAccess\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceDisablePeerAccess)(peerDevice);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceEnablePeerAccess ( int peerDevice, unsigned int flags) {
        
    init_func();
    cudaError_t (*fakecudaDeviceEnablePeerAccess)(int, unsigned int);
    fakecudaDeviceEnablePeerAccess = dlsym(handle, "cudaDeviceEnablePeerAccess");
    printf("cudaDeviceEnablePeerAccess\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaDeviceEnablePeerAccess)(peerDevice,flags);
    //dlclose(handle);
    return r;
}


cudaError_t cudaGraphicsMapResources ( int count, cudaGraphicsResource_t* resources, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsMapResources)( int , cudaGraphicsResource_t* , cudaStream_t );
    fakecudaGraphicsMapResources = dlsym(handle, "cudaGraphicsMapResources");
    printf("cudaGraphicsMapResources\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsMapResources)( count, resources, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsResourceGetMappedMipmappedArray ( cudaMipmappedArray_t* mipmappedArray, cudaGraphicsResource_t resource) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsResourceGetMappedMipmappedArray)( cudaMipmappedArray_t* , cudaGraphicsResource_t );
    fakecudaGraphicsResourceGetMappedMipmappedArray = dlsym(handle, "cudaGraphicsResourceGetMappedMipmappedArray");
    printf("cudaGraphicsResourceGetMappedMipmappedArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsResourceGetMappedMipmappedArray)( mipmappedArray, resource);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsResourceGetMappedPointer ( void** devPtr, size_t* size, cudaGraphicsResource_t resource) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsResourceGetMappedPointer)( void** , size_t*,cudaGraphicsResource_t );
    fakecudaGraphicsResourceGetMappedPointer = dlsym(handle, "cudaGraphicsResourceGetMappedPointer");
    printf("cudaGraphicsResourceGetMappedPointer\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsResourceGetMappedPointer)( devPtr, size, resource);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsResourceSetMapFlags ( cudaGraphicsResource_t resource, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsResourceSetMapFlags)( cudaGraphicsResource_t, unsigned int );
    fakecudaGraphicsResourceSetMapFlags = dlsym(handle, "cudaGraphicsResourceSetMapFlags");
    printf("cudaGraphicsResourceSetMapFlags\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsResourceSetMapFlags)( resource, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsSubResourceGetMappedArray ( cudaArray_t* array, cudaGraphicsResource_t resource, unsigned int arrayIndex, unsigned int mipLevel) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsSubResourceGetMappedArray)( cudaArray_t* ,cudaGraphicsResource_t, unsigned int , unsigned int);
    fakecudaGraphicsSubResourceGetMappedArray = dlsym(handle, "cudaGraphicsSubResourceGetMappedArray");
    printf("cudaGraphicsSubResourceGetMappedArray\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsSubResourceGetMappedArray)(array, resource, arrayIndex, mipLevel);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsUnmapResources ( int count, cudaGraphicsResource_t* resources, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsUnmapResources)(int ,cudaGraphicsResource_t*, cudaStream_t);
    fakecudaGraphicsUnmapResources = dlsym(handle, "cudaGraphicsUnmapResources");
    printf("cudaGraphicsUnmapResources\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsUnmapResources)(count, resources, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsUnregisterResource ( cudaGraphicsResource_t resource) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsUnregisterResource)(cudaGraphicsResource_t);
    fakecudaGraphicsUnregisterResource = dlsym(handle, "cudaGraphicsUnregisterResource");
    printf("cudaGraphicsUnregisterResource\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsUnregisterResource)(resource);
    //dlclose(handle);
    return r;
}

struct cudaChannelFormatDesc cudaCreateChannelDesc ( int  x, int  y, int  z, int  w, enum cudaChannelFormatKind f ) {
    init_func();
    struct cudaChannelFormatDesc (*fakecudaCreateChannelDesc)( int, int , int , int , enum cudaChannelFormatKind);
    fakecudaCreateChannelDesc = dlsym(handle, "cudaCreateChannelDesc");
    printf("cudaCreateChannelDesc:\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
	//nvml_memquery();
    struct cudaChannelFormatDesc r= (*fakecudaCreateChannelDesc)( x,y,z,w,f);
	//nvml_memquery();
	//printf("\n\n");
    //dlclose(handle);
    return r;
}

cudaError_t cudaCreateTextureObject ( cudaTextureObject_t* pTexObject, const struct cudaResourceDesc* pResDesc, const struct cudaTextureDesc* pTexDesc, const struct cudaResourceViewDesc* pResViewDesc) {
        
    init_func();
    cudaError_t (*fakecudaCreateTextureObject)(cudaTextureObject_t* , const struct cudaResourceDesc* , const struct cudaTextureDesc* , const struct cudaResourceViewDesc* );
    fakecudaCreateTextureObject = dlsym(handle, "cudaCreateTextureObject");
    printf("cudaCreateTextureObject\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaCreateTextureObject)( pTexObject, pResDesc, pTexDesc, pResViewDesc);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDestroyTextureObject ( cudaTextureObject_t texObject) {
        
    init_func();
    cudaError_t (*fakecudaDestroyTextureObject)(cudaTextureObject_t );
    fakecudaDestroyTextureObject = dlsym(handle, "cudaDestroyTextureObject");
    printf("cudaDestroyTextureObject\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaDestroyTextureObject)( texObject);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetChannelDesc ( struct cudaChannelFormatDesc* desc, cudaArray_const_t array) {
        
    init_func();
    cudaError_t (*fakecudaGetChannelDesc)(struct cudaChannelFormatDesc* ,  cudaArray_const_t);
    fakecudaGetChannelDesc = dlsym(handle, "cudaGetChannelDesc");
    printf("cudaGetChannelDesc\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGetChannelDesc)( desc, array);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetTextureObjectResourceDesc ( struct cudaResourceDesc* pResDesc, cudaTextureObject_t texObject) {
        
    init_func();
    cudaError_t (*fakecudaGetTextureObjectResourceDesc)( struct cudaResourceDesc* ,  cudaTextureObject_t);
    fakecudaGetTextureObjectResourceDesc = dlsym(handle, "cudaGetTextureObjectResourceDesc");
    printf("cudaGetTextureObjectResourceDesc\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGetTextureObjectResourceDesc)( pResDesc, texObject);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetTextureObjectResourceViewDesc ( struct cudaResourceViewDesc* pResViewDesc, cudaTextureObject_t texObject) {
        
    init_func();
    cudaError_t (*fakecudaGetTextureObjectResourceViewDesc)( struct cudaResourceViewDesc* ,  cudaTextureObject_t);
    fakecudaGetTextureObjectResourceViewDesc = dlsym(handle, "cudaGetTextureObjectResourceViewDesc");
    printf("cudaGetTextureObjectResourceViewDesc\n");
    if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error); 
            exit(1);
    }
    cudaError_t r= (*fakecudaGetTextureObjectResourceViewDesc)( pResViewDesc, texObject);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetTextureObjectTextureDesc ( struct cudaTextureDesc* pTexDesc, cudaTextureObject_t texObject) {
    
    init_func();
    cudaError_t (*fakecudaGetTextureObjectTextureDesc)( struct cudaTextureDesc* ,  cudaTextureObject_t);
    fakecudaGetTextureObjectTextureDesc = dlsym(handle, "cudaGetTextureObjectTextureDesc");
    printf("cudaGetTextureObjectTextureDesc\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGetTextureObjectTextureDesc)( pTexDesc, texObject);
    //dlclose(handle);
    return r;
}

cudaError_t cudaCreateSurfaceObject ( cudaSurfaceObject_t* pSurfObject, const struct cudaResourceDesc* pResDesc) {
        
    init_func();
    cudaError_t (*fakecudaCreateSurfaceObject)( cudaSurfaceObject_t* ,  const struct cudaResourceDesc*);
    fakecudaCreateSurfaceObject = dlsym(handle, "cudaCreateSurfaceObject");
    printf("cudaCreateSurfaceObject\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaCreateSurfaceObject)( pSurfObject, pResDesc );
    //dlclose(handle);
    return r;
}

cudaError_t cudaDestroySurfaceObject ( cudaSurfaceObject_t surfObject) {
        
    init_func();
    cudaError_t (*fakecudaDestroySurfaceObject)( cudaSurfaceObject_t);
    fakecudaDestroySurfaceObject = dlsym(handle, "cudaDestroySurfaceObject");
    printf("cudaDestroySurfaceObject\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaDestroySurfaceObject)( surfObject );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGetSurfaceObjectResourceDesc ( struct cudaResourceDesc* pResDesc, cudaSurfaceObject_t surfObject) {
        
    init_func();
    cudaError_t (*fakecudaGetSurfaceObjectResourceDesc)( struct cudaResourceDesc* , cudaSurfaceObject_t);
    fakecudaGetSurfaceObjectResourceDesc = dlsym(handle, "cudaGetSurfaceObjectResourceDesc");
    printf("cudaGetSurfaceObjectResourceDesc\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGetSurfaceObjectResourceDesc)( pResDesc,  surfObject );
    //dlclose(handle);
    return r;
}

cudaError_t cudaDriverGetVersion ( int* driverVersion) {
        
    init_func();
    cudaError_t (*fakecudaDriverGetVersion)( int* );
    fakecudaDriverGetVersion = dlsym(handle, "cudaDriverGetVersion");
    printf("cudaDriverGetVersion\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaDriverGetVersion)( driverVersion );
    //dlclose(handle);
    return r;
}

cudaError_t cudaRuntimeGetVersion ( int* runtimeVersion) {
        
    init_func();
    cudaError_t (*fakecudaRuntimeGetVersion)( int* );
    fakecudaRuntimeGetVersion = dlsym(handle, "cudaRuntimeGetVersion");
    printf("cudaRuntimeGetVersion\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaRuntimeGetVersion)( runtimeVersion );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphAddChildGraphNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies, cudaGraph_t childGraph) {
        
    init_func();
    cudaError_t (*fakecudaGraphAddChildGraphNode)( cudaGraphNode_t* , cudaGraph_t, cudaGraphNode_t* , size_t, cudaGraph_t);
    fakecudaGraphAddChildGraphNode = dlsym(handle, "cudaGraphAddChildGraphNode");
    printf("cudaGraphAddChildGraphNode\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphAddChildGraphNode)( pGraphNode,  graph, pDependencies, numDependencies, childGraph);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphAddDependencies ( cudaGraph_t graph, cudaGraphNode_t* from, cudaGraphNode_t* to, size_t numDependencies) {
        
    init_func();
    cudaError_t (*fakecudaGraphAddDependencies)( cudaGraph_t , cudaGraphNode_t*,  cudaGraphNode_t* , size_t);
    fakecudaGraphAddDependencies = dlsym(handle, "cudaGraphAddDependencies");
    printf("cudaGraphAddDependencies\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphAddDependencies)( graph,  from, to, numDependencies);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphAddEmptyNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies) {
        
    init_func();
    cudaError_t (*fakecudaGraphAddEmptyNode)( cudaGraphNode_t*, cudaGraph_t, cudaGraphNode_t* , size_t);
    fakecudaGraphAddEmptyNode = dlsym(handle, "cudaGraphAddEmptyNode");
    printf("cudaGraphAddEmptyNode\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphAddEmptyNode)( pGraphNode,  graph, pDependencies, numDependencies);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphAddHostNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies, const struct cudaHostNodeParams* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphAddHostNode)( cudaGraphNode_t*, cudaGraph_t, cudaGraphNode_t* , size_t, const struct cudaHostNodeParams* );
    fakecudaGraphAddHostNode = dlsym(handle, "cudaGraphAddHostNode");
    printf("cudaGraphAddHostNode\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphAddHostNode)( pGraphNode,  graph, pDependencies, numDependencies, pNodeParams);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphAddKernelNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies, const struct cudaKernelNodeParams* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphAddKernelNode)( cudaGraphNode_t*, cudaGraph_t, cudaGraphNode_t* , size_t, const struct cudaKernelNodeParams* );
    fakecudaGraphAddKernelNode = dlsym(handle, "cudaGraphAddKernelNode");
    printf("cudaGraphAddKernelNode\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphAddKernelNode)( pGraphNode,  graph, pDependencies, numDependencies, pNodeParams);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphAddMemcpyNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies, const struct cudaMemcpy3DParms* pCopyParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphAddMemcpyNode)( cudaGraphNode_t*, cudaGraph_t, cudaGraphNode_t* , size_t, const struct cudaMemcpy3DParms* );
    fakecudaGraphAddMemcpyNode = dlsym(handle, "cudaGraphAddMemcpyNode");
    printf("cudaGraphAddMemcpyNode\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphAddMemcpyNode)( pGraphNode,  graph, pDependencies, numDependencies, pCopyParams);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphAddMemsetNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies, const struct cudaMemsetParams* pMemsetParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphAddMemsetNode)( cudaGraphNode_t*, cudaGraph_t,  cudaGraphNode_t* , size_t, const struct cudaMemsetParams* );
    fakecudaGraphAddMemsetNode = dlsym(handle, "cudaGraphAddMemsetNode");
    printf("cudaGraphAddMemsetNode\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphAddMemsetNode)( pGraphNode,  graph, pDependencies, numDependencies, pMemsetParams);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphChildGraphNodeGetGraph ( cudaGraphNode_t node, cudaGraph_t* pGraph) {
        
    init_func();
    cudaError_t (*fakecudaGraphChildGraphNodeGetGraph)( cudaGraphNode_t, cudaGraph_t* );
    fakecudaGraphChildGraphNodeGetGraph = dlsym(handle, "cudaGraphChildGraphNodeGetGraph");
    printf("cudaGraphChildGraphNodeGetGraph\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphChildGraphNodeGetGraph)( node,  pGraph );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphClone ( cudaGraph_t* pGraphClone, cudaGraph_t originalGraph) {
        
    init_func();
    cudaError_t (*fakecudaGraphClone)( cudaGraph_t* , cudaGraph_t );
    fakecudaGraphClone = dlsym(handle, "cudaGraphClone");
    printf("cudaGraphClone\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphClone)( pGraphClone,  originalGraph );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphCreate ( cudaGraph_t* pGraph, unsigned int flags) {
        
    init_func();
    cudaError_t (*fakecudaGraphCreate)( cudaGraph_t* , unsigned int );
    fakecudaGraphCreate = dlsym(handle, "cudaGraphCreate");
    printf("cudaGraphCreate\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphCreate)( pGraph,  flags );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphDestroy ( cudaGraph_t graph) {
        
    init_func();
    cudaError_t (*fakecudaGraphDestroy)( cudaGraph_t );
    fakecudaGraphDestroy = dlsym(handle, "cudaGraphDestroy");
    printf("cudaGraphDestroy\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphDestroy)( graph );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphDestroyNode ( cudaGraphNode_t node) {
        
    init_func();
    cudaError_t (*fakecudaGraphDestroyNode)( cudaGraphNode_t );
    fakecudaGraphDestroyNode = dlsym(handle, "cudaGraphDestroyNode");
    printf("cudaGraphDestroyNode\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphDestroyNode)( node );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphExecDestroy ( cudaGraphExec_t graphExec) {
        
    init_func();
    cudaError_t (*fakecudaGraphExecDestroy)( cudaGraphExec_t );
    fakecudaGraphExecDestroy = dlsym(handle, "cudaGraphExecDestroy");
    printf("cudaGraphExecDestroy\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphExecDestroy)( graphExec );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphExecKernelNodeSetParams ( cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const struct cudaKernelNodeParams* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphExecKernelNodeSetParams)( cudaGraphExec_t ,cudaGraphNode_t, const struct cudaKernelNodeParams* );
    fakecudaGraphExecKernelNodeSetParams = dlsym(handle, "cudaGraphExecKernelNodeSetParams");
    printf("cudaGraphExecKernelNodeSetParams\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphExecKernelNodeSetParams)( hGraphExec, node, pNodeParams );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphGetEdges ( cudaGraph_t graph, cudaGraphNode_t* from, cudaGraphNode_t* to, size_t* numEdges) {
        
    init_func();
    cudaError_t (*fakecudaGraphGetEdges)( cudaGraph_t ,cudaGraphNode_t*, cudaGraphNode_t* , size_t* );
    fakecudaGraphGetEdges = dlsym(handle, "cudaGraphGetEdges");
    printf("cudaGraphGetEdges\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphGetEdges)( graph, from, to, numEdges );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphGetNodes ( cudaGraph_t graph, cudaGraphNode_t* nodes, size_t* numNodes) {
        
    init_func();
    cudaError_t (*fakecudaGraphGetNodes)( cudaGraph_t ,cudaGraphNode_t* , size_t* );
    fakecudaGraphGetNodes = dlsym(handle, "cudaGraphGetNodes");
    printf("cudaGraphGetNodes\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphGetNodes)( graph,nodes, numNodes );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphGetRootNodes ( cudaGraph_t graph, cudaGraphNode_t* pRootNodes, size_t* pNumRootNodes) {
        
    init_func();
    cudaError_t (*fakecudaGraphGetRootNodes)( cudaGraph_t ,cudaGraphNode_t* , size_t* );
    fakecudaGraphGetRootNodes = dlsym(handle, "cudaGraphGetRootNodes");
    printf("cudaGraphGetRootNodes\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphGetRootNodes)( graph,pRootNodes, pNumRootNodes );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphHostNodeGetParams( cudaGraphNode_t node, struct cudaHostNodeParams* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphHostNodeGetParams)( cudaGraphNode_t , struct cudaHostNodeParams* );
    fakecudaGraphHostNodeGetParams = dlsym(handle, "cudaGraphHostNodeGetParams");
    printf("cudaGraphHostNodeGetParams\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphHostNodeGetParams)( node , pNodeParams );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphHostNodeSetParams ( cudaGraphNode_t node, const struct cudaHostNodeParams* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphHostNodeSetParams)( cudaGraphNode_t ,const struct cudaHostNodeParams* );
    fakecudaGraphHostNodeSetParams = dlsym(handle, "cudaGraphHostNodeSetParams");
    printf("cudaGraphHostNodeSetParams\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphHostNodeSetParams)( node , pNodeParams );
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphInstantiate ( cudaGraphExec_t* pGraphExec, cudaGraph_t graph, cudaGraphNode_t* pErrorNode, char* pLogBuffer, size_t bufferSize) {
        
    init_func();
    cudaError_t (*fakecudaGraphInstantiate)( cudaGraphExec_t* ,const cudaGraph_t ,cudaGraphNode_t* ,char* ,size_t );
    fakecudaGraphInstantiate = dlsym(handle, "cudaGraphInstantiate");
    printf("cudaGraphInstantiate\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphInstantiate)( pGraphExec , graph ,  pErrorNode, pLogBuffer, bufferSize);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphKernelNodeGetParams ( cudaGraphNode_t node, struct cudaKernelNodeParams* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphKernelNodeGetParams)( cudaGraphNode_t , struct cudaKernelNodeParams* );
    fakecudaGraphKernelNodeGetParams = dlsym(handle, "cudaGraphKernelNodeGetParams");
    printf("cudaGraphKernelNodeGetParams\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphKernelNodeGetParams)( node, pNodeParams);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphKernelNodeSetParams ( cudaGraphNode_t node, const struct cudaKernelNodeParams* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphKernelNodeSetParams)( cudaGraphNode_t ,const struct cudaKernelNodeParams* );
    fakecudaGraphKernelNodeSetParams = dlsym(handle, "cudaGraphKernelNodeSetParams");
    printf("cudaGraphKernelNodeSetParams\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphKernelNodeSetParams)( node, pNodeParams);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphLaunch ( cudaGraphExec_t graphExec, cudaStream_t stream) {
        
    init_func();
    cudaError_t (*fakecudaGraphLaunch)( cudaGraphExec_t ,cudaStream_t );
    fakecudaGraphLaunch = dlsym(handle, "cudaGraphLaunch");
    printf("cudaGraphLaunch\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphLaunch)( graphExec, stream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphMemcpyNodeGetParams ( cudaGraphNode_t node, struct cudaMemcpy3DParms* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphMemcpyNodeGetParams)( cudaGraphNode_t , struct cudaMemcpy3DParms* );
    fakecudaGraphMemcpyNodeGetParams = dlsym(handle, "cudaGraphMemcpyNodeGetParams");
    printf("cudaGraphMemcpyNodeGetParams\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphMemcpyNodeGetParams)( node, pNodeParams);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphMemcpyNodeSetParams ( cudaGraphNode_t node, const struct cudaMemcpy3DParms* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphMemcpyNodeSetParams)( cudaGraphNode_t ,const struct cudaMemcpy3DParms* );
    fakecudaGraphMemcpyNodeSetParams = dlsym(handle, "cudaGraphMemcpyNodeSetParams");
    printf("cudaGraphMemcpyNodeSetParams\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphMemcpyNodeSetParams)( node, pNodeParams);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphMemsetNodeGetParams ( cudaGraphNode_t node, struct cudaMemsetParams* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphMemsetNodeGetParams)( cudaGraphNode_t , struct cudaMemsetParams* );
    fakecudaGraphMemsetNodeGetParams = dlsym(handle, "cudaGraphMemsetNodeGetParams");
    printf("cudaGraphMemsetNodeGetParams\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphMemsetNodeGetParams)( node, pNodeParams);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphMemsetNodeSetParams ( cudaGraphNode_t node, const struct cudaMemsetParams* pNodeParams) {
        
    init_func();
    cudaError_t (*fakecudaGraphMemsetNodeSetParams)( cudaGraphNode_t , const struct cudaMemsetParams* );
    fakecudaGraphMemsetNodeSetParams = dlsym(handle, "cudaGraphMemsetNodeSetParams");
    printf("cudaGraphMemsetNodeSetParams\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphMemsetNodeSetParams)( node, pNodeParams);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphNodeFindInClone ( cudaGraphNode_t* pNode, cudaGraphNode_t originalNode, cudaGraph_t clonedGraph) {
        
    init_func();
    cudaError_t (*fakecudaGraphNodeFindInClone)( cudaGraphNode_t* ,cudaGraphNode_t , cudaGraph_t );
    fakecudaGraphNodeFindInClone = dlsym(handle, "cudaGraphNodeFindInClone");
    printf("cudaGraphNodeFindInClone\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphNodeFindInClone)( pNode, originalNode, clonedGraph);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphNodeGetDependencies ( cudaGraphNode_t node, cudaGraphNode_t* pDependencies, size_t* pNumDependencies) {
        
    init_func();
    cudaError_t (*fakecudaGraphNodeGetDependencies)( cudaGraphNode_t ,cudaGraphNode_t* , size_t* );
    fakecudaGraphNodeGetDependencies = dlsym(handle, "cudaGraphNodeGetDependencies");
    printf("cudaGraphNodeGetDependencies\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphNodeGetDependencies)( node, pDependencies, pNumDependencies);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphNodeGetDependentNodes ( cudaGraphNode_t node, cudaGraphNode_t* pDependentNodes, size_t* pNumDependentNodes) {
        
    init_func();
    cudaError_t (*fakecudaGraphNodeGetDependentNodes)( cudaGraphNode_t ,cudaGraphNode_t* , size_t* );
    fakecudaGraphNodeGetDependentNodes = dlsym(handle, "cudaGraphNodeGetDependentNodes");
    printf("cudaGraphNodeGetDependentNodes\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphNodeGetDependentNodes)( node, pDependentNodes, pNumDependentNodes);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphNodeGetType ( cudaGraphNode_t node, enum cudaGraphNodeType * pType) {
        
    init_func();
    cudaError_t (*fakecudaGraphNodeGetType)( cudaGraphNode_t , enum cudaGraphNodeType *  );
    fakecudaGraphNodeGetType = dlsym(handle, "cudaGraphNodeGetType");
    printf("cudaGraphNodeGetType\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphNodeGetType)( node, pType);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphRemoveDependencies ( cudaGraph_t graph, cudaGraphNode_t* from,  cudaGraphNode_t* to, size_t numDependencies) {
        
    init_func();
    cudaError_t (*fakecudaGraphRemoveDependencies)( cudaGraph_t, cudaGraphNode_t* , cudaGraphNode_t* ,size_t );
    fakecudaGraphRemoveDependencies = dlsym(handle, "cudaGraphRemoveDependencies");
    printf("cudaGraphRemoveDependencies\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphRemoveDependencies)( graph, from, to, numDependencies);
    //dlclose(handle);
    return r;
}

cudaError_t cudaProfilerInitialize ( const char* configFile, const char* outputFile, cudaOutputMode_t outputMode) {
        
    init_func();
    cudaError_t (*fakecudaProfilerInitialize)( const char* , const char* , cudaOutputMode_t);
    fakecudaProfilerInitialize = dlsym(handle, "cudaProfilerInitialize");
    printf("cudaProfilerInitialize\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaProfilerInitialize)( configFile,  outputFile, outputMode);
    //dlclose(handle);
    return r;
}

cudaError_t cudaProfilerStart ( void) {
    
    init_func();
    cudaError_t (*fakecudaProfilerStart)( void);
    fakecudaProfilerStart = dlsym(handle, "cudaProfilerStart");
    printf("cudaProfilerStart\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaProfilerStart)( );
    //dlclose(handle);
    return r;
}

cudaError_t cudaProfilerStop ( void) {
        
    init_func();
    cudaError_t (*fakecudaProfilerStop)( void);
    fakecudaProfilerStop = dlsym(handle, "cudaProfilerStop");
    printf("cudaProfilerStop\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaProfilerStop)( );
    //dlclose(handle);
    return r;
}

/*
cudaError_t cudaGLGetDevices( unsigned int* pCudaDeviceCount, int* pCudaDevices, unsigned int  cudaDeviceCount, cudaGLDeviceList deviceList) {
        
    init_func();
    cudaError_t (*fakecudaGLGetDevices)( unsigned int* , int* , unsigned int , cudaGLDeviceList );
    fakecudaGLGetDevices = dlsym(handle, "cudaGLGetDevices");
    printf("cudaGLGetDevices\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGLGetDevices)(pCudaDeviceCount,  pCudaDevices,  cudaDeviceCount, deviceList);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsGLRegisterBuffer( cudaGraphicsResource** resource, GLuint buffer, unsigned int flags) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsGLRegisterBuffer)(cudaGraphicsResource** , GLuint, unsigned int );
    fakecudaGraphicsGLRegisterBuffer = dlsym(handle, "cudaGraphicsGLRegisterBuffer");
    printf("cudaGraphicsGLRegisterBuffer\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsGLRegisterBuffer)(resource,  buffer, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsGLRegisterImage(cudaGraphicsResource** resource, GLuint image, GLenum target, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsGLRegisterImage)(cudaGraphicsResource** , GLuint , GLenum , unsigned int);
    fakecudaGraphicsGLRegisterImage = dlsym(handle, "cudaGraphicsGLRegisterImage");
    printf("cudaGraphicsGLRegisterImage\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsGLRegisterImage)(resource, image, target,flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaWGLGetDevice(int* device, HGPUNV hGpu) {
        
    init_func();
    cudaError_t (*fakecudaWGLGetDevice)(int* , HGPUNV);
    fakecudaWGLGetDevice = dlsym(handle, "cudaWGLGetDevice");
    printf("cudaWGLGetDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaWGLGetDevice)( device, hGpu);
    //dlclose(handle);
    return r;
}

cudaError_t cudaD3D9GetDevice(int* device, const char* pszAdapterName) {
        
    init_func();
    cudaError_t (*fakecudaD3D9GetDevice)(int* , const char* );
    fakecudaD3D9GetDevice = dlsym(handle, "cudaD3D9GetDevice");
    printf("cudaD3D9GetDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaD3D9GetDevice)( device, pszAdapterName);
    //dlclose(handle);
    return r;
}

cudaError_t cudaD3D9GetDevices(unsigned int* pCudaDeviceCount, int* pCudaDevices, unsigned int  cudaDeviceCount, IDirect3DDevice9* pD3D9Device, cudaD3D9DeviceList deviceList) {
        
    init_func();
    cudaError_t (*fakecudaD3D9GetDevices)(unsigned int* , int* , unsigned int , IDirect3DDevice9* , cudaD3D9DeviceList );
    fakecudaD3D9GetDevices = dlsym(handle, "cudaD3D9GetDevices");
    printf("cudaD3D9GetDevices\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaD3D9GetDevices)( pCudaDeviceCount,  pCudaDevices,  cudaDeviceCount, pD3D9Device, deviceList);
    //dlclose(handle);
    return r;
}

cudaError_t cudaD3D9GetDirect3DDevice(IDirect3DDevice9** ppD3D9Device) {
        
    init_func();
    cudaError_t (*fakecudaD3D9GetDirect3DDevice)(IDirect3DDevice9**  );
    fakecudaD3D9GetDirect3DDevice = dlsym(handle, "cudaD3D9GetDirect3DDevice");
    printf("cudaD3D9GetDirect3DDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaD3D9GetDirect3DDevice)( ppD3D9Device);
    //dlclose(handle);
    return r;
}

cudaError_t cudaD3D9SetDirect3DDevice(IDirect3DDevice9* pD3D9Device, int  device = -1) {
        
    init_func();
    cudaError_t (*fakecudaD3D9SetDirect3DDevice)(IDirect3DDevice9* , int  );
    fakecudaD3D9SetDirect3DDevice = dlsym(handle, "cudaD3D9SetDirect3DDevice");
    printf("cudaD3D9SetDirect3DDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaD3D9SetDirect3DDevice)( pD3D9Device, device = -1);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsD3D9RegisterResource(cudaGraphicsResource** resource, IDirect3DResource9* pD3DResource, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsD3D9RegisterResource)(cudaGraphicsResource** , IDirect3DResource9* , unsigned int);
    fakecudaGraphicsD3D9RegisterResource = dlsym(handle, "cudaGraphicsD3D9RegisterResource");
    printf("cudaGraphicsD3D9RegisterResource \n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsD3D9RegisterResource)( resource, pD3DResource, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaD3D10GetDevice(int* device, IDXGIAdapter* pAdapter) {
        
    init_func();
    cudaError_t (*fakecudaD3D10GetDevice)(int* , IDXGIAdapter* );
    fakecudaD3D10GetDevice = dlsym(handle, "cudaD3D10GetDevice");
    printf("cudaD3D10GetDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaD3D10GetDevice)( device,  pAdapter);
    //dlclose(handle);
    return r;
}

cudaError_t cudaD3D10GetDevices(unsigned int* pCudaDeviceCount, int* pCudaDevices, unsigned int cudaDeviceCount, ID3D10Device* pD3D10Device, cudaD3D10DeviceList deviceList) {
        
    init_func();
    cudaError_t (*fakecudaD3D10GetDevices)(unsigned int* , int* , unsigned int, ID3D10Device* , cudaD3D10DeviceList );
    fakecudaD3D10GetDevices = dlsym(handle, "cudaD3D10GetDevices");
    printf("cudaD3D10GetDevices\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaD3D10GetDevices)( pCudaDeviceCount,  pCudaDevices, cudaDeviceCount, pD3D10Device, deviceList);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsD3D10RegisterResource(cudaGraphicsResource** resource, ID3D10Resource* pD3DResource, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsD3D10RegisterResource)(cudaGraphicsResource** , ID3D10Resource* , unsigned int );
    fakecudaGraphicsD3D10RegisterResource = dlsym(handle, "cudaGraphicsD3D10RegisterResource");
    printf("cudaGraphicsD3D10RegisterResource\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsD3D10RegisterResource)(resource,  pD3DResource, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaD3D11GetDevice(int* device, IDXGIAdapter* pAdapter) {
        
    init_func();
    cudaError_t (*fakecudaD3D11GetDevice)(int* , IDXGIAdapter* );
    fakecudaD3D11GetDevice = dlsym(handle, "cudaD3D11GetDevice");
    printf("cudaD3D11GetDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaD3D11GetDevice)(device, pAdapter);
    //dlclose(handle);
    return r;
}

cudaError_t cudaD3D11GetDevices(unsigned int* pCudaDeviceCount, int* pCudaDevices, unsigned int  cudaDeviceCount, ID3D11Device* pD3D11Device, cudaD3D11DeviceList deviceList) {
        
    init_func();
    cudaError_t (*fakecudaD3D11GetDevices)(unsigned int* , int* , unsigned int , ID3D11Device* , cudaD3D11DeviceList );
    fakecudaD3D11GetDevices = dlsym(handle, "cudaD3D11GetDevices");
    printf("cudaD3D11GetDevices\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaD3D11GetDevices)( pCudaDeviceCount,  pCudaDevices,  cudaDeviceCount, pD3D11Device,  deviceList);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsD3D11RegisterResource(cudaGraphicsResource** resource, ID3D11Resource* pD3DResource, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsD3D11RegisterResource)(cudaGraphicsResource** , ID3D11Resource* , unsigned int );
    fakecudaGraphicsD3D11RegisterResource = dlsym(handle, "cudaGraphicsD3D11RegisterResource");
    printf("cudaGraphicsD3D11RegisterResource\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsD3D11RegisterResource)(resource, pD3DResource,  flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsVDPAURegisterOutputSurface(cudaGraphicsResource** resource, VdpOutputSurface vdpSurface, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsVDPAURegisterOutputSurface)(cudaGraphicsResource** , VdpOutputSurface, unsigned int );
    fakecudaGraphicsVDPAURegisterOutputSurface = dlsym(handle, "cudaGraphicsVDPAURegisterOutputSurface");
    printf("cudaGraphicsVDPAURegisterOutputSurface\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsVDPAURegisterOutputSurface)(resource,  vdpSurface,  flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsVDPAURegisterVideoSurface(cudaGraphicsResource** resource, VdpVideoSurface  vdpSurface, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsVDPAURegisterVideoSurface)(cudaGraphicsResource** , VdpVideoSurface , unsigned int );
    fakecudaGraphicsVDPAURegisterVideoSurface = dlsym(handle, "cudaGraphicsVDPAURegisterVideoSurface");
    printf("cudaGraphicsVDPAURegisterVideoSurface\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsVDPAURegisterVideoSurface)(resource,  vdpSurface,  flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaVDPAUGetDevice(int* device, VdpDevice vdpDevice, VdpGetProcAddress* vdpGetProcAddress) {
        
    init_func();
    cudaError_t (*fakecudaVDPAUGetDevice)(int* , VdpDevice , VdpGetProcAddress* );
    fakecudaVDPAUGetDevice = dlsym(handle, "cudaVDPAUGetDevice");
    printf("cudaVDPAUGetDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaVDPAUGetDevice)( device,  vdpDevice,  vdpGetProcAddress);
    //dlclose(handle);
    return r;
}

cudaError_t cudaVDPAUSetVDPAUDevice(int device, VdpDevice vdpDevice, VdpGetProcAddress* vdpGetProcAddress) {
        
    init_func();
    cudaError_t (*fakecudaVDPAUSetVDPAUDevice)(int , VdpDevice , VdpGetProcAddress* );
    fakecudaVDPAUSetVDPAUDevice = dlsym(handle, "cudaVDPAUSetVDPAUDevice");
    printf("cudaVDPAUSetVDPAUDevice\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaVDPAUSetVDPAUDevice)( device, vdpDevice,  vdpGetProcAddress);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEGLStreamConsumerAcquireFrame(cudaEglStreamConnection* conn, cudaGraphicsResource_t* pCudaResource, cudaStream_t* pStream, unsigned int  timeout) {
        
    init_func();
    cudaError_t (*fakecudaEGLStreamConsumerAcquireFrame)(cudaEglStreamConnection* , cudaGraphicsResource_t* , cudaStream_t* , unsigned int);
    fakecudaEGLStreamConsumerAcquireFrame = dlsym(handle, "cudaEGLStreamConsumerAcquireFrame");
    printf("cudaEGLStreamConsumerAcquireFrame\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEGLStreamConsumerAcquireFrame)( conn, pCudaResource,  pStream,timeout);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEGLStreamConsumerConnect(cudaEglStreamConnection* conn, EGLStreamKHR eglStream) {
        
    init_func();
    cudaError_t (*fakecudaEGLStreamConsumerConnect)(cudaEglStreamConnection* , EGLStreamKHR );
    fakecudaEGLStreamConsumerConnect = dlsym(handle, "cudaEGLStreamConsumerConnect");
    printf("cudaEGLStreamConsumerConnect\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEGLStreamConsumerConnect)( conn, eglStream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEGLStreamConsumerConnectWithFlags(cudaEglStreamConnection* conn, EGLStreamKHR eglStream,unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaEGLStreamConsumerConnectWithFlags)(cudaEglStreamConnection* , EGLStreamKHR ,unsigned int );
    fakecudaEGLStreamConsumerConnectWithFlags = dlsym(handle, "cudaEGLStreamConsumerConnectWithFlags");
    printf("cudaEGLStreamConsumerConnectWithFlags\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEGLStreamConsumerConnectWithFlags)( conn, eglStream,flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEGLStreamConsumerDisconnect(cudaEglStreamConnection* conn) {
        
    init_func();
    cudaError_t (*fakecudaEGLStreamConsumerDisconnect)(cudaEglStreamConnection* );
    fakecudaEGLStreamConsumerDisconnect = dlsym(handle, "cudaEGLStreamConsumerDisconnect");
    printf("cudaEGLStreamConsumerDisconnect\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEGLStreamConsumerDisconnect)( conn);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEGLStreamConsumerReleaseFrame(cudaEglStreamConnection* conn, cudaGraphicsResource_t pCudaResource, cudaStream_t* pStream) {
        
    init_func();
    cudaError_t (*fakecudaEGLStreamConsumerReleaseFrame)(cudaEglStreamConnection* , cudaGraphicsResource_t , cudaStream_t* );
    fakecudaEGLStreamConsumerReleaseFrame = dlsym(handle, "cudaEGLStreamConsumerReleaseFrame");
    printf("cudaEGLStreamConsumerReleaseFrame\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEGLStreamConsumerReleaseFrame)( conn,  pCudaResource,  pStream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEGLStreamProducerConnect(cudaEglStreamConnection* conn, EGLStreamKHR eglStream, EGLint width, EGLint height) {
        
    init_func();
    cudaError_t (*fakecudaEGLStreamProducerConnect)(cudaEglStreamConnection* , EGLStreamKHR , EGLint, EGLint);
    fakecudaEGLStreamProducerConnect = dlsym(handle, "cudaEGLStreamProducerConnect");
    printf("cudaEGLStreamProducerConnect\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEGLStreamProducerConnect)(conn,  eglStream,  width,  height);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEGLStreamProducerDisconnect(cudaEglStreamConnection* conn) {
        
    init_func();
    cudaError_t (*fakecudaEGLStreamProducerDisconnect)(cudaEglStreamConnection* );
    fakecudaEGLStreamProducerDisconnect = dlsym(handle, "cudaEGLStreamProducerDisconnect");
    printf("cudaEGLStreamProducerDisconnect\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEGLStreamProducerDisconnect)(conn);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEGLStreamProducerPresentFrame(cudaEglStreamConnection* conn, cudaEglFrame eglframe, cudaStream_t* pStream) {
        
    init_func();
    cudaError_t (*fakecudaEGLStreamProducerPresentFrame)(cudaEglStreamConnection* , cudaEglFrame , cudaStream_t* );
    fakecudaEGLStreamProducerPresentFrame = dlsym(handle, "cudaEGLStreamProducerPresentFrame");
    printf("cudaEGLStreamProducerPresentFrame\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEGLStreamProducerPresentFrame)( conn,  eglframe,  pStream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEGLStreamProducerReturnFrame(cudaEglStreamConnection* conn, cudaEglFrame* eglframe, cudaStream_t* pStream) {
        
    init_func();
    cudaError_t (*fakecudaEGLStreamProducerReturnFrame)(cudaEglStreamConnection* , cudaEglFrame* , cudaStream_t* );
    fakecudaEGLStreamProducerReturnFrame = dlsym(handle, "cudaEGLStreamProducerReturnFrame");
    printf("cudaEGLStreamProducerReturnFrame\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEGLStreamProducerReturnFrame)( conn,  eglframe,  pStream);
    //dlclose(handle);
    return r;
}

cudaError_t cudaEventCreateFromEGLSync(cudaEvent_t* phEvent, EGLSyncKHR eglSync, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaEventCreateFromEGLSync)(cudaEvent_t* , EGLSyncKHR , unsigned int);
    fakecudaEventCreateFromEGLSync = dlsym(handle, "cudaEventCreateFromEGLSync");
    printf("cudaEventCreateFromEGLSync\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaEventCreateFromEGLSync)(phEvent, eglSync, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsEGLRegisterImage(cudaGraphicsResource** pCudaResource, EGLImageKHR image, unsigned int  flags) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsEGLRegisterImage)(cudaGraphicsResource** , EGLImageKHR , unsigned int );
    fakecudaGraphicsEGLRegisterImage = dlsym(handle, "cudaGraphicsEGLRegisterImage");
    printf("cudaGraphicsEGLRegisterImage\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsEGLRegisterImage)(pCudaResource,  image, flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaGraphicsResourceGetMappedEglFrame(cudaEglFrame* eglFrame, cudaGraphicsResource_t resource, unsigned int  index, unsigned int  mipLevel) {
        
    init_func();
    cudaError_t (*fakecudaGraphicsResourceGetMappedEglFrame)(cudaEglFrame* , cudaGraphicsResource_t , unsigned int , unsigned int );
    fakecudaGraphicsResourceGetMappedEglFrame = dlsym(handle, "cudaGraphicsResourceGetMappedEglFrame");
    printf("cudaGraphicsResourceGetMappedEglFrame\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error); 
        exit(1);
    }
    cudaError_t r= (*fakecudaGraphicsResourceGetMappedEglFrame)( eglFrame, resource, index, mipLevel);
    //dlclose(handle);
    return r;
}*/
