/***************************************************************************
*  $MCI Módulo de implementação: TAB Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automaçãoo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de módulos C
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

typedef struct TAB_tagTabuleiro {

	LIS_tppLista * pCabecaLista;
	/* Ponteiro para a cabeça da lista que representa as linhas */

	int num_de_linhas;
	/*Numero de linhas do tabuleiro(matriz)*/

	int num_de_colunas;
	/*Numero de colunas do tabuleiro(matriz)*/


} TAB_ancoraTabuleiro;


/********************************************************/

TAB_tpCondRet cria_tabuleiro(LIS_tppLista caminho_matriz, LIS_tppLista colunas_matriz,  TAB_ancoraTabuleiro **ancora_matriz ) {

	//Cria as listas
	LIS_CriarLista(caminho_matriz, "Lin");
	LIS_CriarLista(colunas_matriz, "Colu");
	
	//Preenche as linhas e colunas com vazios 'V'
	
	int numDoCaminho , numColunas;
	for (numDoCaminho = 0; numDoCaminho < tamanho_matriz; numDoCaminho++)
	{
		//Cria 8 linhas
		LIS_InserirNo(caminho_matriz, colunas_matriz);

		for (numColunas = 0; numColunas < tamanho_matriz; numColunas++)
		{
			//Cria 8 colunas para cada linha
			LIS_InserirNo(colunas_matriz, NULL);                                    // Temos que apontar cada elemento para uma casa (ainda n temos casa)
		}

	} /* endFor */


	//Linka a ancora com linha da matriz.
	ancora_matriz = caminho_matriz;

	return TAB_CondRetOK;
}



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
