#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO_MAX 10

#include "EstruturaVetores.h"

typedef struct EstruturaAux {
    int *elementos;
    int qtdElementos;
    int capacidade;
} EstruturaAux;

EstruturaAux *vetorPrincipal;

// Inicializa as estruturas auxiliares
void inicializar() {
        const char *fileName = "db.txt";
    FILE *fp;

    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("Arquivo '%s' não existe. Criando '%s'.\n", fileName, fileName);
        fp = fopen(fileName, "w");
        if (fp == NULL) {
            printf("Erro ao criar o arquivo '%s'.\n", fileName);
            return;
        }
        printf("Arquivo criado com sucesso!\n");
    }else{
        printf("Arquivo '%s' encontrado!\n", fileName);
    }
    fclose(fp);
    
    vetorPrincipal = malloc(sizeof(EstruturaAux) * TAMANHO_MAX);
    for (int i = 0; i < TAMANHO_MAX; i++) {
        vetorPrincipal[i].elementos = NULL;
        vetorPrincipal[i].qtdElementos = 0;
        vetorPrincipal[i].capacidade = 0;
    }
}

int verificarPosicao(int posicao) {
    return (posicao < 1 || posicao > 10) ? POSICAO_INVALIDA : SUCESSO;
}

int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (verificarPosicao(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].elementos != NULL) return JA_TEM_ESTRUTURA_AUXILIAR;
    if (tamanho <= 0) return TAMANHO_INVALIDO;

    vetorPrincipal[posicao - 1].elementos = malloc(sizeof(int) * tamanho);
    if (vetorPrincipal[posicao - 1].elementos == NULL) return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[posicao - 1].qtdElementos = 0;
    vetorPrincipal[posicao - 1].capacidade = tamanho;

    return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (verificarPosicao(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].elementos == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao - 1].qtdElementos == vetorPrincipal[posicao - 1].capacidade) return SEM_ESPACO;

    vetorPrincipal[posicao - 1].elementos[vetorPrincipal[posicao - 1].qtdElementos] = valor;
    vetorPrincipal[posicao - 1].qtdElementos++;
    return SUCESSO;
}

int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (verificarPosicao(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].elementos == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao - 1].qtdElementos == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[posicao - 1].qtdElementos--;
    return SUCESSO;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (verificarPosicao(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].elementos == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao - 1].qtdElementos == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    for (int i = 0; i < vetorPrincipal[posicao - 1].qtdElementos; i++) {
        if (vetorPrincipal[posicao - 1].elementos[i] == valor) {
            for (int j = i; j < vetorPrincipal[posicao - 1].qtdElementos - 1; j++) {
                vetorPrincipal[posicao - 1].elementos[j] = vetorPrincipal[posicao - 1].elementos[j + 1];
            }
            vetorPrincipal[posicao - 1].qtdElementos--;
            return SUCESSO;
        }
    }
    return NUMERO_INEXISTENTE;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (verificarPosicao(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].elementos == NULL) return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < vetorPrincipal[posicao - 1].qtdElementos; i++) {
        vetorAux[i] = vetorPrincipal[posicao - 1].elementos[i];
    }
    return SUCESSO;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (getDadosEstruturaAuxiliar(posicao, vetorAux) != SUCESSO) return POSICAO_INVALIDA;

    int qtd = vetorPrincipal[posicao - 1].qtdElementos;
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (vetorAux[i] > vetorAux[j]) {
                int temp = vetorAux[i];
                vetorAux[i] = vetorAux[j];
                vetorAux[j] = temp;
            }
        }
    }
    return SUCESSO;
}

int getDadosDeTodasEstruturasAuxiliares(int vet[]) {
    int total = 0;
    for (int i = 0; i < TAMANHO_MAX; i++) {
        if (vetorPrincipal[i].elementos != NULL) {
            for (int j = 0; j < vetorPrincipal[i].qtdElementos; j++) {
                vet[total++] = vetorPrincipal[i].elementos[j];
            }
        }
    }
    
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (vet[i] > vet[j]) {
                int temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
            }
        }
    }
    
    return total > 0 ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
}

void bubbleSort(int * vetor, int size) 
{
    int i = 1;
    int aux;
    int troca = 1;
    while (troca) 
    {
        troca = 0;
        i = 1;
        while (i < size) 
        {
            if (vetor[i] < vetor[i - 1]) 
            {
                aux = vetor[i];
                vetor[i] = vetor[i - 1];
                vetor[i - 1] = aux;
                troca = 1;
            }
            i++;
        }
    }
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{   
    
    getDadosDeTodasEstruturasAuxiliares(vetorAux);
    
    int size = 0;

    int areAllEmpty = 1;

    for (int i = 0; i < 10; i++) 
    {
        if (vetorPrincipal[i].elementos != NULL)
        {
            if (vetorPrincipal[i].capacidade != 0) 
            {
                areAllEmpty = 0;
                for (int j = 0; j < vetorPrincipal[i].capacidade; size++, j++); 
            }
        }
    }
    
    if (size == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    //

    bubbleSort(vetorAux, size);

    return SUCESSO;
}



int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (verificarPosicao(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].elementos == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao - 1].capacidade + novoTamanho < 1) return NOVO_TAMANHO_INVALIDO;

    int *novoArray = realloc(vetorPrincipal[posicao - 1].elementos, sizeof(int) * (vetorPrincipal[posicao - 1].capacidade + novoTamanho));
    if (novoArray == NULL) return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[posicao - 1].elementos = novoArray;
    vetorPrincipal[posicao - 1].capacidade += novoTamanho;
    if (vetorPrincipal[posicao - 1].qtdElementos > vetorPrincipal[posicao - 1].capacidade)
        vetorPrincipal[posicao - 1].qtdElementos = vetorPrincipal[posicao - 1].capacidade;

    return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (verificarPosicao(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].elementos == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao - 1].qtdElementos == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    return vetorPrincipal[posicao - 1].qtdElementos;
}

No* montarListaEncadeadaComCabecote() {
    No *cabecote = malloc(sizeof(No));
    cabecote->prox = NULL;
    No *ultimo = cabecote;
    
    for (int i = 0; i < TAMANHO_MAX; i++) {
        if (vetorPrincipal[i].elementos != NULL) {
            for (int j = 0; j < vetorPrincipal[i].qtdElementos; j++) {
                No *novo = malloc(sizeof(No));
                novo->conteudo = vetorPrincipal[i].elementos[j];
                novo->prox = NULL;
                ultimo->prox = novo;
                ultimo = novo;
            }
        }
    }
    return cabecote;
}

void getDadosListaEncadeadaComCabecote(No *list, int vet[]) {
    No *current = list->prox;
    int i = 0;
    while (current != NULL) {
        vet[i++] = current->conteudo;
        current = current->prox;
    }
}

void destruirListaEncadeadaComCabecote(No **inicio) {
    No *current = *inicio;
    while (current != NULL) {
        No *aux = current;
        current = current->prox;
        free(aux);
    }
    *inicio = NULL;
}


void finalizar() {
    printf("Salvando arquivo...\n");
    const char *fileName = "db.txt";
    int save = saveFile(fileName);

    if(save == 1){
        printf("Arquivo salvo com sucesso!\n");
    }
    else{
        printf("Erro ao salvar arquivo!\n");
    }
    
    for (int i = 0; i < TAMANHO_MAX; i++) {
        if (vetorPrincipal[i].elementos != NULL) {
            free(vetorPrincipal[i].elementos);
            vetorPrincipal[i].elementos = NULL;
        }
    }
    free(vetorPrincipal);
    vetorPrincipal = NULL;
}
