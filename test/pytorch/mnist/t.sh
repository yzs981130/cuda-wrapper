gcc -I /usr/local/cuda-10.0/include/ cuda-wrapper-rt.c -fPIC -shared -ldl -lcuda -o ./libcuda-rt.so
LD_PRELOAD=/workspace/rxy-wrapper/libcuda-rt.so python main.py --epochs 1
