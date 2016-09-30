/***************************************************************************
*  $MCI Módulo de implementação: TAB Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automaçãoo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
*
*  Projeto: INF 1301 / 1628 Automatizacao dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tbf   26/set/2016 início desenvolvimento.
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "lista.h"

#define	   tamanho_matriz	8

#define LISTA_OWN
#include "TABULEIRO.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeca (ancora) da matriz
*
***********************************************************************/

typedef struct TAB_tagTabuleiro {

	LIS_tppLista * pCabecaLista;
	/* Ponteiro para a cabeça da lista que representa as linhas */

	int num_de_linhas;
	/*Numero de linhas do tabuleiro(matriz)*/

	int num_de_colunas;
	/*Numero de colunas do tabuleiro(matriz)*/


} TAB_ancoraTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeca (ancora) de uma casa
*
***********************************************************************/

typedef struct TAB_tagAncoraCasa {

	TAB_casaMatriz * pCasaMatriz;
	/* Ponteiro para uma casa */

} TAB_ancoraCasa;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor de uma estrutura casa
*
***********************************************************************/

typedef struct TAB_tagCasa {



} TAB_casaMatriz;


/***************************************************************************
*
*  Funcao: LIS  &Criar Tabuleiro
*
*  *************************************************************************/

TAB_tpCondRet cria_tabuleiro(LIS_tppLista caminho_matriz, LIS_tppLista colunas_matriz,  TAB_ancoraTabuleiro **ancora_matriz, TAB_ancoraCasa **ancora_casa ) {

	//Cria as listas
	LIS_CriarLista(caminho_matriz, "Cami");
	LIS_CriarLista(colunas_matriz, "Colu");
	
	//Preenche os valores das listas criadas.
	
	int numDoCaminho , numColunas;
	for (numDoCaminho = 0; numDoCaminho < tamanho_matriz; numDoCaminho++)
	{
		//Cria 8 caminhos (linhas)
		LIS_InserirNo(caminho_matriz, colunas_matriz);
		(*ancora_matriz)->num_de_linhas++;

		for (numColunas = 0; numColunas < tamanho_matriz; numColunas++)
		{
			//Cria 8 colunas para cada linha
			LIS_InserirNo(colunas_matriz, ancora_casa);								// <- Digo que cada elemento da matriz aponta pra uma cabeça de casa
			(*ancora_matriz)->num_de_colunas++;
																				
		}
	} /* endFor */

	//Linka a ancora com linha da matriz.
	(*ancora_matriz)->pCabecaLista = caminho_matriz;

	return TAB_CondRetOK;

}
/* Fim funcao: LIS  &Criar tabuleiro */



// AREA DO TAUAN------------------
TAB_tpCondRet inserirPeca()
{
	return TAB_CondRetOK;
}

TAB_tpCondRet moverPeca()
{
	return TAB_CondRetOK;
}

TAB_tpCondRet retirarPeca()
{
	return TAB_CondRetOK;
}

TAB_tpCondRet obterPeca()
{
	return TAB_CondRetOK;
}
// FIM AREA DO TAUAN----------------


// AREA DA JULIA--------------------
TAB_tpCondRet obterListaAmeacantes()
{
	return TAB_CondRetOK;
}

TAB_tpCondRet obterListaAmeacados()
{
	return TAB_CondRetOK;
}

TAB_tpCondRet destruirTabuleiro()
{
	return TAB_CondRetOK;
}
// FIM AREA DA JULIA-----------------
