#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cuda.h>
#include <string.h>
#include <sys/time.h>

static const char LIB_STRING[] = "libcuda.so";
long long cnt = 0;

#define checkCudaErrors(err)  __checkCudaErrors (err, __FILE__, __LINE__)
void __checkCudaErrors( CUresult err, const char *file, const int line )
{
    if( CUDA_SUCCESS != err) {
        fprintf(stderr,
                "CUDA Driver API error = %04d from file <%s>, line %i.\n",
                err, file, line );
        //exit(-1);
    }
    /*cnt++;
    printf("%lld\n",cnt);
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("millisecond: %ld\n", tv.tv_sec * 1000 + tv.tv_usec / 1000);*/
}


CUresult cuDeviceGetName(char *name, int len, CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceGetName)(char*, int, CUdevice);
    fakecuDeviceGetName = dlsym(handle, "cuDeviceGetName");
    printf("cuDeviceGetName\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetName)(name, len, dev));
    //strcpy(name, "yzs's GPU");
    dlclose(handle);
}

CUresult cuInit(unsigned int Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuInit)(unsigned int);
    fakecuInit = dlsym(handle, "cuInit");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    printf("cuInit\n");

    //printf("Flags: %d\n", Flags);
    checkCudaErrors((*fakecuInit)(Flags));
    dlclose(handle);
}

CUresult cuDeviceGet(CUdevice* device, int ordinal) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceGet)(CUdevice* , int);
    fakecuDeviceGet = dlsym(handle, "cuDeviceGet");
    printf("cuDeviceGet\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGet)(device, ordinal));
    dlclose(handle);
}

CUresult cuDriverGetVersion(int *driverVersion) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDriverGetVersion)(int *);
    fakecuDriverGetVersion = dlsym(handle, "cuDriverGetVersion");
    printf("cuDriverGetVersion\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDriverGetVersion)(driverVersion));
    dlclose(handle);
}

CUresult cuDeviceGetCount(int *count) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceGetCount)(int *);
    fakecuDeviceGetCount = dlsym(handle, "cuDeviceGetCount");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    printf("cuDeviceGetCount\n" );
    checkCudaErrors((*fakecuDeviceGetCount)(count));
    dlclose(handle);
}

// deprecated
CUresult cuDeviceComputeCapability(int *major, int * minor, CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceComputeCapability)(int *, int *, CUdevice);
    fakecuDeviceComputeCapability = dlsym(handle, "cuDeviceComputeCapability");
    printf("cuDeviceComputeCapability\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceComputeCapability)(major, minor, dev));
    dlclose(handle);
}

CUresult cuDeviceTotalMem_v2(size_t *bytes, CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceTotalMem_v2)(size_t *, CUdevice);
    fakecuDeviceTotalMem_v2 = dlsym(handle, "cuDeviceTotalMem_v2");
    printf("cuDeviceTotalMem_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceTotalMem_v2)(bytes, dev));
    dlclose(handle);
}

// deprecated
CUresult cuDeviceGetProperties(CUdevprop *prop, CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceGetProperties)(CUdevprop *, CUdevice);
    fakecuDeviceGetProperties = dlsym(handle, "cuDeviceGetProperties");
    printf("cuDeviceGetProperties\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetProperties)(prop, dev));
    dlclose(handle);
}

CUresult cuDeviceGetAttribute(int *pi, CUdevice_attribute attrib, CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceGetAttribute)(int *, CUdevice_attribute, CUdevice);
    fakecuDeviceGetAttribute = dlsym(handle, "cuDeviceGetAttribute");
    printf("cuDeviceGetAttribute\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetAttribute)(pi, attrib, dev));
    dlclose(handle);
}
 
CUresult cuDeviceGetLuid(char* luid, unsigned int* deviceNodeMask, CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceGetLuid)(char* , unsigned int* , CUdevice);
    fakecuDeviceGetLuid = dlsym(handle, "cuDeviceGetLuid");
    printf("cuDeviceGetLuid\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetLuid)(luid, deviceNodeMask, dev));
    dlclose(handle);
}

CUresult cuDeviceGetUuid(CUuuid* uuid, CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceGetUuid)(CUuuid* , CUdevice);
    fakecuDeviceGetUuid = dlsym(handle, "cuDeviceGetUuid");
    printf("cuDeviceGetUuid\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetUuid)(uuid, dev));
    dlclose(handle);
}

CUresult cuCtxCreate_v2(CUcontext *pctx, unsigned int flags, CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxCreate_v2)(CUcontext *, unsigned int, CUdevice);
    fakecuCtxCreate_v2 = dlsym(handle, "cuCtxCreate_v2");
    printf("cuCtxCreate_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxCreate_v2)(pctx, flags, dev));
    dlclose(handle);
}

CUresult cuCtxPushCurrent_v2(CUcontext pctx) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxPushCurrent_v2)(CUcontext);
    fakecuCtxPushCurrent_v2 = dlsym(handle, "cuCtxPushCurrent_v2");
    printf("cuCtxPushCurrent_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxPushCurrent_v2)(pctx));
    dlclose(handle);
}

CUresult cuCtxSetCacheConfig(CUfunc_cache config) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxSetCacheConfig)(CUfunc_cache );
    fakecuCtxSetCacheConfig = dlsym(handle, "cuCtxSetCacheConfig");
    printf("cuCtxSetCacheConfig\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxSetCacheConfig)(config));
    dlclose(handle);
}

CUresult cuCtxGetCurrent(CUcontext *pctx) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxGetCurrent)(CUcontext *);
    fakecuCtxGetCurrent = dlsym(handle, "cuCtxGetCurrent");
    printf("cuCtxGetCurrent\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetCurrent)(pctx));
    dlclose(handle);
}

CUresult cuCtxGetCacheConfig(CUfunc_cache* pconfig) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxGetCacheConfig)(CUfunc_cache*);
    fakecuCtxGetCacheConfig = dlsym(handle, "cuCtxGetCacheConfig");
    printf("cuCtxGetCacheConfig\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetCacheConfig)(pconfig));
    dlclose(handle);
}

CUresult cuCtxDestroy_v2(CUcontext ctx) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxDestroy_v2)(CUcontext);
    fakecuCtxDestroy_v2 = dlsym(handle, "cuCtxDestroy_v2");
    printf("cuCtxDestroy_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxDestroy_v2)(ctx));
    dlclose(handle);
}

CUresult cuCtxGetApiVersion(CUcontext ctx, unsigned int *version) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxGetApiVersion)(CUcontext, unsigned int *);
    fakecuCtxGetApiVersion = dlsym(handle, "cuCtxGetApiVersion");
    printf("cuCtxGetApiVersion\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetApiVersion)(ctx, version));
    dlclose(handle);
}

CUresult cuCtxSynchronize(void) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxSynchronize)(void);
    fakecuCtxSynchronize = dlsym(handle, "cuCtxSynchronize");
    printf("cuCtxSynchronize\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxSynchronize)());
    dlclose(handle);
}

CUresult cuModuleLoadData(CUmodule *module, const void *image ) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuModuleLoadData)(CUmodule* , const void* );
    fakecuModuleLoadData = dlsym(handle, "cuModuleLoadData");
    printf("cuModuleLoadData\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleLoadData)(module, image ));
    dlclose(handle);
}

CUresult cuModuleLoadDataEx(CUmodule *module, const void *image, unsigned int numOptions, CUjit_option *options, void **optionValues) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuModuleLoadDataEx)(CUmodule *, const void *, unsigned int, CUjit_option *, void **);
    fakecuModuleLoadDataEx = dlsym(handle, "cuModuleLoadDataEx");
    printf("cuModuleLoadDataEx\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleLoadDataEx)(module, image, numOptions, options, optionValues));
    dlclose(handle);
}

CUresult cuLinkAddData(CUlinkState state, CUjitInputType type, void* data, size_t size, const char* name, unsigned int numOptions, CUjit_option* options, void** optionValues) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuLinkAddData)(CUlinkState , CUjitInputType , void* , size_t , const char* , unsigned int , CUjit_option* , void** );
    fakecuLinkAddData = dlsym(handle, "cuLinkAddData");
    printf("cuLinkAddData\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuLinkAddData)(state, type, data, size, name, numOptions, options, optionValues));
    dlclose(handle);
}

CUresult cuLinkAddFile(CUlinkState state, CUjitInputType type, const char* path, unsigned int numOptions, CUjit_option* options, void** optionValues) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuLinkAddFile)(CUlinkState , CUjitInputType , const char* , unsigned int , CUjit_option* , void** );
    fakecuLinkAddFile = dlsym(handle, "cuLinkAddFile");
    printf("cuLinkAddFile\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuLinkAddFile)(state, type, path, numOptions, options, optionValues));
    dlclose(handle);
}

CUresult cuLinkComplete(CUlinkState state, void** cubinOut, size_t* sizeOut) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuLinkComplete)(CUlinkState ,  void** , size_t* );
    fakecuLinkComplete = dlsym(handle, "cuLinkComplete");
    printf("cuLinkComplete\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuLinkComplete)(state, cubinOut, sizeOut));
    dlclose(handle);
}

CUresult cuLinkCreate(unsigned int numOptions, CUjit_option* options, void** optionValues, CUlinkState* stateOut) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuLinkCreate)(unsigned int , CUjit_option* , void** , CUlinkState* );
    fakecuLinkCreate = dlsym(handle, "cuLinkCreate");
    printf("cuLinkCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuLinkCreate)(numOptions, options, optionValues, stateOut));
    dlclose(handle);
}

CUresult cuLinkDestroy(CUlinkState state) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuLinkDestroy)(CUlinkState );
    fakecuLinkDestroy = dlsym(handle, "cuLinkDestroy");
    printf("cuLinkDestroy\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuLinkDestroy)(state));
    dlclose(handle);
}

CUresult cuModuleUnload(CUmodule hmod) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuModuleUnload)(CUmodule);
    fakecuModuleUnload = dlsym(handle, "cuModuleUnload");
    printf("cuModuleUnload\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleUnload)(hmod));
    dlclose(handle);
}

CUresult cuArray3DCreate(CUarray* pHandle, const CUDA_ARRAY3D_DESCRIPTOR* pAllocateArray) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuArray3DCreate)(CUarray* , const CUDA_ARRAY3D_DESCRIPTOR* );
    fakecuArray3DCreate = dlsym(handle, "cuArray3DCreate");
    printf("cuArray3DCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuArray3DCreate)(pHandle, pAllocateArray));
    dlclose(handle);
}

CUresult cuArray3DGetDescriptor(CUDA_ARRAY3D_DESCRIPTOR* pArrayDescriptor, CUarray hArray) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuArray3DGetDescriptor)(CUDA_ARRAY3D_DESCRIPTOR* , CUarray );
    fakecuArray3DGetDescriptor = dlsym(handle, "cuArray3DGetDescriptor");
    printf("cuArray3DGetDescriptor\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuArray3DGetDescriptor)(pArrayDescriptor, hArray));
    dlclose(handle);
}

CUresult cuArrayCreate(CUarray* pHandle, const CUDA_ARRAY_DESCRIPTOR* pAllocateArray) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuArrayCreate)(CUarray* ,const CUDA_ARRAY_DESCRIPTOR* );
    fakecuArrayCreate = dlsym(handle, "cuArrayCreate");
    printf("cuArrayCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuArrayCreate)(pHandle, pAllocateArray));
    dlclose(handle);
}

CUresult cuArrayDestroy(CUarray hArray) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuArrayDestroy)(CUarray );
    fakecuArrayDestroy = dlsym(handle, "cuArrayDestroy");
    printf("cuArrayDestroy\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuArrayDestroy)(hArray));
    dlclose(handle);
}

CUresult cuArrayGetDescriptor(CUDA_ARRAY_DESCRIPTOR* pArrayDescriptor, CUarray hArray) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuArrayGetDescriptor)(CUDA_ARRAY_DESCRIPTOR* , CUarray );
    fakecuArrayGetDescriptor = dlsym(handle, "cuArrayGetDescriptor");
    printf("cuArrayGetDescriptor\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuArrayGetDescriptor)(pArrayDescriptor,hArray));
    dlclose(handle);
}

CUresult cuDeviceGetByPCIBusId(CUdevice* dev, const char* pciBusId) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceGetByPCIBusId)(CUdevice* , const char* );
    fakecuDeviceGetByPCIBusId = dlsym(handle, "cuDeviceGetByPCIBusId");
    printf("cuDeviceGetByPCIBusId\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetByPCIBusId)(dev, pciBusId));
    dlclose(handle);
}

CUresult cuModuleGetFunction(CUfunction* hfunc, CUmodule hmod, const char* name) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuModuleGetFunction)(CUfunction *, CUmodule, const char *);
    fakecuModuleGetFunction = dlsym(handle, "cuModuleGetFunction");
    printf("cuModuleGetFunction\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleGetFunction)(hfunc, hmod, name));
    dlclose(handle);
}

CUresult cuModuleGetGlobal_v2(CUdeviceptr* dptr, size_t* bytes, CUmodule hmod, const char* name) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuModuleGetGlobal_v2)(CUdeviceptr *, size_t *, CUmodule, const char *);
    fakecuModuleGetGlobal_v2 = dlsym(handle, "cuModuleGetGlobal_v2");
    printf("cuModuleGetGlobal_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleGetGlobal_v2)(dptr, bytes, hmod, name));
    dlclose(handle);
}

CUresult cuModuleGetSurfRef(CUsurfref* pSurfRef, CUmodule hmod, const char* name) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuModuleGetSurfRef)(CUsurfref* , CUmodule , const char* );
    fakecuModuleGetSurfRef = dlsym(handle, "cuModuleGetSurfRef");
    printf("cuModuleGetSurfRef\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleGetSurfRef)(pSurfRef, hmod, name));
    dlclose(handle);
}

CUresult cuModuleGetTexRef(CUtexref* pTexRef, CUmodule hmod, const char* name) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuModuleGetTexRef)(CUtexref* , CUmodule , const char* );
    fakecuModuleGetTexRef = dlsym(handle, "cuModuleGetTexRef");
    printf("cuModuleGetTexRef\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleGetTexRef)(pTexRef, hmod, name));
    dlclose(handle);
}

CUresult cuModuleLoad(CUmodule* module, const char* fname) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuModuleLoad)(CUmodule* , const char* );
    fakecuModuleLoad = dlsym(handle, "cuModuleLoad");
    printf("cuModuleLoad\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleLoad)(module, fname));
    dlclose(handle);
}

CUresult cuFuncSetBlockShape(CUfunction hfunc, int x, int y, int z) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuFuncSetBlockShape)(CUfunction, int, int, int);
    fakecuFuncSetBlockShape = dlsym(handle, "cuFuncSetBlockShape");
    printf("cuFuncSetBlockShape\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuFuncSetBlockShape)(hfunc, x, y, z));
    dlclose(handle);
}

CUresult cuFuncSetSharedSize(CUfunction hfunc, unsigned int bytes) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuFuncSetSharedSize)(CUfunction, unsigned int);
    fakecuFuncSetSharedSize = dlsym(handle, "cuFuncSetSharedSize");
    printf("cuFuncSetSharedSize\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuFuncSetSharedSize)(hfunc, bytes));
    dlclose(handle);
}

CUresult cuMemGetInfo_v2(size_t *free, size_t *total) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemGetInfo_v2)(size_t *, size_t *);
    fakecuMemGetInfo_v2 = dlsym(handle, "cuMemGetInfo_v2");
    printf("cuMemGetInfo_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemGetInfo_v2)(free, total));
    *free =  *free/2;
    *total = *total / 2;
    printf("free : %zu, total : %zu\n", *free, *total);
    dlclose(handle);
}

CUresult cuEventElapsedTime(float* pMilliseconds, CUevent hStart, CUevent hEnd) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEventElapsedTime)(float *, CUevent, CUevent);
    fakecuEventElapsedTime = dlsym(handle, "cuEventElapsedTime");
    printf("cuEventElapsedTime\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEventElapsedTime)(pMilliseconds, hStart, hEnd));
    dlclose(handle);
}

CUresult cuEventDestroy_v2(CUevent hEvent) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEventDestroy_v2)(CUevent);
    fakecuEventDestroy_v2 = dlsym(handle, "cuEventDestroy_v2");
    printf("cuEventDestroy_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEventDestroy_v2)(hEvent));
    dlclose(handle);
}

CUresult cuEventSynchronize(CUevent hEvent) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEventSynchronize)(CUevent);
    fakecuEventSynchronize = dlsym(handle, "cuEventSynchronize");
    printf("cuEventSynchronize\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEventSynchronize)(hEvent));
    dlclose(handle);
}

CUresult cuDestroyExternalMemory(CUexternalMemory extMem) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDestroyExternalMemory)(CUexternalMemory );
    fakecuDestroyExternalMemory = dlsym(handle, "cuDestroyExternalMemory");
    printf("cuDestroyExternalMemory\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDestroyExternalMemory)(extMem));
    dlclose(handle);
}

CUresult cuDestroyExternalSemaphore(CUexternalSemaphore extSem) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDestroyExternalSemaphore)(CUexternalSemaphore );
    fakecuDestroyExternalSemaphore = dlsym(handle, "cuDestroyExternalSemaphore");
    printf("cuDestroyExternalSemaphore\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDestroyExternalSemaphore)(extSem));
    dlclose(handle);
}

CUresult cuExternalMemoryGetMappedBuffer(CUdeviceptr* devPtr, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC* bufferDesc) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuExternalMemoryGetMappedBuffer)(CUdeviceptr* , CUexternalMemory , const CUDA_EXTERNAL_MEMORY_BUFFER_DESC* );
    fakecuExternalMemoryGetMappedBuffer = dlsym(handle, "cuExternalMemoryGetMappedBuffer");
    printf("cuExternalMemoryGetMappedBuffer\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuExternalMemoryGetMappedBuffer)(devPtr, extMem, bufferDesc));
    dlclose(handle);
}

CUresult cuExternalMemoryGetMappedMipmappedArray(CUmipmappedArray* mipmap, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC* mipmapDesc) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuExternalMemoryGetMappedMipmappedArray)(CUmipmappedArray* , CUexternalMemory , const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC* );
    fakecuExternalMemoryGetMappedMipmappedArray = dlsym(handle, "cuExternalMemoryGetMappedMipmappedArray");
    printf("cuExternalMemoryGetMappedMipmappedArray\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuExternalMemoryGetMappedMipmappedArray)(mipmap, extMem, mipmapDesc));
    dlclose(handle);
}

CUresult cuImportExternalMemory(CUexternalMemory* extMem_out, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC* memHandleDesc) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuImportExternalMemory)(CUexternalMemory* , const CUDA_EXTERNAL_MEMORY_HANDLE_DESC* );
    fakecuImportExternalMemory = dlsym(handle, "cuImportExternalMemory");
    printf("cuImportExternalMemory\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuImportExternalMemory)(extMem_out, memHandleDesc));
    dlclose(handle);
}

CUresult cuImportExternalSemaphore(CUexternalSemaphore* extSem_out, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC* semHandleDesc) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuImportExternalSemaphore)(CUexternalSemaphore* , const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC* );
    fakecuImportExternalSemaphore = dlsym(handle, "cuImportExternalSemaphore");
    printf("cuImportExternalSemaphore\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuImportExternalSemaphore)(extSem_out, semHandleDesc));
    dlclose(handle);
}

CUresult cuSignalExternalSemaphoresAsync(const CUexternalSemaphore* extSemArray, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS* paramsArray, unsigned int  numExtSems, CUstream stream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuSignalExternalSemaphoresAsync)(const CUexternalSemaphore* , const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS* , unsigned int , CUstream );
    fakecuSignalExternalSemaphoresAsync = dlsym(handle, "cuSignalExternalSemaphoresAsync");
    printf("cuSignalExternalSemaphoresAsync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuSignalExternalSemaphoresAsync)(extSemArray, paramsArray, numExtSems, stream));
    dlclose(handle);
}

CUresult cuWaitExternalSemaphoresAsync(const CUexternalSemaphore* extSemArray, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS* paramsArray, unsigned int numExtSems, CUstream stream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuWaitExternalSemaphoresAsync)(const CUexternalSemaphore* , const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS* , unsigned int , CUstream );
    fakecuWaitExternalSemaphoresAsync = dlsym(handle, "cuWaitExternalSemaphoresAsync");
    printf("cuWaitExternalSemaphoresAsync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuWaitExternalSemaphoresAsync)(extSemArray, paramsArray, numExtSems, stream));
    dlclose(handle);
}

CUresult cuEventQuery(CUevent hEvent) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEventQuery)(CUevent);
    fakecuEventQuery = dlsym(handle, "cuEventQuery");
    printf("cuEventQuery\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuEventQuery)(hEvent));
    dlclose(handle);
    return r;
}

CUresult cuStreamBatchMemOp(CUstream stream, unsigned int count, CUstreamBatchMemOpParams* paramArray, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamBatchMemOp)(CUstream , unsigned int, CUstreamBatchMemOpParams* , unsigned int );
    fakecuStreamBatchMemOp = dlsym(handle, "cuStreamBatchMemOp");
    printf("cuStreamBatchMemOp\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuStreamBatchMemOp)(stream, count, paramArray, flags));
    dlclose(handle);
    return r;
}

CUresult cuStreamWaitValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamWaitValue32)(CUstream , CUdeviceptr , cuuint32_t , unsigned int );
    fakecuStreamWaitValue32 = dlsym(handle, "cuStreamWaitValue32");
    printf("cuStreamWaitValue32\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuStreamWaitValue32)(stream, addr, value, flags));
    dlclose(handle);
    return r;
}

CUresult cuStreamWaitValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamWaitValue64)(CUstream , CUdeviceptr , cuuint64_t , unsigned int );
    fakecuStreamWaitValue64 = dlsym(handle, "cuStreamWaitValue64");
    printf("cuStreamWaitValue64\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuStreamWaitValue64)(stream, addr, value, flags));
    dlclose(handle);
    return r;
}

CUresult cuStreamWriteValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamWriteValue32)(CUstream , CUdeviceptr , cuuint32_t , unsigned int );
    fakecuStreamWriteValue32 = dlsym(handle, "cuStreamWriteValue32");
    printf("cuStreamWriteValue32\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuStreamWriteValue32)(stream, addr, value, flags));
    dlclose(handle);
    return r;
}

CUresult cuStreamWriteValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamWriteValue64)(CUstream , CUdeviceptr , cuuint64_t , unsigned int );
    fakecuStreamWriteValue64 = dlsym(handle, "cuStreamWriteValue64");
    printf("cuStreamWriteValue64\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuStreamWriteValue64)(stream, addr, value, flags));
    dlclose(handle);
    return r;
}

CUresult cuEventRecord(CUevent hEvent, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEventRecord)(CUevent, CUstream);
    fakecuEventRecord = dlsym(handle, "cuEventRecord");
    printf("cuEventRecord\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEventRecord)(hEvent, hStream));
    dlclose(handle);
}


CUresult cuEventCreate(CUevent* phEvent, unsigned int Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEventCreate)(CUevent * , unsigned int);
    fakecuEventCreate = dlsym(handle, "cuEventCreate");
    printf("cuEventCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEventCreate)(phEvent, Flags));
    dlclose(handle);
}

//deprecated
CUresult cuLaunchGrid(CUfunction f, int grid_width, int grid_height) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuLaunchGrid)(CUfunction, int, int);
    fakecuLaunchGrid = dlsym(handle, "cuLaunchGrid");
    printf("cuLaunchGrid\n");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuLaunchGrid)(f, grid_width, grid_height));
    dlclose(handle);
}

//deprecated
CUresult cuParamSetv(CUfunction hfunc, int offset, void* ptr, unsigned int numbytes) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuParamSetv)(CUfunction, int, void* , unsigned int);
    fakecuParamSetv = dlsym(handle, "cucuParamSetv");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuParamSetv)(hfunc, offset, ptr, numbytes));
    dlclose(handle);
}

//deprecated
CUresult cuParamSetSize(CUfunction hfunc, unsigned int numbytes) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuParamSetSize)(CUfunction, unsigned int);
    fakecuParamSetSize = dlsym(handle, "cuParamSetSize");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuParamSetSize)(hfunc, numbytes));
    dlclose(handle);
}

CUresult cuMemcpyDtoH_v2(void* dstHost, CUdeviceptr srcDevice, size_t ByteCount) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyDtoH_v2)(void* , CUdeviceptr, size_t);
    fakecuMemcpyDtoH_v2 = dlsym(handle, "cuMemcpyDtoH_v2");
    printf("cuMemcpyDtoH_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyDtoH_v2)(dstHost, srcDevice, ByteCount));
    dlclose(handle);
}

CUresult cuMemcpyHtoD_v2(CUdeviceptr dstDevice, const void* srcHost, size_t ByteCount) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyHtoD_v2)(CUdeviceptr, const void* , size_t);
    fakecuMemcpyHtoD_v2 = dlsym(handle, "cuMemcpyHtoD_v2");
    printf("cuMemcpyHtoD_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyHtoD_v2)(dstDevice, srcHost, ByteCount));
    dlclose(handle);
}

CUresult cuMemHostGetFlags(unsigned int* pFlags, void* p) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemHostGetFlags)(unsigned int* , void* );
    fakecuMemHostGetFlags = dlsym(handle, "cuMemHostGetFlags");
    printf("cuMemHostGetFlags\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemHostGetFlags)(pFlags, p));
    dlclose(handle);
}

CUresult cuMemHostGetDevicePointer_v2(CUdeviceptr* pdptr, void* p, unsigned int Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemHostGetDevicePointer_v2)(CUdeviceptr* , void* , unsigned int);
    fakecuMemHostGetDevicePointer_v2 = dlsym(handle, "cuMemHostGetDevicePointer_v2");
    printf("cuMemHostGetDevicePointer_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemHostGetDevicePointer_v2)(pdptr, p, Flags));
    dlclose(handle);
}

CUresult cuMemHostUnregister(void* p) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemHostUnregister)(void* );
    fakecuMemHostUnregister = dlsym(handle, "cuMemHostUnregister");
    printf("cuMemHostUnregister\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemHostUnregister)(p));
    dlclose(handle);
}

CUresult cuMemHostRegister(void* p, size_t bytesize, unsigned int Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemHostRegister)(void* , size_t, unsigned int);
    fakecuMemHostRegister = dlsym(handle, "cuMemHostRegister");
    printf("cuMemHostRegister\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemHostRegister)(p, bytesize, Flags));
    dlclose(handle);
}

CUresult cuMemHostAlloc(void** pp, size_t bytesize, unsigned int Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemHostAlloc)(void** , size_t, unsigned int);
    fakecuMemHostAlloc = dlsym(handle, "cuMemHostAlloc");
    printf("cuMemHostAlloc\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemHostAlloc)(pp, bytesize, Flags));
    dlclose(handle);
}

CUresult cuMemFreeHost(void* p) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemFreeHost)(void* );
    fakecuMemFreeHost = dlsym(handle, "cuMemFreeHost");
    printf("cuMemFreeHost\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemFreeHost)(p));
    dlclose(handle);
}

CUresult cuMemAllocHost_v2(void** pp, size_t bytesize) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemAllocHost_v2)(void** , size_t);
    fakecuMemAllocHost_v2 = dlsym(handle, "cuMemAllocHost_v2");
    printf("cuMemAllocHost_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemAllocHost_v2)(pp, bytesize));
    dlclose(handle);
}

CUresult cuMemGetAddressRange_v2(CUdeviceptr* pbase, size_t* psize, CUdeviceptr dptr) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemGetAddressRange_v2)(CUdeviceptr* , size_t* , CUdeviceptr);
    fakecuMemGetAddressRange_v2 = dlsym(handle, "cuMemGetAddressRange_v2");
    printf("cuMemGetAddressRange_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemGetAddressRange_v2)(pbase, psize, dptr));
    dlclose(handle);
}

CUresult cuMemFree_v2(CUdeviceptr dptr) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemFree_v2)(CUdeviceptr);
    fakecuMemFree_v2 = dlsym(handle, "cuMemFree_v2");
    printf("cuMemFree\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemFree_v2)(dptr));
    dlclose(handle);
}

CUresult cuMemAlloc_v2(CUdeviceptr* dptr, size_t bytesize) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemAlloc_v2)(CUdeviceptr* , size_t);
    fakecuMemAlloc_v2 = dlsym(handle, "cuMemAlloc_v2");
    printf("cuMemAlloc_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemAlloc_v2)(dptr, bytesize));
    dlclose(handle);
}

CUresult cuMemAllocPitch(CUdeviceptr* dptr, size_t* pPitch, size_t WidthInBytes, size_t Height, unsigned int  ElementSizeBytes) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemAllocPitch)(CUdeviceptr* , size_t* , size_t, size_t, unsigned int );
    fakecuMemAllocPitch = dlsym(handle, "cuMemAllocPitch");
    printf("cuMemAllocPitch\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemAllocPitch)(dptr, pPitch, WidthInBytes, Height, ElementSizeBytes));
    dlclose(handle);
}

CUresult cuMemsetD32Async(CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream ) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD32Async)(CUdeviceptr, unsigned int, size_t, CUstream);
    fakecuMemsetD32Async = dlsym(handle, "cuMemsetD32Async");
    printf("cuMemsetD32Async\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD32Async)(dstDevice, ui, N, hStream));
    dlclose(handle);
}

CUresult cuStreamAddCallback (CUstream hStream, CUstreamCallback callback, void* userData, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamAddCallback)(CUstream, CUstreamCallback, void *, unsigned int);
    fakecuStreamAddCallback = dlsym(handle, "cuStreamAddCallback");
    printf("cuStreamAddCallback\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamAddCallback)(hStream, callback, userData, flags));
    dlclose(handle);
}

CUresult cuStreamAttachMemAsync (CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int  flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamAttachMemAsync)(CUstream, CUdeviceptr, size_t, unsigned int);
    fakecuStreamAttachMemAsync = dlsym(handle, "cuStreamAttachMemAsync");
    printf("cuStreamAttachMemAsync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamAttachMemAsync)(hStream, dptr, length, flags));
    dlclose(handle);
}

CUresult cuStreamBeginCapture (CUstream hStream ) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamBeginCapture)(CUstream );
    fakecuStreamBeginCapture = dlsym(handle, "cuStreamBeginCapture");
    printf("cuStreamBeginCapture\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamBeginCapture)(hStream));
    dlclose(handle);
}

CUresult cuModuleLoadFatBinary(CUmodule* module, const void* fatCubin) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuModuleLoadFatBinary)(CUmodule *, const void *);
    fakecuModuleLoadFatBinary = dlsym(handle, "cuModuleLoadFatBinary");
    printf("cuModuleLoadFatBinary\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleLoadFatBinary)(module, fatCubin));
    dlclose(handle);
}

CUresult cuCtxEnablePeerAccess(CUcontext peerContext, unsigned int Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxEnablePeerAccess)(CUcontext, unsigned int);
    fakecuCtxEnablePeerAccess = dlsym(handle, "cuCtxEnablePeerAccess");
    printf("cuCtxEnablePeerAccess\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxEnablePeerAccess)(peerContext, Flags));
    dlclose(handle);
}

CUresult cuLaunchKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void** kernelParams, void** extra) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuLaunchKernel)(CUfunction, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, CUstream, void**, void**);
    fakecuLaunchKernel = dlsym(handle, "cuLaunchKernel");
    printf("cuLaunchKernel\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuLaunchKernel)(f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream, kernelParams, extra));
    dlclose(handle);
}

CUresult cuStreamSynchronize(CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamSynchronize)(CUstream);
    fakecuStreamSynchronize = dlsym(handle, "cuStreamSynchronize");
    printf("cuStreamSynchronize\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamSynchronize)(hStream));
    dlclose(handle);
}

CUresult cuGraphAddChildGraphNode(CUgraphNode* phGraphNode, CUgraph hGraph, CUgraphNode* dependencies, size_t numDependencies, CUgraph childGraph) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphAddChildGraphNode)(CUgraphNode* , CUgraph , CUgraphNode* , size_t , CUgraph );
    fakecuGraphAddChildGraphNode = dlsym(handle, "cuGraphAddChildGraphNode");
    printf("cuGraphAddChildGraphNode\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphAddChildGraphNode)(phGraphNode, hGraph, dependencies, numDependencies, childGraph));
    dlclose(handle);
}

CUresult cuGraphAddDependencies(CUgraph hGraph, CUgraphNode* from, CUgraphNode* to, size_t numDependencies) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphAddDependencies)(CUgraph , CUgraphNode* , CUgraphNode* , size_t );
    fakecuGraphAddDependencies = dlsym(handle, "cuGraphAddDependencies");
    printf("cuGraphAddDependencies\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphAddDependencies)(hGraph, from, to, numDependencies));
    dlclose(handle);
}

CUresult cuGraphAddEmptyNode(CUgraphNode* phGraphNode, CUgraph hGraph, CUgraphNode* dependencies, size_t numDependencies) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphAddEmptyNode)(CUgraphNode* , CUgraph , CUgraphNode* , size_t );
    fakecuGraphAddEmptyNode = dlsym(handle, "cuGraphAddEmptyNode");
    printf("cuGraphAddEmptyNode\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphAddEmptyNode)(phGraphNode, hGraph, dependencies, numDependencies));
    dlclose(handle);
}

CUresult cuGraphAddHostNode(CUgraphNode* phGraphNode, CUgraph hGraph, CUgraphNode* dependencies, size_t numDependencies, const CUDA_HOST_NODE_PARAMS* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphAddHostNode)(CUgraphNode* , CUgraph , CUgraphNode* , size_t , const CUDA_HOST_NODE_PARAMS* );
    fakecuGraphAddHostNode = dlsym(handle, "cuGraphAddHostNode");
    printf("cuGraphAddHostNode\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphAddHostNode)(phGraphNode, hGraph, dependencies, numDependencies, nodeParams));
    dlclose(handle);
}

CUresult cuGraphAddKernelNode(CUgraphNode* phGraphNode, CUgraph hGraph, CUgraphNode* dependencies, size_t numDependencies, const CUDA_KERNEL_NODE_PARAMS* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphAddKernelNode)(CUgraphNode* , CUgraph , CUgraphNode* , size_t , const CUDA_KERNEL_NODE_PARAMS* );
    fakecuGraphAddKernelNode = dlsym(handle, "cuGraphAddKernelNode");
    printf("cuGraphAddKernelNode\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphAddKernelNode)(phGraphNode, hGraph, dependencies, numDependencies, nodeParams));
    dlclose(handle);
}

CUresult cuGraphAddMemcpyNode(CUgraphNode* phGraphNode, CUgraph hGraph, CUgraphNode* dependencies, size_t numDependencies, const CUDA_MEMCPY3D* copyParams, CUcontext ctx) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphAddMemcpyNode)(CUgraphNode* , CUgraph , CUgraphNode* , size_t , const CUDA_MEMCPY3D* ,CUcontext );
    fakecuGraphAddMemcpyNode = dlsym(handle, "cuGraphAddMemcpyNode");
    printf("cuGraphAddMemcpyNode\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphAddMemcpyNode)(phGraphNode, hGraph, dependencies, numDependencies, copyParams, ctx));
    dlclose(handle);
}

CUresult cuGraphAddMemsetNode(CUgraphNode* phGraphNode, CUgraph hGraph, CUgraphNode* dependencies, size_t numDependencies, const CUDA_MEMSET_NODE_PARAMS* memsetParams, CUcontext ctx) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphAddMemsetNode)(CUgraphNode* , CUgraph , CUgraphNode* , size_t , const CUDA_MEMSET_NODE_PARAMS*  ,CUcontext );
    fakecuGraphAddMemsetNode = dlsym(handle, "cuGraphAddMemsetNode");
    printf("cuGraphAddMemsetNode\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphAddMemsetNode)(phGraphNode, hGraph, dependencies, numDependencies, memsetParams, ctx));
    dlclose(handle);
}

CUresult cuGraphChildGraphNodeGetGraph(CUgraphNode hNode, CUgraph* phGraph) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphChildGraphNodeGetGraph)(CUgraphNode , CUgraph* );
    fakecuGraphChildGraphNodeGetGraph = dlsym(handle, "cuGraphChildGraphNodeGetGraph");
    printf("cuGraphChildGraphNodeGetGraph\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphChildGraphNodeGetGraph)(hNode, phGraph));
    dlclose(handle);
}

CUresult cuGraphClone(CUgraph* phGraphClone, CUgraph originalGraph) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphClone)(CUgraph* , CUgraph );
    fakecuGraphClone = dlsym(handle, "cuGraphClone");
    printf("cuGraphClone\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphClone)(phGraphClone, originalGraph));
    dlclose(handle);
}

CUresult cuGraphCreate(CUgraph* phGraph, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphCreate)(CUgraph* , unsigned int );
    fakecuGraphCreate = dlsym(handle, "cuGraphCreate");
    printf("cuGraphCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphCreate)(phGraph, flags));
    dlclose(handle);
}

CUresult cuGraphDestroy(CUgraph hGraph) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphDestroy)(CUgraph );
    fakecuGraphDestroy = dlsym(handle, "cuGraphDestroy");
    printf("cuGraphDestroy\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphDestroy)(hGraph));
    dlclose(handle);
}

CUresult cuGraphDestroyNode(CUgraphNode hNode) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphDestroyNode)(CUgraphNode );
    fakecuGraphDestroyNode = dlsym(handle, "cuGraphDestroyNode");
    printf("cuGraphDestroyNode\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphDestroyNode)(hNode));
    dlclose(handle);
}

CUresult cuGraphExecDestroy(CUgraphExec hGraphExec) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphExecDestroy)(CUgraphExec );
    fakecuGraphExecDestroy = dlsym(handle, "cuGraphExecDestroy");
    printf("cuGraphExecDestroy\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphExecDestroy)(hGraphExec));
    dlclose(handle);
}

CUresult cuGraphExecKernelNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_KERNEL_NODE_PARAMS* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphExecKernelNodeSetParams)(CUgraphExec ,CUgraphNode ,const CUDA_KERNEL_NODE_PARAMS* );
    fakecuGraphExecKernelNodeSetParams = dlsym(handle, "cuGraphExecKernelNodeSetParams");
    printf("cuGraphExecKernelNodeSetParams\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphExecKernelNodeSetParams)(hGraphExec, hNode, nodeParams));
    dlclose(handle);
}

CUresult cuGraphGetEdges(CUgraph hGraph, CUgraphNode* from, CUgraphNode* to, size_t* numEdges) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphGetEdges)(CUgraph , CUgraphNode* , CUgraphNode* , size_t* );
    fakecuGraphGetEdges = dlsym(handle, "cuGraphGetEdges");
    printf("cuGraphGetEdges\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphGetEdges)(hGraph,from, to, numEdges));
    dlclose(handle);
}

CUresult cuGraphGetNodes(CUgraph hGraph, CUgraphNode* nodes, size_t* numNodes) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphGetNodes)(CUgraph ,  CUgraphNode* , size_t* );
    fakecuGraphGetNodes = dlsym(handle, "cuGraphGetNodes");
    printf("cuGraphGetNodes\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphGetNodes)(hGraph,nodes, numNodes));
    dlclose(handle);
}

CUresult cuGraphGetRootNodes(CUgraph hGraph, CUgraphNode* rootNodes, size_t* numRootNodes) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphGetRootNodes)(CUgraph ,  CUgraphNode* , size_t* );
    fakecuGraphGetRootNodes = dlsym(handle, "cuGraphGetRootNodes");
    printf("cuGraphGetRootNodes\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphGetRootNodes)(hGraph,rootNodes, numRootNodes));
    dlclose(handle);
}

CUresult cuGraphHostNodeGetParams(CUgraphNode hNode, CUDA_HOST_NODE_PARAMS* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphHostNodeGetParams)( CUgraphNode , CUDA_HOST_NODE_PARAMS* );
    fakecuGraphHostNodeGetParams = dlsym(handle, "cuGraphHostNodeGetParams");
    printf("cuGraphHostNodeGetParams\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphHostNodeGetParams)(hNode, nodeParams));
    dlclose(handle);
}

CUresult cuGraphHostNodeSetParams(CUgraphNode hNode, const CUDA_HOST_NODE_PARAMS* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphHostNodeSetParams)( CUgraphNode , const CUDA_HOST_NODE_PARAMS* );
    fakecuGraphHostNodeSetParams = dlsym(handle, "cuGraphHostNodeSetParams");
    printf("cuGraphHostNodeSetParams\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphHostNodeSetParams)(hNode, nodeParams));
    dlclose(handle);
}

CUresult cuGraphInstantiate(CUgraphExec* phGraphExec, CUgraph hGraph, CUgraphNode* phErrorNode, char* logBuffer, size_t bufferSize) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphInstantiate)(CUgraphExec* , CUgraph , CUgraphNode* , char* , size_t );
    fakecuGraphInstantiate = dlsym(handle, "cuGraphInstantiate");
    printf("cuGraphInstantiate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphInstantiate)(phGraphExec, hGraph, phErrorNode, logBuffer, bufferSize));
    dlclose(handle);
}

CUresult cuGraphKernelNodeGetParams(CUgraphNode hNode, CUDA_KERNEL_NODE_PARAMS* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphKernelNodeGetParams)(CUgraphNode , CUDA_KERNEL_NODE_PARAMS* );
    fakecuGraphKernelNodeGetParams = dlsym(handle, "cuGraphKernelNodeGetParams");
    printf("cuGraphKernelNodeGetParams\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphKernelNodeGetParams)(hNode, nodeParams));
    dlclose(handle);
}

CUresult cuGraphKernelNodeSetParams(CUgraphNode hNode, const CUDA_KERNEL_NODE_PARAMS* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphKernelNodeSetParams)(CUgraphNode , const CUDA_KERNEL_NODE_PARAMS* );
    fakecuGraphKernelNodeSetParams = dlsym(handle, "cuGraphKernelNodeSetParams");
    printf("cuGraphKernelNodeSetParams\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphKernelNodeSetParams)(hNode, nodeParams));
    dlclose(handle);
}

CUresult cuGraphLaunch(CUgraphExec hGraphExec, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphLaunch)(CUgraphExec , CUstream );
    fakecuGraphLaunch = dlsym(handle, "cuGraphLaunch");
    printf("cuGraphLaunch\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphLaunch)(hGraphExec, hStream));
    dlclose(handle);
}

CUresult cuGraphMemcpyNodeGetParams(CUgraphNode hNode, CUDA_MEMCPY3D* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphMemcpyNodeGetParams)(CUgraphNode , CUDA_MEMCPY3D* );
    fakecuGraphMemcpyNodeGetParams = dlsym(handle, "cuGraphMemcpyNodeGetParams");
    printf("cuGraphMemcpyNodeGetParams\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphMemcpyNodeGetParams)(hNode, nodeParams));
    dlclose(handle);
}

CUresult cuGraphMemcpyNodeSetParams(CUgraphNode hNode, const CUDA_MEMCPY3D* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphMemcpyNodeSetParams)(CUgraphNode , const CUDA_MEMCPY3D* );
    fakecuGraphMemcpyNodeSetParams = dlsym(handle, "cuGraphMemcpyNodeSetParams");
    printf("cuGraphMemcpyNodeSetParams\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphMemcpyNodeSetParams)(hNode, nodeParams));
    dlclose(handle);
}

CUresult cuGraphMemsetNodeGetParams(CUgraphNode hNode, CUDA_MEMSET_NODE_PARAMS* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphMemsetNodeGetParams)(CUgraphNode , CUDA_MEMSET_NODE_PARAMS* );
    fakecuGraphMemsetNodeGetParams = dlsym(handle, "cuGraphMemsetNodeGetParams");
    printf("cuGraphMemsetNodeGetParams\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphMemsetNodeGetParams)(hNode, nodeParams));
    dlclose(handle);
}

CUresult cuGraphMemsetNodeSetParams(CUgraphNode hNode, const CUDA_MEMSET_NODE_PARAMS* nodeParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphMemsetNodeSetParams)(CUgraphNode , const CUDA_MEMSET_NODE_PARAMS* );
    fakecuGraphMemsetNodeSetParams = dlsym(handle, "cuGraphMemsetNodeSetParams");
    printf("cuGraphMemsetNodeSetParams\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphMemsetNodeSetParams)(hNode, nodeParams));
    dlclose(handle);
}

CUresult cuGraphNodeFindInClone( CUgraphNode* phNode, CUgraphNode hOriginalNode, CUgraph hClonedGraph) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphNodeFindInClone)( CUgraphNode* , CUgraphNode , CUgraph );
    fakecuGraphNodeFindInClone = dlsym(handle, "cuGraphNodeFindInClone");
    printf("cuGraphNodeFindInClone\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphNodeFindInClone)(phNode, hOriginalNode, hClonedGraph));
    dlclose(handle);
}

CUresult cuGraphNodeGetDependencies(CUgraphNode hNode, CUgraphNode* dependencies, size_t* numDependencies) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphNodeGetDependencies)(CUgraphNode , CUgraphNode* , size_t* );
    fakecuGraphNodeGetDependencies = dlsym(handle, "cuGraphNodeGetDependencies");
    printf("cuGraphNodeGetDependencies\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphNodeGetDependencies)(hNode, dependencies, numDependencies));
    dlclose(handle);
}

CUresult cuGraphNodeGetDependentNodes(CUgraphNode hNode, CUgraphNode* dependentNodes, size_t* numDependentNodes) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphNodeGetDependentNodes)(CUgraphNode , CUgraphNode* , size_t* );
    fakecuGraphNodeGetDependentNodes = dlsym(handle, "cuGraphNodeGetDependentNodes");
    printf("cuGraphNodeGetDependentNodes\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphNodeGetDependentNodes)(hNode, dependentNodes, numDependentNodes));
    dlclose(handle);
}

CUresult cuGraphNodeGetType(CUgraphNode hNode, CUgraphNodeType* type) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphNodeGetType)( CUgraphNode , CUgraphNodeType* );
    fakecuGraphNodeGetType = dlsym(handle, "cuGraphNodeGetType");
    printf("cuGraphNodeGetType\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphNodeGetType)(hNode, type));
    dlclose(handle);
}

CUresult cuGraphRemoveDependencies(CUgraph hGraph, CUgraphNode* from, CUgraphNode* to, size_t numDependencies) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphRemoveDependencies)(CUgraph , CUgraphNode* , CUgraphNode* , size_t );
    fakecuGraphRemoveDependencies = dlsym(handle, "cuGraphRemoveDependencies");
    printf("cuGraphRemoveDependencies\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphRemoveDependencies)(hGraph, from, to, numDependencies));
    dlclose(handle);
}

CUresult cuDeviceCanAccessPeer( int* canAccessPeer, CUdevice dev, CUdevice peerDev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceCanAccessPeer)(int*, CUdevice, CUdevice);
    fakecuDeviceCanAccessPeer = dlsym(handle, "cuDeviceCanAccessPeer");
    printf("cuDeviceCanAccessPeer\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceCanAccessPeer)(canAccessPeer, dev, peerDev));
    dlclose(handle);
}

CUresult cuDeviceGetP2PAttribute( int* value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceGetP2PAttribute)(int*, CUdevice_P2PAttribute , CUdevice, CUdevice);
    fakecuDeviceGetP2PAttribute = dlsym(handle, "cuDeviceGetP2PAttribute");
    printf("cuDeviceGetP2PAttribute\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetP2PAttribute)(value, attrib,srcDevice,dstDevice));
    dlclose(handle);
}

CUresult cuFuncGetAttribute(int* pi, CUfunction_attribute attrib, CUfunction hfunc) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuFuncGetAttribute)(int*, CUfunction_attribute, CUfunction);
    fakecuFuncGetAttribute = dlsym(handle, "cuFuncGetAttribute");
    printf("cuFuncGetAttribute\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuFuncGetAttribute)(pi, attrib, hfunc));
    dlclose(handle);
}

CUresult cuGraphicsMapResources(unsigned int count, CUgraphicsResource* resources, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsMapResources)(unsigned int , CUgraphicsResource* , CUstream );
    fakecuGraphicsMapResources = dlsym(handle, "cuGraphicsMapResources");
    printf("cuGraphicsMapResources\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsMapResources)(count, resources,hStream));
    dlclose(handle);
}

CUresult cuGraphicsResourceGetMappedMipmappedArray(CUmipmappedArray* pMipmappedArray, CUgraphicsResource resource) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsResourceGetMappedMipmappedArray)(CUmipmappedArray* , CUgraphicsResource );
    fakecuGraphicsResourceGetMappedMipmappedArray = dlsym(handle, "cuGraphicsResourceGetMappedMipmappedArray");
    printf("cuGraphicsResourceGetMappedMipmappedArray\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsResourceGetMappedMipmappedArray)(pMipmappedArray, resource));
    dlclose(handle);
}

CUresult cuGraphicsResourceGetMappedPointer(CUdeviceptr* pDevPtr, size_t* pSize, CUgraphicsResource resource) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsResourceGetMappedPointer)( CUdeviceptr* , size_t* , CUgraphicsResource);
    fakecuGraphicsResourceGetMappedPointer = dlsym(handle, "cuGraphicsResourceGetMappedPointer");
    printf("cuGraphicsResourceGetMappedPointer\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsResourceGetMappedPointer)(pDevPtr, pSize, resource));
    dlclose(handle);
}

CUresult cuGraphicsResourceSetMapFlags(CUgraphicsResource resource, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsResourceSetMapFlags)(CUgraphicsResource , unsigned int);
    fakecuGraphicsResourceSetMapFlags = dlsym(handle, "cuGraphicsResourceSetMapFlags");
    printf("cuGraphicsResourceSetMapFlags\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsResourceSetMapFlags)(resource, flags));
    dlclose(handle);
}

CUresult cuGraphicsSubResourceGetMappedArray(CUarray* pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsSubResourceGetMappedArray)(CUarray* , CUgraphicsResource , unsigned int , unsigned int );
    fakecuGraphicsSubResourceGetMappedArray = dlsym(handle, "cuGraphicsSubResourceGetMappedArray");
    printf("cuGraphicsSubResourceGetMappedArray\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsSubResourceGetMappedArray)(pArray,resource, arrayIndex, mipLevel));
    dlclose(handle);
}

CUresult cuGraphicsUnmapResources(unsigned int count, CUgraphicsResource* resources, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsUnmapResources)(unsigned int, CUgraphicsResource* , CUstream );
    fakecuGraphicsUnmapResources = dlsym(handle, "cuGraphicsUnmapResources");
    printf("cuGraphicsUnmapResources\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsUnmapResources)(count, resources, hStream));
    dlclose(handle);
}

CUresult cuGraphicsUnregisterResource(CUgraphicsResource resource) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsUnregisterResource)(CUgraphicsResource );
    fakecuGraphicsUnregisterResource = dlsym(handle, "cuGraphicsUnregisterResource");
    printf("cuGraphicsUnregisterResource\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsUnregisterResource)(resource));
    dlclose(handle);
}

CUresult cuProfilerInitialize(const char* configFile, const char* outputFile ) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuProfilerInitialize)(const char* , const char* );
    fakecuProfilerInitialize = dlsym(handle, "cuProfilerInitialize");
    printf("cuProfilerInitialize\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuProfilerInitialize)(configFile, outputFile));
    dlclose(handle);
}

CUresult cuProfilerStart(void) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuProfilerStart)(void);
    fakecuProfilerStart = dlsym(handle, "cuProfilerStart");
    printf("cuProfilerStart\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuProfilerStart)());
    dlclose(handle);
}

CUresult cuProfilerStop(void) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuProfilerStop)(void);
    fakecuProfilerStop = dlsym(handle, "cuProfilerStop");
    printf("cuProfilerStop\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuProfilerStop)());
    dlclose(handle);
}

CUresult cuFuncSetAttribute(CUfunction hfunc, CUfunction_attribute attrib, int value) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuFuncSetAttribute)(CUfunction , CUfunction_attribute , int );
    fakecuFuncSetAttribute = dlsym(handle, "cuFuncSetAttribute");
    printf("cuFuncSetAttribute\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuFuncSetAttribute)(hfunc, attrib, value));
    dlclose(handle);
}

CUresult cuStreamQuery(CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamQuery)(CUstream);
    fakecuStreamQuery = dlsym(handle, "cuStreamQuery");
    printf("cuStreamQuery\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamQuery)(hStream));
    dlclose(handle);
}

CUresult cuDevicePrimaryCtxGetState(CUdevice dev, unsigned int* flags, int* active) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDevicePrimaryCtxGetState)(CUdevice, unsigned int *, int *);
    fakecuDevicePrimaryCtxGetState = dlsym(handle, "cuDevicePrimaryCtxGetState");
    printf("cuDevicePrimaryCtxGetState\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDevicePrimaryCtxGetState)(dev, flags, active));
    dlclose(handle);
}

CUresult cuCtxSetCurrent(CUcontext ctx) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxSetCurrent)(CUcontext);
    fakecuCtxSetCurrent = dlsym(handle, "cuCtxSetCurrent");
    printf("cuCtxSetCurrent\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxSetCurrent)(ctx));
    dlclose(handle);
}

CUresult cuCtxSetLimit(CUlimit limit, size_t value) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxSetLimit)(CUlimit , size_t );
    fakecuCtxSetLimit = dlsym(handle, "cuCtxSetLimit");
    printf("cuCtxSetLimit\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxSetLimit)(limit, value));
    dlclose(handle);
}

CUresult cuStreamWaitEvent(CUstream hStream, CUevent hEvent, unsigned int Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamWaitEvent)(CUstream, CUevent, unsigned int);
    fakecuStreamWaitEvent = dlsym(handle, "cuStreamWaitEvent");
    printf("cuStreamWaitEvent\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamWaitEvent)(hStream, hEvent, Flags));
    dlclose(handle);
}

/*CUresult cuThreadExchangeStreamCaptureMode(CUstreamCaptureMode* mode) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuThreadExchangeStreamCaptureMode)(CUstreamCaptureMode* );
    fakecuThreadExchangeStreamCaptureMode = dlsym(handle, "cuThreadExchangeStreamCaptureMode");
    printf("cuThreadExchangeStreamCaptureMode\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuThreadExchangeStreamCaptureMode)(mode));
    dlclose(handle);
}*/

CUresult cuMemsetD32_v2(CUdeviceptr dstDevice, unsigned int ui, size_t N) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD32_v2)(CUdeviceptr, unsigned int, size_t);
    fakecuMemsetD32_v2 = dlsym(handle, "cuMemsetD32_v2");
    printf("cuMemsetD32_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD32_v2)(dstDevice, ui, N));
    dlclose(handle);
}

CUresult cuMemAllocManaged(CUdeviceptr* dptr, size_t bytesize, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemAllocManaged)(CUdeviceptr*, size_t, unsigned int);
    fakecuMemAllocManaged = dlsym(handle, "cuMemAllocManaged");
    printf("cuMemAllocManaged\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemAllocManaged)(dptr, bytesize, flags));
    dlclose(handle);
}

CUresult cuCtxGetSharedMemConfig(CUsharedconfig* pConfig) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxGetSharedMemConfig)(CUsharedconfig *);
    fakecuCtxGetSharedMemConfig = dlsym(handle, "cuCtxGetSharedMemConfig");
    printf("cuCtxGetSharedMemConfig\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetSharedMemConfig)(pConfig));
    dlclose(handle);
}

CUresult cuCtxGetStreamPriorityRange(int* leastPriority, int* greatestPriority) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxGetStreamPriorityRange)(int* , int* );
    fakecuCtxGetStreamPriorityRange = dlsym(handle, "cuCtxGetStreamPriorityRange");
    printf("cuCtxGetStreamPriorityRange\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetStreamPriorityRange)(leastPriority, greatestPriority));
    dlclose(handle);
}

CUresult cuCtxPopCurrent(CUcontext* pctx) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxPopCurrent)(CUcontext* );
    fakecuCtxPopCurrent = dlsym(handle, "cuCtxPopCurrent");
    printf("cuCtxPopCurrent\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxPopCurrent)(pctx));
    dlclose(handle);
}

CUresult cuFuncSetCacheConfig(CUfunction hfunc, CUfunc_cache config) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuFuncSetCacheConfig)(CUfunction, CUfunc_cache);
    fakecuFuncSetCacheConfig = dlsym(handle, "cuFuncSetCacheConfig");
    printf("cuFuncSetCacheConfig\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuFuncSetCacheConfig)(hfunc, config));
    dlclose(handle);
}

CUresult cuFuncSetSharedMemConfig(CUfunction hfunc, CUsharedconfig config) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuFuncSetSharedMemConfig)(CUfunction, CUsharedconfig);
    fakecuFuncSetSharedMemConfig = dlsym(handle, "cuFuncSetSharedMemConfig");
    printf("cuFuncSetSharedMemConfig\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuFuncSetSharedMemConfig)(hfunc, config));
    dlclose(handle);
}

CUresult cuLaunchCooperativeKernelMultiDevice(CUDA_LAUNCH_PARAMS* launchParamsList, unsigned int numDevices, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuLaunchCooperativeKernelMultiDevice)(CUDA_LAUNCH_PARAMS* , unsigned int, unsigned int);
    fakecuLaunchCooperativeKernelMultiDevice = dlsym(handle, "cuLaunchCooperativeKernelMultiDevice");
    printf("cuLaunchCooperativeKernelMultiDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuLaunchCooperativeKernelMultiDevice)(launchParamsList, numDevices, flags));
    dlclose(handle);
}

CUresult cuLaunchHostFunc(CUstream hStream, CUhostFn fn, void* userData) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuLaunchHostFunc)(CUstream , CUhostFn , void* );
    fakecuLaunchHostFunc = dlsym(handle, "cuLaunchHostFunc");
    printf("cuLaunchHostFunc\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuLaunchHostFunc)(hStream, fn, userData));
    dlclose(handle);
}

CUresult cuLaunchCooperativeKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void** kernelParams) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuLaunchCooperativeKernel)( CUfunction , unsigned int , unsigned int , unsigned int, unsigned int, unsigned int , unsigned int , unsigned int, CUstream , void** );
    fakecuLaunchCooperativeKernel = dlsym(handle, "cuLaunchCooperativeKernel");
    printf("cuLaunchCooperativeKernel\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuLaunchCooperativeKernel)(f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream, kernelParams));
    dlclose(handle);
}

CUresult cuStreamCreate(CUstream* phStream, unsigned int Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamCreate)(CUstream *, unsigned int);
    fakecuStreamCreate = dlsym(handle, "cuStreamCreate");
    printf("cuStreamCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamCreate)(phStream, Flags));
    dlclose(handle);
}

CUresult cuStreamCreateWithPriority(CUstream* phStream, unsigned int flags, int priority) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamCreateWithPriority)(CUstream *, unsigned int, int );
    fakecuStreamCreateWithPriority = dlsym(handle, "cuStreamCreateWithPriority");
    printf("cuStreamCreateWithPriority\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamCreateWithPriority)(phStream, flags, priority));
    dlclose(handle);
}

CUresult cuCtxGetDevice(CUdevice* device) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxGetDevice)(CUdevice *);
    fakecuCtxGetDevice = dlsym(handle, "cuCtxGetDevice");
    printf("cuCtxGetDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetDevice)(device));
    dlclose(handle);
}

CUresult cuCtxGetFlags(unsigned int* flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxGetFlags)(unsigned int* );
    fakecuCtxGetFlags = dlsym(handle, "cuCtxGetFlags");
    printf("cuCtxGetFlags\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetFlags)(flags));
    dlclose(handle);
}

CUresult cuCtxGetLimit(size_t* pvalue, CUlimit limit) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxGetLimit)(size_t* , CUlimit );
    fakecuCtxGetLimit = dlsym(handle, "cuCtxGetLimit");
    printf("cuCtxGetLimit\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetLimit)(pvalue, limit));
    dlclose(handle);
}

CUresult cuMemcpyDtoHAsync_v2(void* dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyDtoHAsync_v2)(void *, CUdeviceptr, size_t, CUstream);
    fakecuMemcpyDtoHAsync_v2 = dlsym(handle, "cuMemcpyDtoHAsync_v2");
    printf("cuMemcpyDtoHAsync_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuMemcpyDtoHAsync_v2)(dstHost, srcDevice, ByteCount, hStream));
    dlclose(handle);
    return r;
}

CUresult cuGetErrorName(CUresult error_, const char** pStr) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGetErrorName)(CUresult, const char **);
    fakecuGetErrorName = dlsym(handle, "cuGetErrorName");
    printf("cuGetErrorName\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGetErrorName)(error_, pStr));
    dlclose(handle);
}

CUresult cuDevicePrimaryCtxRelease(CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDevicePrimaryCtxRelease)(CUdevice);
    fakecuDevicePrimaryCtxRelease = dlsym(handle, "cuDevicePrimaryCtxRelease");
    printf("cuDevicePrimaryCtxRelease\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDevicePrimaryCtxRelease)(dev));
    dlclose(handle);
}

CUresult cuDevicePrimaryCtxReset(CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDevicePrimaryCtxReset)(CUdevice);
    fakecuDevicePrimaryCtxReset = dlsym(handle, "cuDevicePrimaryCtxReset");
    printf("cuDevicePrimaryCtxReset\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDevicePrimaryCtxReset)(dev));
    dlclose(handle);
}

CUresult cuMemcpy(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpy)(CUdeviceptr , CUdeviceptr , size_t );
    fakecuMemcpy = dlsym(handle, "cuMemcpy");
    printf("cuMemcpy\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpy)(dst, src, ByteCount));
    dlclose(handle);
}

CUresult cuMemcpy2D(const CUDA_MEMCPY2D* pCopy) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpy2D)(const CUDA_MEMCPY2D* );
    fakecuMemcpy2D = dlsym(handle, "cuMemcpy2D");
    printf("cuMemcpy2D\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpy2D)(pCopy));
    dlclose(handle);
}

CUresult cuMemcpy2DAsync(const CUDA_MEMCPY2D* pCopy, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpy2DAsync)(const CUDA_MEMCPY2D* , CUstream );
    fakecuMemcpy2DAsync = dlsym(handle, "cuMemcpy2DAsync");
    printf("cuMemcpy2DAsync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpy2DAsync)(pCopy, hStream));
    dlclose(handle);
}

CUresult cuMemcpy2DUnaligned(const CUDA_MEMCPY2D* pCopy) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpy2DUnaligned)(const CUDA_MEMCPY2D* );
    fakecuMemcpy2DUnaligned = dlsym(handle, "cuMemcpy2DUnaligned");
    printf("cuMemcpy2DUnaligned\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpy2DUnaligned)(pCopy ));
    dlclose(handle);
}

CUresult cuMemcpy3D(const CUDA_MEMCPY3D* pCopy) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpy3D)(const CUDA_MEMCPY3D* );
    fakecuMemcpy3D = dlsym(handle, "cuMemcpy3D");
    printf("cuMemcpy3D\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpy3D)(pCopy));
    dlclose(handle);
}

CUresult cuMemcpy3DAsync(const CUDA_MEMCPY3D* pCopy, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpy3DAsync)(const CUDA_MEMCPY3D* , CUstream );
    fakecuMemcpy3DAsync = dlsym(handle, "cuMemcpy3DAsync");
    printf("cuMemcpy3DAsync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpy3DAsync)(pCopy, hStream));
    dlclose(handle);
}

CUresult cuMemcpy3DPeer(const CUDA_MEMCPY3D_PEER* pCopy) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpy3DPeer)(const CUDA_MEMCPY3D_PEER* );
    fakecuMemcpy3DPeer = dlsym(handle, "cuMemcpy3DPeer");
    printf("cuMemcpy3DPeer\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpy3DPeer)(pCopy ));
    dlclose(handle);
}

CUresult cuMemcpy3DPeerAsync(const CUDA_MEMCPY3D_PEER* pCopy, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpy3DPeerAsync)(const CUDA_MEMCPY3D_PEER* ,CUstream );
    fakecuMemcpy3DPeerAsync = dlsym(handle, "cuMemcpy3DPeerAsync");
    printf("cuMemcpy3DPeerAsync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpy3DPeerAsync)(pCopy, hStream));
    dlclose(handle);
}

CUresult cuMemcpyAsync(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyAsync)(CUdeviceptr , CUdeviceptr , size_t , CUstream );
    fakecuMemcpyAsync = dlsym(handle, "cuMemcpyAsync");
    printf("cuMemcpyAsync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyAsync)(dst, src, ByteCount,hStream));
    dlclose(handle);
}

CUresult cuMemcpyAtoA(CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyAtoA)(CUarray , size_t , CUarray , size_t , size_t );
    fakecuMemcpyAtoA = dlsym(handle, "cuMemcpyAtoA");
    printf("cuMemcpyAtoA\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyAtoA)(dstArray, dstOffset, srcArray, srcOffset, ByteCount));
    dlclose(handle);
}

CUresult cuMemcpyAtoD(CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyAtoD)(CUdeviceptr , CUarray , size_t , size_t );
    fakecuMemcpyAtoD = dlsym(handle, "cuMemcpyAtoD");
    printf("cuMemcpyAtoD\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyAtoD)(dstDevice, srcArray, srcOffset, ByteCount));
    dlclose(handle);
}

CUresult cuMemcpyAtoH(void* dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyAtoH)(void* , CUarray , size_t , size_t );
    fakecuMemcpyAtoH = dlsym(handle, "cuMemcpyAtoH");
    printf("cuMemcpyAtoH\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyAtoH)(dstHost, srcArray, srcOffset, ByteCount));
    dlclose(handle);
}

CUresult cuMemcpyAtoHAsync(void* dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyAtoHAsync)(void* , CUarray , size_t , size_t , CUstream );
    fakecuMemcpyAtoHAsync = dlsym(handle, "cuMemcpyAtoHAsync");
    printf("cuMemcpyAtoHAsync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyAtoHAsync)(dstHost, srcArray, srcOffset, ByteCount, hStream));
    dlclose(handle);
}

CUresult cuMemcpyDtoA(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyDtoA)(CUarray , size_t , CUdeviceptr , size_t );
    fakecuMemcpyDtoA = dlsym(handle, "cuMemcpyDtoA");
    printf("cuMemcpyDtoA\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyDtoA)(dstArray, dstOffset, srcDevice, ByteCount));
    dlclose(handle);
}

CUresult cuMemcpyHtoA(CUarray dstArray, size_t dstOffset, const void* srcHost, size_t ByteCount) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyHtoA)(CUarray , size_t , const void* , size_t );
    fakecuMemcpyHtoA = dlsym(handle, "cuMemcpyHtoA");
    printf("cuMemcpyHtoA\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyHtoA)(dstArray, dstOffset, srcHost, ByteCount));
    dlclose(handle);
}

CUresult cuMemcpyHtoAAsync_v2(CUarray dstArray, size_t dstOffset, const void* srcHost, size_t ByteCount, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyHtoAAsync_v2)(CUarray , size_t , const void* , size_t , CUstream);
    fakecuMemcpyHtoAAsync_v2 = dlsym(handle, "cuMemcpyHtoAAsync_v2");
    printf("cuMemcpyHtoAAsync_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyHtoAAsync_v2)(dstArray, dstOffset, srcHost, ByteCount, hStream));
    dlclose(handle);
}


CUresult cuMemcpyHtoDAsync_v2(CUdeviceptr dstDevice, const void* srcHost, size_t ByteCount, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyHtoDAsync_v2)(CUdeviceptr, const void*, size_t, CUstream);
    fakecuMemcpyHtoDAsync_v2 = dlsym(handle, "cuMemcpyHtoDAsync_v2");
    printf("cuMemcpyHtoDAsync_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuMemcpyHtoDAsync_v2)(dstDevice, srcHost, ByteCount, hStream));
    dlclose(handle);
    return r;
}

CUresult cuMemcpyDtoD(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyDtoD)(CUdeviceptr, CUdeviceptr, size_t);
    fakecuMemcpyDtoD = dlsym(handle, "cuMemcpyDtoD");
    printf("cuMemcpyDtoD\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyDtoD)(dstDevice, srcDevice, ByteCount));
    dlclose(handle);
}

CUresult cuMemcpyPeer(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyPeer)(CUdeviceptr , CUcontext , CUdeviceptr , CUcontext , size_t );
    fakecuMemcpyPeer = dlsym(handle, "cuMemcpyPeer");
    printf("cuMemcpyPeer\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyPeer)(dstDevice, dstContext, srcDevice, srcContext, ByteCount));
    dlclose(handle);
}

CUresult cuMemcpyPeerAsync(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyPeerAsync)(CUdeviceptr , CUcontext , CUdeviceptr , CUcontext , size_t, CUstream );
    fakecuMemcpyPeerAsync = dlsym(handle, "cuMemcpyPeerAsync");
    printf("cuMemcpyPeerAsync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyPeerAsync)(dstDevice, dstContext, srcDevice, srcContext, ByteCount, hStream));
    dlclose(handle);
}

CUresult cuMemsetD16(CUdeviceptr dstDevice, unsigned short us, size_t N) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD16)(CUdeviceptr ,unsigned short , size_t );
    fakecuMemsetD16 = dlsym(handle, "cuMemsetD16");
    printf("cuMemsetD16\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD16)(dstDevice, us, N));
    dlclose(handle);
}

CUresult cuMemsetD16Async(CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD16Async)(CUdeviceptr ,unsigned short , size_t ,CUstream );
    fakecuMemsetD16Async = dlsym(handle, "cuMemsetD16Async");
    printf("cuMemsetD16Async\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD16Async)(dstDevice, us, N, hStream));
    dlclose(handle);
}

CUresult cuMemsetD2D16(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD2D16)(CUdeviceptr , size_t , unsigned short , size_t ,size_t );
    fakecuMemsetD2D16 = dlsym(handle, "cuMemsetD2D16");
    printf("cuMemsetD2D16\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD2D16)(dstDevice, dstPitch, us, Width , Height));
    dlclose(handle);
}

CUresult cuMemsetD2D16Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD2D16Async)(CUdeviceptr , size_t , unsigned short , size_t ,size_t ,CUstream );
    fakecuMemsetD2D16Async = dlsym(handle, "cuMemsetD2D16Async");
    printf("cuMemsetD2D16Async\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD2D16Async)(dstDevice, dstPitch, us, Width , Height, hStream));
    dlclose(handle);
}

CUresult cuMemsetD2D32(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD2D32)(CUdeviceptr , size_t , unsigned int , size_t ,size_t );
    fakecuMemsetD2D32 = dlsym(handle, "cuMemsetD2D32");
    printf("cuMemsetD2D32\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD2D32)(dstDevice, dstPitch, ui, Width , Height));
    dlclose(handle);
}

CUresult cuMemsetD2D32Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD2D32Async)(CUdeviceptr , size_t , unsigned int , size_t ,size_t ,CUstream );
    fakecuMemsetD2D32Async = dlsym(handle, "cuMemsetD2D32Async");
    printf("cuMemsetD2D32Async\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD2D32Async)(dstDevice, dstPitch, ui, Width , Height, hStream));
    dlclose(handle);
}

CUresult cuMemsetD2D8(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD2D8)(CUdeviceptr , size_t , unsigned char , size_t ,size_t );
    fakecuMemsetD2D8 = dlsym(handle, "cuMemsetD2D8");
    printf("cuMemsetD2D8\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD2D8)(dstDevice, dstPitch, uc, Width , Height));
    dlclose(handle);
}

CUresult cuMemsetD2D8Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD2D8Async)(CUdeviceptr , size_t , unsigned char , size_t ,size_t , CUstream );
    fakecuMemsetD2D8Async = dlsym(handle, "cuMemsetD2D8Async");
    printf("cuMemsetD2D8Async\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD2D8Async)(dstDevice, dstPitch, uc, Width , Height, hStream));
    dlclose(handle);
}

CUresult cuOccupancyMaxPotentialBlockSize(int* minGridSize, int* blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int  blockSizeLimit) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuOccupancyMaxPotentialBlockSize)(int *, int *, CUfunction, CUoccupancyB2DSize, size_t, int);
    fakecuOccupancyMaxPotentialBlockSize = dlsym(handle, "cuOccupancyMaxPotentialBlockSize");
    printf("cuOccupancyMaxPotentialBlockSize\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuOccupancyMaxPotentialBlockSize)(minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit));
    dlclose(handle);
}

CUresult cuOccupancyMaxPotentialBlockSizeWithFlags(int* minGridSize, int* blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int  blockSizeLimit, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuOccupancyMaxPotentialBlockSizeWithFlags)(int *, int *, CUfunction, CUoccupancyB2DSize, size_t, int,unsigned int);
    fakecuOccupancyMaxPotentialBlockSizeWithFlags = dlsym(handle, "cuOccupancyMaxPotentialBlockSizeWithFlags");
    printf("cuOccupancyMaxPotentialBlockSizeWithFlags\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuOccupancyMaxPotentialBlockSizeWithFlags)(minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit,flags));
    dlclose(handle);
}

CUresult cuDevicePrimaryCtxRetain(CUcontext* pctx, CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDevicePrimaryCtxRetain)(CUcontext *, CUdevice);
    fakecuDevicePrimaryCtxRetain = dlsym(handle, "cuDevicePrimaryCtxRetain");
    printf("cuDevicePrimaryCtxRetain\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDevicePrimaryCtxRetain)(pctx, dev));
    dlclose(handle);
}

CUresult cuTexObjectCreate(CUtexObject* pTexObject, const CUDA_RESOURCE_DESC* pResDesc, const CUDA_TEXTURE_DESC* pTexDesc, const CUDA_RESOURCE_VIEW_DESC* pResViewDesc) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuTexObjectCreate)(CUtexObject* , const CUDA_RESOURCE_DESC* , const CUDA_TEXTURE_DESC* , const CUDA_RESOURCE_VIEW_DESC* );
    fakecuTexObjectCreate = dlsym(handle, "cuTexObjectCreate");
    printf("cuTexObjectCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuTexObjectCreate)(pTexObject,pResDesc, pTexDesc, pResViewDesc));
    dlclose(handle);
}

CUresult cuTexObjectDestroy(CUtexObject texObject) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuTexObjectDestroy)(CUtexObject );
    fakecuTexObjectDestroy = dlsym(handle, "cuTexObjectDestroy");
    printf("cuTexObjectDestroy\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuTexObjectDestroy)(texObject));
    dlclose(handle);
}

CUresult cuTexObjectGetResourceDesc(CUDA_RESOURCE_DESC* pResDesc, CUtexObject texObject) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuTexObjectGetResourceDesc)(CUDA_RESOURCE_DESC* , CUtexObject );
    fakecuTexObjectGetResourceDesc = dlsym(handle, "cuTexObjectGetResourceDesc");
    printf("cuTexObjectGetResourceDesc\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuTexObjectGetResourceDesc)(pResDesc, texObject));
    dlclose(handle);
}

CUresult cuTexObjectGetResourceViewDesc(CUDA_RESOURCE_VIEW_DESC* pResViewDesc, CUtexObject texObject) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuTexObjectGetResourceViewDesc)(CUDA_RESOURCE_VIEW_DESC* , CUtexObject );
    fakecuTexObjectGetResourceViewDesc = dlsym(handle, "cuTexObjectGetResourceViewDesc");
    printf("cuTexObjectGetResourceViewDesc\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuTexObjectGetResourceViewDesc)(pResViewDesc, texObject));
    dlclose(handle);
}

CUresult cuTexObjectGetTextureDesc(CUDA_TEXTURE_DESC* pTexDesc, CUtexObject texObject) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuTexObjectGetTextureDesc)(CUDA_TEXTURE_DESC* , CUtexObject );
    fakecuTexObjectGetTextureDesc = dlsym(handle, "cuTexObjectGetTextureDesc");
    printf("cuTexObjectGetTextureDesc\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuTexObjectGetTextureDesc)(pTexDesc, texObject));
    dlclose(handle);
}

CUresult cuSurfObjectCreate(CUsurfObject* pSurfObject, const CUDA_RESOURCE_DESC* pResDesc) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuSurfObjectCreate)(CUsurfObject* , const CUDA_RESOURCE_DESC* );
    fakecuSurfObjectCreate = dlsym(handle, "cuSurfObjectCreate");
    printf("cuSurfObjectCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuSurfObjectCreate)(pSurfObject, pResDesc));
    dlclose(handle);
}

CUresult cuSurfObjectDestroy( CUsurfObject surfObject) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuSurfObjectDestroy)(CUsurfObject );
    fakecuSurfObjectDestroy = dlsym(handle, "cuSurfObjectDestroy");
    printf("cuSurfObjectDestroy\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuSurfObjectDestroy)(surfObject));
    dlclose(handle);
}

CUresult cuSurfObjectGetResourceDesc(CUDA_RESOURCE_DESC* pResDesc, CUsurfObject surfObject) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuSurfObjectGetResourceDesc)(CUDA_RESOURCE_DESC* , CUsurfObject );
    fakecuSurfObjectGetResourceDesc = dlsym(handle, "cuSurfObjectGetResourceDesc");
    printf("cuSurfObjectGetResourceDesc\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuSurfObjectGetResourceDesc)(pResDesc, surfObject));
    dlclose(handle);
}

CUresult cuCtxDisablePeerAccess(CUcontext peerContext) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxDisablePeerAccess)(CUcontext );
    fakecuCtxDisablePeerAccess = dlsym(handle, "cuCtxDisablePeerAccess");
    printf("cuCtxDisablePeerAccess\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxDisablePeerAccess)(peerContext));
    dlclose(handle);
}

CUresult cuGetErrorString(CUresult error_, const char** pStr) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGetErrorString)(CUresult, const char **);
    fakecuGetErrorString = dlsym(handle, "cuGetErrorString");
    printf("cuGetErrorString\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGetErrorString)(error_, pStr));
    dlclose(handle);
}

CUresult cuDeviceGetPCIBusId(char* pciBusId, int len, CUdevice dev) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDeviceGetPCIBusId)(char *, int, CUdevice);
    fakecuDeviceGetPCIBusId = dlsym(handle, "cuDeviceGetPCIBusId");
    printf("cuDeviceGetPCIBusId\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetPCIBusId)(pciBusId, len, dev));
    dlclose(handle);
}

CUresult cuIpcCloseMemHandle(CUdeviceptr dptr) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuIpcCloseMemHandle)(CUdeviceptr );
    fakecuIpcCloseMemHandle = dlsym(handle, "cuIpcCloseMemHandle");
    printf("cuIpcCloseMemHandle\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuIpcCloseMemHandle)(dptr));
    dlclose(handle);
}

CUresult cuIpcGetEventHandle(CUipcEventHandle* pHandle, CUevent event) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuIpcGetEventHandle)(CUipcEventHandle* , CUevent );
    fakecuIpcGetEventHandle = dlsym(handle, "cuIpcGetEventHandle");
    printf("cuIpcGetEventHandle\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuIpcGetEventHandle)(pHandle, event));
    dlclose(handle);
}

CUresult cuIpcGetMemHandle(CUipcMemHandle* pHandle, CUdeviceptr dptr) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuIpcGetMemHandle)(CUipcMemHandle* , CUdeviceptr );
    fakecuIpcGetMemHandle = dlsym(handle, "cuIpcGetMemHandle");
    printf("cuIpcGetMemHandle\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuIpcGetMemHandle)(pHandle, dptr));
    dlclose(handle);
}

CUresult cuIpcOpenEventHandle(CUevent* phEvent, CUipcEventHandle handle) {
    char *error;
    void *hand;
    hand = dlopen (LIB_STRING, RTLD_LAZY);
    if (!hand) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuIpcOpenEventHandle)(CUevent* , CUipcEventHandle );
    fakecuIpcOpenEventHandle = dlsym(hand, "cuIpcOpenEventHandle");
    printf("cuIpcOpenEventHandle\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuIpcOpenEventHandle)(phEvent, handle));
    dlclose(hand);
}

CUresult cuIpcOpenMemHandle(CUdeviceptr* pdptr, CUipcMemHandle handle, unsigned int Flags) {
    char *error;
    void *hand;
    hand = dlopen (LIB_STRING, RTLD_LAZY);
    if (!hand) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuIpcOpenMemHandle)(CUdeviceptr* , CUipcMemHandle , unsigned int );
    fakecuIpcOpenMemHandle = dlsym(hand, "cuIpcOpenMemHandle");
    printf("cuIpcOpenMemHandle\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuIpcOpenMemHandle)(pdptr, handle, Flags));
    dlclose(hand);
}

CUresult cuPointerGetAttribute(void* data, CUpointer_attribute attribute, CUdeviceptr ptr) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuPointerGetAttribute)(void*, CUpointer_attribute, CUdeviceptr);
    fakecuPointerGetAttribute = dlsym(handle, "cuPointerGetAttribute");
    printf("cuPointerGetAttribute\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuPointerGetAttribute)(data, attribute, ptr));
    dlclose(handle);
}

CUresult cuPointerGetAttributes(unsigned int numAttributes, CUpointer_attribute* attributes, void** data, CUdeviceptr ptr) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuPointerGetAttributes)(unsigned int , CUpointer_attribute* , void** , CUdeviceptr );
    fakecuPointerGetAttributes = dlsym(handle, "cuPointerGetAttributes");
    printf("cuPointerGetAttributes\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuPointerGetAttributes)(numAttributes, attributes, data, ptr));
    dlclose(handle);
}

CUresult cuPointerSetAttribute(const void* value, CUpointer_attribute attribute, CUdeviceptr ptr) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuPointerSetAttribute)(const void* , CUpointer_attribute , CUdeviceptr );
    fakecuPointerSetAttribute = dlsym(handle, "cuPointerSetAttribute");
    printf("cuPointerSetAttribute\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuPointerSetAttribute)(value, attribute, ptr));
    dlclose(handle);
}

CUresult cuMemsetD8_v2(CUdeviceptr dstDevice, unsigned char uc, size_t N) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD8_v2)(CUdeviceptr, unsigned char, size_t);
    fakecuMemsetD8_v2 = dlsym(handle, "cuMemsetD8_v2");
    printf("cuMemsetD8_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD8_v2)(dstDevice, uc, N));
    dlclose(handle);
}

CUresult cuDevicePrimaryCtxSetFlags(CUdevice dev, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuDevicePrimaryCtxSetFlags)(CUdevice, unsigned int);
    fakecuDevicePrimaryCtxSetFlags = dlsym(handle, "cuDevicePrimaryCtxSetFlags");
    printf("cuDevicePrimaryCtxSetFlags\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDevicePrimaryCtxSetFlags)(dev, flags));
    dlclose(handle);
}

CUresult cuMemcpyDtoDAsync_v2(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyDtoDAsync_v2)(CUdeviceptr, CUdeviceptr, size_t, CUstream);
    fakecuMemcpyDtoDAsync_v2 = dlsym(handle, "cuMemcpyDtoDAsync_v2");
    printf("cuMemcpyDtoDAsync_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyDtoDAsync_v2)(dstDevice, srcDevice, ByteCount, hStream));
    dlclose(handle);
}

CUresult cuOccupancyMaxActiveBlocksPerMultiprocessor(int* numBlocks, CUfunction func, int  blockSize, size_t dynamicSMemSize) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuOccupancyMaxActiveBlocksPerMultiprocessor)( int* , CUfunction , int, size_t );
    fakecuOccupancyMaxActiveBlocksPerMultiprocessor = dlsym(handle, "cuOccupancyMaxActiveBlocksPerMultiprocessor");
    printf("cuOccupancyMaxActiveBlocksPerMultiprocessor\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuOccupancyMaxActiveBlocksPerMultiprocessor)( numBlocks,  func, blockSize,  dynamicSMemSize));
    dlclose(handle);
}

CUresult cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int* numBlocks, CUfunction func, int  blockSize, size_t dynamicSMemSize, unsigned int  flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)( int* , CUfunction , int, size_t ,unsigned int);
    fakecuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags = dlsym(handle, "cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags");
    printf("cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)( numBlocks,  func, blockSize,  dynamicSMemSize,flags));
    dlclose(handle);
}

CUresult cuStreamDestroy_v2(CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamDestroy_v2)(CUstream );
    fakecuStreamDestroy_v2 = dlsym(handle, "cuStreamDestroy_v2");
    printf("cuStreamDestroy_v2\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamDestroy_v2)(hStream));
    dlclose(handle);
}

CUresult cuStreamEndCapture(CUstream hStream, CUgraph* phGraph) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamEndCapture)(CUstream , CUgraph* );
    fakecuStreamEndCapture = dlsym(handle, "cuStreamEndCapture");
    printf("cuStreamEndCapture\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamEndCapture)(hStream, phGraph));
    dlclose(handle);
}

CUresult cuStreamGetCaptureInfo(CUstream hStream, CUstreamCaptureStatus* captureStatus, cuuint64_t* id) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamGetCaptureInfo)(CUstream , CUstreamCaptureStatus* , cuuint64_t* );
    fakecuStreamGetCaptureInfo = dlsym(handle, "cuStreamGetCaptureInfo");
    printf("cuStreamGetCaptureInfo\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamGetCaptureInfo)(hStream, captureStatus, id));
    dlclose(handle);
}

CUresult cuStreamGetCtx(CUstream hStream, CUcontext* pctx) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamGetCtx)(CUstream , CUcontext*  );
    fakecuStreamGetCtx = dlsym(handle, "cuStreamGetCtx");
    printf("cuStreamGetCtx\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamGetCtx)(hStream, pctx));
    dlclose(handle);
}

CUresult cuStreamGetFlags(CUstream hStream, unsigned int* flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamGetFlags)(CUstream , unsigned int*  );
    fakecuStreamGetFlags = dlsym(handle, "cuStreamGetFlags");
    printf("cuStreamGetFlags\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamGetFlags)(hStream, flags));
    dlclose(handle);
}

CUresult cuStreamGetPriority(CUstream hStream, int* priority) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamGetPriority)(CUstream , int*  );
    fakecuStreamGetPriority = dlsym(handle, "cuStreamGetPriority");
    printf("cuStreamGetPriority\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamGetPriority)(hStream, priority));
    dlclose(handle);
}

CUresult cuStreamIsCapturing(CUstream hStream, CUstreamCaptureStatus* captureStatus) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuStreamIsCapturing)(CUstream , CUstreamCaptureStatus*  );
    fakecuStreamIsCapturing = dlsym(handle, "cuStreamIsCapturing");
    printf("cuStreamIsCapturing\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamIsCapturing)(hStream, captureStatus));
    dlclose(handle);
}

CUresult cuCtxSetSharedMemConfig(CUsharedconfig config) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxSetSharedMemConfig)(CUsharedconfig );
    fakecuCtxSetSharedMemConfig = dlsym(handle, "cuCtxSetSharedMemConfig");
    printf("cuCtxSetSharedMemConfig\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxSetSharedMemConfig)(config));
    dlclose(handle);
}

CUresult cuMemsetD8Async(CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemsetD8Async)(CUdeviceptr, unsigned char, size_t , CUstream);
    fakecuMemsetD8Async = dlsym(handle, "cuMemsetD8Async");
    printf("cuMemsetD8Async\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD8Async)( dstDevice, uc, N, hStream));
    dlclose(handle);
}

CUresult cuMipmappedArrayCreate(CUmipmappedArray* pHandle, const CUDA_ARRAY3D_DESCRIPTOR* pMipmappedArrayDesc, unsigned int  numMipmapLevels) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMipmappedArrayCreate)(CUmipmappedArray* , const CUDA_ARRAY3D_DESCRIPTOR* , unsigned int );
    fakecuMipmappedArrayCreate = dlsym(handle, "cuMipmappedArrayCreate");
    printf("cuMipmappedArrayCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMipmappedArrayCreate)( pHandle, pMipmappedArrayDesc, numMipmapLevels));
    dlclose(handle);
}

CUresult cuMipmappedArrayDestroy(CUmipmappedArray hMipmappedArray) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMipmappedArrayDestroy)(CUmipmappedArray );
    fakecuMipmappedArrayDestroy = dlsym(handle, "cuMipmappedArrayDestroy");
    printf("cuMipmappedArrayDestroy\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMipmappedArrayDestroy)( hMipmappedArray));
    dlclose(handle);
}

CUresult cuMipmappedArrayGetLevel(CUarray* pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMipmappedArrayGetLevel)(CUarray* , CUmipmappedArray , unsigned int );
    fakecuMipmappedArrayGetLevel = dlsym(handle, "cuMipmappedArrayGetLevel");
    printf("cuMipmappedArrayGetLevel\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMipmappedArrayGetLevel)( pLevelArray, hMipmappedArray, level));
    dlclose(handle);
}

CUresult cuMemAdvise(CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemAdvise)(CUdeviceptr , size_t , CUmem_advise , CUdevice );
    fakecuMemAdvise = dlsym(handle, "cuMemAdvise");
    printf("cuMemAdvise\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemAdvise)( devPtr, count, advice, device));
    dlclose(handle);
}

CUresult cuMemPrefetchAsync(CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemPrefetchAsync)(CUdeviceptr , size_t , CUdevice ,CUstream );
    fakecuMemPrefetchAsync = dlsym(handle, "cuMemPrefetchAsync");
    printf("cuMemPrefetchAsync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemPrefetchAsync)( devPtr, count, dstDevice, hStream));
    dlclose(handle);
}

CUresult cuMemRangeGetAttribute(void* data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemRangeGetAttribute)(void* , size_t , CUmem_range_attribute , CUdeviceptr , size_t );
    fakecuMemRangeGetAttribute = dlsym(handle, "cuMemRangeGetAttribute");
    printf("cuMemRangeGetAttribute\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemRangeGetAttribute)( data, dataSize, attribute, devPtr, count));
    dlclose(handle);
}

CUresult cuMemRangeGetAttributes(void** data, size_t* dataSizes, CUmem_range_attribute* attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemRangeGetAttributes)(void** , size_t* , CUmem_range_attribute* , size_t , CUdeviceptr , size_t );
    fakecuMemRangeGetAttributes = dlsym(handle, "cuMemRangeGetAttributes");
    printf("cuMemRangeGetAttributes\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemRangeGetAttributes)( data, dataSizes, attributes, numAttributes, devPtr, count));
    dlclose(handle);
}

/*
CUresult cuGLGetDevices(unsigned int* pCudaDeviceCount, CUdevice* pCudaDevices, unsigned int cudaDeviceCount, CUGLDeviceList deviceList) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGLGetDevices)(unsigned int* , CUdevice* , unsigned int , CUGLDeviceList );
    fakecuGLGetDevices = dlsym(handle, "cuGLGetDevices");
    printf("cuGLGetDevices\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGLGetDevices)( pCudaDeviceCount, pCudaDevices, cudaDeviceCount, deviceList));
    dlclose(handle);
}

CUresult cuGraphicsGLRegisterBuffer(CUgraphicsResource* pCudaResource, GLuint buffer, unsigned int Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsGLRegisterBuffer)(CUgraphicsResource* , GLuint , unsigned int );
    fakecuGraphicsGLRegisterBuffer = dlsym(handle, "cuGraphicsGLRegisterBuffer");
    printf("cuGraphicsGLRegisterBuffer\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsGLRegisterBuffer)( pCudaResource, buffer, Flags));
    dlclose(handle);
}

CUresult cuGraphicsGLRegisterImage(CUgraphicsResource* pCudaResource, GLuint image, GLenum target, unsigned int Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsGLRegisterImage)( CUgraphicsResource* , GLuint , GLenum , unsigned int );
    fakecuGraphicsGLRegisterImage = dlsym(handle, "cuGraphicsGLRegisterImage");
    printf("cuGraphicsGLRegisterImage\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsGLRegisterImage)( pCudaResource, image, target, Flags));
    dlclose(handle);
}

CUresult cuWGLGetDevice(CUdevice* pDevice, HGPUNV hGpu) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuWGLGetDevice)(CUdevice* , HGPUNV );
    fakecuWGLGetDevice = dlsym(handle, "cuWGLGetDevice");
    printf("cuWGLGetDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuWGLGetDevice)(pDevice, hGpu));
    dlclose(handle);
}

CUresult cuD3D9CtxCreate(CUcontext* pCtx, CUdevice* pCudaDevice, unsigned int Flags, IDirect3DDevice9* pD3DDevice) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D9CtxCreate)(CUcontext* , CUdevice* , unsigned int , IDirect3DDevice9* );
    fakecuD3D9CtxCreate = dlsym(handle, "cuD3D9CtxCreate");
    printf("cuD3D9CtxCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D9CtxCreate)(pCtx, pCudaDevice, Flags, pD3DDevice));
    dlclose(handle);
}

CUresult cuD3D9CtxCreateOnDevice(CUcontext* pCtx, unsigned int flags, IDirect3DDevice9* pD3DDevice, CUdevice cudaDevice) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D9CtxCreateOnDevice)(CUcontext* ,  unsigned int , IDirect3DDevice9* , CUdevice);
    fakecuD3D9CtxCreateOnDevice = dlsym(handle, "cuD3D9CtxCreateOnDevice");
    printf("cuD3D9CtxCreateOnDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D9CtxCreateOnDevice)(pCtx, Flags, pD3DDevice, cudaDevice));
    dlclose(handle);
}

CUresult cuD3D9GetDevice(CUdevice* pCudaDevice, const char* pszAdapterName) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D9GetDevice)(CUdevice* , const char* );
    fakecuD3D9GetDevice = dlsym(handle, "cuD3D9GetDevice");
    printf("cuD3D9GetDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D9GetDevice)( pCudaDevice,  pszAdapterName));
    dlclose(handle);
}

CUresult cuD3D9GetDevice(CUdevice* pCudaDevice, const char* pszAdapterName) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D9GetDevice)(CUdevice* , const char* );
    fakecuD3D9GetDevice = dlsym(handle, "cuD3D9GetDevice");
    printf("cuD3D9GetDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D9GetDevice)( pCudaDevice,  pszAdapterName));
    dlclose(handle);
}

CUresult cuD3D9GetDevices(unsigned int* pCudaDeviceCount, CUdevice* pCudaDevices, unsigned int  cudaDeviceCount, IDirect3DDevice9* pD3D9Device, CUd3d9DeviceList deviceList) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D9GetDevices)(unsigned int* , CUdevice* , unsigned int , IDirect3DDevice9* , CUd3d9DeviceList );
    fakecuD3D9GetDevices = dlsym(handle, "cuD3D9GetDevices");
    printf("cuD3D9GetDevices\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D9GetDevices)( pCudaDeviceCount,  pCudaDevices, cudaDeviceCount,  pD3D9Device,  deviceList));
    dlclose(handle);
}

CUresult cuD3D9GetDevice(CUdevice* pCudaDevice, const char* pszAdapterName) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D9GetDevice)(CUdevice* , const char* );
    fakecuD3D9GetDevice = dlsym(handle, "cuD3D9GetDevice");
    printf("cuD3D9GetDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D9GetDevice)( pCudaDevice,  pszAdapterName));
    dlclose(handle);
}

CUresult cuD3D9GetDirect3DDevice(IDirect3DDevice9** ppD3DDevice) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D9GetDirect3DDevice)(IDirect3DDevice9** );
    fakecuD3D9GetDirect3DDevice = dlsym(handle, "cuD3D9GetDirect3DDevice");
    printf("cuD3D9GetDirect3DDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D9GetDirect3DDevice)( ppD3DDevice));
    dlclose(handle);
}

CUresult cuGraphicsD3D9RegisterResource( CUgraphicsResource* pCudaResource, IDirect3DResource9* pD3DResource, unsigned int  Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsD3D9RegisterResource)( CUgraphicsResource* , IDirect3DResource9* , unsigned int );
    fakecuGraphicsD3D9RegisterResource = dlsym(handle, "cuGraphicsD3D9RegisterResource");
    printf("cuGraphicsD3D9RegisterResource\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsD3D9RegisterResource)( pCudaResource,  pD3DResource, Flags));
    dlclose(handle);
}

CUresult cuD3D10GetDevice(CUdevice* pCudaDevice, IDXGIAdapter* pAdapter) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D10GetDevice)(CUdevice* , IDXGIAdapter* );
    fakecuD3D10GetDevice = dlsym(handle, "cuD3D10GetDevice");
    printf("cuD3D10GetDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D10GetDevice)(pCudaDevice, pAdapter ));
    dlclose(handle);
}

CUresult cuD3D10GetDevices(unsigned int* pCudaDeviceCount, CUdevice* pCudaDevices, unsigned int  cudaDeviceCount, ID3D10Device* pD3D10Device, CUd3d10DeviceList deviceList) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D10GetDevices)(unsigned int* , CUdevice* , unsigned int , ID3D10Device* , CUd3d10DeviceList );
    fakecuD3D10GetDevices = dlsym(handle, "cuD3D10GetDevices");
    printf("cuD3D10GetDevices\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D10GetDevices)(pCudaDeviceCount,  pCudaDevices, cudaDeviceCount,  pD3D10Device,  deviceList));
    dlclose(handle);
}

CUresult cuGraphicsD3D10RegisterResource(CUgraphicsResource* pCudaResource, ID3D10Resource* pD3DResource, unsigned int  Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsD3D10RegisterResource)(CUgraphicsResource* , ID3D10Resource* , unsigned int );
    fakecuGraphicsD3D10RegisterResource = dlsym(handle, "cuGraphicsD3D10RegisterResource");
    printf("cuGraphicsD3D10RegisterResource\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsD3D10RegisterResource)( pCudaResource,  pD3DResource,  Flags));
    dlclose(handle);
}

CUresult cuD3D11GetDevice(CUdevice* pCudaDevice, IDXGIAdapter* pAdapter) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D11GetDevice)(CUdevice* , IDXGIAdapter* );
    fakecuD3D11GetDevice = dlsym(handle, "cuD3D11GetDevice");
    printf("cuD3D11GetDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D11GetDevice)( pCudaDevice,  pAdapter));
    dlclose(handle);
}

CUresult cuD3D11GetDevices(unsigned int* pCudaDeviceCount, CUdevice* pCudaDevices, unsigned int  cudaDeviceCount, ID3D11Device* pD3D11Device, CUd3d11DeviceList deviceList) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuD3D11GetDevices)(unsigned int* , CUdevice* , unsigned int  , ID3D11Device* , CUd3d11DeviceList );
    fakecuD3D11GetDevices = dlsym(handle, "cuD3D11GetDevices");
    printf("cuD3D11GetDevices\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuD3D11GetDevices)(pCudaDeviceCount,  pCudaDevices, cudaDeviceCount,  pD3D11Device,  deviceList));
    dlclose(handle);
}

CUresult cuGraphicsD3D11RegisterResource(CUgraphicsResource* pCudaResource, ID3D11Resource* pD3DResource, unsigned int  Flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsD3D11RegisterResource)(CUgraphicsResource* , ID3D11Resource* , unsigned int);
    fakecuGraphicsD3D11RegisterResource = dlsym(handle, "cuGraphicsD3D11RegisterResource");
    printf("cuGraphicsD3D11RegisterResource\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsD3D11RegisterResource)( pCudaResource,  pD3DResource, Flags));
    dlclose(handle);
}

CUresult cuGraphicsVDPAURegisterOutputSurface(CUgraphicsResource* pCudaResource, VdpOutputSurface vdpSurface, unsigned int flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsVDPAURegisterOutputSurface)(CUgraphicsResource* , VdpOutputSurface , unsigned int );
    fakecuGraphicsVDPAURegisterOutputSurface = dlsym(handle, "cuGraphicsVDPAURegisterOutputSurface");
    printf("cuGraphicsVDPAURegisterOutputSurface\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsVDPAURegisterOutputSurface)( pCudaResource, vdpSurface, flags));
    dlclose(handle);
}

CUresult cuGraphicsVDPAURegisterVideoSurface(CUgraphicsResource* pCudaResource, VdpVideoSurface vdpSurface, unsigned int  flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsVDPAURegisterVideoSurface)(CUgraphicsResource* , VdpVideoSurface, unsigned int );
    fakecuGraphicsVDPAURegisterVideoSurface = dlsym(handle, "cuGraphicsVDPAURegisterVideoSurface");
    printf("cuGraphicsVDPAURegisterVideoSurface\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsVDPAURegisterVideoSurface)( pCudaResource, vdpSurface, flags));
    dlclose(handle);
}

CUresult cuVDPAUCtxCreate(CUcontext* pCtx, unsigned int  flags, CUdevice device, VdpDevice vdpDevice, VdpGetProcAddress* vdpGetProcAddress) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuVDPAUCtxCreate)(CUcontext* , unsigned int  , CUdevice , VdpDevice , VdpGetProcAddress* );
    fakecuVDPAUCtxCreate = dlsym(handle, "cuVDPAUCtxCreate");
    printf("cuVDPAUCtxCreate\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuVDPAUCtxCreate)( pCtx, flags, device, vdpDevice,  vdpGetProcAddress));
    dlclose(handle);
}

CUresult cuVDPAUGetDevice(CUdevice* pDevice, VdpDevice vdpDevice, VdpGetProcAddress* vdpGetProcAddress) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuVDPAUGetDevice)(CUdevice* , VdpDevice , VdpGetProcAddress* );
    fakecuVDPAUGetDevice = dlsym(handle, "cuVDPAUGetDevice");
    printf("cuVDPAUGetDevice\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuVDPAUGetDevice)( pDevice,  vdpDevice,  vdpGetProcAddress));
    dlclose(handle);
}

CUresult cuEGLStreamConsumerAcquireFrame(CUeglStreamConnection* conn, CUgraphicsResource* pCudaResource, CUstream* pStream, unsigned int  timeout) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEGLStreamConsumerAcquireFrame)(CUeglStreamConnection* , CUgraphicsResource* , CUstream* , unsigned int );
    fakecuEGLStreamConsumerAcquireFrame = dlsym(handle, "cuEGLStreamConsumerAcquireFrame");
    printf("cuEGLStreamConsumerAcquireFrame\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEGLStreamConsumerAcquireFrame)( conn,  pCudaResource,  pStream, timeout));
    dlclose(handle);
}

CUresult cuEGLStreamConsumerConnect(CUeglStreamConnection* conn, EGLStreamKHR stream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEGLStreamConsumerConnect)(CUeglStreamConnection* , EGLStreamKHR  );
    fakecuEGLStreamConsumerConnect = dlsym(handle, "cuEGLStreamConsumerConnect");
    printf("cuEGLStreamConsumerConnect\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEGLStreamConsumerConnect)( conn, stream));
    dlclose(handle);
}

CUresult cuEGLStreamConsumerConnectWithFlags(CUeglStreamConnection* conn, EGLStreamKHR stream,unsigned int  flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEGLStreamConsumerConnectWithFlags)(CUeglStreamConnection* , EGLStreamKHR ,unsigned int );
    fakecuEGLStreamConsumerConnectWithFlags = dlsym(handle, "cuEGLStreamConsumerConnectWithFlags");
    printf("cuEGLStreamConsumerConnectWithFlags\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEGLStreamConsumerConnectWithFlags)( conn, stream,flags));
    dlclose(handle);
}

CUresult cuEGLStreamConsumerDisconnect( CUeglStreamConnection* conn) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEGLStreamConsumerDisconnect)( CUeglStreamConnection* );
    fakecuEGLStreamConsumerDisconnect = dlsym(handle, "cuEGLStreamConsumerDisconnect");
    printf("cuEGLStreamConsumerDisconnect\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEGLStreamConsumerDisconnect)( conn));
    dlclose(handle);
}

CUresult cuEGLStreamConsumerReleaseFrame(CUeglStreamConnection* conn, CUgraphicsResource pCudaResource, CUstream* pStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEGLStreamConsumerReleaseFrame)( CUeglStreamConnection* , CUgraphicsResource , CUstream* );
    fakecuEGLStreamConsumerReleaseFrame = dlsym(handle, "cuEGLStreamConsumerReleaseFrame");
    printf("cuEGLStreamConsumerReleaseFrame\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEGLStreamConsumerReleaseFrame)(conn, pCudaResource,  pStream));
    dlclose(handle);
}

CUresult cuEGLStreamProducerConnect(CUeglStreamConnection* conn, EGLStreamKHR stream, EGLint width, EGLint height) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEGLStreamProducerConnect)(CUeglStreamConnection* , EGLStreamKHR , EGLint , EGLint );
    fakecuEGLStreamProducerConnect = dlsym(handle, "cuEGLStreamProducerConnect");
    printf("cuEGLStreamProducerConnect\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEGLStreamProducerConnect)(conn, stream,  width, height));
    dlclose(handle);
}

CUresult cuEGLStreamProducerDisconnect(CUeglStreamConnection* conn) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEGLStreamProducerDisconnect)( CUeglStreamConnection* );
    fakecuEGLStreamProducerDisconnect = dlsym(handle, "cuEGLStreamProducerDisconnect");
    printf("cuEGLStreamProducerDisconnect\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEGLStreamProducerDisconnect)(conn));
    dlclose(handle);
}

CUresult cuEGLStreamProducerPresentFrame(CUeglStreamConnection* conn, CUeglFrame eglframe, CUstream* pStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEGLStreamProducerPresentFrame)( CUeglStreamConnection* , CUeglFrame , CUstream* );
    fakecuEGLStreamProducerPresentFrame = dlsym(handle, "cuEGLStreamProducerPresentFrame");
    printf("cuEGLStreamProducerPresentFrame\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEGLStreamProducerPresentFrame)( conn,  eglframe, pStream));
    dlclose(handle);
}

CUresult cuEGLStreamProducerReturnFrame(CUeglStreamConnection* conn, CUeglFrame* eglframe, CUstream* pStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEGLStreamProducerReturnFrame)(CUeglStreamConnection* , CUeglFrame* , CUstream* );
    fakecuEGLStreamProducerReturnFrame = dlsym(handle, "cuEGLStreamProducerReturnFrame");
    printf("cuEGLStreamProducerReturnFrame\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEGLStreamProducerReturnFrame)(conn,  eglframe, pStream));
    dlclose(handle);
}

CUresult cuEventCreateFromEGLSync(CUevent* phEvent, EGLSyncKHR eglSync, unsigned int  flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuEventCreateFromEGLSync)(CUevent* , EGLSyncKHR , unsigned int );
    fakecuEventCreateFromEGLSync = dlsym(handle, "cuEventCreateFromEGLSync");
    printf("cuEventCreateFromEGLSync\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEventCreateFromEGLSync)(phEvent, eglSync, flags));
    dlclose(handle);
}

CUresult cuGraphicsEGLRegisterImage(CUgraphicsResource* pCudaResource, EGLImageKHR image, unsigned int  flags) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsEGLRegisterImage)(CUgraphicsResource* , EGLImageKHR, unsigned int );
    fakecuGraphicsEGLRegisterImage = dlsym(handle, "cuGraphicsEGLRegisterImage");
    printf("cuGraphicsEGLRegisterImage\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsEGLRegisterImage)( pCudaResource, image, flags));
    dlclose(handle);
}

CUresult cuGraphicsResourceGetMappedEglFrame(CUeglFrame* eglFrame, CUgraphicsResource resource, unsigned int  index, unsigned int  mipLevel) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuGraphicsResourceGetMappedEglFrame)(CUeglFrame* , CUgraphicsResource, unsigned int , unsigned int );
    fakecuGraphicsResourceGetMappedEglFrame = dlsym(handle, "cuGraphicsResourceGetMappedEglFrame");
    printf("cuGraphicsResourceGetMappedEglFrame\n");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuGraphicsResourceGetMappedEglFrame)(eglFrame, resource,index, mipLevel));
    dlclose(handle);
}*/
