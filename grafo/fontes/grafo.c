/***************************************************************************
*  $MCI M�dulo de implementa��o: GRA  Grafo Gen�rico (implementado por listas)
*
*  Arquivo gerado:              grafo.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Lucas Menezes (LM); Lorenzo Saraiva (LS); Felipe Santos(FS).
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       LM   22/SET/2014 in�cio desenvolvimento

***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


#define GRA_OWN
#include "grafo.h"
#undef GRA_OWN



/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabe�a de grafo
*
*
***********************************************************************/

   typedef struct GRA_tagGrafo {

         LIS_tppLista  pOrigens ;
               /* Ponteiro para a cabe�a da lista de origens*/

         LIS_tppLista  pVertices ;
               /* Ponteiro para a cabe�a da lista de v�rtices*/

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

   } GRA_tpGrafo ;

   struct GRA_verticeGrafo
   {
	   int verticeId;
			/* id �nico que identifica aquele v�rtice */
	   void *pInfo;
		   /* ponteiro para a Informa��o armazenada no v�rtice */
	   LIS_tppLista listaArestas;
			/* Ponteiro para a Lista de Adjac�ncias de cada v�rtice */
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
	/* N�o houve problemas , retorne OK */
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
	/* Todo n� adicionado, como n�o tem aresta � uma nova componente conexa */
	

	GRA_noGrafo novoNo=(GRA_noGrafo)malloc(sizeof(struct GRA_verticeGrafo)); //cria n�
	LIS_IrInicioLista(grafo->pVertices);

	while(LIS_AvancarElementoCorrente( grafo->pVertices ,1 )!=LIS_CondRetFimLista)
		
	LIS_InserirElementoApos(grafo->pVertices,novoNo); //cria nova coisa na lista de n�s

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
