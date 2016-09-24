#if ! defined( TabStr_ )
#define TabStr_
/***************************************************************************
*
*  $MCD Módulo de definição: TBS  Tabela de strings
*
*  Arquivo gerado:              TabStr.H
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
*  $ED Descrição do módulo
*     Este módulo implementa funções de acesso uma tabela de strings.
*     A tabela de string agrega em um único arquivo todos os strings
*     utilizados em determinado programa.
*
*     O presente módulo opera com uma tabela residente em memória.
*
*     O conteúdo dessa tabela é gerado pelo programa GERATAB.EXE
*     a partir de um ou mais arquivos contendo as especificações de strings.
*
*     O conteúdo das correspondentes tabelas de definição é gerado pelo
*     programa GERADEF.EXE a partir dos mesmos arquivos de especificações
*     utilizado por GERATAB.EXE.
*
*  $EIU Interface com o usuário pessoa
*     Os strings são terminados por zero, e são compatíveis com as funções
*     definidas na biblioteca C.
*
***************************************************************************/
 
#if defined( TabStr_OWN )
   #define TabStr_EXT
#else
   #define TabStr_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

#define     TBS_MAX_LENGTH            256
#define     TBS_MIN_LENGTH              5


/***********************************************************************
*
*  $TC Tipo de dados: TBS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno
*
***********************************************************************/

   typedef enum {

         TBS_CondRetErroTabela = -3 ,
               /* Tabela mal formada */

         TBS_CondRetTruncado   = -2 ,
               /* String truncado, tamanho maior do que o espaço disponível */

         TBS_CondRetNaoExiste  = -1 ,
               /* Não encontrou o string */

         TBS_CondRetOK         =  0
               /* Operou corretamente */

   } TBS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: TBS Obter um string contido na tabela
*
*  $ED Descrição da função
*     Procura a identificação de um string na tabela de strings.
*     Caso encontrado, copia-o para o espaço disponibilizado pelo cliente.
*     Não sendo encontrado copia o string com idString == 1; default:
*
*        "Identificaao de string %d nao foi encontrada."
*
*     Contido no arquivo de especificação de string: DefinicaoDefault.defstr
*
*     Caso este também não seja encontrado, copia o string ERRO_STRING
*     definido neste módulo. Default:
*
*        "?!?!?"
*
*  $EP Parâmetros
*     idString    - identifica o string a ser procurado na tabela
*     dimString   - é a dimensão máxima, incluindo o zero terminal,
*                   que o string obtido poderá ter
*     pString     - ponteiro para espaço receptor do string com pelo
*                   menos dimString bytes
*
*  $FV Valor retornado
*     Condição de retorno
*
***********************************************************************/

   TBS_tpCondRet TBS_ObterString( long   idString  ,
                                  int    dimString ,
                                  char * pString ) ;


/***********************************************************************
*
*  $FC Função: TBS Obter o tamanho de um string
*
*  $ED Descrição da função
*     Retorna o tamanho do string idString contido na tabela
*
*  $EP Parâmetros
*     idStr - identificação do string
*
*  $FV Valor retornado
*     tamanho do string
*        == TBS_CondRetNaoExiste  caso não seja encontrado
*
***********************************************************************/

   int TBS_ObterTamanhoString( long idString ) ;


/***********************************************************************
*
*  $FC Função: TBS Teste - deturpar idString
*
*  $ED Descrição da função
*     Força um valor lido no idString de um determinado string.
*
***********************************************************************/

   void TBS_TesteDeturparIdString( int idString , int inxElemento ) ;

#undef TabStr_EXT

/********** Fim do módulo de definição: TBS  Tabela de strings **********/

#else
#endif
