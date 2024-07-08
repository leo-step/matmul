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
