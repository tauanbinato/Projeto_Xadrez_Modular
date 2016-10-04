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
//Include de outros modulos
#include   "lista.h"
#include   "Peca.h"

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
	PEC_tppPeca  * pPeca;

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

	/* Declaracoes necessarias */
	int numDoCaminho, numColunas;
	char *vetor_IDS[tamanho_matriz] = { "um" , "dois" , "tres" , "quatro" , "cinco" , "seis" , "sete" , "oito" };

	LIS_tppLista  *caminho_matriz;
	LIS_tppLista  *colunas_matriz;
	TAB_ppAncoraCasa *cabeca_casa;

	TAB_ancoraCasa *aux_cabecaCasa;
	TAB_ancoraTabuleiro *aux_ancoraTAB;
	/* --------------------------------- */

	

	/* Fazendo as alocacaos necessarias */
	
	cabeca_casa = (TAB_ppAncoraCasa *)malloc(sizeof(TAB_ancoraCasa));
	if (cabeca_casa == NULL) {
		return TAB_CondRetFaltouMemoria;
	}

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
	
	
	
	for (numDoCaminho = 0; numDoCaminho < tamanho_matriz; numDoCaminho++)
	{
		//Cria 8 caminhos (linhas)
		
		LIS_CriarLista(&colunas_matriz, vetor_IDS[numDoCaminho]);
		LIS_InserirNo(&caminho_matriz, colunas_matriz);
		(*cabeca_TAB)->num_de_linhas++;
		
		for (numColunas = 0; numColunas < tamanho_matriz; numColunas++)
		{
			
			//Cria 8 elementos para cada linha e aponta para uma casa
			aux_cabecaCasa = (TAB_ancoraCasa *)malloc(sizeof(TAB_ancoraCasa));
			if (aux_cabecaCasa == NULL) {
			
				return TAB_CondRetFaltouMemoria;
			}
		
			*cabeca_casa = aux_cabecaCasa;
			
			LIS_InserirNo(&colunas_matriz, cabeca_casa);
			free(aux_cabecaCasa);
		                 
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
**
*  Funcao: TAB &inserir Peça
*Função InserirPeca – Receberá a coordenada linha-coluna, o identificador da peça a ser inserida e a sua cor. 
*Crie os retornos necessários inclusive prevendo a colocação da peça em uma coordenada inexistente
*  *************************************************************************/
TAB_tpCondRet inserirPeca(TAB_ppAncoraTabuleiro *cabeca_TAB, int **cord_linha , int **cord_coluna , char **id_peca , char **id_cor)
{

	int corrente;
	char **nomePeca , **corPeca;
	TAB_ppAncoraCasa *aux_Casa;
	PEC_tppPeca *aux_Peca;

	printf("Valores: cord_linha: %d  cord_coluna: %d  , id peca: %c   id_cor: %c\n" ,cord_linha , cord_coluna , *id_peca , *id_cor);

	//Testa se esta OUT of RANGE
	if ((cord_linha > tamanho_matriz || cord_coluna > tamanho_matriz ) || (cord_linha == 0 || cord_coluna == 0)) {
		return TAB_CondRetNaoAchou;
	}


	/*Anda atraves da cabeça ate encontrar a linha desejada*/
	for (corrente = 1; corrente == cord_linha; corrente++) {
		if (corrente == cord_linha) {
			break;
		}
		LIS_AvancarElementoCorrente((*cabeca_TAB)->pCabecaLista);
	}
	printf("Corrente : %d || Linha : %d\n", corrente, cord_linha);

	/*Anda atraves dos elementos de uma linha ate encontrar a coluna desejada*/
	for (corrente = 1; corrente == cord_coluna; corrente++) {
	
		LIS_ObterNo((*cabeca_TAB)->pCabecaLista, &aux_Casa);

	}
	printf("Corrente : %d || Coluna : %d\n", corrente, cord_coluna);


	aux_Peca = (*aux_Casa)->pCasaMatriz->pPeca;

	//Utiliza funcoes de acesso do modulo peca
	printf("id_peca: %c   id_cor: %c \n", *id_peca, *id_cor);
	/*Crio a peca que sera inserida no tabuleiro*/
	PEC_criaPeca(&aux_Peca, id_peca, id_cor);
	PEC_insereNomeDePeca(&aux_Peca, id_peca);
	PEC_insereCorDePeca(&aux_Peca, id_cor);
	
	PEC_obtemNomeDePeca(&aux_Peca, &nomePeca);
	PEC_obtemCorDePeca(&aux_Peca, &corPeca);

	printf("Peca adicionda : %c\n",nomePeca);
	printf("Cor da peca adicionda : %c\n", corPeca);
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
