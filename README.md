# matmul - 2x faster than numpy on M1 Pro ⚡️
```
Running version 0 (numpy)
423.842788 GFLOPs

Running version 4 (matmul)
811.098115 GFLOPs
```
## Getting started
```
Usage: ./run.sh <number>
```
The bash script compiles and executes a binary with `mul{number}.c` to measure the FLOPs of `matrix_multiply`. To run the numpy baseline (`mul0.py`), you will need to set the python command inside of `run.sh`.
## Five steps to beating numpy
### 1. Baseline (mul0) & matrix.h
We start by measuring the baseline performance of numpy for matrix multiplication. The total number of floating-point operations for multiplying two NxN matrices is 2\*N\*N*N (each cell in the NxN output matrix requires N multiplication and N addition operations). Dividing this number by the time taken to multiply the matrices gives up the FLOPs (around 400 GFLOPs on the M1 Pro). We also need to create a small matrix library for testing our implementations in C (see `matrix.h`). The matrix values are stored in row-major order in a contiguous 1d array. The matrix struct also contains the dimensions.
### 2. Naive algorithm (mul1)
The naive algorithm uses a triple for-loop setup to perform the full row-by-column multiplication for each output cell. The loop order has an impact on performance due to caching (a reoccurring theme in making this algorithm fast). We prefer to iterate over rows rather than columns because elements in a row are stored next to each other in memory, enabling spacial locality for caching. The outer loop iterates over the matrix where we access its rows, letting us repeatedly make the cache-friendly memory access.
### 3. Tiled multiply (mul2)
### 4. Transpose-then-multiply (mul3)
### 5. Fused multiply-add (mul4)
