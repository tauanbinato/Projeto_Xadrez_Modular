/***************************************************************************
*
*  M¢dulo de implementa‡„o: CED  Controlador de espaços de dados alocados dinamicamente
*
*  Arquivo gerado:          CESPDIN.c
*  Letras identificadoras:  CED
*  N£mero identificador:    
*
*  Nome l¢gico da base:  Arcabouço para a automação de testes de programas redigidos em C
*  Nome do arquivo base: D:\AUTOTEST\PROJETOS\ARCABOUC.BSW
*
*     INF 1301 / 1628 Automatização dos testes de módulos C
*  Direitos autorais da base
*     LES/DI/PUC-Rio
*
*  Estado corrente de distribui‡„o da base
*     Vers„o: 2    Modifica‡„o:      Altera‡„o:      Data libera‡„o: 
*
*     Autorizou libera‡„o     
*
*  Hist¢rico do projeto
*     Vers Modf Altr  Autor    Data     Observa‡”es
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*  Altera‡”es de emergˆncia realizadas e ainda n„o passadas a limpo
*  Altera‡”es e corre‡”es realizadas
*
***************************************************************************/

/******************* Declara‡”es encapsuladas do m¢dulo *******************/

   /****** Inclus”es utilizadas pelo m¢dulo ******/

   #include    <malloc.h>
   #include    <stdio.h>
   #include    <memory.h>
   #include    <string.h>

   /****** Inclus„o do m¢dulo de defini‡„o pr¢prio ******/

   #define CESPDIN_PROPRIO
   #include "CESPDIN.h"
   #undef CESPDIN_PROPRIO

   /****** Declara‡”es internas ao m¢dulo ******/

   #include    "Generico.h"
   #include    "GeraAlt.h"

   #include    "..\tabelas\IdTiposEspaco.def"

       /* O pragma é necessário para assegurar alinhamento a byte,
          uma vez que toda a aritmética com ponteiros assume isso */

   #pragma pack (1)

   #define     DIM_NOME_ARQ_FONTE  32
   #define     DIM_PONTEIRO         4

   #define     TIPO_MSG_INFO     "!!!"
   #define     TIPO_MSG_ERRO     "ee>"
   #define     TIPO_MSG_VAZIA    "   "

   #define     CHAR_ALOC      '|'
   #define     CHAR_DESALOC   '?'

   #define     LIMITE_FREQUENCIA      1000
   #define     LIMITE_INF_FREQUENCIA    10
   #define     LIMITE_SUP_FREQUENCIA  1000

   /* Controle do conteúdo do espaço alocado
   *
   * Ao serem alocados, a parte Valor dos espaços é inicializados para
   * CHAR_ALOC ("`"). Ao serem desalocados, os espaço todo é preenchido
   * com CHAR_DESALOC ("!"). Isto permite verificar o estado do espaço
   * ao acessá-lo. O objetivo é provocar erros sistemáticos caso um
   * programa tente utilizar espaços desalocados, ou se esqueça de
   * inicializar campos que contenha ponteiros.
   */

   #define     DIM_VALOR      2
   #define     DIM_CONTROLE   2
   #define     CONTROLE       "\x96\xC3"
   #define     CONTROLE_ERRO  "\x01\0"

   /* Todos os espaços são antecedidos e sucedidos por strings constantes
   * de controle (CONTROLE). Isto permite verificar se houve extravasão
   * ao transferir dados para o espaço.
   */

   #define     IMPRESSAO_DIGITAL  3141593526

   /* Todos os espacos de dados teem esta marca digital.
   * Isto permite assegurar que se trata de um espaço controlado.
   * O que, por sua vez permite misturar módulos instrumentados
   * com módulos otimizados (não instrumentados) sem que ocorram erros
   * de processamento que acabam levando ao cancelamento do programa
   */

   /***** Tipos de dados internos ao m¢dulo *****/

/***********************************************************************
*
*  Tipo de dados: CED Elemento da lista de controle de espaços de dados
*
*  Descri‡„o do tipo
*
*     Esta estrutura define a organização de um espaço de dados
*     alocado pelo controlador de vazamento.
*     O elemento prevê campos para a identificação do tipo do espaço de
*     dados e para o controle de extravasão dos limites estabelecidos
*     para o espaço de dados útil.
*
***********************************************************************/

      typedef struct tgElemListaControle {

      /* Estrutura de dados : Raiz de CED Elemento da lista de controle de espaços de dados */


         /* Estrutura de dados : Marcador de espaço controlado */

            unsigned long ImpressaoDigital ;

         /* Estrutura de dados : Tamanho total do espaço */

            int tamTotal ;

         /* Estrutura de dados : Ponteiro para o elemento anterior na lista de espaços alocados */

            struct tgElemListaControle * pAnt ;

         /* Estrutura de dados : Ponteiro para o elemento a seguir na lista de espaços alocados */

            struct tgElemListaControle * pProx ;

         /* Estrutura de dados : Identificador do espaço */

            int idEspaco ;

         /* Estrutura de dados : Marca de espaço ativo */

            int ehAtivo ;

         /* Estrutura de dados : Identificador do tipo do valor contido no espaço alocado */

            int idTipoValor ;

         /* Estrutura de dados : Dimensão, em bytes, do valor contido no espaço alocado */

            int tamValor ;

         /* Estrutura de dados : Número da linha do código fonte */

            int numLinhaFonte ;

         /* Estrutura de dados : Nome arquivo fonte */

            char NomeArquivoFonte[ DIM_NOME_ARQ_FONTE ] ;

         /* Estrutura de dados : Marcador de controle de extravasão antes do espaço */

            char ControleAntes[ DIM_CONTROLE ] ;

         /* Estrutura de dados : Dummy a ser substituído pelo espaço a ser ocupado pelo valor */

            char Valor[ DIM_VALOR ] ;

         /* Estrutura de dados : Marcador de controle de extravasão após */

            char ControleApos[  DIM_CONTROLE ] ;

      } tpElemListaControle ;

   /***** Estruturas de dados internas ao m¢dulo *****/

   /* Estrutura de dados : *CED  Dados globais encapsulados */


      /* Estrutura de dados : Constantes lógicas */

         #define  TRUE     1
         #define  FALSE    0

      /* Estrutura de dados : Controle de inicialização */

         static int estaInicializado = FALSE ;

      /* Estrutura de dados : Origem da lista de espaços alocados */

         static tpElemListaControle * pOrgLista = NULL;

      /* Estrutura de dados : Iterador: espaço corrente */

         static tpElemListaControle * pEspacoCorr = NULL;

      /* Estrutura de dados : Contador de espaços alocados */

         static long numEspacosAlocados = 0 ;

      /* Estrutura de dados : Contador do total de chamadas de alocação */

         static long TotalAlocacoes = 0 ;

      /* Estrutura de dados : Espaço total alocado */

         static long EspacoTotalAlocado = 0 ;

      /* Estrutura de dados : Limite de memória disponível */

         static long LimiteMemoria = 0 ;

      /* Estrutura de dados : Limite de número de espaços alocados */

         static long LimiteNumEspacos = 0 ;

      /* Estrutura de dados : Limite de freqüência estabelecido */

         static int FrequenciaMalloc ;

      /* Estrutura de dados : Contagem de NULLs gerados */

         static long ContaNULL ;

   /***** Prot¢tipos de pacotes internos ao m¢dulo *****/
       
      static void DesalocarEspaco( tpElemListaControle * pEspaco ) ;
       
      static tpElemListaControle * ObterOrigemElemento( void * Ponteiro ) ;
       
      static void ExibirCabecalho( char * TipoMsg , tpElemListaControle * pEspaco ) ;
       
      static void ExibirMensagem( char * Msg ) ;
       
      static int VerificarEspaco( tpElemListaControle * pEspaco ) ;

/********************** C¢digo dos pacotes do m¢dulo **********************/

/***************************************************************************
*
*  Fun‡„o: CED  &Inicializar o controlador de alocação de espaços dinâmicos
*
*  Descri‡„o da fun‡„o
*     Esta função inicializa o controlador de espaços em memória dinâmica.
*     A função deve ser chamada uma única vez, antes de qualquer outra função
*     do módulo.
*     Sugere-se que seja chamada ao iniciar o teste do módulo controlado.
*     O interpretador de comandos de controle de espaços dinâmicos
*     provê o comando de teste  =inicializarespacos  que chama a presente
*     função.
*
***************************************************************************/

   void CED_InicializarControlador( void )
   {

   /* Raiz de CED  &Inicializar o controlador de alocação de espaços dinâmicos */

      TST_ASSERT( !estaInicializado ) ;

      pOrgLista            = NULL ;
      pEspacoCorr          = NULL ;
      numEspacosAlocados   = 0 ;
      TotalAlocacoes       = 0 ;
      EspacoTotalAlocado   = 0 ;
      LimiteMemoria        = 0 ;
      LimiteNumEspacos     = 0 ;
      FrequenciaMalloc     = 0 ;
      ContaNULL            = 0 ;

      ALT_Inicializar( 0 ) ;

      estaInicializado     = TRUE ;

   } /* Fim pacote: Raiz de CED  &Inicializar o controlador de alocação de espaços dinâmicos */

/***************************************************************************
*
*  Fun‡„o: CED  &Alocar espaço
*
*  Descri‡„o da fun‡„o
*     Nos módulos controlados esta função substitui a função "malloc".
*     A susbtituição é transparente para o módulo controlado,
*     basta que inclua o módulo de controle de acesso a espaços de dados
*     dinâmicos. Ou seja, se o módulo de definição "CESPDIN.H" for
*     incluido, a presente função será utilizada ao chamar "malloc"
*     dentro do módulo cliente. Não sendo incluido "CESPDIN.H", será
*     chamada a função "malloc" padrão de C.
*
*     O espaço será alocado com controle somente se o módulo de controle
*     de espaço dinâmico tiver sido inicializado, ver comando de teste
*
*         =inicializarespacos     e a correspondente função.
*
*     Desta forma pode-se restringir o controle somente aos módulos
*     sob teste.
*
*     O valor (parte útil do espaço alocado) é inicializado para o
*     caractere '|', permitindo a verificação de se o valor foi
*     corretamente inicializado ou não após à inicialização na função
*     cliente.
*
*     Para assegurar transparência é definida a macro CED_MALLOC
*     que providencia os argumentos linha e arquivo fonte. Estes, por sua
*     vez, permitem identificar onde o espaço foi alocado, facilitando,
*     assim, resolver eventuais problemas de vazamento de memória
*     e/ou de uso incorreto de espaços.
*
*     A função aloca um "struct" contendo diversos controles além do
*     espaço útil (valor). O campo valor deste "struct" corresponde ao
*     espaço que seria alocado pela função de biblioteca "malloc".
*     O ponteiro retornado aponta para o campo valor, tornando
*     transparente o fato de se utilizar "malloc" ou esta função.
*
*     A função pode simular o esgotamento de memória. Para isto é necessário
*     estabelecer um limite através de uma das funções a isto destinadas.
*     Por exemplo, se o limite de espaço alocado for diferente de zero e o
*     total de espaço já alocado acrescido do espaço solicitado for maior
*     do que o limite estabelecido, a função não aloca espaço e retorna NULL,
*     simulando falta de memória.
*
*     A função pode simular esgotamento aleatório de memória. Para isto
*     é necessário estabelecer a freqüência de NULLs simulados, vela o
*     comando =limitarfrequencia em INTRPCED.C
*
*     Consulte as funções CED_Limitar... para detalhes das formas de
*     limite que podem ser estabelecidas.
*
***************************************************************************/

   void * CED_Malloc( size_t Tamanho ,
                      int    numLinhaFonte ,
                      char * NomeArquivoFonte )
   {

   /* Dados do bloco: Raiz de CED  &Alocar espaço */

      tpElemListaControle * pEspaco ;

   /* Dados do bloco: Inicializar a identificação do código fonte */

      int tamNomeArq ;

   /* Raiz de CED  &Alocar espaço */

      TST_ASSERT( Tamanho > 0 ) ;
      TST_ASSERT( numLinhaFonte > 0 ) ;
      TST_ASSERT( NomeArquivoFonte != NULL ) ;

      /* Alocar sem controle quando não inicializado */

         if ( ! estaInicializado )
         {
            return malloc( Tamanho ) ;
         } /* if */

      /* Controlar limites de memória */

         if ( LimiteMemoria > 0 )
         {
            if ( LimiteMemoria < EspacoTotalAlocado + ( long ) Tamanho )
            {
               TST_ExibirPrefixo( TIPO_MSG_INFO , "Simula falta de memória." ) ;
               ContaNULL++ ;
               return NULL ;
            } /* if */
         } /* if */

         if ( LimiteNumEspacos > 0 )
         {
            if ( numEspacosAlocados >= LimiteNumEspacos )
            {
               TST_ExibirPrefixo( TIPO_MSG_INFO , "Limita número de espaços alocados." ) ;
               ContaNULL++ ;
               return NULL ;
            } /* if */
         } /* if */

         if ( FrequenciaMalloc > 0 )
         {
            if ( ALT_GerarFrequencia( 1 , &FrequenciaMalloc , LIMITE_FREQUENCIA ) > 0)
            {
               TST_ExibirPrefixo( TIPO_MSG_INFO , "Simulou NULL por freqüência." ) ;
               ContaNULL++ ;
               return NULL ;
            } /* if */
         } /* if */

      /* Alocar o espaço solicitado */

         pEspaco = ( tpElemListaControle * )
                     malloc( sizeof( tpElemListaControle ) + Tamanho -
                             DIM_VALOR ) ;

         if ( pEspaco == NULL )
         {
            TST_ExibirPrefixo( TIPO_MSG_INFO , "Memória real insuficiente." ) ;
            return NULL ;
         } /* if */


         /* Alocar o espaço solicitado */

         pEspaco = ( tpElemListaControle * )
                     malloc( sizeof( tpElemListaControle ) + Tamanho -
                             DIM_VALOR ) ;

         if ( pEspaco == NULL )
         {
            return NULL ;
         }

         EspacoTotalAlocado += Tamanho ;

      /* Inicializar os valores de controle do espaço */

         pEspaco->ImpressaoDigital = IMPRESSAO_DIGITAL ;
         pEspaco->tamTotal         = Tamanho + sizeof( tpElemListaControle ) ;
         pEspaco->idEspaco         = TotalAlocacoes ;
         pEspaco->idTipoValor      = CED_ID_TIPO_VALOR_NULO ;
         pEspaco->ehAtivo          = TRUE ;
         pEspaco->tamValor         = Tamanho ;
         memcpy( pEspaco->ControleAntes ,   CONTROLE  , DIM_CONTROLE ) ;
         memset( pEspaco->Valor ,           CHAR_ALOC , Tamanho ) ;
         memcpy( pEspaco->Valor + Tamanho , CONTROLE  , DIM_CONTROLE ) ;

      /* Inicializar a identificação do código fonte */

         pEspaco->numLinhaFonte = numLinhaFonte ;

         tamNomeArq = strlen( NomeArquivoFonte ) ;
         if ( tamNomeArq >= DIM_NOME_ARQ_FONTE )
         {
            NomeArquivoFonte += ( tamNomeArq - DIM_NOME_ARQ_FONTE + 1 ) ;
         } /* if */
         strcpy( pEspaco->NomeArquivoFonte , NomeArquivoFonte ) ;

      /* Encadear na lista de espaços alocados */

         pEspaco->pAnt      = NULL ;
         pEspaco->pProx     = pOrgLista ;
         if ( pOrgLista != NULL )
         {
            pOrgLista->pAnt = pEspaco ;
         } /* if */
         pOrgLista          = pEspaco ;

         numEspacosAlocados ++ ;
         TotalAlocacoes ++ ;

      return ( void * ) &( pEspaco->Valor ) ;

   } /* Fim pacote: Raiz de CED  &Alocar espaço */

/***************************************************************************
*
*  Fun‡„o: CED  &Desalocar espaço
*
*  Descri‡„o da fun‡„o
*     Elimina o elemento da lista de controle. Todos os bytes são tornados
*     iguais a 'x'. O identificador do tipo do espaço também
*     é destruído, possibilitando verificar se ele ainda está alocado.
*
*     Ao usar esta função deve-se tomar o cuidado de nunca usar free para
*     desalocar um espaço controlado por este módulo.
*     Ou seja, evite o uso de malloc e free em módulos distintos em
*     que malloc está num módulo controlado e free não.
*     O mais seguro é ou ter todos os módulos sob controle, ou ter nenhum.
*
***************************************************************************/

   void CED_Free( void * Ponteiro )
   {

   /* Dados do bloco: Raiz de CED  &Desalocar espaço */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  &Desalocar espaço */

      TST_ASSERT( estaInicializado ) ;

      if ( Ponteiro == NULL )
      {
         TST_ExibirPrefixo( TIPO_MSG_INFO , "Desalocar espaço recebeu ponteiro nulo" ) ;
         return ;
      } /* if */

      pEspaco = ObterOrigemElemento( Ponteiro ) ;
      if ( pEspaco == NULL )
      {
         free( Ponteiro ) ;
         return ;
      } /* if */

      DesalocarEspaco( pEspaco ) ;

   } /* Fim pacote: Raiz de CED  &Desalocar espaço */

/***************************************************************************
*
*  Fun‡„o: CED  &Exibir conteúdo do espaço
*
*  Descri‡„o da fun‡„o
*     Exibe o conteudo completo de um espaço de memória.
*     A parte útil é exibida em formato hexadecimal convencional
*
***************************************************************************/

   void CED_ExibirEspaco( void * Ponteiro )
   {

   /* Dados do bloco: Raiz de CED  &Exibir conteúdo do espaço */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  &Exibir conteúdo do espaço */

      TST_ASSERT( estaInicializado ) ;

      if ( Ponteiro == NULL )
      {
         TST_ExibirPrefixo( TIPO_MSG_INFO , "Exibir espaço recebeu ponteiro nulo." ) ;
         return ;
      } /* if */

      pEspaco = ObterOrigemElemento( Ponteiro ) ;
      if ( pEspaco == NULL )
      {
         return ;
      } /* if */

      ExibirCabecalho( TIPO_MSG_INFO , pEspaco ) ;

      TST_ExibirEspacoHexa( pEspaco->tamValor , pEspaco->Valor ) ;

   } /* Fim pacote: Raiz de CED  &Exibir conteúdo do espaço */

/***************************************************************************
*
*  Fun‡„o: CED  &Exibir todos os espaços
*
*  Descri‡„o da fun‡„o
*     Exibe todos os espaços que satisfazem uma determinada regra.
*     Ver o tipo CED_tpModoExibir para uma explicação quanto às regras
*     de seleção de espaços a exibir.
*        CED_ExibirTodos     - exibe todos os espaços
*        CED_ExibirAtivos    - exibe os espaços marcados ativos
*        CED_ExibirInativos  - exibe os espaços marcados não ativos
*
***************************************************************************/

   void CED_ExibirTodosEspacos( CED_tpModoExibir Regra )
   {

   /* Dados do bloco: Tratar modo de exibir */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  &Exibir todos os espaços */

      TST_ASSERT( estaInicializado ) ;

      pEspaco = pOrgLista ;

      while ( pEspaco != NULL ) {

      /* Tratar modo de exibir */

         switch ( Regra ) {

         /* Exibir todos os espaços */

            case CED_ExibirTodos :
            {

               CED_ExibirEspaco( &( pEspaco->Valor )) ;

               break ;

            } /* fim ativa: Exibir todos os espaços */

         /* Exibir todos os espaços alocados ativos */

            case CED_ExibirAtivos :
            {

               if ( pEspaco->ehAtivo )
               {
                  CED_ExibirEspaco( &( pEspaco->Valor )) ;
               } /* if */

               break ;

            } /* fim ativa: Exibir todos os espaços alocados ativos */

         /* Exibir todos os espaços alocados inativos */

            case CED_ExibirInativos :
            {

               if ( !( pEspaco->ehAtivo ))
               {
                  CED_ExibirEspaco( &( pEspaco->Valor )) ;
               } /* if */

               break ;

            } /* fim ativa: Exibir todos os espaços alocados inativos */

         /* Exibir nada */

            default :
            {

               break ;

            } /* fim ativa: Exibir nada */

         } /* fim seleciona: Tratar modo de exibir */

      /* Avançar para o próximo espaço a exibir */

         pEspaco = pEspaco->pProx ;

      } /* fim repete: Raiz de CED  &Exibir todos os espaços */

   } /* Fim pacote: Raiz de CED  &Exibir todos os espaços */

/***************************************************************************
*
*  Fun‡„o: CED  &Definir tipo do espaço
*
*  Descri‡„o da fun‡„o
*     Caso o tipo do espaço ainda não esteja definido, atribui o tipo.
*
*     O tipo do espaço é inicializado para CED_ID_TIPO_VALOR_NULO
*     quando da alocação com CED_Malloc. Posteriormente pode ser
*     alterado com a presente função.
*
*     A atribuição será realizada somente se uma das condições a seguir
*     for verdadeira:
*     - o tipo a ser atribuido é CED_ID_TIPO_VALOR_NULO
*     - ou o tipo do espaço é CED_ID_TIPO_VALOR_NULO
*
*     Para trocar o tipo de um espaço precisa-se primeiro torná-lo
*     igual a CED_ID_TIPO_VALOR_NULO para, depois, atribuir o novo tipo.
*
*     Uma vez definido o tipo do espaço, funções cliente podem controlar
*     a consistência entre o tipo implicitamente associado ao ponteiro
*     e o tipo que o espaço de fato contém.
*
*     Sugere-se que o desenvolvedor da aplicação crie uma tabela global
*     contendo um "enum" com os nomes de todos os tipos ('typedef struct') que
*     podem ser utilizados como declaradores de espaços dinâmicos.
*     Ao definir o tipo, pode-se, agora, utilizar o nome correspondente
*     ao tipo do espaço alocado como o idTipo a ser definido. Veja
*     as explicações no arquivo IdTiposEspaco.def no subdiretório Tabelas
*
*     O presente sistema de controle de tipos não prevê mecanismos para
*     tratamento de herança.
*
***************************************************************************/

   int CED_DefinirTipoEspaco( void * Ponteiro , int idTipo )
   {

   /* Dados do bloco: Raiz de CED  &Definir tipo do espaço */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  &Definir tipo do espaço */

      TST_ASSERT( estaInicializado ) ;

      if ( Ponteiro == NULL )
      {
         return FALSE ;
      } /* if */

      pEspaco = ObterOrigemElemento( Ponteiro ) ;

      if ( pEspaco == NULL )
      {
         return FALSE ;
      } /* if */

      if ( ( idTipo == CED_ID_TIPO_VALOR_NULO )
        || ( pEspaco->idTipoValor == CED_ID_TIPO_VALOR_NULO ))
      {
         pEspaco->idTipoValor = idTipo ;
         return TRUE ;
      } /* if */

      return FALSE ;

   } /* Fim pacote: Raiz de CED  &Definir tipo do espaço */

/***************************************************************************
*
*  Fun‡„o: CED  &Marcar ativo o espaço
*
*  Descri‡„o da fun‡„o
*     Marca determinado espaço como ativo.
*
*     A marca ativo/não ativo é utilizada para apoiar o controle de
*     vazamento de memória. Siga o seguinte roteiro:
*     - Marque todos os espaços não ativos.
*     - A partir das âncoras, percorra as estruturas ativas marcando
*       ativos os espaços visitados. Este percorrimento é recursivo.
*       Retorna-se da chamada se encontrar um espaço já marcado ativo, ou
*       se não tiver para onde caminhar. Note que para poder fazer isto
*       é necessário conhecer-se o tipo dos dados contidos em cada um
*       dos espaços alocados.
*     - Percorra a lista de todos os espaços verificando se cada espaço
*       visitado é ou não inativo. Os não ativos provavelmente correspondem
*       a vazamento de memória.
*
***************************************************************************/

   void CED_MarcarEspacoAtivo( void * Ponteiro )
   {

   /* Dados do bloco: Raiz de CED  &Marcar ativo o espaço */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  &Marcar ativo o espaço */

      TST_ASSERT( estaInicializado ) ;

      if ( Ponteiro == NULL )
      {
         return ;
      } /* if */

      pEspaco = ObterOrigemElemento( Ponteiro ) ;
      if ( pEspaco == NULL )
      {
         return ;
      } /* if */

      pEspaco->ehAtivo = TRUE ;

   } /* Fim pacote: Raiz de CED  &Marcar ativo o espaço */

/***************************************************************************
*
*  Fun‡„o: CED  &Marcar não ativo o espaço
*
*  Descri‡„o da fun‡„o
*     Ver CED_MarcarEspacoAtivo
*
***************************************************************************/

   void CED_MarcarEspacoNaoAtivo( void * Ponteiro )
   {

   /* Dados do bloco: Raiz de CED  &Marcar não ativo o espaço */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  &Marcar não ativo o espaço */

      TST_ASSERT( estaInicializado ) ;
         
      if ( Ponteiro == NULL )
      {
         return ;
      } /* if */
         
      pEspaco = ObterOrigemElemento( Ponteiro ) ;
      if ( pEspaco == NULL )
      {
         return ;
      } /* if */
         
      pEspaco->ehAtivo = FALSE ;

   } /* Fim pacote: Raiz de CED  &Marcar não ativo o espaço */

/***************************************************************************
*
*  Fun‡„o: CED  &Marcar não ativos todos os espaços
*
*  Descri‡„o da fun‡„o
*     Percorre todos os espaços alocados marcando-os inativos.
*
*     Veja: CED_MarcarEspacoAtivo
*
***************************************************************************/

   void CED_MarcarTodosEspacosInativos( )
   {

   /* Dados do bloco: Raiz de CED  &Marcar não ativos todos os espaços */

      tpElemListaControle * pEspaco ;
         

   /* Raiz de CED  &Marcar não ativos todos os espaços */

      TST_ASSERT( estaInicializado ) ;
         
      pEspaco = pOrgLista ;
      while ( pEspaco != NULL )
      {
         pEspaco->ehAtivo = FALSE ;
         pEspaco = pEspaco->pProx ;
      } /* while */

   } /* Fim pacote: Raiz de CED  &Marcar não ativos todos os espaços */

/***************************************************************************
*
*  Fun‡„o: CED  &Limitar memória disponível
*
*  Descri‡„o da fun‡„o
*     Estabelece um limite de memória disponível. Este limite afeta
*     o comportamento da função CED_Malloc.
*
*     Embora a função possa ser chamada a qualquer momento, recomenda-se
*     que seja chamada antes do primeiro caso de teste capaz de alocar
*     espaço de memória dinâmica por intermédio da função CED_Malloc
*     contida nesse módulo.
*
***************************************************************************/

   void CED_LimitarMemoriaDisponivel( long NovoLimiteMemoria )
   {

   /* Raiz de CED  &Limitar memória disponível */

      TST_ASSERT( estaInicializado ) ;
      TST_ASSERT( NovoLimiteMemoria >= 0 ) ;

      LimiteMemoria = NovoLimiteMemoria ;

   } /* Fim pacote: Raiz de CED  &Limitar memória disponível */

/***************************************************************************
*
*  Fun‡„o: CED  &Limitar número de espaços alocados
*
*  Descri‡„o da fun‡„o
*     Limita o número de espaços alocados. Esta função afeta o comportamento
*     de CED_Malloc, estabelecendo um limite para o número total de
*     espaços alocados em um dado momento.
*
*     Embora a função possa ser chamada a qualquer momento, recomenda-se
*     que seja chamada antes do primeiro caso de teste que provoque
*     alocação de espaço de memória.
*
***************************************************************************/

   void CED_LimitarNumeroTotalEspacos( long numTotalEspacos )
   {

   /* Raiz de CED  &Limitar número de espaços alocados */

      TST_ASSERT( estaInicializado ) ;
      TST_ASSERT( numTotalEspacos >= 0 ) ;

      LimiteNumEspacos = numTotalEspacos ;

   } /* Fim pacote: Raiz de CED  &Limitar número de espaços alocados */

/***************************************************************************
*
*  Fun‡„o: CED  &Limitar com freqüência de geração de NULL
*
*  Descri‡„o da fun‡„o
*     Esta função estabelece a freqüência com a qual não deverá ser
*     gerado NULL, o complemento a esta freqüência é a frequüência com
*     a qual deverá ser retornado NULL (não aloca) independentemente da
*     existência ou não de memória disponível.
*     A função visa apoiar a verificação de se o comportamento de um
*     programa leva em conta os retornos de falta de memória.
*
***************************************************************************/

   int CED_LimitarFrequencia( int Frequencia )
   {

   /* Raiz de CED  &Limitar com freqüência de geração de NULL */

      TST_ASSERT( estaInicializado ) ;

      if ( ( Frequencia <  LIMITE_INF_FREQUENCIA )
        || ( Frequencia >= LIMITE_SUP_FREQUENCIA ))
      {
         return FALSE ;
      } /* if */

      FrequenciaMalloc = Frequencia ;

      return TRUE ;

   } /* Fim pacote: Raiz de CED  &Limitar com freqüência de geração de NULL */

/***************************************************************************
*
*  Fun‡„o: CED  &Limitar, eliminar limites
*
*  Descri‡„o da fun‡„o
*     Esta função elimina todos os limites de memória por ventura em vigor.
*
***************************************************************************/

   void CED_EliminarLimites( )
   {

   /* Raiz de CED  &Limitar, eliminar limites */

      TST_ASSERT( estaInicializado ) ;

      LimiteMemoria        = 0 ;
      LimiteNumEspacos     = 0 ;
      FrequenciaMalloc     = 0 ;

   } /* Fim pacote: Raiz de CED  &Limitar, eliminar limites */

/***************************************************************************
*
*  Fun‡„o: CED  &Obter o tipo do espaço de dados
*
*  Descri‡„o da fun‡„o
*     Retorna o identificador do tipo do espaço apontado.
*
***************************************************************************/

   int CED_ObterTipoEspaco( void * Ponteiro )
   {

   /* Dados do bloco: Raiz de CED  &Obter o tipo do espaço de dados */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  &Obter o tipo do espaço de dados */

      TST_ASSERT( estaInicializado ) ;

      if ( Ponteiro == NULL )
      {
         return CED_PONTEIRO_NULO ;
      } /* if */

      pEspaco = ObterOrigemElemento( Ponteiro ) ;
      if ( pEspaco == NULL )
      {
         return CED_ID_TIPO_ILEGAL ;
      } /* if */

      return pEspaco->idTipoValor ;

   } /* Fim pacote: Raiz de CED  &Obter o tipo do espaço de dados */

/***************************************************************************
*
*  Fun‡„o: CED  &Obter tamanho do valor contido no espaço
*
*  Descri‡„o da fun‡„o
*     Retorna o número de bytes úteis do espaço
*
***************************************************************************/

   int CED_ObterTamanhoValor( void * Ponteiro )
   {

   /* Dados do bloco: Raiz de CED  &Obter tamanho do valor contido no espaço */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  &Obter tamanho do valor contido no espaço */

      TST_ASSERT( estaInicializado ) ;
         
      if ( Ponteiro == NULL )
      {
         return -1 ;
      } /* if */
         
      pEspaco = ObterOrigemElemento( Ponteiro ) ;
      if ( pEspaco == NULL )
      {
         return -1 ;
      } /* if */

      return pEspaco->tamValor ;

   } /* Fim pacote: Raiz de CED  &Obter tamanho do valor contido no espaço */

/***************************************************************************
*
*  Fun‡„o: CED  &Obter número de espaços alocados
*
*  Descri‡„o da fun‡„o
*     Retorna o número de elementos da lista de espaços alocados
*
***************************************************************************/

   int CED_ObterNumeroEspacosAlocados( )
   {

   /* Raiz de CED  &Obter número de espaços alocados */

      TST_ASSERT( estaInicializado ) ;

      return numEspacosAlocados ;

   } /* Fim pacote: Raiz de CED  &Obter número de espaços alocados */

/***************************************************************************
*
*  Fun‡„o: CED  &Obter total de espaços alocados
*
*  Descri‡„o da fun‡„o
*     Retorna o número total de vezes que foi chamada a função
*     CED_Malloc.
*
***************************************************************************/

   int CED_ObterTotalAlocacoes( )
   {

   /* Raiz de CED  &Obter total de espaços alocados */

      TST_ASSERT( estaInicializado ) ;

      return TotalAlocacoes ;

   } /* Fim pacote: Raiz de CED  &Obter total de espaços alocados */

/***************************************************************************
*
*  Fun‡„o: CED  &Obter número total de NULLs gerados
*
*  Descri‡„o da fun‡„o
*     Retorna o número de NULLs retornados em virtude de limitações impostas.
*     Veja as funcoes CED_LimitarXXX
*
***************************************************************************/

   long CED_ObterNumNULL( void )
   {

   /* Raiz de CED  &Obter número total de NULLs gerados */

      TST_ASSERT( estaInicializado ) ;

      return ContaNULL ;

   } /* Fim pacote: Raiz de CED  &Obter número total de NULLs gerados */

/***************************************************************************
*
*  Fun‡„o: CED  &Obter número de espaços segundo regra
*
*  Descri‡„o da fun‡„o
*     Obtém o número de elementos contidos na lista de espaços alocados,
*     segundo a regra:
*        CED_ExibirTodos     - exibe todos os espaços
*        CED_ExibirAtivos    - exibe os espaços marcados ativos
*        CED_ExibirInativos  - exibe os espaços marcados não ativos
*
***************************************************************************/

   int CED_ObterNumeroEspacos( CED_tpModoExibir Regra )
   {

   /* Dados do bloco: Raiz de CED  &Obter número de espaços segundo regra */

      tpElemListaControle * pEspaco ;
      int Conta = 0 ;

   /* Raiz de CED  &Obter número de espaços segundo regra */

      TST_ASSERT( estaInicializado ) ;
               
      pEspaco = pOrgLista ;

      while ( pEspaco != NULL )
      {
         switch ( Regra )
         {
            case CED_ExibirTodos :
               Conta ++ ;
               break ;

            case CED_ExibirAtivos :
               if ( pEspaco->ehAtivo )
               {
                  Conta ++ ;
               } /* if */
               break ;

            case CED_ExibirInativos :
               if ( !( pEspaco->ehAtivo ))
               {
                  Conta ++ ;
               } /* if */
               break ;

            default:
               break ;

         } /* fim switch */

         pEspaco = pEspaco->pProx ;
      } /* while */

      return Conta ;

   } /* Fim pacote: Raiz de CED  &Obter número de espaços segundo regra */

/***************************************************************************
*
*  Fun‡„o: CED  &Obter espaço total alocado
*
*  Descri‡„o da fun‡„o
*     Obtém o total, em bytes, de espaços úteis alocados.
*
***************************************************************************/

   long CDE_ObterEspacoTotalAlocado( )
   {

   /* Raiz de CED  &Obter espaço total alocado */

      TST_ASSERT( estaInicializado ) ;

      return EspacoTotalAlocado ;

   } /* Fim pacote: Raiz de CED  &Obter espaço total alocado */

/***************************************************************************
*
*  Fun‡„o: CED  &Iterador: iniciar iterador de espaços
*
*  Descri‡„o da fun‡„o
*     Inicia o iterador com o primeiro espaço da lista de controle de espaços
*     dinâmicos.
*
*     O iterador pode ser utilizado para verificar a integridade dos
*     espaços de dados sob controle do módulo. Para isto a função de
*     verificação de espaços deve percorrer todos os espaços alocados
*     disparando o controle individual para cada um deles.
*     Pode-se também simular um garbage collector, percorrendo todos
*     os espaços e marca-los inativos. Depois percorrer, a partir
*     das ancoras, todos os espaços adjacentes, marcando ativos os
*     espaços visitados. Evidentemente se já estiver marcado ativo
*     retorna-se para tratar do próximo estado pendente na pilha.
*     Ao final, os espaços que ainda estiverem marcados inativos
*     correspondem a vazamento de memória.
*
***************************************************************************/

   void CED_InicializarIteradorEspacos( )
   {

   /* Raiz de CED  &Iterador: iniciar iterador de espaços */

      TST_ASSERT( estaInicializado ) ;

      pEspacoCorr = pOrgLista ;

   } /* Fim pacote: Raiz de CED  &Iterador: iniciar iterador de espaços */

/***************************************************************************
*
*  Fun‡„o: CED  &Iterador: avançar para o próximo espaço
*
*  Descri‡„o da fun‡„o
*     Avança o iterador para o próximo espaço.
*
***************************************************************************/

   int CED_AvancarProximoEspaco( )
   {

   /* Raiz de CED  &Iterador: avançar para o próximo espaço */

      TST_ASSERT( estaInicializado ) ;

      if ( pEspacoCorr == NULL )
      {
         return FALSE ;
      } /* if */

      pEspacoCorr = pEspacoCorr->pProx ;

      if ( pEspacoCorr != NULL )
      {
         return TRUE ;
      } else {
         return FALSE ;
      } /* if */

   } /* Fim pacote: Raiz de CED  &Iterador: avançar para o próximo espaço */

/***************************************************************************
*
*  Fun‡„o: CED  &Iterador: obter referência para o espaço corrente
*
*  Descri‡„o da fun‡„o
*     Obtém a referência para a parte útil do espaço corrente.
*
***************************************************************************/

   void * CED_ObterPonteiroEspacoCorrente( )
   {

   /* Raiz de CED  &Iterador: obter referência para o espaço corrente */

      TST_ASSERT( estaInicializado ) ;

      if ( pEspacoCorr == NULL )
      {
         return NULL ;
      } /* if */

      return ( void * ) &( pEspacoCorr->Valor ) ;

   } /* Fim pacote: Raiz de CED  &Iterador: obter referência para o espaço corrente */

/***************************************************************************
*
*  Fun‡„o: CED  &Iterador: existe espaço corrente
*
*  Descri‡„o da fun‡„o
*     Verifica se o iterador referencia um espaço corrente.
*     Caso retorne FALSE, o iterador chegou ao final da lista de espaços
*     ou, então, ainda não foi inicializado.
*
***************************************************************************/

   int CED_ExisteEspacoCorrente( )
   {

   /* Raiz de CED  &Iterador: existe espaço corrente */

      TST_ASSERT( estaInicializado ) ;

      if ( pEspacoCorr == NULL )
      {
         return FALSE ;
      } /* if */

      return TRUE ;

   } /* Fim pacote: Raiz de CED  &Iterador: existe espaço corrente */

/***************************************************************************
*
*  Fun‡„o: CED  &Iterador: terminar iterador
*
*  Descri‡„o da fun‡„o
*     Desativa o iterador. A referência para o espáco corrente passa
*     a ser NULL.
*
***************************************************************************/

   void CED_TerminarIteradorEspacos( )
   {

   /* Raiz de CED  &Iterador: terminar iterador */

      pEspacoCorr = NULL ;

   } /* Fim pacote: Raiz de CED  &Iterador: terminar iterador */

/***************************************************************************
*
*  Fun‡„o: CED  &Iterador: excluir espaço corrente
*
*  Descri‡„o da fun‡„o
*     Elimina o espaço corrente da lista de espaços controlados.
*     O espaço é liberado tornando ilegais todos os acessos realizados
*     por funções do usuário.
*     Na realidade esta função corresponde a um CED_Free.
*     Utilize esta função somente para para eliminar espaços sabidamente
*     inativos, ou para deturpar ao testar reações a anomalias em estruturas
*     de dados.
*
***************************************************************************/

   void CED_ExcluirEspacoCorrente( )
   {

   /* Dados do bloco: Raiz de CED  &Iterador: excluir espaço corrente */

      tpElemListaControle * pDesaloca ;

   /* Raiz de CED  &Iterador: excluir espaço corrente */

      TST_ASSERT( estaInicializado ) ;

      if ( pEspacoCorr != NULL )
      {
         pDesaloca   = pEspacoCorr ;
         pEspacoCorr = pEspacoCorr->pProx ;
         DesalocarEspaco( pDesaloca ) ;
      } /* if */

   } /* Fim pacote: Raiz de CED  &Iterador: excluir espaço corrente */

/***************************************************************************
*
*  Fun‡„o: CED  &Verificar se espaço é ativo
*
*  Descri‡„o da fun‡„o
*     Retorna TRUE se o espaço referenciado está marcado ativo
*
***************************************************************************/

   int CED_EhEspacoAtivo( void * Ponteiro )
   {

   /* Dados do bloco: Raiz de CED  &Verificar se espaço é ativo */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  &Verificar se espaço é ativo */

      TST_ASSERT( estaInicializado ) ;

      if ( Ponteiro == NULL )
      {
         return FALSE ;
      } /* if */

      pEspaco = ObterOrigemElemento( Ponteiro ) ;
      if ( pEspaco == NULL )
      {
         return FALSE ;
      } /* if */

      return pEspaco->ehAtivo ;

   } /* Fim pacote: Raiz de CED  &Verificar se espaço é ativo */

/***************************************************************************
*
*  Fun‡„o: CED  &Verificar a integridade de um espaço de dados
*
*  Descri‡„o da fun‡„o
*     Verifica a integridade de um determinado espaço de dados.
*     Retorna o número de falhas encontradas.
*     Esta função pode levar a um cancelamento do programa, caso o ponteiro
*     fornecido esteja errado.
*
***************************************************************************/

   int CED_VerificarEspaco( void * Ponteiro ,
                            int ( * pVerificarValor )( void * pValor ))
   {

   /* Dados do bloco: Raiz de CED  &Verificar a integridade de um espaço de dados */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  &Verificar a integridade de um espaço de dados */

      TST_ASSERT( estaInicializado ) ;

      /* Verificar as referências para o espaço */

         if ( Ponteiro == NULL )
         {
            return TRUE ;
         } /* if */

         pEspaco = ObterOrigemElemento( Ponteiro ) ;

         if ( pEspaco == NULL )
         {
            return FALSE ;
         } /* if */

      /* Verificar o conteúdo do espaço */

         if ( pVerificarValor != NULL )
         {
            if ( pVerificarValor( pEspaco->Valor ) == 0 )
            {
               ExibirMensagem( "Valor contido no espaço está incorreto." ) ;
               ExibirCabecalho( TIPO_MSG_VAZIA , pEspaco ) ;
               fprintf( TST_ObterArqLog( ) , "\n" ) ;
               return FALSE ;
            } /* if */
         } /* if */

      return TRUE ;

   } /* Fim pacote: Raiz de CED  &Verificar a integridade de um espaço de dados */

/***************************************************************************
*
*  Fun‡„o: CED  &Verificar todos os espaços alocados
*
*  Descri‡„o da fun‡„o
*     Percorre toda a lista, verificando um a um os espaços.
*     Caso um ou mais espaços estejam errados, pode ocorrer
*     cancelamento da execução em virtude de acesso a memória ilegal.
*
***************************************************************************/

   int CED_VerificarTudo( int ( * pVerificarValor )( void * pValor ))
   {

   /* Dados do bloco: Raiz de CED  &Verificar todos os espaços alocados */

      tpElemListaControle * pEspaco ;

      int ContaErro   = 0 ,
          ContaEspaco = 0 ;

   /* Raiz de CED  &Verificar todos os espaços alocados */

      TST_ASSERT( estaInicializado ) ;

      /* Verificar toda a lista de espaços */

         pEspaco = pOrgLista ;
         while ( pEspaco != NULL )
         {
            ContaEspaco ++ ;
            if ( ! CED_VerificarEspaco( pEspaco->Valor , pVerificarValor ))
            {
               ContaErro ++ ;
            } /* if */
            pEspaco = pEspaco->pProx ;
         } /* while */

      /* Verificar número de espaços alocados */

         if ( ContaEspaco != numEspacosAlocados )
         {
            ExibirMensagem( "Número de espaços alocados errado." ) ;
            ContaErro ++ ;
         } /* if */

         if ( numEspacosAlocados > TotalAlocacoes )
         {
            ExibirMensagem( "Número de espaços alocados maior do que total alocado." ) ;
            ContaErro ++ ;
         } /* if */

      return ContaErro == 0 ;

   } /* Fim pacote: Raiz de CED  &Verificar todos os espaços alocados */

/***************************************************************************
*
*  Fun‡„o: CED  -Desalocar espaço dado
*
*  Descri‡„o da fun‡„o
*
***************************************************************************/

   void DesalocarEspaco( tpElemListaControle * pEspaco )
   {

   /* Raiz de CED  -Desalocar espaço dado */

      /* Desalocar o espaço apontado */

         if ( pEspaco->pProx != NULL )
         {
            pEspaco->pProx->pAnt  = pEspaco->pAnt ;
         } /* if */

         if ( pEspaco->pAnt != NULL )
         {
            pEspaco->pAnt->pProx = pEspaco->pProx ;
         } else {
            pOrgLista = pEspaco->pProx ;
         } /* if */

         numEspacosAlocados -- ;
         EspacoTotalAlocado -= pEspaco->tamValor ;

      /* Limpar o espaço a liberar */


         memset( pEspaco->ControleAntes , CHAR_DESALOC ,
                 pEspaco->tamValor + DIM_CONTROLE ) ;

         memcpy( pEspaco->ControleAntes + pEspaco->tamValor + DIM_CONTROLE ,
                 CONTROLE_ERRO , DIM_CONTROLE ) ;

         pEspaco->idTipoValor = CED_ID_TIPO_ILEGAL ;
         free( pEspaco ) ;

   } /* Fim pacote: Raiz de CED  -Desalocar espaço dado */

/***************************************************************************
*
*  Fun‡„o: CED  -Obter ponteiro para o elemento da lista de espaços ativos
*
*  Descri‡„o da fun‡„o
*     Retorna o ponteiro para o início do elemento da lista de espaços
*     alocados, no entanto sem controlar a integridade do espáco.
*
***************************************************************************/

   tpElemListaControle * ObterOrigemElemento( void * Ponteiro )
   {

   /* Dados do bloco: Raiz de CED  -Obter ponteiro para o elemento da lista de espaços ativos */

      tpElemListaControle * pEspaco ;

   /* Raiz de CED  -Obter ponteiro para o elemento da lista de espaços ativos */

      TST_ASSERT( Ponteiro != NULL ) ;

      pEspaco = ( tpElemListaControle * )
                  ((( char * ) Ponteiro ) - ( sizeof( tpElemListaControle ) -
                     DIM_VALOR - DIM_CONTROLE )) ;

      if ( pEspaco->ImpressaoDigital != IMPRESSAO_DIGITAL )
      {
         return NULL ;
      } /* if */


      if ( VerificarEspaco( pEspaco ))
      {
         ExibirMensagem(  "Espaço de dados está corrompido." ) ;

         ExibirCabecalho( TIPO_MSG_VAZIA , pEspaco ) ;

         fprintf( TST_ObterArqLog( ) , "\n" ) ;

         return NULL ;
      } /* if */

      return pEspaco ;

   } /* Fim pacote: Raiz de CED  -Obter ponteiro para o elemento da lista de espaços ativos */

/***************************************************************************
*
*  Fun‡„o: CED  -Exibir cabecalho do espaco
*
*  Descri‡„o da fun‡„o
*     Exibe todos os atributos, exceto o valor, contido no espaço.
*
***************************************************************************/

   void ExibirCabecalho( char * TipoMsg , tpElemListaControle * pEspaco )
   {

   /* Dados do bloco: Raiz de CED  -Exibir cabecalho do espaco */

      FILE * pArqLog ;

      int i ;

   /* Dados do bloco: Exibir ponteiro do espaço */

      char * pVal  ;
      char * pChar ;

   /* Raiz de CED  -Exibir cabecalho do espaco */

      pArqLog = TST_ObterArqLog( ) ;

      fprintf( pArqLog , "\n\n%s  Espaço de dados, id: %5d" ,
                  TipoMsg , pEspaco->idEspaco ) ;

      /* Exibir ponteiro do espaço */

         pVal  = pEspaco->Valor ;

         fprintf( pArqLog , "  Ponteiro valor: %p imagem:" , pVal ) ;

         pChar = ( char * ) &pVal ;
         for( i = 0 ; i < DIM_PONTEIRO ; i++ )
         {
            fprintf( pArqLog , " %02X" , pChar[ i ] ) ;
         } /* for */

      /* Exibir identificação do espaço antecessor */

         if ( pEspaco->pAnt != NULL  )
         {
            fprintf( pArqLog , "  Id ant: %5d" , pEspaco->pAnt->idEspaco ) ;
         } else {
            fprintf( pArqLog , "  Origem" ) ;
         } /* if */

      /* Exibir identificação do espaço sucessor */

         if ( pEspaco->pProx != NULL )
         {
            fprintf( pArqLog , "  Id suc: %5d" , pEspaco->pProx->idEspaco ) ;
         } else {
            fprintf( pArqLog , "  Final" ) ;
         } /* if */

      /* Exibir o identificador do tipo do valor */

         if ( pEspaco->idTipoValor != CED_ID_TIPO_VALOR_NULO )
         {
            fprintf( pArqLog , "\n     Id tipo valor: %d" , pEspaco->idTipoValor ) ;
         } else {
            fprintf( pArqLog , "\n     Tipo indefinido" ) ;
         } /* if */

      /* Tamanho útil do valor alocado */

         fprintf( pArqLog , "  Tamanho: %d" , pEspaco->tamValor ) ;

      /* Exibir flag ativo */

         if ( pEspaco->ehAtivo )
         {
            fprintf( pArqLog , "  Ativo" ) ;
         } else {
            fprintf( pArqLog , "  Não ativo" ) ;
         } /* if */

      /* Exibir número da linha de código fonte onde foi alocado */

         fprintf( pArqLog , "  Linha onde alocou: %d" , pEspaco->numLinhaFonte ) ;

      /* Exibir nome do arquivo onde alocou */

         fprintf( pArqLog , "  Arquivo: %s" , pEspaco->NomeArquivoFonte ) ;

      /* Exibir controle antes */

         if ( memcmp( pEspaco->ControleAntes , CONTROLE , DIM_CONTROLE ) == 0 )
         {
            fprintf( pArqLog , "\n     Controle antes OK" ) ;
         } else {
            fprintf( pArqLog , "\n     Controle antes errado:" ) ;
            for( i = 0 ; i < DIM_CONTROLE ; i++ )
            {
               fprintf( pArqLog , " %02X" , pEspaco->ControleAntes[ i ] ) ;
            } /* for */
         } /* if */

      /* Exibir controle após */

         if ( memcmp( pEspaco->ControleApos - DIM_VALOR + pEspaco->tamValor ,
                      CONTROLE , DIM_CONTROLE ) == 0 )
         {
            fprintf( pArqLog , "  Controle após OK" ) ;
         } else {
            fprintf( pArqLog , "  Controle após errado:" ) ;
            for( i = 0 ; i < DIM_CONTROLE ; i++ )
            {
               fprintf( pArqLog , " %02X" , pEspaco->ControleApos[ i ] ) ;
            } /* for */
         } /* if */

   } /* Fim pacote: Raiz de CED  -Exibir cabecalho do espaco */

/***************************************************************************
*
*  Fun‡„o: CED  -Exibir mensagem de erro
*
*  Descri‡„o da fun‡„o
*     Exibe uma mensagem de erro ou advertência no formato padrão
*
***************************************************************************/

   void ExibirMensagem( char * Msg )
   {

   /* Raiz de CED  -Exibir mensagem de erro */

      TST_ContarFalhas( ) ;
      TST_ExibirPrefixo( TIPO_MSG_ERRO , Msg ) ;

   } /* Fim pacote: Raiz de CED  -Exibir mensagem de erro */

/***************************************************************************
*
*  Fun‡„o: CED  -Verificar integridade de determinado espaço
*
*  Descri‡„o da fun‡„o
*     Controla a integridade após conhecer o ponteiro para a origem
*     do espaço. Não controla o campo valor.
*
***************************************************************************/

   int VerificarEspaco( tpElemListaControle * pEspaco )
   {

   /* Dados do bloco: Raiz de CED  -Verificar integridade de determinado espaço */

      int ContaErro = 0 ;

   /* Raiz de CED  -Verificar integridade de determinado espaço */

      /* Verificar id espaço */

         if ( ( pEspaco->idEspaco   < 0 )
           || ( pEspaco->idEspaco   > TotalAlocacoes )
           || ( numEspacosAlocados  > TotalAlocacoes ))
         {
            ContaErro ++ ;
            ExibirMensagem( "Identificação do espaço está errada." ) ;
         } /* if */

      /* Verificar encadeamento origem da lista */

         if ( pOrgLista != NULL )
         {
            if ( pOrgLista->pAnt != NULL )
            {
               ContaErro ++ ;
               ExibirMensagem( "Origem da lista de espaços está errada." ) ;
            } /* if */
         } else {
            ContaErro ++ ;
            ExibirMensagem( "Origem da lista não vazia é NULL." ) ;
            pOrgLista = pEspaco ;
         } /* if */

      /* Verificar encadeamento antes */

         if ( pEspaco != pOrgLista )
         {
            if ( pEspaco->pAnt != NULL )
            {
               if ( pEspaco->pAnt->pProx != pEspaco )
               {
                  ContaErro ++ ;
                  ExibirMensagem( "Encadeamento antes está errado." ) ;
                  pEspaco->pAnt = NULL ;
               } /* if */
            } else {
               ContaErro ++ ;
               ExibirMensagem( "Espáco anterior == NULL, mas não é a origem da lista de espaços." ) ;
            } /* if */
         } else
         {
            if ( pEspaco->pAnt != NULL )
            {
               ContaErro ++ ;
               ExibirMensagem( "Espaço origem da lista está errada." ) ;
               pEspaco->pAnt = NULL ;
            } /* if */
         } /* if */

      /* Verificar encadeamento após */

         if ( pEspaco->pProx != NULL )
         {
            if ( pEspaco->pProx->pAnt != pEspaco )
            {
               ContaErro ++ ;
               ExibirMensagem( "Encadeamento após está errado." ) ;
               pEspaco->pProx = NULL ;
            } /* if */
         } /* if */

      /* Verificar tamanho */

         if ( ( pEspaco->tamTotal != pEspaco->tamValor +
                          ( int ) sizeof( tpElemListaControle ))
           || ( pEspaco->tamValor <= 0 ))
         {
            ContaErro ++ ;
            ExibirMensagem( "Tamanho do espaço está errado." ) ;
         } /* if */

      /* Verificar controle antes */

         if ( memcmp( pEspaco->ControleAntes , CONTROLE , DIM_CONTROLE ) != 0 )
         {
            ContaErro ++ ;
            ExibirMensagem( "Controle de extravasão antes está errado." ) ;
         } /* if */

      /* Verificar controle após */

         if ( memcmp( pEspaco->ControleApos - DIM_VALOR + pEspaco->tamValor ,
                      CONTROLE , DIM_CONTROLE ) != 0 )
         {
            ContaErro ++ ;
            ExibirMensagem( "Controle de extravasão após está errado." ) ;
         } /* if */

      return ContaErro ;

   } /* Fim pacote: Raiz de CED  -Verificar integridade de determinado espaço */

/********** Fim do m¢dulo: CED  Controlador de espaços de dados alocados dinamicamente **********/

