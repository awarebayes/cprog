import ctypes
from typing import List

lib = ctypes.CDLL("../library/libarr.so")

_arr_fib = lib.arr_fib
_arr_fib.argtypes = (
    ctypes.POINTER(ctypes.c_int),
    ctypes.c_int,
)

_entries = lib.entries
_entries.argtypes = (
    ctypes.POINTER(ctypes.c_int),
    ctypes.c_int,
    ctypes.POINTER(ctypes.c_int),
    ctypes.POINTER(ctypes.c_int),
)
_entries.restype = ctypes.c_int


def fib_arr(n: int) -> List[int]:
    buffer = (ctypes.c_int * n)()
    _arr_fib(buffer, n)
    return list(buffer)


def entries(arr: List[int]) -> List[int]:
    buf_size = ctypes.c_int(0)
    arr_ptr = (ctypes.c_int * len(arr))(*arr)
    ec = _entries(arr_ptr, len(arr), None, buf_size)
    assert ec == 1
    buffer = (ctypes.c_int * buf_size.value)()
    ec = _entries(arr_ptr, len(arr), buffer, buf_size)
    assert ec == 0
    return list(buffer)
