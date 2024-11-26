#include <stdio.h>
#include <stdlib.h>

#define VAZIO 0
#define JOGADOR1 1
#define JOGADOR2 2

void configTabuleiro(int tabuleiro[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i < 3 && (i + j) % 2 != 0) {
                tabuleiro[i][j] = JOGADOR1;
            } else if (i > 4 && (i + j) % 2 != 0) {
                tabuleiro[i][j] = JOGADOR2;
            } else {
                tabuleiro[i][j] = VAZIO;
            }
        }
    }
}

void imprimirTabuleiro(int tabuleiro[8][8], int pecasComidasJogador1, int pecasComidasJogador2, char *nomeJogador1, char *nomeJogador2) {
    printf("\n  ");
    for (int j = 0; j < 8; j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i);
        for (int j = 0; j < 8; j++) {
            if (tabuleiro[i][j] == JOGADOR1) {
                printf("P ");
            } else if (tabuleiro[i][j] == JOGADOR2) {
                printf("O ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\nPecas comidas:\n");
    printf("%s (P): %d\n", nomeJogador1, pecasComidasJogador1);
    printf("%s (O): %d\n", nomeJogador2, pecasComidasJogador2);
}

int movimentoValido(int tabuleiro[8][8], int x1, int y1, int x2, int y2, int JOGADOR) {
    if (x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8) return 0;

    if (tabuleiro[x2][y2] != VAZIO) return 0;
    if (JOGADOR == JOGADOR1){
        if (x2 - x1 == 1 && abs(y2 - y1) == 1) {
            return 1;
        } else if (x2 - x1 == 2 && abs(y2 - y1) == 2){
            int x3 = (x1 + x2) / 2;
            int y3 = (y1 + y2) / 2;
            if (tabuleiro[x3][y3] == JOGADOR2){
                return 1;
            }
        }
    }

    if (JOGADOR == JOGADOR2){
        if (x1 - x2 == 1 && abs(y2 - y1) == 1){
            return 1;
        } else if (x1 - x2 == 2 && abs(y2 - y1) == 2){
            int x3 = (x1 + x2) / 2;
            int y3 = (y1 + y2) / 2;
            if (tabuleiro[x3][y3] == JOGADOR1){
                return 1;
            }
        }
    }
    return 0;
}

void moverPeca(int tabuleiro[8][8], int x1, int y1, int x2, int y2, int *pecasComidasJogador1, int *pecasComidasJogador2) {
    tabuleiro[x2][y2] = tabuleiro[x1][y1];
    tabuleiro[x1][y1] = VAZIO;

    if (abs(x2 - x1) == 2 && abs(y2 - y1) == 2) {
        int x3 = (x1 + x2) / 2;
        int y3 = (y1 + y2) / 2;
        if (tabuleiro[x3][y3] == JOGADOR1){
            (*pecasComidasJogador2)++;
        } else if (tabuleiro[x3][y3] == JOGADOR2)
            (*pecasComidasJogador1)++;
        tabuleiro[x3][y3] = VAZIO;
    }
}

int temMovimentoValido(int tabuleiro[8][8], int JOGADOR) {
    for (int x1 = 0; x1 < 8; x1++) {
        for (int y1 = 0; y1 < 8; y1++) {
            if (tabuleiro[x1][y1] == JOGADOR) {
                for (int dx = -2; dx <= 2; dx++) {
                    for (int dy = -2; dy <= 2; dy++) {
                        int x2 = x1 + dx;
                        int y2 = y1 + dy;

                        if (movimentoValido(tabuleiro, x1, y1, x2, y2, JOGADOR)) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void menuInicial() {
    int opcao;
    while (1) {
        printf("Bem-vindo ao jogo de Damas!\n");
        printf("1. Jogar\n");
        printf("2. Sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                return;
            case 2:
                printf("Saindo do jogo...\n");
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

int main() {
    int tabuleiro[8][8];
    int pecasComidasJogador1 = 0, pecasComidasJogador2 = 0;
    int jogadorAtual = JOGADOR1;
    char nomeJogador1[50], nomeJogador2[50];

    menuInicial();
    printf("Digite o nome do Jogador 1 (P): ");
    scanf("%s", nomeJogador1);
    printf("Digite o nome do Jogador 2 (O): ");
    scanf("%s", nomeJogador2);
    configTabuleiro(tabuleiro);

    while (1) {
        imprimirTabuleiro(tabuleiro, pecasComidasJogador1, pecasComidasJogador2, nomeJogador1, nomeJogador2);
        printf("%s, insira seu movimento (x1 y1 x2 y2): ", jogadorAtual == JOGADOR1 ? nomeJogador1 : nomeJogador2);
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        if (x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8 || x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8) {
            printf("Movimento fora do tabuleiro. Tente novamente.\n");
            continue;
        }

        if (tabuleiro[x1][y1] != jogadorAtual) {
            printf("Você não pode mover essa peça.\n");
            continue;
        }

        if (movimentoValido(tabuleiro, x1, y1, x2, y2, jogadorAtual)) {
            moverPeca(tabuleiro, x1, y1, x2, y2, &pecasComidasJogador1, &pecasComidasJogador2);

            if (!temMovimentoValido(tabuleiro, jogadorAtual == JOGADOR1 ? JOGADOR2 : JOGADOR1)) {
                printf("%s venceu!\n", jogadorAtual == JOGADOR1 ? nomeJogador1 : nomeJogador2);
                break;
            }

            jogadorAtual = (jogadorAtual == JOGADOR1) ? JOGADOR2 : JOGADOR1;
        } else {
            printf("Movimento inválido. Tente novamente.\n");
        }
    }

    return 0;
}