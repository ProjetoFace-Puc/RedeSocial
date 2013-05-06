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
} CabLista ;

void LIS_insere_antes (CabLista * lst, (void *) valor) {
ElemLista * pElem;
pElem = LIS_cria_elemento (lst, valor);
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
}


void LIS_insere_depois (CabLista * lst, (void *) valor) {
ElemLista * pElem;
pElem = LIS_cria_elemento (lst, valor)
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
}


ElemLista LIS_cria_lista () {
return NULL;
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
/*checa se elemento est� na lista*/
if (ponteiro == NULL)
return lst;
/*testa se � o primeiro*/
if (lst == ponteiro)
lst = ponteiro->ElemProx;
else
ponteiro->ElemAnt->ElemProx = ponteiro->ElemProx;
if (ponteiro->ElemProx != NULL)
/*testa se � o �ltimo*/
ponteiro->ElemProx->ElemAnt = ponteiro->ElemAnt;
/*retira elemento e libera a vari�vel de ponteiro*/
free (ponteiro);
return lst;
}


ElemLista * LIS_cria_elemento (CabLista lst, (void *) valor) {
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


void LIS_limpar_cabeca (CabLista * lst) {
lst->ElemCorrente = NULL;
lst->FimLista = NULL;
lst->OrigemLista = NULL;
lst->NumElem = 0;
}


void LIS_ir_fim (CabLista * lst) {
lst->ElemCorrente = lst->FimLista;
}


void LIS_ir_inicio (CabLista * lst) {
lst->ElemCorrente = lst->OrigemLista;
}

void LIS_ir_dir (CabLista * lst) { /*Ir Direita ??*/

lst->ElemCorrente = lst->ElemCorrente->ElemProx;

}

void LIS_ir_esq (CabLista * lst) { /*Ir Esquerda ??*/

lst->ElemCorrente = lst->ElemCorrente->ElemAnt;

}

void * LIS_obter_valor (CabLista * lst) {
if (lst->ElemCorrente == NULL) 
return NULL;
return lst->ElemCorrente->valor;
}

/* incompleto */
void LIS_excluir_elemento (CabLista * lst) {

ElemLista * pElem;

pElem = lst->ElemCorrente;

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
	
LIS_liberar_elemento (lst, pElem); /* falta fazer a função de liberar elemento*/ 

}
