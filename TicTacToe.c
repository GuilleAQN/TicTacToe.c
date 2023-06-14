// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char tablero[3][3];
const char JUGADOR = 'X';
const char MAQUINA = 'O';

void resetearTablero();
void imprimirTablero();
int verEspaciosLibres();
void movimientoJugador();
void movimientoMaquina();
char comprobarGanador();
void imprimirGanador(char);

int main(){

   char ganador = ' ';
   char respuesta = ' ';

   do{

      ganador = ' ';
      respuesta = ' ';
      resetearTablero();

      while(ganador == ' ' && verEspaciosLibres() != 0){
         imprimirTablero();

         movimientoJugador();
         ganador = comprobarGanador();
         if(ganador != ' ' || verEspaciosLibres() == 0){
            break;
         }

         movimientoMaquina();
         ganador = comprobarGanador();
         if(ganador != ' ' || verEspaciosLibres() == 0){
            break;
         }
      }

      imprimirTablero();
      imprimirGanador(ganador);

      printf("\nTe gustaría jugar de nuevo? (Y/N): ");
      fflush(stdin);
      scanf("%c", &respuesta);
      respuesta = toupper(respuesta);

   } while (respuesta == 'Y');

   printf("Gracias por jugar!");

   return 0;
}

void resetearTablero(){

   for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
         tablero[i][j] = ' ';
      }
   }

}

void imprimirTablero(){

   printf("\n %c | %c | %c ", tablero[0][0], tablero[0][1], tablero[0][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", tablero[1][0], tablero[1][1], tablero[1][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", tablero[2][0], tablero[2][1], tablero[2][2]);
   printf("\n");

}

int verEspaciosLibres(){

   int espaciosLibres = 9;

   for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
         if(tablero[i][j] != ' '){
            espaciosLibres--;
         }
      }
   }
   return espaciosLibres;

}

void movimientoJugador(){

   int x;
   int y;

   do{

      printf("Introduzca una fila #(1-3): ");
      scanf("%d", &x);
      x--;
      printf("Introduzca una columna #(1-3): ");
      scanf("%d", &y);
      y--;

      if(tablero[x][y] != ' '){
         printf("Movimiento Inválido!\n");
      }
      else{
         tablero[x][y] = JUGADOR;
         break;
      }
   } while (tablero[x][y] != ' ');
   
}

void movimientoMaquina(){

   //Crea una semilla base en el tiempo de ahora
   srand(time(0));
   int x;
   int y;

   if(verEspaciosLibres() > 0){
      do{
         x = rand() % 3;
         y = rand() % 3;
      } while (tablero[x][y] != ' ');
      
      tablero[x][y] = MAQUINA;
   }
   else{
      imprimirGanador(' ');
   }

}

char comprobarGanador(){

   //Comprobamos Filas
   for(int i = 0; i < 3; i++){
      if(tablero[i][0] == tablero[i][1] && tablero[i][0] == tablero[i][2])
      {
         return tablero[i][0];
      }
   }

   //Comprobamos Columnas
   for(int i = 0; i < 3; i++){
      if(tablero[0][i] == tablero[1][i] && tablero[0][i] == tablero[2][i]){
         return tablero[0][i];
      }
   }

   //Comprobamos Diagonales
   if(tablero[0][0] == tablero[1][1] && tablero[0][0] == tablero[2][2]){
      return tablero[0][0];
   }
   if(tablero[0][2] == tablero[1][1] && tablero[0][2] == tablero[2][0]){
      return tablero[0][2];
   }

   return ' ';

}

void imprimirGanador(char ganador){

   if(ganador == JUGADOR){
      printf("GANASTE!");
   }
   else if(ganador == MAQUINA){
      printf("PERDISTE!");
   }
   else{
      printf("EMPATE!");
   }
   
}