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
*     1       tb,ja,lp   26/set/2016 início desenvolvimento.
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
*  **************************************************************************/

TAB_tpCondRet cria_tabuleiro(TAB_ppAncoraTabuleiro *cabeca_TAB) {


	int numDoCaminho, numColunas;
	LIS_tppLista  *caminho_matriz;
	LIS_tppLista  *colunas_matriz;
	TAB_ancoraCasa *cabeca_Casa;
	TAB_ancoraTabuleiro *aux_ancoraTAB;
	/* Fazendo as alocacaos necessarias */
	
	// - Alocando cabeça da ancora.
	aux_ancoraTAB = (TAB_ancoraTabuleiro *)malloc(sizeof(TAB_ancoraTabuleiro));
	if (aux_ancoraTAB == NULL) {
	
		return TAB_CondRetFaltouMemoria;
	}

	*cabeca_TAB = aux_ancoraTAB;

	// - Aloca as listas
	LIS_CriarLista(&caminho_matriz, "Cami");
	
	/* --------------------------------- */
	

	//Inicializando estrutura.
	(*cabeca_TAB)->num_de_linhas = 0;
	(*cabeca_TAB)->num_de_colunas = 0;

	//Preenche os valores das listas criadas.


	for (numDoCaminho = 0; numDoCaminho < tamanho_matriz; numDoCaminho++)
	{
		//Cria 8 caminhos (linhas)
		LIS_CriarLista(colunas_matriz, "Colu");
		LIS_InserirNo(caminho_matriz, colunas_matriz);
		(*cabeca_TAB)->num_de_linhas++;
		
		for (numColunas = 0; numColunas < tamanho_matriz; numColunas++)
		{
			
			//Cria 8 colunas para cada linha
			cabeca_Casa = (TAB_ancoraCasa *)malloc(sizeof(TAB_ancoraCasa));
			if (cabeca_Casa == NULL) {
			
				return TAB_CondRetFaltouMemoria;
			}
		
			LIS_InserirNo(colunas_matriz, cabeca_Casa);
			free(cabeca_Casa);
		                 
			(*cabeca_TAB)->num_de_colunas++;
		
		}
	} /* endFor */

	  // Linka a cabeca do tabuleiro com a linha da matriz.
	(*cabeca_TAB)->pCabecaLista = caminho_matriz;
	printf("Numero de linhas na matriz: %d || Numero de elementos na matriz: %d\n", (*cabeca_TAB)->num_de_linhas++, (*cabeca_TAB)->num_de_colunas++);
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

/***************************************************************************
*
*  Funcao: TAB  &Mover Peca
*
*  **************************************************************************/
TAB_tpCondRet moverPeca()
{
	return TAB_CondRetOK;
}/*Fim funcao: TAB &Mover Peca*/

/***************************************************************************
*
*  Funcao: TAB  &Retirar Peca
*
*  **************************************************************************/
TAB_tpCondRet retirarPeca()
{
	return TAB_CondRetOK;
}/*Fim funcao: TAB &Retirar Peca*/

/***************************************************************************
*
*  Funcao: TAB  &Obter Peca
*
*  **************************************************************************/
TAB_tpCondRet obterPeca()
{
	return TAB_CondRetOK;
}/*Fim funcao: &TAB obter Peca*/
// FIM AREA DO TAUAN----------------


// AREA DA JULIA--------------------

/***************************************************************************
*
*  Funcao: TAB  &Obter Lista Ameacantes
*
*  **************************************************************************/
TAB_tpCondRet obterListaAmeacantes( int linha, int coluna, LIS_tppLista * pListaAmeacantes )
{

	return TAB_CondRetOK;
}/*Fim funcao: &TAB obter Lista Ameacantes*/

/***************************************************************************
*
*  Funcao: TAB  &Obter Lista Ameacados
*
*  **************************************************************************/
TAB_tpCondRet obterListaAmeacados( int linha, int coluna, LIS_tppLista * pListaAmeacantes )
{
	return TAB_CondRetOK;
}/*Fim funcao: &TAB obter Lista Ameacados*/

/***************************************************************************
*
*  Funcao: TAB  &Destruir Tabuleiro
*
*  **************************************************************************/
TAB_tpCondRet destruirTabuleiro()
{
	return TAB_CondRetOK;
}/*Fim funcao: &TAB Destruir Tabuleiro*/
// FIM AREA DA JULIA-----------------
