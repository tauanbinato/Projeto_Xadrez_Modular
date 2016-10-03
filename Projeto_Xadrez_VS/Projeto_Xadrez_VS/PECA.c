/***************************************************************************
*  $MCI Módulo de implementação: PEC Peca
*
*  Arquivo gerado:              PECA.c
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    Arcabouço para a automaçãoo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PECA.BSW
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


#define LISTA_OWN
#include "Peca.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: PEC Descritor de uma estrutura Peca
*
***********************************************************************/

typedef struct PEC_tagPeca {

	
	char *nome_peca;
	/* Nome da peca especifica*/

	char *cor_peca;
	/* Cor da peca especifica*/


} PEC_Peca;

PEC_tpCondRet PEC_insereNomeDePeca(PEC_tppPeca *peca , char *nome_peca) {

	(*peca)->nome_peca = *nome_peca;

	return PEC_CondRetOK;
}

PEC_tpCondRet PEC_insereCorDePeca(PEC_tppPeca *peca, char *cor_peca) {

	(*peca)->cor_peca = *cor_peca;

	return PEC_CondRetOK;
}
