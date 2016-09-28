#pragma once
#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: TAB  Matriz de listas duplamente encadeadas
*
*  Arquivo gerado:              TABULEIRO.h
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Julia Aleixo , Lucas Palma , Tauan Binato
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tbf   26/set/2016 in�cio desenvolvimento.
*
*  $ED Descri��o do m�dulo
*
*
***************************************************************************/

#if defined( TABULEIRO_OWN )
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do Tabuleiro
*
***********************************************************************/

typedef enum {

	TAB_CondRetOK,
	/* Concluiu corretamente  = 0*/

	TAB_CondRetListaVazia,
	/* A lista n�o cont�m elementos = 1 */

	TAB_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	TAB_CondRetNaoAchou,
	/* N�o encontrou o valor procurado = 3*/

	TAB_CondRetFaltouMemoria
	/* Faltou mem�ria ao tentar criar um elemento de lista = 4 */

} TAB_tpCondRet;

/* 
------FUN��ES N�O PRONTAS DO TAUAN--------

-Fun��o InserirPeca � Receber� a coordenada linha-coluna, o identificador da pe�a a ser inserida e a sua cor.
 Crie os retornos necess�rios inclusive prevendo a coloca��o da pe�a em uma coordenada inexistente.
-Fun��o MoverPeca �a coordenada de origem e a coordenada de destino. Esta fun��o dever� verificar se a pe�a poder� executar este movimento e se capturar� uma pe�a de outra cor.
 Caso isso aconte�a, a pe�a oponente ser� retirada do tabuleiro.  Crie os retornos necess�rios.
-Fun��o RetirarPeca � Receber� uma coordenada linha-coluna e a pe�a contida nesta casa ser� retirada. Crie os retornos necess�rios. 
-Fun��o ObterPeca � Receber� uma coordenada linha-coluna e retornar� a identifica��o da pe�a <Nome , Cor>.

*/

TAB_tpCondRet inserirPeca();
TAB_tpCondRet moverPeca();
TAB_tpCondRet retirarPeca();
TAB_tpCondRet obterPeca();



/*
------FUN��ES N�O PRONTAS DA JULIA--------

-Fun��o ObterListaAmeacantes � Receber� uma coordenada linha-coluna e retornar� o ponteiro para a correspondente cabe�a de lista.
 N�o se esque�a de projetar uma forma de operar sobre esta lista no m�dulo de teste.
-Fun��o ObterListaAmeacados � Receber� uma coordenada linha-coluna e retornar� o ponteiro para a correspondente cabe�a de lista.
-Fun��o DestruirTabuleiro � destr�i o conte�do de cada casa do tabuleiro e o pr�prio tabuleiro, caso este tenha sido alocado em mem�ria din�mica.
 Obs. no 4�. trabalho ser� examinado se ocorre vazamento de mem�ria. 
*/

TAB_tpCondRet obterListaAmeacantes();
TAB_tpCondRet obterListaAmeacados();
TAB_tpCondRet destruirTabuleiro();


/***********************************************************************
*
*  $FC Fun��o: TAB  &Criar Tabuleiro
*
*  $ED Descri��o da fun��o
*     Cria uma ancora que aponta para o inicio de uma lista e coluna de tamanho fixo
*     Cria uma lista duplamente encadeada com um identificador para representar a linha de uma matriz	
*	  Cria uma lista duplamente encadeada com um identificador para representar a coluna de uma matriz	
*
*  $EP Par�metros
*     linha         - ponteiro de ponteiro para a estrutura do tipo LIS_tpLista*
*					  a ser criada.
*
*	  coluna        - ponteiro de ponteiro para a estrutura do tipo LIS_tpLista*
*					  a ser criada.
*
*	  ancora_matriz - ponteiro de ponteiro para uma estrutura do tipo TAB_ancoraTabuleiro
*
*     idMatriz       - string de identifica��o da matriz
*
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condi��o de retorno LIS_CondRetOK.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     LIS_CondRetFaltouMemoria.
*
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

TAB_tpCondRet cria_tabuleiro(LIS_tppLista linha, LIS_tppLista coluna, TAB_ancoraTabuleiro **ancora_matriz, char * idMatriz);



#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: TAB  Tabuleiro **********/

#else
#endif