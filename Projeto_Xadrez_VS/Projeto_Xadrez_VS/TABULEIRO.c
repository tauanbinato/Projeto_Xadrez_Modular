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

#define LISTA_OWN
#include "TABULEIRO.h"
#undef LISTA_OWN

typedef struct TAB_tagTabuleiro {

	LIS_tppLista * pLinha;
	/* Ponteiro para a cabeça da linha */

	LIS_tppLista * pColuna;
	/* Ponteiro para a cabeça da coluna */

	char idMatriz[5];
	/*Identificação da matriz*/


} TAB_ancoraTabuleiro;

/********************************************************/

TAB_tpCondRet cria_tabuleiro(LIS_tppLista linha, LIS_tppLista coluna , TAB_ancoraTabuleiro **ancora_matriz , char * idMatriz) {

	//Cria as listas
	LIS_CriarLista(linha, "Lin");
	LIS_CriarLista(coluna, "Colu");
	
	//Preenche as linhas e colunas com vazios 'V'
	int numLinhasxColunas;
	for ( numLinhasxColunas = 0; numLinhasxColunas < 8; numLinhasxColunas++)
	{
		LIS_InserirNo(linha, 'V');
		LIS_InserirNo(coluna, 'V');
	}

	//Criando uma cabeça para essa matriz
	strcpy((*ancora_matriz)->idMatriz, idMatriz);
	(*ancora_matriz)->pLinha = linha;
	(*ancora_matriz)->pColuna = coluna;

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
