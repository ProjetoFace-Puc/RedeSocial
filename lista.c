typedef struct elemlista {

	(void *) info;
	ElemLista * ElemProx;
	ElemLista * ElemAnt;

} ElemLista ;

typedef struct cablista {

	ElemLista * OrigemLista;
	ElemLista * FimLista;
	ElemLista * ElemCorrente;	
	int NumElem;
	void (* excluir_valor) (void * valor)

} CabLista ;


   static void liberar_elemento (CabLista  lst, ElemLista  * pElem) ;

   static ElemLista *cria_elemento(CabLista lst, (void *) valor) ;

   static void limpar_cabeca(CabLista lst) ;


LIS_cond_ret LIS_insere_antes (CabLista * lst, (void *) valor) {

ElemLista * pElem;
pElem = cria_elemento (lst, valor);

/*se vazia, a lista fica com um unico elemento, o que acaba de ser inserido*/
if (lst->ElemCorrente == NULL) {
	lst->OrigemLista = pElem;
	lst->FimLista = pElem;
}

else {

	if (lst->ElemCorrente->ElemAnt != NULL) {
		pElem->ElemAnt = lst->ElemCorrente->ElemAnt;
		lst->ElemCorrente->ElemAnt->ElemProx = pElem;
	}

	else 
		lst->OrigemLista = pElem;

	pElem->ElemProx = lst->ElemCorrente;
	lst->ElemCorrente->ElemAnt = pElem;
}

lst->ElemCorrente = pElem;

return LIS_OK;

}

LIS_cond_ret LIS_insere_depois (CabLista * lst, (void *) valor) {

ElemLista * pElem;
pElem = cria_elemento (lst, valor)

if (lst->ElemCorrente == NULL) {
	lst->OrigemLista = pElem;
	lst->FimLista = pElem;
}

else {

	if (lst->ElemCorrente->ElemProx != NULL) {
		pElem->ElemProx = lst->ElemCorrente->ElemProx;
		lst->ElemCorrente->ElemProx->ElemAnt = pElem;
	}

	else 
		lst->FimLista = pElem;

	pElem->ElemAnt = lst->ElemCorrente;
	lst->ElemCorrente->ElemProx = pElem;
}

lst->ElemCorrente = pElem;
return LIS_OK;

}

CabLista LIS_cria_lista (void (*excluir_valor), (void * dado)) {

	CabLista * lst = NULL;
	lst = (CabLista *)malloc(sizeof(CabLista));
	if (lst == NULL)
		return NULL;
	limpar_cabeca(lst);
	lst->excluir_valor = excluir_valor;
	return lst;
}

ElemLista * LIS_busca (ElemLista * lst, (void *) valor) {

ElemLista * ponteiro;
for (ponteiro = lst; ponteiro != NULL; ponteiro = ponteiro->ElemProx)
	if (ponteiro->info == valor)
		return ponteiro;
	return NULL;
}


ElemLista * LIS_retira_elemento (ElemLista * lst, (void *) valor) {

ElemLista * ponteiro = LIS_busca(lst, valor);
/*checa se elemento está na lista*/
if (ponteiro == NULL)
	return lst;
/*testa se é o primeiro*/
if (lst == ponteiro)
	lst = ponteiro->ElemProx;
else
	ponteiro->ElemAnt->ElemProx = ponteiro->ElemProx;
if (ponteiro->ElemProx != NULL)
/*testa se é o último*/
	ponteiro->ElemProx->ElemAnt = ponteiro->ElemAnt;
/*retira elemento e libera a variável de ponteiro*/
free (ponteiro);

return lst;

}

ElemLista * cria_elemento (CabLista lst, (void *) valor) {

ElemLista * pElem;
pElem = (ElemLista *)malloc(sizeof(ElemLista)); 
if (pElem == NULL)
	return NULL;

pElem->ElemProx = NULL;
pElem->ElemAnt = NULL;
pElem->info = valor;

lst->NumElem++;

return pElem;

}

void limpar_cabeca (CabLista * lst) {

lst->ElemCorrente = NULL;
lst->FimLista = NULL;
lst->OrigemLista = NULL;
lst->NumElem = 0;
}

void LIS_ir_fim (CabLista * lst) { /*Ir Ultimo*/

lst->ElemCorrente = lst->FimLista;

}

void LIS_ir_inicio (CabLista * lst) { /*Ir Primeiro*/

lst->ElemCorrente = lst->OrigemLista;

}

void LIS_ir_dir (CabLista * lst) { /*Ir Direita ??*/

lst->ElemCorrente = lst->ElemCorrente->ElemProx;

}

void LIS_ir_esq (CabLista * lst) { /*Ir Esquerda ??*/

lst->ElemCorrente = lst->ElemCorrente->ElemAnt;

}


void * LIS_obter_valor (CabLista * lst) { /*ObterCorrente*/

if (lst->ElemCorrente == NULL) 
	return NULL;

return lst->ElemCorrente->valor;

}

LIS_cond_ret LIS_excluir_elemento (CabLista * lst) {

ElemLista * pElem;

pElem = lst->ElemCorrente;
if (lst->ElemCorrente == NULL)
	return LIS_VAZIA;

if (pElem->ElemAnt != NULL) {
	pElem->ElemAnt->ElemProx = pElem->ElemProx;
	lst->ElemCorrente = pElem->ElemAnt;
}
else {
	lst->ElemCorrente = pElem->ElemProx;
	lst->OrigemLista = lst->ElemCorrente;
}

if (pElem->ElemProx != NULL) 
	pElem->ElemProx->ElemAnt = pElem->ElemAnt;
else
	lst->FimLista = pElem->ElemAnt;
	
liberar_elemento (lst, pElem);
return LIS_OK;

}

void LIS_destruir_lista (CabLista * lst) {

	LIS_esvasiar_lista (lst);
	free (lst);
}

void LIS_esvaziar_lista (CabLista * lst) {

	ElemLista * pElem;
	ElemLista * prox;

	pElem = lst->OrigemLista;
	while (pElem != NULL) {
		prox = pElem->ElemProx;
		liberar_elemento (lst, pElem);
		pElem = prox;		
	}

	limpar_cabeca (lst);
}

LST_cond_ret LIS_procurar_valor (CabLista * lst (void *) valor) {

	ElemLista * pElem;

	if (lst->ElemCorrente == NULL)
		return LIS_VAZIA;
	for (pElem = lst->ElemCorrente; pElem != NULL; pElem = pElem->ElemProx) {
		if (pElem->info == valor) {
			lst->ElemCorrente = pElem;
			return LIS_OK; 
		}
	}

	return LIS_NAO_ENCONTROU;

}

void liberar_elemento (CabLista * lst, ElemLista * pElem) {

	if ((lst->excluir_valor != NULL) && (pElem->info != NULL))
		lst->excluir_valor(pElem->info);

	free(pElem);
	lst->NumElem--;
}

LIS_cond_ret LIS_avancar_elem_corrente (CabLista * lst, int NumElem) {

	int i;
	ElemLista * pElem;

	if (lst->ElemCorrente == NULL)
		return LIS_VAZIA;

	if (NumElem > 0) {

		pElem = lst->ElemCorrente;
		for (i = NumElem; i > 0; i--) {
			if (pElem == NULL)
				break;
			pElem = pElem->ElemProx;
		}

		if (pElem != NULL) {

			lst->ElemCorrente = pElem;
			return LIS_OK;
		}

		lst->ElemCorrente = lst->FimLista;
		return LIS_FIM_LISTA;


       
	}


}
