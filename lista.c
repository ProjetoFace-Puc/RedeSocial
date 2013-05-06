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


void * LIS_obter_valor (CabLista * lst) {
if (lst->ElemCorrente == NULL) 
return NULL;
return lst->ElemCorrente->valor;
}