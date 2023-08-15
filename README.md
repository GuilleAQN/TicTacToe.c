# Juego de <span style="color:green">Tic</span> <span style="color: red;">Tac</span> <span style="color: blue;">Toe</span>

⁣        ⭕ | ⭕ |❌\n
        ➖➕➖➕➖
        ⭕ |⁣ ❌| ⭕
        ➖➕➖➕➖
        ❌ | ❌| ⭕

Este es un juego de Tres en Raya implementado en el lenguaje de programación C, que permite a dos jugadores competir entre sí o jugar contra la computadora. El juego se ejecuta en la consola y presenta una interfaz simple pero efectiva para disfrutar del clásico juego.

## Características

- **Modos de juego**: <span style="color: green;">Jugador vs Jugador (PvP)</span> y <span style="color: red;">Jugador vs Máquina (PvE)</span>.
- **Interfaz de consola interactiva y fácil de entender**.
- **Opción para ver las instrucciones del juego**.
- **Sistema de colores para distinguir los movimientos de los jugadores**.
- **Opción para jugar múltiples partidas consecutivas**.
- **Verificación de ganador y empate**.
- Elección de ser el jugador <span style="color: red;">X (rojo)</span> o el jugador <span style="color: blue;">O (azul)</span>.

## Instrucciones

1. Ejecuta el programa y elige una de las opciones del menú principal:
   - **Jugar**: Ingresa al modo de juego y selecciona el modo PvP o PvE.
   - **Ver instrucciones**: Lee una breve explicación de cómo jugar al Tres en Raya.
   - **Salir**: Finaliza el juego.

2. En el modo de juego, sigue las instrucciones para realizar tu movimiento:
   - **Ingresa la fila (1-3)** donde deseas colocar tu símbolo.
   - **Ingresa la columna (1-3)** donde deseas colocar tu símbolo.

3. El juego mostrará el tablero actualizado después de cada movimiento. Cuando se alcance una victoria o empate, se mostrará el resultado y se te dará la opción de jugar nuevamente.

4. En el modo Jugador vs Máquina, la máquina realizará movimientos automáticos basados en una estrategia aleatoria.

## Requisitos

- Compilador de C (por ejemplo, GCC) instalado en tu sistema.
- Sistema operativo compatible con la manipulación de la consola y colores de texto (como Windows).

## Compilación y Ejecución

1. Abre una terminal o línea de comandos en el directorio donde se encuentra el archivo fuente (.c).
2. Compila el programa usando el siguiente comando (si estás utilizando GCC):
   ```bash
   gcc -o TicTacToe TicTacToe.c
    ```
3. Ejecuta el programa compilado:
  ```bash
  ./TicTacToe
   ```

4.## Créditos

Este juego de Tres en Raya fue desarrollado por Omar Guillermo Aquino Mena como proyecto educativo. Siéntete libre de utilizar, modificar y distribuir el código según tus necesidades.

## Notas

- Este programa se basa en la lógica del juego de Tres en Raya y presenta una interfaz simple. Puede haber mejoras adicionales y características avanzadas que se pueden agregar según las necesidades del usuario.

¡Diviértete jugando al Tres en Raya! Si tienes alguna pregunta o sugerencia, no dudes en ponerte en contacto con el desarrollador en [omarguillermo1@gmail.com](mailto:omarguillermo1@gmail.com).
