# Python Optimization and Language Binding

Example code for calculating the angle between two celestial objects, implemented as follows:

Description | Source
---------|----------
Pure Python code | angle_between_two_objects_default.ipynb
Python code optimized for just-in-time compilation, using [Numba](https://numba.pydata.org/) | angle_between_two_objects_optimized.ipynb
Python code calling C code, using [ctypes](https://docs.python.org/3/library/ctypes.html) | ctypes.ipynb, abo_lib.c
Python code calling C code, using [CFFI](https://cffi.readthedocs.io/en/latest/) | cffi.ipynb, abo_lib.c

For a walkthough of these implementations, check out [this article](https://devtoprd.com/archives/986).