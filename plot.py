import numpy as np
import matplotlib.pyplot as plt

Ip, w0, E0 = 0.5, 0.057, 0.08
dt = 0.6
E_cutoff = Ip + 3.17*(E0**2/(4.*w0**2))
order_cutoff = E_cutoff / w0

data = np.loadtxt('data.dat')
time, Ef, Af, alphaf, dreal, dimag = data[:,0], data[:,1], data[:,2], data[:,3], data[:,4], data[:,5]

ndata = np.size(time)
w = 2. * np.pi * np.fft.fftfreq(ndata, dt)[:ndata/2]
spec = np.log10(np.fft.fft(2 * dreal)[:ndata/2])
order = w / w0

fig = plt.figure()
ax1 = plt.subplot(221)
ax2 = plt.subplot(223)
ax3 = plt.subplot(122)

ax1.plot(time, Ef)
ax1.set_title('Incident fields')
ax1.set_xlabel('Time (a.u.)')
ax1.set_ylabel('Fields')
ax1.grid()
# d(t)
ax2.plot(time, dreal)
ax2.set_title('Emission in time domain')
ax2.set_xlabel('Time (a.u.)')
ax2.set_ylabel(r'$d(t)$')
ax2.grid()
# d(w)
ax3.plot(order, spec, '.-')
map(lambda i: ax3.axvline(x=i, lw=0.5, c='k'), range(100)[1:-1:2])
ax3.axvline(x=order_cutoff, lw=2, c='k')
ax3.set_title('Harmonic generation')
ax3.set_xlabel(r'Order ($\omega/\omega_c$)')
ax3.set_ylabel('Emission')

plt.tight_layout()
plt.show()
