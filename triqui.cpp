#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <windows.h>

void bienvenida(){
    printf("Juego del triqui\n");
    printf("Usted es el jugador X y la computadora es el jugador O\n");
    printf("El tablero tiene la siguiente forma:\n");
    printf(" 0 | 1 | 2\n");
    printf("---+---+---\n");
    printf(" 3 | 4 | 5\n");
    printf("---+---+---\n");
    printf(" 6 | 7 | 8\n");
}

char cuadricula(int i){
    switch(i){
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }

}

void crearTablero(int b[9]){
    printf(" %c | %c | %c\n", cuadricula(b[0]), cuadricula(b[1]), cuadricula(b[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", cuadricula(b[3]), cuadricula(b[4]), cuadricula(b[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", cuadricula(b[6]), cuadricula(b[7]), cuadricula(b[8]));
}

int gana(const int tablero[9]) {
    unsigned ganadas[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(tablero[ganadas[i][0]] != 0 &&
            tablero[ganadas[i][0]] == tablero[ganadas[i][1]] &&
            tablero[ganadas[i][0]] == tablero[ganadas[i][2]])
            return tablero[ganadas[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player) {
    int ganador = gana(board);
    if(ganador != 0) return ganador*player;

    int movimiento = -1;
    int puntaje = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            int estePuntaje = -minimax(board, player*-1);
            if(estePuntaje > puntaje) {
                puntaje = estePuntaje;
                movimiento = i;
            }
            board[i] = 0;
        }
    }
    if(movimiento == -1) return 0;
    return puntaje;
}

void movimientoAI(int tablero[9]){
    int movimiento = -1;
    int puntaje = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(tablero[i] == 0) {
            tablero[i] = 1;
            int estePuntaje = -minimax(tablero, -1);
            tablero[i] = 0;
            if(estePuntaje > puntaje) {
                puntaje = estePuntaje;
                movimiento = i;
            }
        }
    }
    tablero[movimiento] = 1;
}

void movimientoJugador(int tablero[9]){
    int movimiento = 0;
    do {
        printf("\nIngrese un movimiento de 0 a 8: ");
        scanf("%d", &movimiento);
        if(movimiento < 0 || movimiento > 8 || tablero[movimiento] != 0) {
            printf("Movimiento invalido o casilla ocupada. Por favor, intente de nuevo.\n");
        }
    } while (movimiento < 0 || movimiento > 8 || tablero[movimiento] != 0);
    tablero[movimiento] = -1;
}

int main() {
    char continuar;
    do {
        int tablero[9] = {0,0,0,0,0,0,0,0,0};
        bienvenida();
        printf("1. Para iniciar el Jugador\n");
        printf("2. Para iniciar la Computadora\n");
        int inicio = 0;
        scanf("%d", &inicio);
        printf("\n");
        unsigned turno;
        for(turno = 0; turno < 9 && gana(tablero) == 0; ++turno) {
            if((turno+inicio) % 2 == 0)
                movimientoAI(tablero);
            else {
                crearTablero(tablero);
                movimientoJugador(tablero);
            }
        }
        switch(gana(tablero)) {
            case 0:
                system("color 6");
                printf("Empate\n");
                break;
            case 1:
                system("color 4");
                crearTablero(tablero);
                printf("Perdiste\n");
                break;
            case -1:
                system("color 2");
                printf("Ganaste\n");
                break;
        }
        printf("¿Quieres jugar de nuevo? (S/N): ");
        scanf(" %c", &continuar);
    } while(continuar == 'S' || continuar == 's');
    return 0;
}