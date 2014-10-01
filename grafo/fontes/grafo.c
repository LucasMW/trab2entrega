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

   struct GRA_arestaGrafo{
   
   GRA_noGrafo noApontado;

   int verticeId;
   
   };
   typedef struct GRA_arestaGrafo* GRA_tpAresta;

   int visitados[1000];

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
int dfs(GRA_tppGrafo grafo, GRA_noGrafo node_i, int node_j)
{
	int ret = 0;
	GRA_tpAresta aresta;
	do{
		aresta = (GRA_tpAresta)LIS_ObterValor(node_i->listaArestas);
		if (aresta->verticeId == node_j )
			return 1;
		if (visitados[aresta->verticeId] == 0){
			visitados[aresta->verticeId] = 1;
			ret = dfs(grafo,aresta->noApontado,node_j);
		}

	}while(LIS_AvancarElementoCorrente( grafo->pOrigens ,1 )!=LIS_CondRetFimLista); 
	
	return ret;
}
static void AtualizaConexos( GRA_tppGrafo grafo, int node_i, int node_j, int addOrTake)
{
	int qtdNos = 0, i, flagVisitados, flagOrigens = 0;
	GRA_noGrafo noExterno;
	GRA_tpAresta noInterno;

	if (addOrTake){

	LIS_IrInicioLista(grafo->pOrigens);

	do{
		noExterno = (GRA_noGrafo)LIS_ObterValor(grafo->pOrigens);
		if (noExterno->verticeId == node_i || noExterno->verticeId == node_j)
			flagOrigens++;
	}while(LIS_AvancarElementoCorrente( grafo->pOrigens ,1 )!=LIS_CondRetFimLista);

	if (flagOrigens == 2){
		LIS_IrInicioLista(grafo->pOrigens);

	do{
		noExterno = (GRA_noGrafo)LIS_ObterValor(grafo->pOrigens);
		if (noExterno->verticeId == node_i || noExterno->verticeId == node_j)
			LIS_ExcluirElemento(grafo->pOrigens);
	}while(LIS_AvancarElementoCorrente( grafo->pOrigens ,1 )!=LIS_CondRetFimLista);
	}
	}else{
		LIS_IrInicioLista(grafo->pOrigens);
		do{
		noExterno = (GRA_noGrafo)LIS_ObterValor(grafo->pOrigens);
		if (noExterno->verticeId == node_i )
		break;
	}while(LIS_AvancarElementoCorrente( grafo->pOrigens ,1 )!=LIS_CondRetFimLista);
		
		if (!dfs(grafo, noExterno, node_j)){

		do{
		noExterno = (GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if (noExterno->verticeId == node_j)
			break;
	}while(LIS_AvancarElementoCorrente( grafo->pOrigens ,1 )!=LIS_CondRetFimLista);
		LIS_IrFinalLista( grafo->pOrigens);
		LIS_InserirElementoApos( grafo->pOrigens , noExterno);
		}				
	}
	
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
	GRA_EsvaziarGrafo(grafo);
	LIS_DestruirLista(grafo->pOrigens);
	grafo->pOrigens=NULL;
	LIS_DestruirLista(grafo->pVertices);
	grafo->pVertices=NULL;
	free(grafo);
	grafo=NULL; //never be acessed again
	return GRA_CondRetOK;
}


GRA_tpCondRet   GRA_InserirNo ( GRA_tppGrafo grafo, void * pInfo, int * pNoId)
{
	/* Todo nó adicionado, como não tem aresta é uma nova componente conexa */
	GRA_noGrafo novoNo, novaOrigem;
	
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
	novaOrigem=(GRA_noGrafo)malloc(sizeof(struct GRA_verticeGrafo));
	if(!novoNo)
		return GRA_CondRetFaltouMemoria;
	novoNo->verticeId=id;
	novoNo->pInfo=pInfo;
	novaOrigem->verticeId = id;
	novaOrigem->pInfo=pInfo;
	if(LIS_CriarLista(&novoNo->listaArestas,free)==LIS_CondRetFaltouMemoria)
		return GRA_CondRetFaltouMemoria;
	LIS_InserirElementoApos(grafo->pVertices,novoNo); //cria nova elementolista na lista de nós representando esse vértice
	LIS_InserirElementoApos(grafo->pOrigens,novaOrigem); //Linka a componenteconexa ao novo nó sem arestas
	*pNoId = id;
	return GRA_CondRetOK;
}
GRA_tpCondRet  GRA_InserirAresta( GRA_tppGrafo grafo, int node_i, int node_j)
{
	int i = 0, j = 0;
	GRA_noGrafo  noOrigem, noDestino;
	GRA_tpAresta aresta1, aresta2, noTemp;
	aresta1= (GRA_tpAresta)malloc(sizeof(struct GRA_arestaGrafo));
	aresta2= (GRA_tpAresta)malloc(sizeof(struct GRA_arestaGrafo));
	
	if (!IdExisteJa(grafo, node_j))
		return GRA_CondRetNoNaoExiste;
	if  (!IdExisteJa(grafo, node_i))
		return GRA_CondRetNoNaoExiste;

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
		noTemp = (GRA_tpAresta)LIS_ObterValor(noOrigem->listaArestas);
		if (noTemp == NULL)
			break;
		if (noTemp->verticeId == noDestino->verticeId){
		return GRA_CondRetArestaJaExiste;
		}
	}while(LIS_AvancarElementoCorrente( noOrigem->listaArestas ,1 )!=LIS_CondRetFimLista);

	aresta1->verticeId = noDestino->verticeId;
	aresta1->noApontado = noDestino;	

	LIS_InserirElementoApos(noOrigem->listaArestas,aresta1);
	
	LIS_IrInicioLista(noDestino->listaArestas);

	do{
		noTemp = (GRA_tpAresta)LIS_ObterValor(noDestino->listaArestas);
		if (noTemp == NULL)
			break;
		if (noTemp->verticeId == noOrigem->verticeId){

		return GRA_CondRetArestaJaExiste;
		}
	}while(LIS_AvancarElementoCorrente( noDestino->listaArestas ,1 )!=LIS_CondRetFimLista);
	
	aresta2->verticeId = noOrigem->verticeId;
	aresta2->noApontado = noOrigem;

	LIS_InserirElementoApos(noDestino->listaArestas, aresta2);
	/*AtualizaConexos(grafo, node_i, node_j,1);*/
	

	return GRA_CondRetOK;
}

GRA_tpCondRet  GRA_ExcluirAresta( GRA_tppGrafo grafo, int node_i, int node_j)
{
	int i = 0, j = 0, flag = 0;
	GRA_noGrafo  noOrigem, noDestino;
	GRA_tpAresta noComp;
	
	if (!IdExisteJa(grafo, node_j))
		return GRA_CondRetNoNaoExiste;
	if  (!IdExisteJa(grafo, node_i))
		return GRA_CondRetNoNaoExiste;

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
	LIS_IrInicioLista(noDestino->listaArestas);
	do{
		noComp = (GRA_tpAresta)LIS_ObterValor(noOrigem->listaArestas);
		if (noComp == NULL)
			break;
		if (noComp->verticeId == noDestino->verticeId){
			LIS_ExcluirElemento( noOrigem->listaArestas );
			flag = 1;
			break;
		}
	}while(LIS_AvancarElementoCorrente( noOrigem->listaArestas ,1 )!=LIS_CondRetFimLista);
	
	if (flag == 0)
		return GRA_CondRetArestaNaoExiste;
	flag = 0;
	

	do{
		noComp = (GRA_tpAresta)LIS_ObterValor(noDestino->listaArestas);
		if (noComp == NULL)
			break;
		if (noComp->verticeId == noOrigem->verticeId){
		LIS_ExcluirElemento( noDestino->listaArestas );
		flag = 1;
		break;
		}
	}while(LIS_AvancarElementoCorrente( noDestino->listaArestas ,1 )!=LIS_CondRetFimLista);
	
	if (flag == 0)
		return GRA_CondRetArestaNaoExiste;
	/*AtualizaConexos(grafo, node_i, node_j,0);*/
	return GRA_CondRetOK;
}
GRA_tpCondRet  GRA_ImprimirGrafo(GRA_tppGrafo grafo)
{
	/* vá em cada vértice e imprima suas componentes conexas */
	GRA_noGrafo p; //percorredor
	GRA_tpAresta acs;  //percorredor
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
				
				acs=(GRA_tpAresta)LIS_ObterValor(l);
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

	
	LIS_EsvaziarLista(grafo->pOrigens);
	LIS_EsvaziarLista(grafo->pVertices);
	

	return GRA_CondRetOK;
}

static void imprimirOrigens (GRA_tppGrafo grafo){
	
	GRA_noGrafo no;
	do{
		LIS_IrInicioLista(grafo->pOrigens);
		no = (GRA_noGrafo)LIS_ObterValor(grafo->pOrigens);
		printf("%d\n",no->verticeId);

	}while(LIS_AvancarElementoCorrente(grafo->pOrigens,1)!=LIS_CondRetFimLista);
}
GRA_tpCondRet GRA_ObterValorNo(GRA_tppGrafo grafo, int noId,void** endVar)
{
	GRA_noGrafo no;
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return  GRA_CondRetGrafoVazio;
	do 
	{   no=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(no->verticeId==noId)
		{ /* Achou */
			*endVar=no->pInfo;
			return GRA_CondRetOK;
		}
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	/* Nao Achou */
	return GRA_CondRetNoNaoExiste;
}


