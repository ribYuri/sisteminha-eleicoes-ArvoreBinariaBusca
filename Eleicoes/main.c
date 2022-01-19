#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinBusca.h"

int main(){
    int opcoes;

    while (opcoes != 9){

        printf("             NAVEGUE ESCOLHENDO UM DOS NUMEROS (0 -> Mostra Cadastrados)                \n");
        printf("========================================================================================\n");
        printf("| 1 -> Cadastrar Titulo     ||  2 -> Descadastrar Titulo  ||  3 -> Inscrever Candidato |\n");
        printf("| 4 -> Inciar Nova Votacao  ||  5 -> Votar                ||  6 -> Retirar Voto        |\n");
        printf("| 7 -> Resultado Parcial    ||  8 -> Ja votaram           ||  9 -> Finalizar Programa  |\n");
        printf("========================================================================================\n");
        printf("                                     OPCAO = ");
        scanf("%d", &opcoes);
        system("cls");

        if (opcoes == 0){
            printf("==================ELEITORES CADASTRADOS==================\n\n");
            imprimeArvore(arvoreTitulos);
            printf("\n");
            system("pause"); system("cls");
        } else if (opcoes == 1){
            cadastraTitulo(&arvoreTitulos);
            printf("\n");
            system("pause"); system("cls");
        } else if (opcoes == 2){
            descadastrarTitulo(&arvoreTitulos);
            printf("\n");
            system("pause"); system("cls");
        } else if (opcoes == 3){
            inscreveCandidato();
            printf("\n");
            system("pause"); system("cls");
        } else if (opcoes == 4){
            iniciarVotacao();
            printf("\n");
            system("pause"); system("cls");
        } else if (opcoes == 5){
            votar();
            printf("\n");
            system("pause"); system("cls");
        } else if (opcoes == 6){
            retirarVoto();
            printf("\n");
            system("pause"); system("cls");
        } else if (opcoes == 7){
            resultadoParcial();
            printf("\n");
            system("pause"); system("cls");
        } else if (opcoes == 8){
            if (arvoreVotos == NULL)
                printf("Ninguem votou ate o momomento...\n");
            else {
                printf("==================PESSOAS QUE JA VOTARRAM==================\n\n");
                imprimeArvore(arvoreVotos);
            }
            printf("\n");
            system("pause"); system("cls");
        } else if (opcoes == 9){
            liberaEstruturas();
        }
    }

    printf("Programa encerrado.\n");
    return 0;
}
