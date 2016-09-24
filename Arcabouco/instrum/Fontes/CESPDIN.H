#if ! defined( CESPDIN_ )
#define CESPDIN_
/***************************************************************************
*
*  $MCD Módulo de definição: CED  Controlador de espaços de dados alocados dinamicamente
*
*  Arquivo gerado:              CESPDIN.h
*  Letras identificadoras:      CED
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
*  $ED Descrição do módulo
*     O módulo de instrumentação CNTESPAC disponibiliza um conjunto de
*     funções para
*     - controlar a extravasão de espaços de dados alocados ao usuário
*     - controlar o acesso a espaços já desalocados
*     - controlar a consistência entre o tipo implicito de um ponteiro e o
*       tipo do espaço por ele apontado
*     - controlar o vazamento de memória
*     - simular ter-se atingido o limite de memória disponível
*     - controlar a integridade da estrutura de espaços de dados dinâmicos
*     - exibir o conteçudo de espaços de dados em formato hexadecimal
*
*  $EIU Interface com o usuário pessoa
*     Para fazer com que um determinado módulo tenha todos os usos de
*     malloc e free controlados, basta incluir o módulo de definição
*     deste módulo. Idealmente use uma construção similar a:
*
*     #ifdef _DEBUG
*        #include "cntespac.h"
*     #endif
*
*     Isto fará com que todas as chamadas malloc e free do módulo controlado
*     sejam direcionadas para as funções equivalentes disponibilizadas
*     pelo presente módulo.
*
*     Para possibilitar a remoção automática da instrumentação
*     circunde todos os usos de funções desse módulo com o
*     comando de compilação condicional #ifdef _DEBUG
*     A recompilação do módulo instrumentado sem o nome _DEBUG
*     definido deveria resultar em zero erros de compilação.
*     Antes de recompilar destrua o correspondente módulo objeto.
*
*     Para o correto funcionamento das funções desse módulo, é necessário
*     que contenha o comando:
*
*     #pragma pack (1)
*
*     Esse comando pode introduzir dependências de plataforma,
*     tornando o módulo não portátil. Nesse caso remova o comando
*     #pragma e faça os ajustes necessários nas massas de teste e no
*     presente módulo de modo que se torne operacional na plataforma
*     desejada.
*
*     Em geral, o sintoma de mal funcionamento após a remoção de #pragma
*     é pequenas extravasões de espaço passarem despercebidas pela
*     instrumentação.
*
***************************************************************************/
 
#if defined( CESPDIN_OWN )
   #define CESPDIN_EXT
#else
   #define CESPDIN_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

#define     CED_PONTEIRO_NULO       -2


/***********************************************************************
*
*  $TC Tipo de dados: CED Modos de exibição
*
*
*  $ED Descrição do tipo
*     Enumera todos os modos de listar espaços alocados
*
***********************************************************************/

   typedef enum {

         CED_ExibirTodos    = 1 ,
               /* Exibir todos os espaços */

         CED_ExibirAtivos   = 2 ,
               /* Exibir todos os espaços ativos */

         CED_ExibirInativos = 3
               /* Exibir todos os espaços inativos */

   } CED_tpModoExibir ;


/***********************************************************************
*
*  $FC Função: CED  &Inicializar o controlador de alocação de espaços dinâmicos
*
*  $ED Descrição da função
*     Esta função inicializa o controlador de espaços em memória dinâmica.
*     A função deve ser chamada uma única vez, antes de qualquer outra função
*     do módulo.
*     Sugere-se que seja chamada ao iniciar o teste do módulo controlado.
*     O interpretador de comandos de controle de espaços dinâmicos
*     provê o comando de teste  =inicializarespacos  que chama a presente
*     função.
*
*  $EP Parâmetros
*     $P pArqLogParm - ponteiro para o arquivo log de teste. Não pode ser nulo.
*
***********************************************************************/

   void CED_InicializarControlador( void ) ;


/***********************************************************************
*
*  $FC Função: CED  &Alocar espaço
*
*  $ED Descrição da função
*     Nos módulos controlados esta função substitui a função "malloc".
*     A susbtituição é transparente para o módulo controlado,
*     basta que inclua o módulo de controle de acesso a espaços de dados
*     dinâmicos. Ou seja, se o módulo de definição "Cntespac.h" for
*     incluido, a presente função será utilizada ao chamar "malloc"
*     dentro do módulo cliente. Não sendo incluido "Cntespac.h", será
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
*     Consulte as funções CED_Limitar... para detalhes das formas de
*     limite que podem ser estabelecidas.
*
*  $EP Parâmetros
*     $P Tamanho          - número de bytes do valor a ser alocado.
*     $P numLinhaFonte    - número da linha do código fonte onde foi
*                           chamada a função. Use __LINE__ como argumento
*                           da chamada.
*     $P NomeArquivoFonte - nome do arquivo fonte contendo a chamada.
*                           Use __FILE__ como argumento da chamada.
*
*  $FV Valor retornado
*     Ponteiro void para o espaço útil disponibilizado para a função
*     cliente. O espaço útil corresponde a o que seria retornado por malloc
*
*  $EIU Interface com usuário pessoa
*     Ao invés de utilizar a função CED_Malloc utilize a macro CED_MALLOC
*     uma vez que esta fornece automáticamente a identificação do local
*     onde foi realizada a chamada.
*
***********************************************************************/

   #define  CED_MALLOC( Tamanho ) \
               CED_Malloc( Tamanho , __LINE__ , __FILE__ )

   void * CED_Malloc( size_t Tamanho ,
                      int    numLinhaFonte ,
                      char * NomeArquivoFonte ) ;


/***********************************************************************
*
*  $FC Função: CED  &Desalocar espaço
*
*  $ED Descrição da função
*     Elimina o elemento da lista de controle. Todos os bytes são tornados
*     iguais a '!' (x21). O identificador do tipo do espaço também
*     é destruído, possibilitando verificar se ele ainda está alocado.
*
*     Ao usar esta função deve-se tomar os seguintes cuidados:
*     - nunca use esta função para desalocar um espaço que não esteja sob
*       controle deste módulo. Ou seja, evite o uso de malloc e free em
*       módulos distintos em que malloc não é controlado e free é.
*     - nunca use free para desalocar um espaço controlado por este módulo.
*       Ou seja, evite o uso de malloc e free em módulos distintos em
*       que malloc é controlado e free não é.
*
*     O mais seguro é ou ter todos os módulos sob controle, ou ter nenhum.
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaço útil) do espaço
*                   a ser liberado
*
***********************************************************************/

   void CED_Free( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Função: CED  &Exibir conteúdo do espaço
*
*  $ED Descrição da função
*     Exibe o conteudo completo de um espaço de memória.
*     A parte útil é exibida em formato hexadecimal convencional
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o valor (parte útil) contido no espaço
*                   alocado, é o ponteiro retornado por CED_Malloc.
*
***********************************************************************/

   void CED_ExibirEspaco( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Função: CED  &Exibir todos os espaços
*
*  $ED Descrição da função
*     Exibe todos os espaços que satisfazem uma determinada regra.
*     Ver o tipo CED_tpModoExibir para uma explicação quanto às regras
*     de seleção de espaços a exibir.
*
***********************************************************************/

   void CED_ExibirTodosEspacos( CED_tpModoExibir Regra ) ;


/***********************************************************************
*
*  $FC Função: CED  &Definir tipo do espaço
*
*  $ED Descrição da função
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
*     as explicações no arquivo IdTiposEspaco.def
*
*     O presente sistema de controle de tipos não prevê mecanismos para
*     tratamentoi de herança.
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaço útil) do espaço
*                   a ser tipado
*     $P idTipo   - novo identificador de tipo a ser dado ao espaço.
*
*  $FV Valor retornado
*     TRUE   1    - se a atribuição foi bem sucedida
*     FALSE  0    - se não foi possível atribuir. Isto será o caso se
*                   o tipo do espáco já estava definido ao chamar a função,
*                   ou se o ponteiro for NULL.
*
***********************************************************************/

   int CED_DefinirTipoEspaco( void * Ponteiro , int idTipo ) ;


/***********************************************************************
*
*  $FC Função: CED  &Marcar ativo o espaço
*
*  $ED Descrição da função
*     Marca determinado espaço como ativo.
*
*     A marca ativo/não ativo é utilizada para apoiar o controle de
*     vazamento de memória. Siga o seguinte roteiro:
*     - Marque todos os espaços não ativos.
*     - Percorra as estruturas ativas marcando ativos os espaços visitados.
*     - Percorra a lista de todos os espaços verificando se cada espaço visitado
*       é ou não inativo.
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaço útil) do espaço
*                   a ser marcado
*
***********************************************************************/

   void CED_MarcarEspacoAtivo( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Função: CED  &Marcar não ativo o espaço
*
*  $ED Descrição da função
*     Ver CED_MarcarEspacoAtivo
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaço útil) do espaço
*                   a ser marcado
*
***********************************************************************/

   void CED_MarcarEspacoNaoAtivo( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Função: CED  &Marcar não ativos todos os espaços
*
*  $ED Descrição da função
*     Percorre todos os espaços alocados marcando-os inativos.
*
***********************************************************************/

   void CED_MarcarTodosEspacosInativos( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Limitar memória disponível
*
*  $ED Descrição da função
*     Estabelece um limite de memória disponível. Este limite afeta
*     o comportamento da função CED_Malloc.
*
*     Embora a função possa ser chamada a qualquer momento, recomenda-se
*     que seja chamada antes do primeiro caso de teste capaz de alocar
*     espaço de memória dinâmica por intermédio da função CED_Malloc
*     contida nesse módulo.
*
*  $EP Parâmetros
*     $P NovoLimiteMemoria - Estabelece o limite de memória disponível.
*                            Caso seja zero, o controle de limite não
*                            será efetuado por CED_Malloc.
*
***********************************************************************/

   void CED_LimitarMemoriaDisponivel( long NovoLimiteMemoria ) ;


/***********************************************************************
*
*  $FC Função: CED  &Limitar número de espaços alocados
*
*  $ED Descrição da função
*     Limita o número de espaços alocados. Esta função afeta o comportamento
*     de CED_Malloc, estabelecendo um limite para o número total de
*     espaços alocados em um dado momento.
*
*     Embora a função possa ser chamada a qualquer momento, recomenda-se
*     que seja chamada antes do primeiro caso de teste que provoque
*     alocação de espaço de memória.
*
*  $EP Parâmetros
*     $P numTotalEspacos - indica o limite de espaços que podem estar
*                          alocados a cada instante. Se zero, não
*                          será realizado o controle.
*
***********************************************************************/

   void CED_LimitarNumeroTotalEspacos( long numTotalEspacos ) ;


/***********************************************************************
*
*  $FC Função: CED  &Limitar, eliminar limites
*
*  $ED Descrição da função
*     Esta função elimina todos os limites de memória por ventura em vigor.
*
***********************************************************************/

   void CED_EliminarLimites( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Obter o tipo do espaço de dados
*
*  $ED Descrição da função
*     Retorna o identificador do tipo do espaço apontado.
*     Será CED_ID_TIPO_ESPACO_NULO se nunca foi atribuído um tipo ao espaço
*     e será CED_ID_TIPO_ILEGAL se o espaço já havia sido liberado.
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaço útil) do espaço
*                   do qual se deseja saber o tipo
*
***********************************************************************/

   int CED_ObterTipoEspaco( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Função: CED  &Obter tamanho do valor contido no espaço
*
*  $ED Descrição da função
*     Retorna o número de bytes úteis do espaço
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para a porção útil do espaço
*                   da qual se deseja saber o tamanho
*
***********************************************************************/

   int CED_ObterTamanhoValor( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Função: CED  &Obter número de espaços alocados
*
*  $ED Descrição da função
*     Retorna o número de espaços contidos na lista de espaços alocados
*
***********************************************************************/

   int CED_ObterNumeroEspacosAlocados( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Obter total de espaços alocados
*
*  $ED Descrição da função
*     Retorna o número total de vezes que foi chamada a função
*     CED_Malloc.
*
***********************************************************************/

   int CED_ObterTotalAlocacoes( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Obter número de espaços segundo regra
*
***********************************************************************/

   int CED_ObterNumeroEspacos( CED_tpModoExibir Regra ) ;


/***********************************************************************
*
*  $FC Função: CED  &Obter espaço total alocado
*
*  $ED Descrição da função
*     Obtém o total em bytes de espaços úteis alocados.
*
***********************************************************************/

   long CDE_ObterEspacoTotalAlocado( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Iterador: iniciar iterador de espaços
*
*  $ED Descrição da função
*     Inicia o iterador com o primeiro espaço da lista de controle de espaços
*     dinâmicos.
*
***********************************************************************/

   void CED_InicializarIteradorEspacos( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Iterador: avançar para o próximo espaço
*
*  $ED Descrição da função
*     Avança o iterador para o próximo espaço.
*
*  $FV Valor retornado
*     TRUE  caso o espaco para o qual caminhou existe.
*     FALSE se não existe iterador ou chegou ao fim da lista de espaços
*
***********************************************************************/

   int CED_AvancarProximoEspaco( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Iterador: obter referência para o espaço corrente
*
*  $ED Descrição da função
*     Obtém a referência para a parte útil do espaço corrente.
*
***********************************************************************/

   void * CED_ObterPonteiroEspacoCorrente( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Iterador: existe espaço corrente
*
*  $ED Descrição da função
*     Verifica se o iterador referencia um espaço corrente.
*
***********************************************************************/

   int CED_ExisteEspacoCorrente( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Iterador: terminar iterador
*
*  $ED Descrição da função
*     Desativa o iterador. Deixa de existir a referência para o espáco corrente.
*
***********************************************************************/

   void CED_TerminarIteradorEspacos( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Iterador: excluir espaço corrente
*
*  $ED Descrição da função
*     Elimina o espaço corrente da lista de espaços controlados.
*     O espaço é liberado tornando ilegais todos os acessos realizados
*     por funções do usuário. Utilize esta função somente para deturpar, ou
*     para eliminar espaços sabidamente inativos.
*
***********************************************************************/

   void CED_ExcluirEspacoCorrente( ) ;


/***********************************************************************
*
*  $FC Função: CED  &Verificar se espaço é ativo
*
*  $ED Descrição da função
*     Retorna TRUE se o espaço referenciado está marcado ativo
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaço útil) do espaço
*                   do qual se deseja saber se é ativo ou não
*
***********************************************************************/

   int CED_EhEspacoAtivo( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Função: CED  &Verificar a integridade de um espaço de dados
*
*  $ED Descrição da função
*     Verifica a integridade de um determinado espaço de dados.
*     Retorna o número de falhas encontradas.
*     Esta função pode levar a um cancelamento por erro, caso o ponteiro
*     fornecido esteja errado.
*
*  $EP Parâmetros
*     $P Ponteiro para a porção útil do espaço. Este é o ponteiro
*                 retornado pela função CED_Malloc
*     $P int pVerificarValor( void * pValor )
*                 função fornecida pelo cliente para verificar a corretude
*                 do espaço útil. A função recebe como parâmetro um
*                 ponteiro para o espaço a verificar e retorna
*                 0 caso o espaço não esteja correto e != 0 se estiver
*                 correto. Todas as mensagens de erro devem ser dadas
*                 pela função de verificação. Procure utilizar as
*                 funções do módulo TESTEGEN para exibir as mensagens
*                 e realizar as comparações.
*                 Caso não deseje verificar o valor, forneça NULL como
*                 argumento.
*
*  $FV Valor retornado
*     TRUE   se espaço é válido ou o ponteiro for NULL
*     FALSE  caso contrário
*
***********************************************************************/

   int CED_VerificarEspaco( void * Ponteiro ,
                            int ( * pVerificarValor )( void * pValor )) ;


/***********************************************************************
*
*  $FC Função: CED  &Verificar todos os espaços alocados
*
*  $ED Descrição da função
*     Percorre toda a lista, verificando um a um os espaços.
*     Caso um ou mais espaços estejam errados, pode ocorrer
*     cancelamento da execução em virtude de acesso a memória ilegal.
*
*  $EP Parâmetros
*     $P pVerificarValor - é o ponteiro para uma função que verifica o conteúdo
*                          do espaço útil. O parâmetro pValor dessa função
*                          apontará para o valor a ser controlado
*
*  $FV Valor retornado
*     TRUE   se todos os espaços estão válidos
*     FALSE  caso contrário
*
***********************************************************************/

   int CED_VerificarTudo( int ( * pVerificarValor )( void * pValor )) ;

/***********************************************************************

/* Código final do módulo */

#if !defined( CESPDIN_OWN )
   #define malloc CED_MALLOC
   #define free   CED_Free
#endif

#undef CESPDIN_EXT

/********** Fim do módulo de definição: CED  Controlador de espaços de dados alocados dinamicamente **********/

#else
#endif
