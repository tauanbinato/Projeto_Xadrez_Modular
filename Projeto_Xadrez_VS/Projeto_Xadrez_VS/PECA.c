/***************************************************************************
*  $MCI M�dulo de implementa��o: PEC Peca
*
*  Arquivo gerado:              PECA.c
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    Arcabou�o para a automa��oo de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PECA.BSW
*
*  Projeto: INF 1301 / 1628 Automatizacao dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tb,ja,lp   26/set/2016 in�cio desenvolvimento.
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

	
	char nome_peca[2];
	/* Nome da peca especifica*/

	char cor_peca[2];
	/* Cor da peca especifica*/


} PEC_Peca;
