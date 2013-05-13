/*

$MCI Módulo de implementação: Lista duplamente encadeada 
Letras identificadoras: LIS

*/

#include <stdio.h>
#include "lista.h"

/* $TC Tipo de dados: Elemento da lista */

typedef struct elemlista {

	(void *) info; /* Ponteiro do tipo void para a informação contida no elemento, que pode ter qualquer tipo */
	ElemLista * ElemProx; /* Ponteiro para próximo elemento da lista */
	ElemLista * ElemAnt; /* Ponteiro para elemento anterior da lista */

} ElemLista ;

/* $TC Tipo de dados: Cabeça da lista */

typedef struct cablista {

	ElemLista * OrigemLista; /* Ponteiro para a origem da lista */
	ElemLista * FimLista; /* Ponteiro para o fim da lista */
	ElemLista * ElemCorrente; /* Ponteiro para elemento corrente */	
	int NumElem; /* Numero total de elementos na lista */
	void (* excluir_valor) (void * valor) /* Ponteiro para função que exclui um valor de qualquer tipo */

} CabLista ;


   static void liberar_elemento (CabLista lst, ElemLista * pElem) ;

   static ElemLista * cria_elemento(CabLista lst, (void *) valor) ;

   static void limpar_cabeca(CabLista lst) ;


/* Função: Insere um novo elemento antes do elemento corrente na lista */

LIS_cond_ret LIS_insere_antes (CabLista * lst, (void *) valor) {

	ElemLista * pElem;
	pElem = cria_elemento (lst, valor);

	/*Checagem: Se vazia, a lista fica com um unico elemento, o que acaba de ser inserido */
	if (lst->ElemCorrente == NULL) {
		lst->OrigemLista = pElem;
		lst->FimLista = pElem;
	} 

	else {

		if (lst->ElemCorrente->ElemAnt != NULL) {
			pElem->ElemAnt = lst->ElemCorrente->ElemAnt;
			lst->ElemCorrente->ElemAnt->ElemProx = pElem;
		}

		else {
			lst->OrigemLista = pElem;
		} /* if */

		pElem->ElemProx = lst->ElemCorrente;
		lst->ElemCorrente->ElemAnt = pElem;
	} /* if */

	lst->ElemCorrente = pElem;

	return LIS_OK;

} /* Fim da função: Inserir elemento antes */

/* Função: Insere um novo elemento depois do elemento corrente */	

LIS_cond_ret LIS_insere_depois (CabLista * lst, (void *) valor) {

	ElemLista * pElem;
	pElem = cria_elemento (lst, valor)

	/* Se não houver um elemento, a lista fica com um único elemento; o que foi inserido, que se torna a origem e o fim da lista */
	if (lst->ElemCorrente == NULL) {
		lst->OrigemLista = pElem;
		lst->FimLista = pElem;
	} /* if */

	else {

		if (lst->ElemCorrente->ElemProx != NULL) {
			pElem->ElemProx = lst->ElemCorrente->ElemProx;
			lst->ElemCorrente->ElemProx->ElemAnt = pElem;
		}

		else {
			lst->FimLista = pElem;
		} /* if */

		pElem->ElemAnt = lst->ElemCorrente;
		lst->ElemCorrente->ElemProx = pElem;
	} /* if */

	lst->ElemCorrente = pElem;
	return LIS_OK;

} /* Fim da função: Insere elemento depois */  


/* Função: Cria lista duplamente encadeada */

CabLista LIS_cria_lista (void (*excluir_valor), (void * dado)) {

	CabLista * lst = NULL;
	lst = (CabLista *)malloc(sizeof(CabLista));
	if (lst == NULL) {
		return NULL;
	} /* if */
	limpar_cabeca(lst);
	lst->excluir_valor = excluir_valor;
	return lst;
	
} /* Fim da função: Criar lista*/


/* Função: Busca elemento e o retorna */

ElemLista * LIS_busca (ElemLista * lst, (void *) valor) {

	ElemLista * pElem; /* Ponteiro para o elemento */
	for (pElem = lst; pElem != NULL; pElem = pElem->ElemProx) {
		if (pElem->info == valor) {
			return pElem;
		} /* if */
	} /* for */
	return NULL;
} /* Fim da função: Busca elemento */

/* Função: Retira um elemento da lista */

ElemLista * LIS_retira_elemento (ElemLista * lst, (void *) valor) {

	ElemLista * pElem = LIS_busca(lst, valor);
	/* Checa se elemento está na lista */
	if (pElem == NULL) { /* Testa se é o primeiro */
		return lst;
	} /* if */
	
	if (lst == pElem) {
		lst = pElem->ElemProx;
	}
	else {
		pElem->ElemAnt->ElemProx = pElem->ElemProx;
	} /* if  */

	if (pElem->ElemProx != NULL) { /* Testa se é o último */
		pElem->ElemProx->ElemAnt = pElem->ElemAnt;
	} /* if */
	/* Retira elemento e libera a variável de ponteiro, pElem */
	free (pElem);
	return lst;
} /* Fim da função: Retira um elemento */

/* Função: Cria um elemento */

ElemLista * cria_elemento (CabLista lst, (void *) valor) {

	ElemLista * pElem;
	pElem = (ElemLista *)malloc(sizeof(ElemLista));
	if (pElem == NULL) {
		return NULL;
	} /* if */

	pElem->ElemProx = NULL;
	pElem->ElemAnt = NULL;
	pElem->info = valor;
	lst->NumElem++;

	return pElem;

} /* Fim da função: Cria elemento */

/* Função: Limpa a estrutura cabeça da lista */
void limpar_cabeca (CabLista * lst) {

	lst->ElemCorrente = NULL;
	lst->FimLista = NULL;
	lst->OrigemLista = NULL;
	lst->NumElem = 0;
} /* Fim da função: Limpar cabeça da lista */


/* Função: Vai para fim da lista */

LIS_cond_ret LIS_ir_fim (CabLista * lst) { 

	lst->ElemCorrente = lst->FimLista;
		return LIS_OK;

} /* Fim da função: Ir para fim da lista */


/* Função: Vai para início da lista */
LIS_cond_ret LIS_ir_inicio (CabLista * lst) { 

	lst->ElemCorrente = lst->OrigemLista;
		return LIS_OK;

} /* Fim da função: Ir para início da lista */


/* Função: Vai para direita; próximo elemento */
LIS_cond_ret LIS_ir_dir (CabLista * lst) { 

	lst->ElemCorrente = lst->ElemCorrente->ElemProx;
		return LIS_OK;
} /* Fim da função: Ir para direita */

/* Função: Vai para esquerda;  elemento anterior */
LIS_cond_ret LIS_ir_esq (CabLista * lst) { 

	lst->ElemCorrente = lst->ElemCorrente->ElemAnt;
		return LIS_OK;
} /* Fim da função: Ir para esquerda*/

/* Função: Obtem valor do elemento corrente da lista */
void * LIS_obter_valor (CabLista * lst) { 

	if (lst->ElemCorrente == NULL) {
		return NULL;
	}
	return lst->ElemCorrente->valor;
} /* Fim da função: Obter valor */ 

/* Função: Exclui um elemento */
LIS_cond_ret LIS_excluir_elemento (CabLista * lst) {

	ElemLista * pElem;

	pElem = lst->ElemCorrente;
	if (lst->ElemCorrente == NULL) {
		return LIS_VAZIA;
	} /* if */

	if (pElem->ElemAnt != NULL) {
		pElem->ElemAnt->ElemProx = pElem->ElemProx;
		lst->ElemCorrente = pElem->ElemAnt;
	}
	else {
		lst->ElemCorrente = pElem->ElemProx;
		lst->OrigemLista = lst->ElemCorrente;
	} /* if */

	if (pElem->ElemProx != NULL) {
		pElem->ElemProx->ElemAnt = pElem->ElemAnt;
	}
	else {
		lst->FimLista = pElem->ElemAnt;
	} /* if */

	liberar_elemento (lst, pElem);
	return LIS_OK;

} /* Fim da função: Exclui elemento */


/* Função: Destroi lista */
void LIS_destruir_lista (CabLista * lst) {

	LIS_esvasiar_lista (lst);
	free (lst);
}/* Fim da função: Destroi lista */

/* Função: Esvazia lista */
void LIS_esvaziar_lista (CabLista * lst) {

	ElemLista * pElem;
	ElemLista * prox;

	pElem = lst->OrigemLista;
	while (pElem != NULL) {
		prox = pElem->ElemProx;
		liberar_elemento (lst, pElem);
		pElem = prox;	
	} /* while */

	limpar_cabeca (lst);
} /* Fim da função: Esvazia lista */


/* Função: Procura um valor na lista  */ 
LST_cond_ret LIS_procurar_valor (CabLista * lst, (void *) valor) {
	
	ElemLista * pElem;

	if (lst->ElemCorrente == NULL) {
		return LIS_VAZIA;
	} /* if */

	for (pElem = lst->OrigemLista; pElem != NULL; pElem = pElem->ElemProx) {
		if (pElem->info == valor) {
			lst->ElemCorrente = pElem;
			return LIS_OK;
		} /* if */
	} /* for */

	return LIS_NAO_ENCONTROU;

} /* Fim da função: Procura valor */

/* Função: Libera um elemento */
void liberar_elemento (CabLista * lst, ElemLista * pElem) {

	if ((lst->excluir_valor != NULL) && (pElem->info != NULL)) {
		lst->excluir_valor(pElem->info);
	} /* if */

	free(pElem);
	lst->NumElem--;
} /* Fim da função: Libera elemento */

/* Função: Avança o elemento corrente da lista */
LIS_cond_ret LIS_avancar_elem_corrente (CabLista * lst, int NumElem) {

	int i;
	ElemLista * pElem;

	if (lst->ElemCorrente == NULL) {
		return LIS_VAZIA;
	} /* if */

	if (NumElem > 0) {

		pElem = lst->ElemCorrente;
		for (i = NumElem; i > 0; i--) {
			if (pElem == NULL) {
				break;
			} /* if */
			pElem = pElem->ElemProx;
		} /* for */
	
		if (pElem != NULL) {
			lst->ElemCorrente = pElem;
			return LIS_OK;
		} /* if */

		lst->ElemCorrente = lst->FimLista;
		return LIS_FIM_LISTA;      
	} /* if */
} /* Fim da função: Avança elemento corrente */
