import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile as waves
import math as math

#Creació de l'arxiu a partir del qual traiem la frequencia de mostreig i les seves mostres d'audio
arxiu = '/Users/giselaflotatsboix/PAV/P3/pav_2301_02.wav'
fm, audio = waves.read(arxiu)
audio = audio.astype(float)

#Vector temps
dt = 1/fm
mostres = []
for x in range(0, len(audio)):
    mostres.append(x*dt)

#Enfinestrem utilitzant Hamming 
# audioEnfinestrat = audio2*np.hamming(len(audio)) per alguna raó no funciona
a0 = 0.53836
a1 = 0.46164
finestra = []
for i in range(0, len(audio)):
    finestra.append(a0-a1*math.cos(2*math.pi*i/(len(audio)-1)))

audioEnfinestrat = audio*finestra; 

#Autocorrelació
autocorrelacio=np.correlate(audioEnfinestrat, audioEnfinestrat, "same")
limits = np.arange(-0.5*len(autocorrelacio), 0.5*len(autocorrelacio), 1)

#Gràfica
plt.subplot(211)
plt.title("Senyal temporal")
plt.plot(mostres, audio, linewidth = 0.5)
plt.xlabel('Temps (s)')
plt.xlim(0.5, 0.8)
plt.ylim(-6000, 6000)
plt.ylabel('Forma de ona')
plt.grid(True)
plt.subplot(212)
plt.title("Autocorrelació")
plt.xlabel("Mostres")
plt.ylabel("Autocorrelació")
plt.plot(limits, autocorrelacio, linewidth = 0.5)
plt.xlim(-1500, 1500)
plt.grid(True)
plt.show()