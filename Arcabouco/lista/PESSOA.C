/***************************************************************************
*
*  $MCD Módulo de definição: PES  Estrutura de uma Pessoa
*
*  Arquivo gerado:              PESSOA.C
*  Letras identificadoras:      PES
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PESSOA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Tauan Binato , Julia Aleixo , Lucas Palma
*
*  $ED Descrição do módulo
*     Implementa uma estrutura de pessoa com nome e iniciais
*
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>

#include   <malloc.h>
#include   <assert.h>


#define PESSOA_OWN
#include "PESSOA.h"
#undef PESSOA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Informacoes do nome
*
*
***********************************************************************/
typedef struct infonome
{
	char *iniciais; //iniciais (string)
	
	char *nome; //nome (string)

} Infonome;

/***************************************************************************
*
*  Função: PES  &Criar Estrutura
*  ****/
PES_tpCondRet PES_Criar_Estrutura(Infonome **pessoa){

	*pessoa = (Infonome *)malloc(sizeof( Infonome));
	if(pessoa == NULL){
		return PES_CondRetFaltouMemoria;
	}

	(*pessoa)->iniciais = NULL;
	(*pessoa)->nome = NULL;

	return PES_CondRetOK;
}
/* Fim função: PES  &Criar estrutura */
/***********************************************************************
*
*  Função: PES  &Preencher estrutura
*  ****/
   
    PES_tpCondRet PES_preencher_estrutura(Infonome **pessoa,char *nome, char *iniciais)
{

	int i = strlen(nome);

	(*pessoa)->nome = (char*)malloc(i * sizeof(char));
	if((*pessoa)->nome == NULL){
		 return PES_CondRetFaltouMemoria ;
	}
	strcpy((*pessoa)->nome, nome);

	i = strlen(iniciais);

	(*pessoa)->iniciais = (char*)malloc(i * sizeof(char));
	if((*pessoa)->iniciais == NULL){
		return PES_CondRetFaltouMemoria ;
	}

	strcpy((*pessoa)->iniciais, iniciais);

	return PES_CondRetOK;
}
	/* Fim função: PES  &Preencher Estrutura */
/***********************************************************************

/***************************************************************************
*
*  Função: PES  &Obter referência para as iniciais do valor da estrutura
*  ****/

   PES_tpCondRet PES_ObterValorIniciais( char **strIni , Infonome *pValor )
   {
	  
	  char *aux[100];
	  int tamanhoIni = strlen(pValor->iniciais);
      printf("Entrou aqui.3 || tamanhoIni = %d || pValor Iniciais = %s \n",tamanhoIni,pValor->iniciais);
	  

      if ( pValor == NULL )
      {
		printf("Entrou pValor NULL");
		strIni = NULL;
        return PES_CondRetEstruturaVazia ;
      } /* fim if */

	  strIni = (char**)malloc(tamanhoIni * sizeof(char));
	  if(*strIni == NULL){
	  printf("strIni faltou memoria = %s\n",*strIni);
	  return PES_CondRetFaltouMemoria;
	  }
	  
	  printf("strIni = %s , Iniciais = %s\n",*strIni , pValor->iniciais);
	  strcpy((*strIni),(pValor)->iniciais);
	  printf("strIni = %s\n",*strIni);
	  

      return PES_CondRetOK;

   } /* Fim função: PES  &Obter referência para as iniciais do valor da estrutura */

   /***************************************************************************
*
*  Função: PES  &Obter referência para as iniciais do valor da estrutura
*  ****/

   PES_tpCondRet PES_ObterValorNome( char **strNome , Infonome *pValor )
   {

	  char *aux[100];
	  int tamanhoNome = strlen(pValor->nome);
      printf("Entrou aqui || tamanhoIni = %d || pValor Nome = %s \n",tamanhoNome,pValor->nome);
	  

      if ( pValor == NULL )
      {
		printf("Entrou pValor NULL");
		strNome = NULL;
        return PES_CondRetEstruturaVazia ;
      } /* fim if */


	  printf("aqui.\n");
	  strNome = (char**)malloc(tamanhoNome * sizeof(char));
	  if(*strNome == NULL){
	  printf("strIni faltou memoria = %s\n",*strNome);
	  return PES_CondRetFaltouMemoria;
	  }
	  
	  printf("strIni = %s , Iniciais = %s\n",*strNome , pValor->nome);
	  strcpy((*strNome),(pValor)->nome);
	  printf("strIni = %s",*strNome);
	  

      return PES_CondRetOK;

   } /* Fim função: PES  &Obter referência para as iniciais do valor da estrutura */