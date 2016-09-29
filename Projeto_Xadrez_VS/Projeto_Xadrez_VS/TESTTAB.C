/***************************************************************************
*  $MCI Módulo de implementação: TTAB Teste Tabuleiro
*
*  Arquivo gerado:              TestTAB.c
*  Letras identificadoras:      TTAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs , julia , tauan , lucas
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data         Observações
*     5       lp,ja, tb 28/nov/2016   alteração de funções e edição do scrpit de teste
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



static const char CRIAR_TABULEIRO_CMD[] = "=criatabuleiro";

/***********************************************************************
*
*  $FC Função: TTAB &Testar tabuleiro
*
*  $ED Descrição da função
*     Cria uma matriz representada por lista de listas
*
*     Comandos disponíveis:
*
*     =resetteste - anula o vetor de listas. Provoca vazamento de memória
*	  =criatabuleiro - cria um tabuleiro com lista de listas.
*
***********************************************************************/


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[DIM_VT_LISTA];


TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{


	/* Testar CriarTabuleiro */

		 if (strcmp(ComandoTeste, CRIAR_TABULEIRO_CMD) == 0)
		 {

			 numLidos = LER_LerParametros("isi",
				 &inxLista, StringDado, &CondRetEsp);

			 if ((numLidos != 3)
				 || (!ValidarInxLista(inxLista, VAZIO)))
			 {
				 return TST_CondRetParm;
			 } /* if */

			 CondRet = LIS_CriarLista(&vtListas[inxLista], StringDado);

			 if (CondRet == 6) {

				 return TST_CondRetMemoria;

			 }

			 return TST_CompararInt(CondRetEsp, CondRet,
				 "Condicao de retorno errada ao criar lista");

		 } /* fim ativa: Testar CriarLista */

	return TST_CondRetNaoConhec;

} /* Fim função: TLIS &Testar lista */


  /********** Fim do módulo de implementação: TTAB Teste tabuleiro **********/