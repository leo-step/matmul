import numpy as np
import time

N = 4096
if __name__ == "__main__":
    # numpy float64 by default
    A = np.random.randn(N, N).astype(np.float32) 
    B = np.random.randn(N, N).astype(np.float32)
    # print(A.dtype)
    # for each cell, in the N^2 output, you are multiplying
    # two vectors of size N. note: its actually 2N compute
    # for each cell because you have to mul and then add

    # these are floating point ops
    flop = N*N*2*N
    # now need to get number of seconds
    # for i in range(100):
    start = time.monotonic()
    C = A @ B
    end = time.monotonic()
    print((flop*1e-12)/(end-start), "TFLOPS")
    # M1 Pro Mac, float32 - 0.5 TFLOPs
    # float64 is half as fast, and we don't need that precision
    # 10 cores (8 performance and 2 efficiency)
    # 16GB memory
    # what is theoretical TFLOPs??