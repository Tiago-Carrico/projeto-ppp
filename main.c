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
    lPDI lista_pdis_pref[25];
    lCIDADE cidades_fav[3];
    lUSER users;
}USER;

////////////////////////Funçoes de compilaçao////////////////////
int compilar_lista_cidades(lCIDADE lista);
int compilar_lista_users(lUSER lista);


///////////////////////Funçoes de users/////////////////////////
lUSER cria_lista_USERS();
void procura_lista_USERS(lUSER lista, char chave[], lUSER *ant, lUSER *actual);
lUSER insere_lista_USERS(lUSER lista,char nome[100],char nascimento[30], char nr_telefone[20], char morada[50], char pdi_hot[50]);
void troca_user(USER *a, USER *b);
void Sort_user(USER *start);
void imprime_lista_users(lUSER lista);
void sel_pref_user(lUSER lista_user, lCIDADE lista_cidade);
int criar_user();
int ler_users(lUSER lista);
void eliminar_utilizador(char *nome_fich);


//////////////////////Funçoes de cidades///////////////////////
lCIDADE cria_lista_cidade();
lCIDADE procura_lista_CIDADES(lCIDADE lista, char chave[], lCIDADE *ant, lCIDADE *actual);
lCIDADE insere_lista_CIDADES(lCIDADE lista, char it[]);
void troca_cidade(CIDADE *a, CIDADE *b);
void ler_ficheiro_cidades(lCIDADE lista);
void Sort_cidade(CIDADE *start);
void imprime_lista_cidades(lCIDADE lista);
int lista_vazia_CIDADES(lCIDADE lista);
void imprime_lcidades_popularidade (lCIDADE lista);
void imprime_lcidades_por_popularidade (lCIDADE lista);


/////////////////////Funçoes de PDI's/////////////////////////
lPDI cria_lista_PDIS();
lPDI procura_lista_PDIS(lPDI lista, char chave[], lPDI *ant, lPDI *actual);
void insere_lista_PDIS(lPDI lista,char nome_pdi[100],char descricao[2000], char horario[100]);
void imprime_lista_PDIS(lPDI lista);
lPDI procura_pdi_hot(lCIDADE procurar,char chave[],lCIDADE *ant,lCIDADE *actual);
void imprime_lpdi_popularidade (lPDI lista);
void imprime_lpdi_por_popularidade (lPDI lista);

////////////////////Funçoes gerais/multiusos/////////////////
int procura_ficheiro(char *nome_fich,char procurar[2000]);
int menu(lCIDADE lista_cidades, lUSER lista_users);
void placeholder();
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

void procura_lista_USERS(lUSER lista, char chave[], lUSER *ant, lUSER *actual) {
    *ant = lista;
    *actual = lista->users;
    if(*actual != NULL) {
    }
    while ((*actual) != NULL && strcmp((*actual)->nome, chave)<0){
        *ant = *actual;
        *actual = (*actual)->users;
        if(*actual != NULL) {
        }
    }

    if ((*actual) != NULL && strcmp((*actual)->nome, chave) != 0) {
        *actual = NULL;
    }
    if(*actual != NULL) {
    }
}


lUSER insere_lista_USERS(lUSER lista,char nome[100],char nascimento[30], char nr_telefone[20], char morada[50], char pdi_hot[50]) {
    lUSER no;
    lUSER ant, inutil;
    no = (lUSER) malloc (sizeof(USER));

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
        imprime_lista_PDIS(l->lista_pdis_pref);
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

lCIDADE procura_lista_CIDADES(lCIDADE lista, char chave[], lCIDADE *ant, lCIDADE *actual) {
    *ant = lista;
    *actual = lista->cidades;
    while ((*actual) != NULL && strcmp((*actual)->n_cidade,  chave)<0){
        *ant = *actual;
        *actual = (*actual)->cidades;
                printf("nope, ainda nao encontrou\n");
    }
    if ((*actual) != NULL && strcmp((*actual)->n_cidade, chave)!=0) {
        *actual = NULL;
    }

                printf("encontrou a cidade\n");
        return *actual;

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

lPDI procura_lista_PDIS(lPDI lista, char chave[], lPDI *ant, lPDI *actual) {
    *ant = lista;
    *actual = lista->PDIS;
    while ((*actual) != NULL && strcmp((*actual)->n_pdi, chave)<0){
        *ant = *actual;
        *actual = (*actual)->PDIS;
    }
    if ((*actual) != NULL && strcmp((*actual)->n_pdi, chave)!=0)
        *actual = NULL;

    return *actual;
}

void insere_lista_PDIS(lPDI lista,char nome_pdi[100],char descricao[2000], char horario[100]) {
    lPDI no;
    lPDI ant, inutil;
    no = (lPDI) malloc (sizeof(PDI));

    if (no != NULL) {

        strcpy(no->n_pdi, nome_pdi);
        strcpy(no->descricao, descricao);
        strcpy(no->horario, horario);
        no->popularidade = 0;
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

lCIDADE procura_lcidades_best (lCIDADE lista,char chave[],lCIDADE *ant,lCIDADE *actual)
{
    *ant=lista;
    *actual=lista->cidades;
    while ((*actual)!=NULL && strcmp((*actual)->n_cidade,chave) < 0) {
        *ant = *actual;
        *actual = (*actual)->cidades;
    }
        if ((*actual) != NULL && strcmp((*actual)->n_cidade, chave) != 0)
            *actual = NULL;

    return *actual;
}


lCIDADE procura_cidades_best(lCIDADE procurar,char chave[],lCIDADE *ant,lCIDADE *actual) {
    *ant = procurar;
    *actual = procurar->cidades;
    lCIDADE l_cidade = NULL;
    while ((*actual != NULL)) {
        l_cidade = (*ant)->cidades;
        while (l_cidade != NULL && strcmp(l_cidade->n_cidade, chave) != 0) {
            l_cidade = l_cidade->cidades;
        }

        if (l_cidade != NULL && strcmp(l_cidade->n_cidade, chave) == 0) {
            l_cidade->popularidade++;
            return l_cidade;

        }
        else if (l_cidade == NULL) {
            *ant = *actual;
            *actual = (*actual)->cidades;
        }
    }
    return NULL;
}

lPDI procura_pdi_hot(lCIDADE procurar,char chave[],lCIDADE *ant,lCIDADE *actual) {
    *ant = procurar;
    *actual = procurar->cidades;
    lPDI l_pdi = NULL;
    while ((*actual != NULL)) {
        l_pdi = (*ant)->PDIS;
        while (l_pdi != NULL && strcmp(l_pdi->n_pdi, chave) != 0) {
            l_pdi = l_pdi->PDIS;
        }

        if (l_pdi != NULL && strcmp(l_pdi->n_pdi, chave) == 0) {
            l_pdi->popularidade++;
            return l_pdi;

        }
        else if (l_pdi == NULL) {
            *ant = *actual;
            *actual = (*actual)->cidades;
        }
    }
}


void imprime_lista_cidades(lCIDADE lista) {
    lCIDADE l = lista->cidades;
    while (l) {
        printf("\n\n%s\n ", l->n_cidade);
        imprime_lista_PDIS(l->PDIS);
        l = l->cidades;
    }
}


void troca_cidade(CIDADE *a, CIDADE *b){
    char *temp = a->n_cidade;
    strcpy(a->n_cidade, b->n_cidade);
    strcpy(b->n_cidade, temp);
}

void Sort_cidade(CIDADE *start){
    int trocado, i;
    CIDADE *ptr1;
    CIDADE *lptr = NULL;


    if (start == NULL)
        return;

    do
    {
        trocado = 0;
        ptr1 = start;

        while (ptr1->cidades != lptr)
        {
            if (strcmp(ptr1->n_cidade, ptr1->cidades->n_cidade) > 0)
            {
                troca_cidade(ptr1, ptr1->cidades);
                trocado = 1;
            }
            ptr1 = ptr1->cidades;
        }
        lptr = ptr1;
    }
    while (trocado);
}

void troca_user(USER *a, USER *b){
    char *temp = a->nome;
    strcpy(a->nome, b->nome);
    strcpy(b->nome, temp);
}

void Sort_user(USER *start){
    int trocado, i;
    USER *ptr1;
    USER *lptr = NULL;

    if (start == NULL)
        return;

    do
    {
        trocado = 0;
        ptr1 = start;

        while (ptr1->users != lptr)
        {
            if (strcmp(ptr1->nome, ptr1->users->nome) > 0)
            {
                troca_user(ptr1, ptr1->users);
                trocado = 1;
            }
            ptr1 = ptr1->users;
        }
        lptr = ptr1;
    }
    while (trocado);
}

void ler_ficheiro_cidades(lCIDADE lista) {
    FILE *teste;
    char linha[2000];
    char nome_cidade[100];
    char nome_pdit[50];
    char descricaot[1000];
    char horariot[100];
    lCIDADE aux;

    teste = fopen("project.txt", "r");
    while (fgets(linha, 2000, teste) != NULL) {

        if (linha[0]=='*') {
            strcpy(nome_cidade, linha+1);
            aux = insere_lista_CIDADES(lista, nome_cidade);
        }

        else if (linha[0]=='&') {
            strcpy(nome_pdit, linha+1);
            nome_pdit[strlen(nome_pdit)-1]='\0';
        }

        else if (linha[0]=='#') {
            strcpy(descricaot, linha+1);
        }

        else if (linha[0]=='$') {
            strcpy(horariot, linha+1);
            insere_lista_PDIS(aux->PDIS, nome_pdit, descricaot, horariot);
            aux->popularidade = 0;
        }
    }
    fclose(teste);
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
    fprintf(users, "+%s\n?%s\n@%s\n!%s\n", nome, nascimento, telefone, morada);
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

    users = fopen("utilizadores.txt", "r");
    while (fgets(linha, 2000, users) != NULL) {

        if (linha[0]=='+') {
            linha[strlen(linha)-1]='\0';
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

void eliminar_utilizador(char *nome_fich){
    FILE *file_names,*file_copia;
    char ch[1000];
    char str[8];
    char nome[1000];
    char linha[1000];
    gets(linha);

    file_names = fopen(nome_fich,"r");
    file_copia = fopen("copia.txt","w");
    int num_linha = 1;
    int linha_apagar = procura_ficheiro(nome_fich,linha) +1;

    char teste[] = "fucking hell save me";
    char buffer[100];

    while (fgets(ch, 1000, file_names) != NULL){
        if((num_linha != linha_apagar) && (num_linha != linha_apagar + 1) && (num_linha != linha_apagar + 2) && (num_linha != linha_apagar + 3)){
            fprintf(file_copia, "%s", ch);
            num_linha++;
        }
        else {
            fputs("", file_copia);
            num_linha++;
        }
    }


    fclose( file_names );
    fclose( file_copia );

    if(fclose(file_names) == 0)
        printf("ok");
    else
        printf("1 fclose falhou");

    if(fclose(file_copia) == 0)
        printf("ok2");
    else
        printf("2 fclose falhou");

    int ret = remove(nome_fich);
    remove(nome_fich);
    printf("remove %d",ret);
    int rev = rename("copia.txt",nome_fich);
    rename("copia.txt",nome_fich);
    printf("rename: %d", rev);
}

int procura_ficheiro(char* nome_fich, char procurar[2000]) {
    FILE *file_procura;
    char linha[2000];
    int nr_linha = 0;

    file_procura = fopen(nome_fich, "r");
    while(fgets(linha, 2000, file_procura) != NULL) {
        strcpy(linha, linha+1);
        linha[strlen(linha)-1]='\0';
        if(strcmp(linha, procurar) == 0) {
            return nr_linha;
        }
        else {
            nr_linha++;
        }
    }
    fclose(file_procura);
}

void def_locs_pref(lCIDADE lista_cidade, lUSER lista_user) {
    char nome_atual[100];
    int j;
    lUSER ant, user_procurado;
    //TODO fuck shit fuck shit fuck why dont you fucking work

    do {
        printf("Escreve o nome do utilizador:\n");
        gets(nome_atual);
        procura_lista_USERS(lista_user, nome_atual, &ant, &user_procurado);

    }while (user_procurado == NULL);

    printf("Indique as suas tres cidades preferidas:\n");
    printf("Indique o nome da cidade:\n");
    for(j = 0; j < 3 ; j++){
        char nome_cidade_atual[50];
        lCIDADE ant_cidade,actual_cidade;
        printf("Indique o nome da cidade:\n");
        gets(nome_cidade_atual);
        lCIDADE procura_cidade = procura_cidades_best(lista_cidade, nome_cidade_atual, &ant_cidade, &actual_cidade);

                printf("cidade_actual: %s", procura_cidade->n_cidade);
                printf("cidade: %s\n", procura_cidade->n_cidade);

        if (procura_cidade == NULL && j != 0){
            printf("A cidade que selecionou nao existe.\n");
            sel_pref_user(lista_user, lista_cidade);
        }

        else {
                    printf("encontrei a cidade");
            user_procurado->cidades_fav[j] = procura_cidade;
        }
    }

}


void sel_pref_user(lUSER lista_user, lCIDADE lista_cidade){
    char nome_atual[100];
    char pdi_hot[100];
    lUSER ant;
    lUSER user_procurado;
    lCIDADE ant_hot;
    lCIDADE actual_hot;

    int i, n, j;
    do {
        printf("Escreve o nome do utilizador:\n");
        gets(nome_atual);
        procura_lista_USERS(lista_user, nome_atual, &ant, &user_procurado);

    }while (user_procurado == NULL);

        printf("Dados do utilizador:\nNome:%s\nData de nascimento:%s\nNr. de telefone:%s\nMorada:%s\n", user_procurado->nome,user_procurado->nascimento,user_procurado->nr_telefone,user_procurado->morada);

        printf("Indique o ponto de interesse ""hot");
        gets(pdi_hot);
        lPDI procurado_hot = procura_pdi_hot(lista_cidade, pdi_hot, &ant_hot, &actual_hot);
        if(procurado_hot == NULL){
            printf("O ponto de interesse não foi encontrado");
            sel_pref_user(lista_user, lista_cidade);
        }
        else{
            user_procurado->pdi_hot = procurado_hot;
        }


        printf("Indique quantos pontos de interesse quer definir:");
        scanf("%d", &n);
        printf("Indique o nome do ponto de interesse preferido:\n");
        for(i = 0; i <= n ; i++){
            char nome_pdi_atual[50];
            gets(nome_pdi_atual);
            lCIDADE ant2;
            lCIDADE actual;
            lPDI procura_pdi = procura_pdi_hot(lista_cidade, nome_pdi_atual, &ant2, &actual);

            if (procura_pdi == NULL && i != 0){
                printf("O ponto de interesse que selecionou nao existe.\n");
                sel_pref_user(lista_user, lista_cidade);
            }

            else if(procura_pdi != NULL && i != 0) {
                user_procurado->lista_pdis_pref[i] = procura_pdi;
                printf("Indique o nome do ponto de interesse preferido:\n");
            }
        }

}

void imprime_lcidades_popularidade (lCIDADE lista) {
    lCIDADE l=lista->cidades;
    while(l){
        printf("%s Popularidade: %d\n",l->n_cidade,l->popularidade);
        imprime_lpdi_popularidade(l->PDIS);
        l=l->cidades;
    }
}

void imprime_lpdi_popularidade (lPDI lista) {
    lPDI l=lista->PDIS;
    while(l){
        printf("\t%s Popularidade: %d\n",l->n_pdi,l->popularidade);
        l=l->PDIS;
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
    printf("\n3)Ver todos os utilizadores registados");
    printf("\n4)Selecionar preferencias para um utilizador existente");
    printf("\n5)Ver os destinos pela sua popularidade");
    printf("\n6)Construir uma viagem baseada nos gostos de um utilizador");
    printf("\n7)Eliminar um utilizador");
    printf("\n8)Acabar a sessao");
    printf("\n---------------------------------------------------------------------------------------------------------------\n");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            imprime_lista_cidades(lista_cidades);
            menu(lista_cidades,lista_users);
        case 2:
            criar_user();
            menu(lista_cidades,lista_users);
        case 3:
            imprime_lista_users(lista_users);
        case 4:
            sel_pref_user(lista_users, lista_cidades);
            menu(lista_cidades,lista_users);
        case 5:
            imprime_lcidades_por_popularidade(lista_cidades);
            menu(lista_cidades,lista_users);
        case 6:
            printf("Ainda nao foi implementado");
            menu(lista_cidades,lista_users);
        case 7:
            gets(user);
            eliminar_utilizador("utilizadores.txt");
            menu(lista_cidades,lista_users);
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

    compilar_lista_users(l_users);
    compilar_lista_cidades(l_cidades);

    menu(l_cidades,l_users);

    return 0;
}


void imprime_lcidades_por_popularidade (lCIDADE lista) {
    lCIDADE l=lista->cidades;
    while (l) {
        if (l->popularidade >= 1) {
            printf("%s Popularidade: %d\n",l->n_cidade,l->popularidade);
            imprime_lpdi_por_popularidade(l->PDIS);
            printf("\n");
            l=l->cidades;
        } else {
            imprime_lpdi_por_popularidade(l->PDIS);
            l=l->cidades;
        }

    }
}

void imprime_lpdi_por_popularidade (lPDI lista) {
    lPDI l=lista->PDIS;
    while (l) {
        if (l->popularidade>=1) {
            printf("%s Popularidade: %d\n",l->n_pdi,l->popularidade);
            l=l->PDIS;
        } else {
            l=l->PDIS;
        }
    }
}

