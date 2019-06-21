gcc -I /usr/local/cuda-10.0/include/ cuda-wrapper.c -fPIC -shared -ldl -lcuda -o ./release/libcuda.so
gcc -I /usr/local/cuda-10.0/include/ cuda-wrapper2.c -fPIC -shared -ldl -lcuda -o ./release/libcuda2.so
