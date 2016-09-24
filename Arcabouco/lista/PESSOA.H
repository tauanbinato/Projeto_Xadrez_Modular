#if ! defined( PESSOA_ )
#define PESSOA_
/***************************************************************************
*
*  $MCD Módulo de definição: PES  Estrutura de uma Pessoa
*
*  Arquivo gerado:              PESSOA.h
*  Letras identificadoras:      PES
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PESSOA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Tauan Binato , Julia Aleixo , Lucas Palma
*
*  $ED Descrição do módulo
*     Implementa uma estrutura de pessoa com nome e iniciais
*
*
***************************************************************************/
 
#if defined( PESSOA_OWN )
   #define PESSOA_EXT
#else
   #define PESSOA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Estrutura de pessoa */

typedef struct infonome Infonome;

/***********************************************************************
*
*  $TC Tipo de dados: PES Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções
*
***********************************************************************/

   typedef enum {

         PES_CondRetOK ,
               /* Concluiu corretamente */

         PES_CondRetEstruturaVazia ,
               /* A lista não contém elementos */

         PES_CondRetFimEstrutura ,
               /* Foi atingido o fim de lista */

         PES_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         PES_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento de lista */

		 PES_CondRetStringDiferente
			   /* Faltou memória ao tentar criar um elemento de lista */

   } PES_tpCondRet ;

     /***********************************************************************
*
*  $FC Função: &Criar Estrutura
*
*  $ED Descrição da função
*     Aloca dinamicamente uma nova estrutura inicializando suas entidades com null.
*
*  $EP Parâmetros
*     pessoa    - ponteiro duplo para uma estrutura.
*                 
*
*  $FV Valor retornado
*     PES_CondRetOK   - criou corretamente
*	  PES_CondRet_FaltouMemoria  - Houve problema na alocação de memoria.
*      
***********************************************************************/

   PES_tpCondRet PES_Criar_Estrutura(Infonome **pessoa);

   /***********************************************************************
*
*  $FC Função: &Preencher estrutura
*
*  $ED Descrição da função
*     Vai na estrutura de valor e preenche com os parametros de string.
*
*  $EP Parâmetros
*     nome      - nome completo da pessoa
*     iniciais  - iniciais da mesma pessoa
*                 
*
*  $FV Valor retornado
*     PES_CondRetOK   - Preencheu corretamente
*	  PES_CondRet_FaltouMemoria  - Houve problema na alocação de memoria.
*      
***********************************************************************/

   PES_tpCondRet PES_preencher_estrutura(Infonome **pessoa,char *nome, char *iniciais);

   /***********************************************************************
*
*  $FC Função: &Obter Valor Iniciais
*
*  $ED Descrição da função
*     Vai na estrutura retornando por referencia uma inicial.
*
*  $EP Parâmetros
*     strIni      - ponteiro para string iniciais
*     pValor      - ponteiro para estrutura Infonome
*                 
*  $FV Valor retornado
*     PES_CondRetOK   - Obteve corretamente
*	  PES_CondRetEstruturaVazia  - Houve problema na alocação de memoria.
*      
***********************************************************************/
   PES_tpCondRet PES_ObterValorIniciais( char **strIni , Infonome *pValor );

/***********************************************************************
*
*  $FC Função: &Obter Valor Nome
*
*  $ED Descrição da função
*     Vai na estrutura retornando por referencia um nome.
*
*  $EP Parâmetros
*     strIni      - ponteiro para string nome
*     pValor      - ponteiro para estrutura Infonome
*                 
*  $FV Valor retornado
*     PES_CondRetOK   - Obteve corretamente
*	  PES_CondRetEstruturaVazia  - Houve problema na alocação de memoria.
*      
***********************************************************************/
   PES_tpCondRet PES_ObterValorNome( char **strNome , Infonome *pValor );

#undef PESSOA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif