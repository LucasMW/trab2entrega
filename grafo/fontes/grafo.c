/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo Genérico (implementado por listas)
*
*  Arquivo gerado:              grafo.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Lucas Menezes (LM); Lorenzo Saraiva (LS); Felipe Santos(FS).
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       LM   22/SET/2014 início desenvolvimento

***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


#define GRA_OWN
#include "grafo.h"
#undef GRA_OWN



/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de grafo
*
*
***********************************************************************/

   typedef struct GRA_tagGrafo {

         LIS_tppLista  pOrigens ;
               /* Ponteiro para a cabeça da lista de origens*/

         LIS_tppLista  pVertices ;
               /* Ponteiro para a cabeça da lista de vértices*/

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } GRA_tpGrafo ;

   struct GRA_verticeGrafo
   {
	   int verticeId;
			/* id único que identifica aquele vértice */
	   void *pInfo;
		   /* ponteiro para a Informação armazenada no vértice */
	   LIS_tppLista listaArestas;
			/* Ponteiro para a Lista de Adjacências de cada vértice */
   };
   typedef struct GRA_verticeGrafo* GRA_noGrafo;


GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo* refgrafo ,int max_nodes )
{
	GRA_tpGrafo* tempgraf;
	tempgraf=(GRA_tpGrafo*)malloc(sizeof(GRA_tpGrafo));
	if(!tempgraf)
		return  GRA_CondRetFaltouMemoria;
	if(LIS_CriarLista(&tempgraf->pOrigens,free)!=LIS_CondRetOK)
		return GRA_CondRetFaltouMemoria;
	if(LIS_CriarLista(&tempgraf->pVertices,free)!=LIS_CondRetOK)
		return GRA_CondRetFaltouMemoria;
	/* Não houve problemas , retorne OK */
	*refgrafo=tempgraf; //return by reference
	return GRA_CondRetOK;
}
GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo grafo )
{
	
	LIS_DestruirLista(grafo->pOrigens);
	grafo->pOrigens=NULL;
	LIS_DestruirLista(grafo->pVertices);
	grafo->pVertices=NULL;
	free(grafo);
	grafo=NULL; //never be acessed again
	return GRA_CondRetOK;
}
GRA_tpCondRet   GRA_InserirNo ( GRA_tppGrafo grafo, void * pInfo, int* pNoId)
{
	/* Todo nó adicionado, como não tem aresta é uma nova componente conexa */
	

	GRA_noGrafo novoNo=(GRA_noGrafo)malloc(sizeof(struct GRA_verticeGrafo)); //cria nó
	LIS_IrInicioLista(grafo->pVertices);

	while(LIS_AvancarElementoCorrente( grafo->pVertices ,1 )!=LIS_CondRetFimLista)
		
	LIS_InserirElementoApos(grafo->pVertices,novoNo); //cria nova coisa na lista de nós

	return GRA_CondRetOK;
}
GRA_tpCondRet  GRA_InserirAresta( GRA_tppGrafo grafo, int node_i, int node_j, float cost, char direction)
{
	return GRA_CondRetOK;
}
GRA_tpCondRet  GRA_ImprimirGrafo(GRA_tppGrafo graph)
{
	return GRA_CondRetOK;
}
GRA_tpCondRet GRA_EsvaziarGrafo( GRA_tppGrafo grafo )
{
	return GRA_CondRetOK;
}
