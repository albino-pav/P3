import matplotlib.pyplot as plt
import soundfile as sf 
import numpy as np 
import scipy.signal as sc

f1 = plt.figure(1)
senyalwav, fmwav = sf.read('voiced_seg.wav')
twav = np.arange(0, len(senyalwav))/fmwav
plt.plot(twav, senyalwav)
plt.grid(b=None, which='major', axis='both')
plt.show()

f2 = plt.figure(2)
correlation = sc.correlate(senyalwav, senyalwav, mode='same', method='auto')
plt.plot(twav, correlation)
plt.grid(b=None, which='major', axis='both')
plt.show()

fig, axs = plt.subplots(2)
minor_ticks = np.arange(0, len(senyalwav)/fmwav, 0.0005)
fig.suptitle('Frame and autocorelation')
axs[0].plot(twav, senyalwav)
axs[0].set_title('Voiced frame')
axs[0].grid(b=None, which='both', axis='both')
axs[0].set_xticks(minor_ticks, minor=True)
axs[1].plot(twav, correlation)
axs[1].set_title('Correlation')
axs[1].grid(b=None, which='both', axis='both')
axs[1].set_xticks(minor_ticks, minor=True)
plt.show()
