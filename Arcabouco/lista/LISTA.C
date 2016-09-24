//?/***************************************************************************
//*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
//*
//*  Arquivo gerado:              LISTA.c
//*  Letras identificadoras:      LIS
//*
//*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
//*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
//*
//*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
//*  Gestor:  LES/DI/PUC-Rio
//*  Autores: avs
//*
//*  $HA Histórico de evolução:
//*     Versão  Autor    Data     Observações
//*     4       avs   01/fev/2006 criar linguagem script simbólica
//*     3       avs   08/dez/2004 uniformização dos exemplos
//*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
//*     1       avs   16/abr/2003 início desenvolvimento
//*
//***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"
#include	<assert.h>

#include    "Lista.h"
#include	"PESSOA.H"


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

         Infonome * pValor ;
               /* Ponteiro para a estrutura infonome */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
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
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       Infonome *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/
   

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      LIS_tpLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

      return pLista ;

   } /* Fim função: LIS  &Criar lista */
   /***********************************************************************
*
*  $FC Função: LIS  -Insere ordenado (chave de ordenação: iniciais)
*
***********************************************************************/

LIS_tpCondRet  LIS_insereOrdenado (LIS_tppLista Lista, Infonome* pValor)
{
	tpElemLista *novoElem, *aux = NULL;
	tpElemLista *auxProx = Lista->pOrigemLista;

	char ** iniciais_auxProx , ** iniciais_pValor;
	
	//Chama funções do módulo PESSOA
	PES_ObterValorIniciais(iniciais_pValor , pValor);
	PES_ObterValorIniciais(iniciais_auxProx , auxProx->pValor);

	printf("values:  %s %s :::",*iniciais_auxProx, *iniciais_pValor);
	/*
	novoElem = CriarElemento(Lista , pValor);

	if(Lista->pOrigemLista == NULL){
		printf("\n::::::::a1::::::::\n");
		Lista->pOrigemLista = novoElem;
		printf("ELEM: %d \n", novoElem->pValor);
		return LIS_CondRetOK;
		
	}
	printf("iniaux %s inival %s\n",iniciais_auxProx, iniciais_pValor );
	if(strcmp(*iniciais_auxProx, *iniciais_pValor) > 0){
		printf("\n::::::::a2::::::::\n");
		Lista->pOrigemLista->pAnt = novoElem;
		novoElem->pProx = Lista->pOrigemLista;
		Lista->pOrigemLista = novoElem;
		printf("ELEM: %d \n", novoElem->pValor);
		return LIS_CondRetOK;
	}

	aux = auxProx;
	while(strcmp(*iniciais_auxProx, *iniciais_pValor) < 0){
		if(aux->pProx == NULL){
			printf("\n::::::::a3::::::::\n");
			aux->pProx = novoElem;
			printf("ELEM: %d \n", novoElem->pValor);
			return LIS_CondRetOK;
		}
		aux = auxProx;
		auxProx = auxProx->pProx;
		PES_ObterValorIniciais(iniciais_auxProx , auxProx->pValor);
	}

	novoElem->pProx = aux->pProx;
	aux->pProx = novoElem;
	novoElem->pAnt = aux;
	printf("\n::::::::a0::::::::\n");
	if(novoElem->pProx != NULL){
		novoElem->pProx->pAnt = novoElem;
	}
	printf("ELEM: %d \n", novoElem->pValor);
	return LIS_CondRetOK;*/
	
	while(auxProx != NULL && strcmp(*iniciais_auxProx, *iniciais_pValor) == -1)
	{
		aux = auxProx;
		auxProx = auxProx->pProx;

		PES_ObterValorIniciais(iniciais_auxProx , auxProx->pValor);
	}

	novoElem = CriarElemento(Lista , pValor);
	
	if(aux == NULL) 
	{
		novoElem->pProx = Lista->pOrigemLista;
		Lista->pOrigemLista = novoElem;
		//novoElem->pProx->pAnt = novoElem;
	}
	else 
	{
		novoElem->pProx = aux->pProx;
		aux->pProx = novoElem;
		novoElem->pAnt = aux;
	}

	printf("ELEM: %d \n", novoElem->pValor);

	return LIS_CondRetOK;

} /* Fim Função: LIS -Insere ordenado (chave de ordenação: iniciais)  */
/***********************************************************************
*
*  $FC Função: LIS  -Exibe Elementos da Lista
*
***********************************************************************/
LIS_tpCondRet ExibeElemLista(LIS_tppLista pLista)
{   
	char **aux_Iniciais;
	char **aux_Nome;
	pLista->pElemCorr = pLista->pOrigemLista;

	if(pLista->pElemCorr == NULL){
		
		return LIS_CondRetListaVazia;
	}
	
	//DUVIDA, N TERIAMOS QUE POR O ELEMENTO CORRENTO DE VOLTA PARA O PRIMEIRO ELEMENTO CASO N TIVESSE?

	while (pLista->pElemCorr != NULL)
	{
		
		//Chama funções do módulo PESSOA
	    PES_ObterValorIniciais(aux_Iniciais , pLista->pElemCorr->pValor);
		printf("saiu obtervaloriniciais\n");
	    PES_ObterValorNome(aux_Nome , pLista->pElemCorr->pValor);

		printf("Iniciais: %s, Nome: %s\n",aux_Iniciais,aux_Nome);
		LIS_AvancarElementoCorrente(pLista , pLista->numElem);   
	}

	free(aux_Iniciais);
	free(aux_Nome);

	return LIS_CondRetOK;
}/* Fim Função: LIS -Exibe Elementos da Lista  */
/***************************************************************************
*
*  Função: LIS  &Destruir lista                                                                          
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista                                                                          
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

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista , Infonome * pValor)
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inserir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                         Infonome * pValor        )
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */
         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista , Infonome **pValor )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
		pValor = NULL;
        return LIS_CondRetFimLista ;

      } /* if */
	 
	  *pValor = pLista->pElemCorr->pValor ;
	  
      return LIS_CondRetOK;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial                                                             
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final                                                              
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento Corrente				
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista , int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo pessoa													
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    Infonome * pValor        )
   {
      
	  char ** aux_Nome , ** aux_Iniciais , **aux_Nome_na_Struct , **aux_Iniciais_na_Struct;
      tpElemLista * pElem ;

	  //Chama funções do módulo PESSOA
	  PES_ObterValorIniciais(aux_Iniciais_na_Struct , pValor);
	  PES_ObterValorNome(aux_Nome_na_Struct , pValor);

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
		    //Chama funções do módulo PESSOA
	        PES_ObterValorIniciais(aux_Iniciais , pElem->pValor);
			PES_ObterValorNome(aux_Nome , pElem->pValor);

		  if ( strcmp(*aux_Iniciais,*aux_Iniciais_na_Struct) == 0 && strcmp(*aux_Nome,*aux_Nome_na_Struct) == 0 )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */


      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista , Infonome *       pValor  )
   {

	  char ** aux_Nome , ** aux_Iniciais;
      tpElemLista * pElem ;
      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
	 
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

	  //Chama funções do módulo PESSOA
	  //PES_ObterValorIniciais(aux_Iniciais , pValor);
	  //PES_ObterValorNome(aux_Nome , pValor);
	  //PES_preencher_estrutura(&pElem->pValor, *aux_Nome , *aux_Iniciais);
	  pElem->pValor = pValor;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/