#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

// Variables globales usadas
char tablero[3][3];

/*
 * @brief Enumeración para los diferentes jugadores
 */
typedef enum
{
    JUGADOR_1 = 'X',
    JUGADOR_2 = 'O',
    MAQUINA = JUGADOR_2
} Jugador;

/*
 * @brief Enumeración para los diferentes modos de juegos
 */
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
void imprimirMenuTitulo();
void imprimirInstruccionesTitulo();
bool jugarDeNuevo();
char *imprimirCaracter(char caracter);
void limpiar();
void limpiarBuffer();

int main()
{
    int opcion;

    do
    {

        imprimirMenuTitulo();
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

        limpiarBuffer();

    } while (opcion != 3);

    return 0;
}

/*
 * @brief Limpiar el tablero
 *
 * Reemplazando las 'X' y 'O' del tablero con un espacio en blanco
 *
 * @return Void.
 */
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

/*
 * @brief Imprimir el tablero
 *
 * Cada valor se imprime formateado con el color correspondiente
 *
 * @return Void.
 */
void imprimirTablero()
{
    printf("\n\t\t\t  %s | %s | %s ", imprimirCaracter(tablero[0][0]), imprimirCaracter(tablero[0][1]), imprimirCaracter(tablero[0][2]));
    printf("\n\t\t\t ---|---|---\n");
    printf("\t\t\t  %s | %s | %s ", imprimirCaracter(tablero[1][0]), imprimirCaracter(tablero[1][1]), imprimirCaracter(tablero[1][2]));
    printf("\n\t\t\t ---|---|---\n");
    printf("\t\t\t  %s | %s | %s ", imprimirCaracter(tablero[2][0]), imprimirCaracter(tablero[2][1]), imprimirCaracter(tablero[2][2]));
    printf("\n\n");
}

/*
 * @brief Verificar la cantidad de espacion libres
 *
 * Cada posición disponible menos se contabiliza si la posición no es un espacio libre.
 *
 * @return los espacios libres disponibles con un entero.
 */
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

/*
 * @brief Movimiento del jugador
 *
 * El jugador hace su movimiento en base a las filas y columnas del tablero disponibles
 *
 * @param jugadorEnTurno El jugador que le toca jugar
 * @return Void.
 */
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

/*
 * @brief Movimiento de la maquina
 *
 * El movimiento de la maquina es generado de manera completamente aleatorio
 *
 * @return Void.
 */
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

/*
 * @brief Comprobar el ganador
 *
 * Se comprueban si las filas, las columnas y las diagonales (principal, de izquierda a derecha; y
 * la secundaria, de derecha a izquierda), en caso de que no halla ganador se devuelve un espacio,
 * que significa que ninguno a ganado o ganó.
 *
 * @return El carácter del posible ganador.
 */
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
/*
 * @brief Imprimir por consola el ganador
 *
 * En el caso de que sea una partida contra la CPU o contra otro jugador
 *
 * @param ganador El carácter de quién gano la partida
 * @return Void.
 */
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

/*
 * @brief Selección de modo de juego
 *
 * Ya sea, contra la maquina o la CPU, y unicamente estas dos opciones.
 *
 * @return El carácter correspondiente al modo de juego seleccionado.
 */
char seleccionarModoJuego()
{
    char modo;

    do
    {
        imprimirMenuTitulo();
        printf("\t\t\t|    Modo de juego:    |");
        printf("\n\t\t\t|Jugador vs Jugador (%sP%s)|\n\t\t\t|Jugador vs Máquina (%sM%s)|", COLOR_VERDE, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL);
        printf("\n\t\t\t========================");
        printf("\n\t\t\t|Seleccione el modo de Juego: ");
        scanf("%c", &modo);
        modo = toupper(modo);
        if (modo != 'P' && modo != 'M')
        {
            printf("\n\t\t\tPor favor, introduce una de las opciones válidas (P o M)");
            Sleep(3000);
        }
    } while ((modo != JUGADOR_VS_JUGADOR) && (modo != JUGADOR_VS_MAQUINA));

    return modo;
}

/*
 * @brief Jugar la partida
 *
 * Se inicializa el ganador y se juegan por turnos dependiendo el modo de juego seleccionado,
 * esto cambiando de turno dependiendo de quién le toque jugar. En cada movimiento se revisa el
 * ganador en caso de que halla, se pregunta si desea jugar de nuevo.
 *
 * @param modoDeJuego Tipo de modo de juego seleccionado para jugar.
 * @return Void.
 */
void jugar(ModoDeJuego modoDeJuego)
{

    do
    {
        char ganador = ' ';
        resetearTablero();

        while (ganador == ' ' && verEspaciosLibres() != 0)
        {
            limpiarBuffer();
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

    } while (jugarDeNuevo());
}

/*
 * @brief Imprimir, como encabezado del tablero, de quién es el turno actual
 *
 * Se imprime dependiendo de los espacios restantes, de quién es el turno, ya sea si es Jugador vs
 * Jugador o Jugador vs Maquina.
 *
 * @param modoDeJuego El modo de juego correspondiente que se esta jugando.
 * @return Void.
 */
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

/*
 * @brief Imprimir las instrucciones del juego
 *
 * Se repite si el jugador decide que lo necesita.
 *
 * @return Void.
 */
void verInstrucciones()
{

    int opcionInstruccion;

    do
    {
        imprimirInstruccionesTitulo();
        printf("\t\t\tTic Tac Toe es un juego cuyo \n");
        printf("\t\t\tobjetivo es tener tu simbolo\n");
        printf("\t\t\ten linea. Ya sea:\n");
        Sleep(7000);

        imprimirInstruccionesTitulo();
        printf("\t\t\t\t En vertical:");
        printf("\n\n\t\t\t\t  %sO%s |   |  ", COLOR_AZUL, COLOR_NORMAL);
        printf("\n\t\t\t\t ---|---|---\n");
        printf("\t\t\t\t  %sO%s |   |  ", COLOR_AZUL, COLOR_NORMAL);
        printf("\n\t\t\t\t ---|---|---\n");
        printf("\t\t\t\t  %sO%s |   |  \n", COLOR_AZUL, COLOR_NORMAL);
        Sleep(7000);

        imprimirInstruccionesTitulo();
        printf("\t\t\t       En horizontal:");
        printf("\n\n\t\t\t\t    |   |  ");
        printf("\n\t\t\t\t ---|---|---\n");
        printf("\t\t\t\t  %sX%s | %sX%s | %sX%s ", COLOR_ROJO, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL);
        printf("\n\t\t\t\t ---|---|---\n");
        printf("\t\t\t\t    |   |  \n");
        Sleep(7000);

        imprimirInstruccionesTitulo();
        printf("\t\t\t       O, en diagonal:");
        printf("\n\n\t\t\t\t  %sO%s |   |  ", COLOR_AZUL, COLOR_NORMAL);
        printf("\n\t\t\t\t ---|---|---\n");
        printf("\t\t\t\t    | %sO%s |  ", COLOR_AZUL, COLOR_NORMAL);
        printf("\n\t\t\t\t ---|---|---\n");
        printf("\t\t\t\t    |   | %sO%s \n", COLOR_AZUL, COLOR_NORMAL);
        Sleep(7000);

        imprimirInstruccionesTitulo();
        printf("\t\t\tDeberas introducir la posición");
        printf("\n\t\t\ten la que quieras jugar intro-");
        printf("\n\t\t\tduciendo primero la posición ");
        printf("\n\t\t\tde la fila y luego la columna ");
        printf("\n\t\t\tcorrespondiente. Ej. (1,2)\n");
        Sleep(7000);

        imprimirInstruccionesTitulo();
        printf("\t\t\tUn ejemplo de cada posisición\n\t\t\ten el tablero sería:");
        printf("\n\n\t\t\t     (%s1%s,%s1%s) | (%s1%s,%s2%s) | (%s1%s,%s3%s) ", COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL);
        printf("\n\t\t\t    -------|-------|------\n");
        printf("\t\t\t     (%s2%s,%s1%s) | (%s2%s,%s2%s) | (%s2%s,%s3%s)", COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL);
        printf("\n\t\t\t    -------|-------|------\n");
        printf("\t\t\t     (%s3%s,%s1%s) | (%s3%s,%s2%s) | (%s3%s,%s3%s) \n", COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL);
        printf("\n\t\t\t¡Buena suerte en tus partidas!");
        Sleep(10000);
        limpiar();

        imprimirInstruccionesTitulo();
        printf("\t\t\t1. Repetir Instrucciones\n\t\t\t2. Volver al Menú");
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

/*
 * @brief Salir del juego
 *
 * Se imprime un mensaje diciendo que se esta saliendo del juego.
 *
 * @return Void.
 */
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

/*
 * @brief Imprimir el menu del Titulo
 *
 * Se imprime el header del menú
 *
 * @return Void.
 */
void imprimirMenuTitulo()
{
    limpiarBuffer();
    limpiar();
    printf("\n\t\t\t       %sTIC%s %sTAC%s %sTOE%s     ", COLOR_VERDE, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL, COLOR_AZUL, COLOR_NORMAL);
    printf("\n\t\t\t========================");
    printf("\n\t\t\t|         MENU         |\n");
    printf("\t\t\t========================\n");
}

/*
 * @brief Imprimir el menu de las Instruccioes
 *
 * Se imprime el header de las instrucciones
 *
 * @return Void.
 */
void imprimirInstruccionesTitulo()
{
    limpiar();
    printf("\n\t\t\t=============================");
    printf("\n\t\t\t|        INSTRUCCIONES      |\n");
    printf("\t\t\t=============================\n");
}

/*
 * @brief Repetir el juego o finalizarlo
 *
 * Con un bucle se pregunta si se desea jugar de nuevo, en caso que si se devuelve un true, 
 * y si no quiere seguir devuelve un false, volviendo asi el menu
 *
 * @return El valor booleano correspondiente a si desea jugar de nuevo.
 */
bool jugarDeNuevo()
{
    Sleep(2000);
    while (true)
    {
        char opcion;

        limpiar();
        limpiarBuffer();
        printf("\t\t\t¿Deseas jugar de nuevo? (%sy%s/%sn%s): ", COLOR_AZUL, COLOR_NORMAL, COLOR_ROJO, COLOR_NORMAL);
        scanf("%c", &opcion);

        opcion = toupper(opcion);

        if (opcion == 'Y')
        {
            return true;
        }
        else if (opcion == 'N')
        {
            printf("\n\t\t\tVolviendo al Menú");
            for (int i = 0; i < 3; i++)
            {
                printf("%s.%s", COLOR_VERDE, COLOR_NORMAL);
                Sleep(750);
            }

            return false;
        }
        else
        {
            printf("\nPor favor introducir una de las opciones válidas");
            Sleep(2000);
        }
    }
}


/*
 * @brief Formetear las letras X a rojo y los O a azul
 *
 * Se pone el carácter en un espacio dinámico de memoria, y luego se formatea con la
 * función sprint
 * 
 * @param El caracter a formatear.
 * @return El caracter formateado con el color correspondiente.
 */
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

    // Aqui se reserva memoria dinámica para almacenar una cadena de caracteres de tamaño 20 y guarda el puntero a esa memoria en la variable caracterConColor
    char *caracterConColor = (char *)malloc(20 * sizeof(char));

    // La Función "sprintf" reescribe la cadena de caracteres a guardar y la almacena en el buffer de memoria dado (caracterConColor)
    sprintf(caracterConColor, "%s%c%s", color, caracter, COLOR_NORMAL);

    return caracterConColor;
}

/*
 * @brief Limpiar la consola
 *
 * @return Void.
 */
void limpiar()
{
    printf("\033[2J\033[H");
}

/*
 * @brief Limpiar el búffer para evitar errores
 *
 * Con un bucle se toman todos los valores hasta que la variable no sea un carácter
 * y hasta que no sea el final del archivo (EOF), significando que no hay mas
 * entradas en el archivo
 *
 * @return Void.
 */
void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}