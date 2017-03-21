import ctypes as ct

hhg = ct.CDLL('libhhg.so')
calc_hhg = hhg.calc_hhg
calc_hhg.argtypes = [ct.c_long, ct.c_double,
                     ct.POINTER(ct.c_double),
                     ct.POINTER(ct.c_double)]
calc_hhg.restype = None

t0, t1, nt = -500., 500., 10001
E0, w0, sigma = 0.08, 0.057, 206.7

dt = (t1 - t0) / (nt - 1.)

import numpy as np
time = np.linspace(t0, t1, nt)
Ef = E0 * np.exp(-time**2/sigma**2) * np.cos(w0*time)

d = np.empty(nt)
calc_hhg(nt, dt,
         Ef.ctypes.data_as(ct.POINTER(ct.c_double)),
         d.ctypes.data_as(ct.POINTER(ct.c_double)))

import matplotlib.pyplot as plt
f, ax = plt.subplots(2)
ax[0].plot(time, Ef)
ax[1].plot(time, d)
plt.show()
