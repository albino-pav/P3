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

   <img src='https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/Autocorrelación.png'>

   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un segmento de
     unos 30 ms de un fonema sonoro y su periodo de pitch; y, en otro *subplot*, se vea con claridad la
	 autocorrelación de la señal y la posición del primer máximo secundario.

   <img src ='https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/SenyalTemp%26AutocorrelacióPython.png'>

	 NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la librería matplotlib de Python.

   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.

    <img src = 'https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/Pitch.png'>

   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.

   <img src ='https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/voicedunvoiced.png'>

      - Per tal d'aconseguir el resultat óptim, hem estat jugant amb els diferents llindars. Hem utilitzat 3 condicions per tal d'identificar si estavem tractant amb un voiced(false) o un unvoiced(true). 

- Una vez completados los puntos anteriores, dispondrá de una primera versión del detector de pitch. El 
  resto del trabajo consiste, básicamente, en obtener las mejores prestaciones posibles con él.

  * Utilice el programa `wavesurfer` para analizar las condiciones apropiadas para determinar si un
    segmento es sonoro o sordo. 
	
	  - Inserte una gráfica con la detección de pitch incorporada a `wavesurfer` y, junto a ella, los 
	    principales candidatos para determinar la sonoridad de la voz: el nivel de potencia de la señal
		(r[0]), la autocorrelación normalizada de uno (r1norm = r[1] / r[0]) y el valor de la
		autocorrelación en su máximo secundario (rmaxnorm = r[lag] / r[0]).

    <img src = 'https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/WS.Pot_R1_Rmax.png'>

      NOTA: Podem veure en ordre, la potència, la r1 normalitzada i la rmax. Primer d'un tros 

		Puede considerar, también, la conveniencia de usar la tasa de cruces por cero.

	    Recuerde configurar los paneles de datos para que el desplazamiento de ventana sea el adecuado, que
		en esta práctica es de 15 ms.

      - Use el detector de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos detectores.

    <img src = 'https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/WS_Pitch.png'>

      Es veu a dalt de tot el detector de pitch implementat en el programa wavesurfer i a sota el nostre resultat. 
      Es pot destacar que de cop el nostre pitch dona 0 probablement degut a la sonoritat del fonema que està sonant en aquell moment.
  
  * Optimice los parámetros de su sistema de detección de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..
  
  <img src = 'https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/Summary.png'>

  *NOTA* aquests resultats son amb les ampliacions (tot i així no han afectat massa el resultat)
  Podem observar com el major marge d'error el trobem escollint frames sonores com a sordes. 

   * Inserte una gráfica en la que se vea con claridad el resultado de su detector de pitch junto al del
     detector de Wavesurfer. Aunque puede usarse Wavesurfer para obtener la representación, se valorará
	 el uso de alternativas de mayor calidad (particularmente Python).

  <img src = 'https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/WS_Pitch.png'>

   

Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  detector a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del detector. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la detección de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.

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

  CENTER CLIPPING

   Com a técnica de preprocessat hem aplicat center clipping, una transformació no lineal que té com a funció en posar a 0 els valors entre uns thresholds establerts, que hem calculat a partir de la poténcia de la senyal. Amb aquest métode, eliminem la part de senyal que no ens interessa i ens quedem amb la que sí. A la pràctica, el fet d'aplicar el center clipping no ha augmentat molt les presteacions ja que ha augmentat el 0,5% la evaluació utilitzant la base de dades.

   Com a comprovació del center clipping hem fet una gràfica de python on es pot veure que es simplifica molt el gràfic (el codi està a la carpeta graphs_bo)
   Després de comparar varis resultats hem trobat que amb un llindar del 0,8*potència ens seguia donant els mateixos resultats, per tant hem decidit posar aquest nombre ja que es el que simplifica més el gràfic final com veiem a continuació: 

   <img src = 'https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/CenterClipping.png'>

  FILTRO DE MEDIANA
    - Pel que fa a la técnica del postprocessat, hem aplicat el filtre de mediana. El que fa és reemplaçar el valor del pitch per la mediana dels valors del voltant. d'aquesta manera eliminem possibles errors deguts a pics o valls puntuals. Hem utilitzat una mida de finestra d'un valor de 3 de llargada.

    <img src = 'https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/3medianes.png'>

    Adjuntem també, per comparar, els resultats amb una finestra de 2 i 5: 

   - finestra de 2

    <img src = 'https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/2medianes.png'>
  
    - finestra de 5

    <img src = 'https://github.com/giselaflotats/P3/blob/flotats-izquierdo/imatges/5medianes.png'>

  También se valorará la realización de un estudio de los parámetros involucrados. Por ejemplo, si se opta
  por implementar el filtro de mediana, se valorará el análisis de los resultados obtenidos en función de
  la longitud del filtro.
   

Evaluación *ciega* del detector
-------------------------------

Antes de realizar el *pull request* debe asegurarse de que su repositorio contiene los ficheros necesarios
para compilar los programas correctamente ejecutando `make release`.

Con los ejecutables construidos de esta manera, los profesores de la asignatura procederán a evaluar el
detector con la parte de test de la base de datos (desconocida para los alumnos). Una parte importante de
la nota de la práctica recaerá en el resultado de esta evaluación.
