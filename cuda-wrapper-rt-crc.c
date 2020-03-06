#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cuda.h>
#include <string.h>
#include <pthread.h>
#include <cuda_runtime.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
//#include <helper_cuda.h>
#define SIZE 10000

unsigned long long mod = 9973L;

static const char LIB_STRING[] = "libcudart.so";
static const char CONFIG_STRING[] = "WRAPPER_MAX_MEMORY";
void* func[200];
void* func2[10];
int init_flag = 0;
void* handle;
char* error;

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
  unsigned int crc = 0xFFFFFFFF;
  while (len--)
    {
      crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ *buf) & 255];
      buf++;
    }
  return crc;
}

void init_func() {
    if(init_flag == 0 ) {
    	handle = dlopen (LIB_STRING, RTLD_LAZY);
    	if (!handle) {
       	    fprintf (stderr, "%s\n", dlerror());
       	    exit(1);
    	}
	    init_flag = 1;
    	dlerror();
        printf("Init!\n");

        func[0] = dlsym(handle, "cudaMalloc");
	    if ((error = dlerror()) != NULL)  {    
		    fprintf (stderr, "%s\n", error); 
		    exit(1); 
        }
        
    	func[1] = dlsym(handle, "cudaFree");
    	if ((error = dlerror()) != NULL)  {
        	fprintf (stderr, "%s\n", error);
        	exit(1);
    	}

        func[2] = dlsym(handle, "cudaHostAlloc");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[3] = dlsym(handle, "cudaFreeHost");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[4] = dlsym(handle, "cudaDeviceGetStreamPriorityRange");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[5] = dlsym(handle, "cudaHostGetDevicePointer");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[6] = dlsym(handle, "cudaGetDeviceProperties");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[7] = dlsym(handle, "cudaStreamCreateWithPriority");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[8] = dlsym(handle, "cudaStreamCreateWithFlags");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[9] = dlsym(handle, "cudaEventCreateWithFlags");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[10] = dlsym(handle, "cudaEventDestroy");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[11] = dlsym(handle, "cudaStreamDestroy");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[12] = dlsym(handle, "cudaGetDeviceCount");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[13] = dlsym(handle, "cudaCreateChannelDesc");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func2[0] = dlsym(handle, "cudaFuncGetAttributes");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func2[1] = dlsym(handle, "cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[16] = dlsym(handle, "cudaStreamSynchronize");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[17] = dlsym(handle, "cudaMemcpyAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[18] = dlsym(handle, "cudaEventRecord");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[19] = dlsym(handle, "cudaDeviceGetAttribute");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[20] = dlsym(handle, "cudaMemsetAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func2[2] = dlsym(handle, "cudaLaunchKernel");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[22] = dlsym(handle, "cudaGetLastError");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[23] = dlsym(handle, "cudaSetDevice");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[24] = dlsym(handle, "cudaGetDevice");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[25] = dlsym(handle, "cudaProfilerStop");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[26] = dlsym(handle, "cudaProfilerStart");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[27] = dlsym(handle, "cudaProfilerInitialize");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[28] = dlsym(handle, "cudaGraphRemoveDependencies");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[29] = dlsym(handle, "cudaGraphNodeGetType");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[30] = dlsym(handle, "cudaGraphNodeGetDependentNodes");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[31] = dlsym(handle, "cudaGraphNodeGetDependencies");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[32] = dlsym(handle, "cudaGraphNodeFindInClone");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[33] = dlsym(handle, "cudaGraphMemsetNodeSetParams");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[34] = dlsym(handle, "cudaGraphMemsetNodeGetParams");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[35] = dlsym(handle, "cudaGraphMemcpyNodeSetParams");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[36] = dlsym(handle, "cudaGraphMemcpyNodeGetParams");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[37] = dlsym(handle, "cudaGraphLaunch");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[38] = dlsym(handle, "cudaGraphKernelNodeSetParams");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[39] = dlsym(handle, "cudaGraphKernelNodeGetParams");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[40] = dlsym(handle, "cudaGraphInstantiate");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[41] = dlsym(handle, "cudaGraphHostNodeSetParams");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[42] = dlsym(handle, "cudaGraphHostNodeGetParams");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[43] = dlsym(handle, "cudaGraphGetRootNodes");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[44] = dlsym(handle, "cudaGraphGetNodes");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[45] = dlsym(handle, "cudaGraphGetEdges");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        /*func[46] = dlsym(handle, "cudaGraphExecKernelNodeSetParams");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }*/

        func[47] = dlsym(handle, "cudaGraphExecDestroy");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[48] = dlsym(handle, "cudaGraphDestroyNode");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[49] = dlsym(handle, "cudaGraphDestroy");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[50] = dlsym(handle, "cudaGraphCreate");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[51] = dlsym(handle, "cudaGraphClone");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[52] = dlsym(handle, "cudaGraphChildGraphNodeGetGraph");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[53] = dlsym(handle, "cudaGraphAddMemsetNode");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[54] = dlsym(handle, "cudaGraphAddMemcpyNode");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[55] = dlsym(handle, "cudaGraphAddKernelNode");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[56] = dlsym(handle, "cudaGraphAddHostNode");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[57] = dlsym(handle, "cudaGraphAddEmptyNode");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[58] = dlsym(handle, "cudaGraphAddDependencies");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[59] = dlsym(handle, "cudaGraphAddChildGraphNode");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[60] = dlsym(handle, "cudaRuntimeGetVersion");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[61] = dlsym(handle, "cudaDriverGetVersion");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[62] = dlsym(handle, "cudaGetSurfaceObjectResourceDesc");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[63] = dlsym(handle, "cudaDestroySurfaceObject");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[64] = dlsym(handle, "cudaCreateSurfaceObject");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[65] = dlsym(handle, "cudaGetTextureObjectTextureDesc");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[66] = dlsym(handle, "cudaGetTextureObjectResourceViewDesc");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[67] = dlsym(handle, "cudaGetTextureObjectResourceDesc");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[68] = dlsym(handle, "cudaGetChannelDesc");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[69] = dlsym(handle, "cudaDestroyTextureObject");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[70] = dlsym(handle, "cudaCreateTextureObject");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[71] = dlsym(handle, "cudaGraphicsUnregisterResource");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[72] = dlsym(handle, "cudaGraphicsUnmapResources");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[73] = dlsym(handle, "cudaGraphicsSubResourceGetMappedArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[74] = dlsym(handle, "cudaGraphicsResourceSetMapFlags");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[75] = dlsym(handle, "cudaGraphicsResourceGetMappedPointer");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[76] = dlsym(handle, "cudaGraphicsResourceGetMappedMipmappedArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[77] = dlsym(handle, "cudaGraphicsMapResources");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[78] = dlsym(handle, "cudaDeviceEnablePeerAccess");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[79] = dlsym(handle, "cudaDeviceDisablePeerAccess");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[80] = dlsym(handle, "cudaDeviceCanAccessPeer");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[81] = dlsym(handle, "cudaPointerGetAttributes");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[82] = dlsym(handle, "cudaMemset3DAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[83] = dlsym(handle, "cudaMemset3D");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[84] = dlsym(handle, "cudaMemset2DAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[85] = dlsym(handle, "cudaMemset2D");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[86] = dlsym(handle, "cudaMemset");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[87] = dlsym(handle, "cudaMemcpyToSymbolAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[88] = dlsym(handle, "cudaMemcpyToSymbol");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[89] = dlsym(handle, "cudaMemcpyPeerAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[90] = dlsym(handle, "cudaMemcpyPeer");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[91] = dlsym(handle, "cudaMemcpyFromSymbolAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[92] = dlsym(handle, "cudaMemcpyFromSymbol");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[93] = dlsym(handle, "cudaMemcpy3DPeerAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[94] = dlsym(handle, "cudaMemcpy3DPeer");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[95] = dlsym(handle, "cudaMemcpy3DAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[96] = dlsym(handle, "cudaMemcpy3D");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[97] = dlsym(handle, "cudaMemcpy2DToArrayAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[98] = dlsym(handle, "cudaMemcpy2DToArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[99] = dlsym(handle, "cudaMemcpy2DFromArrayAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[100] = dlsym(handle, "cudaMemcpy2DFromArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[101] = dlsym(handle, "cudaMemcpy2DAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[102] = dlsym(handle, "cudaMemcpy2DArrayToArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[103] = dlsym(handle, "cudaMemcpy2D");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[104] = dlsym(handle, "cudaMemcpy");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[105] = dlsym(handle, "cudaMemRangeGetAttributes");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[106] = dlsym(handle, "cudaMemRangeGetAttribute");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[107] = dlsym(handle, "cudaMemPrefetchAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[108] = dlsym(handle, "cudaMemAdvise");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[109] = dlsym(handle, "cudaHostUnregister");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[110] = dlsym(handle, "cudaHostRegister");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[111] = dlsym(handle, "cudaHostGetFlags");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[112] = dlsym(handle, "cudaGetSymbolSize");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[113] = dlsym(handle, "cudaGetSymbolAddress");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[114] = dlsym(handle, "cudaGetMipmappedArrayLevel");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[115] = dlsym(handle, "cudaFreeMipmappedArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[116] = dlsym(handle, "cudaFreeArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[117] = dlsym(handle, "cudaArrayGetInfo");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func2[3] = dlsym(handle, "cudaOccupancyMaxActiveBlocksPerMultiprocessor");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[119] = dlsym(handle, "cudaSetDoubleForHost");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[120] = dlsym(handle, "cudaSetDoubleForDevice");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[120] = dlsym(handle, "cudaSetDoubleForDevice");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[121] = dlsym(handle, "cudaLaunchHostFunc");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[122] = dlsym(handle, "cudaLaunchCooperativeKernelMultiDevice");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func2[4] = dlsym(handle, "cudaLaunchCooperativeKernel");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        /*func2[5] = dlsym(handle, "cudaGetParameterBufferV2");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[125] = dlsym(handle, "cudaGetParameterBuffer");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }*/

        func2[6] = dlsym(handle, "cudaFuncSetSharedMemConfig");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func2[7] = dlsym(handle, "cudaFuncSetCacheConfig");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func2[8] = dlsym(handle, "cudaFuncSetAttribute");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[129] = dlsym(handle, "cudaWaitExternalSemaphoresAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[130] = dlsym(handle, "cudaSignalExternalSemaphoresAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[131] = dlsym(handle, "cudaImportExternalSemaphore");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[132] = dlsym(handle, "cudaImportExternalMemory");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[133] = dlsym(handle, "cudaExternalMemoryGetMappedMipmappedArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[134] = dlsym(handle, "cudaExternalMemoryGetMappedBuffer");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[135] = dlsym(handle, "cudaDestroyExternalSemaphore");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[136] = dlsym(handle, "cudaDestroyExternalMemory");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[137] = dlsym(handle, "cudaEventSynchronize");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[138] = dlsym(handle, "cudaEventQuery");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[139] = dlsym(handle, "cudaEventElapsedTime");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[140] = dlsym(handle, "cudaEventCreate");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[141] = dlsym(handle, "cudaStreamWaitEvent");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[142] = dlsym(handle, "cudaStreamQuery");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[143] = dlsym(handle, "cudaStreamIsCapturing");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[144] = dlsym(handle, "cudaStreamGetPriority");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[145] = dlsym(handle, "cudaStreamGetFlags");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        /*func[146] = dlsym(handle, "cudaStreamGetCaptureInfo");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }*/

        func[147] = dlsym(handle, "cudaStreamEndCapture");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[148] = dlsym(handle, "cudaStreamCreate");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[149] = dlsym(handle, "cudaStreamBeginCapture");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[150] = dlsym(handle, "cudaStreamAttachMemAsync");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[151] = dlsym(handle, "cudaStreamAddCallback");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[152] = dlsym(handle, "cudaPeekAtLastError");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[153] = dlsym(handle, "cudaGetErrorString");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[154] = dlsym(handle, "cudaGetErrorName");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[155] = dlsym(handle, "cudaSetValidDevices");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[156] = dlsym(handle, "cudaSetDeviceFlags");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[157] = dlsym(handle, "cudaIpcOpenMemHandle");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[158] = dlsym(handle, "cudaIpcOpenEventHandle");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[159] = dlsym(handle, "cudaIpcGetMemHandle");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[160] = dlsym(handle, "cudaIpcGetEventHandle");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[161] = dlsym(handle, "cudaIpcCloseMemHandle");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[162] = dlsym(handle, "cudaGetDeviceFlags");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[163] = dlsym(handle, "cudaDeviceSynchronize");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[164] = dlsym(handle, "cudaDeviceSetSharedMemConfig");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[165] = dlsym(handle, "cudaDeviceSetLimit");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[166] = dlsym(handle, "cudaDeviceSetCacheConfig");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[167] = dlsym(handle, "cudaDeviceReset");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[168] = dlsym(handle, "cudaDeviceGetSharedMemConfig");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[169] = dlsym(handle, "cudaDeviceGetPCIBusId");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[170] = dlsym(handle, "cudaDeviceGetP2PAttribute");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[171] = dlsym(handle, "cudaDeviceGetLimit");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[172] = dlsym(handle, "cudaDeviceGetCacheConfig");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[173] = dlsym(handle, "cudaDeviceGetByPCIBusId");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[174] = dlsym(handle, "cudaChooseDevice");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[175] = dlsym(handle, "cudaMallocMipmappedArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[176] = dlsym(handle, "cudaMallocArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[177] = dlsym(handle, "cudaMallocHost");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[178] = dlsym(handle, "cudaMalloc3DArray");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[179] = dlsym(handle, "cudaMalloc3D");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[180] = dlsym(handle, "cudaMallocManaged");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[181] = dlsym(handle, "cudaMallocPitch");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }

        func[182] = dlsym(handle, "cudaMemGetInfo");
        if ((error = dlerror()) != NULL)  {
            fprintf (stderr, "%s\n", error);
            exit(1);
        }
    }

}

void end_func() {

}

cudaError_t cudaMalloc( void** devPtr, size_t bytesize) {
    init_func();     
    //printf("cudaMalloc:\n");
    cudaError_t r= (*(cudaError_t (*)( void** , size_t ))(func[0]))( devPtr , bytesize);
    end_func();
    return r;
}

cudaError_t cudaFree( void* devPtr ) {
        
    init_func();
    //printf("cudaFree:\n");
    cudaError_t r= (*(cudaError_t (*)( void* ))(func[1]))( devPtr );
    end_func();
    return r;
}

cudaError_t cudaHostAlloc ( void** pHost, size_t size, unsigned int flags) {
        
    init_func();
    //printf("cudaHostAlloc\n");
    cudaError_t r= (*(cudaError_t (*)(void** , size_t , unsigned int))(func[2]))(pHost, size, flags);
    end_func();
    return r;
}

cudaError_t cudaFreeHost ( void* ptr) {
        
    init_func();
    //printf("cudaFreeHost\n");
    cudaError_t r= (*(cudaError_t (*)(void* ))(func[3]))( ptr);
    end_func();
    return r;
}

cudaError_t cudaDeviceGetStreamPriorityRange( int* leastPriority, int* greatestPriority) {
        
    init_func();
    //printf("cudaDeviceGetStreamPriorityRange\n");
    cudaError_t r= (*(cudaError_t (*)(int* ,int* ))(func[4]))(leastPriority, greatestPriority);
    end_func();
    return r;
}

cudaError_t cudaHostGetDevicePointer ( void** pDevice, void* pHost, unsigned int  flags) {
        
    init_func();
    //printf("cudaHostGetDevicePointer\n");
    cudaError_t r= (*(cudaError_t (*)(void** , void* , unsigned int ))(func[5]))(pDevice, pHost, flags);
    end_func();
    return r;
}

cudaError_t cudaGetDeviceProperties( struct cudaDeviceProp* prop, int device) {
        
    init_func();
    //printf("cudaGetDeviceProperties\n");
    cudaError_t r= (*(cudaError_t (*)(struct cudaDeviceProp* , int ))(func[6]))( prop,device);
    end_func();
    return r;
}

cudaError_t cudaStreamCreateWithPriority( cudaStream_t* pStream, unsigned int  flags, int  priority) {
        
    init_func();
    //printf("cudaStreamCreateWithPriority\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t* , unsigned int  , int ))(func[7]))(pStream,  flags,  priority);
    end_func();
    return r;
}

cudaError_t cudaStreamCreateWithFlags( cudaStream_t* pStream, unsigned int  flags) {
        
    init_func();
    //printf("cudaStreamCreateWithFlags\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t* , unsigned int ))(func[8]))(pStream,  flags);
    end_func();
    return r;
}

cudaError_t cudaEventCreateWithFlags ( cudaEvent_t* event, unsigned int  flags) {
        
    init_func();
    //printf("cudaEventCreateWithFlags:\n");
    cudaError_t r= (*(cudaError_t (*)(cudaEvent_t*, unsigned int ))(func[9]))(event, flags);
    end_func();
    return r;
}

cudaError_t cudaEventDestroy ( cudaEvent_t event) {
        
    init_func();
    //printf("cudaEventDestroy\n");
    cudaError_t r= (*(cudaError_t (*)(cudaEvent_t ))(func[10]))(event);
    end_func();
    return r;
}

cudaError_t cudaStreamDestroy ( cudaStream_t stream) {
        
    init_func();
    //printf("cudaStreamDestroy\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t ))(func[11]))(stream);
    end_func();
    return r;
}

cudaError_t cudaGetDeviceCount( int* count ) {
        
    init_func();
    //printf("cudaGetDeviceCount:\n");
    cudaError_t r= (*(cudaError_t (*)(int* ))(func[12]))(count);
    end_func();
    return r;
}

struct cudaChannelFormatDesc cudaCreateChannelDesc ( int  x, int  y, int  z, int  w, enum cudaChannelFormatKind f ) {
    init_func();
    //printf("cudaCreateChannelDesc:\n");
    struct cudaChannelFormatDesc r= (*(struct cudaChannelFormatDesc (*)(int, int , int , int , enum cudaChannelFormatKind))(func[13]))( x,y,z,w,f);
    end_func();
    return r;
}

cudaError_t cudaFuncGetAttributes ( struct cudaFuncAttributes* attr, const void* func) {
        
    init_func();
    //printf("cudaFuncGetAttributes\n");
    cudaError_t r= (*(cudaError_t (*)(struct cudaFuncAttributes* , const void* ))(func2[0]))(attr, func);
    end_func();
    return r;
}

cudaError_t cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags ( int* numBlocks, const void* func, int  blockSize, size_t dynamicSMemSize, unsigned int flags) {
        
    init_func();
    //printf("cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags\n");
    cudaError_t r= (*(cudaError_t (*)(int* , const void* , int , size_t , unsigned int ))(func2[1]))( numBlocks, func, blockSize, dynamicSMemSize, flags);
    end_func();
    return r;
}

cudaError_t cudaStreamSynchronize ( cudaStream_t stream) {
        
    init_func();
    //printf("cudaStreamSynchronize:\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t ))(func[16]))(stream);
    end_func();
    return r;
}

cudaError_t cudaMemcpyAsync ( void* dst, const void* src, size_t count, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    //printf("cudaMemcpyAsync:\n");
    cudaError_t r= (*(cudaError_t (*)(void* , const void* , size_t , enum cudaMemcpyKind , cudaStream_t ))(func[17]))( dst, src, count, kind, stream);
    end_func();
    return r;
}

cudaError_t cudaEventRecord ( cudaEvent_t event, cudaStream_t stream) {
        
    init_func();
    //printf("cudaEventRecord:\n");
    cudaError_t r= (*(cudaError_t (*)(cudaEvent_t, cudaStream_t))(func[18]))( event, stream);
    end_func();
    return r;
}

cudaError_t cudaDeviceGetAttribute ( int* value, enum cudaDeviceAttr attr, int  device ) {
        
    init_func();
    //printf("cudaDeviceGetAttribute\n");
    cudaError_t r= (*(cudaError_t (*)(int* , enum cudaDeviceAttr , int ))(func[19]))( value, attr, device);
    end_func();
    return r;
}

cudaError_t cudaMemsetAsync ( void* devPtr, int  value, size_t count, cudaStream_t stream) {
        
    init_func();
    //printf("cudaMemsetAsync:\n");
    cudaError_t r= (*(cudaError_t (*)(void* , int , size_t, cudaStream_t))(func[20]))(devPtr, value,count, stream);
    end_func();
    return r;
}

cudaError_t cudaLaunchKernel ( const void* func, dim3 gridDim, dim3 blockDim, void** args, size_t sharedMem, cudaStream_t stream) {
        
    init_func();
    printf("cudaLaunchKernel\n");
    const int nbytes = 512;
    unsigned int crc = xcrc32(func, nbytes);
    printf("%u\n", crc);
    printf("%p\n",func);
    //printf("%p\n%p\n",func,(int *)(*args));
    //printf("%p\n%p\n",func,(int *)((int**)args+1));
    //char* funcName = *(char**)((uintptr_t)func + 8);
    //char* funcn = (char* )((uintptr_t)func + 8);
    //printf("%s\n",funcn);
    cudaError_t r= (*(cudaError_t (*)(const void* , dim3 , dim3 , void** , size_t, cudaStream_t ))(func2[2]))( func, gridDim, blockDim, args, sharedMem, stream);
    end_func();
    return r;
}

cudaError_t cudaGetLastError () {
        
    init_func();
    //printf("cudaGetLastError:\n");
    cudaError_t r= (*(cudaError_t (*)(void ))(func[22]))();
    end_func();
    return r;
}

cudaError_t cudaSetDevice (int  device) {
        
    init_func();
    //printf("cudaSetDevice:\n");
    cudaError_t r= (*(cudaError_t (*)(int ))(func[23]))(device);
    end_func();
    return r;
}

cudaError_t cudaGetDevice( int* device) {
        
    init_func();
    //printf("cudaGetDevice:\n");
    cudaError_t r= (*(cudaError_t (*)(int* ))(func[24]))(device);
    end_func();
    return r;
}

cudaError_t cudaProfilerStop ( void) {
        
    init_func();
    //printf("cudaProfilerStop\n");
    cudaError_t r= (*(cudaError_t (*)(void ))(func[25]))( );
    end_func();
    return r;
}

cudaError_t cudaProfilerStart ( void) {
    
    init_func();
    //printf("cudaProfilerStart\n");
    cudaError_t r= (*(cudaError_t (*)(void ))(func[26]))( );
    end_func();
    return r;
}

cudaError_t cudaProfilerInitialize ( const char* configFile, const char* outputFile, cudaOutputMode_t outputMode) {
        
    init_func();
    printf("cudaProfilerInitialize\n");
    cudaError_t r= (*(cudaError_t (*)(const char* , const char* , cudaOutputMode_t))(func[27]))( configFile,  outputFile, outputMode);
    end_func();
    return r;
}

cudaError_t cudaGraphRemoveDependencies ( cudaGraph_t graph, cudaGraphNode_t* from,  cudaGraphNode_t* to, size_t numDependencies) {
        
    init_func();
    printf("cudaGraphRemoveDependencies\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraph_t, cudaGraphNode_t* , cudaGraphNode_t* ,size_t))(func[28]))( graph, from, to, numDependencies);
    end_func();
    return r;
}

cudaError_t cudaGraphNodeGetType ( cudaGraphNode_t node, enum cudaGraphNodeType * pType) {
        
    init_func();
    printf("cudaGraphNodeGetType\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t , enum cudaGraphNodeType * ))(func[29]))( node, pType);
    end_func();
    return r;
}

cudaError_t cudaGraphNodeGetDependentNodes ( cudaGraphNode_t node, cudaGraphNode_t* pDependentNodes, size_t* pNumDependentNodes) {
        
    init_func();
    printf("cudaGraphNodeGetDependentNodes\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t ,cudaGraphNode_t* , size_t* ))(func[30]))( node, pDependentNodes, pNumDependentNodes);
    end_func();
    return r;
}

cudaError_t cudaGraphNodeGetDependencies ( cudaGraphNode_t node, cudaGraphNode_t* pDependencies, size_t* pNumDependencies) {
        
    init_func();
    printf("cudaGraphNodeGetDependencies\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t ,cudaGraphNode_t* , size_t* ))(func[31]))( node, pDependencies, pNumDependencies);
    end_func();
    return r;
}

cudaError_t cudaGraphNodeFindInClone ( cudaGraphNode_t* pNode, cudaGraphNode_t originalNode, cudaGraph_t clonedGraph) {
        
    init_func();
    printf("cudaGraphNodeFindInClone\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t* ,cudaGraphNode_t , cudaGraph_t ))(func[32]))( pNode, originalNode, clonedGraph);
    end_func();
    return r;
}

cudaError_t cudaGraphMemsetNodeSetParams ( cudaGraphNode_t node, const struct cudaMemsetParams* pNodeParams) {
        
    init_func();
    printf("cudaGraphMemsetNodeSetParams\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t , const struct cudaMemsetParams* ))(func[33]))( node, pNodeParams);
    end_func();
    return r;
}

cudaError_t cudaGraphMemsetNodeGetParams ( cudaGraphNode_t node, struct cudaMemsetParams* pNodeParams) {
        
    init_func();
    printf("cudaGraphMemsetNodeGetParams\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t , struct cudaMemsetParams* ))(func[34]))( node, pNodeParams);
    end_func();
    return r;
}

cudaError_t cudaGraphMemcpyNodeSetParams ( cudaGraphNode_t node, const struct cudaMemcpy3DParms* pNodeParams) {
        
    init_func();
    printf("cudaGraphMemcpyNodeSetParams\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t ,const struct cudaMemcpy3DParms* ))(func[35]))( node, pNodeParams);
    end_func();
    return r;
}

cudaError_t cudaGraphMemcpyNodeGetParams ( cudaGraphNode_t node, struct cudaMemcpy3DParms* pNodeParams) {
        
    init_func();
    printf("cudaGraphMemcpyNodeGetParams\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t , struct cudaMemcpy3DParms* ))(func[36]))( node, pNodeParams);
    end_func();
    return r;
}

cudaError_t cudaGraphLaunch ( cudaGraphExec_t graphExec, cudaStream_t stream) {
        
    init_func();
    printf("cudaGraphLaunch\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphExec_t ,cudaStream_t ))(func[37]))( graphExec, stream);
    end_func();
    return r;
}

cudaError_t cudaGraphKernelNodeSetParams ( cudaGraphNode_t node, const struct cudaKernelNodeParams* pNodeParams) {
        
    init_func();
    printf("cudaGraphKernelNodeSetParams\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t ,const struct cudaKernelNodeParams* ))(func[38]))( node, pNodeParams);
    end_func();
    return r;
}

cudaError_t cudaGraphKernelNodeGetParams ( cudaGraphNode_t node, struct cudaKernelNodeParams* pNodeParams) {
        
    init_func();
    printf("cudaGraphKernelNodeGetParams\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t , struct cudaKernelNodeParams* ))(func[39]))( node, pNodeParams);
    end_func();
    return r;
}

cudaError_t cudaGraphInstantiate ( cudaGraphExec_t* pGraphExec, cudaGraph_t graph, cudaGraphNode_t* pErrorNode, char* pLogBuffer, size_t bufferSize) {
        
    init_func();
    printf("cudaGraphInstantiate\n");
    cudaError_t r= (*(cudaError_t (*)( cudaGraphExec_t* ,const cudaGraph_t ,cudaGraphNode_t* ,char* ,size_t ))(func[40]))( pGraphExec , graph ,  pErrorNode, pLogBuffer, bufferSize);
    end_func();
    return r;
}

cudaError_t cudaGraphHostNodeSetParams ( cudaGraphNode_t node, const struct cudaHostNodeParams* pNodeParams) {
        
    init_func();
    printf("cudaGraphHostNodeSetParams\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t ,const struct cudaHostNodeParams* ))(func[41]))( node , pNodeParams );
    end_func();
    return r;
}

cudaError_t cudaGraphHostNodeGetParams( cudaGraphNode_t node, struct cudaHostNodeParams* pNodeParams) {
        
    init_func();
    printf("cudaGraphHostNodeGetParams\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t , struct cudaHostNodeParams* ))(func[42]))( node , pNodeParams );
    end_func();
    return r;
}

cudaError_t cudaGraphGetRootNodes ( cudaGraph_t graph, cudaGraphNode_t* pRootNodes, size_t* pNumRootNodes) {
        
    init_func();
    printf("cudaGraphGetRootNodes\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraph_t ,cudaGraphNode_t* , size_t* ))(func[43]))( graph,pRootNodes, pNumRootNodes );
    end_func();
    return r;
}

cudaError_t cudaGraphGetNodes ( cudaGraph_t graph, cudaGraphNode_t* nodes, size_t* numNodes) {
        
    init_func();
    printf("cudaGraphGetNodes\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraph_t ,cudaGraphNode_t* , size_t* ))(func[44]))( graph,nodes, numNodes );
    end_func();
    return r;
}

cudaError_t cudaGraphGetEdges ( cudaGraph_t graph, cudaGraphNode_t* from, cudaGraphNode_t* to, size_t* numEdges) {
        
    init_func();
    printf("cudaGraphGetEdges\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraph_t ,cudaGraphNode_t*, cudaGraphNode_t* , size_t* ))(func[45]))( graph, from, to, numEdges );
    end_func();
    return r;
}

/*cudaError_t cudaGraphExecKernelNodeSetParams ( cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const struct cudaKernelNodeParams* pNodeParams) {
        
    init_func();
    printf("cudaGraphExecKernelNodeSetParams\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphExec_t ,cudaGraphNode_t, const struct cudaKernelNodeParams* ))(func[46]))( hGraphExec, node, pNodeParams );
    end_func();
    return r;
}*/

cudaError_t cudaGraphExecDestroy ( cudaGraphExec_t graphExec) {
        
    init_func();
    printf("cudaGraphExecDestroy\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphExec_t ))(func[47]))( graphExec );
    end_func();
    return r;
}

cudaError_t cudaGraphDestroyNode ( cudaGraphNode_t node) {
        
    init_func();
    printf("cudaGraphDestroyNode\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t ))(func[48]))( node );
    end_func();
    return r;
}

cudaError_t cudaGraphDestroy ( cudaGraph_t graph) {
        
    init_func();
    printf("cudaGraphDestroy\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraph_t ))(func[49]))( graph );
    end_func();
    return r;
}

cudaError_t cudaGraphCreate ( cudaGraph_t* pGraph, unsigned int flags) {
        
    init_func();
    printf("cudaGraphCreate\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraph_t* , unsigned int ))(func[50]))( pGraph,  flags );
    end_func();
    return r;
}

cudaError_t cudaGraphClone ( cudaGraph_t* pGraphClone, cudaGraph_t originalGraph) {
        
    init_func();
    printf("cudaGraphClone\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraph_t* , cudaGraph_t ))(func[51]))( pGraphClone,  originalGraph );
    end_func();
    return r;
}

cudaError_t cudaGraphChildGraphNodeGetGraph ( cudaGraphNode_t node, cudaGraph_t* pGraph) {
        
    init_func();
    printf("cudaGraphChildGraphNodeGetGraph\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t, cudaGraph_t* ))(func[52]))( node,  pGraph );
    end_func();
    return r;
}

cudaError_t cudaGraphAddMemsetNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies, const struct cudaMemsetParams* pMemsetParams) {
        
    init_func();
    printf("cudaGraphAddMemsetNode\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t*, cudaGraph_t,  cudaGraphNode_t* , size_t, const struct cudaMemsetParams* ))(func[53]))( pGraphNode,  graph, pDependencies, numDependencies, pMemsetParams);
    end_func();
    return r;
}

cudaError_t cudaGraphAddMemcpyNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies, const struct cudaMemcpy3DParms* pCopyParams) {
        
    init_func();
    printf("cudaGraphAddMemcpyNode\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t*, cudaGraph_t, cudaGraphNode_t* , size_t, const struct cudaMemcpy3DParms* ))(func[54]))( pGraphNode,  graph, pDependencies, numDependencies, pCopyParams);
    end_func();
    return r;
}

cudaError_t cudaGraphAddKernelNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies, const struct cudaKernelNodeParams* pNodeParams) {
        
    init_func();
    printf("cudaGraphAddKernelNode\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t*, cudaGraph_t, cudaGraphNode_t* , size_t, const struct cudaKernelNodeParams* ))(func[55]))( pGraphNode,  graph, pDependencies, numDependencies, pNodeParams);
    end_func();
    return r;
}

cudaError_t cudaGraphAddHostNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies, const struct cudaHostNodeParams* pNodeParams) {
        
    init_func();
    printf("cudaGraphAddHostNode\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t*, cudaGraph_t, cudaGraphNode_t* , size_t, const struct cudaHostNodeParams* ))(func[56]))( pGraphNode,  graph, pDependencies, numDependencies, pNodeParams);
    end_func();
    return r;
}

cudaError_t cudaGraphAddEmptyNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies) {
        
    init_func();
    printf("cudaGraphAddEmptyNode\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphNode_t*, cudaGraph_t, cudaGraphNode_t* , size_t))(func[57]))( pGraphNode,  graph, pDependencies, numDependencies);
    end_func();
    return r;
}

cudaError_t cudaGraphAddDependencies ( cudaGraph_t graph, cudaGraphNode_t* from, cudaGraphNode_t* to, size_t numDependencies) {
        
    init_func();
    printf("cudaGraphAddDependencies\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraph_t , cudaGraphNode_t*,  cudaGraphNode_t* , size_t))(func[58]))( graph,  from, to, numDependencies);
    end_func();
    return r;
}

cudaError_t cudaGraphAddChildGraphNode ( cudaGraphNode_t* pGraphNode, cudaGraph_t graph, cudaGraphNode_t* pDependencies, size_t numDependencies, cudaGraph_t childGraph) {
        
    init_func();
    printf("cudaGraphAddChildGraphNode\n");
    cudaError_t r= (*(cudaError_t (*)( cudaGraphNode_t* , cudaGraph_t, cudaGraphNode_t* , size_t, cudaGraph_t))(func[59]))( pGraphNode,  graph, pDependencies, numDependencies, childGraph);
    end_func();
    return r;
}

cudaError_t cudaRuntimeGetVersion ( int* runtimeVersion) {
        
    init_func();
    printf("cudaRuntimeGetVersion\n");
    cudaError_t r= (*(cudaError_t (*)( int*))(func[60]))( runtimeVersion );
    end_func();
    return r;
}

cudaError_t cudaDriverGetVersion ( int* driverVersion) {
        
    init_func();
    printf("cudaDriverGetVersion\n");
    cudaError_t r= (*(cudaError_t (*)( int*))(func[61]))( driverVersion );
    end_func();
    return r;
}

cudaError_t cudaGetSurfaceObjectResourceDesc ( struct cudaResourceDesc* pResDesc, cudaSurfaceObject_t surfObject) {
        
    init_func();
    printf("cudaGetSurfaceObjectResourceDesc\n");
    cudaError_t r= (*(cudaError_t (*)( struct cudaResourceDesc* , cudaSurfaceObject_t))(func[62]))( pResDesc,  surfObject );
    end_func();
    return r;
}

cudaError_t cudaDestroySurfaceObject ( cudaSurfaceObject_t surfObject) {
        
    init_func();
    printf("cudaDestroySurfaceObject\n");
    cudaError_t r= (*(cudaError_t (*)( cudaSurfaceObject_t))(func[63]))( surfObject );
    end_func();
    return r;
}

cudaError_t cudaCreateSurfaceObject ( cudaSurfaceObject_t* pSurfObject, const struct cudaResourceDesc* pResDesc) {
        
    init_func();
    printf("cudaCreateSurfaceObject\n");
    cudaError_t r= (*(cudaError_t (*)( cudaSurfaceObject_t* ,  const struct cudaResourceDesc* ))(func[64]))( pSurfObject, pResDesc );
    end_func();
    return r;
}

cudaError_t cudaGetTextureObjectTextureDesc ( struct cudaTextureDesc* pTexDesc, cudaTextureObject_t texObject) {
    
    init_func();
    printf("cudaGetTextureObjectTextureDesc\n");
    cudaError_t r= (*(cudaError_t (*)( struct cudaTextureDesc* ,  cudaTextureObject_t ))(func[65]))( pTexDesc, texObject);
    end_func();
    return r;
}

cudaError_t cudaGetTextureObjectResourceViewDesc ( struct cudaResourceViewDesc* pResViewDesc, cudaTextureObject_t texObject) {
        
    init_func();
    printf("cudaGetTextureObjectResourceViewDesc\n");
    cudaError_t r= (*(cudaError_t (*)( struct cudaResourceViewDesc* ,  cudaTextureObject_t ))(func[66]))( pResViewDesc, texObject);
    end_func();
    return r;
}

cudaError_t cudaGetTextureObjectResourceDesc ( struct cudaResourceDesc* pResDesc, cudaTextureObject_t texObject) {
        
    init_func();
    printf("cudaGetTextureObjectResourceDesc\n");
    cudaError_t r= (*(cudaError_t (*)(  struct cudaResourceDesc* ,  cudaTextureObject_t ))(func[67]))( pResDesc, texObject);
    end_func();
    return r;
}

cudaError_t cudaGetChannelDesc ( struct cudaChannelFormatDesc* desc, cudaArray_const_t array) {
        
    init_func();
    printf("cudaGetChannelDesc\n");
    cudaError_t r= (*(cudaError_t (*)(  struct cudaChannelFormatDesc* ,  cudaArray_const_t ))(func[68]))( desc, array);
    end_func();
    return r;
}

cudaError_t cudaDestroyTextureObject ( cudaTextureObject_t texObject) {
        
    init_func();
    printf("cudaDestroyTextureObject\n");
    cudaError_t r= (*(cudaError_t (*)(cudaTextureObject_t ))(func[69]))( texObject);
    end_func();
    return r;
}

cudaError_t cudaCreateTextureObject ( cudaTextureObject_t* pTexObject, const struct cudaResourceDesc* pResDesc, const struct cudaTextureDesc* pTexDesc, const struct cudaResourceViewDesc* pResViewDesc) {
        
    init_func();
    printf("cudaCreateTextureObject\n");
    cudaError_t r= (*(cudaError_t (*)(cudaTextureObject_t* , const struct cudaResourceDesc* , const struct cudaTextureDesc* , const struct cudaResourceViewDesc* ))(func[70]))( pTexObject, pResDesc, pTexDesc, pResViewDesc);
    end_func();
    return r;
}

cudaError_t cudaGraphicsUnregisterResource ( cudaGraphicsResource_t resource) {
        
    init_func();
    printf("cudaGraphicsUnregisterResource\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphicsResource_t ))(func[71]))(resource);
    end_func();
    return r;
}

cudaError_t cudaGraphicsUnmapResources ( int count, cudaGraphicsResource_t* resources, cudaStream_t stream) {
        
    init_func();
    printf("cudaGraphicsUnmapResources\n");
    cudaError_t r= (*(cudaError_t (*)(int ,cudaGraphicsResource_t*, cudaStream_t))(func[72]))(count, resources, stream);
    end_func();
    return r;
}

cudaError_t cudaGraphicsSubResourceGetMappedArray ( cudaArray_t* array, cudaGraphicsResource_t resource, unsigned int arrayIndex, unsigned int mipLevel) {
        
    init_func();
    printf("cudaGraphicsSubResourceGetMappedArray\n");
    cudaError_t r= (*(cudaError_t (*)(cudaArray_t* ,cudaGraphicsResource_t, unsigned int , unsigned int))(func[73]))(array, resource, arrayIndex, mipLevel);
    end_func();
    return r;
}

cudaError_t cudaGraphicsResourceSetMapFlags ( cudaGraphicsResource_t resource, unsigned int  flags) {
        
    init_func();
    printf("cudaGraphicsResourceSetMapFlags\n");
    cudaError_t r= (*(cudaError_t (*)(cudaGraphicsResource_t, unsigned int))(func[74]))( resource, flags);
    end_func();
    return r;
}

cudaError_t cudaGraphicsResourceGetMappedPointer ( void** devPtr, size_t* size, cudaGraphicsResource_t resource) {
        
    init_func();
    printf("cudaGraphicsResourceGetMappedPointer\n");
    cudaError_t r= (*(cudaError_t (*)(void** , size_t*,cudaGraphicsResource_t))(func[75]))( devPtr, size, resource);
    end_func();
    return r;
}

cudaError_t cudaGraphicsResourceGetMappedMipmappedArray ( cudaMipmappedArray_t* mipmappedArray, cudaGraphicsResource_t resource) {
        
    init_func();
    printf("cudaGraphicsResourceGetMappedMipmappedArray\n");
    cudaError_t r= (*(cudaError_t (*)(cudaMipmappedArray_t* , cudaGraphicsResource_t))(func[76]))( mipmappedArray, resource);
    end_func();
    return r;
}

cudaError_t cudaGraphicsMapResources ( int count, cudaGraphicsResource_t* resources, cudaStream_t stream) {
        
    init_func();
    printf("cudaGraphicsMapResources\n");
    cudaError_t r= (*(cudaError_t (*)(int , cudaGraphicsResource_t* , cudaStream_t))(func[77]))( count, resources, stream);
    end_func();
    return r;
}

cudaError_t cudaDeviceEnablePeerAccess ( int peerDevice, unsigned int flags) {
        
    init_func();
    printf("cudaDeviceEnablePeerAccess\n");
    cudaError_t r= (*(cudaError_t (*)(int, unsigned int ))(func[78]))(peerDevice,flags);
    //dlclose(handle);
    return r;
}

cudaError_t cudaDeviceDisablePeerAccess ( int peerDevice) {
        
    init_func();
    printf("cudaDeviceDisablePeerAccess\n");
    cudaError_t r= (*(cudaError_t (*)(int ))(func[79]))(peerDevice);
    end_func();
    return r;
}

cudaError_t cudaDeviceCanAccessPeer ( int* canAccessPeer, int device, int peerDevice) {
        
    init_func();
    printf("cudaDeviceCanAccessPeer\n");
    cudaError_t r= (*(cudaError_t (*)(int*, int, int))(func[80]))(canAccessPeer,device, peerDevice);
    end_func();
    return r;
}

cudaError_t cudaPointerGetAttributes ( struct cudaPointerAttributes* attributes, const void* ptr) {
        
    init_func();
    printf("cudaPointerGetAttributes\n");
    cudaError_t r= (*(cudaError_t (*)(struct cudaPointerAttributes* , const void* ))(func[81]))( attributes,ptr);
    end_func();
    return r;
}

cudaError_t cudaMemset3DAsync ( struct cudaPitchedPtr pitchedDevPtr, int  value, struct cudaExtent extent, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemset3DAsync\n");
    cudaError_t r= (*(cudaError_t (*)(struct cudaPitchedPtr, int, struct cudaExtent, cudaStream_t ))(func[82]))( pitchedDevPtr,value, extent, stream);
    end_func();
    return r;
}

cudaError_t cudaMemset3D ( struct cudaPitchedPtr pitchedDevPtr, int value, struct cudaExtent extent) {
        
    init_func();
    printf("cudaMemset3D\n");
    cudaError_t r= (*(cudaError_t (*)(struct cudaPitchedPtr, int, struct cudaExtent ))(func[83]))( pitchedDevPtr,value, extent);
    end_func();
    return r;
}

cudaError_t cudaMemset2DAsync( void* devPtr, size_t pitch, int  value, size_t width, size_t height, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemset2DAsync\n");
    cudaError_t r= (*(cudaError_t (*)(void* ,size_t, int , size_t, size_t, cudaStream_t ))(func[84]))(devPtr,pitch, value,width, height, stream);
    end_func();
    return r;
}

cudaError_t cudaMemset2D ( void* devPtr, size_t pitch, int  value, size_t width, size_t height) {
        
    init_func();
    printf("cudaMemset2D\n");
    cudaError_t r= (*(cudaError_t (*)(void* ,size_t, int , size_t, size_t ))(func[85]))(devPtr,pitch, value,width, height);
    end_func();
    return r;
}

cudaError_t cudaMemset (void* devPtr, int value, size_t count) {
    
    init_func();
    printf("cudaMemset\n");
    cudaError_t r= (*(cudaError_t (*)(void* , int , size_t ))(func[86]))(devPtr, value,count);
    end_func();
    return r;
}

cudaError_t cudaMemcpyToSymbolAsync(const void* symbol, const void* src, size_t count, size_t offset, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemcpyToSymbolAsync\n");
    cudaError_t r= (*(cudaError_t (*)(const void* , const void* , size_t, size_t, enum cudaMemcpyKind, cudaStream_t))(func[87]))( symbol, src, count,offset, kind, stream);
    end_func();
    return r;
}

cudaError_t cudaMemcpyToSymbol ( const void* symbol, const void* src, size_t count, size_t offset, enum cudaMemcpyKind kind) {
        
    init_func();
    printf("cudaMemcpyToSymbol\n");
    cudaError_t r= (*(cudaError_t (*)(const void* , const void* , size_t, size_t, enum cudaMemcpyKind))(func[88]))( symbol, src, count,offset, kind);
    end_func();
    return r;
}

cudaError_t cudaMemcpyPeerAsync( void* dst, int dstDevice, const void* src, int srcDevice, size_t count, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemcpyPeerAsync\n");
    cudaError_t r= (*(cudaError_t (*)(void* , int , const void*, int, size_t, cudaStream_t))(func[89]))(dst, dstDevice, src,srcDevice, count, stream);
    end_func();
    return r;
}

cudaError_t cudaMemcpyPeer ( void* dst, int dstDevice, const void* src, int srcDevice, size_t count) {
        
    init_func();
    printf("cudaMemcpyPeer\n");
    cudaError_t r= (*(cudaError_t (*)(void*, int , const void* , int, size_t))(func[90]))( dst, dstDevice, src,srcDevice, count);
    end_func();
    return r;
}

cudaError_t cudaMemcpyFromSymbolAsync ( void* dst, const void* symbol, size_t count, size_t offset, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemcpyFromSymbolAsync\n");
    cudaError_t r= (*(cudaError_t (*)(void* , const void* , size_t, size_t, enum cudaMemcpyKind, cudaStream_t))(func[91]))( dst, symbol, count, offset,  kind, stream);
    end_func();
    return r;
}

cudaError_t cudaMemcpyFromSymbol( void* dst, const void* symbol, size_t count, size_t offset , enum cudaMemcpyKind kind) {
        
    init_func();
    printf("cudaMemcpyFromSymbol\n");
    cudaError_t r= (*(cudaError_t (*)(void* , const void* , size_t , size_t , enum cudaMemcpyKind))(func[92]))( dst, symbol, count,offset,kind);
    end_func();
    return r;
}

cudaError_t cudaMemcpy3DPeerAsync ( const struct cudaMemcpy3DPeerParms* p, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemcpy3DPeerAsync\n");
    cudaError_t r= (*(cudaError_t (*)(const struct cudaMemcpy3DPeerParms*, cudaStream_t))(func[93]))(p, stream);
    end_func();
    return r;
}

cudaError_t cudaMemcpy3DPeer ( const struct cudaMemcpy3DPeerParms* p) {
        
    init_func();
    printf("cudaMemcpy3DPeer\n");
    cudaError_t r= (*(cudaError_t (*)(const struct cudaMemcpy3DPeerParms* ))(func[94]))(p);
    end_func();
    return r;
}

cudaError_t cudaMemcpy3DAsync ( const struct cudaMemcpy3DParms* p, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemcpy3DAsync\n");
    cudaError_t r= (*(cudaError_t (*)(const struct cudaMemcpy3DParms*, cudaStream_t ))(func[95]))(p, stream);
    end_func();
    return r;
}

cudaError_t cudaMemcpy3D ( const struct cudaMemcpy3DParms* p) {
        
    init_func();
    printf("cudaMemcpy3D\n");
    cudaError_t r= (*(cudaError_t (*)(const struct cudaMemcpy3DParms* ))(func[96]))(p);
    end_func();
    return r;
}

cudaError_t cudaMemcpy2DToArrayAsync ( cudaArray_t dst, size_t wOffset, size_t hOffset, const void* src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemcpy2DToArrayAsync\n");
    cudaError_t r= (*(cudaError_t (*)(cudaArray_t , size_t , size_t, const void*, size_t, size_t, size_t, enum cudaMemcpyKind, cudaStream_t ))(func[97]))( dst,wOffset, hOffset, src,spitch, width,height, kind, stream);
    end_func();
    return r;
}

cudaError_t cudaMemcpy2DToArray ( cudaArray_t dst, size_t wOffset, size_t hOffset, const void* src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind) {
        
    init_func();
    printf("cudaMemcpy2DToArray\n");
    cudaError_t r= (*(cudaError_t (*)(cudaArray_t , size_t , size_t, const void*, size_t, size_t, size_t, enum cudaMemcpyKind ))(func[98]))( dst,wOffset, hOffset, src,spitch, width,height, kind);
    end_func();
    return r;
}

cudaError_t cudaMemcpy2DFromArrayAsync ( void* dst, size_t dpitch, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t width, size_t height, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemcpy2DFromArrayAsync\n");
    cudaError_t r= (*(cudaError_t (*)(void* , size_t , cudaArray_const_t, size_t, size_t, size_t, size_t, enum cudaMemcpyKind, cudaStream_t ))(func[99]))( dst, dpitch, src, wOffset, hOffset,width,height, kind, stream);
    end_func();
    return r;
}

cudaError_t cudaMemcpy2DFromArray ( void* dst, size_t dpitch, cudaArray_const_t src, size_t wOffset, size_t hOffset, size_t width, size_t height, enum cudaMemcpyKind kind) {
        
    init_func();
    printf("cudaMemcpy2DFromArray\n");
    cudaError_t r= (*(cudaError_t (*)(void* , size_t , cudaArray_const_t, size_t, size_t, size_t, size_t, enum cudaMemcpyKind ))(func[100]))( dst, dpitch, src, wOffset, hOffset,width,height, kind);
    end_func();
    return r;
}

cudaError_t cudaMemcpy2DAsync ( void* dst, size_t dpitch, const void* src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemcpy2DAsync\n");
    cudaError_t r= (*(cudaError_t (*)(void* , size_t, const void* , size_t, size_t, size_t, enum cudaMemcpyKind, cudaStream_t ))(func[101]))( dst, dpitch, src, spitch,width,height, kind, stream);
    end_func();
    return r;
}

cudaError_t cudaMemcpy2DArrayToArray ( cudaArray_t dst, size_t wOffsetDst, size_t hOffsetDst, cudaArray_const_t src, size_t wOffsetSrc, size_t hOffsetSrc, size_t width, size_t height, enum cudaMemcpyKind kind) {
        
    init_func();
    printf("cudaMemcpy2DArrayToArray\n");
    cudaError_t r= (*(cudaError_t (*)(cudaArray_t , size_t, size_t, cudaArray_const_t, size_t, size_t, size_t, size_t, enum cudaMemcpyKind ))(func[102]))( dst, wOffsetDst, hOffsetDst, src, wOffsetSrc,hOffsetSrc,width,height, kind);
    end_func();
    return r;
}

cudaError_t cudaMemcpy2D ( void* dst, size_t dpitch, const void* src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind) {
        
    init_func();
    printf("cudaMemcpy2D\n");
    cudaError_t r= (*(cudaError_t (*)(void* , size_t, const void* , size_t, size_t, size_t, enum cudaMemcpyKind ))(func[103]))( dst, dpitch, src, spitch,width,height, kind);
    end_func();
    return r;
}

cudaError_t cudaMemcpy ( void* dst, const void* src, size_t count, enum cudaMemcpyKind kind) {
        
    init_func();
    //printf("cudaMemcpy\n");
    cudaError_t r= (*(cudaError_t (*)(void* , const void* , size_t, enum cudaMemcpyKind ))(func[104]))( dst, src, count, kind);
    end_func();
    return r;
}

cudaError_t cudaMemRangeGetAttributes ( void** data, size_t* dataSizes, enum cudaMemRangeAttribute *attributes, size_t numAttributes, const void* devPtr, size_t count) {
        
    init_func();
    printf("cudaMemRangeGetAttributes\n");
    cudaError_t r= (*(cudaError_t (*)(void** , size_t* , enum cudaMemRangeAttribute *, size_t, const void*, size_t ))(func[105]))( data, dataSizes, attributes, numAttributes , devPtr, count);
    end_func();
    return r;
}

cudaError_t cudaMemRangeGetAttribute ( void* data, size_t dataSize, enum cudaMemRangeAttribute attribute, const void* devPtr, size_t count) {
        
    init_func();
    printf("cudaMemRangeGetAttribute\n");
    cudaError_t r= (*(cudaError_t (*)(void* , size_t , enum cudaMemRangeAttribute, const void* , size_t ))(func[106]))( data, dataSize, attribute, devPtr, count);
    end_func();
    return r;
}

cudaError_t cudaMemPrefetchAsync ( const void* devPtr, size_t count, int  dstDevice, cudaStream_t stream) {
        
    init_func();
    printf("cudaMemPrefetchAsync\n");
    cudaError_t r= (*(cudaError_t (*)(const void* , size_t , int  , cudaStream_t ))(func[107]))(devPtr, count, dstDevice, stream);
    end_func();
    return r;
}

cudaError_t cudaMemAdvise ( const void* devPtr, size_t count, enum cudaMemoryAdvise advice, int  device) {
        
    init_func();
    printf("cudaMemAdvise\n");
    cudaError_t r= (*(cudaError_t (*)(const void*, size_t, enum cudaMemoryAdvise, int ))(func[108]))( devPtr, count, advice, device);
    end_func();
    return r;
}

cudaError_t cudaHostUnregister ( void* ptr) {
        
    init_func();
    printf("cudaHostUnregister\n");
    cudaError_t r= (*(cudaError_t (*)(void* ))(func[109]))(ptr);
    end_func();
    return r;
}

cudaError_t cudaHostRegister ( void* ptr, size_t size, unsigned int  flags) {
        
    init_func();
    printf("cudaHostRegister\n");
    cudaError_t r= (*(cudaError_t (*)(void* , size_t, unsigned int ))(func[110]))(ptr,size, flags);
    end_func();
    return r;
}

cudaError_t cudaHostGetFlags ( unsigned int* pFlags, void* pHost) {
        
    init_func();
    printf("cudaHostGetFlags\n");
    cudaError_t r= (*(cudaError_t (*)(unsigned int* , void* ))(func[111]))(pFlags, pHost);
    end_func();
    return r;
}

cudaError_t cudaGetSymbolSize ( size_t* size, const void* symbol) {
        
    init_func();
    printf("cudaGetSymbolSize\n");
    cudaError_t r= (*(cudaError_t (*)(size_t* , const void* ))(func[112]))(size, symbol);
    end_func();
    return r;
}

cudaError_t cudaGetSymbolAddress ( void** devPtr, const void* symbol) {
        
    init_func();
    printf("cudaGetSymbolAddress\n");
    cudaError_t r= (*(cudaError_t (*)(void** , const void* ))(func[113]))(devPtr, symbol);
    end_func();
    return r;
}

cudaError_t cudaGetMipmappedArrayLevel (cudaArray_t* levelArray, cudaMipmappedArray_const_t mipmappedArray, unsigned int level) {
        
    init_func();
    printf("cudaGetMipmappedArrayLevel\n");
    cudaError_t r= (*(cudaError_t (*)(cudaArray_t* , cudaMipmappedArray_const_t, unsigned int ))(func[114]))( levelArray, mipmappedArray, level);
    end_func();
    return r;
}

cudaError_t cudaFreeMipmappedArray ( cudaMipmappedArray_t mipmappedArray) {
        
    init_func();
    printf("cudaFreeMipmappedArray\n");
    cudaError_t r= (*(cudaError_t (*)(cudaMipmappedArray_t ))(func[115]))( mipmappedArray);
    end_func();
    return r;
}

cudaError_t cudaFreeArray ( cudaArray_t array) {
        
    init_func();
    printf("cudaFreeArray\n");
    cudaError_t r= (*(cudaError_t (*)(cudaArray_t ))(func[116]))( array);
    end_func();
    return r;
}

cudaError_t cudaArrayGetInfo ( struct cudaChannelFormatDesc* desc, struct cudaExtent* extent, unsigned int* flags, cudaArray_t array) {
        
    init_func();
    printf("cudaArrayGetInfo\n");
    cudaError_t r= (*(cudaError_t (*)(struct cudaChannelFormatDesc* , struct cudaExtent* , unsigned int* , cudaArray_t ))(func[117]))( desc, extent, flags, array);
    end_func();
    return r;
}

cudaError_t cudaOccupancyMaxActiveBlocksPerMultiprocessor ( int* numBlocks, const void* func, int blockSize, size_t dynamicSMemSize) {
        
    init_func();
    printf("cudaOccupancyMaxActiveBlocksPerMultiprocessor\n");
    cudaError_t r= (*(cudaError_t (*)(int* , const void* , int , size_t ))(func2[3]))( numBlocks, func, blockSize, dynamicSMemSize);
    end_func();
    return r;
}

cudaError_t cudaSetDoubleForHost ( double* d) {
        
    init_func();
    printf("cudaSetDoubleForHost\n");
    cudaError_t r= (*(cudaError_t (*)(double* ))(func[119]))(d);
    end_func();
    return r;
}

cudaError_t cudaSetDoubleForDevice ( double* d) {
        
    init_func();
    printf("cudaSetDoubleForDevice\n");
    cudaError_t r= (*(cudaError_t (*)(double* ))(func[120]))(d);
    end_func();
    return r;
}

cudaError_t cudaLaunchHostFunc ( cudaStream_t stream, cudaHostFn_t fn, void* userData) {
        
    init_func();
    printf("cudaLaunchHostFunc\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t , cudaHostFn_t , void* ))(func[121]))( stream, fn, userData);
    end_func();
    return r;
}

cudaError_t cudaLaunchCooperativeKernelMultiDevice ( struct cudaLaunchParams* launchParamsList, unsigned int  numDevices, unsigned int  flags) {
        
    init_func();
    printf("cudaLaunchCooperativeKernelMultiDevice\n");
    cudaError_t r= (*(cudaError_t (*)(struct cudaLaunchParams* , unsigned int , unsigned int ))(func[122]))( launchParamsList, numDevices, flags);
    end_func();
    return r;
}

cudaError_t cudaLaunchCooperativeKernel( const void* func, dim3 gridDim, dim3 blockDim, void** args, size_t sharedMem, cudaStream_t stream) {
    
    init_func();
    printf("cudaLaunchCooperativeKernel\n");
    cudaError_t r= (*(cudaError_t (*)(const void* , dim3 , dim3 , void** , size_t , cudaStream_t ))(func2[4]))( func,  gridDim,  blockDim,  args, sharedMem, stream);
    end_func();
    return r;
}

/*void* cudaGetParameterBufferV2 ( void* func, dim3 gridDimension, dim3 blockDimension, unsigned int  sharedMemSize) {
        
    init_func();
    printf("cudaGetParameterBufferV2\n");
    void* r= (*(void* (*)(void* , dim3 , dim3 , unsigned int ))(func2[5]))(func, gridDimension, blockDimension, sharedMemSize);
    end_func();
    return r;
}

void* cudaGetParameterBuffer ( size_t alignment, size_t size) {
        
    init_func();
    printf("cudaGetParameterBuffer\n");
    void* r= (*(void* (*)(size_t , size_t  ))(func[125]))(alignment, size);
    end_func();
    return r;
}*/

cudaError_t cudaFuncSetSharedMemConfig ( const void* func, enum cudaSharedMemConfig config) {
        
    init_func();
    printf("cudaFuncSetSharedMemConfig\n");
    cudaError_t r= (*(cudaError_t (*)(const void* , enum cudaSharedMemConfig ))(func2[6]))( func, config);
    end_func();
    return r;
}

cudaError_t cudaFuncSetCacheConfig ( const void* func, enum cudaFuncCache cacheConfig) {
        
    init_func();
    printf("cudaFuncSetCacheConfig\n");
    cudaError_t r= (*(cudaError_t (*)(const void* , enum cudaFuncCache ))(func2[7]))( func, cacheConfig);
    end_func();
    return r;
}

cudaError_t cudaFuncSetAttribute ( const void* func, enum cudaFuncAttribute attr, int  value) {
        
    init_func();
    printf("cudaFuncSetAttribute\n");
    cudaError_t r= (*(cudaError_t (*)(const void* , enum cudaFuncAttribute, int ))(func2[8]))( func, attr, value);
    end_func();
    return r;
}

cudaError_t cudaWaitExternalSemaphoresAsync ( const cudaExternalSemaphore_t* extSemArray, const struct cudaExternalSemaphoreWaitParams* paramsArray, unsigned int numExtSems, cudaStream_t stream) {
        
    init_func();
    printf("cudaWaitExternalSemaphoresAsync\n");
    cudaError_t r= (*(cudaError_t (*)(const cudaExternalSemaphore_t* , const struct cudaExternalSemaphoreWaitParams* , unsigned int , cudaStream_t ))(func[129]))( extSemArray, paramsArray, numExtSems, stream);
    end_func();
    return r;
}

cudaError_t cudaSignalExternalSemaphoresAsync ( const cudaExternalSemaphore_t* extSemArray, const struct cudaExternalSemaphoreSignalParams* paramsArray, unsigned int numExtSems, cudaStream_t stream) {
        
    init_func();
    printf("cudaSignalExternalSemaphoresAsync\n");
    cudaError_t r= (*(cudaError_t (*)(const cudaExternalSemaphore_t* , const struct cudaExternalSemaphoreSignalParams* , unsigned int , cudaStream_t ))(func[130]))( extSemArray, paramsArray, numExtSems, stream);
    end_func();
    return r;
}

cudaError_t cudaImportExternalSemaphore ( cudaExternalSemaphore_t* extSem_out, const struct cudaExternalSemaphoreHandleDesc* semHandleDesc) {
        
    init_func();
    printf("cudaImportExternalSemaphore\n");
    cudaError_t r= (*(cudaError_t (*)(cudaExternalSemaphore_t* , const struct cudaExternalSemaphoreHandleDesc* ))(func[131]))( extSem_out, semHandleDesc);
    end_func();
    return r;
}

cudaError_t cudaImportExternalMemory ( cudaExternalMemory_t* extMem_out, const struct cudaExternalMemoryHandleDesc* memHandleDesc) {
        
    init_func();
    printf("cudaImportExternalMemory\n");
    cudaError_t r= (*(cudaError_t (*)(cudaExternalMemory_t* , const struct cudaExternalMemoryHandleDesc* ))(func[132]))( extMem_out, memHandleDesc);
    end_func();
    return r;
}

cudaError_t cudaExternalMemoryGetMappedMipmappedArray ( cudaMipmappedArray_t* mipmap, cudaExternalMemory_t extMem, const struct cudaExternalMemoryMipmappedArrayDesc* mipmapDesc) {
        
    init_func();
    printf("cudaExternalMemoryGetMappedMipmappedArray\n");
    cudaError_t r= (*(cudaError_t (*)(cudaMipmappedArray_t* , cudaExternalMemory_t , const struct cudaExternalMemoryMipmappedArrayDesc* ))(func[133]))( mipmap, extMem, mipmapDesc);
    end_func();
    return r;
}

cudaError_t cudaExternalMemoryGetMappedBuffer ( void** devPtr, cudaExternalMemory_t extMem, const struct cudaExternalMemoryBufferDesc* bufferDesc) {
        
    init_func();
    printf("cudaExternalMemoryGetMappedBuffer\n");
    cudaError_t r= (*(cudaError_t (*)(void** , cudaExternalMemory_t , const struct cudaExternalMemoryBufferDesc* ))(func[134]))( devPtr, extMem, bufferDesc);
    end_func();
    return r;
}

cudaError_t cudaDestroyExternalSemaphore ( cudaExternalSemaphore_t extSem) {
        
    init_func();
    printf("cudaDestroyExternalSemaphore\n");
    cudaError_t r= (*(cudaError_t (*)(cudaExternalSemaphore_t ))(func[135]))( extSem);
    end_func();
    return r;
}

cudaError_t cudaDestroyExternalMemory ( cudaExternalMemory_t extMem) {
        
    init_func();
    printf("cudaDestroyExternalMemory\n");
    cudaError_t r= (*(cudaError_t (*)(cudaExternalMemory_t ))(func[136]))( extMem);
    end_func();
    return r;
}

cudaError_t cudaEventSynchronize ( cudaEvent_t event) {
        
    init_func();
    printf("cudaEventSynchronize\n");
    cudaError_t r= (*(cudaError_t (*)(cudaEvent_t ))(func[137]))( event);
    end_func();
    return r;
}

cudaError_t cudaEventQuery ( cudaEvent_t event) {
        
    init_func();
    //printf("cudaEventQuery\n");
    cudaError_t r= (*(cudaError_t (*)(cudaEvent_t ))(func[138]))( event);
    end_func();
    return r;
}

cudaError_t cudaEventElapsedTime ( float* ms, cudaEvent_t start, cudaEvent_t end) {
        
    init_func();
    printf("cudaEventElapsedTime\n");
    cudaError_t r= (*(cudaError_t (*)(float* , cudaEvent_t , cudaEvent_t ))(func[139]))( ms, start, end);
    end_func();
    return r;
}

cudaError_t cudaEventCreate ( cudaEvent_t* event) {
        
    init_func();
    printf("cudaEventCreate:\n");
    cudaError_t r= (*(cudaError_t (*)(cudaEvent_t* ))(func[140]))(event);
    end_func();
    return r;
}

cudaError_t cudaStreamWaitEvent ( cudaStream_t stream, cudaEvent_t event, unsigned int  flags) {
        
    init_func();
    //printf("cudaStreamWaitEvent\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t, cudaEvent_t, unsigned int ))(func[141]))(stream,event,flags);
    end_func();
    return r;
}

cudaError_t cudaStreamQuery ( cudaStream_t stream) {
        
    init_func();
    printf("cudaStreamQuery\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t ))(func[142]))(stream);
    end_func();
    return r;
}

cudaError_t cudaStreamIsCapturing(cudaStream_t stream, enum cudaStreamCaptureStatus *pCaptureStatus) {
        
    init_func();
    printf("cudaStreamIsCapturing\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t, enum cudaStreamCaptureStatus * ))(func[143]))( stream, pCaptureStatus);
    end_func();
    return r;
}

cudaError_t cudaStreamGetPriority ( cudaStream_t hStream, int* priority) {
        
    init_func();
    printf("cudaStreamGetPriority\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t , int* ))(func[144]))(hStream, priority);
    end_func();
    return r;
}

cudaError_t cudaStreamGetFlags( cudaStream_t hStream, unsigned int* flags) {
        
    init_func();
    printf("cudaStreamGetFlags\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t , unsigned int* ))(func[145]))(hStream, flags);
    end_func();
    return r;
}

/*cudaError_t cudaStreamGetCaptureInfo ( cudaStream_t stream, enum cudaStreamCaptureStatus ** pCaptureStatus, unsigned long long* pId) {
        
    init_func();
    printf("cudaStreamGetCaptureInfo\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t , enum cudaStreamCaptureStatus ** , unsigned long long* ))(func[146]))( stream, pCaptureStatus, pId);
    end_func();
    return r;
}*/

cudaError_t cudaStreamEndCapture ( cudaStream_t stream, cudaGraph_t* pGraph) {
        
    init_func();
    printf("cudaStreamEndCapture\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t , cudaGraph_t* ))(func[147]))( stream, pGraph);
    end_func();
    return r;
}

cudaError_t cudaStreamCreate ( cudaStream_t* pStream) {
        
    init_func();
    //printf("cudaStreamCreate\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t* ))(func[148]))( pStream);
    end_func();
    return r;
}

cudaError_t cudaStreamBeginCapture( cudaStream_t stream ) {
        
    init_func();
    printf("cudaStreamBeginCapture\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t ))(func[149]))( stream );
    end_func();
    return r;
}

cudaError_t cudaStreamAttachMemAsync(cudaStream_t stream, void* devPtr, size_t length, unsigned int  flags) {
        
    init_func();
    printf("cudaStreamAttachMemAsync\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t , void* , size_t , unsigned int))(func[150]))( stream, devPtr, length, flags);
    end_func();
    return r;
}

cudaError_t cudaStreamAddCallback( cudaStream_t stream, cudaStreamCallback_t callback, void* userData, unsigned int  flags) {
        
    init_func();
    printf("cudaStreamAddCallback\n");
    cudaError_t r= (*(cudaError_t (*)(cudaStream_t , cudaStreamCallback_t , void* , unsigned int))(func[151]))(stream,  callback, userData,flags);
    end_func();
    return r;
}

cudaError_t cudaPeekAtLastError () {
        
    init_func();
    //printf("cudaPeekAtLastError\n");
    cudaError_t r= (*(cudaError_t (*)(void ))(func[152]))();
    end_func();
    return r;
}

const char* cudaGetErrorString ( cudaError_t err) {
        
    init_func();
    printf("cudaGetErrorString\n");
    const char* r= (*(const char* (*)(cudaError_t ))(func[153]))( err );
    end_func();
    return r;
}

const char* cudaGetErrorName ( cudaError_t err ) {
        
    init_func();
    printf("cudaGetErrorName\n");
    const char* r= (*(const char* (*)(cudaError_t ))(func[154]))( err );
    end_func();
    return r;
}

cudaError_t cudaSetValidDevices( int* device_arr, int  len) {
        
    init_func();
    printf("cudaSetValidDevices\n");
    cudaError_t r= (*(cudaError_t (*)(int* , int ))(func[155]))(device_arr, len);
    end_func();
    return r;
}

cudaError_t cudaSetDeviceFlags( unsigned int  flags) {
        
    init_func();
    printf("cudaSetDeviceFlags\n");
    cudaError_t r= (*(cudaError_t (*)(unsigned int ))(func[156]))( flags);
    end_func();
    return r;
}

cudaError_t cudaIpcOpenMemHandle( void** devPtr, cudaIpcMemHandle_t hand, unsigned int  flags) {
        
    init_func();
    printf("cudaIpcOpenMemHandle\n");
    cudaError_t r= (*(cudaError_t (*)(void** , cudaIpcMemHandle_t , unsigned int))(func[157]))( devPtr, hand, flags);
    end_func();
    return r;
}

cudaError_t cudaIpcOpenEventHandle( cudaEvent_t* event,  cudaIpcEventHandle_t hand) {
        
    init_func();
    printf("cudaIpcOpenEventHandle\n");
    cudaError_t r= (*(cudaError_t (*)(cudaEvent_t* , cudaIpcEventHandle_t ))(func[158]))( event, hand);
    end_func();
    return r;
}

cudaError_t cudaIpcGetMemHandle( cudaIpcMemHandle_t* handle, void* devPtr) {
        
    init_func();
    printf("cudaIpcGetMemHandle\n");
    cudaError_t r= (*(cudaError_t (*)(cudaIpcMemHandle_t* , void* ))(func[159]))( handle, devPtr);
    end_func();
    return r;
}

cudaError_t cudaIpcGetEventHandle( cudaIpcEventHandle_t* handle, cudaEvent_t event) {
        
    init_func();
    printf("cudaIpcGetEventHandle\n");
    cudaError_t r= (*(cudaError_t (*)(cudaIpcEventHandle_t* , cudaEvent_t ))(func[160]))( handle, event);
    end_func();
    return r;
}

cudaError_t cudaIpcCloseMemHandle( void* devPtr) {
        
    init_func();
    printf("cudaIpcCloseMemHandle\n");
    cudaError_t r= (*(cudaError_t (*)(void* ))(func[161]))(devPtr);
    end_func();
    return r;
}

cudaError_t cudaGetDeviceFlags( unsigned int* flags ) {
        
    init_func();
    printf("cudaGetDeviceFlags\n");
    cudaError_t r= (*(cudaError_t (*)(unsigned int* ))(func[162]))(flags);
    end_func();
    return r;
}

cudaError_t cudaDeviceSynchronize() {
        
    init_func();
    printf("cudaDeviceSynchronize\n");
    cudaError_t r= (*(cudaError_t (*)(void ))(func[163]))();
    end_func();
    return r;
}

cudaError_t cudaDeviceSetSharedMemConfig( enum cudaSharedMemConfig config) {
        
    init_func();
    printf("cudaDeviceSetSharedMemConfig\n");
    cudaError_t r= (*(cudaError_t (*)(enum cudaSharedMemConfig ))(func[164]))(config);
    end_func();
    return r;
}

cudaError_t cudaDeviceSetLimit( enum cudaLimit limit, size_t value) {
        
    init_func();
    //printf("cudaDeviceSetLimit\n");
    cudaError_t r= (*(cudaError_t (*)(enum cudaLimit, size_t ))(func[165]))(limit, value);
    end_func();
    return r;
}

cudaError_t cudaDeviceSetCacheConfig( enum cudaFuncCache cacheConfig) {
        
    init_func();
    printf("cudaDeviceSetCacheConfig\n");
    cudaError_t r= (*(cudaError_t (*)(enum cudaFuncCache ))(func[166]))( cacheConfig);
    end_func();
    return r;
}

cudaError_t cudaDeviceReset () {
        
    init_func();
    printf("cudaDeviceReset\n");
    cudaError_t r= (*(cudaError_t (*)(void ))(func[167]))();
    end_func();
    return r;
}

cudaError_t cudaDeviceGetSharedMemConfig( enum cudaSharedMemConfig * pConfig) {
        
    init_func();
    printf("cudaDeviceGetSharedMemConfig\n");
    cudaError_t r= (*(cudaError_t (*)(enum cudaSharedMemConfig * ))(func[168]))( pConfig);
    end_func();
    return r;
}

cudaError_t cudaDeviceGetPCIBusId(char* pciBusId, int len, int device) {
        
    init_func();
    printf("cudaDeviceGetPCIBusId\n");
    cudaError_t r= (*(cudaError_t (*)(char* , int, int ))(func[169]))( pciBusId, len, device);
    end_func();
    return r;
}

cudaError_t cudaDeviceGetP2PAttribute(int* value, enum cudaDeviceP2PAttr attr, int srcDevice, int dstDevice) {
        
    init_func();
    printf("cudaDeviceGetP2PAttribute\n");
    cudaError_t r= (*(cudaError_t (*)(int* , enum cudaDeviceP2PAttr, int, int ))(func[170]))( value, attr, srcDevice, dstDevice);
    end_func();
    return r;
}

cudaError_t cudaDeviceGetLimit( size_t* pValue, enum cudaLimit limit ) {
        
    init_func();
    //printf("cudaDeviceGetLimit\n");
    cudaError_t r= (*(cudaError_t (*)(size_t* , enum cudaLimit ))(func[171]))( pValue, limit);
    end_func();
    return r;
}

cudaError_t cudaDeviceGetCacheConfig( enum cudaFuncCache * pCacheConfig ) {
        
    init_func();
    printf("cudaDeviceGetCacheConfig\n");
    cudaError_t r= (*(cudaError_t (*)(enum cudaFuncCache * ))(func[172]))( pCacheConfig);
    end_func();
    return r;
}

cudaError_t cudaDeviceGetByPCIBusId ( int* device, const char* pciBusId ) {
        
    init_func();
    printf("cudaDeviceGetByPCIBusId\n");
    cudaError_t r= (*(cudaError_t (*)(int* , const char* ))(func[173]))( device, pciBusId);
    end_func();
    return r;
}

cudaError_t cudaChooseDevice ( int* device, const struct cudaDeviceProp* prop ) {
        
    init_func();
    printf("cudaChooseDevice\n");
    cudaError_t r= (*(cudaError_t (*)(int* , const struct cudaDeviceProp* ))(func[174]))( device, prop );
    end_func();
    return r;
}

cudaError_t cudaMallocMipmappedArray(cudaMipmappedArray_t* mipmappedArray, const struct cudaChannelFormatDesc* desc, struct cudaExtent extent, unsigned int  numLevels, unsigned int flags) {

    init_func();
    printf("cudaMallocMipmappedArray\n");
    cudaError_t r= (*(cudaError_t (*)(cudaMipmappedArray_t* , const struct cudaChannelFormatDesc* , struct cudaExtent, unsigned int, unsigned int ))(func[175]))(mipmappedArray, desc, extent,numLevels, flags);
    end_func();
    return r; 
}

cudaError_t cudaMallocArray(cudaArray_t* array, const struct cudaChannelFormatDesc* desc, size_t width, size_t height, unsigned int  flags) {

    init_func();
    printf("cudaMallocArray\n");
    cudaError_t r= (*(cudaError_t (*)(cudaArray_t* , const struct cudaChannelFormatDesc* , size_t, size_t, unsigned int ))(func[176]))( array, desc,width,height,flags);
    end_func();
    return r; 
}

cudaError_t cudaMallocHost(void** ptr, size_t size) {

    init_func();
    printf("cudaMallocHost\n");
    cudaError_t r= (*(cudaError_t (*)(void**, size_t ))(func[177]))( ptr, size);
    end_func();
    return r;
}

cudaError_t cudaMalloc3DArray(cudaArray_t* array, const struct cudaChannelFormatDesc* desc, struct cudaExtent extent, unsigned int  flags) {

    init_func();
    printf("cudaMalloc3DArray\n");
    cudaError_t r= (*(cudaError_t (*)(cudaArray_t* , const struct cudaChannelFormatDesc* , struct cudaExtent, unsigned int ))(func[178]))( array, desc, extent, flags);
    end_func();
    return r;
}

cudaError_t cudaMalloc3D(struct cudaPitchedPtr* pitchedDevPtr, struct cudaExtent extent ) {

    init_func();
    printf("cudaMalloc3D\n");
    cudaError_t r= (*(cudaError_t (*)(struct cudaPitchedPtr*, struct cudaExtent ))(func[179]))( pitchedDevPtr, extent);
    end_func();
    return r;
}

cudaError_t cudaMallocManaged( void** devPtr, size_t bytesize, unsigned int flags) {
    
    init_func();
    printf("cudaMallocManaged\n");
    cudaError_t r= (*(cudaError_t (*)(void** , size_t , unsigned int))(func[180]))( devPtr, bytesize, flags);
    end_func();
    return r;
}

cudaError_t cudaMallocPitch( void** devPtr, size_t* pitch, size_t width, size_t height) {

    init_func();
    printf("cudaMallocPitch\n");
    cudaError_t r= (*(cudaError_t (*)(void** , size_t* , size_t , size_t ))(func[181]))( devPtr, pitch, width, height );
    end_func();
    return r;
}

cudaError_t cudaMemGetInfo( size_t* free , size_t* total) {
        
    init_func();
    printf("cudaMemGetInfo\n");
    cudaError_t r= (*(cudaError_t (*)(size_t* , size_t* ))(func[182]))( free, total );
    end_func();
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
