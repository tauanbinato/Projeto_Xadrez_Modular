/***************************************************************************
*  $MCI Módulo de implementação: ARV  Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\INSTRUM.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <memory.h>

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN

#ifdef _DEBUG
   #include   "Generico.h"
   #include   "Conta.h"
   #include   "cespdin.h"
   #include   "..\\tabelas\\IdTiposEspaco.def"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoArvore {

         #ifdef _DEBUG

         struct tgArvore * pCabeca ;
               /* Ponteiro para cabeca
               *
               *$ED Descrição
               *   Todos os nós da árvore devem apontar para a respectiva cabeça.
               *   Esse ponteiro corresponde a um identificador da árvore para fins
               *   de verificação da integridade. */

         #endif

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */

         char Valor ;
               /* Valor do nó */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpArvore ;

/*****  Dados encapsulados no módulo  *****/

      #ifdef _DEBUG

      static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espaço de dados lixo usado ao testar */

      #endif

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoArvore * CriarNo( tpArvore * pArvore , char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( tpArvore * pArvore , char ValorParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

#ifdef _DEBUG

   static ARV_tpCondRet VerificarNo( tpNoArvore * pNo ) ;

#endif

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV  &Criar árvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( void ** ppArvoreParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_CriarArvore" ) ;
      #endif

      if ( *ppArvoreParm != NULL )
      {
         ARV_DestruirArvore( ppArvoreParm ) ;
      } /* if */

      pArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( pArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pArvore->pNoRaiz = NULL ;
      pArvore->pNoCorr = NULL ;

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pArvore , ARV_TipoEspacoCabeca ) ;
      #endif

      *ppArvoreParm = pArvore ;

      return ARV_CondRetOK ;

   } /* Fim função: ARV  &Criar árvore */

/***************************************************************************
*
*  Função: ARV  &Destruir árvore
*  ****/

   void ARV_DestruirArvore( void ** ppArvoreParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_DestruirArvore" ) ;
      #endif

      pArvore = ( tpArvore * )( * ppArvoreParm ) ;
      if ( pArvore != NULL )
      {
         if ( pArvore->pNoRaiz != NULL )
         {
            DestroiArvore( pArvore->pNoRaiz ) ;
         } /* if */
         free( pArvore ) ;
         *ppArvoreParm = NULL ;
      } /* if */

   } /* Fim função: ARV  &Destruir árvore */

/***************************************************************************
*
*  Função: ARV  &Adicionar filho à esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( void * pArvoreParm , char ValorParm )
   {

      tpArvore   * pArvore ;

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_InserirEsquerda" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * )( pArvoreParm ) ;

      /* Tratar árvore vazia, esquerda */

         CondRet = CriarNoRaiz( pArvoreParm , ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( pArvore , ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV  &Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV  &Adicionar filho à direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( void * pArvoreParm , char ValorParm )
   {

      tpArvore * pArvore ;

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_InserirDireita" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * )( pArvoreParm ) ;

      /* Tratar árvore vazia, direita */

         CondRet = CriarNoRaiz( pArvoreParm , ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( pArvore , ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV  &Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV  &Ir para nó pai
*  ****/

   ARV_tpCondRet ARV_IrPai( void * pArvoreParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_IrPai" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) pArvoreParm ;

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNohEhRaiz ;

   } /* Fim função: ARV  &Ir para nó pai */

/***************************************************************************
*
*  Função: ARV  &Ir para nó à esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( void * pArvoreParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_IrNoEsquerda" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) pArvoreParm ;

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV  &Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV  &Ir para nó à direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( void * pArvoreParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_IrNoDireita" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) pArvoreParm ;

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV  &Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV  &Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( void * pArvoreParm , char * ValorParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_ObterValorCorr" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) pArvoreParm ;

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      * ValorParm = pArvore->pNoCorr->Valor ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV  &Obter valor corrente */

#ifdef _DEBUG

/***************************************************************************
*
*  Função: ARV  &Verificar uma árvore
*  ****/

   ARV_tpCondRet ARV_VerificarArvore( void * pArvoreParm )
   {

      tpArvore * pArvore = NULL ;

      if ( ARV_VerificarCabeca( pArvoreParm ) != ARV_CondRetOK )
      {
         return ARV_CondRetErroEstrutura ;
      } /* if */

      CED_MarcarEspacoAtivo( pArvoreParm ) ;

      pArvore = ( tpArvore * ) ( pArvoreParm ) ;

      return VerificarNo( pArvore->pNoRaiz ) ;

   } /* Fim função: ARV  &Verificar uma árvore */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: ARV  &Verificar um nó cabeça
*  ****/

   ARV_tpCondRet ARV_VerificarCabeca( void * pCabecaParm )
   {

      tpArvore * pArvore = NULL ;

      /* Verifica o tipo do espaço */

         if ( pCabecaParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( ! CED_VerificarEspaco( pCabecaParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( ARV_TipoEspacoCabeca ,
              CED_ObterTipoEspaco( pCabecaParm ) ,
              "Tipo do espaço de dados não é cabeça de árvore." ) != TST_CondRetOK )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         pArvore = ( tpArvore * )( pCabecaParm ) ;

      /* Verifica raiz da árvore */

         if ( pArvore->pNoRaiz != NULL )
         {
            if ( TST_CompararPonteiro( pCabecaParm , pArvore->pNoRaiz->pCabeca ,
                 "Nó raiz não aponta para cabeça." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } else {
            if ( TST_CompararPonteiro( NULL , pArvore->pNoCorr ,
                 "Árvore vazia tem nó corrente não NULL." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      /* Verifica corrente */

         if ( pArvore->pNoCorr != NULL )
         {
            if ( TST_CompararPonteiro( pCabecaParm , pArvore->pNoCorr->pCabeca ,
                 "Nó corrente não aponta para cabeça." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } else {
            if ( TST_CompararPonteiro( NULL , pArvore->pNoRaiz ,
                 "Árvore não vazia tem nó corrente NULL." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      return ARV_CondRetOK ;

   } /* Fim função: ARV  &Verificar um nó cabeça */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: ARV  &Verificar um nó de estrutura
*  ****/

   ARV_tpCondRet ARV_VerificarNo( void * pNoParm )
   {

      tpNoArvore * pNo     = NULL ;
      tpArvore   * pArvore = NULL ;

      /* Verificar se é nó estrutural */

         if ( pNoParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar nó inexistente." ) ;
            return ARV_CondRetErroEstrutura ;

         } /* if */

         if ( ! CED_VerificarEspaco( pNoParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( ARV_TipoEspacoNo ,
              CED_ObterTipoEspaco( pNoParm ) ,
              "Tipo do espaço de dados não é nó de árvore." ) != TST_CondRetOK )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         pNo     = ( tpNoArvore * )( pNoParm ) ;
         pArvore = pNo->pCabeca ;

      /* Verificar cabeça */

         if ( pArvore->pNoRaiz != NULL  )
         {
            if ( TST_CompararPonteiro( pArvore , pArvore->pNoRaiz->pCabeca ,
                 "Nó não pertence à árvore." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } else
         {
            return TST_NotificarFalha( "Nó pertence a árvore vazia." ) ;
         } /* if */

      /* Verificar pai */

         if ( pNo->pNoPai != NULL )
         {
            if ( ( pNo->pNoPai->pNoEsq != pNo )
              && ( pNo->pNoPai->pNoDir != pNo ))
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } else
         {
            if ( TST_CompararPonteiro( pNo , pArvore->pNoRaiz ,
                 "Nó raiz não é apontado por cabeça da árvore." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      /* Verificar filho à esquerda */

         if ( pNo->pNoEsq != NULL )
         {
            if ( TST_CompararPonteiro( pNo , pNo->pNoEsq->pNoPai ,
                 "Pai de filho à esquerda não é este nó." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
            if ( TST_CompararPonteiro( pArvore , pNo->pNoEsq->pCabeca ,
                 "Filho à esquerda não pertence à mesma árvore." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      /* Verificar filho à direita */

         if ( pNo->pNoDir != NULL )
         {
            if ( TST_CompararPonteiro( pNo , pNo->pNoDir->pNoPai ,
                 "Pai de filho à direita não é este nó." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
            if ( TST_CompararPonteiro( pArvore , pNo->pNoDir->pCabeca ,
                 "Filho à direita não pertence à mesma árvore." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      return ARV_CondRetOK ;

   } /* Fim função: ARV  &Verificar um nó de estrutura */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: ARV  &Deturpar árvore
*  ****/

   void ARV_Deturpar( void * pArvoreParm ,
                      ARV_tpModosDeturpacao ModoDeturpar )
   {

      tpArvore * pArvore = NULL ;

      if ( pArvoreParm == NULL )
      {
         return ;
      } /* if */

      pArvore = ( tpArvore * )( pArvoreParm ) ;

      switch ( ModoDeturpar ) {

      /* Modifica o tipo da cabeça */

         case DeturpaTipoCabeca :
         {

            CED_DefinirTipoEspaco( pArvore , CED_ID_TIPO_VALOR_NULO ) ;

            break ;

         } /* fim ativa: Modifica o tipo da cabeça */

      /* Anula ponteiro raiz */

         case DeturpaRaizNula :
         {

            pArvore->pNoRaiz = NULL ;

            break ;

         } /* fim ativa: Anula ponteiro raiz */

      /* Anula ponteiro corrente */

         case DeturpaCorrenteNulo :
         {

            pArvore->pNoCorr = NULL ;

            break ;

         } /* fim ativa: Anula ponteiro corrente */

      /* Faz raiz apontar para lixo */

         case DeturpaRaizLixo :
         {

            pArvore->pNoRaiz = ( tpNoArvore * )( EspacoLixo ) ;

            break ;

         } /* fim ativa: Faz raiz apontar para lixo */

      /* Faz corrente apontar para lixo */

         case DeturpaCorrenteLixo :
         {

            pArvore->pNoCorr = ( tpNoArvore * )( EspacoLixo ) ;

            break ;

         } /* fim ativa: Faz corrente apontar para lixo */

      /* Deturpar espaço cabeca */

         case DeturparEspacoCabeca :
         {

            memcpy( (( char * )( pArvore )) - 10 , "????" , 4 ) ;

            break ;

         } /* fim ativa: Deturpar espaço cabeca */

      /* Deturpa nóo */

         default :

         if ( pArvore->pNoCorr != NULL )
         {

            switch ( ModoDeturpar ) {

            /* Modifica tipo nó corrente */

               case DeturpaTipoNo :
               {

                  CED_DefinirTipoEspaco( pArvore->pNoCorr , CED_ID_TIPO_VALOR_NULO ) ;

                  break ;

               } /* fim ativa: Modifica tipo nó corrente */

            /* Anula ponteiro cabeça */

               case DeturpaPtCabecaNulo :
               {

                  pArvore->pNoCorr->pCabeca = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro cabeça */

            /* Anula ponteiro pai */

               case DeturpaPtPaiNulo :
               {

                  pArvore->pNoCorr->pNoPai = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro pai */

            /* Anula ponteiro filho esquerda */

               case DeturpaPtEsqNulo :
               {

                  pArvore->pNoCorr->pNoEsq = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro filho esquerda */

            /* Anula ponteiro filho direita */

               case DeturpaPtDirNulo :
               {

                  pArvore->pNoCorr->pNoDir = NULL ;

                  break ;

               } /* fim ativa: Anula ponteiro filho direita */

            /* Faz ponteiro cabeça apontar para lixo */

               case DeturpaPtCabecaLixo :
               {

                  pArvore->pNoCorr->pCabeca = ( tpArvore * )( EspacoLixo ) ;

                  break ;

               } /* fim ativa: Faz ponteiro cabeça apontar para lixo */

            /* Faz ponteiro pai apontar para lixo */

               case DeturpaPtPaiLixo :
               {

                  pArvore->pNoCorr->pNoPai = ( tpNoArvore * )( EspacoLixo ) ;

                  break ;

               } /* fim ativa: Faz ponteiro pai apontar para lixo */

            /* Faz ponteiro filho esquerda apontar para lixo */

               case DeturpaPtEsqLixo :
               {

                  pArvore->pNoCorr->pNoEsq = ( tpNoArvore * )( EspacoLixo ) ;

                  break ;

               } /* fim ativa: Faz ponteiro filho esquerda apontar para lixo */

            /* Faz ponteiro filho direita apontar para lixo */

               case DeturpaPtDirLixo :
               {

                  pArvore->pNoCorr->pNoDir = ( tpNoArvore * )( EspacoLixo ) ;

                  break ;

               } /* fim ativa: Faz ponteiro filho direita apontar para lixo */

            /* Atribui valor fora do domínio do espaço */

               case DeturpaValor :
               {

                  memcpy( &( pArvore->pNoCorr->Valor ) , "<<<<<" , 5 ) ;

                  break ;

               } /* fim ativa: Atribui valor fora do domínio do espaço */

            /* Deturpar espaço no */

               case DeturparEspacoNo :
               {

                  memcpy( (( char * )( pArvore->pNoCorr )) - 50 , "????????" , 8 ) ;

                  break ;

               } /* fim ativa: Deturpar espaço no */

            } /* fim seleciona: Deturpa nóo */

            break ;

         } /* fim ativa: Deturpa nóo */

      } /* fim seleciona: Raiz de ARV  &Deturpar árvore */

   } /* Fim função: ARV  &Deturpar árvore */

#endif


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV  -Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoArvore * CriarNo( tpArvore * pArvore , char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pNo , ARV_TipoEspacoNo ) ;
         pNo->pCabeca = pArvore ;
      #else
         pArvore = NULL ;
      #endif

      pNo->pNoPai  = NULL ;
      pNo->pNoEsq  = NULL ;
      pNo->pNoDir  = NULL ;
      pNo->Valor   = ValorParm ;

      return pNo ;

   } /* Fim função: ARV  -Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV  -Criar nó raiz da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( tpArvore * pArvore , char ValorParm )
   {

      tpNoArvore * pNo ;

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( pArvore , ValorParm ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim função: ARV  -Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV  -Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim função: ARV  -Destruir a estrutura da árvore */

#ifdef _DEBUG


/***********************************************************************
*
*  $FC Função: ARV  -Explorar verificando os nós de uma árvore
*
*  $ED Descrição da função
*     Percorre recursivamente a árvore verificando os nós à medida que forem
*     visitados. Caso seja encontrado alguma falha, a verificação será
*     suspensa. Portanto, no caso de falha, é possível que nem todos
*     os nós da árvore sejam visitados.
*
***********************************************************************/

   ARV_tpCondRet VerificarNo( tpNoArvore * pNo )
   {

      ARV_tpCondRet CondErro = ARV_CondRetOK ;

      if ( pNo == NULL )
      {
         return ARV_CondRetOK ;
      } /* if */

      CED_MarcarEspacoAtivo( pNo ) ;

      CondErro = ARV_VerificarNo( pNo ) ;

      if ( CondErro == ARV_CondRetOK )
      {
         CondErro = VerificarNo( pNo->pNoEsq ) ;
      } /* if */

      if ( CondErro == ARV_CondRetOK )
      {
         CondErro = VerificarNo( pNo->pNoDir ) ;
      } /* if */

      return CondErro ;

   } /* Fim função: ARV  -Explorar verificando os nós de uma árvore */

#endif

/********** Fim do módulo de implementação: ARV  Módulo árvore **********/

