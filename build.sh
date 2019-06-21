gcc -I /usr/local/cuda-10.0/include/ cuda-wrapper.c -fPIC -shared -ldl -lcuda -o ./release/libcuda.so
