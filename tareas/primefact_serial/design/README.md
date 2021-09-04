#Diseño

##Diagrama de clases
![Diagrama UML](https://github.com/gustavopintocr/ppc21b-02-Gustavo-Pinto/blob/main/tareas/primefact_serial/design/primefact_serial.png?raw=true "Diagrama UML")

##Distribución
- **Arreglo de enteros:** Esta clase consiste en dos estructuras basicas, las cuales son:
`Struct array_int_t`
`Struct sub_array_t`

- **Struct array_int_t: **Consiste en un arreglo de enteros, con varios atributos como:
`La capacidad del arreglo`
`Un contador para los elementos del arreglo`
`Un subarrreglo que contiene un numero y su factorización serial`

- **Struct sub_array_t** Esta es una estructura de con numeros de 64 bits, con varios atributos como:
`La capacidad del subarreglo`
`Un contador para los elementos del subarreglo`
`El numero a factorizar`
`Las bases del número`
`Los exponentes del número`

> > Esta clase cuenta con métodos esenciales para  iniciar, destruir, añadir elementos, aumentar la capacidad, factorizar los números e imprimimirlos.
