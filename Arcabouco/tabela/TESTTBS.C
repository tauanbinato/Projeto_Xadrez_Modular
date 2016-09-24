/***************************************************************************
*  $MCI Módulo de implementação: TTBS Teste de tabela de string
*
*  Arquivo gerado:              TESTTBS.c
*  Letras identificadoras:      TTBS
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

#include    <stdio.h>
#include    <string.h>
#include    <assert.h>

#include    "tst_espc.h"
#include    "generico.h"
#include    "lerparm.h"

#include    "TabStr.h"

#define  DIM_STRING  250


const char CMD_OBTER_STRING[ ]      = "=ObterString" ;
const char CMD_OBTER_TAMANHO[ ]     = "=ObterTamTab" ;
const char CMD_DETURPAR_STRING[ ]   = "=DeturparId" ;
const char CMD_OBTER_TAM_REAL[ ]    = "=ObterTamReal" ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TTBS Testar tabela de strings
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      char StringDado[   DIM_STRING ] ;
      char StringObtido[ DIM_STRING ] ;

      TST_tpCondRet CondRet = TST_CondRetNaoExecutou ;

      int numLidos          = -1 ;
      int tamDado           = -1 ;
      int idString          = -1 ;
      int CondRetEsperada   = -1 ;
      int CondRetObtida     = -1 ;

      char * pFim = NULL ;

      int tamEsperado = -1 ;

      int tamObtido = -2 ;

      int inxElemento ;

      StringDado[ 0 ] = 0 ;
      memset( StringObtido , '+' , DIM_STRING ) ;

      /* Obter string */

         if ( strcmp( ComandoTeste , CMD_OBTER_STRING ) == 0 )
         {

            numLidos = LER_LerParametros( "iisi" ,
                               &idString  , &tamDado,
                               StringDado , &CondRetEsperada ) ;

            if ( ( numLidos != 4 )
              || ( idString  < 0 ))
            {
               return TST_CondRetParm ;
            } /* if */

            pFim = strchr( StringDado , '%' ) ;
            if ( pFim != NULL )
            {
               *pFim = 0 ;
            } /* if */

            if ( tamDado <= TBS_MIN_LENGTH )
            {
               tamDado = TBS_MIN_LENGTH + 1 ;
            } /* if */

            if ( tamDado > TBS_MAX_LENGTH )
            {
               tamDado = TBS_MAX_LENGTH ;
            } /* if */

            CondRetObtida = TBS_ObterString( idString  , tamDado , StringObtido ) ;

            CondRet = TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                "Condição de retorno errada." ) ;

            if ( CondRet != TST_CondRetOK )
            {
               return CondRet ;
            } /* if */

            return TST_CompararString( StringDado , StringObtido ,
                            "Strings não são iguais" ) ;

         } /* fim ativa: Obter string */

      /* Obter tamanho real do string */

         if ( strcmp( ComandoTeste , CMD_OBTER_TAM_REAL ) == 0 )
         {

            numLidos = LER_LerParametros( "iiii" ,
                               &idString    , &tamDado,
                               &tamEsperado , &CondRetEsperada ) ;

            if ( ( numLidos != 4 )
              || ( idString  < 0 ))
            {
               return TST_CondRetParm ;
            } /* if */

            pFim = strchr( StringDado , '%' ) ;
            if ( pFim != NULL )
            {
               *pFim = 0 ;
            } /* if */

            if ( tamDado <= TBS_MIN_LENGTH )
            {
               tamDado = TBS_MIN_LENGTH + 1 ;
            } /* if */

            if ( tamDado > TBS_MAX_LENGTH )
            {
               tamDado = TBS_MAX_LENGTH ;
            } /* if */

            CondRetObtida = TBS_ObterString( idString  , tamDado , StringObtido ) ;

            CondRet = TST_CompararInt( CondRetEsperada , CondRetObtida ,
                                "Condição de retorno errada." ) ;

            if ( CondRet != TST_CondRetOK )
            {
               return CondRet ;
            } /* if */

            return TST_CompararInt( tamEsperado , strlen( StringObtido ) ,
                                "Tamanho real não está correto." ) ;

         } /* fim ativa: Obter tamanho real do string */

      /* Obter tamanho do string */

         if ( strcmp( ComandoTeste , CMD_OBTER_TAMANHO ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &idString , &tamDado ) ;

            if ( ( numLidos != 2 )
              || ( idString  < 0 ))
            {
               return TST_CondRetParm ;
            } /* if */

            tamObtido = TBS_ObterTamanhoString( idString ) ;


            return TST_CompararInt( tamDado , tamObtido ,
                            "Tamanhos não são iguais" ) ;

         } /* fim ativa: Obter tamanho do string */

      /* Deturpar o idString de elemento da tabela */

         if ( strcmp( ComandoTeste , CMD_DETURPAR_STRING ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxElemento , &idString ) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            TBS_TesteDeturparIdString( idString , inxElemento ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Deturpar o idString de elemento da tabela */

      return CondRet ;

   } /* Fim função: TTBS Testar tabela de strings */

/********** Fim do módulo de implementação: TTBS Teste de tabela de string **********/

