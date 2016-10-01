/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <stdlib.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void *pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeca de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

		 char idLista[5];
			   /*Identificação da lista*/

		// void(*ExcluirValor) (void * pValor);                                              Acho q n tem necessidade disso.
		 /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tpLista ;

/***** Prototipos das fun��es encapuladas no m�dulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista* pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Funcao: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista (LIS_tppLista* pLista, char* idLista) {

	  LIS_tpLista * aux ;
	  
      aux = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( aux == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */
	  
      LimparCabeca( aux ) ;
	  strcpy(aux->idLista, idLista);
	  *pLista = aux;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Funcao: LIS  &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestroiLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

	  if (pLista == NULL)
		  return LIS_CondRetListaNaoExiste;

      LIS_EsvaziarLista( pLista ) ;

	  return LIS_CondRetOK;

   } /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
**
*  Funcao: LIS  &ObeterId
*  ****/

   LIS_tpCondRet LIS_ObterId(LIS_tppLista pLista, char *idLista) {

	   idLista = pLista->idLista;
	   return LIS_CondRetOK;
   
   } /* Fim Fun��o: LIS  &ObterId */
    
/***************************************************************************

*
*  Funcao: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

   LIS_tpCondRet LIS_InserirNo( LIS_tppLista* pLista ,void * pValor        )
      
   {
      tpElemLista * pElem ;
	  char * aux;
      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inserir ap�s */
         pElem = CriarElemento( pLista , pValor ) ;

         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */
		
      /* Encadear o elemento ap�s o elemento */

         if ((*pLista)->pElemCorr == NULL )
         {
			 (*pLista)->pOrigemLista = pElem ;
			 (*pLista)->pFimLista = pElem ;
         } else
         {
            if ((*pLista)->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = (*pLista)->pElemCorr->pProx ;
			   (*pLista)->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
				(*pLista)->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = (*pLista)->pElemCorr ;
			(*pLista)->pElemCorr->pProx = pElem ;

         } /* if */
		
		 pElem->pValor = pValor;

		 (*pLista)->pElemCorr = pElem ;
		 
         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirNoCorrente( LIS_tppLista* pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ((*pLista)->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = (*pLista)->pElemCorr ;

      /* Desencadeia � esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
			(*pLista)->pElemCorr    = pElem->pAnt ;
         } else {
			 (*pLista)->pElemCorr    = pElem->pProx ;
			 (*pLista)->pOrigemLista = (*pLista)->pElemCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
			 (*pLista)->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( &pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

LIS_tpCondRet LIS_ObterNo( LIS_tppLista* pLista, char* CharObtido ) {
#ifdef _DEBUG
	   assert(pLista != NULL);
#endif

	   if ((*pLista)->pElemCorr == NULL)
	   {
		   *CharObtido = NULL;
		   return LIS_CondRetListaVazia;
	   } /* if */

	   *CharObtido = (*pLista)->pElemCorr->pValor;
	  
	   return LIS_CondRetOK;

   } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista* pLista)
   {

      int i ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( (*pLista)->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avan�ar para frente */
		 if ((*pLista)->pElemCorr->pProx != NULL) {

			 (*pLista)->pElemCorr = (*pLista)->pElemCorr->pProx;

			 return LIS_CondRetOK;
		 }

		 /* fim ativa: Tratar avan�ar para frente */
		 
		 /* Tratar No corrente é o ultimo */
		 else if ((*pLista)->pElemCorr->pProx == NULL)
			 return LIS_CondRetFimLista;

   } /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Voltar elemento
*  ****/

LIS_tpCondRet LIS_VoltarElementoCorrente(LIS_tppLista* pLista)
   {

	   int i;

		#ifdef _DEBUG
			assert(pLista != NULL);
		#endif

	   /* Tratar lista vazia */

	   if ((*pLista)->pElemCorr == NULL)
	   {

		   return LIS_CondRetListaVazia;

	   } /* fim ativa: Tratar lista vazia */

		 /* Tratar avan�ar para tras */
	   if ((*pLista)->pElemCorr->pAnt != NULL) {

		   (*pLista)->pElemCorr = (*pLista)->pElemCorr->pAnt;

		   return LIS_CondRetOK;
	   }

	   /* fim ativa: Tratar avan�ar para tras */

	   /* Tratar No corrente é o primeiro */
	   else if ((*pLista)->pElemCorr->pAnt == NULL)
		   return LIS_CondRetInicioLista;

   } /* Fim fun��o: LIS  &Avan�ar elemento */
/***************************************************************************
*
*  Fun��o: LIS  &Alterar elemento corrente
*  ****/

LIS_tpCondRet LIS_AlterarElementoCorrente(LIS_tppLista pLista, char CharDado)
{
#ifdef _DEBUG
	assert(pLista != NULL);
#endif
	
	/* Tratar se Lista Existe */
	if (pLista == NULL) {

		return LIS_CondRetListaNaoExiste;
	}
	/* fim ativa: Tratar se Lista Existe */

	/* Tratar lista vazia */

	if (pLista->pElemCorr == NULL)
	{
		return LIS_CondRetListaVazia;

	} /* fim ativa: Tratar lista vazia */

   
	/* Tratar troca */
	pLista->pElemCorr->pValor = CharDado;

	/* fim ativa: Tratar troca */

	return LIS_CondRetOK;

} /* Fim fun��o: LIS  &Avan�ar elemento */

/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista (ESTATICA)
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Funcao: LIS  -Criar o elemento (ESTATICA)
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista* pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;
	

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */
	   
      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;
	  (*pLista)->numElem ++ ;

      return pElem ;

   } /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista (ESTATICA)
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {
      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
	  pLista->numElem = 0;

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */

/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/

   //