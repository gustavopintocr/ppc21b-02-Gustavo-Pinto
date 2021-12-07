# Simulacion de una rotonda
Se simula el tráfico en una rotonda con entradas y salidas en los cuatro puntos cardinales (N, S, E, O), la cual es transitada por vehículos que corresponden a hilos de ejecución.

La simulación recibe en la entrada estándar un entero que indica la capacidad de cada uno de los cuatro segmentos de la rotonda. Un segmento es un tramo circular que inicia en una entrada de la rotonda y termina en la próxima salida de la misma. En el ejemplo de entrada, la capacidad de segmento es de 2, lo cual significa que en cada uno de los cuatro segmentos de la rotonda sólo caben a lo sumo dos vehículos al mismo tiempo sin colisionar. Si en esta rotonda hubiere en un momento tres o más vehículos en el tramo, es porque habría ocurrido una colisión. Nótese que la capacidad total de la rotonda es la suma de la capacidad de cada uno de sus cuatro segmentos.

Después de la capacidad del segmento, la simulación recibe un par ordenado de letras por cada vehículo. La primera letra indica el punto cardinal por el que ingresa el vehículo a la rotonda, y la segunda letra indica la dirección a la que se dirige, es decir, el punto cardinal por donde saldrá de la rotonda. Por ejemplo, SO corresponde a un vehículo que ingresa por la entrada sur y se dirige hacia la salida oeste tras realizar un giro de 270 grados en dirección antihorario.

## Créditos

2021 Gustavo Pinto - Universidad de Costa Rica

