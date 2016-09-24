/***************************************************************************
*  $MCI Módulo de implementação: GTD  Gerar tabela de definição
*
*  Arquivo gerado:              GERATBDF.c
*  Letras identificadoras:      GTD
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
*  $ED Descrição do módulo
*     Gera a tabela de definição para acesso à tabela de strings residentes.
*     Uma tabela de definição é formada por uma lista de declarações de
*     constantes, cada uma correspondendo à chave de acesso ao respectivo
*     string na tabela de strings. Através dessa chave as funções
*     TBS_ObterTamanhoString e TBS_ObterString definidas no módulo
*     TABSTR acessam os strings na tabela.
*
*     Para cada tabela de especificação de strings é gerada uma tabela
*     de definição. Desta forma cada módulo especificará os seus strings
*     específicos e disporá da tabela de definição correspondente.
*     Desta forma cada módulo depende somente dos strings que efetivamente
*     usa.
*
*     Esta ferramenta é parte do conjunto de ferramentas que visa agilizar
*     a internacionalização de programas. Os outros dois componentes
*     desse conjunto são:
*
*     GERATAB  - Programa gerador de tabelas de definição: gera as
*                constantes simbólicas a serem utilizados nos módulos
*                de implementação
*
*     TABSTR   - módulo de acesso à tabela de strings.
*
*  $EIU Interface com o usuário pessoa
*     Estão definidos os parâmetros de linha de comando:
*
*      /E<nome arquivo especificação>   obrigatório
*         este arquivo contém a lista de especificações de strings.
*
*      /D<nome arquivo definição>     opcional
*         este será o arquivo gerado. Conterá a tabela de definição
*         das chaves de acesso aos strings especificados.
*         O nome default do arquivo tabela é   .tabdef
*
*      /h /H /? geram o help do comando   GeraTab
*
*     Os arquivos de especificação de strings contém zero ou mais linhas.
*     Cada linha pode ser:
*
*       em branco             - é ignorada
*       // na primeira coluna - é comentário ignorado
*       offset de identificação do string
*       especificação de string
*
*     Uma linha de especificação de string tem o formato:
*
*       NomeString    idString   String
*
*          NomeString - é um nome satisfazendo a sintaxe C para uma constante
*                       simbólica. Este nome será o identificador simbólico
*                       do string.
*
*          idString   - é o valor da constante simbólica. Os strings e
*                       os idString devem formar uma relação um para um.
*                       Para impedir a ocorrência de idString iguais
*                       em diferentes Arquivos String, sugere-se a adoção
*                       do seguinte padrão de programação:
*
*                       - para cada módulo existirá no máximo um Arquivo
*                         String. Caso o módulo não defina string, não
*                         será necessário criar um Arquivo String
*                       - para cada módulo é definido um número identificador
*                         único. A diferença de números identificadores
*                         de módulos consecutivos deve ser sempre maior do
*                         que o número de strings definidos no módulo
*                         de menor identificador. Sugere-se dar incrementos
*                         de pelo menos 50.
*                       - o offset de número identificador é definido no
*                         arquivo de especificação de strings, ver
*                         declarador <Offset>
*                       - os idStrings são gerados consecutivamente a partir
*                         do número identificador do módulo
*
*           String    - é um string no formato C. Valem todos os escapes
*                       padrão de C.
*
*  $EIM Interface com outros módulos
*     O arquivo tabela de definição gerado possui uma lista de declarações de
*     constantes inteiras.
*
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define DIM_ID_PARM              2
#define DIM_BUFFER             512
#define DIM_NOME_ARQUIVO       512
#define DIM_NOME_STRING         34
#define DIM_STRING             256
#define DIM_STRINGAO          1023

#define LIMPA_FIM                1
#define LIMPA_INIC               2
#define CHARS_FIM                " \r\n\t"
#define ID_COMENTARIO            "//"

#define SEPARADOR_EXTENSAO       '.'
#define SEPARADOR_DIRETORIO      '\\'

const char ExtArquivoEspec[ ]  = ".espstr" ;
const char ExtArquivoTabela[ ] = ".inc" ;

const char CMD_OFFSET[ ]       = "<Offset>" ;

const char idParmArquivoEspec[ ] = "/E" ;
const char idParmTabelaDef[ ]    = "/T" ;
const char idParmAuxilio1[ ]     = "/h" ;
const char idParmAuxilio2[ ]     = "/H" ;
const char idParmAuxilio3[ ]     = "/?" ;

/***********************************************************************
*
*  $TC Tipo de dados: GT Códigos de retorno de funções
*
*
***********************************************************************/

   typedef enum {

         CondRetOK ,
               /* Função executou correto */

         CondRetFimArq ,
               /* Fim de arquivo de leitura */

         CondRetOverflow ,
               /* Linha lida é longa demais para o buffer */

         CondRetErro
               /* Erro de leitura de arquivo */

   } tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: GT Códigos de término de processamento
*
*
***********************************************************************/

   typedef enum {

         CodigoOK ,
               /* Executou corretamente o programa */

         CodigoAuxilio ,
               /* Foi solicitado auxílio */

         CodigoArquivoNaoAbre ,
               /* Arquivo não abre */

         CodigoNaoArquivoLista ,
               /* Arquivo lista de arquivos não foi definido */

         CodigoParametroDuplo ,
               /* Parâmetro duplicado */

         CodigoErroProcessamento ,
               /* Erro de processamento */

         CodigoErroParametro
               /* Parâmetro errado */

   } tpCodigoErro ; ;

/*****  Dados encapsulados no módulo  *****/

      static char NomeArquivoEspec[ DIM_BUFFER ] ;
            /* Nome do arquivo de especificação lido */

      static char NomeArquivoTabela[ DIM_BUFFER ] ;
            /* Nome do arquivo tabela de definição gerado */

      static char NomeArquivoCodigo[ DIM_BUFFER ] ;
            /* Nome de código do arquivo tabela de definição */

      static int ContaEspecString ;
            /* Conta especificações de string a gerar */

      static int ContaErros    = 0 ;
            /* Conta erros ao processar GERATBDF */

/***** Protótipos das funções encapuladas no módulo *****/

   static void GerarTabelaDefinicao( char * NomeArquivoEspec ,
                                     char * NomeArquivoTabela ) ;

   static tpCondRet LerTrimmed( FILE * pArqLe    ,
                                char * pBuffer   ,
                                int    dimBuffer ,
                                int    Modo       ) ;

   static int ObterInxExtensao( char * NomeArquivo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: GTD Processar linha de comando de gera tabela de definição
*
***********************************************************************/

   int main( int numParametros , char ** vtParametros  )
   {

      tpCodigoErro CodigoErro = CodigoOK ;

      char ParametroCorr[ DIM_BUFFER ] ;

      int i ;
      int numParmEspec  = 0 ;
      int numParmTabela = 0 ;

      int tamNome = 0 ;

      /* Identificar o programa gerador de tabela de definição */

         printf( "\nGeraTbdf - Gerar a tabela de definição" ) ;
         printf( "\n           LES/DI/PUC-Rio, versao 1, 05/12/2004\n" ) ;

      /* Processar todos os parâmetros de GERATBDF */

         /* Processar parâmetros do comando GERATBDF */

            ContaEspecString    = 0 ;
            ContaErros          = 0 ;
            numParmEspec        = 0 ;
            numParmTabela       = 0 ;

            NomeArquivoEspec[  0 ] = 0 ;
            NomeArquivoTabela[ 0 ] = 0 ;
            ParametroCorr[     0 ] = 0 ;

            for ( i = 1 ; i < numParametros ; i ++ ) {

            /* Obter parâmetro corrente de GERATBDF */

               strcpy( ParametroCorr , vtParametros[ i ] ) ;

            /* Processar parâmetro arquivo especificação de string */

               if ( memcmp( ParametroCorr , idParmArquivoEspec , DIM_ID_PARM ) == 0 )
               {

                  if ( numParmEspec > 0 )
                  {
                     CodigoErro = CodigoParametroDuplo ;
                     printf( "\n>>> Arquivo especificação %s definido multiplas vezes." , ParametroCorr ) ;
                     ContaErros ++ ;

                  } else
                  {
                     numParmEspec ++ ;
                     strcpy( NomeArquivoEspec , & ParametroCorr[ DIM_ID_PARM ] ) ;

                     if ( ObterInxExtensao( NomeArquivoEspec ) == - 1 )
                     {
                        strcat( NomeArquivoEspec , ExtArquivoEspec ) ;
                     } /* if */

                  } /* if */

               } /* fim ativa: Processar parâmetro arquivo especificação de string */

            /* Processar parâmetro tabela de definição a ser gerada */

               else if ( memcmp( ParametroCorr , idParmTabelaDef , DIM_ID_PARM ) == 0 )
               {

                  if ( numParmTabela > 0 )
                  {
                     CodigoErro = CodigoParametroDuplo ;
                     printf( "\n>>> Arquivo tabela %s definido multiplas vezes." , ParametroCorr ) ;
                     ContaErros ++ ;

                  } else
                  {
                     numParmTabela ++ ;
                     strcpy( NomeArquivoTabela , & ParametroCorr[ DIM_ID_PARM ] ) ;

                     if ( ObterInxExtensao( NomeArquivoTabela ) == - 1 )
                     {
                        strcat( NomeArquivoTabela , ExtArquivoTabela ) ;
                     } /* if */
                  } /* if */

               } /* fim ativa: Processar parâmetro tabela de definição a ser gerada */

            /* Processar parâmetro auxílio de GERATBDF */

               else if ( ( memcmp( ParametroCorr , idParmAuxilio1 , DIM_ID_PARM ) == 0 )
                      || ( memcmp( ParametroCorr , idParmAuxilio2 , DIM_ID_PARM ) == 0 )
                      || ( memcmp( ParametroCorr , idParmAuxilio3 , DIM_ID_PARM ) == 0 )
                      || ( ParametroCorr[ 0 ] == '?' ))
               {

                  CodigoErro = CodigoAuxilio ;

               } /* fim ativa: Processar parâmetro auxílio de GERATBDF */

            /* Tratar parâmetro errado para GERATBDF */

               else
               {

                  printf( "\n>>> Parametro errado: %s" , ParametroCorr ) ;
                  CodigoErro = CodigoErroParametro ;
                  ContaErros ++ ;

               } /* fim ativa: Tratar parâmetro errado para GERATBDF */

            } /* fim repete: Processar parâmetros do comando GERATBDF */

         /* Definir o nome de codigo do arquivo */

            strcpy( NomeArquivoCodigo, NomeArquivoEspec ) ;
            NomeArquivoCodigo[ ObterInxExtensao( NomeArquivoEspec ) ] = 0 ;

            tamNome = strlen( NomeArquivoCodigo ) ;
            for( i = tamNome - 1 ; i >= 0 ; i-- )
            {
               if ( NomeArquivoCodigo[ i ] == SEPARADOR_DIRETORIO )
               {
                  strcpy( &NomeArquivoCodigo[ 0 ] , &NomeArquivoCodigo[ i + 1 ] ) ;
                  break ;
               } /* if */
            } /* for */

         /* Verificar integridade de dados de GERATBDF */

            if ( numParmEspec == 0 )
            {
               CodigoErro = CodigoNaoArquivoLista ;
               printf( "\n>>> O arquivo especificacao de string nao foi definido." ) ;
               ContaErros ++ ;
            } /* if */

            if ( numParmTabela == 0 )
            {
               strcpy( NomeArquivoTabela, NomeArquivoEspec ) ;
               NomeArquivoTabela[ ObterInxExtensao( NomeArquivoEspec ) ] = 0 ;
               strcat( NomeArquivoTabela , ExtArquivoTabela ) ;
            } /* if */

         /* Listar mensagens de auxílo da linha de comando */

            if( CodigoErro != CodigoOK )
            {

               printf( "\n\nSintaxe da linha de comando: " ) ;
               printf( "\n geratbdf { /E<Arquivo Espec> | /T<Arquivo Tabela> | /h | /H | /? | ? }" ) ;
               printf( "\n" ) ;
               printf( "\n   <Arquivo Espec> E' o nome de um arquivo que contem as" ) ;
               printf( "\n         especificacoes dos strings." ) ;
               printf( "\n   <Arquivo Tabela> parametro opcional, e' o nome do arquivo" ) ;
               printf( "\n         tabela de de definicao a ser gerado." ) ;
               printf( "\n As extensoes default sao: " ) ;
               printf( "\n   espstr - para os arquivos contendo especificações de strings." ) ;
               printf( "\n   tabdef - para o arquivo tabela de definicao a ser gerado." ) ;
               printf( "\n Nao sendo fornecido o nome do arquivo a ser gerado, a tabela " ) ;
               printf( "\n sera gerada no arquivo <Arquivo Espec>.tabdef" ) ;
               printf( "\n" ) ;

               if ( CodigoErro != CodigoAuxilio )
               {
                  return 4 ;
               } /* if */

               return 0 ;

            } /* fim ativa: Listar mensagens de auxílo da linha de comando */

      /* Gerar a tabela de definição identificada */

         GerarTabelaDefinicao( NomeArquivoEspec , NomeArquivoTabela ) ;

      /* Terminar GERATBDF */

         if ( ContaErros > 0 )
         {
            CodigoErro = CodigoErroProcessamento ;
            printf( "\n\n>>> Foram encontrados %i erros.\n\n " ,
            ContaErros ) ;
            return 4 ;
         } /* if */

         printf( "\n\n" ) ;

         return 0 ;

   } /* Fim função: GTD Processar linha de comando de gera tabela de definição */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: GTD Gerar a tabela de definição
*
*  $ED Descrição da função
*     Gera a tabela de definição identificada nos parâmetros
*
***********************************************************************/

   void GerarTabelaDefinicao( char * NomeArquivoEspec ,
                              char * NomeArquivoTabela )
   {

      FILE * pArquivoEspec  = NULL ;
      FILE * pArquivoTabela = NULL ;

      tpCondRet CondRet = CondRetErro ;

      char Buffer[     DIM_BUFFER ] ;
      char StringLido[ DIM_BUFFER ] ;

      long idString = -1 ;
      long Offset   = -1 ;

      int numLidos  = -1 ;

      /* Abrir arquivos de GERATBDF */

         pArquivoEspec  = fopen( NomeArquivoEspec  , "r" ) ;
         if ( pArquivoEspec == NULL )
         {
            printf( "\nNao abriu o arquivo de especificacao: %s" ,
                    NomeArquivoEspec ) ;
            ContaErros ++ ;
         } /* if */

         pArquivoTabela = fopen( NomeArquivoTabela , "w" ) ;
         if ( pArquivoTabela == NULL )
         {
            printf( "\nNao abriu o arquivo tabela de definicao: %s" ,
                    NomeArquivoTabela ) ;
            ContaErros ++ ;
         } /* if */

      /* Gera o texto da tabela de definição */

         if ( ContaErros == 0 )
         {

            /* Gerar cabeçalho da tabela de definição */

               fprintf( pArquivoTabela ,
                          "#ifndef _%s_str" , NomeArquivoCodigo ) ;
               fprintf( pArquivoTabela ,
                        "\n#define _%s_str" , NomeArquivoCodigo ) ;
               fprintf( pArquivoTabela ,
                        "\n" ) ;
               fprintf( pArquivoTabela ,
                        "\n/* !!!!!!!!!! Aquivo gerado! Nao o edite! !!!!!!!!!! */" ) ;
               fprintf( pArquivoTabela ,
                        "\n" ) ;
               fprintf( pArquivoTabela ,
                        "\n/****************************************************************************" ) ;
               fprintf( pArquivoTabela ,
                        "\n*" ) ;
               fprintf( pArquivoTabela ,
                        "\n* $AT Tabela de definição de chaves de acesso a strings gerada" ) ;
               fprintf( pArquivoTabela ,
                        "\n*" ) ;
               fprintf( pArquivoTabela ,
                        "\n* Arquivo gerado: %s" , NomeArquivoTabela ) ;
               fprintf( pArquivoTabela ,
                        "\n*" ) ;
               fprintf( pArquivoTabela ,
                        "\n* Projeto: INF 1301/1628 Exemplos" ) ;
               fprintf( pArquivoTabela ,
                        "\n* Gestor:  LES/DI/PUC-Rio" ) ;
               fprintf( pArquivoTabela ,
                        "\n*" ) ;
               fprintf( pArquivoTabela ,
                        "\n* Arquivo de especificação de strings: %s" , NomeArquivoEspec ) ;
               fprintf( pArquivoTabela ,
                        "\n*" ) ;
               fprintf( pArquivoTabela ,
                        "\n***************************************************************************/" ) ;
               fprintf( pArquivoTabela ,
                        "\n" ) ;

            /* Obter offset das definições */

               CondRet = LerTrimmed( pArquivoEspec , Buffer , DIM_BUFFER - 1 ,
                                     LIMPA_INIC | LIMPA_FIM ) ;

               if ( CondRet != CondRetOK )
               {
                  printf( "\nArquivo %s vazio" , NomeArquivoEspec ) ;
                  ContaErros ++ ;
               } else
               {
                  numLidos = sscanf( Buffer , " %s %li" , StringLido , &Offset ) ;
                  if ( ( numLidos != 2 )
                    || ( strcmp( StringLido , CMD_OFFSET ) != 0 ))
                  {
                     printf( "\nFaltou a definição de offset em %s" , NomeArquivoEspec ) ;
                     ContaErros ++ ;
                  } /* if */
               } /* if */

            /* Processar as especificações */

               if ( ContaErros == 0 )
               {

                  CondRet = LerTrimmed( pArquivoEspec , Buffer , DIM_BUFFER - 1 ,
                                        LIMPA_INIC | LIMPA_FIM ) ;

                  while ( CondRet == CondRetOK )
                  {
                     numLidos = sscanf( Buffer , " %s %li" , StringLido , &idString ) ;
                     if ( numLidos != 2 )
                     {
                        printf( "\nArquivo de especificação errado: %s" , Buffer ) ;
                        ContaErros ++ ;
                        break ;
                     } /* if */

                     fprintf( pArquivoTabela ,
                              "\n   const int %-20s = %5li ;" ,
                              StringLido , idString + Offset ) ;
                     CondRet = LerTrimmed( pArquivoEspec , Buffer , DIM_BUFFER - 1 ,
                                           LIMPA_INIC | LIMPA_FIM ) ;

                  } /* while */

               } /* fim ativa: Processar as especificações */

            /* Gerar término do arquivo */

               fprintf( pArquivoTabela ,
                        "\n" ) ;
               fprintf( pArquivoTabela ,
                        "\n#endif" ) ;
               fprintf( pArquivoTabela ,
                        "\n" ) ;
               fprintf( pArquivoTabela ,
                        "\n/* Fim tabela de definição gerada */" ) ;
               fprintf( pArquivoTabela ,
                        "\n" ) ;

         } /* fim ativa: Gera o texto da tabela de definição */

      /* Fechar arquivos de GERATBDF */

         if ( pArquivoEspec != NULL )
         {
            fclose( pArquivoEspec ) ;
         } /* if */

         if ( pArquivoTabela != NULL )
         {
            fclose( pArquivoTabela ) ;
         } /* if */

   } /* Fim função: GTD Gerar a tabela de definição */


/***********************************************************************
*
*  $FC Função: GT Ler eliminando brancos no início e no final
*
*  $ED Descrição da função
*     Lê uma linha, eliminando os caracteres "branco" no início e no final
*     Salta linhas de comentário
*     Linhas nulas após eliminação de brancos são saltadas
*
*  $EP Parâmetros
*     pArqLe     - ponteiro para descritor de arquivo de leitura
*     pBuffer    - ponteiro para a área de leitura
*     dimBuffer  - dimensão do buffer
*     Modo       - modo de limpeza, qualquer combinação ( OR ) de 0,1 ou 2
*                  das condições a seguir :
*                      LIMPA_INIC - limpa antes
*                      LIMPA_FIM  - limpa no final
*
*  $FV Valor retornado
*     CondRetOK     - leu um buffer válido
*
*     CondRetFimArq - encontrou fim de arquivo
*                     Buffer contém string nulo
*
*     CondRetErro   - erro permanente de leitura
*                     Buffer contém string nulo
*
***********************************************************************/

   tpCondRet LerTrimmed( FILE * pArqLe    ,
                         char * pBuffer   ,
                         int    dimBuffer ,
                         int    Modo       )
   {

      int Continua = 0 ;
      int i        = 0 ;

      int tamLinha ;

      /* Controlar final de arquivo */

         if ( feof( pArqLe ))
         {

            pBuffer[ 0 ] = 0 ;
            return CondRetFimArq ;

         } /* fim ativa: Controlar final de arquivo */

      /* Procurar linha não vazia */

         Continua = 1 ;

         while ( Continua ) {

         /* Ler linha de arquivo */

            pBuffer[ dimBuffer - 1 ] = '@' ;

            if ( fgets( pBuffer , dimBuffer , pArqLe ) == NULL )
            {
               pBuffer[ 0 ] = 0 ;
               if ( feof( pArqLe ))
               {
                  return CondRetFimArq ;
               } else {
                  return CondRetErro ;
               } /* if */
            } /* if */

            if ( pBuffer[ dimBuffer - 1 ] != '@' )
            {
               printf( "\n>>> Linha longa demais" ) ;
               ContaErros ++ ;
               return CondRetOverflow ;
            } /* if */

         /* Limpar a linha */

            /* Eliminar lixo no final */

               if ( Modo & LIMPA_FIM )
               {

                  tamLinha = ( int ) strlen( pBuffer ) ;
                  for( i = tamLinha - 1 ; i >= 0 ; i -- )
                  {
                     if ( strchr( CHARS_FIM , pBuffer[ i ] ) == NULL )
                     {
                        break ;
                     } /* if */
                  } /* for */

                  i++ ;
                  pBuffer[ i ] = 0 ;

               } /* fim ativa: Eliminar lixo no final */

            /* Eliminar lixo no início */

               if ( Modo & LIMPA_INIC )
               {

                  tamLinha = ( int ) strlen( pBuffer ) ;
                  for( i = 0 ; i < tamLinha ; i++ )
                  {
                     if ( pBuffer[ i ] != ' ' )
                     {
                        break ;
                     } /* if */
                  } /* for */

                  if ( i > 0 )
                  {
                     strcpy( pBuffer , pBuffer + i ) ;
                  } /* if */

               } /* fim ativa: Eliminar lixo no início */

         /* Determinar o que fazer com a linha */

            Continua = 0 ;

            if ( ( memcmp( pBuffer , ID_COMENTARIO , strlen( ID_COMENTARIO )) == 0 )
              || ( strlen( pBuffer ) == 0 ))
            {
               Continua = 1 ;
            } /* if */

         } /* fim repete: Procurar linha não vazia */

      return CondRetOK ;

   } /* Fim função: GT Ler eliminando brancos no início e no final */


/***********************************************************************
*
*  $FC Função: GT Obter índice do nome de extensão
*
*  $EP Parâmetros
*     NomeArquivo - nome do arquivo a examinar
*
*  $FV Valor retornado
*     Indice do caractere '.' separador do nome de extensão
*        será -1 caso o nome de extensão não exista
*
***********************************************************************/

   int ObterInxExtensao( char * NomeArquivo )
   {

      int Encontrou ,
          i ;

      Encontrou = -1 ;

      for( i = strlen( NomeArquivo ) - 1 ; i > 0  ; i -- )
      {
         if ( NomeArquivo[ i ] == SEPARADOR_EXTENSAO )
         {
            Encontrou = i ;
            break ;

         } else if ( NomeArquivo[ i ] == SEPARADOR_DIRETORIO )
         {
            break ;

         } /* if */
      } /* for */

      return Encontrou ;

   } /* Fim função: GT Obter índice do nome de extensão */

/********** Fim do módulo de implementação: GTD  Gerar tabela de definição **********/

