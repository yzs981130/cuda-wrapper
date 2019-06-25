mkdir -p release
gcc -I /usr/local/cuda/include/ cuda-wrapper.c -fPIC -shared -ldl -lcuda -o ./release/libcuda.so
gcc -I /usr/local/cuda/include/ cuda-wrapper2.c -fPIC -shared -ldl -lcuda -o ./release/libcuda2.so
