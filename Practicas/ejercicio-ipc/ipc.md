# Ejercicio IPC

Un padre inventó un juego de adivinanzas para jugar con sus 10 hijos.

## Explicación del juego:
1) El padre piensa un número secreto random `0≤S<50`.
2) En cada ronda, cada hijo `i` debe pensar un número random `0≤Kᵢ<100`, escribirlo en un papel, y dárselo al padre para que lo lea.
3) El padre va leyendo todos los números en orden.
    - Si el número `Kᵢ > S`, entonces el hijo `i` pierde.
    - Si el número `Kᵢ ≤ S`, entonces el hijo `i` sigue jugando en la siguiente ronda.
4) Luego de la ronda, cada hijo debe esperar un segundo, y luego empezar la nueva ronda (volver al paso 2).
5) El juego continúa indefinidamente mientras quede más de un hijo jugando. En caso de que quede un solo hijo jugando, este es el ganador.


## Ejemplo (con 3 hijos):
Supongamos que el padre piensa número secreto 50.
|  Ronda  | Hijo 1 | Hijo 2 | Hijo 3 |
| ------- | ------ | ------ | ------ |
| Ronda 1 |   ✓ 30 |   ✗ 52 |   ✓ 20 |
| Ronda 2 |   ✓ 49 |     -  |   ✓ 10 |
| Ronda 3 |   ✓ 48 |     -  |   ✗ 80 |

Ganador: Hijo 1 en 3 rondas.

---

Se pide modelar este juego en un programa utilizando pipes y señales, y respetando las siguientes condiciones:
- Cuando un hijo pierda, se debe terminar el proceso mediante una señal de sigkill.
- Cuando un hijo gane, se le debe avisar al mismo mediante una señal de sigterm. Luego, el hijo debe imprimir un mensaje "Gané", junto con su `i`.
- Los hijos deberán esperar un segundo entre cada ronda.
