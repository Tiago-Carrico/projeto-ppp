#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct PDI * lPDI;
typedef struct PDI {
    char n_pdi[50];
    char descricao[1000];
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
        strcpy(aux->morada, "");
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
        *actual = NULL;     //se o elemento nao for encontrado
}


lUSER insere_lista_USERS(lUSER lista,char nome[100],char nascimento[30], char nr_telefone[20], char morada[50], char pdi_hot[50]) {
    lUSER no;
    lUSER ant, inutil;
    no = (lUSER) malloc (sizeof(USER));    //reserva espaço para o nó

    if (no != NULL) {
        strcpy(no->nome, nome);
        strcpy(no->nascimento, nascimento);
        strcpy(no->nr_telefone, nr_telefone);
        strcpy(no->morada, morada);
        procura_lista_USERS(lista, nome, &ant, &inutil);
        no->users = ant->users;
        ant->users = no;
    }
}

//TODO em primeiro imprime uma folha de dados vazia, mas de resto funciona, ver depois
void imprime_lista_users(lUSER lista) {
    lUSER l = lista->nome; //salta o header
    while (l) {
        printf("\nNome: %s\nData de nascimento:%s\n Nr. de telefone: %s\nMorada: %s\n ", l->nome, l->nascimento, l->nr_telefone, l->morada);
        //imprime_lista_PDIS(l->PDIS);
        l = l->users;
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
    no = (lCIDADE) malloc (sizeof(CIDADE));    //reserva espaço para o nó

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
        *actual = NULL;     //se o elemento nao for encontrado
}

void insere_lista_PDIS(lPDI lista,char nome_pdi[100],char descricao[2000], char horario[100]) {
    lPDI no;
    lPDI ant, inutil;
    no = (lPDI) malloc (sizeof(PDI));    //reserva espaço para o nó

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
    lPDI l = lista->PDIS; //salta o header
    while (l) {
        printf("%s ", l->n_pdi);
        printf("%s ", l->descricao);
        printf("Horario:%s ", l->horario);
        printf("\n");
        l = l->PDIS;
    }
}

void imprime_lista_cidades(lCIDADE lista) {
    lCIDADE l = lista->cidades; //salta o header
    while (l) {
        printf("\n\n%s\n ", l->n_cidade);
        imprime_lista_PDIS(l->PDIS);
        l = l->cidades;
    }
}

//https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/

void swap_cidade(CIDADE *a, CIDADE *b){
    char *temp = a->n_cidade;
    strcpy(a->n_cidade, b->n_cidade);
    strcpy(b->n_cidade, temp);
}

void Sort_cidade(CIDADE *start)
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
                swap_cidade(ptr1, ptr1->cidades);
                swapped = 1;
            }
            ptr1 = ptr1->cidades;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void swap_user(USER *a, USER *b){
    char *temp = a->nome;
    strcpy(a->nome, b->nome);
    strcpy(b->nome, temp);
}

void Sort_user(CIDADE *start)
{
    int swapped, i;
    USER *ptr1;
    USER *lptr = NULL;

    if (start == NULL)  //verificar se a lista esta vazia
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->users != lptr)
        {
            if (strcmp(ptr1->nome, ptr1->users->nome) > 0)
            {
                swap_cidade(ptr1, ptr1->users);
                swapped = 1;
            }
            ptr1 = ptr1->users;
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
    char descricaot[1000];
    char horariot[100];
    lCIDADE aux;

    teste = fopen("D:\\Documentos\\Uni\\1a2s\\PPP\\projeto_ppp\\cmake-build-debug\\project.txt", "r");
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
}

int criar_user() {
    //iniciar variaveis para todos os dados necessarios
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

    //abre ficheiro
    FILE* users; //criar var do ficheiro
    users = fopen("utilizadores.txt", "a"); //abrir documento texto
    fprintf(users, "+%s\n?%s\n@%s\n!%s\n", nome, nascimento, telefone, morada); //escrever os dados do user, + para o nome, ? para a data de nascimento, @ para o telefone, ! para a morada
    fclose(users); //fechar ficheiro

    return 0;
}

int ler_users(lUSER lista){
    FILE *users;
    char linha[2000];
    char nome[100];
    char nascimento[30];
    char nr_telefone[20];
    char morada[50];
    lUSER aux;

    users = fopen("D:\\Documentos\\Uni\\1a2s\\PPP\\projeto_ppp\\cmake-build-debug\\utilizadores.txt", "r");
    while (fgets(linha, 2000, users) != NULL) {

        if (linha[0]=='+') {
            strcpy(nome, linha+1);
        }

        else if (linha[0]=='?') {
            strcpy(nascimento, linha+1);
        }

        else if (linha[0]=='@') {
            strcpy(nr_telefone, linha+1);
        }

        else if (linha[0]=='!') {
            strcpy(morada, linha+1);
            aux = insere_lista_USERS(lista, nome, nascimento, nr_telefone, morada, "");
        }

        else {
            printf("O ficheiro está corrupto");
        }
    }
    fclose(users);
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



void placeholder() {
    //so placeholder para switch, etc.
}


int menu(lCIDADE lista) {
    char user[100];
    int opcao;
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("Escreva um numero de acordo com a operaçao que pretende realizar:");
    printf("\n1)Ver todos os destinos possiveis");
    printf("\n2)Criar um novo utilizador");
    printf("\n3)Selecionar preferencias para um utilizador existente");
    printf("\n4)Remover PDIS favoritos de um utilizador");
    printf("\n5)Ver os PDI's pela sua popularidade");
    printf("\n6)Construir uma viagem baseada nos gostos de um utilizador");
    printf("\n7)Eliminar um utilizador");
    printf("\n8)Acabar a sessao");
    printf("\n---------------------------------------------------------------------------------------------------------------\n");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            printf("");
            ler_ficheiro(lista);
            Sort_cidade(lista);
            imprime_lista_cidades(lista);
            menu(lista);
        case 2:
            printf("");
            criar_user();
            menu(lista);
        case 3:
            placeholder();
            menu(lista);
        case 4:
            placeholder();
            menu(lista);
        case 5:
            placeholder();
            menu(lista);
        case 6:
            placeholder();
            menu(lista);
        case 7:
            gets(user);
            eliminar_utilizador("utilizadores.txt", 50);
        case 8:
            return 0;
        default:
            printf("Essa não é uma opcao possivel");
            menu(lista);
    }
}


int main() {
    lCIDADE l_cidades;
    l_cidades = cria_lista_cidade();
    lUSER l_users;
    l_users = cria_lista_USERS();
    //menu(l_cidades);           //-> devera ficar ligado no final, desligado para testes com listas ligadas e ficheiros
    //ler_ficheiro(l_cidades);
    //criar_user();     //-> testado, funciona ao escrever o user no file
    //imprime_lista_cidades(l_cidades);
    //printf("\n\n\n");
    //Sort_cidade(l_cidades);
    //imprime_lista_cidades(l_cidades);

    ler_users(l_users);
    Sort_user(l_users);
    imprime_lista_users(l_users);

    return 0;
}



