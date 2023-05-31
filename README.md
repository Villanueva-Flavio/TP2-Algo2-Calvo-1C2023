Si quieren saber más acerca de las cosas que fui implementando, les dejo este README.

Movimientos:
  Para implementar el movimiento de las fichas, en realidad se hizo un enfoque en las celdas.
  Cuando se ejecuta un movimiento en cualquier dirección, en realidad lo que se está haciendo
  en profundidad no es mover la ficha, sino literalmente cambiar las posiciones de las celdas.
  Es decir, muevo la ficha hacia adelante y la celda en la que estoy parado adquiere la información
  de la siguiente celda, mientras que la siguiente celda adquiere la información que tenía la celda anterior.

Búsqueda de la ficha:
  Para la búsqueda es simple. Se realiza una iteración de x por y por z.
  Para reducir la complejidad algorítmica de dicha iteración, es mejor que se itere menos en la z.
  Entonces, para evitar esto, dependiendo de lo que elija el jugador (precisamente en el tipo de ficha),
  la iteración será hasta un valor z definido según el tipo de ficha que quiere buscar el jugador.