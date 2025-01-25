#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

#define SUCESSO 0
#define JA_TEM_ESTRUTURA_AUXILIAR -1
#define POSICAO_INVALIDA -2
#define SEM_ESPACO_DE_MEMORIA -3
#define TAMANHO_INVALIDO -4
#define SEM_ESTRUTURA_AUXILIAR -5
#define SEM_ESPACO -6
#define NUMERO_INEXISTENTE -7
#define ESTRUTURA_AUXILIAR_VAZIA -8

int *vetoresAuxiliares[TAM] = {NULL};
int tamanhos[TAM] = {0};
int ocupados[TAM] = {0};

int ehPosicaoValida(int posicao) {
    return (posicao >= 1 && posicao <= TAM) ? SUCESSO : POSICAO_INVALIDA;
}

int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }

    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }

    int index = posicao - 1;

    if (vetoresAuxiliares[index] != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    vetoresAuxiliares[index] = (int *)malloc(tamanho * sizeof(int));

    if (vetoresAuxiliares[index] == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    tamanhos[index] = tamanho;
    ocupados[index] = 0;

    return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }

    int index = posicao - 1;

    if (vetoresAuxiliares[index] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (ocupados[index] >= tamanhos[index]) {
        return SEM_ESPACO;
    }

    vetoresAuxiliares[index][ocupados[index]] = valor;
    ocupados[index]++;

    return SUCESSO;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }

    int index = posicao - 1;

    if (vetoresAuxiliares[index] == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (ocupados[index] == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    for (int i = 0; i < ocupados[index]; i++) {
        vetorAux[i] = vetoresAuxiliares[index][i];
    }

    return SUCESSO;
}

void listarTodasEstruturas() {
    for (int i = 0; i < TAM; i++) {
        printf("Posição %d: ", i + 1);

        if (vetoresAuxiliares[i] == NULL) {
            printf("(sem estrutura auxiliar)\n");
        } else {
            printf("[");
            for (int j = 0; j < ocupados[i]; j++) {
                printf("%d", vetoresAuxiliares[i][j]);
                if (j < ocupados[i] - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        }
    }
}

void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (vetoresAuxiliares[i] != NULL) {
            free(vetoresAuxiliares[i]);
            vetoresAuxiliares[i] = NULL;
        }
    }
}

void abrirArquivo() {
    FILE *file = fopen("main.c", "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo main.c\n");
        return;
    }

    printf("Arquivo main.c aberto com sucesso.\n\nConteúdo:\n");

    char c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
}

int main() {
    abrirArquivo();
    return 0;
}
