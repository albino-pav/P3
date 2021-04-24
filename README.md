PAV - P3: detección de pitch
============================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 3](https://github.com/albino-pav/P3).
Siga las instrucciones de la [Práctica 2](https://github.com/albino-pav/P2) para realizar un `fork` de la
misma y distribuir copias locales (*clones*) del mismo a los distintos integrantes del grupo de prácticas.

Recuerde realizar el *pull request* al repositorio original una vez completada la práctica.

Ejercicios básicos
------------------

- Complete el código de los ficheros necesarios para realizar la detección de pitch usando el programa
  `get_pitch`.

   * Complete el cálculo de la autocorrelación e inserte a continuación el código correspondiente.
   	<img width="496" alt="Autocorrelacion_codigo2" src="https://user-images.githubusercontent.com/79319805/115220557-99f56400-a100-11eb-9302-f60b9652796b.PNG">

   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un segmento de
     unos 30 ms de un fonema sonoro y su periodo de pitch; y, en otro *subplot*, se vea con claridad la
	 autocorrelación de la señal y la posición del primer máximo secundario.

	 NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la librería matplotlib de Python.
	![image](https://user-images.githubusercontent.com/79308448/115963454-9e19eb00-a51f-11eb-9c72-7d2743005af0.png)
	
	>Hemos calculado la frecuencia de pitch como (1/75,40) * 16000=  212,20 Hz. 
	>El segmento de audio contiene la vocal "e". Tras el cálculo, obtenemos una autocorrelación par respecto al origen.
	>Para su representación hemos usado el siguiente código, ayudándonos de la biblioteca matplotlib de Python:
	![image](https://user-images.githubusercontent.com/79308448/115963040-53e43a00-a51e-11eb-8610-903acae749e5.png)
	
   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.
	![image](https://user-images.githubusercontent.com/79308448/115963081-7bd39d80-a51e-11eb-899a-e17b047146dd.png)

   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.
	![image](https://user-images.githubusercontent.com/79308448/115963551-14b6e880-a520-11eb-830a-c4fb1d02a76f.png)

- Una vez completados los puntos anteriores, dispondrá de una primera versión del detector de pitch. El 
  resto del trabajo consiste, básicamente, en obtener las mejores prestaciones posibles con él.

  * Utilice el programa `wavesurfer` para analizar las condiciones apropiadas para determinar si un
    segmento es sonoro o sordo. 
	
	  - Inserte una gráfica con la detección de pitch incorporada a `wavesurfer` y, junto a ella, los 
	    principales candidatos para determinar la sonoridad de la voz: el nivel de potencia de la señal
		(r[0]), la autocorrelación normalizada de uno (r1norm = r[1] / r[0]) y el valor de la
		autocorrelación en su máximo secundario (rmaxnorm = r[lag] / r[0]).

		Puede considerar, también, la conveniencia de usar la tasa de cruces por cero.

	    Recuerde configurar los paneles de datos para que el desplazamiento de ventana sea el adecuado, que
		en esta práctica es de 15 ms.
	![image](https://user-images.githubusercontent.com/79308448/115963611-5a73b100-a520-11eb-82c6-236c12432e5a.png)
	>Según el detector de pitch incorporado en wavesurfer vemos que del segmento 0,8s al 1,3s se detecta sonoridad. 
	>Los valores de este detector oscilan entre 180 y 220 Hz.


      - Use el detector de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos detectores.
	<img width="953" alt="pitch lindisimo" src="https://user-images.githubusercontent.com/79308448/115963721-f69db800-a520-11eb-8d6e-315ffef1da7f.PNG">

	> En esta imagen vemos el detector de pitch implementado con nuestro código (formato data plot), el pitch que detecta el wavesurfer, la potencia calculada y la señal de voz sonora.
	> Podemos ver que detectamos el pitch correctamente. Aun así, posteriormente modificaremos diferentes parámetros para tener un sistema aún más preciso.
  
  * Optimice los parámetros de su sistema de detección de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..
	<img width="378" alt="summary" src="https://user-images.githubusercontent.com/79308448/115963805-454b5200-a521-11eb-880e-2f0950145358.PNG">
	>Hemos modificado parámetros en el detector de sonoridad para tener una mejor detección de los segmentos de audio de la base de datos. 
	>Creemos que es un valor adecuado al estar por encima del 90%.


   * Inserte una gráfica en la que se vea con claridad el resultado de su detector de pitch junto al del
     detector de Wavesurfer. Aunque puede usarse Wavesurfer para obtener la representación, se valorará
	 el uso de alternativas de mayor calidad (particularmente Python).
    ![image](https://user-images.githubusercontent.com/79308448/115963953-37e29780-a522-11eb-8242-523a9b5f94bc.png)
    >Vemos el pitch optimizado implementado con nuestro código (formato pitch contour), el pitch que detecta el wavesurfer, la potencia calculada y la señal de voz sonora.
    >El pitch calculado y el proporcionado por el wavesurfer son prácticamente iguales, por lo que estamos satisfechas con el resultado obtenido, aunque siempre se podría mejorar aún más.

Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  detector a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del detector. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la detección de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.
![image](https://user-images.githubusercontent.com/79308448/115964932-0ddfa400-a527-11eb-8a16-670e89af8e2e.png)

- Implemente las técnicas que considere oportunas para optimizar las prestaciones del sistema de detección
  de pitch.

  Entre las posibles mejoras, puede escoger una o más de las siguientes:

  * Técnicas de preprocesado: filtrado paso bajo, *center clipping*, etc.
  * Técnicas de postprocesado: filtro de mediana, *dynamic time warping*, etc.
  * Métodos alternativos a la autocorrelación: procesado cepstral, *average magnitude difference function*
    (AMDF), etc.
  * Optimización **demostrable** de los parámetros que gobiernan el detector, en concreto, de los que
    gobiernan la decisión sonoro/sordo.
  * Cualquier otra técnica que se le pueda ocurrir o encuentre en la literatura.

  Encontrará más información acerca de estas técnicas en las [Transparencias del Curso](https://atenea.upc.edu/pluginfile.php/2908770/mod_resource/content/3/2b_PS%20Techniques.pdf)
  y en [Spoken Language Processing](https://discovery.upc.edu/iii/encore/record/C__Rb1233593?lang=cat).
  También encontrará más información en los anexos del enunciado de esta práctica.

  Incluya, a continuación, una explicación de las técnicas incorporadas al detector. Se valorará la
  inclusión de gráficas, tablas, código o cualquier otra cosa que ayude a comprender el trabajo realizado.

  También se valorará la realización de un estudio de los parámetros involucrados. Por ejemplo, si se opta
  por implementar el filtro de mediana, se valorará el análisis de los resultados obtenidos en función de
  la longitud del filtro.
>Center clipping

![image](https://user-images.githubusercontent.com/79308448/115965430-8b0c1880-a529-11eb-896b-b16fff8d9486.png)

>Filtro de mediana

![image](https://user-images.githubusercontent.com/79308448/115965457-a70fba00-a529-11eb-9751-8d16cd700d5a.png)

Evaluación *ciega* del detector
-------------------------------

Antes de realizar el *pull request* debe asegurarse de que su repositorio contiene los ficheros necesarios
para compilar los programas correctamente ejecutando `make release`.

Con los ejecutables construidos de esta manera, los profesores de la asignatura procederán a evaluar el
detector con la parte de test de la base de datos (desconocida para los alumnos). Una parte importante de
la nota de la práctica recaerá en el resultado de esta evaluación.
