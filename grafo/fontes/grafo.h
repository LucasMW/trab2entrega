typedef struct GRA_tagGrafo * GRA_tppGrafo ;

typedef enum {

         GRA_CondRetOK ,
               /* Concluiu corretamente */
		 GRA_CondRetFaltouMemoria ,
		      /* Não há memória pra alocar */
         GRA_CondRetGrafoVazio ,
               /* o grafo não contém elementos */


   } GRA_tpCondRet ;
/***********************************************************************
*
*  $FC Função: GRA  &Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo genérico composto de lista de componentes conexas e e uma lista de vertices
*     Os possíveis tipos de elementos armazenados nos nós do grafo são desconhecidos a priori
*     Esta função apenas inicializa as listas de componentes conexas (vértices e Comp Conexas) 
*
*  $EP Parâmetros
*	  grafo			- endereço ponteiro para a cabeça do grafo a ser gerado, a ser retornado por referência
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo nó
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retornará a GRA_CondRetOK
*     
*
*     Se ocorreu alguma alocação de memória não conseguir ser realizada
*     a função retornará GRA_CondRetFaltouMemoria.
*    
*
***********************************************************************/
GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo* grafo);

/***********************************************************************
*
*  $FC Função: GRA  &Destruir grafo
*
*  $ED Descrição da função
*     
*
*  $EP Parâmetros
*	  grafo			- endereço ponteiro para a cabeça do grafo a ser destruido
*
*  $FV Valor retornado
*     Se executou corretamente retorna por referência o ponteiro para o grafo e retornará
*	  a GRA_CondRetOK
*     
*
*     Se ocorreu alguma alocação de memória não conseguir ser realizada
*     a função retornará GRA_CondRetFaltouMemoria.
*    
*
***********************************************************************/


GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo* grafo );


GRA_tpCondRet   GRA_InsereNo ( GRA_tppGrafo* grafo, void * pInfo);
GRA_tpCondRet   GRA_ExcluiNo ( GRA_tppGrafo* grafo, int no);
GRA_tpCondRet  GRA_InserirAresta( GRA_tppGrafo* grafo, int no_i, int no_j, float cost, char direction);
GRA_tpCondRet  GRA_ExcluirAresta (GRA_tppGrafo* grafo, int no_i, int no_j);
GRA_tpCondRet GRA_EsvaziarGrafo( GRA_tppGrafo* grafo );
GRA_tpCondRet  GRA_ImprimirGrafo(GRA_tppGrafo* graph);
