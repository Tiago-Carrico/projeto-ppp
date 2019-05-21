#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct PDI * lPDI;
typedef struct PDI {
    char n_pdi[50];
    char descricao[256];
    char horario[50];
    lPDI PDIS;
}PDI;


typedef struct CIDADE * lCIDADE;
typedef struct CIDADE {
    char n_cidade[50];
    lPDI PDIS;
    lCIDADE cidades;
}CIDADE;

typedef struct USER * lUSER;
typedef struct USER {
    char nome[100];
    char nascimento[30];
    char nr_telefone[20];
    char morada[50];
    char pdi_hot[50];
    lUSER users;
}USER;

lUSER cria_lista_USERS() {
    lUSER aux;
    aux = (lUSER) malloc (sizeof (USER));
    if (aux != NULL) {
        strcpy(aux->nome, "");
        strcpy(aux->nascimento, "");
        strcpy(aux->nr_telefone, "");
        aux->users = NULL;
    }
    return aux;
}

void procura_lista_USERS(lUSER lista, char chave[], lUSER *ant, lUSER *actual) {
    *ant = lista;
    *actual = lista->users;
    while ((*actual) != NULL && strcmp((*actual)->nome, chave)<0){
        *ant = *actual;
        *actual = (*actual)->users;
    }
    if ((*actual) != NULL && strcmp((*actual)->nome, chave)!=0)
        *actual = NULL;
}


void insere_lista_USERS(lUSER lista,char nome[100],char nascimento[30], char nr_telefone[20], char morada[50], char pdi_hot[50]) {
    lUSER no;
    lUSER ant, inutil;
    no = (lUSER) malloc (sizeof(USER));

    if (no != NULL) {

        strcpy(no->nome, nome);
        strcpy(no->nascimento, nascimento);
        strcpy(no->nr_telefone, nr_telefone);

        procura_lista_USERS(lista, nome, &ant, &inutil);

        no->users = ant->users;

        ant->users = no;
    }

}

lPDI cria_lista_PDIS() {
    lPDI aux;
    aux = (lPDI) malloc (sizeof (PDI));
    if (aux != NULL) {
        strcpy(aux->n_pdi, "");
        strcpy(aux->descricao, "");
        strcpy(aux->horario, "");
        aux->PDIS = NULL;
    }
    return aux;
}

lCIDADE cria_lista_cidade() {
    lCIDADE aux;
    aux = (lCIDADE) malloc (sizeof (CIDADE));
    if (aux != NULL) {
        strcpy(aux->n_cidade, "");
        aux->PDIS = cria_lista_PDIS();
        aux->cidades = NULL;
    }
    return aux;
}

int lista_vazia_CIDADES(lCIDADE lista) {
    return(lista->cidades == NULL ? 2 : 0);
}

void procura_lista_CIDADES(lCIDADE lista, char chave[], lCIDADE *ant, lCIDADE *actual) {
    *ant = lista;
    *actual = lista->cidades;
    while ((*actual) != NULL && strcmp((*actual)->n_cidade,  chave)<0){
        *ant = *actual;
        *actual = (*actual)->cidades;
    }
    if ((*actual) != NULL && strcmp((*actual)->n_cidade, chave)!=0)
        *actual = NULL;

}

lCIDADE insere_lista_CIDADES(lCIDADE lista, char it[]) {
    lCIDADE no;
    lCIDADE ant, inutil;
    no = (lCIDADE) malloc (sizeof(CIDADE));

    if (no != NULL) {

        strcpy(no->n_cidade, it);

        procura_lista_CIDADES (lista, it, &ant, &inutil);

        no->PDIS = cria_lista_PDIS();

        no->cidades = ant->cidades;

        ant->cidades = no;

    }
    return no;
}

void procura_lista_PDIS(lPDI lista, char chave[], lPDI *ant, lPDI *actual) {
    *ant = lista;
    *actual = lista->PDIS;
    while ((*actual) != NULL && strcmp((*actual)->n_pdi, chave)<0){
        *ant = *actual;
        *actual = (*actual)->PDIS;
    }
    if ((*actual) != NULL && strcmp((*actual)->n_pdi, chave)!=0)
        *actual = NULL;
}



void insere_lista_PDIS(lPDI lista,char nome_pdi[100],char descricao[2000], char horario[100]) {
    lPDI no;
    lPDI ant, inutil;
    no = (lPDI) malloc (sizeof(PDI));

    if (no != NULL) {

        strcpy(no->n_pdi, nome_pdi);
        strcpy(no->descricao, descricao);
        strcpy(no->horario, horario);
        procura_lista_PDIS(lista, nome_pdi, &ant, &inutil);

        no->PDIS = ant->PDIS;

        ant->PDIS = no;
    }

}

void imprime_lista_PDIS(lPDI lista) {
    lPDI l = lista->PDIS;
    while (l) {
        printf("%s ", l->n_pdi);
        printf("%s ", l->descricao);
        printf("%s ", l->horario);

        l = l->PDIS;
    }
}

void imprime_lista_cidades(lCIDADE lista) {
    lCIDADE l = lista->cidades;
    while (l) {
        printf("%s ", l->n_cidade);
        imprime_lista_PDIS(l->PDIS);
        l = l->cidades;
    }
}



void swap(CIDADE *a, CIDADE *b)
{
    char *temp = a->n_cidade;
    lCIDADE temp2 = a->cidades;

    strcpy(a->n_cidade, b->n_cidade);


    strcpy(b->n_cidade, temp);

}

void organizar_cidade(CIDADE *start)
{
    int swapped, i;
    CIDADE *ptr1;
    CIDADE *lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->cidades != lptr)
        {
            if (strcmp(ptr1->n_cidade, ptr1->cidades->n_cidade) > 0)
            {
                swap(ptr1, ptr1->cidades);
                swapped = 1;
            }
            ptr1 = ptr1->cidades;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void ler_ficheiro(lCIDADE lista) {
    FILE *teste;
    char linha[2000];
    char nome_cidade[100];
    char nome_pdit[50];
    char descricaot[2000];
    char horariot[100];

    lCIDADE aux;


    teste = fopen("C:\\Users\\Francisco Pais\\Desktop\\Eng. Inf\\ProjetoPPP\\project.txt", "r");
    while (fgets(linha, 2000, teste) != NULL) {

        if (linha[0]=='*') {

            strcpy(nome_cidade, linha+1);

            aux = insere_lista_CIDADES(lista, nome_cidade);
        }

        else if (linha[0]=='&') {

            strcpy(nome_pdit, linha+1);
        }


        else if (linha[0]=='#') {

            strcpy(descricaot, linha+1);
        }

        else if (linha[0]=='$') {

            strcpy(horariot, linha+1);
            insere_lista_PDIS(aux->PDIS, nome_pdit, descricaot, horariot);
        }

        else {
            printf("O ficheiro está corrupto");
        }

    }

    fclose(teste);
    imprime_lista_cidades(lista);

}

int criar_user() {

    char nome[100];
    char nascimento[30];
    char telefone[20];
    char morada[50];


    printf("Nome: \n");
    gets(nome);
    printf("Data de nascimento: \n");
    gets(nascimento);
    printf("Nr. telefone: \n");
    gets(telefone);
    printf("Morada: \n");
    gets(morada);

    USER user_atual;
    strcpy(user_atual.nome, nome);
    strcpy(user_atual.nascimento, nascimento);
    strcpy(user_atual.nr_telefone, telefone);
    strcpy(user_atual.morada, morada);


    FILE* users;
    users = fopen("utilizadores.txt", "a");
    fprintf(users, "£%s\n§%s\n@%s\n!%s\n", nome, nascimento, telefone, morada);
    fclose(users);

    return 0;
}

int procura_ficheiro(char *nomefile,char *str){
    FILE *f;

    int numero_linha = 1;

    f = fopen(nomefile,"r");
    char max[150];
    while(fgets(max,sizeof(max),f) != NULL){
        if((strstr(max,str) != NULL)){
            return numero_linha;
        }
        numero_linha++;
    }
}



void eliminar_utilizador(char *nomefile,int bi){
    FILE *fptr1,*fptr2;
    char ch;
    char str_bi[8];

    sprintf(str_bi,"%d",bi);

    fptr1 = fopen(nomefile,"r");
    ch = getc(fptr1);

    int num_linha = 1;
    int linha_apagar = procura_ficheiro(nomefile,str_bi);

    fptr2 = fopen("replica.c","w");


    for(;;){
        if(ch == EOF){
            break;
        }
        if(num_linha != linha_apagar){
            putc(ch,fptr2);
        }
        if(ch == '\n'){
            num_linha++;
        }
        ch = getc(fptr1);
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(nomefile);
    rename("replica.c",nomefile);
}



int menu()
{
    int i;
    system("cls");
    printf("Indique o que pretende executar\n\n");
    printf("1.- Registo de utilizadores\n");
    printf("2.-  Lista de locais com respectivo pontos de interesse e suas informacoes\n");
    printf("3.- Ver a popularidade dos locais e respectivos pontos de interesse\n\n");
    printf("4.- Definir ponto hot do utilizador\n");
    printf("5.- Indique os 3 locais preferidos do utilizador\n");
    printf("6.- defina os seus pontos de interesse favoritos\n");
    printf("7.- Criar viagem\n");
    printf("8.- Lista de locais e pontos de interesse mais populares");
    printf("9.-Dados dos utilizadores ");
    printf("10.- Alterar dados do utilizador\n");
    printf("11.- Sair");
    scanf("%d",&i);
    while ((i<1)||(i>5)){
        printf("\nIndique corretamente o que executar\n");
        scanf("%d",&i);
    }
    if (i=1){
        system("cls");
        printf("Escolheu a opcao 1. - Registo de utilizadores\n");
    }
    else if (i=10){
        system("cls");
        printf("Escolheu a opcao 10. - Alterar dados do utilizador\n");
    }
    else if (i=11){
        system("cls");
        printf("Escolheu a opcao 11. -Sair \n");

    }
    else if (i=4){
        system("cls");
        printf("Escolheu a opcao 4. - Registar utilizadores\n");
    }
    else if (i=5){
        system("cls");
        printf("Escolheu a opcao (1) - Registar utilizadores\n");
    }
    else if (i=6){
        system("cls");
        printf("Escolheu a opcao (1) - Registar utilizadores\n");
        return 0;
    }

}






int main() {
    lCIDADE l_cidades;
    /*l_cidades = cria_lista_cidade();*/
    /*menu(l_cidades);           //-> devera ficar ligado no final, desligado para testes com listas ligadas e ficheiros*/
    ler_ficheiro(l_cidades);
    criar_user();
    /*imprime_lista_cidades(l_cidades);*/

    return 0;
}
