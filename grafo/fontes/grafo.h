typedef struct GRA_tagGrafo * GRA_tppGrafo ;

typedef enum {

         GRA_CondRetOK ,
               /* Concluiu corretamente */

         GRA_CondRetGrafoVazio ,
               /* o grafo não contém elementos */


   } GRA_tpCondRet ;
GRA_tpCondRet GRA_Cria( GRA_tppGrafo* grafo ,int max_nodes );
GRA_tpCondRet   GRA_InsereNo ( GRA_tppGrafo* grafo, void * pInfo);
GRA_tpCondRet  GRA_InsereAresta( GRA_tppGrafo* grafo, int node_i, int node_j, float cost, char direction);
GRA_tpCondRet  GRA_Imprime(GRA_tppGrafo* graph);
