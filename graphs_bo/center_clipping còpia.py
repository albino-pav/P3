import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile as waves
import math as math

#Creació de l'arxiu a partir del qual traiem la frequencia de mostreig i les seves mostres d'audio
arxiu = '/Users/giselaflotatsboix/PAV/P3/pav_2301_02_curta.wav'
fm, audio = waves.read(arxiu)
audio = audio.astype(float)

#Vector temps
dt = 1/fm
mostres = []
for x in range(0, len(audio)):
    mostres.append(x*dt)

#Apliquem center clipping (valor que hem fet servir 0.8)
frontera = max(audio)*0.8
cc = np.array(audio)

for n in range(0, len(cc)):
    if cc[n] >= frontera:
        cc[n] -= frontera
    else:
        if cc[n] <= -frontera:
            cc[n] += frontera
        else:
            cc[n] = 0

#Gràfica
plt.subplot(211)
plt.title('Senyal temporal')
plt.plot(mostres, audio, linewidth = 0.5)
plt.xlabel('Temps (s)')
plt.ylabel('Forma de ona')
plt.grid(True)
plt.subplot(212)
plt.title('Center clipping')
plt.xlabel('Temps (s)')
plt.ylabel('Forma de ona amb center clipping')
plt.plot(mostres, cc, linewidth = 0.5)
plt.grid(True)
plt.show()