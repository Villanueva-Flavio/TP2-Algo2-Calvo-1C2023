Si quieren saber más acerca de las cosas que fui implementando les dejo este readme

Movimientos:
  Para implementar el movimiento de las fichas en realidad se hizo un enfoque a las celdas.
  Cuando se ejecuta un movimiento en cualquier dirección en realidad lo que se está haciendo
  a profundidad no es mover la ficha, sino literalmente cambiar las posiciones de las celdas.
  Es decir, muevo la ficha adelante, entonces la ficha en donde estoy parado va a adquirir la información
  de la siguiente celda, y la siguiente celda va a adquirir la información que tenía la anterior celda.

Busqueda de la ficha:
  Para la búsqueda es simple. Se hace una iteración de x por y por z.
  Para reducir la complejidad algoritmica de dicha iteración es mejor que se itere menos la z,
  entonces para evitar esto, dependiendo de lo que elija el jugador (precisamente en el tipo de ficha),
  la iteración será hasta un valor z definido según el tipo de ficha que quiere buscar el jugador.
