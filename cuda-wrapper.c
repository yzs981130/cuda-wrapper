#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cuda.h>
#include <string.h>

static const char LIB_STRING[] = "libcuda.so";

#define checkCudaErrors(err)  __checkCudaErrors (err, __FILE__, __LINE__)
void __checkCudaErrors( CUresult err, const char *file, const int line )
{
    //if( CUDA_SUCCESS != err) {
        fprintf(stderr,
                "CUDA Driver API error = %04d from file <%s>, line %i.\n",
                err, file, line );
        //exit(-1);
    //}
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetName)(name, len, dev));
    strcpy(name, "yzs's GPU");
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
    printf("cuInit!!!!!!\n");

    printf("Flags: %d\n", Flags);
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
    printf("cuDeviceGetCount: %d", *count);
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetAttribute)(pi, attrib, dev));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxPushCurrent_v2)(pctx));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetCurrent)(pctx));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetApiVersion)(ctx, version));
    dlclose(handle);
}

CUresult cuCtxSynchronize() {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuCtxSynchronize)();
    fakecuCtxSynchronize = dlsym(handle, "cuCtxSynchronize");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxSynchronize)());
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleLoadDataEx)(module, image, numOptions, options, optionValues));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleUnload)(hmod));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuModuleGetGlobal_v2)(dptr, bytes, hmod, name));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuEventSynchronize)(hEvent));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuEventQuery)(hEvent));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemAlloc_v2)(dptr, bytesize));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamAddCallback)(hStream, callback, userData, flags));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamSynchronize)(hStream));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceCanAccessPeer)(canAccessPeer, dev, peerDev));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuFuncGetAttribute)(pi, attrib, hfunc));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxSetCurrent)(ctx));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamWaitEvent)(hStream, hEvent, Flags));
    dlclose(handle);
}

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
    fakecuMemAllocManaged = dlsym(handle, "cuMemsetD32_v2");

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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetSharedMemConfig)(pConfig));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuFuncSetCacheConfig)(hfunc, config));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamCreate)(phStream, Flags));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuCtxGetDevice)(device));
    dlclose(handle);
}
/*
CUresult cuMemcpyDtoHAsync(void* dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyDtoHAsync)(void *, CUdeviceptr, size_t, CUstream);
    fakecuMemcpyDtoHAsync = dlsym(handle, "cuMemcpyDtoHAsync");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuMemcpyDtoHAsync)(dstHost, srcDevice, ByteCount, hStream));
    dlclose(handle);
    return r;
}*/

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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDevicePrimaryCtxRelease)(dev));
    dlclose(handle);
}
/*
CUresult cuMemcpyHtoDAsync(CUdeviceptr dstDevice, const void* srcHost, size_t ByteCount, CUstream hStream) {
    char *error;
    void *handle;
    handle = dlopen (LIB_STRING, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();

    CUresult (*fakecuMemcpyHtoDAsync)(CUdeviceptr, const void*, size_t, CUstream);
    fakecuMemcpyHtoDAsync = dlsym(handle, "cuMemcpyHtoDAsync");

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    CUresult r;
    checkCudaErrors(r = (*fakecuMemcpyHtoDAsync)(dstDevice, srcHost, ByteCount, hStream));
    dlclose(handle);
    return r;
}
*/
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemcpyDtoD)(dstDevice, srcDevice, ByteCount));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuOccupancyMaxPotentialBlockSize)(minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDevicePrimaryCtxRetain)(pctx, dev));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuDeviceGetPCIBusId)(pciBusId, len, dev));
    dlclose(handle);
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuPointerGetAttribute)(data, attribute, ptr));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuOccupancyMaxActiveBlocksPerMultiprocessor)( numBlocks,  func, blockSize,  dynamicSMemSize));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuStreamDestroy_v2)(hStream));
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

    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    checkCudaErrors((*fakecuMemsetD8Async)( dstDevice, uc, N, hStream));
    dlclose(handle);
}


