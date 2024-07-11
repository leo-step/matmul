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
```
Running version 0
423.842788 GFLOPs
```
### 2. Naive algorithm (mul1)
The naive algorithm uses a triple for-loop setup to perform the full row-by-column multiplication for each output cell. The loop order has an impact on performance due to caching (a reoccurring theme in making this algorithm fast). We prefer to iterate over rows rather than columns because elements in a row are stored next to each other in memory, enabling spacial locality for caching. The outer loop iterates over the matrix where we access its rows, letting us repeatedly make the cache-friendly memory access.
```
Running version 1
1.614034 GFLOPs
```
_Note: you may want to decrease the matrix dimension to N=2048 because it takes too long._
### 3. Tiled multiply (mul2)
The cache won't store full rows and columns for the matrices we are multiplying, but there is a way to break down the problems into many smaller matrix multiplications. We can create partitions of size 8x8 (which I found to be optimal for performance) and perform multiplication and addition on those tiles with the naive algorithm to get the final result (see diagrams, [source](https://learn.microsoft.com/en-us/cpp/parallel/amp/walkthrough-matrix-multiplication?view=msvc-170)).

> _The matrices are partitioned into four 2x2 matrices, which are defined as follows:_<br><br>
> ![image](https://github.com/leo-step/matmul/assets/44349262/db141754-fb5d-4219-91d6-90bf1b4780ac)
> ![image](https://github.com/leo-step/matmul/assets/44349262/4fa5b7b0-4efa-4928-9091-03025e9f5703)<br><br>
> _The product of A and B can now be written and calculated as follows:_<br><br>
> ![image](https://github.com/leo-step/matmul/assets/44349262/3bafa83c-4209-4bdf-bc58-5e19d3de77fa)<br>

The data now fits into the cache, which improves the performance by a decent amount.
```
Running version 2
5.618256 GFLOPs
```
### 4. Transpose-then-multiply (mul3)
Going back to the naive algorithm, we got caching performance gains by accessing the rows of the first matrix we were multiplying, but less so on the second matrix where we access columns. By transposing the second matrix before multiplying, we can achieve a performance improvement since the columns become rows and can now be cached effectively.
```
Running version 3
2.417634 GFLOPs
```
### 5. Fused multiply-add (mul4)
