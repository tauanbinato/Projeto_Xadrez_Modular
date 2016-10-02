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
#include "Tabuleiro.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeca (ancora) da matriz
*
***********************************************************************/

typedef struct TAB_tagTabuleiro {

	LIS_tppLista  *pCabecaLista;
	/* Ponteiro para a cabeça da lista que representa as linhas */

	int num_de_linhas;
	/*Numero de linhas do tabuleiro(matriz)*/

	int num_de_colunas;
	/*Numero de colunas do tabuleiro(matriz)*/


} TAB_ancoraTabuleiro;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor de uma estrutura casa
*
***********************************************************************/

typedef struct TAB_tagCasa {

	LIS_tppLista * pListaAmeacantes;
	LIS_tppLista * pListaAmeacados;
	//falta um ponteiro aqui

} TAB_casaMatriz;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeca (ancora) de uma casa
*
***********************************************************************/

typedef struct TAB_tagAncoraCasa {

	TAB_casaMatriz * pCasaMatriz;
	/* Ponteiro para uma casa */

} TAB_ancoraCasa;



/***************************************************************************
*
*  Funcao: TAB  &Criar Tabuleiro
*
*  *************************************************************************/

TAB_tpCondRet cria_tabuleiro(LIS_tppLista *caminho_matriz, LIS_tppLista *colunas_matriz, TAB_ppAncoraTabuleiro *cabeca_TAB, TAB_ppAncoraCasa *cabeca_Casa) {


	int numDoCaminho, numColunas;
	
	//Alocando cabeça da ancora.
	*cabeca_TAB = (TAB_ancoraTabuleiro *)malloc(sizeof(TAB_ancoraTabuleiro));
	if (*cabeca_TAB == NULL) {
		return TAB_CondRetFaltouMemoria;
	}
	
	//Cria as listas
	LIS_CriarLista(caminho_matriz, "Cami");
	LIS_CriarLista(colunas_matriz, "Colu");

	// Linka a cabeca do tabuleiro com a linha da matriz.
	(*cabeca_TAB)->pCabecaLista = caminho_matriz;
	

	//Preenche os valores das listas criadas.


	for (numDoCaminho = 0; numDoCaminho < tamanho_matriz; numDoCaminho++)
	{
		//Cria 8 caminhos (linhas)
		LIS_InserirNo(caminho_matriz, colunas_matriz);
		(*cabeca_TAB)->num_de_linhas++;
		
		for (numColunas = 0; numColunas < tamanho_matriz; numColunas++)
		{
			
			//Cria 8 colunas para cada linha
			*cabeca_Casa = (TAB_ancoraCasa *)malloc(sizeof(TAB_ancoraCasa));
			if (*cabeca_Casa == NULL) {
				return TAB_CondRetFaltouMemoria;
			}
			LIS_InserirNo(colunas_matriz, cabeca_Casa);								// <- Digo que cada elemento da matriz aponta pra uma cabeça de casa
			(*cabeca_TAB)->num_de_colunas++;
		
		}
	} /* endFor */

	

	return TAB_CondRetOK;

}
/* Fim funcao: TAB  &Criar tabuleiro */



// AREA DO TAUAN------------------
/***************************************************************************
*
*  Funcao: TAB &inserir Peça
*  ****/
TAB_tpCondRet inserirPeca()
{
	return TAB_CondRetOK;
}/*Fim funcao: TAB &Inserir Peça*/

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
TAB_tpCondRet obterListaAmeacantes( int linha, int coluna, LIS_tppLista * pListaAmeacantes )
{

	return TAB_CondRetOK;
}

TAB_tpCondRet obterListaAmeacados( int linha, int coluna, LIS_tppLista * pListaAmeacantes )
{
	return TAB_CondRetOK;
}

TAB_tpCondRet destruirTabuleiro()
{
	return TAB_CondRetOK;
}
// FIM AREA DA JULIA-----------------
