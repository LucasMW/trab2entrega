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
static int IdExisteJa(GRA_tppGrafo grafo,int id)
{	GRA_noGrafo p;
	LIS_IrInicioLista(grafo->pVertices);
	p=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
	if(p->verticeId==id)
		return 1; // EXISTE
	while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista)
	{	
		p=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		//printf("<id %d, pvid %d>\n",id,p->verticeId);
		if(p->verticeId==id)
			return 1; //EXISTE


	}
	return 0; //NAO EXISTE
}
static int VerificaVisitados ( int * visitados, int qtdNos)
{
	int i = 0;
	for ( i; i<qtdNos; i++){
		if (visitados[i] == 0)
			return 0;
	}
	return 1;
}
static void AtualizaConexos( GRA_tppGrafo grafo)
{
	int visitados[1000], qtdNos = 0, i, flagVisitados;
	GRA_noGrafo noExterno,noInterno;
	LIS_IrInicioLista(grafo->pVertices);
	while(LIS_AvancarElementoCorrente( grafo->pVertices ,1 )!=LIS_CondRetFimLista)
		qtdNos++;
	for( i = 0; i < qtdNos ; i++)
		visitados[i] = 0;
	while(LIS_AvancarElementoCorrente( grafo->pOrigens ,1 )!=LIS_CondRetFimLista){
		noExterno = (GRA_noGrafo)LIS_ObterValor(grafo->pOrigens);
	while(LIS_AvancarElementoCorrente( noExterno->listaArestas ,1 )!=LIS_CondRetFimLista)
	{
		noInterno = (GRA_noGrafo)LIS_ObterValor(noExterno->listaArestas);
		visitados[noInterno->verticeId] = 1;
	}
	if (VerificaVisitados(visitados,qtdNos))
	{
		flagVisitados = 1;
	break;
	}
}
	if (flagVisitados)
	{
		LIS_ProcurarValor( grafo->pOrigens , noExterno );
		while(LIS_AvancarElementoCorrente( grafo->pVertices ,1 )!=LIS_CondRetFimLista)
			LIS_ExcluirElemento( grafo->pVertices );
	}
}
GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo* refgrafo)
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
	GRA_noGrafo novoNo;
	
	int id=1; //ids começam em 1
		if(LIS_IrFinalLista(grafo->pVertices)!=LIS_CondRetListaVazia)
		{	
			while(IdExisteJa(grafo,id))
			{	id++;
				//printf("id: %d\t",id);
			}	//Garantirá que id sera sempre diferente
		}
		else
			id=1; //ids começam em 1
    novoNo=(GRA_noGrafo)malloc(sizeof(struct GRA_verticeGrafo)); //cria nó
	if(!novoNo)
		return GRA_CondRetFaltouMemoria;
	novoNo->verticeId=id;
	novoNo->pInfo=pInfo;
	if(LIS_CriarLista(&novoNo->listaArestas,free)==LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	LIS_InserirElementoApos(grafo->pVertices,novoNo); //cria nova elementolista na lista de nós representando esse vértice
	LIS_InserirElementoApos(grafo->pOrigens,novoNo); //Linka a componenteconexa ao novo nó sem arestas
	return GRA_CondRetOK;
}
GRA_tpCondRet  GRA_InserirAresta( GRA_tppGrafo grafo, int node_i, int node_j, float cost, char direction)
{
	int i = 0, j = 0;
	GRA_noGrafo  noOrigem, noDestino, noComp;
	
	if (!IdExisteJa(grafo, node_j))
		return GRA_CondRetNoNaoExiste;
	if  (!IdExisteJa(grafo, node_i))
		return GRA_CondRetNoNaoExiste;;

	LIS_IrInicioLista(grafo->pVertices);	
	
	do{
		noOrigem=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(noOrigem->verticeId==node_i)
			break; //EXISTE
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

	LIS_IrInicioLista(grafo->pVertices);

	do{
		noDestino=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(noDestino->verticeId==node_j)
			break; //EXISTE
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

	LIS_IrInicioLista(noOrigem->listaArestas);

	do{
		noComp = (GRA_noGrafo)LIS_ObterValor(noOrigem->listaArestas);
		if (noComp == NULL)
			break;
		if (noComp->verticeId == noDestino->verticeId){
		return GRA_CondRetArestaJaExiste;
		}
	}while(LIS_AvancarElementoCorrente( noOrigem->listaArestas ,1 )!=LIS_CondRetFimLista);
		
	LIS_InserirElementoApos(noOrigem->listaArestas,noDestino);
	
	LIS_IrInicioLista(noDestino->listaArestas);

	do{
		noComp = (GRA_noGrafo)LIS_ObterValor(noDestino->listaArestas);
		if (noComp == NULL)
			break;
		if (noComp->verticeId == noOrigem->verticeId){

		return GRA_CondRetArestaJaExiste;
		}
	}while(LIS_AvancarElementoCorrente( noDestino->listaArestas ,1 )!=LIS_CondRetFimLista);
		
	LIS_InserirElementoApos(noDestino->listaArestas,noOrigem);
	
	AtualizaConexos(grafo);
	return GRA_CondRetOK;
}
GRA_tpCondRet  GRA_ImprimirGrafo(GRA_tppGrafo grafo)
{
	/* vá em cada vértice e imprima suas componentes conexas */
	GRA_noGrafo p,acs; //percorredor
	LIS_tppLista l; //percorredor
	printf("\n");
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	do
	{
		p=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		printf("Vertice %d Arestas: ",p->verticeId);
		l=p->listaArestas;
		if(LIS_IrInicioLista(l)!=LIS_CondRetListaVazia)
		{
			printf("{ ");
			do 
			{
				
				acs=(GRA_noGrafo)LIS_ObterValor(l);
				printf("%d ",acs->verticeId);
			
			}while(LIS_AvancarElementoCorrente(l,1)!=LIS_CondRetFimLista);
			printf("} ");
		}
		else
			printf("NADA");
		printf("\n");
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

		

	return GRA_CondRetOK;
}
GRA_tpCondRet GRA_EsvaziarGrafo( GRA_tppGrafo grafo )
{
	GRA_noGrafo noTemp;
	if (LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return GRA_CondRetGrafoVazio;
	do{
		noTemp=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		LIS_EsvaziarLista(noTemp->listaArestas);
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);

	LIS_EsvaziarLista(grafo->pVertices);
	LIS_EsvaziarLista(grafo->pOrigens);

	return GRA_CondRetOK;
}
