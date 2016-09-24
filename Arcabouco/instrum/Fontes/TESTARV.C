/***************************************************************************
*  $MCI Módulo de implementação: TARV Teste específico para o módulo árvore
*
*  Arquivo gerado:              TESTARV.C
*  Letras identificadoras:      TST
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: C:\LIXO\INSTRUM.BSW
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
*  $ED Descrição do módulo
*     Este mÇodulo contém as funções específicas para o teste de um módulo.
*     Mais especificamente, contém a função que interpreta os comandos de
*     teste que exercitarão as funções do módulo em teste.
*
*     Caso o módulo em teste requeira um contexto explícito,
*     este contexto deverá ser estabelecido no presente módulo.
*
*     Uma possível maneira é incluir comandos de teste que constróem
*     ou destóem o contexto.
*     Alterar as funções TST_InicializarTeste e TST_TerminarTeste
*     contidas no módulo TesteGen deve ser evitado para manter
*     a integridade do arcabouço ("framework") de teste.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "CEspDin.h"
#include    "lerparm.h"

#include    "arvore.h"

/* Tabela dos nomes dos comandos de teste específicos */

const char RESET_CMD     [ ] = "=resetarvore" ;
const char CRIAR_ARV_CMD [ ] = "=criar"       ;
const char INS_DIR_CMD   [ ] = "=insdir"      ;
const char INS_ESQ_CMD   [ ] = "=insesq"      ;
const char IR_PAI_CMD    [ ] = "=irpai"       ;
const char IR_ESQ_CMD    [ ] = "=iresq"       ;
const char IR_DIR_CMD    [ ] = "=irdir"       ;
const char OBTER_VAL_CMD [ ] = "=obter"       ;
const char DESTROI_CMD   [ ] = "=destruir"    ;

/* os comandos a seguir somente operam em modo _DEBUG */

const char VER_CABECA_CMD[ ] = "=verificarcabeca" ;
const char VER_ARVORE_CMD[ ] = "=verificararvore" ;
const char VER_MEMORIA_CMD[ ] = "=verificarmemoria" ;
const char DETURPAR_CMD[ ]   = "=deturpar" ;

int estaInicializado = 0 ;

#define DIM_VT_ARVORES  5

void * vtRefArvore[ DIM_VT_ARVORES ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int VerificarInx( int inxArvore ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TARV &Efetuar operações específicas
*
*  $ED Descrição da função
*     Comandos de teste específicos para testar o módulo árvore:
*
*     Podem ser criadas até 5 árvores simultaneamente
*     As árvores são conhecidas pelo seu índice de 0 a 4
*
*     =resetarvore
*
*     =criar   <inxArvore>  <Cond ret>
*                   - chama a função ARV_CriarArvore( )
*
*     =insdir  <inxArvore> <Char> <Cond ret>
*                   - chama a função ARV_InserirDireita( )
*                     Obs. notação: <Char>  é o valor do parâmetro
*                     que se encontra no comando de teste.
*
*     =insesq  <inxArvore> <Char> <Cond ret>
*                   - chama a função ARV_InserirEsquerda( )
*
*     =irpai   <inxArvore> <Cond ret>
*                   - chama a função ARV_IrPai( )
*
*     =iresq   <inxArvore> <Cond ret>
*                   - chama a função ARV_IrEsquerda( )
*
*     =irdir   <inxArvore> <Cond ret>
*                   - chama a função ARV_IrDireita( )
*
*     =obter   <inxArvore> <Char> <Cond ret>
*                   - chama a função ARV_ObterValorCorr( ) e compara
*                     o valor retornado com o valor <Char>
*
*     =destroi <inxArvore> <Cond ret>
*                   - chama a função ARV_DestruirArvore( )
*
*
*     Estes comandos somente podem ser executados se o modulo tiver sido
*     compilado com _DEBUG ligado
*
*     =verificarcabeca       <inxArvore>
*
*     =verificararvore       <inxArvore>
*
*     =verificarmemoria
*
*     =deturpar              <inxArvore> < idCodigoDeturpa >
*
*
*
*     Ver explicação detalhada em TST_ESPC.H
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver condicoes de retorno em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      ARV_tpCondRet CondRetObtido   = ARV_CondRetOK ;
      ARV_tpCondRet CondRetEsperada = ARV_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

      int  NumLidos      = -1 ;
      int  inxArvore     = -1 ;

      int i ;

      TST_tpCondRet Ret ;

      #ifdef _DEBUG
         int  IntEsperado   = -1 ;
      #endif

      /* Tratar: inicializar contexto */

         if ( strcmp( ComandoTeste , RESET_CMD ) == 0 )
         {

            if ( estaInicializado )
            {
               for( i = 0 ; i < DIM_VT_ARVORES ; i++ )
               {
                  ARV_DestruirArvore( & ( vtRefArvore[ i ] )) ;
               } /* for */
            } /* if */

            for( i = 0 ; i < DIM_VT_ARVORES ; i++ )
            {
               vtRefArvore[ i ] = 0 ;
            } /* for */

            estaInicializado = 1 ;

         } /* fim ativa: Tratar: inicializar contexto */

      /* Testar ARV Criar árvore */

         else if ( strcmp( ComandoTeste , CRIAR_ARV_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_CriarArvore( &( vtRefArvore[ inxArvore ] )) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar árvore." );

         } /* fim ativa: Testar ARV Criar árvore */

      /* Testar ARV Adicionar filho à direita */

         else if ( strcmp( ComandoTeste , INS_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,
                               &inxArvore , &ValorDado , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirDireita( vtRefArvore[ inxArvore ] , ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir àa direita." );

         } /* fim ativa: Testar ARV Adicionar filho à direita */

      /* Testar ARV Adicionar filho à esquerda */

         else if ( strcmp( ComandoTeste , INS_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,
                               &inxArvore , &ValorDado , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirEsquerda( vtRefArvore[ inxArvore ] , ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir à esquerda." );

         } /* fim ativa: Testar ARV Adicionar filho à esquerda */

      /* Testar ARV Ir para nó pai */

         else if ( strcmp( ComandoTeste , IR_PAI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrPai( vtRefArvore[ inxArvore ] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para pai." );

         } /* fim ativa: Testar ARV Ir para nó pai */

      /* Testar ARV Ir para nó à esquerda */

         else if ( strcmp( ComandoTeste , IR_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoEsquerda( vtRefArvore[ inxArvore ] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para esquerda." );

         } /* fim ativa: Testar ARV Ir para nó à esquerda */

      /* Testar ARV Ir para nó à direita */

         else if ( strcmp( ComandoTeste , IR_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoDireita( vtRefArvore[ inxArvore ] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para direita." );

         } /* fim ativa: Testar ARV Ir para nó à direita */

      /* Testar ARV Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,
                               &inxArvore , &ValorEsperado , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_ObterValorCorr( vtRefArvore[ inxArvore ] , &ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "Conteúdo do nó está errado." ) ;

         } /* fim ativa: Testar ARV Obter valor corrente */

      /* Testar ARV Destruir árvore */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &inxArvore ) ;
            if ( ( NumLidos != 1 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            ARV_DestruirArvore( &( vtRefArvore[ inxArvore ] )) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ARV Destruir árvore */

      /* Testar verificador de cabeça */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_CABECA_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                                          &inxArvore ) ;
            if ( ( NumLidos != 1 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            return ARV_VerificarCabeca( vtRefArvore[ inxArvore ] ) ;

         } /* fim ativa: Testar verificador de cabeça */
      #endif

      /* Testar verificador de árvore */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_ARVORE_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                                          &inxArvore , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsperada ,
                             ARV_VerificarArvore( vtRefArvore[ inxArvore ] ) ,
                             "Retorno incorreto ao verificar árvore." ) ;

         } /* fim ativa: Testar verificador de árvore */
      #endif

      /* Deturpar uma árvore */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , DETURPAR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore , &IntEsperado ) ;

            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            ARV_Deturpar( vtRefArvore[ inxArvore ] , IntEsperado ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Deturpar uma árvore */
      #endif

      /* Verificar vazamento de memória */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_MEMORIA_CMD ) == 0 )
         {

            CED_ExibirTodosEspacos( CED_ExibirTodos ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Verificar vazamento de memória */
      #endif

      return TST_CondRetNaoConhec ;

   } /* Fim função: TARV &Efetuar operações específicas */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TARV -Verificar índice de árvore
*
*  $FV Valor retornado
*     0 - inxArvore não vale
*     0 - inxArvore vale
*
***********************************************************************/

   int VerificarInx( int inxArvore )
   {

      if ( ( inxArvore <   0 )
        || ( inxArvore >= DIM_VT_ARVORES ))
      {
         return 0 ;
      } /* if */

      return 1 ;

   } /* Fim função: TARV -Verificar índice de árvore */

/********** Fim do módulo de implementação: TARV Teste específico para o módulo árvore **********/

