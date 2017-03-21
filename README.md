# HHG from strong field approximation theory

## Usage
Simply `make`, then `./test` or `python run.py`

## Core function
```c
void calc_hhg(long nt, double dt, double* Ef, double* dout)
```
requires `nt`, the size of the time grid, `dt`, the time step size, `Ef`, the grid storing electric field and `dout`, the real part of $d(t)$

## Files
- libhhg.cc: the source file that builds a tiny library file `libhhg.so` providing the interface function `calc_hhg`. See `main.cc` to see how to call `calc_hhg`.

- run.py: a simple python script invoking libhhg.so, can easily manipulate parameters and call `calc_hhg` function to generate dipole(t)

- main_full.cc: an indepedent file to calculate HHG for H1s with the SFA model
