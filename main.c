#include <stdio.h>
#include <stdlib.h>

static const char BRANCO = 'O';
static const char PRETO = 'X';
static const char VAZIO = '~';
int linhas;
int colunas;
char *tabuleiro;



int inicializaTabuleiro() {
    tabuleiro = malloc(linhas * colunas * sizeof(char));

    for(int i = 0; i < linhas * colunas; ++i) {
        tabuleiro[i] = VAZIO;
    }
    return 0;
}

void configuraTabuleiro() {
    int n;
    printf("Será criado um tabuleiro de tamanho 2*N por 2*N. \n");
    printf("Por favor, digite o valor de  N desejado: ");
    scanf("%d", &n);
    linhas =  2 * n;
    colunas = 2 * n;

    if (!inicializaTabuleiro()) {
        printf("Tabuleiro %d*%d criado", linhas, colunas);
    } else {
        printf("Erro ao inicializar o tabuleiro.");
    }

}

int obtemValor(int x, int y) {
    return tabuleiro[colunas * x + y];
}

int setValor(int x, int y, char valor) {
    tabuleiro[colunas * x + y] = valor;
}

void realizarJogada(int x, int y) {
    //TODO
    /*int jogadaValida = 0;
    while(!jogadaValida) {
        printf("Por favor, digite uma coordenada para realizar a jogada: ");
        scanf("%d", &n);

        if (obtemValor(x,y) == VAZIO) {

        }
    }
*/
}

void imprimeTabuleiro() {
    printf("\n");
    for (int l = 0; l < linhas; ++l) {
        for (int i = 0; i < linhas; ++i){
            printf("+---");
        }
        printf("+");
        printf("\n");
        for (int c = 0; c < colunas; ++c) {
            char v = obtemValor(l,c);
            printf("| %c ",v);
        }
        printf("| \n");
    }
    for (int i = 0; i < linhas; ++i){
        printf("+---");
    }
    printf("+");
    printf("\n");
}

void inciaJogo() {
    //TODO
    int gameover = 0;
    while(!gameover) {
        // imprimeTabuleiro();
        // realizaJogada
        // trocaJogadorAtual
    }
}

int main (void) {
    printf("Hello World \n");
    configuraTabuleiro();
    //iniciaThreads
    //iniciaJogo
    imprimeTabuleiro();
}
