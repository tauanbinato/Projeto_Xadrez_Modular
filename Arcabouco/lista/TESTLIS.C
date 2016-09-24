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
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/
#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"
#include	"Pessoa.h"

static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char PROCURA_VALOR_LISTA_CMD [ ] = "=procuravalor"   ;
static const char OBTER_VALOR_INICIAIS_CMD[ ] = "=obteminiciais"  ;
static const char OBTER_VALOR_NOME_CMD	  [ ] = "=obtemnome"      ;
static const char CRIAR_ESTR_CMD		  [ ] = "=criareestru"    ;
static const char PREENCHE_ESTR_CMD		  [ ] = "=preestrutura"   ;
static const char EXIBE_ELEM_CMD		  [ ] = "=exibeelemento"  ;
static const char INSERE_ORD_CMD		  [ ] = "=insereord"      ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"  ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"   ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"    ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;
Infonome	*vtStructs[DIM_VT_LISTA];

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

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
*     =criarlista                   inxLista									            ok
*     =destruirlista                inxLista	                                            ok
*     =esvaziarlista                inxLista												ok
*     =irinicio                     inxLista												ok
*     =irfinal                      inxLista												ok										
*     =insereord                    inxLista  inxStruct            CondRetEsp               ok
*     =inselemantes                 inxLista  inxStruct            CondRetEsp				ok		
*     =inselemapos                  inxLista  inxStruct            CondRetEsp               ok
*     =obtervalorelem               inxLista  inxStruct            CondretPonteiro          ok
*     =excluirelem                  inxLista                       CondRetEsp               ok
*     =avancarelem                  inxLista  numElem              CondRetEsp               ok
*     =procuravalor                 inxLista  inxStruct            CondRetEsp				ok
*     =exibeelemento                inxLista                       CondRetEsp					
*     =criareestru                  inxStruct                      CondRetEsp               ok
*     =preestrutura                 inxStruct string1   string2    CondRetEsp               ok
*     =obteminiciais                inxStruct string1              CondRetEsp               ok
*     =obtemnome					inxStruct string1			   CondRetEsp               ok
*
*
***********************************************************************/
 
   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
		  inxStruct = -1;

      TST_tpCondRet CondRet ;
	  PES_tpCondRet CondRet_PES;
	  LIS_tpCondRet CondRet_LIS;

      char   StringDado[  DIM_VALOR ] ;
	  char	 StringDado_2[ DIM_VALOR ];
	  char * pDado ;
	  char * pDado_2;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;
	  StringDado_2[ 0 ] = 0;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

		 //INICIO TESTES PESSOA

	  /* Testar criarErstrutura */												

		 else if ( strcmp( ComandoTeste , CRIAR_ESTR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,&inxStruct, &CondRetEsp ) ;
		
			if ( ( numLidos != 2 )
              || ( ! ValidarInxStruct( inxStruct , VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
		
            CondRet_PES = PES_Criar_Estrutura(&vtStructs[inxStruct]);
			printf("craindo estrutura: %d\n", vtStructs[inxStruct]);
            return TST_CompararInt( CondRetEsp , CondRet_PES ,
                     "Condicao de retorno errada ao tentar criar uma estrutura.") ;

		 }
		 /* fim ativa: teste criar estrutura */

		 /* Testar Obter valor iniciais */

		 else if ( strcmp( ComandoTeste , OBTER_VALOR_INICIAIS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,&inxStruct,StringDado, &CondRetEsp ) ;
			if ( ( numLidos != 3 )
              || ( ! ValidarInxStruct( inxStruct , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = ( char * ) malloc( (strlen( StringDado ) + 1 )*sizeof(char)) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            CondRet_PES = PES_ObterValorIniciais( &pDado, vtStructs[inxStruct] );

            if(!strcmp(pDado, StringDado)){
				CondRet_PES = PES_CondRetOK;
			} else {
				CondRet_PES = PES_CondRetStringDiferente;
			}

            if ( CondRet_PES != PES_CondRetOK )
            {
               free( pDado ) ;
            } /* if */


            return TST_CompararInt( CondRetEsp , CondRet_PES ,
                     "Condicao de retorno errada ao tentar obter valor das iniciais de uma estrutura.") ;

		 }

		 /* fim ativa: teste Obter Valor Iniciais */

		 /* Testar Obter Valor Nome */	

		  else if ( strcmp( ComandoTeste , OBTER_VALOR_NOME_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "isi" ,&inxStruct,StringDado, &CondRetEsp ) ;
			if ( ( numLidos != 3 )
              || ( ! ValidarInxStruct( inxStruct , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = ( char * ) malloc( (strlen( StringDado ) + 1)*sizeof(char) ) ;

            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            CondRet_PES = PES_ObterValorNome( &pDado, vtStructs[inxStruct] );

			if(!strcmp(pDado, StringDado)){
				CondRet_PES = PES_CondRetOK;
			} else {
				CondRet_PES = PES_CondRetStringDiferente;
			}

            if ( CondRet_PES != PES_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet_PES ,
                     "Condicao de retorno errada ao tentar obter valor das iniciais de uma estrutura.") ;

		 }

		 /* fim ativa: teste Obter Valor Nome */

	     /* Testar preencherErstrutura */												

		 else if ( strcmp( ComandoTeste , PREENCHE_ESTR_CMD ) == 0 )
         {

			int condRet_CriarEstrutura;

            numLidos = LER_LerParametros( "issi" ,&inxStruct,
                       StringDado, StringDado_2 , &CondRetEsp ) ;

			if ( ( numLidos != 4 )
              || ( ! ValidarInxStruct( inxStruct , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

			pDado_2 = ( char * ) malloc( strlen( StringDado_2 ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;
            strcpy( pDado_2 , StringDado_2 ) ;

			//condRet_CriarEstrutura = PES_Criar_Estrutura(&vtStructs[inxStruct]);

            CondRet_PES = PES_preencher_estrutura(&vtStructs[ inxStruct ] , pDado , pDado_2) ;

            if ( CondRet_PES != PES_CondRetOK )
            {
               free( pDado ) ;
			   free(pDado_2) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet_PES ,
                     "Condicao de retorno errada ao tentar preencher a estrutura.") ;

		 }
		 /* fim ativa: teste preencher estrutura */

		 //*FIM TESTES PESSOA

         /* Testar Procurar Valor */	

		 else if ( strcmp( ComandoTeste , PROCURA_VALOR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,&inxLista, &inxStruct, &CondRetEsp ) ;
			
			if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) || ( ! ValidarInxStruct( inxStruct , NAO_VAZIO ))  )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet_LIS = LIS_ProcurarValor( vtListas[inxLista] , vtStructs[inxStruct]);

            return TST_CompararInt( CondRetEsp , CondRet_LIS ,
                     "Condicao de retorno errada ao tentar procurar valor na lista.") ;
		 }

		 /* fim ativa: procurar valor */

	     /* Testar InsereOrdenado */

		 else if ( strcmp( ComandoTeste , INSERE_ORD_CMD ) == 0 )
         {

			numLidos = LER_LerParametros( "iii" ,
                       &inxLista ,&inxStruct, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) || ( ! ValidarInxStruct( inxStruct , NAO_VAZIO ))  )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet_LIS = LIS_insereOrdenado(vtListas[inxLista], vtStructs[inxStruct]);

            return TST_CompararInt( CondRetEsp , CondRet_LIS ,
                     "Condicao de retorno errada ao tentar inserir ordenando.") ;
		 }

		 /* Testar Exibe */

		 else if ( strcmp( ComandoTeste , EXIBE_ELEM_CMD ) == 0 )
         {

			numLidos = LER_LerParametros( "ii" ,
                       &inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet_LIS = ExibeElemLista(vtListas[inxLista]);

            return TST_CompararInt( CondRetEsp , CondRet_LIS ,
                     "Condicao de retorno errada ao tentar exibir lista.") ;
		 }


      /* Testar CriarLista */                                                                  

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

			printf("inserindo estrutura: %d\n", vtStructs[inxStruct]);

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtListas[ inxLista ] =
                 LIS_CriarLista( DestruirValor ) ;

            return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista lista */                                                         

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

			if(vtListas[inxLista] != NULL) return TST_CondRetErro;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

		 /* Testar Exibir Valor */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxLista , &inxStruct , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) || ( ! ValidarInxStruct( inxStruct , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet_LIS = LIS_InserirElementoAntes( vtListas[ inxLista ] , vtStructs[inxStruct] ) ;    

            return TST_CompararInt( CondRetEsp , CondRet_LIS ,
                     "Condicao de retorno errada ao inserir antes."                   ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxLista , &inxStruct , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) || ( ! ValidarInxStruct( inxStruct , NAO_VAZIO ))  )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet_LIS = LIS_InserirElementoAntes( vtListas[ inxLista ] , vtStructs[inxStruct] ) ;

            return TST_CompararInt( CondRetEsp , CondRet_LIS ,
                     "Condicao de retorno errada ao inserir antes."                   ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxLista , &inxStruct , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) || ( ! ValidarInxStruct( inxStruct , NAO_VAZIO ))  )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet_LIS = LIS_InserirElementoApos( vtListas[ inxLista ] , vtStructs[inxStruct] ) ;

            return TST_CompararInt( CondRetEsp , CondRet_LIS ,
                     "Condicao de retorno errada ao inserir apos."                   ) ;

         } /* fim ativa: Testar inserir elemento apos */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {	
			char **ppDado_Nome;
			Infonome * pDado;
		
            numLidos = LER_LerParametros( "iisi" , &inxLista,&inxStruct , StringDado , &ValEsp ) ;

			ppDado_Nome = ( char ** ) malloc( strlen( (StringDado ) + 1)*sizeof(char) ) ;
			

            if ( ( numLidos != 4 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			
			if( ! ValidarInxStruct( inxStruct , NAO_VAZIO )){
				return TST_CompararPonteiroNulo( 0 , vtStructs[inxStruct] ,
                         "Valor não deveria existir." ) ;
			}
			
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */
			
            CondRet_LIS =  LIS_ObterValor( vtListas[ inxLista ] , &pDado );
		    
			PES_ObterValorNome(ppDado_Nome , vtStructs[inxStruct]);

		    if (TST_CompararString( StringDado , *ppDado_Nome , "Valor do elemento errado." ) == TST_CondOK){

				TST_CompararString( StringDado , *ppDado_Nome , "Valor do elemento errado." );
			}

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , vtStructs[inxStruct] ,
                         "Valor não deveria existir." ) ;
            } /* if */
			
            if ( vtStructs[inxStruct] == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , vtStructs[inxStruct] ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */
			
			return TST_CompararInt( (long)vtStructs[inxStruct] ,
                                  (long)pDado   ,
                                  "ponteiros diferem."       ) ;

            //return TST_CompararString( StringDado , *ppDado_Nome , "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrInicioLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrFinalLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avançar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avançar elemento */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */

   /***********************************************************************
*
*  $FC Função: TLIS -Validar indice de estrutura
*
***********************************************************************/

   int ValidarInxStruct( int inxStruct , int Modo )
   {

      if ( ( inxStruct <  0 )
        || ( inxStruct >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtStructs[ inxStruct ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtStructs[ inxStruct ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */


/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

