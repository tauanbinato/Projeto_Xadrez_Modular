/***************************************************************************
*  $MCI Módulo de implementação: TBS  Tabela de strings
*
*  Arquivo gerado:              TabStr.C
*  Letras identificadoras:      TBS
*  Número identificador:        000
*
*  Nome da base de software:    Gerar e acessar tabelas de strings
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\TABELA.BSW
*
*  Projeto: INF 1301/1628 - Exemplos
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1        avs  20/11/2004  Inicio desenvolvimento
*
***************************************************************************/

#include <string.h>
#include <assert.h>

#define TabStr_OWN
#include "TabStr.H"
#undef TabStr_OWN

#define     DIM_STRING                256
#define     ID_NAO_ENCONTROU            1
#define     STRING_ERRO           "?!?!?"
    /* TMS_MIN_LENGTH deve ser igual ou maior do que o comprimento do
    *  string STRING_ERRO */

#include    "TabelaString.tab"

/***** Protótipos das funções encapuladas no módulo *****/

   static tpElementoTabela * ProcurarIdString( long idString ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TBS Obter o tamanho de um string
*  ****/

   int TBS_ObterTamanhoString( long idString )
   {

      tpElementoTabela * pElementoTabela ;

      /* Controlar parâmetros */
      #ifdef _DEBUG

         assert( idString >= 1 ) ;
      #endif

      /* Recuperar o descritor do string na tabela */

         pElementoTabela = ProcurarIdString( idString ) ;
         if ( pElementoTabela != NULL )
         {
            return pElementoTabela->tamString ;
         } /* if */

         return TBS_CondRetNaoExiste ;

   } /* Fim função: TBS Obter o tamanho de um string */

/***************************************************************************
*
*  Função: TBS Obter um string contido na tabela
*  ****/

   TBS_tpCondRet TBS_ObterString( long   idString  ,
                                  int    dimString ,
                                  char * pString )
   {

      tpElementoTabela * pElementoTabela ;

      TBS_tpCondRet CondRet = TBS_CondRetOK ;

      char * pStringTabela = NULL ;

      /* Controlar parâmetros de obter string */

         assert(  idString  >= 0 ) ;
         assert(( dimString >  TBS_MIN_LENGTH ) && ( dimString <= TBS_MAX_LENGTH )) ;
         assert(  pString   != NULL ) ;

      /* Obter ponteiro para o string na tabela */

         pElementoTabela      = ProcurarIdString( idString ) ;

         if ( pElementoTabela == NULL )
         {
            CondRet = TBS_CondRetNaoExiste ;
            pElementoTabela = ProcurarIdString( ID_NAO_ENCONTROU ) ;
         } /* if */

      /* Tratar erro de formação da tabela */

         if ( pElementoTabela == NULL )
         {

            strcpy( pString , STRING_ERRO ) ;
            return TBS_CondRetErroTabela ;

         } /* fim ativa: Tratar erro de formação da tabela */

      /* Controlar tamanho no buffer receptor */

         dimString -- ; /* assegurar espaço para o 0 final */

         if ( dimString >= pElementoTabela->tamString )
         {
            dimString = pElementoTabela->tamString ;
         } else
         {
            CondRet   = TBS_CondRetTruncado ;
         } /* if */

      /* Copiar string para o destino */

         pStringTabela = vtpStringoes[ pElementoTabela->inxSubTabela ]
                                   + pElementoTabela->inxOrigemString ;

         memcpy( pString , pStringTabela , dimString ) ;
         pString[ dimString ] = 0 ;

      return CondRet ;

   } /* Fim função: TBS Obter um string contido na tabela */

/***************************************************************************
*
*  Função: TBS Teste - deturpar idString
*  ****/

   void TBS_TesteDeturparIdString( int idString , int inxElemento )
   {

      assert(( 0 <= inxElemento ) && ( inxElemento < DIM_TABELA_STRING )) ;

      vtTabelaPesquisa[ inxElemento ].idString = idString ;

   } /* Fim função: TBS Teste - deturpar idString */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TBS Procurar string na tabela
*
*  $ED Descrição da função
*     Ver "TabelaString.tabstr" para detalhes quanto à organização da tabela.
*
*  $EP Parâmetros
*     idString - identificação do string a procurar
*
*  $FV Valor retornado
*     ponteiro para o elemento da tabela que contém o string procurado.
*     Será NULL se não encontrado.
*
***********************************************************************/

   tpElementoTabela * ProcurarIdString( long idString )
   {

      int Inf  ,
          Sup  ,
          Meio  ;

      tpElementoTabela * pElem = NULL ;

      Inf = 0 ;
      Sup = DIM_TABELA_STRING ;

      while ( Inf <= Sup )
      {
         Meio  = ( Inf + Sup ) / 2 ;
         pElem = &( vtTabelaPesquisa[ Meio ] );
         if ( pElem->idString == idString )
         {
            return pElem ;
         } /* if */
         if ( idString < pElem->idString )
         {
            Sup = Meio - 1 ;
         } else {
            Inf = Meio + 1 ;
         } /* if */

      } /* while */

      return NULL ;

   } /* Fim função: TBS Procurar string na tabela */

/********** Fim do módulo de implementação: TBS  Tabela de strings **********/

