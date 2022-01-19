#ifndef ARVOREBINBUSCA_H_INCLUDED
#define ARVOREBINBUSCA_H_INCLUDED

typedef struct {
    int titulo_eleitor;
    char Nome[50];
    int voto;
}Info;

typedef struct No_Est{
    Info *info;
    struct No_Est *pEsq, *pDir;
}No;

No *arvoreTitulos;
No *arvoreVotos;

int votacaoIniciada;

void cadastraTitulo(No**);
int descadastrarTitulo(No**);
int removeCandidato(Info);
void iniciarVotacao();
void resetaVotacao(No*);
void resetaVotosCandidatos();
int votar();
int votoValido(int, int);
int retirarVoto();
int pesquisa (No*, Info**);
void pesquisaArvVotacao (No*, Info**);
No* cria_no (Info*);
int insere (No**, Info*);
int insereArvVotacao (No**, Info*);
int retira (Info, No**);
void sucessor (No*, No**);
void imprimeArvore (No*);
void liberaInfos(No*);
void liberaArvore(No*);

typedef struct CelulaEst{
    Info *info;
    int numDeVotos;
    struct CelulaEst* Prox;
} Celula;

typedef struct {
    Celula* primeiro;
    Celula* ultimo;
} Lista;

Lista listaCandidatos;


int inscreveCandidato();
int candidatoNaLista(Info*);
int Lvazia (Lista*);
void fazListaVazia(Lista*);
void add(Lista*, Info*);
void imprimeCandidatos(Lista);
void resultadoParcial();
int liberaLista(Celula*);
void liberaEstruturas();


#endif ARVOREBINBUSCA_H_INCLUDED
