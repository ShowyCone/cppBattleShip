#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

// Declaración de variables globales
int attempts = 8;
char abc[] = "ABCDEFGH";
int board[8][8], secretBoard[8][8], startingBoard[8][8];
int row, column;
int letterCoord, numberCoord;
int iter = 0;
int win = 0;

// Función que renderiza la matriz
void matrixRender(int added, int boardType[8][8]) {
    if (added) {
        // [Number-Row] [Letter-Column]

        bool condition1, condition2;
        condition1 = secretBoard[numberCoord][letterCoord] == 0 && (secretBoard[numberCoord][letterCoord + 1] == 1 || secretBoard[numberCoord][letterCoord + 1] == 2);
        condition2 = secretBoard[numberCoord][letterCoord] == 1 || secretBoard[numberCoord][letterCoord] == 2;
        if ((condition1) || (condition2)) {
            iter--;
        } else {
            secretBoard[numberCoord][letterCoord] = 1;
            secretBoard[numberCoord][letterCoord + 1] = 2;
        }
        if (letterCoord == 7) {
            secretBoard[numberCoord][letterCoord] = 0;
            secretBoard[numberCoord][letterCoord + 1] = 0;
            if (secretBoard[numberCoord + 1][1] == 2) secretBoard[numberCoord + 1][0] = 1;

            iter--;
        }
    } else {
        cout << " ----------------------------------------" << endl;
        for (row = 0; row < 8; row++) {
            for (int i = 0; i < 8; i++) {
                if (row == 0 && i == 0) cout << " | * ||";
                if (row == 0) cout << " | " << abc[i];
            }
            cout << " | " << endl;
            if (row == 0) {
                cout << " ========================================" << endl;
            }
            for (column = 0; column < 8; column++) {
                if (column == 0) cout << " | " << row + 1 << " ||";
                cout << " | " << boardType[row][column];
            }
        }
        cout << " | " << endl;
        cout << " ----------------------------------------" << endl;
    }
}

// Asigna de manera aleatoria la posicion de los buques
void randomAssignment() {
    for (iter = 0; iter <= 7; iter++) {
        numberCoord = rand() % 8;
        letterCoord = rand() % 8;
        matrixRender(1, board);
    }
}

// Recibe una letra(que corresponde a una coordenada) y devuelve su indice en la matriz(convertido en un numero)
int letterToNumber(char letter) {
    int accountant = 1;
    int result = letter;
    while (accountant <= 8) {
        result = letter - accountant;
        if (result == 64) {
            return accountant;
        }
        accountant++;
    }
    return accountant;
}

// Verifica que en la posición dada por el usuario haya o no un buque
void isShip(int rowC, int columnC) {
    if (secretBoard[rowC][columnC] == 1 || secretBoard[rowC][columnC] == 2) {
        cout << endl;
        if (secretBoard[rowC][columnC] == 1) {
            board[rowC][columnC] = 1;
            board[rowC][columnC + 1] = 1;
            system("cls");
            cout << endl;
            cout << "Has hacertado!" << endl;
            cout << "Te quedan " << attempts << " intentos" << endl;
            secretBoard[rowC][columnC] = 0;
        } else if (secretBoard[rowC][columnC] == 2) {
            board[rowC][columnC - 1] = 1;
            board[rowC][columnC] = 1;
            system("cls");
            cout << endl;
            cout << "Has hacertado!" << endl;
            cout << "Te quedan " << attempts << " intentos" << endl;
            secretBoard[rowC][columnC] = 0;
        } 
        cout << endl;
        win++;
        if (win == 8) {
            attempts = 0;
        }
    } else {
        system("cls");
        cout << "Has fallado vuelve a intentarlo" << endl;
        attempts--;
        cout << "Te quedan " << attempts << " intentos" << endl;
    }
}

// Función principal del juego
main() {
    int firstCoord, secondCoord;
    char letterColumn;
    int x, y;

    // Modifica la semilla de función rand dependiendo de la hora del dispositivo para asegurar aleatoriedad
    srand(time(NULL));

    randomAssignment();

    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            startingBoard[x][y] = secretBoard[x][y];
        }
    }

    do {
        matrixRender(0, board);
        cout <<"Ingrese la primera coordenada [ingrese un numero valido (1, 2, 3, 4, 5, 6, 7, 8)]: ";
        cin >> firstCoord;
        cout << endl << "Ingrese la segunda coordenada [ingrese una letra en mayuscula valida (A, B, C, D, E, F, G, H)]: ";
        cin >> letterColumn;

        firstCoord = firstCoord - 1;
        secondCoord = letterToNumber(letterColumn) - 1;

        isShip(firstCoord, secondCoord);
        if (attempts == 0) {
            system("cls");
            if (win == 8) cout << "Has ganado!" << endl;
            else if (win != 8) cout << "Has perdido!" << endl;
            cout << endl << "El tablero inicial es el siguiente: " << endl;
            matrixRender(0, startingBoard);
            cout << endl << "Tu tablero de juego es el siguiente: " << endl;
            matrixRender(0, board);
        }
    } while (attempts);

    return 0;
}