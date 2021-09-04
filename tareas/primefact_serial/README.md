# Factorización Serial
La factorización serial surge como solución  a la tarea repetitiva y tediosa de factorizar  números enteros en sus componentes primos. Esto ayudó tanto a los seres humanos como a las computadoras tradicionales, ya que la seguridad de sus comunicaciones privadas, datos sensibles y su dinero en el banco depende de esta dificultad, ya que están protegidos por números difíciles de factorizar.

Cuando hablamos de factorizar debemos saber que un número se divide en tres categorías:
- [Número Uno](https://es.wikipedia.org/wiki/Uno "Número Uno")
- [Números Primos](https://es.wikipedia.org/wiki/Número_primo "Números Primos")
- [Números Compuestos](https://es.wikipedia.org/wiki/Número_compuesto "Números Compuestos")

Factorizar serialmente consiste en descomponer números primos y compuestos de la siguiente forma:

  - **7:** 7
  - **1400:** 2^3 5^2 7

Además existen condiciones especiales para el número 1 y  los números negativos, por lo que se espera una respuesta como:

- **1:** NA
-  **-2:** invalid number


## Ejecución del programa

### Construcción
Para construir el programa:

`make`

### Limpieza
Para limpiar los archivos generados por el compilador

`make clean`

#### Prueba de memoria

`make memcheck`

#### Checkeo del lint
Esta prueba no requiere de la construcción del programa

`make lint`

#### Ejecución de casos de prueba

`make test`

## Créditos

Copyright 2021 Gustavo Pinto - Universidad de Costa Rica

