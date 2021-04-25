import matplotlib.pyplot as plt
import numpy as np

file = open("pav_2311.f0", 'r')
refFile = open("pav_2311.f0ref", 'r')

fig, axs = plt.subplots(2, 1)

axs[0].plot(np.loadtxt(file), 'mo', markersize = 1)
axs[0].set(title='pav_2311.f0')

axs[1].plot(np.loadtxt(refFile), 'yo', markersize = 1)
axs[1].set(title='pav_2311.f0ref (Wavesurfer)')

fig.tight_layout()
plt.savefig("./assets/pitch-compare.png")

file.close()
refFile.close()