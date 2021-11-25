# Factorización Concurrente
La factorización surge como solución  a la tarea repetitiva y tediosa de factorizar  números enteros en sus componentes primos. Esto ayudó tanto a los seres humanos como a las computadoras tradicionales, ya que la seguridad de sus comunicaciones privadas, datos sensibles y su dinero en el banco depende de esta dificultad, ya que están protegidos por números difíciles de factorizar.

Cuando hablamos de factorizar debemos saber que un número se divide en tres categorías:
- [Número Uno](https://es.wikipedia.org/wiki/Uno "Número Uno")
- [Números Primos](https://es.wikipedia.org/wiki/Número_primo "Números Primos")
- [Números Compuestos](https://es.wikipedia.org/wiki/Número_compuesto "Números Compuestos")

Factorizar consiste en descomponer números primos y compuestos de la siguiente forma:

  - **7:** 7
  - **1400:** 2^3 5^2 7

Además existen condiciones especiales para el número 1 y  los números negativos, por lo que se espera una respuesta como:

- **1:** NA
-  **-2:** invalid number

¿Por qué decimos que Concurrente?
Porque se calculan las factorizaciones primas  utilizando hilos que se reparten el trabajo, y por lo tanto, debe tener un incremento en el desempeño en la ejecución del código, de forma corroborable.

## Aplicación de la concurrencia

### Numero de hilos por entrada estandar
El usuario tiene la posibilidad de decidir la cantidad de hilos con la que desea ejecutar el programa, en este caso, debe pasar este numero por la entrada estandar a la hora de correr el programa. Por ejemplo, pasarle 3 como la cantidad de hilos:

`bin/primefact_pthread 3`

### Default
En el caso de que no se le pase ningun numero en la entrada estandar, el programa se ejecutara con un numero de hilos igual al numero de nucleos de la CPU.

## Open MP

[OpenMP](https://es.wikipedia.org/wiki/OpenMP) se basa en el modelo fork-join, paradigma que proviene de los sistemas Unix, donde una tarea muy pesada se divide en K hilos (fork) con menor peso, para luego "recolectar" sus resultados al final y unirlos en un solo resultado (join).

Cuando se incluye una directiva de compilador OpenMP esto implica que se incluye una sincronización obligatoria en todo el bloque. Es decir, el bloque de código se marcará como paralelo y se lanzarán hilos según las características que nos dé la directiva, y al final de ella habrá una barrera para la sincronización de los diferentes hilos (salvo que implícitamente se indique lo contrario con la directiva nowait). Este tipo de ejecución se denomina fork-join.

Gracias a esta herramienta se logró un mejor desempeño en la implementacion de la concurrencia por hilos dentro del programa, además le permite al usuario poder cambiar entre las distruciones que desea (dynamic, static, guided= de una forma más sencilla.

## Ejecución del programa

### Construcción
Para construir el programa:

`make`

### Limpieza
Para limpiar los archivos generados por el compilador

`make clean`

#### Prueba de memoria
Esta prueba requiere la construccion del programa

`make memcheck`

#### Checkeo del lint
Esta prueba no requiere de la construcción del programa

`make lint`

#### Ejecución de casos de prueba

`make test`

## Créditos

2021 Gustavo Pinto - Universidad de Costa Rica

