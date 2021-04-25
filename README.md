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
    ```cpp
      void PitchAnalyzer::autocorrelation(const vector<float> &x, vector<float> &r) const {

        for (unsigned int l = 0; l < r.size(); ++l) {
  		    /// Compute the autocorrelation r[l]
          r[l] = 0;
        for(unsigned int n=l; n < x.size(); n++ ){
          r[l] += x[n]*x[n-l] ;
        }
      }

      if (r[0] == 0.0F) //to avoid log() and divide zero 
        r[0] = 1e-10;
    }
    ```

   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un segmento de
     unos 30 ms de un fonema sonoro y su periodo de pitch; y, en otro *subplot*, se vea con claridad la
	 autocorrelación de la señal y la posición del primer máximo secundario.
    
    NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la librería matplotlib de Python.

   > Para ejecutar la representación de las dos gráficas hemos utilizado Python, aprovechando sus librerias y sus funciones para poder representar tanto la señal como su autocorrelación.
   > La señal que hemos grabado es el fonema sonoro de la vocal 'o'.
   
  <img src="img/Figure_1.png" width="640" align="center">

   > Figure_1

   > NOTA: no entiendemos porque pero las imagenes no se visualizan correctamente, estan todas en la carpeta src/img, debajo de cada imagen pondremos a cual hace referencia.

    ```py
    import matplotlib.pyplot as plt
    import numpy as np
    import soundfile as sf

    signal, fm = sf.read('audio_p3.wav')
    t = np.arange(0, len(signal)) /fm

    plt.figure()

    #Plot de la señal temporal del segmento de voz
    plt.subplot(211)
    plt.plot(t, signal)
    plt.title('Señal temporal')
    plt.xlabel("t(s)")
    plt.grid()

    #Plot de la autocorrelación del segmento de voz
    #Utilizamos la funcion plt.acorr de la bibiloteca malplotlib.pyplot
    #Nos devuelve una grafica de la autocorrelación de la señal
    plt.subplot(212)
    plt.acorr(signal, maxlags = 20) #maxlags = len(signal)-1 ??
    plt.title('Autocorrelación')
    plt.xlabel("\tau(s)")
    plt.grid()

    plt.subplots_adjust(hspace=1)
    plt.show()
  ```

   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.

  ```cpp
      vector<float>::const_iterator iR = r.begin(), iRMax = iR + npitch_min;
        
        for(iR = r.begin() + npitch_min; iR < r.begin() +  npitch_max; iR++ ){
          if(*iR > *iRMax){
            iRMax = iR;
          }
        }

        unsigned int lag = iRMax - r.begin();

        float pot = 10 * log10(r[0]);

  ```

   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.

 ```cpp
      bool PitchAnalyzer::unvoiced(float pot, float r1norm, float rmaxnorm) const {
      /// Implementation of a rule to decide whether the sound is voiced or not.
      /// * You can use the standard features (pot, r1norm, rmaxnorm),
      ///   or compute and use other ones.

        if( pot > power && (rmaxnorm > rmax || r1norm > r1)){
          return false;
        }else{
          return true;
        }

  ```
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

    > Para hacer este apartado hemos vuelto a grabar la señal de la vocal 'o' pero esta ves hemos alargado 
    la señal dejando un inicio y un final de silencio para que se pueda apreciar mejor el contorno del pitch. 
    > En el primer panel, tenemos la tasa de cruces por cero, que vemos que tiende a 0 en el tramo sonoro.
    En el segundo panel, tenemo la potencia de la señal, que vemos que es más elevada en el tramo sonoro.
    Y en el tercer panel, nos encontramos con el pitch que genera el programa `wavesurfer`.

    <img src="img/img2.png" width="640" align="center">
     > img2

      - Use el detector de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos detectores.

     > En el primer panel tenemos el pitch impo,entetado con nuestro propio sistema, y en el segundo el generado
     por el programa `wavesurfer`.
     > Podemos ver que hemos conseguido resultados similares, por lo tanto creemos que hemos implementado un 
     buen sistema.

      <img src="img/img1.png" width="640" align="center">
     > img1
  
  * Optimice los parámetros de su sistema de detección de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..

      <img src="img/img4.png" width="640" align="center">
      > img4

   * Inserte una gráfica en la que se vea con claridad el resultado de su detector de pitch junto al del
     detector de Wavesurfer. Aunque puede usarse Wavesurfer para obtener la representación, se valorará
	 el uso de alternativas de mayor calidad (particularmente Python).
      > Hemos intentado hacer el codigo de Python, pero nos daba un error al leer los archivos que le introduciamos,
      en su lugar para seguir viendo el funcionamiento del detector hemos grabado una frase completa y la hemos pasado
      por el detector.
      En el panel superior tenemos nuestro sistema y en el inferior el del programa, y hemos podido volver a comprobar
      el correcto funcionamiento de nuestro detector ya que consigue una buena aproximación del pitch. Tambien con esta
      frase hemos podido comprobar la variabilidad del tono según si eres hombre o mujer, y podemos ver como la primera 
      parte de la frase al estar grabada por Cecilia tenemos un tono con un rango de frecuencia superior que la segunda
      parte que esta grabada por Percy donde vemos que el rango de frecuencia del tono ha disminuido. 


    <img src="img/img3.png" width="640" align="center">
    > img3
   

Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  detector a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del detector. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la detección de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.

    <img src="img/img5.png" width="640" align="center">
    > img5

- Implemente las técnicas que considere oportunas para optimizar las prestaciones del sistema de detección
  de pitch.

  Entre las posibles mejoras, puede escoger una o más de las siguientes:

  * Técnicas de preprocesado: filtrado paso bajo, *center clipping*, etc.
  * Técnicas de postprocesado: filtro de mediana, *dynamic time warping*, etc.

  ```cpp

  // FILTRO DE MEDIANA
  for (unsigned int i = 1; i < f0.size(); ++i)
  {
    vector<float> aux {f0[i-1],f0[i],f0[i+1]};
    sort(aux.begin(), aux.end());
    f0[i] = aux[1];
  }

  ```

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
    
    > El filtro de mediana que hemos incorporado, se basa en asignar a cada punto el valor de la mediana
      local. Con el conseguimos 
    <img src="img/filtro_mediana.png" width="640" align="center">
    > filtro_mediana

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
