#pragma once
#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: PEC  Estrutura de uma Pca
*
*  Arquivo gerado:              PECA.h
*  Letras identificadoras:      PECA
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PECA.BSW
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


#if defined( PECA_OWN )
#define PECA_EXT
#else
#define PECA_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: PEC Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es de uma PECA
*
***********************************************************************/

typedef enum {

	PEC_CondRetOK,
	/* Concluiu corretamente  = 0*/

	PEC_CondRetListaVazia,
	/* A lista n�o cont�m elementos = 1 */

	PEC_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	PEC_CondRetNaoAchou,
	/* N�o encontrou o valor procurado = 3*/

	PEC_CondRetFaltouMemoria
	/* Faltou mem�ria ao tentar criar um elemento de lista = 4 */

} PEC_tpCondRet;


//Estruturas-----------------------------------------
typedef struct PEC_tagPeca * PEC_tppPeca;
//Estruturas-----------------------------------------



/***********************************************************************
*
*  $FC Fun��o: PEC  &Insere nome 
*
*  $ED Descri��o da fun��o
*     Insere um nome em uma estrutura peca
*
*  $EP Par�metros
*     peca  - ponteiro para a estrutura a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*
***********************************************************************/
PEC_tpCondRet PEC_insereNomeDePeca(PEC_tppPeca *peca, char *nome_peca);


/***********************************************************************
*
*  $FC Fun��o: PEC  &Insere cor
*
*  $ED Descri��o da fun��o
*     Insere uma cor em uma estrutura peca
*
*  $EP Par�metros
*     peca  - ponteiro para a estrutura a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*
***********************************************************************/
PEC_tpCondRet PEC_insereCorDePeca(PEC_tppPeca *peca, char *cor_peca);



#undef PECA_EXT

/********** Fim do m�dulo de defini��o: TAB  Tabuleiro **********/

#else
#endif
