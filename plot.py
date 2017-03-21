import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('data.dat')
#plt.plot(data[:,0], data[:,1], data[:,0], data[:,2], data[:,0], data[:,3])
#plt.plot(data[:,0], data[:,4], data[:,0], data[:,5])
#plt.plot(data[:,0], data[:,4])
#plt.plot(data[:,0], data[:,5], data[:,0], np.sqrt(data[:,4]**2 + data[:,5]**2))
ndata = np.size(data[:,0])
plt.plot(np.log10(np.fft.fft(2 * data[:,4])[:ndata/2]))
#plt.plot(np.log10(np.abs(np.fft.fft(2 * data[:,5])[:ndata/2])))
plt.show()
