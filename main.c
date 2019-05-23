#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct PDI * lPDI;
typedef struct PDI {
    char n_pdi[50];
    char descricao[1000];
    char horario[50];
    int popularidade;
    lPDI PDIS;
}PDI;


typedef struct CIDADE * lCIDADE;
typedef struct CIDADE {
    char n_cidade[50];
    int popularidade;
    lPDI PDIS;
    lCIDADE cidades;
}CIDADE;

typedef struct USER * lUSER;
typedef struct USER {
    char nome[100];
    char nascimento[30];
    char nr_telefone[20];
    char morada[50];
    lPDI pdi_hot;
    //TODO usar como pdis fav e preferencia
    lPDI lista_pdis_pref[25];
    lCIDADE cidades_fav[3];
    lUSER users;
}USER;

////////////////////////Funçoes de compilaçao////////////////////
int compilar_lista_cidades(lCIDADE lista);
int compilar_lista_users(lUSER lista);


///////////////////////Funçoes de users/////////////////////////
lUSER cria_lista_USERS();
lUSER procura_lista_USERS(lUSER lista, char chave[], lUSER *ant, lUSER *actual);
lUSER insere_lista_USERS(lUSER lista,char nome[100],char nascimento[30], char nr_telefone[20], char morada[50], char pdi_hot[50]);
void troca_user(USER *a, USER *b);
void Sort_user(USER *start);
void imprime_lista_users(lUSER lista);
void sel_pref_user(lUSER lista_user, lCIDADE lista_cidade);
int criar_user();
int ler_users(lUSER lista);
void eliminar_utilizador(char *nomefile,int bi);


//////////////////////Funçoes de cidades///////////////////////
lCIDADE cria_lista_cidade();
void procura_lista_CIDADES(lCIDADE lista, char chave[], lCIDADE *ant, lCIDADE *actual);
lCIDADE insere_lista_CIDADES(lCIDADE lista, char it[]);
void troca_cidade(CIDADE *a, CIDADE *b);
void ler_ficheiro_cidades(lCIDADE lista);
void Sort_cidade(CIDADE *start);
void imprime_lista_cidades(lCIDADE lista);
int lista_vazia_CIDADES(lCIDADE lista);


/////////////////////Funçoes de PDI's/////////////////////////
lPDI cria_lista_PDIS();
lPDI procura_lista_PDIS(lPDI lista, char chave[], lPDI *ant, lPDI *actual);
void insere_lista_PDIS(lPDI lista,char nome_pdi[100],char descricao[2000], char horario[100]);


void imprime_lista_PDIS(lPDI lista);
lPDI procura_pdi_hot(lCIDADE procurar,char chave[],lCIDADE *ant,lCIDADE *actual);


////////////////////Funçoes gerais/multiusos/////////////////
int procura_ficheiro(char *nomefile,char *str);
int menu(lCIDADE lista_cidades, lUSER lista_users);
int main();



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

lUSER procura_lista_USERS(lUSER lista, char chave[], lUSER *ant, lUSER *actual) {
    *ant = lista;
    *actual = lista->users;
    lUSER final;

    while ((*actual) != NULL && strcmp((*actual)->nome, chave)<0){
        *ant = *actual;
        *actual = (*actual)->users;
    }
    if((*actual) != NULL && strcmp((*actual)->nome, chave) == 0) {
        final = *actual;
        return final;
    }
    if ((*actual) != NULL && strcmp((*actual)->nome, chave) != 0) {
//TODO esta aqui a soluçao do procurar por um nome, pode ser preciso usar nas outras, e se nao encontrar da o primeiro nome da lista

        final = *actual;
        *actual = NULL;     //se o elemento nao for encontrado
    }
    else if((*actual) != NULL && strcmp((*actual)->nome, chave) == 0) {
        final = *actual;
        return final;
    }

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

void imprime_lista_users(lUSER lista) {
    lUSER l = lista->users; //salta o header
    while (l) {
        printf("\nNome: %s\nData de nascimento:%s\n Nr. de telefone: %s\nMorada: %s\n ", l->nome, l->nascimento, l->nr_telefone, l->morada);
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

lPDI procura_lista_PDIS(lPDI lista, char chave[], lPDI *ant, lPDI *actual) {
    *ant = lista;
    *actual = lista->PDIS;
    while ((*actual) != NULL && strcmp((*actual)->n_pdi, chave)<0){
        *ant = *actual;
        *actual = (*actual)->PDIS;
    }
    if ((*actual) != NULL && strcmp((*actual)->n_pdi, chave)!=0)
        *actual = NULL;     //se o elemento nao for encontrado
    //TODO o return pode ter quebrado isto, nao quebrou no user mas verificar dps
    return *actual;
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

//TODO procura pdi hot
lPDI procura_pdi_hot(lCIDADE procurar,char chave[],lCIDADE *ant,lCIDADE *actual) {
    *ant=procurar;
    *actual=procurar->cidades;
    lPDI l_pdi = NULL;
    while ((*actual != NULL)) {

        l_pdi=(*ant)->PDIS;

        while (l_pdi!=NULL && strcmp(l_pdi->n_pdi,chave)!=0){

            l_pdi=l_pdi->PDIS;
        }

        if (l_pdi!=NULL && strcmp(l_pdi->n_pdi,chave)==0 ) {
            l_pdi->popularidade++;
            return l_pdi;
        }
        else if (l_pdi==NULL) {
            *ant=*actual;
            *actual=(*actual)->cidades;
        }
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

void troca_cidade(CIDADE *a, CIDADE *b){
    char *temp = a->n_cidade;
    strcpy(a->n_cidade, b->n_cidade);
    strcpy(b->n_cidade, temp);
}

void Sort_cidade(CIDADE *start){
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
                troca_cidade(ptr1, ptr1->cidades);
                swapped = 1;
            }
            ptr1 = ptr1->cidades;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void troca_user(USER *a, USER *b){
    char *temp = a->nome;
    strcpy(a->nome, b->nome);
    strcpy(b->nome, temp);
}

void Sort_user(USER *start){
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
                troca_user(ptr1, ptr1->users);
                swapped = 1;
            }
            ptr1 = ptr1->users;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void ler_ficheiro_cidades(lCIDADE lista) {
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
            aux->popularidade = 0;
        }
        /*
        else {
            printf("O ficheiro está corrupto");
        }
         */
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


//TODO nao me lembro de adaptar muito isto, ver dps
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


void sel_pref_user(lUSER lista_user, lCIDADE lista_cidade){
    char nome_atual[100];
    lUSER ant, inutil;
    lUSER user_procurado;
    int i, n;
    printf("Escreve o nome do utilizador:\n");
    gets(nome_atual);
//TODO se o user nao for encontrado da default para o primeiro da lista
    user_procurado = procura_lista_USERS(lista_user, nome_atual, &ant, &inutil);

    if (user_procurado == NULL) {
        printf("O utilizador nao foi encontrado\n");
        sel_pref_user(lista_user, lista_cidade);
    }
    else{
        printf("Dados do utilizador:\nNome:%s\nData de nascimento:%s\nNr. de telefone:%s\nMorada:%s\n", user_procurado->nome,user_procurado->nascimento,user_procurado->nr_telefone,user_procurado->morada);
        printf("Indique quantos pontos de interesse quer definir:");
        scanf("%d", &n);
        for(i = 0; i < n; i++){
            char nome_pdi_atual[50];
            printf("Indique o nome do ponto de interesse preferido:\n");
            gets(nome_pdi_atual);
            lCIDADE ant2;
            lCIDADE actual;
            lPDI procura_pdi = procura_pdi_hot(lista_cidade, nome_pdi_atual, &ant2, &actual);

//TODO da sempre que nao encontra
            if (procura_pdi == NULL){
                printf("O ponto de interesse que selecionou nao existe.\n");
                sel_pref_user(lista_user, lista_cidade);
            }
            else {
                user_procurado->lista_pdis_pref[i] = procura_pdi;
            }
        }

    }
}


void placeholder() {
    //so placeholder para switch, etc.
}


int menu(lCIDADE lista_cidades, lUSER lista_users) {
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
            compilar_lista_cidades(lista_cidades);
            imprime_lista_cidades(lista_cidades);
            menu(lista_cidades,lista_users);
        case 2:
            printf("");
            criar_user();
            menu(lista_cidades,lista_users);
        case 3:
            sel_pref_user(lista_users, lista_cidades);
            menu(lista_cidades,lista_users);
        case 4:
            placeholder();
            menu(lista_cidades,lista_users);
        case 5:
            placeholder();
            menu(lista_cidades,lista_users);
        case 6:
            placeholder();
            menu(lista_cidades,lista_users);
        case 7:
            gets(user);
            eliminar_utilizador("utilizadores.txt", 50);
        case 8:
            return 0;
        default:
            printf("Essa não é uma opcao possivel");
            menu(lista_cidades,lista_users);
    }
}

int compilar_lista_cidades(lCIDADE lista){
    ler_ficheiro_cidades(lista);
    Sort_cidade(lista);
}

int compilar_lista_users(lUSER lista){
    ler_users(lista);
    Sort_user(lista);
}

int main() {
    lCIDADE l_cidades;
    l_cidades = cria_lista_cidade();
    lUSER l_users;
    l_users = cria_lista_USERS();


    //menu(l_cidades);           //-> devera ficar ligado no final, desligado para testes com listas ligadas e ficheiros
    //ler_ficheiro_cidades(l_cidades);
    compilar_lista_cidades(l_cidades);
    //criar_user();     //-> testado, funciona ao escrever o user no file
    //imprime_lista_cidades(l_cidades);
    //printf("\n\n\n");
    Sort_cidade(l_cidades);
    imprime_lista_cidades(l_cidades);
    compilar_lista_users(l_users);
    imprime_lista_users(l_users);
    sel_pref_user(l_users, l_cidades);
    return 0;
}

//TODO imprimir pdis por popularidade, adpatar ao codigo depois de implementar a popularidade
/*
void imprime_lcidades_popularidade (Lcidade lista) {
    Lcidade l=lista->prox;
    while(l){
        printf("%s [POPULARIDADE : %d]\n",l->nome,l->popularidade);

    imprime_lpdi_popularidade(l->lista_pdi);

    l=l->prox;
    }
}

void imprime_lpdi_popularidade (Lpdi lista) {
    Lpdi l=lista->prox;
    while(l){
        printf("    --> %s [POPULARIDADE : %d]\n",l->nome,l->popularidade);
        l=l->prox;
    }
}

 void imprime_lcidades_mais_populares (Lcidade lista) {
    Lcidade l=lista->prox;
    while (l) {
        if (l->popularidade >= 2) {
            printf("%s [POPULARIDADE : %d]\n",l->nome,l->popularidade);
            imprime_lpdi_mais_populares(l->lista_pdi);
            printf("\n");
            l=l->prox;
        } else {
            imprime_lpdi_mais_populares(l->lista_pdi);
            l=l->prox;
        }

    }
}

void imprime_lpdi_mais_populares (Lpdi lista) {
    Lpdi l=lista->prox;
    while (l) {
        if (l->popularidade>=2) {
            printf("    --> %s [POPULARIDADE : %d]\n",l->nome,l->popularidade);
            l=l->prox;
        } else {
            l=l->prox;
        }
    }
}
*/

//TODO imprimir a viagem depois de feita, preciso do algoritmo pra decidir a viagem
/*
 void imprime_viagem (Lcidade *lista) {
    printf("\nENTROU1\n");
    Lcidade l=(*lista)->prox;
    int sum=1;
    while (&l != NULL) {
        printf("\nENTROU2\n");
        printf("%d local a visitar : %s\n",sum,l->nome);
        printf("\nENTROU3\n");
        printf("    Pontos de interesse a visitar neste local: \n");
        printf("\nENTROU4\n");
        imprime_lpdi(l->lista_pdi);
        printf("\nENTROU5\n");
        printf("\n");
        printf("\nENTROU6\n");
        l=l->prox;
    }
}
 */



//TODO compara locais, talvez util para fazer a viagem
/*
double compara_locs (Luser lu,Luser utilizador) {
    Luser l = lu->prox;
    double sum=0;

    while (l) {

        if (l->best_local[0]==NULL) {
            l=l->prox;
            continue;
        } else if ((utilizador->best_local[0] == l->best_local[0] ) || (utilizador->best_local[0] == l->best_local[1] ) || (utilizador->best_local[0] == l->best_local[2] )) {
            sum++;
            l=l->prox;
        } else if ((utilizador->best_local[1] == l->best_local[0] ) || (utilizador->best_local[1] == l->best_local[1] ) || (utilizador->best_local[1] == l->best_local[2] )) {
            sum++;
            l=l->prox;
        } else if ((utilizador->best_local[2] == l->best_local[0] ) || (utilizador->best_local[2] == l->best_local[1] ) || (utilizador->best_local[2] == l->best_local[2] )) {
            sum++;
            l=l->prox;
        }
    }
    return sum;
}
 */


