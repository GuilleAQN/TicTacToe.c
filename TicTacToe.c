// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>


char tablero[3][3];
#define JUGADOR 'X'
#define MAQUINA 'O'

#define COLOR_NORMAL "\033[0m"
#define COLOR_VERDE "\033[0;40;32m"
#define COLOR_ROJO "\033[0;31m"
#define COLOR_AZUL "\033[0;1;34m"

void resetearTablero();
void imprimirTablero();
int verEspaciosLibres();
void movimientoJugador();
void movimientoMaquina();
char comprobarGanador();
void imprimirGanador(char);
boolean jugarDeNuevo();
void limpiar();
char* imprimirCaracter(char caracter);

int main()
{

   char ganador = ' ';
   char respuesta = ' ';

   do
   {

      ganador = ' ';
      respuesta = ' ';
      resetearTablero();

      while (ganador == ' ' && verEspaciosLibres() != 0)
      {
         limpiar();
         imprimirTablero();

         movimientoJugador();
         ganador = comprobarGanador();
         if (ganador != ' ' || verEspaciosLibres() == 0)
         {
            break;
         }

         limpiar();
         movimientoMaquina();
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

   printf("Gracias por jugar!\n\n");

   return 0;
}

// Funcion para reemplazar las 'X' o 'O' para resetear la partida
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

   printf("\n\t %s | %s | %s ", imprimirCaracter(tablero[0][0]), imprimirCaracter(tablero[0][1]), imprimirCaracter(tablero[0][2]));
   printf("\n\t---|---|---\n");
   printf("\t %s | %s | %s ", imprimirCaracter(tablero[1][0]), imprimirCaracter(tablero[1][1]), imprimirCaracter(tablero[1][2]));
   printf("\n\t---|---|---\n");
   printf("\t %s | %s | %s ", imprimirCaracter(tablero[2][0]), imprimirCaracter(tablero[2][1]), imprimirCaracter(tablero[2][2]));
   printf("\n\n");
}

// Función para verificar la cantidad de espacion libres para jugar
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
void movimientoJugador()
{

   int x;
   int y;

   do
   {

      printf("Introduzca una fila #(1-3): ");
      scanf("%d", &x);
      x--;
      printf("Introduzca una columna #(1-3): ");
      scanf("%d", &y);
      y--;

      if (tablero[x][y] != ' ')
      {
         printf("Movimiento Inválido!\n");
      }
      else
      {
         tablero[x][y] = JUGADOR;
         break;
      }

   } while (tablero[x][y] != ' ');
}

// Función para que el la maquina haga su movimiento, el cual es aletorio
void movimientoMaquina()
{

   // Crea una semilla base en el tiempo de ahora
   srand(time(0));
   int x;
   int y;

   if (verEspaciosLibres() > 0)
   {
      do
      {
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

   // Comprobamos Filas
   for (int i = 0; i < 3; i++)
   {
      if (tablero[i][0] == tablero[i][1] && tablero[i][0] == tablero[i][2])
      {
         return tablero[i][0];
      }
   }

   // Comprobamos Columnas
   for (int i = 0; i < 3; i++)
   {
      if (tablero[0][i] == tablero[1][i] && tablero[0][i] == tablero[2][i])
      {
         return tablero[0][i];
      }
   }

   // Comprobamos Diagonales
   if (tablero[0][0] == tablero[1][1] && tablero[0][0] == tablero[2][2])
   {
      return tablero[0][0];
   }
   if (tablero[0][2] == tablero[1][1] && tablero[0][2] == tablero[2][0])
   {
      return tablero[0][2];
   }

   return ' ';
}

// Función imprimir el ganador
void imprimirGanador(char ganador)
{

   if (ganador == JUGADOR)
   {
      printf("GANASTE!\n");
   }
   else if (ganador == MAQUINA)
   {
      printf("PERDISTE!\n");
   }
   else
   {
      printf("EMPATE!\n");
   }
}

// Función para poder repetir el el juego o finalizarlo
boolean jugarDeNuevo()
{
   Sleep(2000);
   while (true)
   {
      char opcion;

      limpiar();
      fflush(stdin);
      printf("Deseas jugar de nuevo (%sy%s/%sn%s): ", COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL);
      scanf("%c", &opcion);

      opcion = toupper(opcion);

      if (opcion == 'Y')
      {
         return false;
      }
      else if (opcion == 'N')
      {
         printf("\nGracias por jugar!!!");
         printf("\nSaliendo");
         for (int i = 0; i < 3; i++)
         {
            printf(".");
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
char* imprimirCaracter(char caracter){
   char* color;

   // Determinar el formato de color según el carácter
   if (caracter == 'X') {
      color = COLOR_ROJO;
   } else if (caracter == 'O') {
      color = COLOR_AZUL;
   } else {
      return " "; // Retornar un espacio en blanco, en caso de que el espacio del tablero esta vació
   }

   char* caracterConColor = (char*)malloc(20 * sizeof(char));
   sprintf(caracterConColor, "%s%c%s", color, caracter, COLOR_NORMAL);

   return caracterConColor;
}

// Función para limpiar la pantalla
void limpiar()
{
   printf("\033[2J\033[H");
}