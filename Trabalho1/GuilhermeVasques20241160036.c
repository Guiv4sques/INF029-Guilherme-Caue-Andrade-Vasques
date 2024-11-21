// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Guilherme Cauê Andrade Vasques
//  email: guivasques90@gmail.com
//  Matrícula: 20241160036
//  Semestre: 2024.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "GuilhermeVasques20241160036.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
  int datavalida = 1;

  //quebrar a string data em strings sDia, sMes, sAno
  int TAM = strlen(data);

  for(int i = 0; i < TAM; i++)
    if(data[i] != '/' && !(data[i] >= '0' && data[i] <= '9')) datavalida = 0;

  DataQuebrada DataQ = quebraData(data);

  if(DataQ.valido)
  {
  int dia = DataQ.iDia, mes = DataQ.iMes, ano = DataQ.iAno;

  if(dia<1 || dia>31 || mes<1 || mes>12) datavalida = 0;
  
  if(dia > DiasNoMes(mes, ano)) datavalida = 0;


  //printf("%s\n", data);

  if (datavalida)
      return 1;
  else
      return 0;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
      //verifique se a data final não é menor que a data inicial
      DataQuebrada inicio, fim; 
  inicio = quebraData(datainicial);
  fim = quebraData(datafinal);
  
  if(fim.iAno < inicio.iAno || ( fim.iAno == inicio.iAno && fim.iMes < inicio.iMes) || ( fim.iAno == inicio.iAno && fim.iMes == inicio.iMes && fim.iDia < inicio.iDia))
  {
      //calcule a distancia entre as datas
      //Verificar Bissexto de ambas as datas
  int BissextoInicio = 0, BissextoFinal = 0;
  BissextoInicio = VerificadorBissexto(inicio.iAno);
  BissextoFinal = VerificadorBissexto(fim.iAno);
  
  dma.qtdAnos = fim.iAno - inicio.iAno;

  dma.qtdMeses = fim.iMes - inicio.iMes;
  if(dma.qtdMeses != 0)
  {
    if(dma.qtdMeses < 0)
    {
      dma.qtdMeses = dma.qtdMeses + 12;
      dma.qtdAnos--;
    }
  }
  
  dma.qtdDias = fim.iDia - inicio.iDia;
  if(dma.qtdDias != 0)
  {
    if(dma.qtdDias < 0)
    {
      dma.qtdDias = dma.qtdDias + DiasNoMes(inicio.iMes, inicio.iAno);
      if(BissextoInicio == 1 && inicio.iMes == 2)
      {
        dma.qtdDias--; //desconsiderar o bissexto nessa linha apenas
      }
      dma.qtdMeses--;
    }
    if((BissextoInicio == 1 && inicio.iMes <= 2 && inicio.iDia < 29) && ((fim.iAno==inicio.iAno&&fim.iMes>2) ||(fim.iAno>inicio.iAno&&fim.iMes<2)))
      {
      dma.qtdDias++;
      }
    if((BissextoFinal == 1 && fim.iMes > 2))
      {
      dma.qtdDias++;
      }
  }


      //se tudo der certo
      dma.retorno = 1;
      return dma;
      
    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
	  char *TextoT = malloc(strlen(texto));

	  strcpy(TextoT, texto);

    if(!isCaseSensitive)
    {
      if(c >= 'a' && c <= 'z') c-=32;
      for(int i = 0; TextoT[i] != '\0'; i++)
      {
        if(TextoT[i] >= 'a' && TextoT[i] <= 'z')
          TextoT[i]-=32;
      }
    }

    for(int i = 0; TextoT[i] != '\0'; i++)
    {
      if(c == TextoT[i]) qtdOcorrencias+=1;
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = -1;

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int pos = 0, achou;
    int i, j, k;

    for(i = 0; i < strlen(strTexto); i++)
    {
      achou = 0;
      k = i;
      for(j = 0; j < strlen(strBusca); j++)
      {
        if(strTexto[k] == -61)
        {
          k++;
        }
        if(strTexto[k] == strBusca[j])
        {
          achou++;
          k++;
        }
        else{
          break;
        }
      }

      if(achou == strlen(strBusca))
      {
        qtdOcorrencias++;
        posicoes[pos] = i + 1;
        posicoes[pos + 1] = k;
        pos += 2;
        i += strlen(strBusca) - 1;
      }

    return qtdOcorrencias;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    int digitosBusca = 10, verificadorBusca = numerobusca;

    while(verificadorBusca/10 != 0)
    {
      digitosBusca*=10;
      verificadorBusca/=10;
    }

    while(numerobase != 0)
    {
      if(numerobase % digitosBusca == numerobusca)
      {  
        qtdOcorrencias++; 
        numerobase/=digitosBusca;
      }else numerobase/=10;
    }

    return qtdOcorrencias;
}




DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

int DiasNoMes(int mes, int ano)
{
  int Bissexto = 0;
  if((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) Bissexto = 1;

  if(mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;
  else if(mes == 2)
  {
    if(Bissexto) return 29;
    else return 28;
  }
  else return 31;
}

int CopiarTextoInteiro(char *texto, int *textoInteiro)
{
    int texto_int[100];
    int i, j;
    for (i = 0; texto[i] != '\0'; i ++)
    {
        texto_int[i] = texto[i];
        texto_int[i + 1] = texto[i + 1];
    }
    int k = 0;
    for (j = 0; j < i; j++)
    {
        if (texto_int[j] != -61)
        {
            textoInteiro[k] = texto_int[j];
            k++;
        }
    }
    return k;
}

int VerificadorBissexto(int ano)
{
  int bissexto = 0;
  if((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) bissexto = 1;
  return bissexto;
}

