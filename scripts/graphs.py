import matplotlib.pyplot as plt
import soundfile as sf
import numpy as np

plt.figure(1)
senyalwav = np.loadtxt('correctpitch.f0')
twav = np.arange(0, len(senyalwav))
plt.plot(twav, senyalwav)
plt.show()

plt.figure(2)
senyalwav2 = np.loadtxt('sb013.f0')
twav2 = np.arange(0, len(senyalwav2))
plt.plot(twav2, senyalwav2)
plt.show()

plt.figure(3)
fig, axs = plt.subplots(2)
fig.suptitle('Wavesurfer estimation vs our implementation estimation')
axs[0].plot(twav, senyalwav)
axs[0].set_title('Wavesurfer .f0 file')
axs[1].plot(twav2, senyalwav2)
axs[1].set_title('Implemented .f0 file')
plt.show()
