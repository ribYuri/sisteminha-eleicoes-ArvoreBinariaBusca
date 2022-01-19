#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinBusca.h"

void cadastraTitulo(No** Raiz){
    Info *registro = (Info*)malloc(sizeof(Info));
    printf("Insira o titulo do eleitor: ");
    scanf("%d", &registro->titulo_eleitor);
    printf("Insira o nome do eleitor: ");
    scanf("\n%[^\n]s", registro->Nome);
    registro->voto = -1;
    if(insere(Raiz, registro)){
        printf("Eleitor Cadastrado com sucesso!\n\n");
    } else
    printf("ERRO!!Titulo de eleitor ja cadastrado\n\n");
}

int descadastrarTitulo(No** ppRaiz){
    int stop = 1;
    Info reg, aux;
    Info *Aux, *Aux2;
    Aux = (Info*)malloc(sizeof(Info));
    printf("Insira o titulo de eleitor a ser removido: ");
    scanf("%d", &Aux->titulo_eleitor);
    Aux->voto = -15515;
    reg = *Aux;
    Aux2 = Aux;

    /*caso seja um candidato, reseta os votos de quem votou nele*/
    if(removeCandidato(reg)){
        while (stop == 1){
            pesquisaArvVotacao(arvoreVotos, &Aux);
            if (Aux2->voto == Aux->voto)
                break;

            Aux->voto = -1;
            aux = *Aux;
            retira(aux, &arvoreVotos);
            Aux = Aux2;
        }
    } else if (pesquisa(arvoreVotos, &Aux)){         /*caso alguem que ja votou; retira seu voto do candidato*/
        votoValido(Aux->voto, -1);
        retira(reg, &arvoreVotos);
    }
    /*descadastra a pessoa*/
    if (retira(reg, ppRaiz)){
        printf("\nTITULO %d REMOVIDO COM SUCESSO.\n", reg.titulo_eleitor);
        return 1;
    } else {
        printf("\nTITULO %d NAO ENCONTRADO\n", reg.titulo_eleitor);
    }
    return 0;
}

int removeCandidato(Info reg){
    if (Lvazia(&listaCandidatos))
        return 0;
    Celula *Aux;
    Aux = listaCandidatos.primeiro;
    while (Aux->Prox != NULL){
        if (reg.titulo_eleitor == Aux->Prox->info->titulo_eleitor){
            if (listaCandidatos.ultimo->Prox == Aux->Prox->Prox && Aux == listaCandidatos.primeiro){
                listaCandidatos.ultimo = listaCandidatos.primeiro;
                listaCandidatos.ultimo->Prox = NULL;
            } else if (listaCandidatos.primeiro->Prox ==  Aux->Prox){
                Aux->Prox = Aux->Prox->Prox;
            } else {
                Aux->Prox = Aux->Prox->Prox;
            }
            return 1;
        }
        Aux = Aux->Prox;
    }
    return 0;
}

void iniciarVotacao(){
    if (arvoreVotos != NULL) {    /*se ja existe uma votação; reseta todos os votos computados*/
        resetaVotacao(arvoreTitulos);
        resetaVotosCandidatos();
        liberaArvore(arvoreVotos);
        free(arvoreVotos);
        arvoreVotos = NULL;
        printf("Votos resetados! Iniciando nova Votacao...!\n");
    }
    if (!Lvazia(&listaCandidatos)) {
        printf("Votacao iniciada!!\n");
        votacaoIniciada = 1;
        votar();
    } else {
        printf("ERRO!! Nao ha candidatos para se votar!! ");
        printf("Por favor inscreva pelo menos um cadidato e entao inicie a votacao!\n\n");
    }
}

void resetaVotacao(No* Raiz) {
    if (Raiz != NULL) {
        resetaVotacao (Raiz->pEsq);
        Raiz->info->voto = -1;
        resetaVotacao (Raiz->pDir);
    }
}
/*reseta votos que candidatos receberam*/
void resetaVotosCandidatos(){
    Celula *Aux;
    Aux = listaCandidatos.primeiro->Prox;
    while (Aux != NULL){
        Aux->numDeVotos = 0;
        Aux = Aux->Prox;
    }
}

int votar(){
    if (Lvazia(&listaCandidatos)){
        printf("ERRO!!Nao ha candidatos inscritos para se votar!! Por favor inscreva candidatos...\n");
        votacaoIniciada = 0;
        return 0;
    }
    if (votacaoIniciada != 1){
        printf("ERRO!!Por favor inicie uma votacao e entao vote...\n");
        return 0;
    }
    Info *inf = (Info*)malloc(sizeof(Info));
    printf("Insira o titulo que esta votando: ");
    scanf("%d", &inf->titulo_eleitor);
    system("cls");
    if (pesquisa(arvoreTitulos, &inf)){
        if (inf->voto == -1){
            printf("============================CANDIDATOS============================\n");
            imprimeCandidatos(listaCandidatos);
            printf("\n\nInsira seu voto (Titulo do candidato): ");
            scanf("%d", &inf->voto);
            if (votoValido(inf->voto, 1)){
                insere (&arvoreVotos, inf);
                printf("VOTO COMPUTADO!\n");
                return 1;
            } else{
                inf->voto = -1;
                printf("ERRO!! O voto nao e valido!!\n");
                return 0;
            }
        } else
        printf("ERRO!! O titulo informado ja votou!!\n");
        return 0;
    } else
    printf("ERRO!! O titulo informado nao esta cadastrado!!\n");
    return 0;
}

int votoValido(int voto, int votaOuRetira){
    Celula *Aux;
    Aux = listaCandidatos.primeiro->Prox;
    while (Aux != NULL){
        if (voto == Aux->info->titulo_eleitor){
            if (votaOuRetira == 1)
                Aux->numDeVotos++;
            else
                Aux->numDeVotos--;
            return 1;
        }
        Aux = Aux->Prox;
    }
    return 0;
}

int retirarVoto(){
    if (arvoreVotos == NULL){
        printf("Nao ha votos computados!\n");
        return 0;
    }
    Info *inf = (Info*)malloc(sizeof(Info));
    printf("Digite o titulo para remocao do voto: ");
    scanf("%d", &inf->titulo_eleitor);
    if (pesquisa(arvoreVotos, &inf)){
        votoValido(inf->voto, -1);
        inf->voto = -1;
        Info x;
        x = *inf;
        retira(x, &arvoreVotos);
        printf("Titulo: %d || Voto removido com sucesso!\n", inf->titulo_eleitor);
        return 1;
    }else
    printf("ERRO!! O titulo ainda nao votou ou nao esta cadastrado!!\n");
    return 0;
}

int pesquisa (No* Raiz, Info **pX) {
    if (Raiz == NULL)
        return 0;
    if ((*pX)->titulo_eleitor < Raiz->info->titulo_eleitor)
        return pesquisa (Raiz->pEsq, pX);
    if ((*pX)->titulo_eleitor > Raiz->info->titulo_eleitor)
        return pesquisa (Raiz->pDir, pX);
    if ((*pX)->titulo_eleitor == Raiz->info->titulo_eleitor){
        *pX = Raiz->info;
    }
    return 1;
}
/*devolve INFO que votou no candidato X*/
void pesquisaArvVotacao (No* Raiz, Info **pX) {
    if (Raiz != NULL) {
        pesquisaArvVotacao (Raiz->pEsq, pX);
        pesquisaArvVotacao (Raiz->pDir, pX);
        if ((*pX)->titulo_eleitor == Raiz->info->voto)
            *pX = Raiz->info;
    }
}

No* cria_no (Info *x) {
    No* novo_no;
    novo_no = (No*)malloc(sizeof(No));
    novo_no->info = x;
    novo_no->pEsq = NULL;
    novo_no->pDir = NULL;
    return (novo_no);
}

int insere (No **Raiz, Info *x) {
    if (*Raiz == NULL) {
        *Raiz = cria_no(x);
        return 1;
    }
    if (x->titulo_eleitor < (*Raiz)->info->titulo_eleitor)
        return insere (&((*Raiz)->pEsq), x);
    if (x->titulo_eleitor > (*Raiz)->info->titulo_eleitor)
        return insere (&((*Raiz)->pDir), x);
    return 0;
}

int retira (Info x, No** p) {
    No* pAux;
    if (*p == NULL)
        return 0;
    if (x.titulo_eleitor < (*p)->info->titulo_eleitor)
        return retira (x, &(*p)->pEsq);
    if (x.titulo_eleitor > (*p)->info->titulo_eleitor)
        return retira (x, &(*p)->pDir);

    if (x.titulo_eleitor == (*p)->info->titulo_eleitor){
        if ((*p)->pDir == NULL) {
            pAux = *p;
            *p = (*p)->pEsq;
            free (pAux);
            return 1;
        }
        if ((*p)->pEsq == NULL) {
            pAux = *p;
            *p = (*p)->pDir;
            free (pAux);
            return 1;
        }
    }
    sucessor (*p, &(*p)->pDir);
    return 1;
}

void sucessor (No* q, No** r) {
    No* pAux;
    if ((*r)->pEsq != NULL) {
        sucessor (q, &(*r)->pEsq);
        return;
    }
    q->info = (*r)->info;
    pAux = *r;
    *r = (*r)->pDir;
    free (pAux);
}

void imprimeArvore (No* Raiz) {
    if (Raiz != NULL) {
        imprimeArvore (Raiz->pEsq);
        printf ("Titulo de eleitor: %d  ||  Nome: %s\n", Raiz->info->titulo_eleitor, Raiz->info->Nome);
        printf("-------------------------------------------------------\n");
        imprimeArvore (Raiz->pDir);
    }
}

void liberaInfos(No* Raiz) {
    if (Raiz != NULL) {
        liberaInfos (Raiz->pEsq);
        liberaInfos (Raiz->pDir);
        free(Raiz->info);
    }
}

void liberaArvore(No* Raiz) {
    if (Raiz != NULL) {
        liberaArvore (Raiz->pEsq);
        liberaArvore (Raiz->pDir);
        free(Raiz);
    }
}

int inscreveCandidato(){
    if(Lvazia(&listaCandidatos))
        fazListaVazia(&listaCandidatos);

    Info *aux = (Info*)malloc(sizeof(Info));
    printf("Insira o titulo da pessoa que ira se candidatar: ");
    scanf("%d", &aux->titulo_eleitor);
    if (candidatoNaLista(aux)){
        printf("ERRO!!O candidato ja esta inscrito!!\n");
        return 0;
    }

    if (pesquisa(arvoreTitulos, &aux)){
        add(&listaCandidatos, aux);
        printf("Candidato inscrito com sucesso\n");
        return 1;
    }else{
        printf("Eleitor ainda nao cadastrado. Insira um NOME para o portador do titulo %d: ", aux->titulo_eleitor);
        scanf("\n%[^\n]s", aux->Nome);
        aux->voto = -1;
        insere(&arvoreTitulos, aux);
        printf("Eleitor cadastrado!O eleitor agora e um candidato!\n");
        add(&listaCandidatos, aux);
        return 1;
    }
}
/*verfica se um candidato ja foi inscrito*/
int candidatoNaLista(Info *reg){
    if (Lvazia(&listaCandidatos))
        return 0;
    Celula *Aux;
    Aux = listaCandidatos.primeiro->Prox;
    while (Aux != NULL){
        if (Aux->info->titulo_eleitor == reg->titulo_eleitor)
            return 1;

        Aux = Aux->Prox;
    }
    return 0;
}

int Lvazia (Lista* pLista) {
    return (pLista->primeiro == pLista->ultimo);
}

void fazListaVazia(Lista *lista){
    lista->primeiro = (Celula*)malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro;
    lista->ultimo->numDeVotos = 0;
    lista->primeiro->Prox = NULL;
}

void add(Lista *lista, Info *item){
    lista->ultimo->Prox = (Celula*)malloc(sizeof(Celula));
    lista->ultimo = lista->ultimo->Prox;
    lista->ultimo->info = item;
    lista->ultimo->numDeVotos = 0;
    lista->ultimo->Prox = NULL;
}

void imprimeCandidatos(Lista lista){
    Celula *Aux;
    Aux = lista.primeiro->Prox;
    while (Aux != NULL){
        printf ("\nTitulo de eleitor: %d  ||  Nome: %s\n", Aux->info->titulo_eleitor, Aux->info->Nome);
        printf("-----------------------------------------------------------------\n");
        Aux = Aux->Prox;
    }
}

void resultadoParcial(){
     if (!Lvazia(&listaCandidatos)){
        Celula *Aux;
        Aux = listaCandidatos.primeiro->Prox;
        printf("=================================Resultado Parcial=================================\n\n");
        while (Aux != NULL){
            printf ("Titulo de eleitor: %d  ||  Nome: %s  ||", Aux->info->titulo_eleitor, Aux->info->Nome);
            printf("  Votos recebidos: %d\n", Aux->numDeVotos);
            printf("-------------------------------------------------------------------------------\n");
            Aux = Aux->Prox;
        }
     } else
     printf("Ainda nao ha candidatos!! Por favor faca a inscricao de algum...\n");
}

int liberaLista(Celula *celula){
    if (celula != NULL){
        liberaLista(celula->Prox);
        free(celula);
    }
    return 1;
}

void liberaEstruturas(){
    liberaInfos(arvoreTitulos);
    liberaArvore(arvoreTitulos);
    free(arvoreTitulos);
    arvoreTitulos = NULL;
    liberaArvore(arvoreVotos);
    free(arvoreVotos);
    arvoreVotos = NULL;
    if (!Lvazia(&listaCandidatos))
        liberaLista(listaCandidatos.primeiro->Prox);

    free(listaCandidatos.primeiro);
    free(listaCandidatos.ultimo);
    printf("Estruturas liberadas...\n");
}
