#pragma once
#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Matriz de listas duplamente encadeadas
*
*  Arquivo gerado:              TABULEIRO.h
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Julia Aleixo , Lucas Palma , Tauan Binato
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tbf   26/set/2016 início desenvolvimento.
*
*  $ED Descrição do módulo
*
*
***************************************************************************/

#if defined( TABULEIRO_OWN )
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do Tabuleiro
*
***********************************************************************/

typedef enum {

	TAB_CondRetOK,
	/* Concluiu corretamente  = 0*/

	TAB_CondRetListaVazia,
	/* A lista não contém elementos = 1 */

	TAB_CondRetFimLista,
	/* Foi atingido o fim de lista  = 2*/

	TAB_CondRetNaoAchou,
	/* Não encontrou o valor procurado = 3*/

	TAB_CondRetFaltouMemoria
	/* Faltou memória ao tentar criar um elemento de lista = 4 */

} TAB_tpCondRet;

/* 
------FUNÇÕES NÃO PRONTAS DO TAUAN--------

-Função InserirPeca – Receberá a coordenada linha-coluna, o identificador da peça a ser inserida e a sua cor.
 Crie os retornos necessários inclusive prevendo a colocação da peça em uma coordenada inexistente.
-Função MoverPeca –a coordenada de origem e a coordenada de destino. Esta função deverá verificar se a peça poderá executar este movimento e se capturará uma peça de outra cor.
 Caso isso aconteça, a peça oponente será retirada do tabuleiro.  Crie os retornos necessários.
-Função RetirarPeca – Receberá uma coordenada linha-coluna e a peça contida nesta casa será retirada. Crie os retornos necessários. 
-Função ObterPeca – Receberá uma coordenada linha-coluna e retornará a identificação da peça <Nome , Cor>.

*/

TAB_tpCondRet inserirPeca();
TAB_tpCondRet moverPeca();
TAB_tpCondRet retirarPeca();
TAB_tpCondRet obterPeca();



/*
------FUNÇÕES NÃO PRONTAS DA JULIA--------

-Função ObterListaAmeacantes – Receberá uma coordenada linha-coluna e retornará o ponteiro para a correspondente cabeça de lista.
 Não se esqueça de projetar uma forma de operar sobre esta lista no módulo de teste.
-Função ObterListaAmeacados – Receberá uma coordenada linha-coluna e retornará o ponteiro para a correspondente cabeça de lista.
-Função DestruirTabuleiro – destrói o conteúdo de cada casa do tabuleiro e o próprio tabuleiro, caso este tenha sido alocado em memória dinâmica.
 Obs. no 4º. trabalho será examinado se ocorre vazamento de memória. 
*/

TAB_tpCondRet obterListaAmeacantes();
TAB_tpCondRet obterListaAmeacados();
TAB_tpCondRet destruirTabuleiro();


/***********************************************************************
*
*  $FC Função: TAB  &Criar Tabuleiro
*
*  $ED Descrição da função
*     Cria uma ancora que aponta para o inicio de uma lista e coluna de tamanho fixo
*     Cria uma lista duplamente encadeada com um identificador para representar a linha de uma matriz	
*	  Cria uma lista duplamente encadeada com um identificador para representar a coluna de uma matriz	
*
*  $EP Parâmetros
*     linha         - ponteiro de ponteiro para a estrutura do tipo LIS_tpLista*
*					  a ser criada.
*
*	  coluna        - ponteiro de ponteiro para a estrutura do tipo LIS_tpLista*
*					  a ser criada.
*
*	  ancora_matriz - ponteiro de ponteiro para uma estrutura do tipo TAB_ancoraTabuleiro
*
*     idMatriz       - string de identificação da matriz
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

TAB_tpCondRet cria_tabuleiro(LIS_tppLista linha, LIS_tppLista coluna, TAB_ancoraTabuleiro **ancora_matriz, char * idMatriz);



#undef TABULEIRO_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro **********/

#else
#endif