/*

$MCI Módulo de implementação: Grafo feito a partir de listas duplamente encadeadas
Letras identificadoras: GRF

*/

#include <stdio.h>
#include "lista.h"
#include "grafo.h"

/* $TC Tipo de dados: Vértice do grafo */

typedef struct vertice{
  
	ElemLista * VerticeAtual;
	CabLista Arestas;

} Vertice ;

/* $TC Tipo de dadis: Cabeça do grafo; contem lista de todos os vértices */
typedef struct cabecagrafo{
	
	Vertice * VerticeAtual;
	CabLista TodosVertices;

} CabGrafo ;


/* Função: Cria grafo */
CabGrafo * GRF_cria_grafo (){
	CabGrafo * grafo = (CabGrafo *) malloc (sizeof(CabGrafo));
	grafo->VerticeAtual->VerticeAtual = NULL;
	grafo->TodosVertices = NULL;
	return grafo;
} /* Fim da função: Cria grafo */

/* Função: Destroi grafo */
GRF_cond_ret GRF_destroi_grafo(CabGrafo * grafo){
	LIS_destroi_lista(grafo->TodosVertices);
	LIS_destroi_lista(grafo->VerticeAtual->Arestas);
	//grafo->VerticeAtual->VerticeAtual->info = NULL;
	//grafo->VerticeAtual->VerticeAtual->ElemProx = NULL;
	//grafo->VerticeAtual->VerticeAtual->ElemAnt = NULL;
	return GRF_OK;
} /* Fim da função: Destroi grafo */


/* Função: Vai para um determinado vértice */
GRF_cond_ret * GRF_ir_vertice(CabLista * lst_vertices, (void *) info) {

	Vertice * pVertice;
	if (lst_vertices->ElemCorrente->info == NULL)
		return GRF_VAZIO; 

	for (pVertice = lst_vertices->OrigemLista; pVertice != NULL; pVertice = pVertice->ElemProx) {
		if (pVertice == info) {
			lst_vertices->ElemCorrente = pVertice;
			return GRF_OK;
		}
	}
	
} /* Fim da função: Vai para vértice */

/* Função: Obtem vértice corrente */
Vertice * GRF_obter_corrente (CabGrafo * grafo) {

	return grafo->VerticeAtual;
} /* Fim da função: Obtem corrente */

/* Função: Cria vértice */
GRF_cond_ret * GRF_criar_vertice(CabGrafo *pGrafo, CabLista * pVizinhos, void * pInfo) {
Vertice * vertice = (Vertice *) malloc (sizeof(Vertice));

	if (vertice == NULL) {
		return GRF_FALTA_MEM;
	} /* if */
	if (pGrafo == NULL) {
		return GRF_VAZIO;
	} /* if */
	if (info == NULL) {
		return GRF_INF_VAZIO;
	} /* if */

vertice->VerticeAtual->info = pInfo;
pGrafo->TodosVertices->FimLista->ElemProx = vertice;
pVizinhos->ElemCorrente = pVizinhos->OrigemLista;

	while(pVizinhos->ElemCorrente != NULL){

		GRF_cria_aresta(pVizinhos->ElemCorrente->info, vertice);
		pVizinhos->ElemCorrente = pVizinhos->ElemCorrente->ElemProx;
	} /* while */
} /* Fim da função: Cria vértice */

/* Função: Cria aresta; ligação entre 2 vértices */
GRF_cond_ret GRF_cria_aresta (Vertice * pVertice1, Vertice * pVertice2) {

	if ((pVertice1 == NULL) || (pVertice2 == NULL)) {
		return GRF_VERT_VAZIO; 
	} /* if */

	pVertice1->Arestas->FimLista->ElemProx = pVertice2;
	pVertice2->Arestas->FimLista->ElemProx = pVertice1;
	 	if((pVertice1->Arestas->FimLista->ElemProx == NULL) || (pVertice2->Arestas->FimLista->ElemProx == NULL)) {
			return GRF_???;
		} /* if */
	return GRF_OK
} /* Fim da função: Cria aresta */

/* Função: Destroi aresta */
	/**************** incompleta *****************/
GRF_cond_ret GRF_destroi_aresta (Vertice * pVertice1, Vertice * pVertice2) {

	 GRF_ir_vertice(CabGrafo * grafo, pVertice1); 
	 GRF_ir_vertice(CabGrafo * grafo, pVertice2);

} /* Fim da função: Destroi aresta */
