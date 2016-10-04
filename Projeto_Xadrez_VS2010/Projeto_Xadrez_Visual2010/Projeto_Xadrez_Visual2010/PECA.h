#pragma once
#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: PEC  Estrutura de uma Pca
*
*  Arquivo gerado:              PECA.h
*  Letras identificadoras:      PECA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PECA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Julia Aleixo , Lucas Palma , Tauan Binato
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tbf   26/set/2016 início desenvolvimento.
*
*  $ED Descrição do módulo
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
*  $TC Tipo de dados: PEC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de uma PECA
*
***********************************************************************/

typedef enum {

	PEC_CondRetOK,
	/* Concluiu corretamente  = 0*/

	PEC_CondRetListaVazia,
	/* A lista não contém elementos = 1 */

	PEC_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	PEC_CondRetNaoAchou,
	/* Não encontrou o valor procurado = 3*/

	PEC_CondRetFaltouMemoria
	/* Faltou memória ao tentar criar um elemento de lista = 4 */

} PEC_tpCondRet;


//Estruturas-----------------------------------------
typedef struct PEC_tagPeca * PEC_tppPeca;
//Estruturas-----------------------------------------



/***********************************************************************
*
*  $FC Função: PEC  &Insere nome 
*
*  $ED Descrição da função
*     Insere um nome em uma estrutura peca
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  nome_peca  - nome de uma peca
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*
***********************************************************************/
PEC_tpCondRet PEC_insereNomeDePeca(PEC_tppPeca *peca, char *nome_peca);


/***********************************************************************
*
*  $FC Função: PEC  &Insere cor
*
*  $ED Descrição da função
*     Insere uma cor em uma estrutura peca
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  cor_peca - nome da cor de uma peca
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*
***********************************************************************/
PEC_tpCondRet PEC_insereCorDePeca(PEC_tppPeca *peca, char *cor_peca);

/***********************************************************************
*
*  $FC Função: PEC  &Obtem nome peca
*
*  $ED Descrição da função
*     Funcao de acesso para obter nome de uma estrutura peca
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  nome_peca  - nome de uma peca
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*
***********************************************************************/
PEC_tpCondRet PEC_obtemNomeDePeca(PEC_tppPeca *peca, char *nome_peca);

/***********************************************************************
*
*  $FC Função: PEC  &Obtem cor peca
*
*  $ED Descrição da função
*     Funcao de acesso para obter nome de uma estrutura peca
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  cor_peca  - nome da cor de uma peca
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*
***********************************************************************/

PEC_tpCondRet PEC_obtemCorDePeca(PEC_tppPeca *peca, char *cor_peca);

/***********************************************************************
*
*  $FC Função: PEC  &Cria Peca
*
*  $ED Descrição da função
*     Cria e inicializa uma peca
*
*  $EP Parâmetros
*     peca  - ponteiro para a estrutura a ser manipulada
*	  nome_peca  - nome de uma peca
*	  cor_peca - nome da cor de uma peca
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*
***********************************************************************/
PEC_tpCondRet PEC_criaPeca(PEC_tppPeca *peca, char *nome_peca, char *cor_peca);

#undef PECA_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro **********/

#else
#endif
