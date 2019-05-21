#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//\\\\\\\\COMENTÁRIOS GERAIS\\\\\\\


//tem de ser lista ligada
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
        *actual = NULL;     //se o elemento nao for encontrado
}


void insere_lista_USERS(lUSER lista,char nome[100],char nascimento[30], char nr_telefone[20], char morada[50], char pdi_hot[50]) {
    lUSER no;
    lUSER ant, inutil;
    no = (lUSER) malloc (sizeof(USER));    //reserva espaço para o nó

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
   //  printf("procura %s %p %p %p %p\n", chave ,lista, *ant, (*ant)->cidades,*actual);
}

lCIDADE insere_lista_CIDADES(lCIDADE lista, char it[]) {
    lCIDADE no;
    lCIDADE ant, inutil;
    no = (lCIDADE) malloc (sizeof(CIDADE));    //reserva espaço para o nó

    if (no != NULL) {
            //printf("struct CITYtest 1: nada\n");
        strcpy(no->n_cidade, it);
            //printf("struct CITYtest2:   %s",no->n_cidade);
        procura_lista_CIDADES (lista, it, &ant, &inutil);
            //printf("struct CITYtest3:   %s",no->n_cidade);
        no->PDIS = cria_lista_PDIS();
            //printf("struct CITYtest4:   %s",no->n_cidade);
        no->cidades = ant->cidades;
            //printf("struct CITYtest5:   %s",no->n_cidade);
        ant->cidades = no;
            //printf("struct CITYtest6:   %s",no->n_cidade);
       // printf("ins %s %p %p %p %p\n", it ,lista, ant, (ant)->cidades,inutil);
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
            //printf("struct PDItest1:   nada\n");
        strcpy(no->n_pdi, nome_pdi);          //e nestes strcpy que bloqueiam algum progresso, sem eles chega ate ao museu do louvre
        strcpy(no->descricao, descricao);
        strcpy(no->horario, horario);
            //printf("struct PDItest2:   %s\n",no->n_pdi);
        procura_lista_PDIS(lista, nome_pdi, &ant, &inutil);
            //printf("struct PDItest3:   %s\n",no->n_pdi);
        no->PDIS = ant->PDIS;
            //printf("struct PDItest4:   %s\n",no->n_pdi);
        ant->PDIS = no;
    }

}

void imprime_lista_PDIS(lPDI lista) {
    lPDI l = lista->PDIS; //salta o header
    while (l) {
        printf("%s ", l->n_pdi);
        printf("%s ", l->descricao);
        printf("%s ", l->horario);
        //imprime_lista_PDIS(l->PDIS);
        l = l->PDIS;
    }
}

void imprime_lista_cidades(lCIDADE lista) {
    lCIDADE l = lista->cidades; //salta o header
    while (l) {
        printf("%s ", l->n_cidade);
        imprime_lista_PDIS(l->PDIS);
        l = l->cidades;
    }
}

//https://stackoverflow.com/questions/33326621/c-program-sort-a-text-file-with-records-alphabetical-order


int organizar_cidade(lCIDADE lista) {
    lCIDADE temp;
    while(lista->cidades != NULL) {
        if (strcmp((lista->n_cidade),lista->cidades->n_cidade) > 0) {
            temp = lista->cidades->cidades;
            lista->cidades->cidades = lista;
            lista->cidades = temp;
        }
    }
    //return strcmp(((CIDADE*)pa)->n_cidade, ((CIDADE*)pb)->n_cidade);
}

int organizar_pdi(lPDI lista) {
    lPDI temp;
    while (lista->PDIS != NULL) {
        if (strcmp((lista->n_pdi), lista->PDIS->n_pdi) > 0) {
            temp = lista->PDIS->PDIS;
            lista->PDIS->PDIS = lista;
            lista->PDIS = temp;
        }
    }
}


void ler_ficheiro(lCIDADE lista) {
    FILE *teste;
    char linha[2000];
    char nome_cidade[100];
    char nome_pdit[50];
    char descricaot[2000];
    char horariot[100];

    lCIDADE aux;
    int count = 1; //counter do numero do pdi, reseta sempre que se vai para uma cidade diferente

    teste = fopen("D:\\Documentos\\Uni\\1a2s\\PPP\\projeto_ppp\\cmake-build-debug\\project.txt", "r");
    while (fgets(linha, 2000, teste) != NULL) {
       // printf("%s", linha + 1);

        if (linha[0]=='*') {
            count = 1; //reseta o counter de pdi
            strcpy(nome_cidade, linha+1);
            //printf("%s", linha+1);
            aux = insere_lista_CIDADES(lista, nome_cidade);
        }

        else if (linha[0]=='&') {
            //printf("PDI nr. %d -> %s", count, linha+1);
            count++; //incrementa o counter do pdi
            strcpy(nome_pdit, linha+1);
        }

//a partir daqui o imprimir cidades para de funcionar

        else if (linha[0]=='#') {
            //printf("Descricao:%s", linha+1);
            strcpy(descricaot, linha+1);
        }

        else if (linha[0]=='$') {
            //printf("Horario: %s", linha+1);
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
    fprintf(users, "£%s\n§%s\n@%s\n!%s\n", nome, nascimento, telefone, morada); //escrever os dados do user, £ para o nome, § para a idade, @ para o telefone
    fclose(users); //fechar ficheiro


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
    scanf("%c", opcao);

    switch(opcao) {
        case '1':
            ler_ficheiro(lista);
            menu(lista);
        case '2':
            criar_user();
            menu(lista);
        case '3':
            placeholder();
            menu(lista);
        case '4':
            placeholder();
            menu(lista);
        case '5':
            placeholder();
            menu(lista);
        case '6':
            placeholder();
            menu(lista);
        case '7':
            gets(user);
            eliminar_utilizador("utilizadores.txt", 50);
        case '8':
            return 0;
        default:
            printf("Essa não é uma opcao possivel");
            menu(lista);
    }
}


int main() {
    lCIDADE l_cidades;
    l_cidades = cria_lista_cidade();
    //menu(l_cidades);           //-> devera ficar ligado no final, desligado para testes com listas ligadas e ficheiros
    ler_ficheiro(l_cidades);
    //criar_user();     //-> testado, funciona ao escrever o user no file
    //imprime_lista_cidades(l_cidades);

    return 0;
}



