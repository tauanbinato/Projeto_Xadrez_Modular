/***************************************************************************
*  $MCI Módulo de implementação: GTB Gerar a tabela de strings residentes
*
*  Arquivo gerado:              GeraTab.C
*  Letras identificadoras:      GTB
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
*     Gera a tabela de strings residente em memória. A geração se dá
*     a partir de um ou mais arquivos de especificação de strings
*     listados em um arquivo contendo a lista de arquivos a processar.
*
*     Os arquivos de especificação de strings servem a um duplo propósito:
*     gerar a tabela residente e gerar os arquivos definição contendo
*     a lista de constantes simbólicas a serem utilizadas nos módulos
*     de implementação nas chamadas à função de recuperação de strings.
*
*     Esta ferramenta é parte do conjunto de ferramentas que visa agilizar
*     a internacionalização de programas. Os outros dois componentes
*     desse conjunto são:
*
*     GERADEF  - Programa gerador de tabelas de definição: gera as
*                constantes simbólicas a serem utilizados nos módulos
*                de implementação
*
*     TABSTR   - módulo de acesso à tabela de strings.
*
*  $EIU Interface com o usuário pessoa
*     Estão definidos os parâmetros de linha de comando:
*
*      /L<nome arquivo lista>   obrigatório
*         este arquivo contém a lista de arquivos contendo definições
*         de strings e deverão figurar na tabela. A extenão default
*         desse arquivo é   .lista
*
*      /T<nome arquivo tabela>     opcional
*         este será o arquivo gerado. Conterá a tabela dos strings
*         extraídos dos arquivos enumerados no arquivo lista.
*         Caso este parâmetro não seja fornecido, o arquivo gerado
*         terá o mesmo nome do arquivo lista, sendo que é susbtituído
*         o nome de extensão pelo nome default da tabela.
*         O nome defaukt do arquivo tabela é   .tabstr
*
*      /h /H /? geram o help do comando   GeraTab
*
*     O arquivo lista contém zero ou mais linhas. Cada linha pode ser:
*
*       em branco             - é ignorada
*       // na primeira coluna - é comentário ignorado
*       <nome arquivo string> - identifica um arquivo contendo as
*                               especificações de strings a serem incluídos
*                               na tabela. A extensão default é  .defstr
*
*     Os arquivos string contém zero ou mais linhas. Cada linha pode ser:
*
*       em branco             - é ignorada
*       // na primeira coluna - é comentário ignorado
*       especificação de string
*
*     Uma linha de especificação de string tem o formato:
*
*       NomeString    idString   String
*
*          NomeString - é um nome satisfazendo a sintaxe C de uma constante
*                       simbólica. Este nome será o identificador simbólico
*                       do string. A ferramenta GeraDef produz um arquivo
*                       contendo a tabela de definição, contendo as
*                       declarações simbólicas dos strings. Essa ferramenta
*                       gera um arquivo definição para cada arquivo string
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
*                       - os idStrings são gerados consecutivamente a partir
*                         do número identificador do módulo
*
*           String    - é um string no formato C. Valem todos os escapes
*                       padrão de C.
*
*  $EIM Interface com outros módulos
*     O arquivo tabela gerado possui:
*
*     - um conjunto de declarações de tipo (struct) utilizados para
*       acessar os elementos da tabela.
*
*     - uma tabela de pesquisa a partir da qual se localiza o string procurado
*
*     - uma ou mais tabelas de armazenamento cada qual contendo um ou mais
*       strings. As tabelas de armazenamento são compostas por múltiplos
*       strings e são limitadas quanto ao comprimento
*
*     - um vetor de referência às tabelas de armazenamento.
*
*     Dado um idString procura-se o seu descritor na tabela de pesquisa.
*     Cada elemento da tabela de pesquisa indica o índice do elemento no
*     vetor de referências que contém as referências das tabelas de
*     armazenamento. O elemento da tabela de pesquisa contém ainda o offset
*     do string dentro da correspondente tabela de armazenamento.
*
*     Todas a variáveis são declaradas static e assume-se que serão utilizadas
*     como globais encapsuladas.
*
*     A tabela será incluída no módulo TabStr. Esse módulo possui funções
*     que permitem extrair os strings contidos na tabela.
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

const char ExtArquivoLista[ ]  = ".lista" ;
const char ExtArquivoString[ ] = ".espstr" ;
const char ExtArquivoTabela[ ] = ".tab" ;

char NomeArquivoTabelaDefault[ ] = "TabelaString.tab" ;
char NomeArquivoStringDefault[ ] = "DefinicaoDefault.espstr" ;
char NomeArquivoEstatisticas[ ]  = "TabelaString.txt" ;

const char CMD_OFFSET[ ]       = "<Offset>" ;

const char idParmArquivoLista[ ] = "/L" ;
const char idParmGerado[ ]       = "/T" ;
const char idParmAuxilio1[ ]     = "/h" ;
const char idParmAuxilio2[ ]     = "/H" ;
const char idParmAuxilio3[ ]     = "/?" ;

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
*  $TC Tipo de dados: GT Elemento da lista de arquivos
*
*
*  $ER Requisitos assegurados pelo tipo
*     Os elementos de lista devem ter os mesmos três primeiros
*     atributos pois está sendo simulada herança.
*
***********************************************************************/

   typedef struct tgElemArquivo {

         struct tgElemArquivo * pAnt ;
               /* Elemento antecessor */

         struct tgElemArquivo * pProx ;
               /* Elemento sucessor */

         char NomeArquivo[ DIM_NOME_ARQUIVO ] ;
               /* Nome do arquivo */

   } tpElemArquivo ;

/***********************************************************************
*
*  $TC Tipo de dados: GT Elemento da lista de strings
*
*
***********************************************************************/

   typedef struct tgElemString {

         struct tgElemString * pAnt ;
               /* Elemento antecessor na lista */

         struct tgElemString * pProx ;
               /* Elemento sucessor na lista */

         char   String[ DIM_STRING ] ;
               /* Valor do string */

         long   idString ;
               /* Identificador do string */

         int    tamString ;
               /* Tamanho do string */

         int    inxString ;
               /* Índice da tabela de armazenamento */

         int    offsetString ;
               /* Offset do string dentro da tabela de armazenamento */

   } tpElemString ;

/*****  Dados encapsulados no módulo  *****/

      static tpElemArquivo * pOrigemListaArquivos = NULL ;
            /* Âncora da lista de arquivos de definição */

      static tpElemString * pOrigemListaStrings = NULL ;
            /* Âncora da lista de strings */

      static char NomeArquivoTabela[ DIM_BUFFER ] ;
            /* Arquivo tabela */

      static char NomeArquivoLista[ DIM_BUFFER ] ;
            /* Arquivo lista */

      static int ContaArquivosString ;
            /* Contador de arquivos de especificação de strings */

      static int ContaEspecString ;
            /* Contador de número de especificações de strings registrados */

      static int ContaStringao ;
            /* Contador de número de stringões gerados */

      static int ContaErros ;
            /* Contador de erros de sintaxe encontrados */

/***** Protótipos das funções encapuladas no módulo *****/

   static tpCondRet ObterTodasListasDados( ) ;

   static void ProcessarArquivoStrings( char * NomeArquivoString ) ;

   static void GerarTabelaStrings( ) ;

   static void GerarEstatisticas( ) ;

   static tpElemString * CriarElemListaString( long   idStringParm ,
                                               int    tamStringParm ,
                                               char * StringParm ) ;

   static tpElemArquivo * CriarElemListaArquivo( char * NomeArquivoParm ) ;

   static int RegistrarArquivo( char * NomeArquivo ) ;

   static int ObterInxExtensao( char * NomeArquivo ) ;

   static tpCondRet LerTrimmed( FILE * pArqLe    ,
                                char * pBuffer   ,
                                int    dimBuffer ,
                                int    Modo       ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: GTB Processar linha de comando de gerar tabela de strings
*
*  $ED Descrição da função
*     Gera a tabela de strings residentes em memória.
*     A tabela é gerada a partir dos arquivos *.def identificados
*     no arquivo ListaArquivos.def passado por parâmetro
*
***********************************************************************/

   int main( int numParametros , char ** vtParametros  )
   {

      tpCodigoErro CodigoErro = CodigoOK ;

      char ParametroCorr[ DIM_BUFFER ] ;

      int i ;

      int numParmLista = 0 ;

      int numParmTabela = 0 ;

      /* Apresentar identificação do programa */

         printf( "\nGeraTab - Gerar a tabela de strings residentes em memória" ) ;
         printf( "\n          LES/DI/PUC-Rio, versão 1, 21/11/2004\n" ) ;

      /* Processar parâmetros de linha de comando */

         ContaArquivosString = 0 ;
         ContaEspecString    = 0 ;
         ContaStringao       = 0 ;
         ContaErros          = 0 ;

         /* Obter todos parâmetros de linha de comando */

            NomeArquivoLista[  0 ] = 0 ;
            ParametroCorr[     0 ] = 0 ;

            strcpy( NomeArquivoTabela , NomeArquivoTabelaDefault ) ;

            for ( i = 1 ; i < numParametros ; i ++ ) {

            /* Obter parametro corrente */

               strcpy( ParametroCorr , vtParametros[ i ] ) ;

            /* Processar parâmetro arquivo lista de arquivos */

               if ( memcmp( ParametroCorr , idParmArquivoLista , DIM_ID_PARM ) == 0 )
               {

                  if ( numParmLista > 0 )
                  {
                     CodigoErro = CodigoParametroDuplo ;
                     printf( "\n>>> Arquivo lista %s definido múltiplas vezes." , ParametroCorr ) ;
                     ContaErros ++ ;

                  } else {
                     numParmLista ++ ;
                     strcpy( NomeArquivoLista , & ParametroCorr[ DIM_ID_PARM ] ) ;

                     if ( ObterInxExtensao( NomeArquivoLista ) == - 1 )
                     {
                        strcat( NomeArquivoLista , ExtArquivoLista ) ;
                     } /* if */
                  } /* if */

               } /* fim ativa: Processar parâmetro arquivo lista de arquivos */

            /* Processar parÂametro arquivo a ser gerado */

               else if ( memcmp( ParametroCorr , idParmGerado , DIM_ID_PARM ) == 0 )
               {

                  if ( numParmTabela > 0 )
                  {
                     CodigoErro = CodigoParametroDuplo ;
                     printf( "\n>>> Arquivo tabela %s definido múltiplas vezes." , ParametroCorr ) ;
                     ContaErros ++ ;

                  } else
                  {
                     numParmTabela ++ ;
                     strcpy( NomeArquivoTabela , & ParametroCorr[ DIM_ID_PARM ] ) ;
                  } /* if */

               } /* fim ativa: Processar parÂametro arquivo a ser gerado */

            /* Processar parâmetro auxílio */

               else if ( ( memcmp( ParametroCorr , idParmAuxilio1 , DIM_ID_PARM ) == 0 )
                      || ( memcmp( ParametroCorr , idParmAuxilio2 , DIM_ID_PARM ) == 0 )
                      || ( memcmp( ParametroCorr , idParmAuxilio3 , DIM_ID_PARM ) == 0 )
                      || ( ParametroCorr[ 0 ] == '?' ))
               {

                  CodigoErro = CodigoAuxilio ;

               } /* fim ativa: Processar parâmetro auxílio */

            /* Tratar parâmetro errado */

               else
               {

                  printf( "\n>>> Parâmetro errado: %s" , ParametroCorr ) ;
                  CodigoErro = CodigoErroParametro ;
                  ContaErros ++ ;

               } /* fim ativa: Tratar parâmetro errado */

            } /* fim repete: Obter todos parâmetros de linha de comando */

         /* Controlar corretude dos parâmetros */

            if ( numParmLista == 0 )
            {
               CodigoErro = CodigoNaoArquivoLista ;
               printf( "\n>>> O arquivo lista não foi definido." ) ;
               ContaErros ++ ;
            } /* if */

            if ( ObterInxExtensao( NomeArquivoTabela ) == -1 )
            {
               strcat( NomeArquivoTabela , ExtArquivoTabela ) ;
            } /* if */

         /* Exibir help de uso do programa */

            if( CodigoErro != CodigoOK )
            {

               printf( "\n\nSintaxe da linha de comando: " ) ;
               printf( "\n geratab { /L<Arquivo Lista> | /T<Arquivo Tabela> | /h | /H | /? | ? }" ) ;
               printf( "\n" ) ;
               printf( "\n   <Arquivo Lista> E' o nome de um arquivo que contem a lista" ) ;
               printf( "\n         dos nomes de todos os arquivos de especificacao de" ) ;
               printf( "\n         strings a serem processados" ) ;
               printf( "\n   <Arquivo Tabela> parametro opcional, e' o nome do arquivo" ) ;
               printf( "\n         tabela de strings a ser gerado." ) ;
               printf( "\n As extensões default sao: " ) ;
               printf( "\n   lista  - para o arquivo que contem a lista de arquivos a processar" ) ;
               printf( "\n   espstr - para os arquivos contendo strings." ) ;
               printf( "\n   tabstr - para o arquivo tabela a ser gerado." ) ;
               printf( "\n Nao sendo fornecido o nome do arquivo a ser gerado, a tabela " ) ;
               printf( "\n sera gerada no arquivo tabelastring.tab " ) ;
               printf( "\n\n" ) ;

               GerarEstatisticas( ) ;

               if ( CodigoErro != CodigoAuxilio )
               {
                  return 4 ;
               } /* if */

               return 0 ;

            } /* fim ativa: Exibir help de uso do programa */

      /* Obter as listas de todos arquivos e todos os strings */

         #ifdef _DEBUG
            Todos os parâmetros estão OK, e não tem solicitação de auxílio
         #endif

         ObterTodasListasDados( ) ;

      /* Gerar o arquivo de strings */

         if ( ContaErros == 0 )
         {

            GerarTabelaStrings( ) ;

         } /* fim ativa: Gerar o arquivo de strings */

      /* Terminar o programa */

         GerarEstatisticas( ) ;

         if ( ContaErros > 0 )
         {
            CodigoErro = CodigoErroProcessamento ;
            printf( "\n\n>>> Foram encontrados %i erros.\n\n" ,
                    ContaErros ) ;
            return 4 ;
         } /* if */

         printf( "\n\n" ) ;

         return 0 ;

   } /* Fim função: GTB Processar linha de comando de gerar tabela de strings */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: GT Obter todas as listas
*
*  $ED Descrição da função
*     Percorre o arquivo lista.
*     Para cada arquivo encontrado extrai todos os strings especificados.
*     Gera a lista de todos os strings a serem inseridos na tabela
*
*  $EAE Assertivas de saída asseguradas
*     A lista de arquivos de especificação de strings e a lista de strings
*     foram criadas.
*     Independentemente de como termina a execução as listas estarão corretas.
*     Caso não tenha ocorrido erro, as listas estão completas.
*     Caso tenha ocorrido erro as listas poderaão estar incompletas.
*     ContaErros conta o número de erros encontrados, 0 se nenhum.
*
***********************************************************************/

   tpCondRet ObterTodasListasDados( )
   {

      FILE * pArquivoLista = NULL ;

      tpCondRet CondRet    = CondRetOK ;

      char LinhaArquivoString[ DIM_BUFFER ] ;
      char NomeArquivoString[ DIM_BUFFER ] ;

      /* Iniciar as listas */

         pOrigemListaStrings  = CriarElemListaString( 0 , 0 , "||" ) ;
         pOrigemListaArquivos = CriarElemListaArquivo( "||" ) ;

      /* Processar arquivo de especificação de strings default */

         ProcessarArquivoStrings( NomeArquivoStringDefault ) ;

      /* Abrir arquivo lista de arquivos de especificação de strings */

         pArquivoLista = fopen( NomeArquivoLista , "r" ) ;

         if ( pArquivoLista == NULL )
         {
            printf( "\n>>> Arquivo lista  %s  não existe." , NomeArquivoLista ) ;
            ContaErros ++ ;
            return CondRetErro ;
         } /* if */

      /* Processar todos os arquivos de definição de string */

         LinhaArquivoString[ 0 ] = 0 ;

         CondRet = LerTrimmed( pArquivoLista , LinhaArquivoString ,
                               DIM_BUFFER - 1 , LIMPA_INIC | LIMPA_FIM ) ;

         while ( CondRet == CondRetOK ) {

         /* Processar arquivo de especificação de strings */

            if ( sscanf( LinhaArquivoString ,
                         "#include \"%[^\"]s\"" , NomeArquivoString ) == 1 )
            {
               ProcessarArquivoStrings( NomeArquivoString ) ;
            } else
            {
               printf( "\n>>> Linha arquivo string errada: %s" , LinhaArquivoString ) ;
               ContaErros ++ ;
            } /* if */

         /* Obter próximo nome de arquivo de definição */

            CondRet = LerTrimmed( pArquivoLista , LinhaArquivoString ,
                                  DIM_BUFFER - 1 , LIMPA_INIC | LIMPA_FIM ) ;

         } /* fim repete: Processar todos os arquivos de definição de string */

         if ( CondRet != CondRetFimArq )
         {
            printf( "\n>>> Litura do arquivo lista % cancelada." ,
                    NomeArquivoLista ) ;
            ContaErros ++ ;
         } /* if */

         fclose( pArquivoLista ) ;

      /* Controlar erros de geração */

         if ( ContaEspecString == 0 )
         {
            printf( "\n>>> Nenhum string foi encontrado" ) ;
            ContaErros ++ ;
         } /* if */

      return CondRetOK ;

   } /* Fim função: GT Obter todas as listas */


/***********************************************************************
*
*  $FC Função: GT Extrair todos os strings de arquivo de definição de strings
*
***********************************************************************/

   void ProcessarArquivoStrings( char * NomeArquivoString )
   {

      FILE * pArquivoString = NULL ;

      long OffsetLido = 0 ;

      char LinhaString[ DIM_BUFFER ] ;

      char NomeConstante[ DIM_NOME_STRING ] ;
      char StringLido[ DIM_STRING ] ;

      int  TemErro    = 1 ;
      int  tamString  = 0 ;

      tpCondRet CondRet = CondRetErro ;

      int  numLidos     = -1 ;
      long idStringLido = -1 ;

      int ContaCh    = 0 ;

      enum
      {
         EstadoInicial ,
         EstadoNormal ,
         EstadoEscape ,
         EstadoOctal ,
         EstadoHexadecimal ,
         EstadoErro = 99
      } Estado = EstadoErro ;

      int inxCh      = 1 ;

      tpElemString * pStringNovo = NULL ;
      tpElemString * pStringCorr = NULL ;

      /* Abrir arquivo de especificação de strings */

         if ( ObterInxExtensao( NomeArquivoString ) == -1 )
         {
            strcat( NomeArquivoString , ExtArquivoString ) ;
         } /* if */

         if ( !RegistrarArquivo( NomeArquivoString ))
         {
            return ;
         } /* if */

         pArquivoString = fopen( NomeArquivoString , "r" ) ;

         if ( pArquivoString == NULL )
         {
            printf( "\n>>> Arquivo  %s  não existe." , NomeArquivoString ) ;
            ContaErros ++ ;
            return ;

         } /* if */

         printf( "\n  Arquivo string:  %s" , NomeArquivoString ) ;
         ContaArquivosString ++ ;

      /* Ler offset de idString */

         CondRet = LerTrimmed( pArquivoString , LinhaString ,
                               DIM_BUFFER - 1 , LIMPA_INIC | LIMPA_FIM ) ;
         if ( CondRet != CondRetOK )
         {
            printf( "\n>>> Arquivo  %s  vazio." , NomeArquivoString ) ;
            ContaErros ++ ;
            return ;
         } /* if */

         numLidos = sscanf( LinhaString , " %s %li" ,
                            StringLido , &OffsetLido ) ;

         if ( ( numLidos != 2 )
           || ( strcmp( StringLido , CMD_OFFSET ) != 0 ))
         {
            printf( "\n>>> Arquivo nao inicia com %s: %s" ,
                    CMD_OFFSET , LinhaString ) ;
            ContaErros ++ ;
            OffsetLido = 0 ;
         } /* if */

      /* Obter todos os strings do arquivo corrente */

         CondRet = LerTrimmed( pArquivoString , LinhaString ,
                               DIM_BUFFER - 1 , LIMPA_INIC | LIMPA_FIM ) ;

         while ( CondRet == CondRetOK ) {

         /* Ler especificação válida */

            numLidos = sscanf( LinhaString , " %s %li %[^\n]" ,
                               NomeConstante , &idStringLido , StringLido ) ;

            TemErro   = 0 ;
            tamString = strlen( StringLido ) ;

            if ( ( numLidos != 3 )
              || ( tamString + 1 > DIM_STRING )
              || ( StringLido[ 0 ] != '\"' )
              || ( StringLido[ tamString - 1 ] != '\"' ))
            {
               TemErro = 1 ;
               printf( "\n>>> Especificacao de string errada: %s" , LinhaString ) ;
               ContaErros ++ ;
            } /* if */

         /* Processar linha de especificação */

            if ( !TemErro )
            {

               inxCh   = 0 ;
               ContaCh = 0 ;
               Estado  = 0 ;

               /* Calcular tamanho compilado do string */

                  inxCh   = 0 ;
                  ContaCh = 0 ;
                  Estado  = EstadoInicial ;

                  while ( inxCh < tamString ) {

                  /* Handle current character */

                     switch( Estado ) {

                     /* Tratar caractere aspas inicial */

                        case EstadoInicial :
                        {

                           if ( StringLido[ inxCh ] != '\"' )
                           {
                              printf( "\n>>> Constante string não inicia com aspas: %s" ,
                                  StringLido ) ;
                              ContaErros++ ;
                              inxCh-- ;
                           } /* if */
                           Estado = EstadoNormal ;

                           break ;

                        } /* fim ativa: Tratar caractere aspas inicial */

                     /* Tratar caractere normal */

                        case EstadoNormal :
                        {

                           if ( StringLido[ inxCh ] == '\\' )
                           {
                              ContaCh ++ ;
                              Estado = EstadoEscape ;

                           } else if ( StringLido[ inxCh ] == '\"' )
                           {
                              if ( tamString - 1 == inxCh )
                              {
                                 StringLido[ inxCh ] = 0 ;
                              } else
                              {
                                 printf( "\n>>> Aspas no meio do string: %s" , StringLido ) ;
                                 ContaErros ++ ;

                                 StringLido[ inxCh ] = '?' ;
                                 ContaCh ++ ;
                              } /* if */

                           } else if ( StringLido[ inxCh ] == 0 )
                           {
                              printf( "\n>>>  Falta aspas final: %s" , StringLido ) ;
                              ContaErros ++ ;
                              tamString = inxCh ; // break out

                           } else
                           {
                              ContaCh ++ ;
                           } /* if */

                           break ;

                        } /* fim ativa: Tratar caractere normal */

                     /* Tratar escape */

                        case EstadoEscape :
                        {

                           if ( ( StringLido[ inxCh ] == 'x' )
                             || ( StringLido[ inxCh ] == 'X' ))
                           {
                              Estado = EstadoHexadecimal ;

                           } else if ( strchr( "01234567" , StringLido[ inxCh ] ) != NULL )
                           {
                              Estado = EstadoOctal ;

                           } else if ( strchr( "abfnrtv\'\"\\?" , StringLido[ inxCh ] ) != NULL )
                           {
                              Estado = EstadoNormal ;

                           } else
                           {
                              printf( "\n>>> Sequencia escape mal formada: %s" , StringLido ) ;
                              ContaErros ++ ;
                              Estado   = EstadoNormal ;
                           } /* if */

                           break ;

                        } /* fim ativa: Tratar escape */

                     /* Tratar escape definição octal */

                        case EstadoOctal :
                        {

                           Estado = EstadoNormal ;

                           if ( strchr( "01234567" , StringLido[ inxCh ] ) == NULL )
                           {
                              inxCh -- ;    /* reler o caractere */
                              break ;
                           }

                           inxCh ++ ;
                           if ( strchr( "01234567" , StringLido[ inxCh ] ) == NULL )
                           {
                              inxCh -- ;    /* reler o caractere */
                           }

                           break ;

                        } /* fim ativa: Tratar escape definição octal */

                     /* Tratar escape hexadecimal */

                        case EstadoHexadecimal :
                        {

                           if ( strchr( "0123456789abcdefABCDEF" , StringLido[ inxCh ] ) == NULL )
                           {
                              Estado = EstadoNormal ;
                              inxCh -- ;
                           }
                           break ;

                        } /* fim ativa: Tratar escape hexadecimal */

                     /* Handle illegal field */

                        default :
                        {

                           printf( "\n>>> Estado desconhecido: %d" , Estado ) ;
                           ContaErros++ ;

                           return ;

                        } /* fim ativa: Handle illegal field */

                     } /* fim seleciona: Handle current character */

                  /* Avançar para o próximo caractere */

                     inxCh ++ ;

                  } /* fim repete: Calcular tamanho compilado do string */

               /* Registrar o string na lista ordenada por idString */

                  #ifdef _DEBUG
                     OffsetLido  contém o offset a ser adicionado a todos os ids de strings
                                 do corrente arquivo
                     ContaCh     contém o tamanho do string em memória (depois de compilado)
                     StringLido  contém o string original, com aspas inicial e
                                 sem aspas final
                  #endif

                  idStringLido += OffsetLido ;

                  pStringCorr  = pOrigemListaStrings ;

                  while ( pStringCorr->pProx != NULL )
                  {
                     if ( pStringCorr->pProx->idString > idStringLido )
                     {
                        break ;
                     } else if ( pStringCorr->pProx->idString == idStringLido )
                     {
                        printf( "\n>>> Identificacao de string duplicada: %s" ,
                                LinhaString ) ;
                        ContaErros ++ ;
                        break ;
                     } /* if */

                     pStringCorr = pStringCorr->pProx ;
                  } /* while */

                  pStringNovo = CriarElemListaString(
                                      idStringLido , ContaCh , StringLido + 1 ) ;
                  ContaEspecString ++ ;

                  pStringNovo->pAnt   = pStringCorr ;
                  pStringNovo->pProx  = pStringCorr->pProx ;
                  pStringCorr->pProx  = pStringNovo ;
                  if ( pStringNovo->pProx != NULL )
                  {
                     pStringNovo->pProx->pAnt = pStringNovo ;
                  } /* if */

            } /* fim ativa: Processar linha de especificação */

         /* Obter a próxima especificação de string */

            CondRet = LerTrimmed( pArquivoString , LinhaString ,
                                  DIM_BUFFER - 1 , LIMPA_INIC | LIMPA_FIM ) ;

         } /* fim repete: Obter todos os strings do arquivo corrente */

      /* Terminar processamento do arquivo de especificação de strings */

         if ( CondRet != CondRetFimArq )
         {
            printf( "\n>>> Litura do arquivo string % cancelada." ,
                    NomeArquivoString ) ;
            ContaErros ++ ;
         } /* if */

         fclose( pArquivoString ) ;

   } /* Fim função: GT Extrair todos os strings de arquivo de definição de strings */


/***********************************************************************
*
*  $FC Função: GT Gerar arquivo tabela de strings
*
***********************************************************************/

   void GerarTabelaStrings( )
   {

      tpElemArquivo * pArquivoCorr = NULL ;

      tpElemString * pStringCorr  = NULL ;

      int tamCorr     = 0 ;
      int ContaTabela = 0 ;

      int inxTabela = -1 ;

      int i ;

      FILE * pArquivoTabela = NULL ;

      /* Abrir arquivo tabela de strings */

         pArquivoTabela = fopen( NomeArquivoTabela , "w" ) ;

         if ( pArquivoTabela == NULL )
         {
            printf( "\n>>> Arquivo tabela  %s  não abre." , NomeArquivoTabela ) ;
            ContaErros ++ ;
            return ;
         } /* if */

      /* Gerar comentários do cabeçalho do arquivo */

         /* Gerar comentário preâmbulo do arquivo gerado */

            fprintf( pArquivoTabela ,
                       "#ifndef _tabela_string_" ) ;
            fprintf( pArquivoTabela ,
                     "\n#define _tabela_string_" ) ;
            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n/* !!!!!!!!!! Aquivo gerado! Não o edite! !!!!!!!!!! */" ) ;
            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n/****************************************************************************" ) ;
            fprintf( pArquivoTabela ,
                     "\n*" ) ;
            fprintf( pArquivoTabela ,
                     "\n* $AT Tabela de strings gerada" ) ;
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

         /* Gerar lista de arquivos processados */

            fprintf( pArquivoTabela ,
                     "\n*" ) ;
            fprintf( pArquivoTabela ,
                     "\n* Arquivos de especificação de strings utilizados para gerar a tabela:" ) ;
            fprintf( pArquivoTabela ,
                     "\n*" ) ;

            pArquivoCorr = pOrigemListaArquivos->pProx ;

            while ( pArquivoCorr != NULL )
            {
               fprintf( pArquivoTabela ,
                        "\n*      - %s" , pArquivoCorr->NomeArquivo ) ;
               pArquivoCorr = pArquivoCorr->pProx ;
            } /* while */

         /* Gerar finalização do comentário de abertura */

            fprintf( pArquivoTabela ,
                     "\n*" ) ;
            fprintf( pArquivoTabela ,
                     "\n***************************************************************************/" ) ;

      /* Gerar tabela de pesquisa */

         /* Gerar declaração do tipo tabela de pesquisa */

            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n#define  DIM_TABELA_STRING  %d" , ContaEspecString ) ;
            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n/* Descritor dos elementos da tabela de pesquisa */" ) ;
            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n   typedef struct" ) ;
            fprintf( pArquivoTabela ,
                     "\n   {" ) ;
            fprintf( pArquivoTabela ,
                     "\n      long idString        ;" ) ;
            fprintf( pArquivoTabela ,
                     "\n      int  tamString       ; /* tamanho strlen do string */" ) ;
            fprintf( pArquivoTabela ,
                     "\n      int  inxSubTabela    ; /* identifica o vetor de texto*/" ) ;
            fprintf( pArquivoTabela ,
                     "\n      int  inxOrigemString ; /* origem no vetor de texto*/" ) ;
            fprintf( pArquivoTabela ,
                     "\n   } tpElementoTabela ;" ) ;

         /* Gerar daclaração cabeçalho da tabela de pesquisa */

            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n/* Tabela de pesquisa" ) ;
            fprintf( pArquivoTabela ,
                     "\n*     Cada elemento corresponde a um string" ) ;
            fprintf( pArquivoTabela ,
                     "\n*     Strings são procurados pelo correspondente id." ) ;
            fprintf( pArquivoTabela ,
                     "\n*     Cada elemento referencia para um vetor de caracteres contendo o" ) ;
            fprintf( pArquivoTabela ,
                     "\n*     string. Fornecendo, ainda, o offset de início do string neste vetor.*/" ) ;
            fprintf( pArquivoTabela ,
                     "\n" ) ;
            fprintf( pArquivoTabela ,
                     "\n   static tpElementoTabela vtTabelaPesquisa[ DIM_TABELA_STRING ] =" ) ;
            fprintf( pArquivoTabela ,
                     "\n   {" ) ;

         /* Gerar corpo da tabela de pesquisa */

            pStringCorr  = pOrigemListaStrings->pProx ;

            tamCorr      = 0 ;
            ContaTabela  = 0 ;

            while ( pStringCorr != NULL )
            {
               if ( tamCorr + pStringCorr->tamString >= DIM_STRINGAO )
               {
                  ContaTabela ++ ;
                  tamCorr = 0 ;
               } /* if */

               pStringCorr->inxString    = ContaTabela ;
               pStringCorr->offsetString = tamCorr ;
               tamCorr                  += pStringCorr->tamString + 1 ;

               fprintf( pArquivoTabela ,
                        "\n      { %8li , %5i , %5i , %5i }" ,
                        pStringCorr->idString  , pStringCorr->tamString ,
                        pStringCorr->inxString , pStringCorr->offsetString ) ;

               if ( pStringCorr->pProx != NULL )
               {
                  fprintf( pArquivoTabela , " ," ) ;
               } else
               {
                  fprintf( pArquivoTabela , "  " ) ;
               } /* if */

               fprintf( pArquivoTabela , " /* \"%s\" */" ,
                        pStringCorr->String ) ;

               pStringCorr = pStringCorr->pProx ;
            } /* while */

            fprintf( pArquivoTabela ,
                     "\n   } ; /* Fim tabela de pesquisa */" ) ;

      /* Gerar vetores de caracteres */

         fprintf( pArquivoTabela ,
                  "\n" ) ;
         fprintf( pArquivoTabela ,
                  "\n/* Vetores de strings" ) ;
         fprintf( pArquivoTabela ,
                  "\n*  Cada vetor contém um ou mais strings terminados em zero" ) ;
         fprintf( pArquivoTabela ,
                  "\n*  Cada vetor contém no máximo %d bytes */" ,
                  DIM_STRINGAO ) ;

         inxTabela = -1 ;

         pStringCorr  = pOrigemListaStrings->pProx ;

         while ( pStringCorr != NULL )
         {
            if ( inxTabela != pStringCorr->inxString )
            {
               if ( inxTabela >= 0 )
               {
                  fprintf( pArquivoTabela ,
                           "\n   ; /* Fim vetor %d */" , inxTabela ) ;
               } /* if */
               inxTabela = pStringCorr->inxString ;
               fprintf( pArquivoTabela , "\n" ) ;
               fprintf( pArquivoTabela ,
                        "\n   static char Stringao_%d[ ] = " , inxTabela ) ;
            } /* if */

            fprintf( pArquivoTabela ,
                     "\n      \"%s\\0\"" , pStringCorr->String ) ;

            pStringCorr = pStringCorr->pProx ;
         } /* while */

         fprintf( pArquivoTabela ,
                  "\n   ; /* Fim vetor %d */" , inxTabela ) ;

      /* Gerar vetor de referências a vetores de strings */

         fprintf( pArquivoTabela ,
                  "\n" ) ;
         fprintf( pArquivoTabela ,
                  "\n/* Vetor de referências a vetores de strings */" ) ;
         fprintf( pArquivoTabela ,
                  "\n" ) ;
         fprintf( pArquivoTabela ,
                  "\n   static char * vtpStringoes[ %i ] = " , ContaTabela + 1 ) ;
         fprintf( pArquivoTabela ,
                  "\n        {" ) ;

         for ( i = 0 ; i <= ContaTabela ; i++ )
         {
            fprintf( pArquivoTabela , " Stringao_%i" , i ) ;
            if ( i < ContaTabela )
            {
               fprintf( pArquivoTabela , " ," ) ;
            } /* if */
         } /* for */

         fprintf( pArquivoTabela , " } ;" ) ;

      /* Gerar término da tabela de strings */

         fprintf( pArquivoTabela ,
                  "\n" ) ;
         fprintf( pArquivoTabela ,
                  "\n#endif" ) ;
         fprintf( pArquivoTabela ,
                  "\n" ) ;
         fprintf( pArquivoTabela ,
                  "\n/* Fim tabela strings gerada */" ) ;
         fprintf( pArquivoTabela ,
                  "\n" ) ;

         fclose( pArquivoTabela ) ;

   } /* Fim função: GT Gerar arquivo tabela de strings */


/***********************************************************************
*
*  $FC Função: GT Gerar arquivo de estatísticas
*
*  $ED Descrição da função
*     Gera um arquivo de estatísticas para fins de automação dos testes
*
***********************************************************************/

   void GerarEstatisticas( )
   {

      FILE * pArquivoEstatisticas = NULL ;

      pArquivoEstatisticas = fopen( NomeArquivoEstatisticas , "w" ) ;

      if ( pArquivoEstatisticas != NULL )
      {
         fprintf( pArquivoEstatisticas , "NumArquivosString: %7d\n" ,
                        ContaArquivosString ) ;
         fprintf( pArquivoEstatisticas , "NumStrings:        %7d\n" ,
                        ContaEspecString ) ;
         fprintf( pArquivoEstatisticas , "NumVetoresString:  %7d\n" ,
                        ContaStringao + 1 ) ;
         fprintf( pArquivoEstatisticas , "NumErros:          %7d\n" ,
                        ContaErros ) ;
         fclose( pArquivoEstatisticas ) ;
      } else
      {
         printf( "\n>>> Arquivo estatisticas  %s  não abre." ,
                 NomeArquivoEstatisticas ) ;
         ContaErros ++ ;
      } /* if */

   } /* Fim função: GT Gerar arquivo de estatísticas */


/***********************************************************************
*
*  $FC Função: GT Criar elemento de lista string
*
***********************************************************************/

   tpElemString * CriarElemListaString( long   idStringParm ,
                                        int    tamStringParm ,
                                        char * StringParm )
   {

      int tamString = 0 ;
      tpElemString * pElemString = NULL ;

      pElemString = ( tpElemString * ) malloc( sizeof( tpElemString )) ;

      tamString = strlen( StringParm ) ;
      if ( tamString >= DIM_STRING )
      {
         tamString = DIM_STRING - 1 ;
         printf( "\n>>> String longo demais: %s" , StringParm ) ;
         StringParm[ tamString ] = 0 ;
         ContaErros ++ ;
      } /* if */

      pElemString->pAnt         = NULL ;
      pElemString->pProx        = NULL ;

      memchr( pElemString->String , 0 , DIM_STRING ) ;
      strcpy( pElemString->String , StringParm ) ;

      pElemString->idString     = idStringParm ;
      pElemString->tamString    = tamStringParm ;
      pElemString->inxString    = 0 ;
      pElemString->offsetString = 0 ;

      return pElemString ;

   } /* Fim função: GT Criar elemento de lista string */


/***********************************************************************
*
*  $FC Função: GT Criar elemento de lista de arquivos
*
***********************************************************************/

   tpElemArquivo * CriarElemListaArquivo( char * NomeArquivoParm )
   {

      tpElemArquivo * pElemArquivo = NULL ;

      pElemArquivo = ( tpElemArquivo * ) malloc( sizeof( tpElemArquivo )) ;
      pElemArquivo->pAnt  = NULL ;
      pElemArquivo->pProx = NULL ;
      strcpy( pElemArquivo->NomeArquivo , NomeArquivoParm ) ;

      return pElemArquivo ;

   } /* Fim função: GT Criar elemento de lista de arquivos */


/***********************************************************************
*
*  $FC Função: GT Inserir arquivo na lista ordenada por nome
*
*  $EP Parâmetros
*     pArquivoNovo - elemento arquivo a ser inserido na lista
*
*  $FV Valor retornado
*     0 se arquivo já estava registrado
*     1 se não
*           destrói o elemento não inserido na lista
*
*  $FGP Tipos e Variáveis globais externas do próprio módulo
*     pOrigemListaArquivos - aponta para a cabeça da lista de arquivos
*
***********************************************************************/

   int RegistrarArquivo( char * NomeArquivo )
   {

      tpElemArquivo * pArquivoNovo  = NULL ;
      tpElemArquivo * pArquivoCorr  = NULL ;

      #ifdef _DEBUG
         A cabeça da lista é um elemento normal.
      #endif

      pArquivoCorr = pOrigemListaArquivos ;

      while ( pArquivoCorr->pProx != NULL )
      {
         if ( strcmp( pArquivoCorr->pProx->NomeArquivo , NomeArquivo ) > 0 )
         {
            break ;

         } else if ( strcmp( pArquivoCorr->pProx->NomeArquivo , NomeArquivo ) == 0 )
         {
            printf( "\n>>> Arquivo string duplicado: %s" , NomeArquivo ) ;
            ContaErros ++ ;

            return 0 ;

         } /* if */

         pArquivoCorr = pArquivoCorr->pProx ;

      } /* while */

      pArquivoNovo = CriarElemListaArquivo( NomeArquivo ) ;

      pArquivoNovo->pAnt  = pArquivoCorr ;
      pArquivoNovo->pProx = pArquivoCorr->pProx ;
      pArquivoCorr->pProx = pArquivoNovo ;
      if ( pArquivoNovo->pProx != NULL )
      {
         pArquivoNovo->pProx->pAnt = pArquivoNovo ;
      } /* if */

      return 1 ;

   } /* Fim função: GT Inserir arquivo na lista ordenada por nome */


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

/********** Fim do módulo de implementação: GTB Gerar a tabela de strings residentes **********/

