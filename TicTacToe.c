// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

// Variables globales usadas
char tablero[3][3];
typedef enum
{
   JUGADOR_1 = 'X',
   JUGADOR_2 = 'O',
   MAQUINA = JUGADOR_2
} Jugador;
typedef enum
{
   JUGADOR_VS_JUGADOR = 'P',
   JUGADOR_VS_MAQUINA = 'M'
} ModoDeJuego;
ModoDeJuego modoDeJuego;
Jugador jugador;

// Valores de Colores utilizados
#define COLOR_NORMAL "\033[0m"
#define COLOR_VERDE "\033[0;40;32m"
#define COLOR_ROJO "\033[0;31m"
#define COLOR_AZUL "\033[0;1;34m"

// Funciones definidas
void resetearTablero();
void imprimirTablero();
int verEspaciosLibres();
void movimientoJugador(Jugador jugadorEnTurno);
void movimientoMaquina();
char comprobarGanador();
void imprimirGanador(char ganador);
void jugar(ModoDeJuego modoDeJuego);
void turno(ModoDeJuego modoDeJuego);
char seleccionarModoJuego();
void verInstrucciones();
void salir();
bool jugarDeNuevo();
char *imprimirCaracter(char caracter);
void limpiar();
void limpiarBuffer();

int main()
{

   int opcion;

   do
   {
      limpiar();

      printf("\n\t\t\t       %sTIC%s %sTAC%s %sTOE%s     ", COLOR_VERDE, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL);
      printf("\n\t\t\t========================");
      printf("\n\t\t\t|         MENU         |\n");
      printf("\t\t\t========================\n");
      printf("\t\t\t|1. Jugar              |\n");
      printf("\t\t\t|2. Ver instrucciones  |\n");
      printf("\t\t\t|3. Salir              |\n");
      printf("\t\t\t========================");
      printf("\n\t\t\t|Ingrese una opción: ");
      scanf("%d", &opcion);

      switch (opcion)
      {
      case 1:
         modoDeJuego = seleccionarModoJuego();
         jugar(modoDeJuego);
         break;
      case 2:
         verInstrucciones();
         break;
      case 3:
         salir();
         break;
      default:
         printf("\n\t\t\tOpción inválida. Ingrese una opción válida.");
         Sleep(5000);
         break;
      }

      while (getchar() != '\n')
         ;

   } while (opcion != 3);

   return 0;
}

// Función para reemplazar las 'X' y 'O', para resetear el tablero
void resetearTablero()
{
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         tablero[i][j] = ' ';
      }
   }
}

// Función para imprimir el tablero con cada valor de este
void imprimirTablero()
{
   printf("\n\t\t\t  %s | %s | %s ", imprimirCaracter(tablero[0][0]), imprimirCaracter(tablero[0][1]), imprimirCaracter(tablero[0][2]));
   printf("\n\t\t\t ---|---|---\n");
   printf("\t\t\t  %s | %s | %s ", imprimirCaracter(tablero[1][0]), imprimirCaracter(tablero[1][1]), imprimirCaracter(tablero[1][2]));
   printf("\n\t\t\t ---|---|---\n");
   printf("\t\t\t  %s | %s | %s ", imprimirCaracter(tablero[2][0]), imprimirCaracter(tablero[2][1]), imprimirCaracter(tablero[2][2]));
   printf("\n\n");
}

// Función para verificar la cantidad de espacios libres para jugar
int verEspaciosLibres()
{
   int espaciosLibres = 9;

   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         if (tablero[i][j] != ' ')
         {
            espaciosLibres--;
         }
      }
   }

   return espaciosLibres;
}

// Función para que el jugador haga su movimiento
void movimientoJugador(Jugador jugadorEnTurno)
{
   int x, y;

   do
   {

      printf("\t\t  Introduzca una fila #(1-3): ");
      if (scanf("%d", &x) != 1)
      {
         printf("\n\t\t        Entrada inválida\n");
         limpiarBuffer();
         Sleep(3000);
         break;
      }
      x--;
      printf("\t\t  Introduzca una columna #(1-3): ");
      if (scanf("%d", &y) != 1)
      {
         printf("\n\t\t        Entrada inválida\n");
         limpiarBuffer();
         Sleep(3000);
         break;
      }
      y--;

      if (tablero[x][y] != ' ')
      {
         printf("\n\t\t      Movimiento Inválido!\n");
         Sleep(3000);
         break;
      }
      else
      {
         tablero[x][y] = jugadorEnTurno;
         break;
      }

   } while (tablero[x][y] != ' ');
}

// Función para que el la maquina haga su movimiento, el cual es aletorio
void movimientoMaquina()
{

   printf("\t\t   Realizando movimiento");
   for (int i = 0; i < 3; i++)
   {
      printf("%s.%s", COLOR_VERDE, COLOR_NORMAL);
      Sleep(750);
   }

   // Crea una semilla base en el tiempo de ahora
   srand(time(0));
   int x, y;

   if (verEspaciosLibres() > 0)
   {
      do
      {
         // Obtenemos los movimientos de X e Y en base a modulo de 3, el cual podra arrojar los valores del 1 al 3
         x = rand() % 3;
         y = rand() % 3;
      } while (tablero[x][y] != ' ');

      tablero[x][y] = MAQUINA;
   }
   else
   {
      imprimirGanador(' ');
   }
}

// Función para comprobar el ganador
char comprobarGanador()
{

   // Comprobamos Filas y Columnas
   for (int i = 0; i < 3; i++)
   {
      bool esGanadorPorFila = tablero[i][0] == tablero[i][1] && tablero[i][0] == tablero[i][2];
      bool esGanadorPorColumna = tablero[0][i] == tablero[1][i] && tablero[0][i] == tablero[2][i];

      if (esGanadorPorFila)
      {
         return tablero[i][0];
      }
      if (esGanadorPorColumna)
      {
         return tablero[0][i];
      }
   }

   // Comprobamos Diagonales
   bool esGanadorPorDiagonalPrincipal = (tablero[0][0] == tablero[1][1] && tablero[0][0] == tablero[2][2]);
   bool esGanadorPorDiagonalSecundaria = (tablero[0][2] == tablero[1][1] && tablero[0][2] == tablero[2][0]);

   if (esGanadorPorDiagonalPrincipal || esGanadorPorDiagonalSecundaria)
   {
      return tablero[1][1];
   }

   return ' ';
}

// Función imprimir el ganador, en el caso de que sea una partida contra la CPU o contra otro jugador
void imprimirGanador(char ganador)
{
   if (modoDeJuego == JUGADOR_VS_JUGADOR)
   {
      if (ganador == JUGADOR_1)
      {
         printf("\t\t      GANADOR: %sJUGADOR 1%s\n", COLOR_ROJO, COLOR_NORMAL);
      }
      else if (ganador == JUGADOR_2)
      {
         printf("\t\t      GANADOR: %sJUGADOR 2%s\n", COLOR_AZUL, COLOR_NORMAL);
      }
      else
      {
         printf("\t\t           EMPATE!\n");
      }
   }
   else if (modoDeJuego == JUGADOR_VS_MAQUINA)
   {
      if (ganador == JUGADOR_1)
      {
         printf("\t\t\t  GANASTE!\n");
      }
      else if (ganador == MAQUINA)
      {
         printf("\t\t\t  PERDISTE!\n");
      }
      else
      {
         printf("\t\t\t    EMPATE!\n");
      }
   }
}


// Función para poder seleccionar el modo de juego, ya sea contra la maquina o la CPU
char seleccionarModoJuego()
{
   char modo;

   do
   {
      fflush(stdin);
      limpiar();
      printf("\n\t\t\t       %sTIC%s %sTAC%s %sTOE%s     ", COLOR_VERDE, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL);
      printf("\n\t\t\t========================");
      printf("\n\t\t\t|         MENU         |\n");
      printf("\t\t\t========================");
      printf("\n\t\t\t|    Modo de juego:    |");
      printf("\n\t\t\t|Jugador vs Jugador (%sP%s)|\n\t\t\t|Jugador vs Máquina (%sM%s)|", COLOR_VERDE, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL);
      printf("\n\t\t\t========================");
      printf("\n\t\t\t|Seleccione el modo de Juego: ");
      scanf("%c", &modo);
      modo = toupper(modo);
      if (modo != 'P' && modo != 'M')
      {
         printf("\n\t\t\tPor favor, introduce una de las opciones válidas (1 o 2)");
         Sleep(3000);
      }
   } while ((modo != JUGADOR_VS_JUGADOR) && (modo != JUGADOR_VS_MAQUINA));

   return modo;
}

// Función para poder iniciar y jugar el Tres en Raya
void jugar(ModoDeJuego modoDeJuego)
{

   do
   {
      char ganador = ' ';
      resetearTablero();

      while (ganador == ' ' && verEspaciosLibres() != 0)
      {
         fflush(stdin);
         limpiar();
         turno(modoDeJuego);
         imprimirTablero();

         if (modoDeJuego == JUGADOR_VS_JUGADOR)
         {
            if (verEspaciosLibres() % 2 == 1)
            {
               movimientoJugador(JUGADOR_1);
            }
            else
            {
               movimientoJugador(JUGADOR_2);
            }
         }
         else if (modoDeJuego == JUGADOR_VS_MAQUINA)
         {
            if (verEspaciosLibres() % 2 == 1)
            {
               movimientoJugador(JUGADOR_1);
            }
            else
            {
               movimientoMaquina();
            }
         }

         ganador = comprobarGanador();

         if (ganador != ' ' || verEspaciosLibres() == 0)
         {
            break;
         }
      }

      limpiar();
      imprimirTablero();
      imprimirGanador(ganador);

   } while (!jugarDeNuevo());
}


// Función para imprimir como encabezado del tablera de quién es el turno actual
void turno(ModoDeJuego modoDeJuego)
{
   if (modoDeJuego == JUGADOR_VS_JUGADOR)
   {
      if (verEspaciosLibres() % 2 == 1)
      {
         printf("\t\t       TURNO: %sJUGADOR 1%s\n", COLOR_ROJO, COLOR_NORMAL);
      }
      else
      {
         printf("\t\t       TURNO: %sJUGADOR 2%s\n", COLOR_AZUL, COLOR_NORMAL);
      }
   }
   else if (modoDeJuego == JUGADOR_VS_MAQUINA)
   {
      if (verEspaciosLibres() % 2 == 1)
      {
         printf("\t\t        TURNO: %sJUGADOR%s\n", COLOR_ROJO, COLOR_NORMAL);
      }
      else
      {
         printf("\t\t       TURNO: %sMAQUINA%s\n", COLOR_AZUL, COLOR_NORMAL);
      }
   }
}

// Función que explica las instrucciones del juego
void verInstrucciones()
{

   int opcionInstruccion;

   do
   {
      limpiar();
      printf("\n\t\t\t=============================");
      printf("\n\t\t\t|        INSTRUCCIONES      |\n");
      printf("\t\t\t=============================\n");
      printf("\t\t\tTic Tac Toe es un juego cuyo \n");
      printf("\t\t\tobjetivo es tener tu simbolo\n");
      printf("\t\t\ten linea. Ya sea:\n");
      Sleep(7000);

      limpiar();
      printf("\n\t\t\t=============================");
      printf("\n\t\t\t|        INSTRUCCIONES      |\n");
      printf("\t\t\t=============================\n");
      printf("\t\t\t\t En vertical:");
      printf("\n\n\t\t\t\t  %sO%s |   |  ", COLOR_AZUL, COLOR_NORMAL);
      printf("\n\t\t\t\t ---|---|---\n");
      printf("\t\t\t\t  %sO%s |   |  ", COLOR_AZUL, COLOR_NORMAL);
      printf("\n\t\t\t\t ---|---|---\n");
      printf("\t\t\t\t  %sO%s |   |  \n", COLOR_AZUL, COLOR_NORMAL);
      Sleep(7000);

      limpiar();
      printf("\n\t\t\t=============================");
      printf("\n\t\t\t|        INSTRUCCIONES      |\n");
      printf("\t\t\t=============================\n");
      printf("\t\t\t       En horizontal:");
      printf("\n\n\t\t\t\t    |   |  ");
      printf("\n\t\t\t\t ---|---|---\n");
      printf("\t\t\t\t  %sX%s | %sX%s | %sX%s ", COLOR_ROJO, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL);
      printf("\n\t\t\t\t ---|---|---\n");
      printf("\t\t\t\t    |   |  \n");
      Sleep(7000);

      limpiar();
      printf("\n\t\t\t=============================");
      printf("\n\t\t\t|        INSTRUCCIONES      |\n");
      printf("\t\t\t=============================\n");
      printf("\t\t\t       O, en diagonal:");
      printf("\n\n\t\t\t\t  %sO%s |   |  ", COLOR_AZUL, COLOR_NORMAL);
      printf("\n\t\t\t\t ---|---|---\n");
      printf("\t\t\t\t    | %sO%s |  ", COLOR_AZUL, COLOR_NORMAL);
      printf("\n\t\t\t\t ---|---|---\n");
      printf("\t\t\t\t    |   | %sO%s \n", COLOR_AZUL, COLOR_NORMAL);
      Sleep(7000);

      limpiar();
      printf("\n\t\t\t=============================");
      printf("\n\t\t\t|        INSTRUCCIONES      |\n");
      printf("\t\t\t=============================\n");
      printf("\n\t\t\tDeberas introducir la posición");
      printf("\n\t\t\ten la que quieras jugar intro-");
      printf("\n\t\t\tduciendo primero la posición ");
      printf("\n\t\t\tde la fila y luego la columna ");
      printf("\n\t\t\tcorrespondiente. Ej. (1,2)\n");
      Sleep(7000);

      limpiar();
      printf("\n\t\t\t=============================");
      printf("\n\t\t\t|        INSTRUCCIONES      |\n");
      printf("\t\t\t=============================\n");
      printf("\t\t\tUn ejemplo de cada posisición\n\t\t\ten el tablero sería:");
      printf("\n\n\t\t\t     (%s1%s,%s1%s) | (%s1%s,%s2%s) | (%s1%s,%s3%s) ", COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL);
      printf("\n\t\t\t    -------|-------|------\n");
      printf("\t\t\t     (%s2%s,%s1%s) | (%s2%s,%s2%s) | (%s2%s,%s3%s)", COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL);
      printf("\n\t\t\t    -------|-------|------\n");
      printf("\t\t\t     (%s3%s,%s1%s) | (%s3%s,%s2%s) | (%s3%s,%s3%s) \n", COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL);
      printf("\n\t\t\t¡Buena suerte en tus partidas!");
      Sleep(10000);
      limpiar();

      printf("\n\t\t\t=============================");
      printf("\n\t\t\t|        INSTRUCCIONES      |\n");
      printf("\t\t\t=============================\n");
      printf("\n\t\t\t1. Repetir Instrucciones\n\t\t\t2. Volver al Menú");
      printf("\n\t\t\tIngrese una opción: ");
      scanf("%d", &opcionInstruccion);

   } while (opcionInstruccion == 1 && opcionInstruccion != 2);

   printf("\n\t\t\tVolviendo al Menú");
   for (int i = 0; i < 3; i++)
   {
      printf("%s.%s", COLOR_VERDE, COLOR_NORMAL);
      Sleep(750);
   }
}

// Función que sirve para salir del juego
void salir()
{
   limpiar();
   printf("\n\n\n\t\t\t!Gracias por jugar!");
   printf("\n\n\t\t\t    Saliendo");
   for (int i = 0; i < 3; i++)
   {
      printf("%s.%s", COLOR_VERDE, COLOR_NORMAL);
      Sleep(750);
   }
   printf("\n\n\n");
}

// Función para poder repetir el el juego o finalizarlo
bool jugarDeNuevo()
{
   Sleep(2000);
   while (true)
   {
      char opcion;

      limpiar();
      fflush(stdin);
      printf("\t\t\t¿Deseas jugar de nuevo? (%sy%s/%sn%s): ", COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL);
      scanf("%c", &opcion);

      opcion = toupper(opcion);

      if (opcion == 'Y')
      {
         return false;
      }
      else if (opcion == 'N')
      {
         printf("\n\t\t\tVolviendo al Menú");
         for (int i = 0; i < 3; i++)
         {
            printf("%s.%s", COLOR_VERDE, COLOR_NORMAL);
            Sleep(750);
         }

         return true;
      }
      else
      {
         printf("\nPor favor introducir una de las opciones válidas");
         Sleep(2000);
      }
   }
}

// Función para poner los colores de las X (rojo) y las X (azul)
char *imprimirCaracter(char caracter)
{
   char *color;

   // Determinar el formato de color según el carácter
   if (caracter == 'X')
   {
      color = COLOR_ROJO;
   }
   else if (caracter == 'O')
   {
      color = COLOR_AZUL;
   }
   else
   {
      return " "; // Retornar un espacio en blanco, en caso de que el espacio del tablero esta vació
   }

   // Aqui se reserva memoria dinámica para almacenar una cadena de caracteres de tamaรฑo 20 y guarda el puntero a esa memoria en la variable caracterConColor
   char *caracterConColor = (char *)malloc(20 * sizeof(char));

   // La Función "sprintf" reescribe la cadena de caracteres a guardar y la almacena en el buffer de memoria dado (caracterConColor)
   sprintf(caracterConColor, "%s%c%s", color, caracter, COLOR_NORMAL);

   return caracterConColor;
}

// Función para limpiar la pantalla
void limpiar()
{
   printf("\033[2J\033[H");
}

// Funcion la cual limpia el buffer con el fin de evitar errores
void limpiarBuffer()
{
   int c; // Declaramos una variable
   // En este bucle se toman todos los valores, se para hasta que no haya mas valores tomados por el getchar() y hasta que no sea el final del archivo (EOF) que significa que no hay mas entradas en el archivo
   while ((c = getchar()) != '\n' && c != EOF);
}