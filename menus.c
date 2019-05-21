#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHUNK 1024

int menu()
{
    int i;
    system("cls");
    printf("Indique o que pretende executar\n\n");
    printf("(1) - Registar utilizadores\n");
    printf("(2) - Listagem de locais e pontos de interesse (ordem alfabetica)\n");
    printf("(3) - Definir preferencias de utilizador\n");
    printf("(4) - Listagem de locais e pontos de interesse mais populares\n\n");
    printf("(5) - Criar Viagem\n");
    printf("(6) - Sair");
    scanf("%d",&i);
    while ((i<1)||(i>5)){
        printf("\nIndique corretamente o que executar\n");
        scanf("%d",&i);
    }
    if (i=1){
        //Funcao para registo de utilizadores

    }
    if (i=2){
        //Funcao que ordena locais e pontos de interesse
        //E apresenta as mesmas no ecra

    }
    if (i=3){
        //Funcao que define prefencias de utilizadores ja registados

    }
    if (i=4){
        //Funcao que ordena locais e pontos de interesse
        //Em funcao da sua popularidade e apresenta no ecra
    }
    if (i=5){
        //Funcao que cria viagem
    }
    if (i=6){
        return 0;
    }

}
