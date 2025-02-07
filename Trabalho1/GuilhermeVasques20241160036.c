#include <stdio.h>
#include "GuilhermeVasques20241160036.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Declarações de funções auxiliares
DataQuebrada extrairData(char data[]);
int ehBissexto(int ano);
int diasNoMes(int mes, int ano);
void removerAcentos(char *texto);

// Função de soma para testes
int somar(int a, int b) {
    return a + b;
}

// Função de fatorial para testes
int calcularFatorial(int num) {
    int fatorial = 1;
    for (int i = num; i > 1; i--)
        fatorial *= i;
    return fatorial;
}

// Validação de data (Q1)
int validarData(char data[]) {
    int valida = 1;
    DataQuebrada dataExtraida = extrairData(data);
    
    if (dataExtraida.valido) {
        int dia = dataExtraida.iDia, mes = dataExtraida.iMes, ano = dataExtraida.iAno;

        if (dia < 1 || dia > 31 || mes < 1 || mes > 12) valida = 0;
        if (dia == 31 && diasNoMes(mes, ano) != 31) valida = 0;
        if (mes == 2 && dia > 29) valida = 0;
        if (mes == 2 && dia == 29 && diasNoMes(mes, ano) != 29) valida = 0;
    } else {
        valida = 0;
    }
    return valida;
}

// Diferença entre duas datas (Q2)
DiasMesesAnos calcularDiferencaDatas(char dataInicio[], char dataFim[]) {
    DiasMesesAnos resultado;
    if (!validarData(dataInicio)) {
        resultado.retorno = 2;
        return resultado;
    }
    if (!validarData(dataFim)) {
        resultado.retorno = 3;
        return resultado;
    }
    
    DataQuebrada inicio = extrairData(dataInicio);
    DataQuebrada fim = extrairData(dataFim);
    
    if (fim.iAno < inicio.iAno || (fim.iAno == inicio.iAno && fim.iMes < inicio.iMes) ||
        (fim.iAno == inicio.iAno && fim.iMes == inicio.iMes && fim.iDia < inicio.iDia)) {
        resultado.retorno = 4;
        return resultado;
    }
    
    resultado.qtdAnos = fim.iAno - inicio.iAno;
    resultado.qtdMeses = fim.iMes - inicio.iMes;
    resultado.qtdDias = fim.iDia - inicio.iDia;
    
    if (resultado.qtdMeses < 0) {
        resultado.qtdMeses += 12;
        resultado.qtdAnos--;
    }
    if (resultado.qtdDias < 0) {
        resultado.qtdDias += diasNoMes(inicio.iMes, inicio.iAno);
        resultado.qtdMeses--;
    }
    resultado.retorno = 1;
    return resultado;
}

// Contagem de ocorrência de caractere (Q3)
int contarCaracter(char *texto, char caractere, int sensivel) {
    int contador = 0;
    char *textoProcessado = malloc(strlen(texto) + 1);
    strcpy(textoProcessado, texto);
    removerAcentos(textoProcessado);
    
    if (!sensivel) {
        for (int i = 0; textoProcessado[i] != '\0'; i++) {
            if (textoProcessado[i] >= 'A' && textoProcessado[i] <= 'Z')
                textoProcessado[i] += 32;
        }
        if (caractere >= 'A' && caractere <= 'Z') caractere += 32;
    }
    
    for (int i = 0; textoProcessado[i] != '\0'; i++) {
        if (textoProcessado[i] == caractere) contador++;
    }
    
    free(textoProcessado);
    return contador;
}

// Inverter número (Q5)
int inverterNumero(int numero) {
    int invertido = 0;
    while (numero != 0) {
        invertido = invertido * 10 + (numero % 10);
        numero /= 10;
    }
    return invertido;
}

// Verificar número dentro de outro número (Q6)
int contarOcorrenciasNumero(int base, int busca) {
    int contador = 0, divisor = 1;
    while (busca / divisor != 0) divisor *= 10;
    while (base != 0) {
        if (base % divisor == busca) {
            contador++;
            base /= divisor;
        } else {
            base /= 10;
        }
    }
    return contador;
}

// Funções auxiliares
DataQuebrada extrairData(char data[]) {
    DataQuebrada resultado;
    resultado.valido = 0;
    sscanf(data, "%d/%d/%d", &resultado.iDia, &resultado.iMes, &resultado.iAno);
    resultado.valido = 1;
    return resultado;
}

int ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int diasNoMes(int mes, int ano) {
    if (mes == 2) return ehBissexto(ano) ? 29 : 28;
    return (mes == 4 || mes == 6 || mes == 9 || mes == 11) ? 30 : 31;
}

void removerAcentos(char *texto) {
    char *comAcentos = "ÁÉÍÓÚÂÊÎÔÛÀÈÌÒÙÃÕÇ";
    char *semAcentos = "AEIOUAEIOUAEIOUAAO";
    for (int i = 0; texto[i] != '\0'; i++) {
        for (int j = 0; comAcentos[j] != '\0'; j++) {
            if (texto[i] == comAcentos[j]) {
                texto[i] = semAcentos[j];
                break;
            }
        }
    }
}