#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const char CARACTERES[] = {'~', 'O', 'X'};
const int TAMANHO_NOME_PLAYER = 20;
int linhas;
int colunas;
int posicoesOcupadas = 0;
int *tabuleiro;
char players[2][21];
int playerAtual = 1;

const char* getDescricaoPlayerAtual() {
    int tamNome = strlen(players[playerAtual - 1]);
    char *desc = malloc((tamNome + 5) * sizeof(char));
    strcat(desc, players[playerAtual - 1]);
    strcat(desc, " [");
    desc[tamNome + 2] = CARACTERES[playerAtual];
    strcat(desc, "]");
    desc[tamNome + 4] = '\0';
    return desc;
}

int inicializaTabuleiro() {
    tabuleiro = malloc(linhas * colunas * sizeof(int));
    for(int i = 0; i < linhas * colunas; i++) {
        tabuleiro[i] = 0;
    }
    return 1;
}

int configuraTabuleiro() {
    int n;
    printf("Será criado um tabuleiro de tamanho 2*N por 2*N. \n");
    printf("Por favor, digite o valor de N desejado (de 1 a 10): ");
    scanf("%d", &n);

    if (n > 0 && n <= 10) {
        linhas =  2 * n;
        colunas = 2 * n;
        if (inicializaTabuleiro()) {
            printf("Tabuleiro %d*%d criado\n", linhas, colunas);
            return 1;
        } else {
            printf("Erro ao inicializar o tabuleiro.\n");
        }
    } else {
        printf("O valor de N deve estar entre 1 e 10!\n");
    }
    return 0;
}

int calculaPosicao(int x, int y) {
    return colunas * y + x;
}

int obtemValor(int x, int y) {
    return tabuleiro[calculaPosicao(x, y)];
}

void setValor(int x, int y, int valor) {
    int pos = calculaPosicao(x, y);
    if (!tabuleiro[pos] && valor) {
        posicoesOcupadas++;
    } else if (tabuleiro[pos] && !valor) {
        posicoesOcupadas--;
    }
    tabuleiro[pos] = valor;
}

void setaProximoPlayer() {
    playerAtual = (playerAtual % 2) + 1;
}

int pedeJogada(int *x, int *y) {
    char *nome = getDescricaoPlayerAtual();
    printf("\nJogada de %s: ", nome);
    scanf("%d %d", x, y);
}

void imprimeLinhaDivisora(int identar) {
    if (identar) {
        printf("   ");
    }
    for (int i = 0; i < colunas; i++) {
        printf("+---");
    }
    printf("+\n");
}

void imprimeTabuleiro() {
    printf("\n");
    printf("     ");
    for (int c = 0; c < colunas; c++) {
        if (c < 10) {
            printf("%d   ", c);
        } else {
            printf("%d  ", c);
        }
    }
    printf("X");
    printf("\n   ");
    for (int l = 0; l < linhas; l++) {
        imprimeLinhaDivisora(l);
        if (l < 10) {
            printf("%d  ", l);
        } else {
            printf("%d ", l);
        }
        for (int c = 0; c < colunas; c++) {
            char v = CARACTERES[obtemValor(c, l)];
            printf("| %c ",v);
        }
        printf("| \n");
    }
    imprimeLinhaDivisora(1);
    printf("Y\n");
}

int pedePlayer(int player) {
    printf("Informe o nome do Player %d [%c] (até %d caracteres): ", player, CARACTERES[player], TAMANHO_NOME_PLAYER);
    char nome[TAMANHO_NOME_PLAYER];
    scanf("%s", nome);
    strcpy(players[player - 1], nome);
    return 1;
}

int pedePlayers() {
    if (pedePlayer(1)) {
        return pedePlayer(2);
    }
    return 0;
}

void setaJogadorInicial() {
    srand(time(NULL));
    playerAtual = rand() % 2 + 1;
}

const char* getNomePlayer(int player) {
    return players[player - 1];
}

int validaJogada(int x, int y) {
    if (x + 1 > colunas || y + 1 > linhas) {
        printf("Jogada inválida! Ultrapassou limites do tabuleiro.");
        return 0;
    }
    if (obtemValor(x, y) > 0) {
        printf("Jogada inválida! Posição ocupada.");
        return 0;
    }
    return 1;
}

int realizaJogada() {
    int y, x;
    int invalidas = 0;
    while (1) {
        pedeJogada(&x, &y);
        if (validaJogada(x, y)) {
            setValor(x, y, playerAtual);
            if (venceu(x, y)) {
                printf("%s venceu o jogo!", players[playerAtual]);
                return 0;
            } else if (posicoesOcupadas == colunas * linhas) {
                printf("Empate!");
                return 0;
            } else {
                break;
            }
        } else {
            invalidas++;
            if (invalidas > 10) {
                printf("Excesso de jogadas inválidas.");
                return 0;
            }
        }
    }
    return 1;
}

int verificaVencedorLinha(int y) {
    int pedras = 0;
    for (int x = 0; x < colunas; x++) {
        if (obtemValor(x, y) == playerAtual) {
            pedras++;
        } else {
            pedras = 0;
        }
        if (pedras == colunas / 2) {
            return 1; // TODO: mudar para alterar o estado!
        }
    }
    return 0;
}

int verificaVencedorColuna(int x) {
    int pedras = 0;
    for (int y = 0; y < linhas; y++) {
        if (obtemValor(x, y) == playerAtual) {
            pedras++;
        } else {
            pedras = 0;
        }
        if (pedras == linhas / 2) {
            return 1; // TODO: mudar para alterar o estado!
        }
    }
    return 0;
}

int verificaVencedorDiagonalPrincipal(int xJogada, int yJogada) {
    int pedras = 0;
    int menor = xJogada > yJogada ? yJogada : xJogada;
    for (int x = xJogada - menor, y = yJogada - menor; x < colunas && y < linhas; x++, y++) {
        if (obtemValor(x , y) == playerAtual) {
            pedras++;
        } else {
            pedras = 0;
        }
        if (pedras == linhas / 2) {
            return 1;
        }
    }
    return 0;
}

int verificaVencedorDiagonalSecundaria(int xJogada, int yJogada) {
    int pedras = 0;
    int difX = colunas - xJogada - 1;
    int menor = yJogada < difX ? yJogada : difX;
    for (int x = xJogada + menor, y = yJogada - menor; x >= 0 && y < linhas; x--, y++) {
        if (obtemValor(x , y) == playerAtual) {
            pedras++;
        } else {
            pedras = 0;
        }
        if (pedras == linhas / 2) {
            return 1;
        }
    }
    return 0;
}

int venceu(int x, int y) {
    return verificaVencedorColuna(x) ||
           verificaVencedorLinha(y) ||
           verificaVencedorDiagonalPrincipal(x, y) ||
           verificaVencedorDiagonalSecundaria(x, y);
}

int main (void) {
    if (configuraTabuleiro()) {
        if (pedePlayers()) {
            setaJogadorInicial();
            while (1) {
                imprimeTabuleiro();
                if (realizaJogada()) {
                    system("clear");
                    setaProximoPlayer();
                } else {
                    imprimeTabuleiro();
                    break;
                }
            }
        } else {
            printf("\nFalha ao configurar players");
        }
    }
    printf("\nFim de jogo!\n");
}
