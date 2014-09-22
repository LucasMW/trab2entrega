typedef struct GRA_tagGrafo * GRA_tppGrafo ;

typedef enum {

         GRA_CondRetOK ,
               /* Concluiu corretamente */

         GRA_CondRetGrafoVazio ,
               /* o grafo não contém elementos */


   } GRA_tpCondRet ;
/***********************************************************************
*
*  $FC Função: GRA  &Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo genérico composto de lista de componentes conexas e e uma lista de vertices
*     Os possíveis tipos de elem armazenados nos nós do grafo são desconhecidos a priori
*     A tipagem é implicita.
*     Não existe identificador de tipo associado ao grafo?
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/
GRA_tpCondRet GRA_Cria( GRA_tppGrafo* grafo ,int max_nodes );
GRA_tpCondRet   GRA_InsereNo ( GRA_tppGrafo* grafo, void * pInfo);
GRA_tpCondRet  GRA_InsereAresta( GRA_tppGrafo* grafo, int node_i, int node_j, float cost, char direction);
GRA_tpCondRet  GRA_Imprime(GRA_tppGrafo* graph);
