import matplotlib.pyplot as plt
import numpy as np
import wave
import sys

spf = wave.open("./pitch_db/train/rl001.wav", "r")

# Extract Raw Audio from Wav File
signal = spf.readframes(-1)
signal = np.frombuffer(signal, dtype=np.int16)
fs = spf.getframerate()

# If Stereo
if spf.getnchannels() == 2:
    print("Just mono files")
    sys.exit(0)

signal = signal[int(1.1*fs):int(1.13*fs)]

Time = np.linspace(0, len(signal) / fs, num=len(signal))

""" plt.figure(1)
plt.title("Signal Wave...")
plt.plot(Time, signal)
plt.show() """

r = np.correlate(signal, signal, mode='full')[len(signal)-1:]

plt.figure(figsize=(14, 5))
plt.plot(r)
plt.xlabel('Lag (samples)')
plt.show()