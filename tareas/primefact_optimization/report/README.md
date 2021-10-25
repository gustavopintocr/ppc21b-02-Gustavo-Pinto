# Reporte

## Desarrollo

### Para desarrollar las optimizaciones se siguió el siguiente método recomendado:

- Medir el rendimiento del código antes de realizar las modificaciones:
Se realizo una medición del tiempo en segundos que tardo el código en ejecutarse en una 
CPU de 8 núcleos, en el clúster Arenal brindado por la E.C.C.I. Y a partir de ello, se determino 
su speedup y eficiencia con respecto a la versión serial del mismo.

- Analizar el código para detectar las regiones críticas a optimizar (profiling):
Mediante la herramienta callgrind de valgrind se pudo detectar la región del código del programa 
basada en mapeo dinámico, que debía ser optimizada por su alto consumo de recursos, el cual se encontraba
 en el método factorizar, en el cual se llamaba la función mod(%) por cada repetición del ciclo que determina 
 si un número es factor primo.

- Hacer las modificaciones que se cree incrementarán el rendimiento en las regiones críticas:
Gracias a la detección de la región anterior, se pudo implementar una mejora de rendimiento al ciclo, mediante 
la disminución de las iteraciones mod (%) a la mitad ya que solo se trabaja con números impares con excepción del número 2.

- Asegurarse de que las modificaciones sean correctas:
Mediante la ejecución de los casos de pruebas /tests se determinó el correcto funcionamiento del código.

- Medir el rendimiento del código después de realizar las modificaciones y comparar para determinar si hubo una ganancia:
Se hizo la medición del rendimiento a través del tiempo de la ejecución del programa, la cual se hizo en el clúster 
Arenal brindado por la E.C.C.I, por medio de la herramienta perf stat, que brindo el tiempo transcurrido en la ejecución
 del programa en un CPU de 8 núcleos, del cual se determinó el speedup y la eficiencia, los cuales determinaron una mejora 
 considerable conforme a la versión anterior.

## Comparación de optimizaciones

![Comparacion1_Optimizaciones](https://github.com/gustavopintocr/ppc21b-02-Gustavo-Pinto/blob/main/tareas/primefact_optimization/report/Comparacion1_Optimizaciones.jpg)

## Comparación grados de concurrencia

![Comparacion2_Concurrencia](https://github.com/gustavopintocr/ppc21b-02-Gustavo-Pinto/blob/main/tareas/primefact_optimization/report/Comparacion2_Concurrencia.jpg)

## KCachegrind

![KCachegrind](https://github.com/gustavopintocr/ppc21b-02-Gustavo-Pinto/blob/main/tareas/primefact_optimization/report/KCachegrind.jpg)

KCachegrind permite encontrar rápida y visualmente las líneas de código fuente que consumen más instrucciones de procesador, y por tanto, 
las líneas críticas que convienen optimizar, incluso en una base de código extensa. En la esquina superior izquierda de la Visualización 
de KCachegrind de las líneas que consumen más procesamiento muestra un gráfico de consumo por cada hilo de ejecución. En la esquina inferior 
izquierda muestra las subrutinas que han ejecutado más instrucciones de procesador en porcentajes, factorize() está seleccionada. En la esquina 
superior derecha se muestra las líneas de código fuente de factorize() que consumieron más instrucciones. Se puede ver que el operador módulo (%)
es el que causa casi la totalidad del procesamiento. Estos son los puntos críticos a optimizar para este programa.

## Conclusión
Analizando los gráficos se pueden llegar a varias conclusiones. La primera es que el mapeo dinámico tiene ventaja sobre el mapeo 
por bloques, aunque sea marginal. Podemos decir que una implementación de mapeo dinámico asegura buenos resultados y es acertado 
tenerla como primera opción. Otra conclusión a la que se puede llegar gracias a las pruebas realizadas, es que los mejores resultados 
de Speedup, se obtienen cuando el número de hilos creados es igual al número de núcleos en el sistema.Por otro lado, se puede observar que, 
a mayor número de hilos, menor eficiencia.

