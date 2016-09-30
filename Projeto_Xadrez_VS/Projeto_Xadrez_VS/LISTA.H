#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor        Data          Observações
*     5       lp,ja, tb 28/nov/2016   alteração de funções e edição do scrpit de teste
*     4       avs       01/fev/2006   criar linguagem script simbólica
*     3       avs       08/dez/2004	  uniformização dos exemplos
*     2       avs       07/jul/2003	  unificação de todos os módulos em um só projeto
*     1       avs       16/abr/2003	  início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia = 2 ,
               /* A lista não contém elementos */

         LIS_CondRetListaNaoExiste,
               /* Lista não existe */

         LIS_CondRetFimLista ,
               /* Foi atingido o final da lista */

		 LIS_CondRetInicioLista,
			   /*Foi atingido o início da lista */

         LIS_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma cabeça de lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     pLista        - ponteiro de ponteiro para a estrutura do tipo LIS_tpLista*
*					  a ser criada.
*
*     idLista       - string de identificação da lista
*
*
*  $FV Valor retornado
*     Se executou corretamente retorna a condição de retorno LIS_CondRetOK.
*     
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     LIS_CondRetFaltouMemoria.
*
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista(LIS_tppLista pLista, char* idLista);

/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*
*  $FV Valor retornado
*     LIS_CondRetOK                - destruiu sem problemas
*     LIS_CondRetListaNaoExiste    - lista nao existe
*
***********************************************************************/

   LIS_tpCondRet LIS_DestroiLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Obter Id
*
*  $ED Descrição da função
*     Obtem o Id contido dentro da cabeça da Lista passada
*
*  $EP Parâmetros
*     pLista  - ponteiro para a cabeça a ser encontrado o Id
*	  idLista - ponteiro para identificacao da Id da lista
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterId(LIS_tppLista pLista, char *idLista);

/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir No
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirNo( LIS_tppLista pLista ,
                                          void * pValor        )
       ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir no corrente
*
*  $ED Descrição da função
*     Exclui o elemento do no corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirNoCorrente( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o caracter contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o caracter contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista     - ponteiro para a lista de onde se quer o valor
*     CharObtido - referência para o char a ser passado pela função
*
*  $FV Valor retornado
*     LIS_CondRetOK             - se o elemento corrente existe
*     LIS_CondRetListaVazia     - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterNo(LIS_tppLista pLista, char *CharObtido) ;


/***********************************************************************
*
*  $FC Função: LIS  &AvancarElementoCorrente
*
*  $ED Descrição da função
*     Avança o elemento corrente um elemento na lista
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK         - se um elemento tiver sido andado
*     CondRetFimLista   - se encontrou o fim da lista antes de andar um elemento
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista) ;


/***********************************************************************
*
*  $FC Função: LIS  &Voltar Elemento Corrente
*
*  $ED Descrição da função
*     Volta o elemento corrente um elemento na lista
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*     CondRetOK            - se um elemento tiver sido voltado
*     CondRetInicioLista   - se encontrou o inicio da lista antes de voltar um elemento
*     CondRetListaVazia    - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_VoltarElementoCorrente(LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Alterar no corrente
*
*  $ED Descrição da função
*     Altera o elemento o caracter contido no elemento corrente
*	  para o fornecido na função
*
*  $EP Parâmetros
*     pLista   - ponteiro para a lista a ser manipulada
*     CharDado - caracter fornecido
*
*  $FV Valor retornado
*     CondRetOK               - se o caracter for alterado com sucesso
*     CondRetListaNaoExiste   - se a lista não existe
*     CondRetListaVazia       - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AlterarElementoCorrente(LIS_tppLista pLista, char CharDado);

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/                 

#else
#endif
