import matplotlib.pyplot as plt
import numpy as np
import soundfile as sf

signal, fs = sf.read('pitch_db/train/rl002.wav')
signal = signal[int(1.1*fs):int(1.13*fs)]
r = np.correlate(signal, signal, mode='full')[len(signal)-1:]

Time = np.linspace(0, len(signal) / fs, num=len(signal))

fig, axs = plt.subplots(2, 1)

axs[0].plot(Time, signal)
axs[0].set_ylabel('Vowel A')
axs[0].grid(True)

axs[1].plot(r)
axs[1].set_ylabel('Autocorrelation')
axs[1].grid(True)

fig.tight_layout()
plt.show()