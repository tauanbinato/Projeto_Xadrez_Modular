/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data         Observações
*     5       lp,ja, tb 28/set/2016   alteração de funções e edição do scrpit de teste
*     4       avs       01/fev/2006   criar linguagem script simbólica
*     3       avs       08/dez/2004   uniformização dos exemplos
*     2       avs       07/jul/2003   unificação de todos os módulos em um só projeto
*     1       avs       16/abr/2003   início desenvolvimento
*
***************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"
#include	"Tabuleiro.h"


/**************************COMANDOS SCRIPT**************************/

static const char CRIAR_TABULEIRO_CMD[]	    =				"=criartabuleiro";
static const char INSERIR_PECA_CMD[]		=				"=inserirpeca";
static const char RESET_LISTA_CMD[]			=				"=resetteste";
static const char CRIAR_LISTA_CMD[]			=				"=criarlista";
static const char DESTROI_LISTA_CMD[]		=				"=destroilista";
static const char INS_NO_CMD[]				=				"=inserirno";
static const char OBTER_NO_CMD[]			=				"=obterno";
static const char EXC_NO_CORRENTE_CMD[]	    =			    "=excluirnocorrente";
static const char AVANCAR_ELEM_CMD[]		=				"=irprox";
static const char VOLTAR_ELEM_CMD[]			=				"=irant";
static const char OBTER_ID_LISTA_CMD[]      =			    "=obteridlista";
static const char ALTERA_NO_CORRENTE_CMD[]  =		     	"=alterarnocorrente";

/************************FIM COMANDOS SCRIPT************************/


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VT_TAB	   10
#define DIM_VALOR     100

LIS_tppLista            vtListas[DIM_VT_LISTA];
LIS_tppLista            vtListas_2[DIM_VT_LISTA];
TAB_ppAncoraTabuleiro	vtMatrizes[DIM_VT_TAB];


/***** Protótipos das funções encapuladas no módulo *****/
// void DestruirValor( void * pValor );
static int ValidarInxLista(int inxLista, int Modo);
static int ValidarInxMatriz(int inxLista, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste                   - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista  idLista      CondRetEsp
*     =obteridlista                 inxLista  idLista
*     =excluirnocorrente            inxLista
*     =irprox						inxLista  CondRetEsp
*     =irant						inxLista  CondRetEsp
*     =alterarnocorrente			inxLista  char         CondRetEsp
*     =destroilista                 inxLista  CondRetEsp
*     ==inserirno                   inxLista  char         CondRetEsp
*     =obterno                      inxLista  char         CondRetEsp
*     =excluirelem                  inxLista  CondRetEsp
*	  =criartabuleiro				inxLista  inxLista_2   CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	/*Inteiros*/
	int inxLista = -1,
		inxLista_2 = -1,
		numLidos = -1,
		CondRetEsp = -1,
		numElem = -1,
		ValEsp = -1,
		i,
		inxMatriz = -1;
	int  cord_linha , cord_coluna;

	/*Condicoes de Retorno*/
	TST_tpCondRet CondRet;
	LIS_tpCondRet CondRet_LIS;
	TAB_tpCondRet CondRet_TAB;


	/*Strings*/
	char   StringDado[DIM_VALOR], StringDado_2[DIM_VALOR] , CharObtido;
	char * pDado;
	char *CharDado ;
	char *CharDado_2;
	StringDado[0] = 0;

	/* Efetuar reset de teste de lista */

	if (strcmp(ComandoTeste, RESET_LISTA_CMD) == 0)
	{

		for (i = 0; i < DIM_VT_LISTA; i++)
		{
			vtListas[i] = NULL;
		} /* for */

		return TST_CondRetOK;

	} /* fim ativa: Efetuar reset de teste de lista */


	  /* Testar InserirPeca */


	else if (strcmp(ComandoTeste, INSERIR_PECA_CMD) == 0)
	{
		char *id_peca , *id_cor;
		id_peca = (char *)malloc(1 + sizeof(char));
		if (id_peca == NULL) return TST_CondRetMemoria;
		id_cor = (char *)malloc(1 + sizeof(char));
		if (id_cor == NULL) return TST_CondRetMemoria;


		numLidos = LER_LerParametros("iiicci", &inxMatriz,&cord_linha,&cord_coluna,id_peca,id_cor,&CondRetEsp);

		
		if ((numLidos != 6) || (!ValidarInxMatriz(inxMatriz, NAO_VAZIO)))
		{
			
			return TST_CondRetParm;
		} /* if */


		CondRet_TAB = inserirPeca(&vtMatrizes[inxMatriz] , cord_linha , cord_coluna , id_peca , id_cor );
		

		if (CondRet_TAB == 6) {
			printf("Entrou");
			return TST_CondRetMemoria;

		}

		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao inserir peca");

	} /* fim ativa: Testar Inserir Peca */


	  /* Testar CriarTabuleiro */


	else if (strcmp(ComandoTeste, CRIAR_TABULEIRO_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii", &inxMatriz, &CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarInxMatriz(inxMatriz, VAZIO)))
		{
			printf("Entrou");
			return TST_CondRetParm;
		} /* if */


		CondRet_TAB = cria_tabuleiro(&vtMatrizes[inxMatriz]);
		

		if (CondRet_TAB == 6) {

			return TST_CondRetMemoria;

		}

		return TST_CompararInt(CondRetEsp, CondRet_TAB,
			"Condicao de retorno errada ao criar tabuleiro");

	} /* fim ativa: Testar CriarTabuleiro */

	  /* Testar CriarLista */

	else if (strcmp(ComandoTeste, CRIAR_LISTA_CMD) == 0)
	{

		numLidos = LER_LerParametros("isi",
			&inxLista, StringDado, &CondRetEsp);

		if ((numLidos != 3)
			|| (!ValidarInxLista(inxLista, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */


		CondRet_LIS = LIS_CriarLista(&vtListas[inxLista], StringDado);



		if (CondRet_LIS == 6) {

			return TST_CondRetMemoria;

		}

		return TST_CompararInt(CondRetEsp, CondRet_LIS,
			"Condicao de retorno errada ao criar lista");

	} /* fim ativa: Testar CriarLista */

	  /* Testar Obter Id */

	else if (strcmp(ComandoTeste, OBTER_ID_LISTA_CMD) == 0)
	{

		numLidos = LER_LerParametros("isi",
			&inxLista, StringDado, &CondRetEsp);

		if (numLidos != 3)
		{
			return TST_CondRetParm;
		} /* if */

		strcpy(pDado, StringDado);

		CondRet_LIS = LIS_ObterId(vtListas[inxLista], pDado);

		return TST_CompararString(pDado, StringDado,
			"Id obtida pela função diferente da esperada");

	} /* fim ativa: Testar CriarLista */

	  /* Testar Destruir lista */

	else if (strcmp(ComandoTeste, DESTROI_LISTA_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&inxLista, &CondRetEsp);
		if ((numLidos != 2))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet_LIS = LIS_DestroiLista(vtListas[inxLista]);

		vtListas[inxLista] = NULL;

		return TST_CompararInt(CondRetEsp, CondRet_LIS,
			"Condicao de retorno errada ao inserir antes.");

	} /* fim ativa: Testar Destruir lista */

	  /* Testar inserir elemento apos */

	else if (strcmp(ComandoTeste, INS_NO_CMD) == 0)
	{

		numLidos = LER_LerParametros("ici",
			&inxLista, &CharDado, &CondRetEsp);

		if (numLidos != 3)
		{
			return TST_CondRetParm;
		} /* if */

		pDado = (char *)malloc(sizeof(char));

		if (pDado == NULL)
		{
			return TST_CondRetMemoria;
		} /* if */

		*pDado = CharDado;

		CondRet_LIS = LIS_InserirNo(&vtListas[inxLista], pDado);

		if (CondRet_LIS != LIS_CondRetOK)
		{
			free(pDado);
		} /* if */

		return TST_CompararInt(CondRetEsp, CondRet_LIS,
			"Condicao de retorno errada ao inserir apos.");

	} /* fim ativa: Testar inserir elemento apos */

	  /* Testar excluir simbolo */

	else if (strcmp(ComandoTeste, EXC_NO_CORRENTE_CMD) == 0)
	{

		numLidos = LER_LerParametros("i",
			&inxLista);

		if ((numLidos != 1)
			|| (!ValidarInxLista(inxLista, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt(0,
			LIS_ExcluirNoCorrente(&vtListas[inxLista]),
			"Condição de retorno errada ao excluir.");

	} /* fim ativa: Testar excluir simbolo */

	  /* Testar obter valor do elemento corrente */

	else if (strcmp(ComandoTeste, OBTER_NO_CMD) == 0)
	{
		numLidos = LER_LerParametros("ici",
			&inxLista, &CharDado, &CondRetEsp);

		if ((numLidos != 3))
		{
			return TST_CondRetParm;
		} /* if */

		CondRet_LIS = LIS_ObterNo(vtListas[inxLista], &CharObtido);

		if (CondRet_LIS == 2)
		{
			return  TST_CompararPonteiroNulo(1, &CharObtido,
				"Erro Lista Vazia");
		} /* if */

		return TST_CompararChar(CharObtido, CharDado,
			"Valor do elemento errado.");

	} /* fim ativa: Testar obter valor do elemento corrente */

	  /* Testar Avançar elemento */

	else if (strcmp(ComandoTeste, AVANCAR_ELEM_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii", &inxLista,
			&CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarInxLista(inxLista, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt(CondRetEsp,
			LIS_AvancarElementoCorrente(vtListas[inxLista]),
			"Condicao de retorno errada ao avancar");

	} /* fim ativa: LIS  &Avançar elemento */

	  /* LIS  &Voltar elemento */

	else if (strcmp(ComandoTeste, VOLTAR_ELEM_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii", &inxLista,
			&CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarInxLista(inxLista, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt(CondRetEsp,
			LIS_VoltarElementoCorrente(vtListas[inxLista]),
			"Condicao de retorno errada ao avancar");

	} /* fim ativa: LIS  &Voltar elemento */

	else if (strcmp(ComandoTeste, ALTERA_NO_CORRENTE_CMD) == 0)
	{

		numLidos = LER_LerParametros("ici", &inxLista, &CharDado,
			&CondRetEsp);

		if ((numLidos != 3))
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt(CondRetEsp,
			LIS_AlterarElementoCorrente(vtListas[inxLista], CharDado),
			"Condicao de retorno errada ao avancar");

	} /* fim ativa: LIS  &Voltar elemento */

	return TST_CondRetNaoConhec;

} /* Fim função: TLIS &Testar lista */


  /*****  Código das funções encapsuladas no módulo  *****/

  /***********************************************************************
  *
  *  $FC Função: TLIS -Destruir valor
  *
  ***********************************************************************/

void DestruirValor(void * pValor)
{

	free(pValor);

} /* Fim função: TLIS -Destruir valor */

  /***********************************************************************
  *
  *  $FC Função: TLIS -Validar indice de lista
  *
  ***********************************************************************/

int ValidarInxLista(int inxLista, int Modo)
{

	if ((inxLista <  0)
		|| (inxLista >= DIM_VT_LISTA))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtListas[inxLista] != 0)
		{
			return FALSE;
		} /* if */


	}
	else
	{
		if (vtListas[inxLista] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TLIS -Validar indice de lista */

int ValidarInxMatriz(int inxLista, int Modo)
{

	if ((inxLista <  0)
		|| (inxLista >= DIM_VT_LISTA))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtMatrizes[inxLista] != 0)
		{
			return FALSE;
		} /* if */


	}
	else
	{
		if (vtMatrizes[inxLista] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TLIS -Validar indice de lista */

  /********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

