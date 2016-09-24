#if ! defined( ARVORE_ )
#define ARVORE_
/***************************************************************************
*
*  $MCD Módulo de definição: ARV  Módulo árvore
*
*  Arquivo gerado:              ARVORE.H
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
*  $ED Descrição do módulo
*     Este módulo exemplifica como utilizar os instrumentos disponibilizados
*     pelo arcabouço.
*     O módulo implementa um conjunto de funções para criar e explorar
*     um conjunto de zero ou mais árvores binárias.
*     Cada árvore possui uma cabeça que referencia o nó raiz e um
*     nó corrente pertencente à árvore.
*     Cada árvore é identificada pela referência (ponteiro) para a sua
*     cabeça.
*     Uma árvore poderá estar vazia, ou seja conter zero nós.
*     Uma árvore vazia não contém nem raiz nem nó corrente.
*
***************************************************************************/
 
#if defined( ARVORE_OWN )
   #define ARVORE_EXT
#else
   #define ARVORE_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: ARV Condições de retorno
*
*
***********************************************************************/

   typedef enum {

         ARV_CondRetOK = 0 ,
               /* Executou correto */

         ARV_CondRetNaoCriouRaiz = 1 ,
               /* Não criou nó raiz */

         ARV_CondRetErroEstrutura = 2 ,
               /* Estrutura da árvore está errada */

         ARV_CondRetNaoEhFolha = 3 ,
               /* Não é folha relativa à direção de inserção desejada */

         ARV_CondRetArvoreNaoExiste = 4 ,
               /* Árvore não existe */

         ARV_CondRetArvoreVazia = 5 ,
               /* Árvore está vazia */

         ARV_CondRetNohEhRaiz = 6 ,
               /* Nó corrente é raiz */

         ARV_CondRetNaoPossuiFilho = 7 ,
               /* Nó corrente não possui filho na direção desejada */

         ARV_CondRetFaltouMemoria = 8
               /* Faltou memória ao alocar dados */

   } ARV_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: ARV Modos de deturpar
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

         DeturpaTipoCabeca        =  1 ,
               /* Modifica o tipo da cabeça */

         DeturpaRaizNula          =  2 ,
               /* Anula ponteiro raiz */

         DeturpaCorrenteNulo      =  3 ,
               /* Anula ponteiro corrente */

         DeturpaRaizLixo          =  4 ,
               /* Faz raiz apontar para lixo */

         DeturpaCorrenteLixo      =  5 ,
               /* Faz corrente apontar para lixo */

         DeturpaTipoNo            =  6 ,
               /* Modifica tipo nó corrente */

         DeturpaPtCabecaNulo      =  7 ,
               /* Anula ponteiro cabeça */

         DeturpaPtPaiNulo         =  8 ,
               /* Anula ponteiro pai */

         DeturpaPtEsqNulo         =  9 ,
               /* Anula ponteiro filho esquerda */

         DeturpaPtDirNulo         = 10 ,
               /* Anula ponteiro filho direita */

         DeturpaPtCabecaLixo      = 11 ,
               /* Faz ponteiro cabeça apontar para lixo */

         DeturpaPtPaiLixo         = 12 ,
               /* Faz ponteiro pai apontar para lixo */

         DeturpaPtEsqLixo         = 13 ,
               /* Faz ponteiro filho esquerda apontar para lixo */

         DeturpaPtDirLixo         = 14 ,
               /* Faz ponteiro filho direita apontar para lixo */

         DeturpaValor             = 15 ,
               /* Atribui valor de tamanho 1 byte maior do que o alocado */

         DeturparEspacoCabeca     = 16 ,
               /* Deturpa espaço da cabeca */

         DeturparEspacoNo         = 17
               /* Deturpa espaço do nó */

   } ARV_tpModosDeturpacao ;

#endif


/***********************************************************************
*
*  $FC Função: ARV  &Criar árvore
*
*  $ED Descrição da função
*     Cria uma nova árvore vazia.
*
*  $EP Parâmetros
*     $P pArvoreParm - parâmetro passado por referência e que receberá
*                      o ponteiro para a árvore criada.
*                      Se o ponteiro for não NULL, a árvore apontada
*                      será destruída antes de criar a nova.
*                      Receberá NULL se não conseguiu alocar a cabeça.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_CriarArvore( void ** ppArvoreParm ) ;


/***********************************************************************
*
*  $FC Função: ARV  &Destruir árvore
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da árvore.
*     Faz nada caso a árvore corrente não exista.
*
*  $EP Parâmetros
*     $P pArvoreParm - referência para o ponteiro para a cabeça da árvore
*                      a ser destruída. Ao sair receberá NULL.
*                      Se == NULL, faz nada
*
***********************************************************************/

   void ARV_DestruirArvore( void ** ppArvoreParm ) ;


/***********************************************************************
*
*  $FC Função: ARV  &Adicionar filho à esquerda
*
*  $ED Descrição da função
*     Adiciona um nó folha à esquerda do nó corrente. O nó corrente
*     não deve ter filho à esquerda ao chamar a função,
*
*  $EP Parâmetros
*     $P pArvoreParm - ponteiro para a cabeça da árvore.
*                      Se a árvore estiver vazia, é criado o nó raiz.
*                      Se for NULL, retorna ARV_CondRetArvoreNaoExiste
*     $P ValorParm   - valor a ser inserido no novo nó
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetNaoEhFolha      - caso o nó corrente não seja folha para a
*                                  esquerda
*     ARV_CondRetErroEstrutura
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_InserirEsquerda( void * pArvoreParm , char ValorParm ) ;


/***********************************************************************
*
*  $FC Função: ARV  &Adicionar filho à direita
*
*  $ED Descrição da função
*     Adiciona um nó folha à direita do nó corrente. O nó corrente
*     não deve ter filho à direita ao chamar a função,
*
*  $EP Parâmetros
*     $P pArvoreParm - ponteiro para a cabeça da árvore.
*                      Se a árvore estiver vazia, é criado o nó raiz.
*                      Se for NULL, retorna ARV_CondRetArvoreNaoExiste
*     $P ValorParm   - valor a ser inserido no novo nó
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetNaoEhFolha      - caso o nó corrente não seja folha para a
*                                  direita
*     ARV_CondRetNaoEhFolha      - caso não seja folha para a direita
*     ARV_CondRetErroEstrutura
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_InserirDireita( void * pArvoreParm , char ValorParm ) ;


/***********************************************************************
*
*  $FC Função: ARV  &Ir para nó pai
*
*  $ED Descrição da função
*     Torna corrente o nó pai do nó corrente.
*     Faz nada se este for a raiz da árvore, ou se árvore estiver vazia.
*
*  $EP Parâmetros
*     $P pArvoreParm - ponteiro para a cabeça da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNohEhRaiz
*
***********************************************************************/

   ARV_tpCondRet ARV_IrPai( void * pArvoreParm ) ;


/***********************************************************************
*
*  $FC Função: ARV  &Ir para nó à esquerda
*
*  $ED Descrição da função
*     Torna corrente o nó filho à esquerda do nó corrente.
*     Faz nada se não existe filho à esquerda, ou se a árvore estiver vazia.
*
*  $EP Parâmetros
*     $P pArvoreParm - ponteiro para a cabeça da árvore.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - nó corrente não possui filho à esquerda
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoEsquerda( void * pArvoreParm ) ;


/***********************************************************************
*
*  $FC Função: ARV  &Ir para nó à direita
*
*  $ED Descrição da função
*     Torna corrente o nó filho à direita do nó corrente.
*     Faz nada se não existe filho à direita.
*
*  $EP Parâmetros
*     $P pArvoreParm - ponteiro para a cabeça da árvore.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - nó corrente não possui filho à direita
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoDireita( void * pArvoreParm ) ;


/***********************************************************************
*
*  $FC Função: ARV  &Obter valor corrente
*
*  $ED Descrição da função
*     Retorna o valor contido no nó corrente da árvore dada.
*     Não altera o parâmetro de retorno (retorna nada) se a árvore
*     estiver vazia.
*
*  $EP Parâmetros
*     $P pArvoreParm - ponteiro para a cabeça da árvore.
*     $P ValorParm   - é o parâmetro que receberá o valor contido no nó.
*                      Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ARV_ObterValorCorr( void * pArvoreParm , char * ValorParm ) ;


/***********************************************************************
*
*  $FC Função: ARV  &Verificar uma árvore
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica completamente uma determinada árvore.
*     Também marca todos os espaços por ela ocupados.
*
***********************************************************************/

#ifdef _DEBUG

   ARV_tpCondRet ARV_VerificarArvore( void * pArvoreParm ) ;

#endif


/***********************************************************************
*
*  $FC Função: ARV  &Verificar um nó cabeça
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica a integridade de um nó cabeça da árvore.
*
*  $EP Parâmetros
*     $P pCabecaParm - ponteiro para um espaço que deveria ser uma cabeça
*                      de árvore.
*
*  $FV Valor retornado
*     Condição de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   ARV_tpCondRet ARV_VerificarCabeca( void * pCabecaParm ) ;

#endif


/***********************************************************************
*
*  $FC Função: ARV  &Verificar um nó de estrutura
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica a integridade de um nó estrutural da árvore.
*
*  $EP Parâmetros
*     $P pNoParm - ponteiro para espaço que deveria ser um nó estrutural.
*
*  $FV Valor retornado
*     Número de erros encontrados.
*
***********************************************************************/

#ifdef _DEBUG

   ARV_tpCondRet ARV_VerificarNo( void * pNoParm ) ;

#endif


/***********************************************************************
*
*  $FC Função: ARV  &Deturpar árvore
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Corrompe elementos específicos da estrutura da árvore.
*     Essa função destina-se a preparar os cenários de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da árvore.
*     Esta função não tem proteção contra erros de uso, consequentemente
*     poderá levar o programa a ser cancelado pelo sistema operacional.
*
*  $EP Parâmetros
*     $P pArvoreParm  - árvore a ser deturpada
*     $P ModoDeturpar - identifica como deve ser feita a deturpação
*                       ARV_tpModosDeturpacao identifica os modos de
*                       deturpação conhecidos
*
***********************************************************************/

#ifdef _DEBUG

   void ARV_Deturpar( void * pArvoreParm ,
                      ARV_tpModosDeturpacao ModoDeturpar ) ;

#endif

#undef ARVORE_EXT

/********** Fim do módulo de definição: ARV  Módulo árvore **********/

#else
#endif
